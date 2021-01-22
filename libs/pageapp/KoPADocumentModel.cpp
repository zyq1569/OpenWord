/* This file is part of the KDE project
 * Copyright (C) 2007 Jan Hambrecht <jaham@gmx.net>
 * Copyright (C) 2008 Fredy Yanardi <fyanardi@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "KoPADocumentModel.h"

#include "KoPADocument.h"
#include "KoPAPageBase.h"
#include <KoShapePainter.h>
#include <KoShapeManager.h>
#include <KoShapeContainer.h>
#include <KoToolManager.h>
#include <KoPageLayout.h>
#include <KoCanvasBase.h>
#include <KoCanvasController.h>
#include <KoSelection.h>
#include <KoShapeLayer.h>
#include <KoShapeGroup.h>
#include <KoShapeGroupCommand.h>
#include <KoShapeUngroupCommand.h>
#include <KoShapeRenameCommand.h>
#include <KoZoomHandler.h>
#include <KoPAOdfPageSaveHelper.h>
#include <KoDrag.h>
#include <KoPAPastePage.h>
#include <KoIcon.h>

#include <klocalizedstring.h>
#include <PageAppDebug.h>

#include <QMimeData>
#include <QApplication>
#include <QClipboard>
#include <QMenu>
#include <QPainterPath>

#include "commands/KoPAPageMoveCommand.h"

KoPADocumentModel::KoPADocumentModel( QObject* parent, KoPADocument *document )
: KoDocumentSectionModel( parent )
, m_document(0)
, m_master(false)
, m_lastContainer( 0 )
{
    setDocument( document );
}

Qt::DropActions KoPADocumentModel::supportedDragActions() const
{
    return Qt::MoveAction;
}

void KoPADocumentModel::update()
{
    emit layoutAboutToBeChanged();
    emit layoutChanged();
    if (m_document) {
        dataChanged(index(0, 0), index(m_document->pageCount() - 1, columnCount() - 1));
    }
}

int KoPADocumentModel::rowCount( const QModelIndex &parent ) const
{
    if (!m_document) {
        return 0;
    }

    // check if parent is root node
    if ( ! parent.isValid() ) {
        return m_document->pages(m_master).count();
    }

    Q_ASSERT(parent.model() == this);
    Q_ASSERT(parent.internalPointer());

    KoShapeContainer *parentShape = dynamic_cast<KoShapeContainer*>( (KoShape*)parent.internalPointer() );
    if ( ! parentShape ) {
        return 0;
    }

    return parentShape->shapeCount();
}

int KoPADocumentModel::columnCount( const QModelIndex & ) const
{
    return 1;
}

QModelIndex KoPADocumentModel::index( int row, int column, const QModelIndex &parent ) const
{
    if ( !m_document ) {
        return QModelIndex();
    }

    // check if parent is root node
    if ( ! parent.isValid() ) {
        if ( row >= 0 && row < m_document->pages(m_master).count() ) {
            return createIndex( row, column, m_document->pages(m_master).at(row) );
        } else {
            return QModelIndex();
        }
    }

    Q_ASSERT(parent.model() == this);
    Q_ASSERT(parent.internalPointer());

    KoShapeContainer *parentShape = dynamic_cast<KoShapeContainer*>( (KoShape*)parent.internalPointer() );
    if ( ! parentShape ) {
        return QModelIndex();
    }

    if ( row < parentShape->shapeCount() ) {
        return createIndex( row, column, childFromIndex( parentShape, row ) );
    } else {
        return QModelIndex();
    }
}

QModelIndex KoPADocumentModel::parent( const QModelIndex &child ) const
{
    // check if child is root node
    if ( ! child.isValid() || !m_document ) {
        return QModelIndex();
    }

    Q_ASSERT(child.model() == this);
    Q_ASSERT(child.internalPointer());

    KoShape *childShape = static_cast<KoShape*>( child.internalPointer() );
    if ( ! childShape ) {
        return QModelIndex();
    }

    // get the children's parent shape
    KoShapeContainer *parentShape = childShape->parent();
    if ( ! parentShape ) {
        return QModelIndex();
    }

    // get the grandparent to determine the row of the parent shape
    KoShapeContainer *grandParentShape = parentShape->parent();
    if ( ! grandParentShape ) {
        KoPAPageBase* page = dynamic_cast<KoPAPageBase*>( parentShape);
        return createIndex( m_document->pages(m_master).indexOf( page ), 0, parentShape );
    }

    return createIndex( indexFromChild( grandParentShape, parentShape ), 0, parentShape );
}

QVariant KoPADocumentModel::data( const QModelIndex &index, int role ) const
{
    if ( ! index.isValid() || !m_document ) {
        return QVariant();
    }

    Q_ASSERT(index.model() == this);
    Q_ASSERT(index.internalPointer());

    KoShape *shape = static_cast<KoShape*>( index.internalPointer() );

    switch (role)
    {
        case Qt::DisplayRole:
        {
            QString name = shape->name();
            if ( name.isEmpty() ) {
                if ( dynamic_cast<KoPAPageBase *>( shape ) ) {
                    if (m_document->pageType() == KoPageApp::Slide ) {
                        name = i18n("Slide %1",  m_document->pageIndex(dynamic_cast<KoPAPageBase *>(shape)) + 1);
                    } else {
                        name = i18n("Page  %1", m_document->pageIndex(dynamic_cast<KoPAPageBase *>(shape)) + 1);
                    }
                } else if ( dynamic_cast<KoShapeLayer*>( shape ) ) {
                    name = i18n("Layer") + QString(" (%1)").arg(shape->zIndex());
                } else if ( dynamic_cast<KoShapeGroup*>( shape ) ) {
                    name = i18n("Group") + QString(" (%1)").arg(shape->zIndex());
                } else {
                    name = i18n("Shape") + QString(" (%1)").arg(shape->zIndex());
                }
            }
            return name;
        }
        case Qt::DecorationRole: return QVariant();//return shape->icon();
        case Qt::EditRole: return shape->name();
        case Qt::SizeHintRole:
        {
            KoPAPageBase *page = dynamic_cast<KoPAPageBase*>(shape);
            if (page) { // return actual page size for page
                KoPageLayout layout = page->pageLayout();
                return QSize(layout.width, layout.height);
            }
            else
                return shape->size();
        }
        case ActiveRole:
        {
            KoCanvasController * canvasController = KoToolManager::instance()->activeCanvasController();
            KoSelection * selection = canvasController->canvas()->shapeManager()->selection();
            if ( ! selection ) {
                return false;
            }

            /* KoShapeLayer *layer = dynamic_cast<KoShapeLayer*>( shape );
            if ( layer )
                return (layer == selection->activeLayer() );
            else */
            return selection->isSelected( shape );
        }
        case PropertiesRole: return QVariant::fromValue( properties( shape ) );
        case AspectRatioRole:
        {
            QTransform matrix = shape->absoluteTransformation( 0 );
            QRectF bbox = matrix.mapRect( shape->outline().boundingRect() );
            KoShapeContainer *container = dynamic_cast<KoShapeContainer*>( shape );
            if ( container ) {
                bbox = QRectF();
                foreach( KoShape* shape, container->shapes() ) {
                    bbox = bbox.united( shape->outline().boundingRect() );
                }
            }
            return qreal(bbox.width()) / bbox.height();
        }
        default:
            if (role >= int(BeginThumbnailRole)) {
                return createThumbnail( shape, QSize( role - int(BeginThumbnailRole), role - int(BeginThumbnailRole) ) );
            } else {
                return QVariant();
            }
    }
}

