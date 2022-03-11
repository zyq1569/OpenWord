/* This file is part of the KDE project

   SPDX-FileCopyrightText: 2006-2008 Thorsten Zachmann <zachmann@kde.org>
   SPDX-FileCopyrightText: 2007, 2009 Thomas Zander <zander@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KOSHAPEMANAGER_H
#define KOSHAPEMANAGER_H

#include "KoShapeManager.h"
#include "KoSelection.h"
#include "KoPointerEvent.h"
#include "KoShape.h"
#include "KoShape_p.h"
#include "KoCanvasBase.h"
#include "KoShapeContainer.h"
#include "KoShapeStrokeModel.h"
#include "KoShapeGroup.h"
#include "KoToolProxy.h"
#include "KoShapeManagerPaintingStrategy.h"
#include "KoShapeShadow.h"
#include "KoShapeLayer.h"
#include "KoFilterEffect.h"
#include "KoFilterEffectStack.h"
#include "KoFilterEffectRenderContext.h"
#include "KoShapeBackground.h"
#include <KoRTree.h>
#include "KoClipPath.h"
#include "KoShapePaintingContext.h"

#include <QPainter>
#include <QTimer>
#include <FlakeDebug.h>

#include <QList>
#include <QObject>
#include <QSet>

#include "KoFlake.h"
#include "flake_export.h"

class KoShape;
class KoSelection;
class KoViewConverter;
class KoCanvasBase;
class KoPointerEvent;
class KoShapeManagerPaintingStrategy;
class KoShapePaintingContext;


class QPainter;
class QPointF;
class QRectF;

/**
 * The shape manager hold a list of all shape which are in scope.
 * There is one shape manager per canvas. This makes the shape manager
 * different from QGraphicsScene, which contains the datamodel for all
 * graphics items: KoShapeManager only contains the subset of shapes
 * that are shown in its canvas.
 *
 * The selection in the different views can be different.
 */
class FLAKE_EXPORT KoShapeManager : public QObject
{
    Q_OBJECT

public:
    /// enum for add()
    enum Repaint
    {
        PaintShapeOnAdd,    ///< Causes each shapes 'update()' to be called after being added to the shapeManager
        AddWithoutRepaint   ///< Avoids each shapes 'update()' to be called for faster addition when its possible.
    };

    /**
     * Constructor.
     */
    explicit KoShapeManager(KoCanvasBase *canvas);
    /**
     * Constructor that takes a list of shapes, convenience version.
     * @param shapes the shapes to start out with, see also setShapes()
     * @param canvas the canvas this shape manager is working on.
     */
    KoShapeManager(KoCanvasBase *canvas, const QList<KoShape *> &shapes);
    ~KoShapeManager() override;


    /**
     * Remove all previously owned shapes and make the argument list the new shapes
     * to be managed by this manager.
     * @param shapes the new shapes to manage.
     * @param repaint if true it will trigger a repaint of the shapes
     */
    void setShapes(const QList<KoShape *> &shapes, Repaint repaint = PaintShapeOnAdd);

    /// returns the list of maintained shapes
    QList<KoShape*> shapes() const;

    /**
     * Get a list of all shapes that don't have a parent.
     */
    QList<KoShape*> topLevelShapes() const;

public Q_SLOTS:
    /**
     * Add a KoShape to be displayed and managed by this manager.
     * This will trigger a repaint of the shape.
     * @param shape the shape to add
     * @param repaint if true it will trigger a repaint of the shape
     */
    void addShape(KoShape *shape, KoShapeManager::Repaint repaint = PaintShapeOnAdd);

    /**
     * Add an additional shape to the manager.
     *
     * For additional shapes only updates are handled
     */
    void addAdditional(KoShape *shape);

    /**
     * Remove a KoShape from this manager
     * @param shape the shape to remove
     */
    void remove(KoShape *shape);

    /**
     * Remove an additional shape
     *
     * For additional shapes only updates are handled
     */
    void removeAdditional(KoShape *shape);

public:
    /// return the selection shapes for this shapeManager
    KoSelection *selection() const;

    /**
     * Paint all shapes and their selection handles etc.
     * @param painter the painter to paint to.
     * @param forPrint if true, make sure only actual content is drawn and no decorations.
     * @param converter to convert between document and view coordinates.
     */
    void paint(QPainter &painter, const KoViewConverter &converter, bool forPrint);

    /**
     * Returns the shape located at a specific point in the document.
     * If more than one shape is located at the specific point, the given selection type
     * controls which of them is returned.
     * @param position the position in the document coordinate system.
     * @param selection controls which shape is returned when more than one shape is at the specific point
     * @param omitHiddenShapes if true, only visible shapes are considered
     */
    KoShape *shapeAt(const QPointF &position, KoFlake::ShapeSelection selection = KoFlake::ShapeOnTop, bool omitHiddenShapes = true);

    /**
     * Returns the shapes which intersects the specific rect in the document.
     * @param rect the rectangle in the document coordinate system.
     * @param omitHiddenShapes if true, only visible shapes are considered
     */
    QList<KoShape *> shapesAt(const QRectF &rect, bool omitHiddenShapes = true);

