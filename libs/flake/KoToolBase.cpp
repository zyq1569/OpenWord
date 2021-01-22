/* This file is part of the KDE project
 * Copyright (C) 2006, 2010 Thomas Zander <zander@kde.org>
 * Copyright (C) 2011 Jan Hambrecht <jaham@gmx.net>
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

#include "KoToolBase.h"
#include "KoToolBase_p.h"

#include "KoCanvasBase.h"
#include "KoPointerEvent.h"
#include "KoDocumentResourceManager.h"
#include "KoCanvasResourceManager.h"
#include "KoViewConverter.h"
#include "KoShapeController.h"
#include "KoShapeBasedDocumentBase.h"
#include "KoToolSelection.h"

#include <klocalizedstring.h>
#include <kactioncollection.h>

#include <QAction>
#include <QWidget>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>

KoToolBase::KoToolBase(KoCanvasBase *canvas)
    : d_ptr(new KoToolBasePrivate(this, canvas))
{
    Q_D(KoToolBase);
    d->connectSignals();
}

KoToolBase::KoToolBase(KoToolBasePrivate &dd)
    : d_ptr(&dd)
{
    Q_D(KoToolBase);
    d->connectSignals();
}

KoToolBase::~KoToolBase()
{

    //Q_D(const KoToolBase);

// Enable this to easily generate action files for tools
//    if (d->actionCollection.size() > 0) {

//        QDomDocument doc;
//        QDomElement e = doc.createElement("Actions");
//        e.setAttribute("name", toolId());
//        e.setAttribute("version", "1");
//        doc.appendChild(e);

//        foreach(QAction *ac, d->actionCollection.values()) {
//            QAction *action = qobject_cast<QAction*>(ac);
//            if (action) {
//                QDomElement a = doc.createElement("Action");
//                a.setAttribute("name", action->objectName());
//                a.setAttribute("icon", action->icon().name());
//                a.setAttribute("text" , action->text());
//                a.setAttribute("whatsThis" , action->whatsThis());
//                a.setAttribute("toolTip" , action->toolTip());
//                a.setAttribute("iconText" , action->iconText());
//                a.setAttribute("shortcut" , action->shortcut(QAction::ActiveShortcut).toString());
//                a.setAttribute("defaultShortcut" , action->shortcut(QAction::DefaultShortcut).toString());
//                a.setAttribute("isCheckable" , QString((action->isChecked() ? "true" : "false")));
//                a.setAttribute("statusTip", action->statusTip());
//                e.appendChild(a);
//            }
//            else {
//                qDebug() << "Got a QAction:" << ac->objectName();
//            }

//        }
//        QFile f(toolId() + ".action");
//        f.open(QFile::WriteOnly);
//        f.write(doc.toString().toUtf8());
//        f.close();

//    }
//    else {
//        qDebug() << "Tool" << toolId() << "has no actions";
//    }
    qDeleteAll(d_ptr->optionWidgets);
    delete d_ptr;
}

/// Ultimately only called from Calligra Sheets
void KoToolBase::updateShapeController(KoShapeBasedDocumentBase *shapeController)
{
    if (shapeController) {
        KoDocumentResourceManager *scrm = shapeController->resourceManager();
        if (scrm) {
            connect(scrm, SIGNAL(resourceChanged(int,QVariant)),
                    this, SLOT(documentResourceChanged(int,QVariant)));
        }
    }
}

void KoToolBase::deactivate()
{
}

void KoToolBase::canvasResourceChanged(int key, const QVariant & res)
{
    Q_UNUSED(key);
    Q_UNUSED(res);
}

void KoToolBase::documentResourceChanged(int key, const QVariant &res)
{
    Q_UNUSED(key);
    Q_UNUSED(res);
}

bool KoToolBase::wantsAutoScroll() const
{
    return true;
}

void KoToolBase::mouseDoubleClickEvent(KoPointerEvent *event)
{
    event->ignore();
}

void KoToolBase::mouseTripleClickEvent(KoPointerEvent *event)
{
    event->ignore();
}

void KoToolBase::shortcutOverrideEvent(QKeyEvent *e)
{
    e->ignore();
}

void KoToolBase::keyPressEvent(QKeyEvent *e)
{
    e->ignore();
}

void KoToolBase::keyReleaseEvent(QKeyEvent *e)
{
    e->ignore();
}

void KoToolBase::wheelEvent(KoPointerEvent * e)
{
    e->ignore();
}

void KoToolBase::touchEvent(QTouchEvent *event)
{
    event->ignore();
}

QVariant KoToolBase::inputMethodQuery(Qt::InputMethodQuery query, const KoViewConverter &) const
{
    Q_D(const KoToolBase);
    if (d->canvas->canvasWidget() == 0)
        return QVariant();

    switch (query) {
    case Qt::ImMicroFocus:
        return QRect(d->canvas->canvasWidget()->width() / 2, 0, 1, d->canvas->canvasWidget()->height());
    case Qt::ImFont:
        return d->canvas->canvasWidget()->font();
    default:
        return QVariant();
    }
}

void KoToolBase::inputMethodEvent(QInputMethodEvent * event)
{
    if (! event->commitString().isEmpty()) {
        QKeyEvent ke(QEvent::KeyPress, -1, 0, event->commitString());
        keyPressEvent(&ke);
    }
    event->accept();
}

void KoToolBase::customPressEvent(KoPointerEvent * event)
{
    event->ignore();
}

void KoToolBase::customReleaseEvent(KoPointerEvent * event)
{
    event->ignore();
}

void KoToolBase::customMoveEvent(KoPointerEvent * event)
{
    event->ignore();
}

bool KoToolBase::wantsTouch() const
{
    return false;
}

void KoToolBase::useCursor(const QCursor &cursor)
{
    Q_D(KoToolBase);
    d->currentCursor = cursor;
    emit cursorChanged(d->currentCursor);
}

QList<QPointer<QWidget> > KoToolBase::optionWidgets()
{
    Q_D(KoToolBase);
    if (d->optionWidgets.empty()) {
        d->optionWidgets = createOptionWidgets();
    }
    return d->optionWidgets;
}

void KoToolBase::addAction(const QString &name, QAction *action)
{
    Q_D(KoToolBase);
    if (action->objectName().isEmpty()) {
        action->setObjectName(name);
    }
    d->actionCollection.insert(name, action);
}

QHash<QString, QAction *> KoToolBase::actions() const
{
    Q_D(const KoToolBase);
    return d->actionCollection;
}

QAction *KoToolBase::action(const QString &name) const
{
    Q_D(const KoToolBase);
    return d->actionCollection.value(name);
}

QWidget * KoToolBase::createOptionWidget()
{
    return 0;
}

QList<QPointer<QWidget> >  KoToolBase::createOptionWidgets()
{
    QList<QPointer<QWidget> > ow;
    if (QWidget *widget = createOptionWidget()) {
        if (widget->objectName().isEmpty()) {
            widget->setObjectName(toolId());
        }
        ow.append(widget);
    }
    return ow;
}

void KoToolBase::setToolId(const QString &id)
{
    Q_D(KoToolBase);
    d->toolId = id;
}

QString KoToolBase::toolId() const
{
    Q_D(const KoToolBase);
    return d->toolId;
}

QCursor KoToolBase::cursor() const
{
    Q_D(const KoToolBase);
    return d->currentCursor;
}

void KoToolBase::deleteSelection()
{
}

void KoToolBase::cut()
{
    copy();
    deleteSelection();
}

QList<QAction*> KoToolBase::popupActionList() const
{
    Q_D(const KoToolBase);
    return d->popupActionList;
}

void KoToolBase::setPopupActionList(const QList<QAction*> &list)
{
    Q_D(KoToolBase);
    d->popupActionList = list;
}

KoCanvasBase * KoToolBase::canvas() const
{
    Q_D(const KoToolBase);
    return d->canvas;
}

void KoToolBase::setStatusText(const QString &statusText)
{
    emit statusTextChanged(statusText);
}

uint KoToolBase::handleRadius() const
{
    Q_D(const KoToolBase);
    if(d->canvas->shapeController()->resourceManager())
    {
        return d->canvas->shapeController()->resourceManager()->handleRadius();
    } else {
        return 3;
    }
}

uint KoToolBase::grabSensitivity() const
{
    Q_D(const KoToolBase);
    if(d->canvas->shapeController()->resourceManager())
    {
        return d->canvas->shapeController()->resourceManager()->grabSensitivity();
    } else {
        return 3;
    }
}

QRectF KoToolBase::handleGrabRect(const QPointF &position) const
{
    Q_D(const KoToolBase);
    const KoViewConverter * converter = d->canvas->viewConverter();
    uint handleSize = 2*grabSensitivity();
    QRectF r = converter->viewToDocument(QRectF(0, 0, handleSize, handleSize));
    r.moveCenter(position);
    return r;
}

QRectF KoToolBase::handlePaintRect(const QPointF &position) const
{
    Q_D(const KoToolBase);
    const KoViewConverter * converter = d->canvas->viewConverter();
    uint handleSize = 2*handleRadius();
    QRectF r = converter->viewToDocument(QRectF(0, 0, handleSize, handleSize));
    r.moveCenter(position);
    return r;
}

void KoToolBase::setTextMode(bool value)
{
    Q_D(KoToolBase);
    d->isInTextMode=value;
}

QStringList KoToolBase::supportedPasteMimeTypes() const
{
    return QStringList();
}

bool KoToolBase::paste()
{
    return false;
}

void KoToolBase::copy() const
{
}

void KoToolBase::dragMoveEvent(QDragMoveEvent *event, const QPointF &point)
{
    Q_UNUSED(event);
    Q_UNUSED(point);
}

void KoToolBase::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
}

void KoToolBase::dropEvent(QDropEvent *event, const QPointF &point)
{
    Q_UNUSED(event);
    Q_UNUSED(point);
}

bool KoToolBase::hasSelection()
{
    KoToolSelection *sel = selection();
    return (sel && sel->hasSelection());
}

KoToolSelection *KoToolBase::selection()
{
    return 0;
}

void KoToolBase::repaintDecorations()
{
}

bool KoToolBase::isInTextMode() const
{
    Q_D(const KoToolBase);
    return d->isInTextMode;
}