Qt::ItemFlags KoPADocumentModel::flags(const QModelIndex &index) const
{
    if ( !m_document ) {
        return 0;
    }

    if ( ! index.isValid() ) {
        return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
    }

    Q_ASSERT(index.model() == this);
    Q_ASSERT(index.internalPointer());

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEditable;
    //if ( dynamic_cast<KoShapeContainer*>( (KoShape*)index.internalPointer() ) )
        flags |= Qt::ItemIsDropEnabled;
    return flags;
}

bool KoPADocumentModel::setData(const QModelIndex &index, const QVariant &value, int role )
{
    if ( ! index.isValid() || !m_document ) {
        return false;
    }

    Q_ASSERT(index.model() == this);
    Q_ASSERT(index.internalPointer());

    KoShape *shape = static_cast<KoShape*>( index.internalPointer() );
    switch (role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            KUndo2Command * cmd = new KoShapeRenameCommand( shape, value.toString() );
            if (dynamic_cast<KoPAPageBase *>(shape)) {
                if (m_document->pageType() == KoPageApp::Slide) {
                    cmd->setText(kundo2_i18n("Rename Slide"));
                } else {
                    cmd->setText(kundo2_i18n("Rename Page"));
                }
            }
            else if (dynamic_cast<KoShapeLayer *>(shape)) {
                cmd->setText(kundo2_i18n("Rename Layer"));
            }
            m_document->addCommand( cmd );
        }   break;
        case PropertiesRole:
            setProperties( shape, value.value<PropertyList>());
            break;
        case ActiveRole:
            /* if (value.toBool())
            {
                KoCanvasController * canvasController = KoToolManager::instance()->activeCanvasController();
                KoSelection * selection = canvasController->canvas()->shapeManager()->selection();

                KoShapeLayer *layer = dynamic_cast<KoShapeLayer*>( shape );
                if ( layer && selection ) {
                    selection->setActiveLayer( layer );
                }
            } */
            break;
        default:
            return false;
    }

    emit dataChanged( index, index );
    return true;
}