    /**
     * Request a repaint to be queued.
     * The repaint will be restricted to the parameters rectangle, which is expected to be
     * in points (the document coordinates system of KoShape) and it is expected to be
     * normalized and based in the global coordinates, not any local coordinates.
     * <p>This method will return immediately and only request a repaint. Successive calls
     * will be merged into an appropriate repaint action.
     * @param rect the rectangle (in pt) to queue for repaint.
     * @param shape the shape that is going to be redrawn; only needed when selectionHandles=true
     * @param selectionHandles if true; find out if the shape is selected and repaint its
     *   selection handles at the same time.
     */
    void update(QRectF &rect, const KoShape *shape = 0, bool selectionHandles = false);

    /**
     * Update the tree for finding the shapes.
     * This will remove the shape from the tree and will reinsert it again.
     * The update to the tree will be postponed until it is needed so that successive calls
     * will be merged into one.
     * @param shape the shape to updated its position in the tree.
     */
    void notifyShapeChanged(KoShape *shape);

    /**
     * Switch to editing the shape that is at the position of the event.
     * This method will check select a shape at the event position and switch to the default tool
     * for that shape, or switch to the default tool if there is no shape at the position.
     * @param event the event that holds the point where to look for a shape.
     */
    void suggestChangeTool(KoPointerEvent *event);

    /**
     * Paint a shape
     *
     * @param shape the shape to paint
     * @param painter the painter to paint to.
     * @param converter to convert between document and view coordinates.
     * @param paintContext the painting context.
     */
    void paintShape(KoShape *shape, QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &paintContext);

    /**
     * Set the strategy of the KoShapeManager
     *
     * This can be used to change the behaviour of the painting of the shapes.
     * @param strategy the new strategy. The ownership of the argument \p
     *    strategy will be taken by the shape manager.
     */
    void setPaintingStrategy(KoShapeManagerPaintingStrategy *strategy);

Q_SIGNALS:
    /// emitted when the selection is changed
    void selectionChanged();
    /// emitted when an object in the selection is changed (moved/rotated etc)
    void selectionContentChanged();
    /// emitted when any object changed (moved/rotated etc)
    void contentChanged();
    /// emitted when a shape is removed.
    void shapeRemoved(KoShape *);
    /// emitted when any shape changed.
    void shapeChanged(KoShape *);

private:

    friend class KoShapeManagerPaintingStrategy;
    KoCanvasBase *canvas();


    class Private;
    Private * const d;
    Q_PRIVATE_SLOT(d, void updateTree())
};


class Q_DECL_HIDDEN KoShapeManager::Private
{
public:
    Private(KoShapeManager *shapeManager, KoCanvasBase *c)
        : selection(new KoSelection()),
          canvas(c),
          tree(4, 2),
          strategy(new KoShapeManagerPaintingStrategy(shapeManager)),
          q(shapeManager)
    {
    }

    ~Private()
    {
        delete selection;
        delete strategy;
    }

    /**
     * Update the tree when there are shapes in m_aggregate4update. This is done so not all
     * updates to the tree are done when they are asked for but when they are needed.
     */
    void updateTree();

    /**
     * Recursively paints the given group shape to the specified painter
     * This is needed for filter effects on group shapes where the filter effect
     * applies to all the children of the group shape at once
     */
    void paintGroup(KoShapeGroup *group, QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &paintContext);

    class DetectCollision
    {
    public:
        DetectCollision()
        {

        }
        void detect(KoRTree<KoShape *> &tree, KoShape *s, int prevZIndex)
        {
            foreach(KoShape *shape, tree.intersects(s->boundingRect()))
            {
                bool isChild = false;
                KoShapeContainer *parent = s->parent();
                while (parent && !isChild)
                {
                    if (parent == shape)
                    {
                        isChild = true;
                    }
                    parent = parent->parent();
                }
                if (isChild)
                {
                    continue;
                }
                if (s->zIndex() <= shape->zIndex() && prevZIndex <= shape->zIndex())
                    // Moving a shape will only make it collide with shapes below it.
                {
                    continue;
                }
                if (shape->collisionDetection() && !shapesWithCollisionDetection.contains(shape))
                {
                    shapesWithCollisionDetection.append(shape);
                }
            }
        }

        void fireSignals()
        {
            foreach(KoShape *shape, shapesWithCollisionDetection)
            {
                shape->priv()->shapeChanged(KoShape::CollisionDetected);
            }
        }

    private:
        QList<KoShape*> shapesWithCollisionDetection;
    };

    QList<KoShape *> shapes;
    QList<KoShape *> additionalShapes; // these are shapes that are only handled for updates
    KoSelection *selection;
    KoCanvasBase *canvas;
    KoRTree<KoShape *> tree;
    QSet<KoShape *> aggregate4update;
    QHash<KoShape*, int> shapeIndexesBeforeUpdate;
    KoShapeManagerPaintingStrategy *strategy;
    KoShapeManager *q;
};

#endif
