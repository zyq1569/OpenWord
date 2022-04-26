/* This file is part of the KDE project
   Copyright 2007 Montel Laurent <montel@kde.org>
   Copyright 2011 Silvio Heinrich <plassy@web.de>

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

#include "PictureTool.h"
#include "PictureShape.h"
#include "ChangeImageCommand.h"
#include "ClipCommand.h"
#include "CropWidget.h"

#include <QUrl>
#include <QFileDialog>
#include <QImageReader>

#include <klocalizedstring.h>
#include <kio/Job>

#include <KoIcon.h>
#include <KoCanvasBase.h>
#include <KoImageCollection.h>
#include <KoImageData.h>
#include <KoSelection.h>
#include <KoShapeManager.h>
#include <KoShapeController.h>
#include <KoDocumentResourceManager.h>
#include <KoPointerEvent.h>
#include <KoFilterEffect.h>
#include <KoFilterEffectRegistry.h>
#include <KoFilterEffectConfigWidgetBase.h>
#include <KoFilterEffectStack.h>

//add
#define HANDLE_DISTANCE 10


#include "ui_wdgPictureTool.h"

struct PictureToolUI: public QWidget, public Ui::PictureTool
{
    PictureToolUI()
    {
        setupUi(this);
    }

    void blockAllSignals(bool block)
    {
        leftDoubleSpinBox->blockSignals(block);
        rightDoubleSpinBox->blockSignals(block);
        topDoubleSpinBox->blockSignals(block);
        bottomDoubleSpinBox->blockSignals(block);
        cropWidget->blockSignals(block);
        cbAspect->blockSignals(block);
        cmbColorMode->blockSignals(block);
    }
};

// ---------------------------------------------------- //


PictureTool::PictureTool(KoCanvasBase* canvas)
    : /*KoToolBase(canvas)*/ KoInteractionTool(canvas),
      m_pictureshape(0),
      m_pictureToolUI(0),
      m_lastHandle(KoFlake::NoHandle),
      m_hotPosition(KoFlake::TopLeftCorner),
      m_mouseWasInsideHandles(false)

{
}

void PictureTool::activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes)
{
    Q_UNUSED(toolActivation);

    foreach (KoShape *shape, shapes)
    {
        if ((m_pictureshape = dynamic_cast<PictureShape*>(shape)))
        {
            break;
        }
    }

    if (!m_pictureshape)
    {
        emit done();
        return;
    }

    if (m_pictureToolUI)
    {
        m_pictureToolUI->cropWidget->setPictureShape(m_pictureshape);
        updateControlElements();
    }

    useCursor(Qt::ArrowCursor);
}

void PictureTool::deactivate()
{
    m_pictureshape = 0;
}

QWidget *PictureTool::createOptionWidget()
{
    m_pictureToolUI = new PictureToolUI();
    m_pictureToolUI->cmbColorMode->addItem(i18n("Standard"), PictureShape::Standard);
    m_pictureToolUI->cmbColorMode->addItem(i18n("Greyscale"), PictureShape::Greyscale);
    m_pictureToolUI->cmbColorMode->addItem(i18n("Monochrome"), PictureShape::Mono);
    m_pictureToolUI->cmbColorMode->addItem(i18n("Watermark"), PictureShape::Watermark);
    m_pictureToolUI->bnImageFile->setIcon(koIcon("document-open"));

    updateControlElements();

    connect(m_pictureToolUI->bnImageFile, &QAbstractButton::clicked, this, &PictureTool::changeUrlPressed);
    connect(m_pictureToolUI->cmbColorMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PictureTool::colorModeChanged);
    connect(m_pictureToolUI->leftDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PictureTool::cropEditFieldsChanged);
    connect(m_pictureToolUI->rightDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PictureTool::cropEditFieldsChanged);
    connect(m_pictureToolUI->topDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PictureTool::cropEditFieldsChanged);
    connect(m_pictureToolUI->bottomDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PictureTool::cropEditFieldsChanged);
    connect(m_pictureToolUI->cbAspect, &QAbstractButton::toggled, this, &PictureTool::aspectCheckBoxChanged);
    connect(m_pictureToolUI->bnFill, &QAbstractButton::pressed, this, &PictureTool::fillButtonPressed);
    connect(m_pictureToolUI->cbContour, &QAbstractButton::toggled, this, &PictureTool::contourCheckBoxChanged);
    connect(m_pictureToolUI->cropWidget, &CropWidget::sigCropRegionChanged, this, &PictureTool::cropRegionChanged);

    return m_pictureToolUI;
}