KoDocumentSectionModel::PropertyList KoPADocumentModel::properties( KoShape* shape ) const
{
    PropertyList l;

    if (KoPAPageBase *page = dynamic_cast<KoPAPageBase *>(shape)) {
        // The idea is to display the page-number so users know what page-number/slide-number
        // the shape has also in the case the slide has a name (in which case it's not named
        // "Slide [slide-number]" any longer.
        // Maybe we should better use KoTextPage::visiblePageNumber here?
        l << Property(i18n("Slide"), QString::number(m_document->pageIndex(page) + 1));
    }

    l << Property(i18n("Visible"), koIcon("layer-visible-on"), koIcon("layer-visible-off"), shape->isVisible());
    l << Property(i18n("Locked"), koIcon("object-locked"), koIcon("object-unlocked"), shape->isGeometryProtected());
    return l;
}

void KoPADocumentModel::setProperties( KoShape* shape, const PropertyList &properties )
{
    bool oldVisibleState = shape->isVisible();
    bool oldLockedState = shape->isGeometryProtected();

    shape->setVisible( properties.at( 0 ).state.toBool() );
    shape->setGeometryProtected( properties.at( 1 ).state.toBool() );

    if ( ( oldVisibleState != shape->isVisible() ) || ( oldLockedState != shape->isGeometryProtected() ) ) {
        shape->update();
    }
}

QImage KoPADocumentModel::createThumbnail( KoShape* shape, const QSize &thumbSize ) const
{
    QSize size(thumbSize.width(), thumbSize.height());
    KoShapePainter shapePainter;

    KoPAPageBase *page = dynamic_cast<KoPAPageBase*>(shape);
    if (page) { // We create a thumbnail with actual width / height ratio for page
        KoZoomHandler zoomHandler;
        KoPageLayout layout = page->pageLayout();
        qreal ratio = (zoomHandler.resolutionX() * layout.width) / (zoomHandler.resolutionY() * layout.height);
        if ( ratio > 1 ) {
            size.setHeight( size.width() / ratio );
        } else {
            size.setWidth( size.height() * ratio );
        }
        QPixmap pixmap = m_document->pageThumbnail( page, size );
        return pixmap.toImage();
    }

    QList<KoShape*> shapes;
    KoShapeContainer *container = dynamic_cast<KoShapeContainer*>(shape);
    if (container) {
        shapes = container->shapes();
    }
    shapes.append(shape);

    shapePainter.setShapes( shapes );

    QImage thumb( size, QImage::Format_RGB32 );
    // draw the background of the thumbnail
    thumb.fill( QColor( Qt::white ).rgb() );
    shapePainter.paint(thumb);

    return thumb;
}

KoShape * KoPADocumentModel::childFromIndex( KoShapeContainer *parent, int row ) const
{
    return parent->shapes().at(row);
}

int KoPADocumentModel::indexFromChild( KoShapeContainer *parent, KoShape *child ) const
{
    if ( !m_document ) {
        return 0;
    }

    return parent->shapes().indexOf( child );
}

Qt::DropActions KoPADocumentModel::supportedDropActions () const
{
    return Qt::MoveAction | Qt::CopyAction;
}

QStringList KoPADocumentModel::mimeTypes() const
{
    QStringList types;
    types << QLatin1String("application/x-kopalayermodeldatalist");
    return types;
}

