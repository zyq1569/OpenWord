/* This file is part of the KDE project

   Copyright (C) 2006-2008 Thorsten Zachmann <zachmann@kde.org>
   Copyright (C) 2006-2008 Thomas Zander <zander@kde.org>

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
 * Boston, MA 02110-1301, USA.
*/

#ifndef DEFAULTTOOL_H
#define DEFAULTTOOL_H

#include <KoInteractionTool.h>
#include <KoFlake.h>
#include <KoShape.h>
#include <commands/KoShapeAlignCommand.h>
#include <commands/KoShapeReorderCommand.h>

#include <QPolygonF>
#include <QTime>

class KoInteractionStrategy;
class KoShapeMoveCommand;
class KoSelection;

/**
 * The default tool (associated with the arrow icon) implements the default
 * interactions you have with flake objects.<br>
 * The tool provides scaling, moving, selecting, rotation and soon skewing of
 * any number of shapes.
 * <p>Note that the implementation of those different strategies are delegated
 * to the InteractionStrategy class and its subclasses.
 */
class DefaultTool : public KoInteractionTool
{
    Q_OBJECT
public:
    /**
     * Constructor for basic interaction tool where user actions are translated
     * and handled by interaction strategies of type KoInteractionStrategy.
     * @param canvas the canvas this tool will be working for.
     */
    explicit DefaultTool( KoCanvasBase *canvas );
    ~DefaultTool() override;

    enum CanvasResource {
        HotPosition = 1410100299
    };

public:

    bool wantsAutoScroll() const override;
    void paint( QPainter &painter, const KoViewConverter &converter ) override;

    void repaintDecorations() override;

    ///reimplemented
    void copy() const override;

    ///reimplemented
    void deleteSelection() override;

    ///reimplemented
    bool paste() override;
    ///reimplemented
    QStringList supportedPasteMimeTypes() const override;
    ///reimplemented
    KoToolSelection* selection() override;

    /**
     * Returns which selection handle is at params point (or NoHandle if none).
     * @return which selection handle is at params point (or NoHandle if none).
     * @param point the location (in pt) where we should look for a handle
     * @param innerHandleMeaning this boolean is altered to true if the point
     *   is inside the selection rectangle and false if it is just outside.
     *   The value of innerHandleMeaning is undefined if the handle location is NoHandle
     */
    KoFlake::SelectionHandle handleAt(const QPointF &point, bool *innerHandleMeaning = 0);

public Q_SLOTS:
    /// Activate the tool and paint selection handles
    void activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes) override;
    /// Deactivate the tool and remove selection handles
    void deactivate() override;

private Q_SLOTS:
    void selectionAlignHorizontalLeft();
    void selectionAlignHorizontalCenter();
    void selectionAlignHorizontalRight();
    void selectionAlignVerticalTop();
    void selectionAlignVerticalCenter();
    void selectionAlignVerticalBottom();

    void selectionBringToFront();
    void selectionSendToBack();
    void selectionMoveUp();
    void selectionMoveDown();

    void selectionGroup();
    void selectionUngroup();

    /// Update actions on selection change
    void updateActions();

public: // Events

    void mousePressEvent( KoPointerEvent *event ) override;
    void mouseMoveEvent( KoPointerEvent *event ) override;
    void mouseReleaseEvent( KoPointerEvent *event ) override;
    void mouseDoubleClickEvent( KoPointerEvent *event ) override;

    void keyPressEvent(QKeyEvent *event) override;

    void customMoveEvent( KoPointerEvent * event ) override;

protected:
    QList<QPointer<QWidget> > createOptionWidgets() override;

    KoInteractionStrategy *createStrategy(KoPointerEvent *event) override;

private:
    void setupActions();
    void recalcSelectionBox();
    void updateCursor();
    /// Returns rotation angle of given handle of the current selection
    qreal rotationOfHandle( KoFlake::SelectionHandle handle, bool useEdgeRotation );

    void selectionAlign(KoShapeAlignCommand::Align align);
    void selectionReorder(KoShapeReorderCommand::MoveShapeType order );
    bool moveSelection( int direction, Qt::KeyboardModifiers modifiers );

    /// Returns selection rectangle adjusted by handle proximity threshold
    QRectF handlesSize();

    // convenience method;
    KoSelection * koSelection();

    void canvasResourceChanged( int key, const QVariant & res ) override;

    /// selects guide line at given position
    void selectGuideAtPosition( const QPointF &position );

    /// Returns list of editable shapes from the given list of shapes
    QList<KoShape*> filterEditableShapes( const QList<KoShape*> &shapes ) const;

    /// Returns the number of editable shapes from the given list of shapes
    uint editableShapesCount( const QList<KoShape*> &shapes ) const;

    /// Return true if @p shape is editable.
    /// For now, this is just reimplemented using AllowedInteraction flags
    /// TODO: Check more flags
    bool isEditable(const KoShape *shape) const;

    /// Returns the interactions allowed on any of the @p shapes
    KoShape::AllowedInteractions allowedInteractions(const QList<KoShape*> &shapes) const;

    KoFlake::SelectionHandle m_lastHandle;
    KoFlake::Position m_hotPosition;
    bool m_mouseWasInsideHandles;
    QPointF m_selectionBox[8];
    QPolygonF m_selectionOutline;
    QPointF m_lastPoint;
    KoShapeMoveCommand *m_moveCommand;
    QTime m_lastUsedMoveCommand;
    QList<KoShape*> m_lastUsedShapes;

    // TODO alter these 3 arrays to be static const instead
    QCursor m_sizeCursors[8];
    QCursor m_rotateCursors[8];
    QCursor m_shearCursors[8];
    qreal m_angle;
    KoToolSelection *m_selectionHandler;
    friend class SelectionHandler;
    KoInteractionStrategy * m_customEventStrategy;

    class GuideLine;
    GuideLine * m_guideLine;
};

#endif
