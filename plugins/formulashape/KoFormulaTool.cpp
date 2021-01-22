/* This file is part of the KDE project
   Copyright (C) 2006 Martin Pfeiffer <hubipete@gmx.net>
                 2009 Jeremias Epperlein <jeeree@web.de>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
 */

#include "KoFormulaTool.h"

#include "KoFormulaShape.h"
#include "FormulaToolWidget.h"
#include "BasicElement.h"
#include "FormulaEditor.h"
#include "FormulaDebug.h"

#include <KoCanvasBase.h>
#include <KoPointerEvent.h>
#include <KoSelection.h>
#include <KoShapeController.h>
#include <KoIcon.h>

#include <klocalizedstring.h>

#include <QKeyEvent>
#include <QAction>
#include <QPainter>
#include <QFile>
#include <QFileDialog>

#include <KoShapeSavingContext.h>
#include <KoShapeLoadingContext.h>
#include <KoOdfLoadingContext.h>
#include <KoOdfStylesReader.h>
#include "FormulaCommand.h"
#include "FormulaCommandUpdate.h"
#include <KoXmlReader.h>
#include <KoXmlWriter.h>
#include <KoGenStyles.h>
#include <KoEmbeddedDocumentSaver.h>
#include "FormulaRenderer.h"
#include <QClipboard>

// this adds const to non-const objects (like std::as_const)
template <typename T> Q_DECL_CONSTEXPR typename std::add_const<T>::type &koAsConst(T &t) noexcept { return t; }
// prevent rvalue arguments:
template <typename T> void koAsConst(const T &&) = delete;


KoFormulaTool::KoFormulaTool( KoCanvasBase* canvas ) : KoToolBase( canvas ),
                                                       m_formulaShape( 0 ),
                                                       m_formulaEditor( 0 )
{
    setupActions();
    setTextMode(true);
}

KoFormulaTool::~KoFormulaTool()
{
    if( m_formulaEditor ) {
        m_cursorList.removeAll(m_formulaEditor);
        delete m_formulaEditor;
    }
    foreach (FormulaEditor* tmp, m_cursorList) {
        delete tmp;
    }
}

void KoFormulaTool::activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes)
{
    Q_UNUSED(toolActivation);
    foreach (KoShape *shape, shapes) {
        m_formulaShape = dynamic_cast<KoFormulaShape*>( shape );
        if( m_formulaShape )
            break;
    }
    
    if( m_formulaShape == 0 )  // none found
    {
        emit done();
        return;
    }
    useCursor(Qt::IBeamCursor);
    m_formulaEditor=0;
    for (int i = 0; i < m_cursorList.count(); i++) {
        FormulaEditor* editor = m_cursorList[i];
        FormulaData* formulaData=m_formulaShape->formulaData();
        if (editor->formulaData() == formulaData) {
            //we have to check if the cursors current element is actually a 
            //child of the m_formulaShape->formulaData()
            m_cursorList.removeAll(editor);
            if (formulaData->formulaElement()->hasDescendant(editor->cursor().currentElement())) {
                if (editor->cursor().isAccepted()) {
                    debugFormula << "Found old cursor";
                    m_formulaEditor=editor;
                    break;
                }
            }
            delete editor;
        }
    }
    if (m_formulaEditor==0) {
        //TODO: there should be a extra constructor for this
        m_formulaEditor = new FormulaEditor( m_formulaShape->formulaData());
    }
    connect(m_formulaShape->formulaData(), SIGNAL(dataChanged(FormulaCommand*,bool)), this, SLOT(updateCursor(FormulaCommand*,bool)));
    for (const TemplateAction &templateAction : koAsConst(m_templateActions)) {
        connect(templateAction.action, &QAction::triggered, this, [this, templateAction] { insert(templateAction.data); });
    }
    //Only for debugging:
    connect(action("write_elementTree"),SIGNAL(triggered(bool)), m_formulaShape->formulaData(), SLOT(writeElementTree()));
}

void KoFormulaTool::deactivate()
{
    for (const TemplateAction &templateAction : koAsConst(m_templateActions)) {
        disconnect(templateAction.action, &QAction::triggered, this, nullptr);
    }
    disconnect(m_formulaShape->formulaData(),0,this,0);
    if (canvas()) {
        m_cursorList.append(m_formulaEditor);
        debugFormula << "Appending cursor";
    }
    if (m_cursorList.count() > 20) { // don't let it grow indefinitely
        delete m_cursorList.takeAt(0);
    }
    m_formulaShape = 0;
}


void KoFormulaTool::updateCursor(FormulaCommand* command, bool undo)
{
    if (command!=0) {
        debugFormula << "Going to change cursor";
        command->changeCursor(m_formulaEditor->cursor(),undo);
    } else {
        debugFormula << "Going to reset cursor";
        resetFormulaEditor();
    }
    repaintCursor();
}