QMimeData * KoPADocumentModel::mimeData( const QModelIndexList & indexes ) const
{
    // check if there is data to encode
    if ( ! indexes.count() ) {
        return 0;
    }

    // check if we support a format
    QStringList types = mimeTypes();
    if ( types.isEmpty() ) {
        return 0;
    }

    QMimeData *data = new QMimeData();
    QString format = types[0];
    QByteArray encoded;
    QDataStream stream(&encoded, QIODevice::WriteOnly);

    // encode the data
    QModelIndexList::ConstIterator it = indexes.begin();
    for( ; it != indexes.end(); ++it) {
        stream << QVariant::fromValue( qulonglong( it->internalPointer() ) );
    }

    data->setData(format, encoded);
    return data;
}

bool KoPADocumentModel::dropMimeData( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent )
{
    Q_UNUSED( row );
    Q_UNUSED( column );

    // check if the action is supported
    if ( ! data || action != Qt::MoveAction ) {
        return false;
    }
    // check if the format is supported
    QStringList types = mimeTypes();
    if ( types.isEmpty() ) {
        return false;
    }
    QString format = types[0];
    if ( ! data->hasFormat(format) ) {
        return false;
    }

    QByteArray encoded = data->data( format );
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    QList<KoShape*> shapes;

    // decode the data
    while( ! stream.atEnd() ) {
        QVariant v;
        stream >> v;
        shapes.append( static_cast<KoShape*>( (void*)v.value<qulonglong>() ) );
    }

    QList<KoShape*> toplevelShapes;
    QList<KoShapeLayer*> layers;
    QList<KoPAPageBase *> pages;
    // remove shapes having its parent in the list
    // and separate the layers
    foreach( KoShape * shape, shapes ) {
        // check whether the selection contains page
        // by the UI rules, the selection should contains page only
        KoPAPageBase *page = dynamic_cast<KoPAPageBase *>( shape );
        if ( page ) {
            pages.append( page );
            continue;
        }

        KoShapeContainer *parentShape = shape->parent();
        bool hasParentInList = false;
        while ( parentShape ) {
            if ( shapes.contains( parentShape ) ) {
                hasParentInList = true;
                break;
            }
            parentShape = parentShape->parent();
        }
        if ( hasParentInList ) {
            continue;
        }

        KoShapeLayer * layer = dynamic_cast<KoShapeLayer*>( shape );
        if ( layer ) {
            layers.append( layer );
        } else {
            toplevelShapes.append( shape );
        }
    }

    // dropping to root, only page(s) is allowed
    if (!parent.isValid()) {
        if ( !pages.isEmpty() ) {
            if ( row < 0 ) {
                return false;
            }
            KoPAPageBase *after = (row != 0) ? m_document->pageByIndex(row - 1, false) : 0;
            debugPageApp << "KoPADocumentModel::dropMimeData parent = root, dropping page(s) as root, moving page(s)";
            return doDrop(pages, after, action);
        }
        else {
            debugPageApp << "KoPADocumentModel::dropMimeData parent = root, dropping non-page as root, returning false";
            return false;
        }
    }
    else if (parent.isValid() && !pages.isEmpty()){
        if (parent.row() < 0) {
            return false;
        }
        KoPAPageBase *after;
        if ((m_document->pageIndex(pages.first()) - 1) == parent.row()) {
            after = (parent.row() != 0) ? m_document->pageByIndex(parent.row() - 1, false) : 0;
        }
        else {
            after = (parent.row() > -1) ? m_document->pageByIndex(parent.row(), false) : 0;
        }
        return doDrop(pages, after, action);
    }

    KoShape *shape = static_cast<KoShape*>( parent.internalPointer() );
    KoShapeContainer * container = dynamic_cast<KoShapeContainer*>( shape );
    if ( container ) {
        KoShapeGroup * group = dynamic_cast<KoShapeGroup*>( container );
        if ( group ) {
            debugPageApp <<"KoPADocumentModel::dropMimeData parent = group";
            if ( ! toplevelShapes.count() ) {
                return false;
            }

            emit layoutAboutToBeChanged();
            beginInsertRows( parent, group->shapeCount(), group->shapeCount()+toplevelShapes.count() );

            KUndo2Command * cmd = new KUndo2Command();
            cmd->setText( kundo2_i18n("Reparent shapes") );

            foreach( KoShape * shape, toplevelShapes ) {
                new KoShapeUngroupCommand( shape->parent(), QList<KoShape*>() << shape, QList<KoShape*>(), cmd );
            }

            new KoShapeGroupCommand( group, toplevelShapes, cmd );
            KoCanvasController * canvasController = KoToolManager::instance()->activeCanvasController();
            canvasController->canvas()->addCommand( cmd );

            endInsertRows();
            emit layoutChanged();
        } else {
            debugPageApp <<"KoPADocumentModel::dropMimeData parent = container";
            if ( toplevelShapes.count() ) {
                emit layoutAboutToBeChanged();
                beginInsertRows( parent, container->shapeCount(), container->shapeCount()+toplevelShapes.count() );

                KUndo2Command * cmd = new KUndo2Command();
                cmd->setText( kundo2_i18n("Reparent shapes") );

                QList<bool> clipped;
                QList<bool> inheritsTransform;
                foreach( KoShape * shape, toplevelShapes ) {
                    if ( ! shape->parent() ) {
                        clipped.append( false );
                        inheritsTransform.append(false);
                        continue;
                    }

                    clipped.append( shape->parent()->isClipped( shape ) );
                    inheritsTransform.append(shape->parent()->inheritsTransform(shape));
                    new KoShapeUngroupCommand( shape->parent(), QList<KoShape*>() << shape, QList<KoShape*>(), cmd );
                }
                // shapes are dropped on a container, so add them to the container
                new KoShapeGroupCommand(container, toplevelShapes, clipped, inheritsTransform, cmd);
                KoCanvasController * canvasController = KoToolManager::instance()->activeCanvasController();
                canvasController->canvas()->addCommand( cmd );

                endInsertRows();
                emit layoutChanged();
            } else if ( layers.count() ) {
                KoShapeLayer * layer = dynamic_cast<KoShapeLayer*>( container );
                if ( ! layer ) {
                    return false;
                }

                // TODO layers are dropped on a layer, so change layer ordering
                return false;
            }
        }
    } else {
        debugPageApp <<"KoPADocumentModel::dropMimeData parent = shape";
        if ( ! toplevelShapes.count() ) {
            return false;
        }

        // TODO shapes are dropped on a shape, reorder them
        return false;
    }

    return true;
}

