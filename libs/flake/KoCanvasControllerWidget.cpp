/* This file is part of the KDE project
 *
 * Copyright (C) 2006, 2008-2009 Thomas Zander <zander@kde.org>
 * Copyright (C) 2006 Peter Simonsson <peter.simonsson@gmail.com>
 * Copyright (C) 2006, 2009 Thorsten Zachmann <zachmann@kde.org>
 * Copyright (C) 2007-2010 Boudewijn Rempt <boud@valdyas.org>
 * Copyright (C) 2007 C. Boemann <cbo@boemann.dk>
 * Copyright (C) 2006-2008 Jan Hambrecht <jaham@gmx.net>
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

#include "KoCanvasControllerWidget.h"
#include "KoCanvasControllerWidget_p.h"

#include "KoCanvasControllerWidgetViewport_p.h"
#include "KoShape.h"
#include "KoViewConverter.h"
#include "KoCanvasBase.h"
#include "KoCanvasObserverBase.h"
#include "KoCanvasSupervisor.h"
#include "KoToolManager_p.h"

#include <FlakeDebug.h>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QEvent>
#include <QDockWidget>
#include <QTimer>
#include <QPointer>

#include <KoConfig.h>

#include <math.h>

void KoCanvasControllerWidget::Private::setDocumentOffset()
{
    // The margins scroll the canvas widget inside the viewport, not
    // the document. The documentOffset is meant to be the value that
    // the canvas must add to the update rect in its paint event, to
    // compensate.

    QPoint pt(q->horizontalScrollBar()->value(), q->verticalScrollBar()->value());
    q->proxyObject->emitMoveDocumentOffset(pt);

    QWidget *canvasWidget = canvas->canvasWidget();

    if (canvasWidget) {
        QWidget *canvasWidget = canvas->canvasWidget();
        QPoint diff = q->documentOffset() - pt;
        if (q->canvasMode() == Spreadsheet && canvasWidget->layoutDirection() == Qt::RightToLeft) {
            canvasWidget->scroll(-diff.x(), diff.y());
        } else {
            canvasWidget->scroll(diff.x(), diff.y());
        }
    }

    q->setDocumentOffset(pt);
}

void KoCanvasControllerWidget::Private::resetScrollBars()
{
    // The scrollbar value always points at the top-left corner of the
    // bit of image we paint.

    int docH = q->documentSize().height() + q->margin();
    int docW = q->documentSize().width() + q->margin();
    int drawH = viewportWidget->height();
    int drawW = viewportWidget->width();

    QScrollBar *hScroll = q->horizontalScrollBar();
    QScrollBar *vScroll = q->verticalScrollBar();

    int horizontalReserve = vastScrollingFactor * drawW;
    int verticalReserve = vastScrollingFactor * drawH;

    int xMin = -horizontalReserve;
    int yMin = -verticalReserve;

    int xMax = docW - drawW + horizontalReserve;
    int yMax = docH - drawH + verticalReserve;

    hScroll->setRange(xMin, xMax);
    vScroll->setRange(yMin, yMax);

    int fontheight = QFontMetrics(q->font()).height();

    vScroll->setPageStep(drawH);
    vScroll->setSingleStep(fontheight);
    hScroll->setPageStep(drawW);
    hScroll->setSingleStep(fontheight);

}

void KoCanvasControllerWidget::Private::emitPointerPositionChangedSignals(QEvent *event)
{
    if (!canvas) return;
    if (!canvas->viewConverter()) return;

    QPoint pointerPos;
    QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
    if (mouseEvent) {
        pointerPos = mouseEvent->pos();
    } else {
        QTabletEvent *tabletEvent = dynamic_cast<QTabletEvent*>(event);
        if (tabletEvent) {
            pointerPos = tabletEvent->pos();
        }
    }

    QPoint pixelPos = (pointerPos - canvas->documentOrigin()) + q->documentOffset();
    QPointF documentPos = canvas->viewConverter()->viewToDocument(pixelPos);

    q->proxyObject->emitDocumentMousePositionChanged(documentPos);
    q->proxyObject->emitCanvasMousePositionChanged(pointerPos);
}


#include <QTime>

void KoCanvasControllerWidget::Private::activate()
{
    QWidget *parent = q;
    while (parent->parentWidget()) {
        parent = parent->parentWidget();
    }
    KoCanvasSupervisor *observerProvider = dynamic_cast<KoCanvasSupervisor*>(parent);
    if (!observerProvider) {
        return;
    }
    foreach(KoCanvasObserverBase *docker, observerProvider->canvasObservers()) {
        KoCanvasObserverBase *observer = dynamic_cast<KoCanvasObserverBase*>(docker);
        if (observer) {
            observer->setObservedCanvas(q->canvas());
        }
    }

}

void KoCanvasControllerWidget::Private::unsetCanvas()
{
    QWidget *parent = q;
    while (parent->parentWidget()) {
        parent = parent->parentWidget();
    }
    KoCanvasSupervisor *observerProvider = dynamic_cast<KoCanvasSupervisor*>(parent);
    if (!observerProvider) {
        return;
    }
    foreach(KoCanvasObserverBase *docker, observerProvider->canvasObservers()) {
        KoCanvasObserverBase *observer = dynamic_cast<KoCanvasObserverBase*>(docker);
        if (observer && observer->observedCanvas() == q->canvas()) {
            observer->unsetObservedCanvas();
        }
    }
}

////////////
KoCanvasControllerWidget::KoCanvasControllerWidget(KActionCollection * actionCollection, QWidget *parent)
    : QAbstractScrollArea(parent)
    , KoCanvasController(actionCollection)
    , d(new Private(this))
{
    // We need to set this as QDeclarativeView sets them a bit different from QAbstractScrollArea
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // And then our own Viewport
    d->viewportWidget = new Viewport(this);
    setViewport(d->viewportWidget);
    d->viewportWidget->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(0);

    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setAutoFillBackground(false);
    /*
      Fixes:   apps starting at zero zoom.
      Details: Since the document is set on the mainwindow before loading commences the initial show/layout can choose
          to set the document to be very small, even to be zero pixels tall.  Setting a sane minimum size on the
          widget means we no longer get rounding errors in zooming and we no longer end up with zero-zoom.
      Note: KoPage apps should probably startup with a sane document size; for Krita that's impossible
     */
    setMinimumSize(QSize(50, 50));
    setMouseTracking(true);

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateCanvasOffsetX()));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateCanvasOffsetY()));
    connect(d->viewportWidget, SIGNAL(sizeChanged()), this, SLOT(updateCanvasOffsetX()));
    connect(proxyObject, SIGNAL(moveDocumentOffset(QPoint)), d->viewportWidget, SLOT(documentOffsetMoved(QPoint)));
}