void KoFormulaTool::paint( QPainter &painter, const KoViewConverter &converter )
{
    painter.save();
    // transform painter from view coordinate system to document coordinate system
    // remember that matrix multiplication is not commutative so painter.matrix
    // has to come last
    painter.setTransform(m_formulaShape->absoluteTransformation(&converter) * painter.transform());
    KoShape::applyConversion(painter,converter);
    m_formulaShape->formulaRenderer()->paintElement(painter,m_formulaShape->formulaData()->formulaElement(),true);
    m_formulaEditor->paint( painter );
    painter.restore();
}

void KoFormulaTool::repaintCursor()
{
    canvas()->updateCanvas( m_formulaShape->boundingRect() );
}

void KoFormulaTool::mousePressEvent( KoPointerEvent *event )
{
    // Check if the event is valid means inside the shape 
    if(!m_formulaShape->boundingRect().contains( event->point )) {
        return;
    }
    // transform the global coordinates into shape coordinates
    QPointF p = m_formulaShape->absoluteTransformation(0).inverted().map( event->point );
    if (event->modifiers() & Qt::ShiftModifier) {
        m_formulaEditor->cursor().setSelecting(true);
    } else {
        m_formulaEditor->cursor().setSelecting(false);
    }
    // set the cursor to the element the user clicked on
    m_formulaEditor->cursor().setCursorTo( p );

    repaintCursor();
    event->accept();
}

void KoFormulaTool::mouseDoubleClickEvent( KoPointerEvent *event )
{
    if( !m_formulaShape->boundingRect().contains( event->point ) ) {
        return;
    }
    // transform the global coordinates into shape coordinates
    QPointF p = m_formulaShape->absoluteTransformation(0).inverted().map( event->point );
    
    //clear the current selection
    m_formulaEditor->cursor().setSelecting(false);
    //place the cursor
    m_formulaEditor->cursor().setCursorTo(p);
    m_formulaEditor->cursor().selectElement(m_formulaEditor->cursor().currentElement());
    repaintCursor();
    event->accept();
}

void KoFormulaTool::mouseMoveEvent( KoPointerEvent *event )
{
//     Q_UNUSED( event )
    if (!(event->buttons() & Qt::LeftButton)) {
	return;
    }
    // Check if the event is valid means inside the shape
    if( !m_formulaShape->boundingRect().contains( event->point ) )
        debugFormula << "Getting most probably invalid mouseMoveEvent";
    
    // transform the global coordinates into shape coordinates
    QPointF p = m_formulaShape->absoluteTransformation(0).inverted().map( event->point );
    //TODO Implement drag and drop of elements
    m_formulaEditor->cursor().setSelecting(true);
    m_formulaEditor->cursor().setCursorTo( p );
    repaintCursor();
    event->accept();
}

void KoFormulaTool::mouseReleaseEvent( KoPointerEvent *event )
{
    Q_UNUSED( event )

    // TODO Implement drag and drop
}

void KoFormulaTool::keyPressEvent( QKeyEvent *event )
{
    FormulaCommand *command=0;
    if( !m_formulaEditor )
        return;

    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right || 
        event->key() == Qt::Key_Up || event->key() == Qt::Key_Down ||
        event->key() == Qt::Key_Home || event->key() == Qt::Key_End ) {
        if (event->modifiers() & Qt::ShiftModifier) {
            m_formulaEditor->cursor().setSelecting(true);
        } else {
            m_formulaEditor->cursor().setSelecting(false);
        }
    }
    switch( event->key() )                           // map key to movement or action
    {
        case Qt::Key_Backspace:
            m_formulaShape->update();
            command=m_formulaEditor->remove( true );
            m_formulaShape->updateLayout();
            m_formulaShape->update();
            break;
        case Qt::Key_Delete:
            m_formulaShape->update();
            command=m_formulaEditor->remove( false );
            m_formulaShape->updateLayout();
            m_formulaShape->update();
            break;
        case Qt::Key_Left:
            m_formulaEditor->cursor().move( MoveLeft );
            break;
        case Qt::Key_Up:
            m_formulaEditor->cursor().move( MoveUp );
            break;
        case Qt::Key_Right:
            m_formulaEditor->cursor().move( MoveRight );
            break;
        case Qt::Key_Down:
            m_formulaEditor->cursor().move( MoveDown );
            break;
        case Qt::Key_End:
            m_formulaEditor->cursor().moveEnd();
            break;
        case Qt::Key_Home:
            m_formulaEditor->cursor().moveHome();
            break;
        default:
            if( event->text().length() != 0 ) {
                command=m_formulaEditor->insertText( event->text() );
            }
    }
    if (command!=0) {
        canvas()->addCommand(new FormulaCommandUpdate(m_formulaShape,command));
    }
    repaintCursor();
    event->accept();
}