void PictureTool::updateControlElements()
{
    if (m_pictureshape)
    {
        QSizeF imageSize = m_pictureshape->imageData()->imageSize();
        PictureShape::ColorMode mode      = m_pictureshape->colorMode();
        ClippingRect clippingRect(m_pictureshape->cropRect());

        clippingRect.right = 1.0 - clippingRect.right;
        clippingRect.bottom = 1.0 - clippingRect.bottom;
        clippingRect.scale(imageSize);

        m_pictureToolUI->blockAllSignals(true);
        m_pictureToolUI->cropWidget->setPictureShape(m_pictureshape);
        m_pictureToolUI->cropWidget->setKeepPictureProportion(m_pictureshape->isPictureInProportion());
        m_pictureToolUI->cbAspect->setChecked(m_pictureshape->isPictureInProportion());
        m_pictureToolUI->cmbColorMode->setCurrentIndex(m_pictureToolUI->cmbColorMode->findData(mode));

        m_pictureToolUI->leftDoubleSpinBox->setRange(0.0, imageSize.width());
        m_pictureToolUI->rightDoubleSpinBox->setRange(0.0, imageSize.width());
        m_pictureToolUI->topDoubleSpinBox->setRange(0.0, imageSize.height());
        m_pictureToolUI->bottomDoubleSpinBox->setRange(0.0, imageSize.height());
        m_pictureToolUI->leftDoubleSpinBox->setValue(clippingRect.left);
        m_pictureToolUI->rightDoubleSpinBox->setValue(clippingRect.right);
        m_pictureToolUI->topDoubleSpinBox->setValue(clippingRect.top);
        m_pictureToolUI->bottomDoubleSpinBox->setValue(clippingRect.bottom);
        m_pictureToolUI->cbContour->setChecked(m_pictureshape->clipPath() != 0);
        m_pictureToolUI->blockAllSignals(false);
    }
}

void PictureTool::changeUrlPressed()
{
    if (m_pictureshape == 0)
    {
        return;
    }
    // TODO: think about using KoFileDialog everywhere, after extending it to support remote urls
    QFileDialog *dialog = new QFileDialog();
    QStringList imageMimeTypes;
    foreach(const QByteArray &mimeType, QImageReader::supportedMimeTypes())
    {
        imageMimeTypes << QLatin1String(mimeType);
    }
    dialog->setMimeTypeFilters(imageMimeTypes);
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->exec();
    QUrl url = dialog->selectedUrls().value(0);

    if (!url.isEmpty())
    {
        // TODO move this to an action in the libs, with a nice dialog or something.
        KIO::StoredTransferJob *job = KIO::storedGet(url, KIO::NoReload, {});
        connect(job, &KJob::result, this, &PictureTool::setImageData);
    }
}

void PictureTool::cropEditFieldsChanged()
{
    ClippingRect clippingRect;
    clippingRect.left = m_pictureToolUI->leftDoubleSpinBox->value();
    clippingRect.right = m_pictureToolUI->rightDoubleSpinBox->value();
    clippingRect.top = m_pictureToolUI->topDoubleSpinBox->value();
    clippingRect.bottom = m_pictureToolUI->bottomDoubleSpinBox->value();
    clippingRect.uniform = false;
    clippingRect.inverted = true;
    clippingRect.normalize(m_pictureshape->imageData()->imageSize());

    m_pictureToolUI->cropWidget->setCropRect(clippingRect.toRect());
}

