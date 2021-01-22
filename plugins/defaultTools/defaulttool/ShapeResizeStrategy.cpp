/* This file is part of the KDE project
 * Copyright (C) 2006-2007 Thomas Zander <zander@kde.org>
 * Copyright (C) 2007,2011 Jan Hambrecht <jaham@gmx.net>
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

#include "ShapeResizeStrategy.h"
#include "SelectionDecorator.h"

#include "ChartResizeStrategy.h"
#include <KoChartInterface.h>

#include <KoShapeManager.h>
#include <KoPointerEvent.h>
#include <KoCanvasBase.h>
#include <commands/KoShapeSizeCommand.h>
#include <commands/KoShapeTransformCommand.h>
#include <KoSnapGuide.h>
#include <KoToolBase.h>
#include <KoSelection.h>
#include <KoShapeContainer.h>
#include <KoShapeContainerModel.h>

#include <klocalizedstring.h>
#include <limits>
#include <math.h>

#include <QDebug>

ShapeResizeStrategy::ShapeResizeStrategy(KoToolBase *tool,
        const QPointF &clicked, KoFlake::SelectionHandle direction )
    : KoInteractionStrategy(tool), m_lastScale(1.0,1.0)
{
    // FIXME: This test is also done in DefaultTool, so it should also be responsible for setting the shapes to operate on
    Q_ASSERT(tool->canvas()->shapeManager()->selection()->count() > 0);
    QList<KoShape*> selectedShapes = tool->canvas()->shapeManager()->selection()->selectedShapes(KoFlake::StrippedSelection);
    foreach(KoShape *shape, selectedShapes) {
        if (shape->allowedInteraction(KoShape::ResizeAllowed, false)) {
            m_selectedShapes << shape;
            m_startPositions << shape->position();
            m_oldTransforms << shape->transformation();
            m_transformations << QTransform();
            m_startSizes << shape->size();
        }
    }
    m_start = clicked;

    KoShape *shp = 0;
    if (tool->canvas()->shapeManager()->selection()->count()>1)
       shp = tool->canvas()->shapeManager()->selection();
    if (tool->canvas()->shapeManager()->selection()->count()==1)
        shp = tool->canvas()->shapeManager()->selection()->firstSelectedShape();

    if ( shp )
    {
        m_windMatrix = shp->absoluteTransformation(0);
        m_unwindMatrix = m_windMatrix.inverted();
        m_initialSize = shp->size();
        m_initialPosition = m_windMatrix.map(QPointF());
    }

    switch(direction) {
        case KoFlake::TopMiddleHandle:
            m_start = 0.5 * (shp->absolutePosition(KoFlake::TopLeftCorner) + shp->absolutePosition(KoFlake::TopRightCorner) );
            m_top = true; m_bottom = false; m_left = false; m_right = false; break;
        case KoFlake::TopRightHandle:
            m_start = shp->absolutePosition(KoFlake::TopRightCorner);
            m_top = true; m_bottom = false; m_left = false; m_right = true; break;
        case KoFlake::RightMiddleHandle:
            m_start = 0.5 * ( shp->absolutePosition(KoFlake::TopRightCorner) + shp->absolutePosition(KoFlake::BottomRightCorner) );
            m_top = false; m_bottom = false; m_left = false; m_right = true; break;
        case KoFlake::BottomRightHandle:
            m_start = shp->absolutePosition(KoFlake::BottomRightCorner);
            m_top = false; m_bottom = true; m_left = false; m_right = true; break;
        case KoFlake::BottomMiddleHandle:
            m_start = 0.5 * ( shp->absolutePosition(KoFlake::BottomRightCorner) + shp->absolutePosition(KoFlake::BottomLeftCorner) );
            m_top = false; m_bottom = true; m_left = false; m_right = false; break;
        case KoFlake::BottomLeftHandle:
            m_start = shp->absolutePosition(KoFlake::BottomLeftCorner);
            m_top = false; m_bottom = true; m_left = true; m_right = false; break;
        case KoFlake::LeftMiddleHandle:
            m_start = 0.5 * ( shp->absolutePosition(KoFlake::BottomLeftCorner) + shp->absolutePosition(KoFlake::TopLeftCorner) );
            m_top = false; m_bottom = false; m_left = true; m_right = false; break;
        case KoFlake::TopLeftHandle:
            m_start = shp->absolutePosition(KoFlake::TopLeftCorner);
            m_top = true; m_bottom = false; m_left = true; m_right = false; break;
        default:
             Q_ASSERT(0); // illegal 'corner'
    }

    tool->setStatusText( i18n("Press CTRL to resize from center.") );

    // Handle possible chart shapes
    for (KoShape *s : m_selectedShapes) {
        if (s->shapeId() == ChartShapeId) {
            m_chartShapes.insert(s, new ChartResizeStrategy(s));
        }
    }
}

ShapeResizeStrategy::~ShapeResizeStrategy()
{
    qDeleteAll(m_chartShapes);
}


void ShapeResizeStrategy::handleMouseMove(const QPointF &point, Qt::KeyboardModifiers modifiers)
{
    tool()->canvas()->updateCanvas(tool()->canvas()->snapGuide()->boundingRect());
    QPointF newPos = tool()->canvas()->snapGuide()->snap( point, modifiers );
    tool()->canvas()->updateCanvas(tool()->canvas()->snapGuide()->boundingRect());

    bool keepAspect = modifiers & Qt::ShiftModifier;
    foreach(KoShape *shape, m_selectedShapes)
        keepAspect = keepAspect || shape->keepAspectRatio();

    qreal startWidth = m_initialSize.width();
    if (startWidth < std::numeric_limits<qreal>::epsilon())
        startWidth = std::numeric_limits<qreal>::epsilon();
    qreal startHeight = m_initialSize.height();
    if (startHeight < std::numeric_limits<qreal>::epsilon())
        startHeight = std::numeric_limits<qreal>::epsilon();

    QPointF distance = m_unwindMatrix.map(newPos) - m_unwindMatrix.map( m_start );
    // guard against resizing zero width shapes, which would result in huge zoom factors
    if (m_initialSize.width() < std::numeric_limits<qreal>::epsilon()) {
        distance.rx() = 0.0;
    }
    // guard against resizing zero height shapes, which would result in huge zoom factors
    if (m_initialSize.height() < std::numeric_limits<qreal>::epsilon()) {
        distance.ry() = 0.0;
    }

    const bool scaleFromCenter = modifiers & Qt::ControlModifier;
    if (scaleFromCenter) {
        distance *= 2.0;
    }

    qreal newWidth = startWidth;
    qreal newHeight = startHeight;

    if (m_left) {
        newWidth = startWidth - distance.x();
    } else if (m_right) {
        newWidth = startWidth + distance.x();
    }

    if (m_top) {
        newHeight = startHeight - distance.y();
    } else if (m_bottom) {
        newHeight = startHeight + distance.y();
    }

    /**
     * Do not let a shape be less than 1px in size in current view
     * coordinates.  If the user wants it to be smaller, he can just
     * zoom-in a bit.
     */
    QSizeF minViewSize(1.0, 1.0);
    QSizeF minDocSize = tool()->canvas()->viewConverter()->viewToDocument(minViewSize);

    if (qAbs(newWidth) < minDocSize.width()) {
        int sign = newWidth >= 0.0 ? 1 : -1; // zero -> '1'
        newWidth = sign * minDocSize.width();
    }

    if (qAbs(newHeight) < minDocSize.height()) {
        int sign = newHeight >= 0.0 ? 1 : -1; // zero -> '1'
        newHeight = sign * minDocSize.height();
    }

    qreal zoomX = newWidth / startWidth;
    qreal zoomY = newHeight / startHeight;

    if (keepAspect) {
        const bool cornerUsed = ((m_bottom?1:0) + (m_top?1:0) + (m_left?1:0) + (m_right?1:0)) == 2;
        if ((cornerUsed && startWidth < startHeight) || m_left || m_right)
            zoomY = zoomX;
        else
            zoomX = zoomY;
    }

    QPointF move;

    if (scaleFromCenter)
        move = QPointF(startWidth / 2.0, startHeight / 2.0);
    else
        move = QPointF(m_left?startWidth:0, m_top?startHeight:0);

    resizeBy( move, zoomX, zoomY );
}