void KoFormulaTool::keyReleaseEvent( QKeyEvent *event )
{
    event->accept();
}

void KoFormulaTool::remove( bool backSpace )
{
    m_formulaShape->update();
    m_formulaEditor->remove( backSpace );
    m_formulaShape->updateLayout();
    m_formulaShape->update();
}

void KoFormulaTool::insert( const QString& action )
{
    FormulaCommand *command;
    m_formulaShape->update();
    command=m_formulaEditor->insertMathML( action );
    if (command!=0) {
        canvas()->addCommand(new FormulaCommandUpdate(m_formulaShape, command));
    }
}

void KoFormulaTool::changeTable ( QAction* action )
{
    FormulaCommand *command;
    m_formulaShape->update();
    bool row=action->data().toList()[0].toBool();
    bool insert=action->data().toList()[1].toBool();
    command=m_formulaEditor->changeTable(insert,row);
    if (command!=0) {
        canvas()->addCommand(new FormulaCommandUpdate(m_formulaShape, command));
    }
}

void KoFormulaTool::insertSymbol ( const QString& symbol )
{
    FormulaCommand *command;
    m_formulaShape->update();
    command=m_formulaEditor->insertText( symbol );
    if (command!=0) {
        canvas()->addCommand(new FormulaCommandUpdate(m_formulaShape, command));
    }
}


QWidget* KoFormulaTool::createOptionWidget()
{
    FormulaToolWidget* options = new FormulaToolWidget( this );
    options->setFormulaTool( this );
    return options;
}

KoFormulaShape* KoFormulaTool::shape()
{
    return m_formulaShape;
}


FormulaEditor* KoFormulaTool::formulaEditor()
{
    return m_formulaEditor;
}


void KoFormulaTool::resetFormulaEditor() {
    m_formulaEditor->setData(m_formulaShape->formulaData());
    FormulaCursor cursor(FormulaCursor(m_formulaShape->formulaData()->formulaElement(),false,0,0));
    m_formulaEditor->setCursor(cursor);
    //if the cursor is not allowed at the beginning of the formula, move it right
    //TODO: check, if this can ever happen
    if ( !m_formulaEditor->cursor().isAccepted() ) {
        m_formulaEditor->cursor().move(MoveRight);
    }
}

void KoFormulaTool::loadFormula()
{
    // get an filepath
    const QString fileName = QFileDialog::getOpenFileName();
    if( fileName.isEmpty() || !shape() )
        return;

    // open the file the filepath points to
    QFile file( fileName );
    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return;

    KoOdfStylesReader stylesReader;
    KoOdfLoadingContext odfContext( stylesReader, 0 );
    KoShapeLoadingContext shapeContext(odfContext, canvas()->shapeController()->resourceManager());

    // setup a DOM structure and start the actual loading process
    KoXmlDocument tmpDocument;
    tmpDocument.setContent( &file, false, 0, 0, 0 );
    FormulaElement* formulaElement = new FormulaElement();     // create a new root element
    formulaElement->readMathML( tmpDocument.documentElement() );     // and load the new formula
    FormulaCommand* command=new FormulaCommandLoad(m_formulaShape->formulaData(),formulaElement);
    canvas()->addCommand(new FormulaCommandUpdate(m_formulaShape, command));
}

void KoFormulaTool::saveFormula()
{
    const QString filePath = QFileDialog::getSaveFileName();
    if( filePath.isEmpty() || !shape() )
        return;

    QFile file( filePath );
    KoXmlWriter writer( &file );
    KoGenStyles styles;
    KoEmbeddedDocumentSaver embeddedSaver;
    KoShapeSavingContext shapeSavingContext( writer, styles, embeddedSaver );

    m_formulaShape->formulaData()->saveMathML( shapeSavingContext );
}