void PictureTool::cropRegionChanged(const QRectF& rect, bool undoPrev)
{
    if (undoPrev)
    {
        canvas()->shapeController()->resourceManager()->undoStack()->undo();
    }

    ChangeImageCommand *cmd = new ChangeImageCommand(m_pictureshape, rect);
    // connect before adding the command, so that "updateControlElements()" is executed
    // when the command is added to the undo stack.
    connect(cmd, &ChangeImageCommand::sigExecuted, this, &PictureTool::updateControlElements);
    canvas()->addCommand(cmd);
}

void PictureTool::colorModeChanged(int cmbIndex)
{
    PictureShape::ColorMode mode = (PictureShape::ColorMode)m_pictureToolUI->cmbColorMode->itemData(cmbIndex).toInt();
    ChangeImageCommand     *cmd  = new ChangeImageCommand(m_pictureshape, mode);
    canvas()->addCommand(cmd);
    // connect after adding the command to the undo stack to prevent a
    // call to "updateControlElements()" at this point
    connect(cmd, &ChangeImageCommand::sigExecuted, this, &PictureTool::updateControlElements);
}

void PictureTool::aspectCheckBoxChanged(bool checked)
{
    m_pictureToolUI->cropWidget->setKeepPictureProportion(checked);
}

void PictureTool::contourCheckBoxChanged(bool checked)
{
    canvas()->addCommand(new ClipCommand(m_pictureshape, checked));
}

void PictureTool::fillButtonPressed()
{
    m_pictureToolUI->cropWidget->maximizeCroppedArea();
}

void PictureTool::setImageData(KJob *job)
{
    if (m_pictureshape == 0)
    {
        return;    // ugh, the user deselected the image in between. We should move this code to main anyway redesign it
    }

    KIO::StoredTransferJob *transferJob = qobject_cast<KIO::StoredTransferJob*>(job);
    Q_ASSERT(transferJob);
    if (m_pictureshape->imageCollection())
    {
        KoImageData        *data = m_pictureshape->imageCollection()->createImageData(transferJob->data());
        ChangeImageCommand *cmd  = new ChangeImageCommand(m_pictureshape, data);
        // connect before adding the command, so that "updateControlElements()" is executed
        // when the command is added to the undo stack.
        connect(cmd, &ChangeImageCommand::sigExecuted, this, &PictureTool::updateControlElements);
        canvas()->addCommand(cmd);
    }
}

void PictureTool::mousePressEvent(KoPointerEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        event->ignore();
    }
    ///---------------add 20220424
    KoInteractionTool::mousePressEvent(event);
    updateCursor();
}

void PictureTool::mouseDoubleClickEvent(KoPointerEvent *event)
{
    if (canvas()->shapeManager()->shapeAt(event->point) != m_pictureshape)
    {
        event->ignore(); // allow the event to be used by another
        return;
    }

    changeUrlPressed();
}

 ///---------------add 20220424
KoInteractionStrategy *PictureTool::createStrategy(KoPointerEvent *event)
{
    Q_UNUSED(event);
    return 0;
}

KoSelection *PictureTool::koSelection()
{
    Q_ASSERT(canvas());
    Q_ASSERT(canvas()->shapeManager());
    return canvas()->shapeManager()->selection();
}

void PictureTool::paint(QPainter &painter, const KoViewConverter &converter)
{
    KoInteractionTool::paint(painter, converter);
    if (currentStrategy() == 0 && koSelection()->count() > 0)
    {
        SelectionPicture decorator(m_mouseWasInsideHandles ? m_lastHandle : KoFlake::NoHandle, true, true);
        decorator.setSelection(koSelection());
        decorator.setHandleRadius(handleRadius());
        decorator.setHotPosition(m_hotPosition);
        decorator.paint(painter, converter);
    }
}

void PictureTool::mouseReleaseEvent(KoPointerEvent *event)
{
    KoInteractionTool::mouseReleaseEvent(event);
    updateCursor();
}

void PictureTool::mouseMoveEvent(KoPointerEvent *event)
{
    KoInteractionTool::mouseMoveEvent(event);
    updateCursor();
}