KoCanvasControllerWidget::~KoCanvasControllerWidget()
{
    d->viewportWidget->canvas()->removeEventFilter(this);
    d->unsetCanvas();
    delete d;
}

void KoCanvasControllerWidget::activate()
{
    d->activate();
}

void KoCanvasControllerWidget::scrollContentsBy(int dx, int dy)
{
    Q_UNUSED(dx);
    Q_UNUSED(dy);
    d->setDocumentOffset();
}

QSize KoCanvasControllerWidget::viewportSize() const
{
    return viewport()->size();
}

void KoCanvasControllerWidget::setDrawShadow(bool drawShadow)
{
    d->viewportWidget->setDrawShadow(drawShadow);
}

void KoCanvasControllerWidget::resizeEvent(QResizeEvent *resizeEvent)
{
    proxyObject->emitSizeChanged(resizeEvent->size());

    // XXX: When resizing, keep the area we're looking at now in the
    // center of the resized view.
    d->resetScrollBars();
    d->setDocumentOffset();
}

void KoCanvasControllerWidget::setCanvas(KoCanvasBase *canvas)
{
    Q_ASSERT(canvas); // param is not null
    if (d->canvas) {
        d->unsetCanvas();
        proxyObject->emitCanvasRemoved(this);
        canvas->setCanvasController(0);
        d->canvas->canvasWidget()->removeEventFilter(this);
    }
    canvas->setCanvasController(this);
    d->canvas = canvas;

    changeCanvasWidget(canvas->canvasWidget());

    proxyObject->emitCanvasSet(this);
    QTimer::singleShot(0, this, SLOT(activate()));

    setPreferredCenterFractionX(0);
    setPreferredCenterFractionY(0);
}

