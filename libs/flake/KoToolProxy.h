/* This file is part of the KDE project
 *
 * Copyright (c) 2006, 2010 Boudewijn Rempt <boud@valdyas.org>
 * Copyright (C) 2006-2010 Thomas Zander <zander@kde.org>
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
#ifndef _KO_TOOL_PROXY_H_
#define _KO_TOOL_PROXY_H_

#include "flake_export.h"

#include <QObject>
#include <QHash>

#include <QTimer>
#include <QTime>
#include <QPoint>
class KoPointerEvent;
class KoToolBase;
class KoCanvasController;
class KoToolProxy;

class QAction;
class QAction;
class QMouseEvent;
class QKeyEvent;
class QWheelEvent;
class QTabletEvent;
class KoCanvasBase;
class KoViewConverter;
class KoToolBase;
class KoToolProxyPrivate;
class QInputMethodEvent;
class KoPointerEvent;
class QDragMoveEvent;
class QDragLeaveEvent;
class QDropEvent;
class QTouchEvent;
class QPainter;
//class QPointF;

/**
 * Tool proxy object which allows an application to address the current tool.
 *
 * Applications typically have a canvas and a canvas requires a tool for
 * the user to do anything.  Since the flake system is responsible for handling
 * tools and also to change the active tool when needed we provide one class
 * that can be used by an application canvas to route all the native events too
 * which will transparently be routed to the active tool.  Without the application
 * having to bother about which tool is active.
 */
class FLAKE_EXPORT KoToolProxy : public QObject
{
    Q_OBJECT
public:
    /**
     * Constructor
     * @param canvas Each canvas has 1 toolProxy. Pass the parent here.
     * @param parent a parent QObject for memory management purposes.
     */
    explicit KoToolProxy(KoCanvasBase *canvas, QObject *parent = 0);
    ~KoToolProxy() override;

    /// Forwarded to the current KoToolBase
    void paint(QPainter &painter, const KoViewConverter &converter);

    /// Forwarded to the current KoToolBase
    void repaintDecorations();

    /**
     * Forward the given touch event to the current KoToolBase.
     * The viewconverter and document offset are necessary to convert all
     * the QTouchPoints to KoTouchPoints that work in document coordinates.
     */
    void touchEvent(QTouchEvent *event);

    /// Forwarded to the current KoToolBase
    void tabletEvent(QTabletEvent *event, const QPointF &point);

    /// Forwarded to the current KoToolBase
    void mousePressEvent(QMouseEvent *event, const QPointF &point);
    void mousePressEvent(KoPointerEvent *event);

    /// Forwarded to the current KoToolBase
    void mouseDoubleClickEvent(QMouseEvent *event, const QPointF &point);
    void mouseDoubleClickEvent(KoPointerEvent *event);

    /// Forwarded to the current KoToolBase
    void mouseMoveEvent(QMouseEvent *event, const QPointF &point);
    void mouseMoveEvent(KoPointerEvent *event);

    /// Forwarded to the current KoToolBase
    void mouseReleaseEvent(QMouseEvent *event, const QPointF &point);
    void mouseReleaseEvent(KoPointerEvent *event);

    /// Forwarded to the current KoToolBase
    void shortcutOverrideEvent(QKeyEvent *event);

    /// Forwarded to the current KoToolBase
    void keyPressEvent(QKeyEvent *event);

    /// Forwarded to the current KoToolBase
    void keyReleaseEvent(QKeyEvent *event);

    /// Forwarded to the current KoToolBase
    void wheelEvent(QWheelEvent * event, const QPointF &point);
    void wheelEvent(KoPointerEvent *event);

    /// Forwarded to the current KoToolBase
    QVariant inputMethodQuery(Qt::InputMethodQuery query, const KoViewConverter &converter) const;

    /// Forwarded to the current KoToolBase
    void inputMethodEvent(QInputMethodEvent *event);

    /// Forwarded to the current KoToolBase
    QList<QAction*> popupActionList() const;

    /// Forwarded to the current KoToolBase
    void deleteSelection();

    /// This method gives the proxy a chance to do things. for example it is need to have working singlekey
    /// shortcuts. call it from the canvas' event function and forward it to QWidget::event() later.
    void processEvent(QEvent *);

    /**
     * Retrieves the entire collection of actions for the active tool
     * or an empty hash if there is no active tool yet.
     */
    QHash<QString, QAction *> actions() const;

    /// returns true if the current tool holds a selection
    bool hasSelection() const;

    /// Forwarded to the current KoToolBase
    void cut();

    /// Forwarded to the current KoToolBase
    void copy() const;

    /// Forwarded to the current KoToolBase
    bool paste();

    /// Forwarded to the current KoToolBase
    QStringList supportedPasteMimeTypes() const;

    /// Forwarded to the current KoToolBase
    void dragMoveEvent(QDragMoveEvent *event, const QPointF &point);

    /// Forwarded to the current KoToolBase
    void dragLeaveEvent(QDragLeaveEvent *event);

    /// Forwarded to the current KoToolBase
    void dropEvent(QDropEvent *event, const QPointF &point);
 
    /// Set the new active tool.
    virtual void setActiveTool(KoToolBase *tool);

    /// \internal
    KoToolProxyPrivate *priv();

Q_SIGNALS:
    /**
     * A tool can have a selection that is copy-able, this signal is emitted when that status changes.
     * @param hasSelection is true when the tool holds selected data.
     */
    void selectionChanged(bool hasSelection);

    /**
     * Emitted every time a tool is changed.
     * @param toolId the id of the tool.
     * @see KoToolBase::toolId()
     */
    void toolChanged(const QString &toolId);

protected:
    virtual QPointF widgetToDocument(const QPointF &widgetPoint) const;
    KoCanvasBase* canvas() const;

private:
    Q_PRIVATE_SLOT(d, void timeout())
    Q_PRIVATE_SLOT(d, void selectionChanged(bool))

    friend class KoToolProxyPrivate;
    KoToolProxyPrivate * const d;
};


class KoToolProxyPrivate
{
public:
    explicit KoToolProxyPrivate(KoToolProxy *p);

    void timeout(); // Auto scroll the canvas

    void checkAutoScroll(const KoPointerEvent &event);

    void selectionChanged(bool newSelection);

    bool isActiveLayerEditable();

    /// the toolManager tells us which KoCanvasController this toolProxy is working for.
    void setCanvasController(KoCanvasController *controller);

    KoToolBase *activeTool;
    bool tabletPressed;
    bool hasSelection;
    QTimer scrollTimer;
    QPoint widgetScrollPoint;
    KoCanvasController *controller;
    KoToolProxy *parent;

    // used to determine if the mouse-release is after a drag or a simple click
    QPoint mouseDownPoint;

    // up until at least 4.3.0 we get a mouse move event when the tablet leaves the canvas.
    bool mouseLeaveWorkaround;

    // for multi clicking (double click or triple click) we need the following
    int multiClickCount;
    Qt::MouseButton multiClickButton;
    QPointF multiClickGlobalPoint;
    QTime multiClickTimeStamp;
};
#endif // _KO_TOOL_PROXY_H_