void ShapeResizeStrategy::handleCustomEvent( KoPointerEvent * event )
{
    QPointF center = 0.5 * QPointF( m_initialSize.width(), m_initialSize.height() );
    qreal zoom = pow(1.01, -0.1 * event->z() );
    m_lastScale *= zoom;
    resizeBy( center, m_lastScale.x(), m_lastScale.y() );
}

void ShapeResizeStrategy::resizeBy( const QPointF &center, qreal zoomX, qreal zoomY )
{
    QTransform matrix;
    matrix.translate(center.x(), center.y()); // translate to
    matrix.scale(zoomX, zoomY);
    matrix.translate(-center.x(), -center.y()); // and back

    // that is the transformation we want to apply to the shapes
    matrix = m_unwindMatrix * matrix * m_windMatrix;

    // the resizing transformation without the mirroring part
    QTransform resizeMatrix;
    resizeMatrix.translate(center.x(), center.y()); // translate to
    resizeMatrix.scale( qAbs(zoomX), qAbs(zoomY) );
    resizeMatrix.translate(-center.x(), -center.y()); // and back

    // the mirroring part of the resizing transformation
    QTransform mirrorMatrix;
    mirrorMatrix.translate(center.x(), center.y()); // translate to
    mirrorMatrix.scale( zoomX < 0 ? -1 : 1, zoomY < 0 ? -1 : 1 );
    mirrorMatrix.translate(-center.x(), -center.y()); // and back

    int i = 0;
    foreach(KoShape *shape, m_selectedShapes)
    {
        shape->update();
        // HACK: Complex shapes like calloutshapes needs more control than setSize() gives
        // as when resizing top/left it implies a positional change too.
        // We cannot use the GenericMatrixChange above because it is used a number of times
        // so it is impossible to know when it is relevant.
        KoShapeContainer *container = dynamic_cast<KoShapeContainer*>(shape);
        if (container && container->model()) {
            container->model()->containerChanged(container, KoShape::BeginResize);
        }
        
        // this uses resize for the zooming part
        shape->applyAbsoluteTransformation( m_unwindMatrix );

        /*
         normally we would just apply the resizeMatrix now and be done with it, but
         we want to resize instead of scale, so we have to separate the scaling part
         of that transformation which can then be used to resize
        */

        // undo the last resize transformation
        shape->applyAbsoluteTransformation( m_transformations[i].inverted() );

        // save the shapes transformation matrix
        QTransform shapeMatrix = shape->absoluteTransformation(0);

        // calculate the matrix we would apply to the local shape matrix
        // that tells us the effective scale values we have to use for the resizing
        QTransform localMatrix = shapeMatrix * resizeMatrix * shapeMatrix.inverted();
        // save the effective scale values
        qreal scaleX = localMatrix.m11();
        qreal scaleY = localMatrix.m22();

        // calculate the scale matrix which is equivalent to our resizing above
        QTransform scaleMatrix = (QTransform().scale( scaleX, scaleY ));
        scaleMatrix =  shapeMatrix.inverted() * scaleMatrix * shapeMatrix;

        // calculate the new size of the shape, using the effective scale values
        QSizeF size( scaleX * m_startSizes[i].width(), scaleY * m_startSizes[i].height() );
        // If a chart shape, handle its children
        if (m_chartShapes.contains(shape)) {
            m_chartShapes[shape]->setSize(m_startSizes[i], scaleX, scaleY);
        }
        // apply the transformation
        shape->setSize( size );
        // apply the rest of the transformation without the resizing part
        shape->applyAbsoluteTransformation( scaleMatrix.inverted() * resizeMatrix );
        shape->applyAbsoluteTransformation( mirrorMatrix );

        // and remember the applied transformation later for later undoing
        m_transformations[i] = shapeMatrix.inverted() * shape->absoluteTransformation(0);

        shape->applyAbsoluteTransformation( m_windMatrix );
        if (container && container->model()) {
            container->model()->containerChanged(container, KoShape::EndResize);
        }
        shape->update();
        i++;
    }
    tool()->canvas()->shapeManager()->selection()->applyAbsoluteTransformation( matrix * m_scaleMatrix.inverted() );
    m_scaleMatrix = matrix;
}