QModelIndex KoPADocumentModel::parentIndexFromShape( const KoShape * child )
{
    if ( !m_document ) {
        return QModelIndex();
    }

    // check if child shape is a layer, and return invalid model index if it is
    const KoShapeLayer *childlayer = dynamic_cast<const KoShapeLayer*>( child );
    if ( childlayer ) {
        return QModelIndex();
    }

    // get the children's parent shape
    KoShapeContainer *parentShape = child->parent();
    if ( ! parentShape ) {
        return QModelIndex();
    }

    // check if the parent is a layer
    KoShapeLayer *parentLayer = dynamic_cast<KoShapeLayer*>( parentShape );


    if ( parentLayer ) {
        KoPAPageBase * page = dynamic_cast<KoPAPageBase*>( parentLayer->parent() );
        if ( page ) {
            return createIndex( m_document->pages(m_master).count() - 1 - m_document->pages(m_master).indexOf( page ), 0, parentLayer );
        }
    }
    // get the grandparent to determine the row of the parent shape
    KoShapeContainer *grandParentShape = parentShape->parent();
    if ( ! grandParentShape ) {
        return QModelIndex();
    }

    return createIndex( indexFromChild( grandParentShape, parentShape ), 0, parentShape );
}

void KoPADocumentModel::setDocument( KoPADocument* document )
{
    if (m_document == document) {
        return;
    }

    if (m_document) {
        disconnect( m_document, SIGNAL(pageAdded(KoPAPageBase*)), this, SLOT(update()) );
        disconnect( m_document, SIGNAL(pageRemoved(KoPAPageBase*)), this, SLOT(update()) );
        disconnect( m_document, SIGNAL(update(KoPAPageBase*)), this, SLOT(update()) );
        disconnect( m_document, SIGNAL(shapeAdded(KoShape*)), this, SLOT(update()) );
        disconnect( m_document, SIGNAL(shapeRemoved(KoShape*)), this, SLOT(update()) );
    }

    beginResetModel();
    m_document = document;
    endResetModel();

    if ( m_document ) {
        connect( m_document, SIGNAL(pageAdded(KoPAPageBase*)), this, SLOT(update()) );
        connect( m_document, SIGNAL(pageRemoved(KoPAPageBase*)), this, SLOT(update()) );
        connect( m_document, SIGNAL(update(KoPAPageBase*)), this, SLOT(update()) );
        connect( m_document, SIGNAL(shapeAdded(KoShape*)), this, SLOT(update()) );
        connect( m_document, SIGNAL(shapeRemoved(KoShape*)), this, SLOT(update()) );
    }
}