void KoFormulaTool::setupActions()
{
    //notice that only empty mrows hows parent is a inferred mrow are treated as placeholders
    //this causes the <mrow><mrow/></mrow> constructs
    addTemplateAction(i18n("Insert fenced element"), "insert_fence","<mfenced><mrow/></mfenced>", koIconNameCStr("brackets"));
    addTemplateAction(i18n("Insert enclosed element"), "insert_enclosed",
                      "<menclosed><mrow/></menclosed>", koIconNameCStr("enclosed"));

    addTemplateAction(i18n("Insert root"), "insert_root","<mroot><mrow><mrow/></mrow></mroot>", koIconNameCStr("root"));
    addTemplateAction(i18n("Insert square root"), "insert_sqrt","<msqrt><mrow/></msqrt>", koIconNameCStr("sqrt"));

    addTemplateAction(i18n("Insert fraction"), "insert_fraction",
                      "<mfrac><mrow><mrow/></mrow><mrow/></mfrac>", koIconNameCStr("frac"));
    addTemplateAction(i18n("Insert bevelled fraction"), "insert_bevelled_fraction",
                      "<mfrac bevelled=\"true\"><mrow><mrow/></mrow><mrow/></mfrac>", koIconNameCStr("bevelled"));

    addTemplateAction(i18n("Insert 3x3 table"), "insert_33table",
                      "<mtable><mtr><mtd><mrow /></mtd><mtd></mtd><mtd></mtd></mtr>" \
                      "<mtr><mtd></mtd><mtd></mtd><mtd></mtd></mtr>" \
                      "<mtr><mtd></mtd><mtd></mtd><mtd></mtd></mtr></mtable>", koIconNameCStr("matrix"));
    addTemplateAction(i18n("Insert 2 dimensional vector"), "insert_21table",
                      "<mtable><mtr><mtd><mrow/></mtd></mtr><mtr><mtd></mtd></mtr></mtable>", koIconNameCStr("vector"));

    addTemplateAction(i18n("Insert subscript"), "insert_subscript",
                      "<msub><mrow><mrow/></mrow><mrow/></msubsup>", koIconNameCStr("rsub"));
    addTemplateAction(i18n("Insert superscript"), "insert_supscript",
                      "<msup><mrow><mrow/></mrow><mrow/></msup>", koIconNameCStr("rsup"));
    addTemplateAction(i18n("Insert sub- and superscript"), "insert_subsupscript",
                      "<msubsup><mrow><mrow/></mrow><mrow/><mrow/></msubsup>", koIconNameCStr("rsubup"));
    addTemplateAction(i18n("Insert overscript"), "insert_overscript",
                      "<mover><mrow><mrow/></mrow><mrow/></mover>", koIconNameCStr("gsup"));
    addTemplateAction(i18n("Insert underscript"), "insert_underscript",
                      "<munder><mrow><mrow/></mrow><mrow/></munder>", koIconNameCStr("gsub"));
    addTemplateAction(i18n("Insert under- and overscript"), "insert_underoverscript",
                      "<munderover><mrow><mrow/></mrow><mrow/><mrow/></munderover>", koIconNameCStr("gsubup"));

    //only for debugging
    QAction * action;
    action = new QAction( "Debug - writeElementTree" , this );
    addAction( "write_elementTree", action );

    QList<QVariant> list;
    action = new QAction( i18n( "Insert row" ), this );
    list<<true<<true;
    action->setData( list);
    list.clear();
    addAction( "insert_row", action );
    action->setIcon(koIcon("insrow"));

    action = new QAction( i18n( "Insert column" ), this );
    list<<false<<true;
    action->setData( list);
    list.clear();
    addAction( "insert_column", action );
    action->setIcon(koIcon("inscol"));

    action = new QAction( i18n( "Remove row" ), this );
    list<<true<<false;
    action->setData( list);
    list.clear();
    addAction( "remove_row", action );
    action->setIcon(koIcon("remrow"));

    action = new QAction( i18n( "Remove column" ), this );
    list<<false<<false;
    action->setData( list);
    list.clear();
    addAction( "remove_column", action );
    action->setIcon(koIcon("remcol"));

}


void KoFormulaTool::addTemplateAction(const QString &caption, const QString &name, const QString &data,
                                      const char *iconName)
{
    QAction *action = new QAction( caption, this );
    addAction(name , action);
    action->setIcon(QIcon::fromTheme(QLatin1String(iconName)));
    m_templateActions.push_back(TemplateAction { action, data });
    // the connection takes place when this KoToolBase is activated
}


void KoFormulaTool::copy() const
{
    QApplication::clipboard()->setText("test");
}

void KoFormulaTool::deleteSelection()
{
    KoToolBase::deleteSelection();
}

bool KoFormulaTool::paste()
{
    const QMimeData* data=QApplication::clipboard()->mimeData();
    if (data->hasFormat("text/plain")) {
        debugFormula << data->text();
        FormulaCommand* command=m_formulaEditor->insertText(data->text());
        if (command!=0) {
            canvas()->addCommand(new FormulaCommandUpdate(m_formulaShape,command));
        }
        repaintCursor();
        return true;
    }
    return false;
}

QStringList KoFormulaTool::supportedPasteMimeTypes() const
{
    QStringList tmp;
    tmp << "text/plain";
    tmp << "application/xml";
    return tmp;
}