KoCanvasBase* KoCanvasControllerWidget::canvas() const
{
    return d->canvas;
}

void KoCanvasControllerWidget::changeCanvasWidget(QWidget *widget)
{
    if (d->viewportWidget->canvas()) {
        widget->setCursor(d->viewportWidget->canvas()->cursor());
        d->viewportWidget->canvas()->removeEventFilter(this);
    }

    d->viewportWidget->setCanvas(widget);
    setFocusProxy(d->canvas->canvasWidget());

    widget->installEventFilter(this);
    widget->setMouseTracking(true);
}

int KoCanvasControllerWidget::visibleHeight() const
{
    if (d->canvas == 0)
        return 0;
    QWidget *canvasWidget = canvas()->canvasWidget();

    int height1;
    if (canvasWidget == 0)
        height1 = viewport()->height();
    else
        height1 = qMin(viewport()->height(), canvasWidget->height());
    int height2 = height();
    return qMin(height1, height2);
}

int KoCanvasControllerWidget::visibleWidth() const
{
    if (d->canvas == 0)
        return 0;
    QWidget *canvasWidget = canvas()->canvasWidget();

    int width1;
    if (canvasWidget == 0)
        width1 = viewport()->width();
    else
        width1 = qMin(viewport()->width(), canvasWidget->width());
    int width2 = width();
    return qMin(width1, width2);
}

int KoCanvasControllerWidget::canvasOffsetX() const
{
    int offset = -horizontalScrollBar()->value();

    if (d->canvas) {
        offset += d->canvas->canvasWidget()->x() + frameWidth();
    }

    return offset;
}

int KoCanvasControllerWidget::canvasOffsetY() const
{
    int offset = -verticalScrollBar()->value();

    if (d->canvas) {
        offset += d->canvas->canvasWidget()->y() + frameWidth();
    }

    return offset;
}

void KoCanvasControllerWidget::updateCanvasOffsetX()
{
    proxyObject->emitCanvasOffsetXChanged(canvasOffsetX());
    if (d->ignoreScrollSignals)
        return;

    setPreferredCenterFractionX((horizontalScrollBar()->value()
                                 + viewport()->width() / 2.0) / documentSize().width());
}

void KoCanvasControllerWidget::updateCanvasOffsetY()
{
    proxyObject->emitCanvasOffsetYChanged(canvasOffsetY());
    if (d->ignoreScrollSignals)
        return;

    setPreferredCenterFractionY((verticalScrollBar()->value()
                                 + verticalScrollBar()->pageStep() / 2.0) / documentSize().height());
}

bool KoCanvasControllerWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (d->canvas && d->canvas->canvasWidget() && (watched == d->canvas->canvasWidget())) {
         if (event->type() == QEvent::MouseMove || event->type() == QEvent::TabletMove) {
            d->emitPointerPositionChangedSignals(event);
        }
    }
    return false;
}

void KoCanvasControllerWidget::ensureVisible(KoShape *shape)
{
    Q_ASSERT(shape);
    ensureVisible(d->canvas->viewConverter()->documentToView(shape->boundingRect()));
}

