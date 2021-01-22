/* This file is part of the KDE project
 * Copyright (C) 2007 Thomas Zander <zander@kde.org>
 * Copyright (C) 2007,2012 C. Boemann <cbo@boemann.dk>
 * Copyright (C) 2007 Jan Hambrecht <jaham@gmx.net>
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
#ifndef KOZOOMCONTROLLER_H
#define KOZOOMCONTROLLER_H

#include "KoZoomAction.h"
#include "kowidgets_export.h"
#include <KoZoomMode.h>
#include <QObject>
#include <QSizeF>

class KoCanvasController;
class KoZoomAction;
class KoZoomHandler;
class KActionCollection;
class QSize;


/**
 * This controller class handles zoom levels for any canvas.
 *
 * For each KoCanvasController you should have one instance of this
 * class to go with it. This class then creates a KoZoomAction and
 * basically handles all zooming for you.
 *
 * All you need to do is connect to the setDocumentSize() slot and
 * keep the controller up-to-date if your on-screen document ever
 * changes (note that this is in document units, so this is a zoom
 * independent size).
 *
 * If you choose to have zoom modes of 'page' and 'width' you are
 * required to set the page size using the setPageSize() method.
 *
 * Additionally you can connect to the zoomChanged() signal if you
 * want to store the latest zoom level and mode, for example to
 * restore the last used one at next restart.
 *
 * The specialAspectMode toggle is only a UI element. It does nothing
 * except emit the aspectModeChanged signal.
 *
 */
class KOWIDGETS_EXPORT KoZoomController : public QObject {
Q_OBJECT
public:
    /**
    * Constructor. Create one per canvasController.  The zoomAction is created in the constructor and will
    * be available to the passed actionCollection for usage by XMLGui.
    * @param controller the canvasController
    * @param zoomHandler the zoom handler (viewconverter with setter methods)
    * @param actionCollection the action collection where the KoZoomAction is added to
    * @param specialButtons controls which special buttons to show
    * @param parent the parent QObject
    */
    KoZoomController(KoCanvasController *controller,
                     KoZoomHandler *zoomHandler,
                     KActionCollection *actionCollection,
                     KoZoomAction::SpecialButtons specialButtons = nullptr,
                     QObject *parent = nullptr);

    /**
     * A special override for for creation of a zoom controller
     * without automatic generation of standard zoom in and zoom out
     * actions. The caller is supposed create and connect the
     * corresponding actions himself.
     *
     * @param controller the canvasController
     * @param zoomHandler the zoom handler (viewconverter with setter methods)
     * @param actionCollection the action collection where the KoZoomAction is added to
     * @param createZoomShortcuts shows whether the zoom actions should be
     *                            created or not.
     * @param specialButtons controls which special buttons to show
     * @param parent the parent QObject
     *
     * Used in KisZoomController.
     */
    KoZoomController(KoCanvasController *controller,
                     KoZoomHandler *zoomHandler,
                     KActionCollection *actionCollection,
                     bool createZoomShortcuts,
                     KoZoomAction::SpecialButtons specialButtons = nullptr,
                     QObject *parent = nullptr);

    /// destructor
    ~KoZoomController() override;

    /// returns the zoomAction that is maintained by this controller
    KoZoomAction *zoomAction() const;

    /**
     * Alter the current zoom mode which updates the Gui.
     * @param mode the new mode that will be used to auto-calculate a new zoom-level if needed.
     */
    void setZoomMode(KoZoomMode::Mode mode);

    /**
     * Set the resolution, zoom, the zoom mode for this zoom Controller.
     * Typically for use just after construction to restore the
     * persistent data.
     *
     * @param mode new zoom mode for the canvas
     * @param zoom (for ZOOM_CONSTANT zoom mode only) new zoom value for
     *             the canvas
     * @param resolutionX new X resolution for the document
     * @param resolutionY new Y resolution for the document
     * @param stillPoint (for ZOOM_CONSTANT zoom mode only) the point
     *                   which will not change its position in widget
     *                   during the zooming. It is measured in view
     *                   coordinate system *before* zoom.
     */
    void setZoom(KoZoomMode::Mode mode, qreal zoom, qreal resolutionX, qreal resolutionY, const QPointF &stillPoint);


    /**
     * Convenience function that changes resolution with
     * keeping the centering unchanged
     */
    void setZoom(KoZoomMode::Mode mode, qreal zoom, qreal resolutionX, qreal resolutionY);

    /**
     * Convenience function that does not touch the resolution of the
     * document
     */
    void setZoom(KoZoomMode::Mode mode, qreal zoom, const QPointF &stillPoint);

    /**
     * Convenience function with @p center always set to the current
     * center point of the canvas
     */
    void setZoom(KoZoomMode::Mode mode, qreal zoom);


  /**
   * Set Aspect Mode button status and begin a chain of signals
   */
    void setAspectMode(bool status);

public Q_SLOTS:
    /**
    * Set the size of the current page in document coordinates which allows zoom modes that use the pageSize
    * to update.
    * @param pageSize the new page size in points
    */
    void setPageSize(const QSizeF &pageSize);

    /**
    * Returns the size of the current page in document coordinates
    * @returns the page size in points
    */
    QSizeF pageSize() const;

    /**
    * Set the dimensions of where text can appear which allows zoom modes that use the text
    * to update.
    * @param min the minimum x value (in document coordinates) where text can appear
    * @param max the maximum x value (in document coordinates) where text can appear
    */
    void setTextMinMax(qreal min, qreal max);

    /**
    * Set the size of the whole document currently being shown on the canvas.
    * The document size will be used together with the current zoom level to calculate the size of the
    * canvas in the canvasController.
    * @param documentSize the new document size in points
    * @param recalculateCenter tells canvas controller not to touch
    *        preferredCenterFraction
    */
    void setDocumentSize(const QSizeF &documentSize, bool recalculateCenter = false);

    /**
    * Returns the size of the whole document currently being shown on the canvas.
    * @returns the document size in points
    */
    QSizeF documentSize() const;

Q_SIGNALS:
    /**
     * This signal is emitted whenever either the zoommode or the zoom level is changed by the user.
     * the application can use the emitted data for persistency purposes.
     */
    void zoomChanged (KoZoomMode::Mode mode, qreal zoom);

    /**
     * emitted when the special aspect mode toggle changes.
     * @see KoZoomAction::aspectModeChanged()
     */
    void aspectModeChanged (bool aspectModeActivated);

    /**
     * Signal is triggered when the user clicks the zoom to selection button.
     * Nothing else happens except that this signal is emitted.
     */
    void zoomedToSelection();

    /**
     * Signal is triggered when the user clicks the zoom to all button.
     * Nothing else happens except that this signal is emitted.
     */
    void zoomedToAll();

protected:
    virtual QSize documentToViewport(const QSizeF &size);

private:
    Q_PRIVATE_SLOT(d, void setAvailableSize())
    Q_PRIVATE_SLOT(d, void requestZoomRelative(const qreal, const QPointF&))
    Q_PRIVATE_SLOT(d, void setZoom(KoZoomMode::Mode, qreal))
    Q_DISABLE_COPY( KoZoomController )

    class Private;
    Private * const d;
};

#endif