void KoPADocumentModel::setMasterMode(bool master)
{
    m_master = master;
    update(); // Rebuild the model
}

bool KoPADocumentModel::doDrop(QList<KoPAPageBase *> pages, KoPAPageBase *pageAfter, Qt::DropAction action)
{
    Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
    bool enableMove = true;

    foreach (KoPAPageBase *page, pages) {
        if (!m_document->pages(false).contains(page)) {
            KoPAPageBase *newPage = page;
            pages.replace(pages.indexOf(page), newPage);
            enableMove = false;
            break;
        }
    }

    if (((modifiers & Qt::ControlModifier) == 0) &&
        ((modifiers & Qt::ShiftModifier) == 0)) {
           QMenu popup;
           QString seq = QKeySequence(Qt::ShiftModifier).toString();
           seq.chop(1);
           QAction *popupMoveAction = new QAction(i18n("&Move Here") + '\t' + seq, this);
           popupMoveAction->setIcon(koIcon("go-jump"));
           seq = QKeySequence(Qt::ControlModifier).toString();
           seq.chop(1);
           QAction *popupCopyAction = new QAction(i18n("&Copy Here") + '\t' + seq, this);
           popupCopyAction->setIcon(koIcon("edit-copy"));
           seq = QKeySequence( Qt::ControlModifier + Qt::ShiftModifier ).toString();
           seq.chop(1);
           QAction *popupCancelAction = new QAction(i18n("C&ancel") + '\t' + QKeySequence(Qt::Key_Escape).toString(), this);
           popupCancelAction->setIcon(koIcon("process-stop"));

           if (enableMove) {
               popup.addAction(popupMoveAction);
           }
           popup.addAction(popupCopyAction);
           popup.addSeparator();
           popup.addAction(popupCancelAction);

           QAction *result = popup.exec(QCursor::pos());

           if (result == popupCopyAction) {
               action = Qt::CopyAction;
           } else if (result == popupMoveAction) {
               action = Qt::MoveAction;
           } else {
               return false;
           }
    } else if ((modifiers & Qt::ControlModifier) != 0) {
        action = Qt::CopyAction;
    } else if ((modifiers & Qt::ShiftModifier) != 0) {
        action = Qt::MoveAction;
    } else {
        return false;
    }

    switch (action) {
    case Qt::MoveAction: {
       KoPAPageMoveCommand *command = new KoPAPageMoveCommand(m_document, pages, pageAfter);
       m_document->addCommand( command );
       if ((m_document->pageIndex(pageAfter) + pages.count()) < m_document->pageCount()) {
            emit requestPageSelection(m_document->pageIndex(pageAfter) + 1, pages.count());
       }
       return true;
    }
    case Qt::CopyAction: {
       // Copy Pages
       KoPAOdfPageSaveHelper saveHelper(m_document, pages);
       KoDrag drag;
       drag.setOdf(KoOdf::mimeType(m_document->documentType()), saveHelper);
       drag.addToClipboard();
       //Paste Pages
       const QMimeData * data = QApplication::clipboard()->mimeData();
       static const KoOdf::DocumentType documentTypes[] = { KoOdf::Graphics, KoOdf::Presentation };

       for (unsigned int i = 0; i < sizeof(documentTypes) / sizeof(KoOdf::DocumentType); ++i) {
           if (data->hasFormat( KoOdf::mimeType(documentTypes[i]))) {
               KoPAPastePage paste(m_document, pageAfter);
               paste.paste(documentTypes[i], data);
               break;
           }
       }
       emit requestPageSelection(m_document->pageIndex(pageAfter) + 1, sizeof(documentTypes) / sizeof(KoOdf::DocumentType) - 1);
       return true;
    }
    default:
       qDebug("Unknown action: %d ", (int)action);
       return false;
    }
    return false;
}