void KoCanvasControllerWidget::ensureVisible(const QRectF &rect, bool smooth)
{
    QRect currentVisible(-canvasOffsetX(), -canvasOffsetY(), visibleWidth(), visibleHeight());

    QRect viewRect = rect.toRect();
    viewRect.translate(d->canvas->documentOrigin());
    if (!viewRect.isValid() || currentVisible.contains(viewRect))
        return; // its visible. Nothing to do.

    // if we move, we move a little more so the amount of times we have to move is less.
    int jumpWidth = smooth ? 0 : currentVisible.width() / 5;
    int jumpHeight = smooth ? 0 : currentVisible.height() / 5;
    if (!smooth && viewRect.width() + jumpWidth > currentVisible.width())
        jumpWidth = 0;
    if (!smooth && viewRect.height() + jumpHeight > currentVisible.height())
        jumpHeight = 0;

    int horizontalMove = 0;
    if (currentVisible.width() <= viewRect.width())      // center view
        horizontalMove = viewRect.center().x() - currentVisible.center().x();
    else if (currentVisible.x() > viewRect.x())          // move left
        horizontalMove = viewRect.x() - currentVisible.x() - jumpWidth;
    else if (currentVisible.right() < viewRect.right())  // move right
        horizontalMove = viewRect.right() - qMax(0, currentVisible.right() - jumpWidth);

    int verticalMove = 0;
    if (currentVisible.height() <= viewRect.height())       // center view
        verticalMove = viewRect.center().y() - currentVisible.center().y();
    if (currentVisible.y() > viewRect.y())               // move up
        verticalMove = viewRect.y() - currentVisible.y() - jumpHeight;
    else if (currentVisible.bottom() < viewRect.bottom()) // move down
        verticalMove = viewRect.bottom() - qMax(0, currentVisible.bottom() - jumpHeight);

    pan(QPoint(horizontalMove, verticalMove));
}

void KoCanvasControllerWidget::recenterPreferred()
{
    const bool oldIgnoreScrollSignals = d->ignoreScrollSignals;
    d->ignoreScrollSignals = true;

    QPointF center = preferredCenter();

    // convert into a viewport based point
    center.rx() += d->canvas->canvasWidget()->x() + frameWidth();
    center.ry() += d->canvas->canvasWidget()->y() + frameWidth();

    // scroll to a new center point
    QPointF topLeft = center - 0.5 * QPointF(viewport()->width(), viewport()->height());
    setScrollBarValue(topLeft.toPoint());

    d->ignoreScrollSignals = oldIgnoreScrollSignals;
}

void KoCanvasControllerWidget::zoomIn(const QPoint &center)
{
    zoomBy(center, sqrt(2.0));
}

void KoCanvasControllerWidget::zoomOut(const QPoint &center)
{
    zoomBy(center, sqrt(0.5));
}

void KoCanvasControllerWidget::zoomBy(const QPoint &center, qreal zoom)
{
    setPreferredCenterFractionX(1.0 * center.x() / documentSize().width());
    setPreferredCenterFractionY(1.0 * center.y() / documentSize().height());

    const bool oldIgnoreScrollSignals = d->ignoreScrollSignals;
    d->ignoreScrollSignals = true;
    proxyObject->emitZoomRelative(zoom, preferredCenter());
    d->ignoreScrollSignals = oldIgnoreScrollSignals;
}

void KoCanvasControllerWidget::zoomTo(const QRect &viewRect)
{
    qreal scale;

    if (1.0 * viewport()->width() / viewRect.width() > 1.0 * viewport()->height() / viewRect.height())
        scale = 1.0 * viewport()->height() / viewRect.height();
    else
        scale = 1.0 * viewport()->width() / viewRect.width();

    zoomBy(viewRect.center(), scale);
}

void KoCanvasControllerWidget::setToolOptionWidgets(const QList<QPointer<QWidget> >&widgetMap)
{
    emit toolOptionWidgetsChanged(widgetMap);
}

void KoCanvasControllerWidget::updateDocumentSize(const QSize &sz, bool recalculateCenter)
{
    // Don't update if the document-size didn't changed to prevent infinite loops and unneeded updates.
    if (KoCanvasController::documentSize() == sz)
        return;

    if (!recalculateCenter) {
        // assume the distance from the top stays equal and recalculate the center.
        setPreferredCenterFractionX(documentSize().width() * preferredCenterFractionX() / sz.width());
        setPreferredCenterFractionY(documentSize().height() * preferredCenterFractionY() / sz.height());
    }

    const bool oldIgnoreScrollSignals = d->ignoreScrollSignals;
    d->ignoreScrollSignals = true;
    KoCanvasController::setDocumentSize(sz);
    d->viewportWidget->setDocumentSize(sz);
    d->resetScrollBars();

    // Always emit the new offset.
    updateCanvasOffsetX();
    updateCanvasOffsetY();

    d->ignoreScrollSignals = oldIgnoreScrollSignals;
}