void PictureTool::updateCursor()
{
    repaintDecorations();
    useCursor(Qt::ArrowCursor);
}

void PictureTool::repaintDecorations()
{
    Q_ASSERT(koSelection());
    if (koSelection()->count() > 0)
    {
        canvas()->updateCanvas(handlesSize());
    }
}


QRectF PictureTool::handlesSize()
{
    QRectF bound = koSelection()->boundingRect();
    // expansion Border
    if (!canvas() || !canvas()->viewConverter())
    {
        return bound;
    }

    QPointF border = canvas()->viewConverter()->viewToDocument(QPointF(HANDLE_DISTANCE, HANDLE_DISTANCE));
    bound.adjust(-border.x(), -border.y(), border.x(), border.y());
    return bound;
}

///------------------------------
///-----------------------------------------SelectionPicture copy [class SelectionDecorator]-----
#define HANDLE_DISTANCE 10

KoFlake::Position SelectionPicture::m_hotPosition = KoFlake::TopLeftCorner;

SelectionPicture::SelectionPicture(KoFlake::SelectionHandle arrows,  bool rotationHandles, bool shearHandles)
    : m_rotationHandles(rotationHandles), m_shearHandles(shearHandles)
    , m_arrows(arrows), m_handleRadius( 3 ), m_lineWidth(1)
{

}

void SelectionPicture::setSelection(KoSelection *selection)
{
    m_selection = selection;
}

void SelectionPicture::setHandleRadius( int radius )
{
    m_handleRadius = radius;
    m_lineWidth = qMax(1, (int)(radius / 2));
}

void SelectionPicture::setHotPosition( KoFlake::Position hotPosition )
{
    m_hotPosition = hotPosition;
}

KoFlake::Position SelectionPicture::hotPosition()
{
    return m_hotPosition;
}

void SelectionPicture::paint(QPainter &painter, const KoViewConverter &converter)
{
    QRectF handleArea;
    painter.save();

    // save the original painter transformation
    QTransform painterMatrix = painter.worldTransform();

    QPen pen;
    //Use the #00adf5 color with 50% opacity
    pen.setColor(QColor(0, 173, 245, 127));
    pen.setWidth(m_lineWidth);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen( pen );
    //bool editable=false;
    KoShape::AllowedInteractions interactions;
    foreach (KoShape *shape, m_selection->selectedShapes(KoFlake::StrippedSelection))
    {
        // apply the shape transformation on top of the old painter transformation
        painter.setWorldTransform( shape->absoluteTransformation(&converter) * painterMatrix );
        // apply the zoom factor
        KoShape::applyConversion( painter, converter );
        // draw the shape bounding rect
        painter.drawRect( QRectF( QPointF(), shape->size() ) );

        interactions |= shape->allowedInteractions();
        shape->update();///20220426 temp add: why? DefaultTool is ok?????
    }

    if (m_selection->count() > 1)
    {
        // more than one shape selected, so we need to draw the selection bounding rect
        painter.setPen(QPen(Qt::blue, 0));
        // apply the selection transformation on top of the old painter transformation
        painter.setWorldTransform(m_selection->absoluteTransformation(&converter) * painterMatrix);
        // apply the zoom factor
        KoShape::applyConversion(painter, converter);
        // draw the selection bounding rect
        painter.drawRect(QRectF(QPointF(), m_selection->size()));
        // save the selection bounding rect for later drawing the selection handles
        handleArea = QRectF(QPointF(), m_selection->size());
    }
    else if (m_selection->firstSelectedShape())
    {
        // only one shape selected, so we compose the correct painter matrix
        painter.setWorldTransform(m_selection->firstSelectedShape()->absoluteTransformation(&converter) * painterMatrix);
        KoShape::applyConversion(painter, converter);
        // save the only selected shapes bounding rect for later drawing the handles
        handleArea = QRectF(QPointF(), m_selection->firstSelectedShape()->size());
    }

    painterMatrix = painter.worldTransform();
    painter.restore();
}