KUndo2Command* ShapeResizeStrategy::createCommand()
{
    tool()->canvas()->snapGuide()->reset();
    QVector<QSizeF> newSizes;
    QVector<QTransform> transformations;
    const int shapeCount = m_selectedShapes.count();

    newSizes.reserve(shapeCount);
    transformations.reserve(shapeCount);
    for ( int i = 0; i < shapeCount; ++i )
    {
        newSizes << m_selectedShapes[i]->size();
        transformations << m_selectedShapes[i]->transformation();
    }
    qInfo()<<Q_FUNC_INFO<<transformations;
    KUndo2Command * cmd = new KUndo2Command(kundo2_i18n("Resize"));
    new KoShapeSizeCommand(m_selectedShapes, m_startSizes, newSizes, cmd );
    new KoShapeTransformCommand( m_selectedShapes, m_oldTransforms, transformations, cmd );
    for (KoShape *s : m_selectedShapes) {
        if (m_chartShapes.contains(s)) {
            m_chartShapes[s]->createCommand(cmd);
        }
    }
    return cmd;
}

void ShapeResizeStrategy::finishInteraction(Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);
    tool()->canvas()->updateCanvas(tool()->canvas()->snapGuide()->boundingRect());
}

void ShapeResizeStrategy::paint( QPainter &painter, const KoViewConverter &converter)
{
    SelectionDecorator decorator (KoFlake::NoHandle, false, false);
    decorator.setSelection(tool()->canvas()->shapeManager()->selection());
    decorator.setHandleRadius(handleRadius());
    decorator.paint(painter, converter);
}