void KoCanvasControllerWidget::setZoomWithWheel(bool zoom)
{
    d->zoomWithWheel = zoom;
}

void KoCanvasControllerWidget::setVastScrolling(qreal factor)
{
    d->vastScrollingFactor = factor;
}

void KoCanvasControllerWidget::pan(const QPoint &distance)
{
    QPoint sourcePoint = scrollBarValue();
    setScrollBarValue(sourcePoint + distance);
}

void KoCanvasControllerWidget::setPreferredCenter(const QPointF &viewPoint)
{
    setPreferredCenterFractionX(viewPoint.x() / documentSize().width());
    setPreferredCenterFractionY(viewPoint.y() / documentSize().height());
    recenterPreferred();
}

QPointF KoCanvasControllerWidget::preferredCenter() const
{
    QPointF center;
    center.setX(preferredCenterFractionX() * documentSize().width());
    center.setY(preferredCenterFractionY() * documentSize().height());
    return center;
}

void KoCanvasControllerWidget::paintEvent(QPaintEvent *event)
{
    QPainter gc(viewport());
    d->viewportWidget->handlePaintEvent(gc, event);
}

void KoCanvasControllerWidget::dragEnterEvent(QDragEnterEvent *event)
{
    d->viewportWidget->handleDragEnterEvent(event);
}

void KoCanvasControllerWidget::dropEvent(QDropEvent *event)
{
    d->viewportWidget->handleDropEvent(event);
}

void KoCanvasControllerWidget::dragMoveEvent(QDragMoveEvent *event)
{
    d->viewportWidget->handleDragMoveEvent(event);
}

void KoCanvasControllerWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    d->viewportWidget->handleDragLeaveEvent(event);
}

void KoCanvasControllerWidget::keyPressEvent(QKeyEvent *event)
{
    KoToolManager::instance()->priv()->switchToolByShortcut(event);
}

void KoCanvasControllerWidget::wheelEvent(QWheelEvent *event)
{
    if (d->zoomWithWheel != ((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier)) {
        const qreal zoomCoeff = event->delta() > 0 ? sqrt(2.0) : sqrt(0.5);
        zoomRelativeToPoint(event->pos(), zoomCoeff);

        event->accept();
    } else
        QAbstractScrollArea::wheelEvent(event);
}

void KoCanvasControllerWidget::zoomRelativeToPoint(const QPoint &widgetPoint, qreal zoomCoeff)
{
    const QPoint offset = scrollBarValue();
    const QPoint mousePos(widgetPoint + offset);

    const bool oldIgnoreScrollSignals = d->ignoreScrollSignals;
    d->ignoreScrollSignals = true;
    proxyObject->emitZoomRelative(zoomCoeff, mousePos);
    d->ignoreScrollSignals = oldIgnoreScrollSignals;
}

bool KoCanvasControllerWidget::focusNextPrevChild(bool)
{
    // we always return false meaning the canvas takes keyboard focus, but never gives it away.
    return false;
}

void KoCanvasControllerWidget::setMargin(int margin)
{
    KoCanvasController::setMargin(margin);
    Q_ASSERT(d->viewportWidget);
    d->viewportWidget->setMargin(margin);
}

QPoint KoCanvasControllerWidget::scrollBarValue() const
{
    QScrollBar * hBar = horizontalScrollBar();
    QScrollBar * vBar = verticalScrollBar();

    return QPoint(hBar->value(), vBar->value());
}

void KoCanvasControllerWidget::setScrollBarValue(const QPoint &value)
{
    QScrollBar * hBar = horizontalScrollBar();
    QScrollBar * vBar = verticalScrollBar();

    hBar->setValue(value.x());
    vBar->setValue(value.y());
}

KoCanvasControllerWidget::Private *KoCanvasControllerWidget::priv()
{
    return d;
}

//have to include this because of Q_PRIVATE_SLOT
//#include "moc_KoCanvasControllerWidget.cpp"
