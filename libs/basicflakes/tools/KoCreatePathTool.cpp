/* This file is part of the KDE project
 *
 * Copyright (C) 2006 Thorsten Zachmann <zachmann@kde.org>
 * Copyright (C) 2008-2010 Jan Hambrecht <jaham@gmx.net>
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

#include "KoCreatePathTool_p.h"
#include "KoCreatePathTool.h"

#include "KoPointerEvent.h"
#include "KoPathShape.h"
#include "KoSelection.h"
#include "KoDocumentResourceManager.h"
#include "KoShapePaintingContext.h"
#include "KoShapeStroke.h"
#include <KoColor.h>

#include <klocalizedstring.h>

#include <QSpinBox>
#include <QPainter>
#include <QLabel>
#include <QGridLayout>
#include <QCheckBox>

//class KoCreatePathToolPrivate : public KoToolBasePrivate
//{
//    KoCreatePathTool * const q;
//public:
//    KoCreatePathToolPrivate(KoCreatePathTool * const qq, KoCanvasBase* canvas)
//        : KoToolBasePrivate(qq, canvas),
//          q(qq),
//          shape(0),
//          activePoint(0),
//          firstPoint(0),
//          handleRadius(3),
//          mouseOverFirstPoint(false),
//          pointIsDragged(false),
//          finishAfterThisPoint(false),
//          hoveredPoint(0),
//          listeningToModifiers(false),
//          angleSnapStrategy(0),
//          angleSnappingDelta(15),
//          angleSnapStatus(false),
//          strokeWidget(0)
//    {}

//    KoPathShape *shape;
//    KoPathPoint *activePoint;
//    KoPathPoint *firstPoint;
//    int handleRadius;
//    bool mouseOverFirstPoint;
//    bool pointIsDragged;
//    bool finishAfterThisPoint;
//    PathConnectionPoint existingStartPoint; ///< an existing path point we started a new path at
//    PathConnectionPoint existingEndPoint;   ///< an existing path point we finished a new path at
//    KoPathPoint *hoveredPoint; ///< an existing path end point the mouse is hovering on
//    bool listeningToModifiers; //  Fine tune when to begin processing modifiers at the beginning of a stroke.

//    AngleSnapStrategy *angleSnapStrategy;
//    int angleSnappingDelta;
//    bool angleSnapStatus;
//    KoStrokeConfigWidget *strokeWidget;

//    void repaintActivePoint() const
//    {
//        const bool isFirstPoint = (activePoint == firstPoint);

//        if (!isFirstPoint && !pointIsDragged)
//        {
//            return;
//        }

//        QRectF rect = activePoint->boundingRect(false);

//        // make sure that we have the second control point inside our
//        // update rect, as KoPathPoint::boundingRect will not include
//        // the second control point of the last path point if the path
//        // is not closed
//        const QPointF &point = activePoint->point();
//        const QPointF &controlPoint = activePoint->controlPoint2();
//        rect = rect.united(QRectF(point, controlPoint).normalized());

//        // when painting the first point we want the
//        // first control point to be painted as well
//        if (isFirstPoint)
//        {
//            const QPointF &controlPoint = activePoint->controlPoint1();
//            rect = rect.united(QRectF(point, controlPoint).normalized());
//        }

//        QPointF border = q->canvas()->viewConverter()
//                         ->viewToDocument(QPointF(handleRadius, handleRadius));

//        rect.adjust(-border.x(), -border.y(), border.x(), border.y());
//        q->canvas()->updateCanvas(rect);
//    }

//    /// returns the nearest existing path point
//    KoPathPoint* endPointAtPosition( const QPointF &position ) const
//    {
//        QRectF roi = q->handleGrabRect(position);
//        QList<KoShape *> shapes = q->canvas()->shapeManager()->shapesAt(roi);

//        KoPathPoint * nearestPoint = 0;
//        qreal minDistance = HUGE_VAL;
//        uint grabSensitivity = q->grabSensitivity();
//        qreal maxDistance = q->canvas()->viewConverter()->viewToDocumentX(grabSensitivity);

//        foreach(KoShape *s, shapes)
//        {
//            KoPathShape * path = dynamic_cast<KoPathShape*>(s);
//            if (!path)
//            {
//                continue;
//            }
//            KoParameterShape *paramShape = dynamic_cast<KoParameterShape*>(s);
//            if (paramShape && paramShape->isParametricShape())
//            {
//                continue;
//            }

//            KoPathPoint * p = 0;
//            uint subpathCount = path->subpathCount();
//            for (uint i = 0; i < subpathCount; ++i)
//            {
//                if (path->isClosedSubpath(i))
//                {
//                    continue;
//                }
//                p = path->pointByIndex(KoPathPointIndex(i, 0));
//                // check start of subpath
//                qreal d = squareDistance(position, path->shapeToDocument(p->point()));
//                if (d < minDistance && d < maxDistance)
//                {
//                    nearestPoint = p;
//                    minDistance = d;
//                }
//                // check end of subpath
//                p = path->pointByIndex(KoPathPointIndex(i, path->subpathPointCount(i)-1));
//                d = squareDistance(position, path->shapeToDocument(p->point()));
//                if (d < minDistance && d < maxDistance)
//                {
//                    nearestPoint = p;
//                    minDistance = d;
//                }
//            }
//        }

//        return nearestPoint;
//    }

//    /// Connects given path with the ones we hit when starting/finishing
//    bool connectPaths( KoPathShape *pathShape, const PathConnectionPoint &pointAtStart, const PathConnectionPoint &pointAtEnd ) const
//    {
//        KoPathShape * startShape = 0;
//        KoPathShape * endShape = 0;
//        KoPathPoint * startPoint = 0;
//        KoPathPoint * endPoint = 0;

//        if (pointAtStart.isValid())
//        {
//            startShape = pointAtStart.path;
//            startPoint = pointAtStart.point;
//        }
//        if (pointAtEnd.isValid())
//        {
//            endShape = pointAtEnd.path;
//            endPoint = pointAtEnd.point;
//        }

//        // at least one point must be valid
//        if (!startPoint && !endPoint)
//        {
//            return false;
//        }
//        // do not allow connecting to the same point twice
//        if (startPoint == endPoint)
//        {
//            endPoint = 0;
//        }

//        // we have hit an existing path point on start/finish
//        // what we now do is:
//        // 1. combine the new created path with the ones we hit on start/finish
//        // 2. merge the endpoints of the corresponding subpaths

//        uint newPointCount = pathShape->subpathPointCount(0);
//        KoPathPointIndex newStartPointIndex(0, 0);
//        KoPathPointIndex newEndPointIndex(0, newPointCount-1);
//        KoPathPoint * newStartPoint = pathShape->pointByIndex(newStartPointIndex);
//        KoPathPoint * newEndPoint = pathShape->pointByIndex(newEndPointIndex);

//        // combine with the path we hit on start
//        KoPathPointIndex startIndex(-1,-1);
//        if (startShape && startPoint)
//        {
//            startIndex = startShape->pathPointIndex(startPoint);
//            pathShape->combine(startShape);
//            pathShape->moveSubpath(0, pathShape->subpathCount()-1);
//        }
//        // combine with the path we hit on finish
//        KoPathPointIndex endIndex(-1,-1);
//        if (endShape && endPoint)
//        {
//            endIndex = endShape->pathPointIndex(endPoint);
//            if (endShape != startShape)
//            {
//                endIndex.first += pathShape->subpathCount();
//                pathShape->combine(endShape);
//            }
//        }
//        // do we connect twice to a single subpath ?
//        bool connectToSingleSubpath = (startShape == endShape && startIndex.first == endIndex.first);

//        if (startIndex.second == 0 && !connectToSingleSubpath)
//        {
//            pathShape->reverseSubpath(startIndex.first);
//            startIndex.second = pathShape->subpathPointCount(startIndex.first)-1;
//        }
//        if (endIndex.second > 0 && !connectToSingleSubpath)
//        {
//            pathShape->reverseSubpath(endIndex.first);
//            endIndex.second = 0;
//        }

//        // after combining we have a path where with the subpaths in the following
//        // order:
//        // 1. the subpaths of the pathshape we started the new path at
//        // 2. the subpath we just created
//        // 3. the subpaths of the pathshape we finished the new path at

//        // get the path points we want to merge, as these are not going to
//        // change while merging
//        KoPathPoint * existingStartPoint = pathShape->pointByIndex(startIndex);
//        KoPathPoint * existingEndPoint = pathShape->pointByIndex(endIndex);

//        // merge first two points
//        if (existingStartPoint)
//        {
//            KoPathPointData pd1(pathShape, pathShape->pathPointIndex(existingStartPoint));
//            KoPathPointData pd2(pathShape, pathShape->pathPointIndex(newStartPoint));
//            KoPathPointMergeCommand cmd1(pd1, pd2);
//            cmd1.redo();
//        }
//        // merge last two points
//        if (existingEndPoint)
//        {
//            KoPathPointData pd3(pathShape, pathShape->pathPointIndex(newEndPoint));
//            KoPathPointData pd4(pathShape, pathShape->pathPointIndex(existingEndPoint));
//            KoPathPointMergeCommand cmd2(pd3, pd4);
//            cmd2.redo();
//        }

//        return true;
//    }

//    void addPathShape()
//    {
//        if (!shape)
//        {
//            return;
//        }

//        if (shape->pointCount() < 2)
//        {
//            cleanUp();
//            return;
//        }

//        // this is done so that nothing happens when the mouseReleaseEvent for the this event is received
//        KoPathShape *pathShape = shape;
//        shape=0;

//        q->addPathShape(pathShape);

//        cleanUp();

//        return;
//    }

//    void cleanUp()
//    {
//        // reset snap guide
//        q->canvas()->updateCanvas(q->canvas()->snapGuide()->boundingRect());
//        q->canvas()->snapGuide()->reset();
//        angleSnapStrategy = 0;

//        delete shape;
//        shape=0;
//        existingStartPoint = 0;
//        existingEndPoint = 0;
//        hoveredPoint = 0;
//        listeningToModifiers = false;
//    }

//    void angleDeltaChanged(int value)
//    {
//        angleSnappingDelta = value;
//        if (angleSnapStrategy)
//        {
//            angleSnapStrategy->setAngleStep(angleSnappingDelta);
//        }
//    }

//    void angleSnapChanged(int angleSnap)
//    {
//        angleSnapStatus = ! angleSnapStatus;
//        if(angleSnapStrategy)
//        {
//            if(angleSnap == Qt::Checked)
//            {
//                angleSnapStrategy->activate();
//            }
//            else
//            {
//                angleSnapStrategy->deactivate();
//            }
//        }
//    }
//};


KoCreatePathTool::KoCreatePathTool(KoCanvasBase *canvas)
    : KoToolBase(*(new KoCreatePathToolPrivate(this, canvas)))
{
}

KoCreatePathTool::~KoCreatePathTool()
{
}

void KoCreatePathTool::paint(QPainter &painter, const KoViewConverter &converter)
{
    Q_D(KoCreatePathTool);
    if (pathStarted())
    {
        KoShapeStroke *stroke(createStroke());
        if (stroke)
        {
            d->shape->setStroke(stroke);
        }
        painter.save();
        paintPath(*(d->shape), painter, converter);
        painter.restore();

        painter.save();

        painter.setTransform(d->shape->absoluteTransformation(&converter) * painter.transform());

        KoShape::applyConversion(painter, converter);

        painter.setPen(QPen(Qt::blue, 0));
        painter.setBrush(Qt::white);   //TODO make configurable

        const bool firstPoint = (d->firstPoint == d->activePoint);
        if (d->pointIsDragged || firstPoint)
        {
            const bool onlyPaintActivePoints = false;
            KoPathPoint::PointTypes paintFlags = KoPathPoint::ControlPoint2;
            if (d->activePoint->activeControlPoint1())
            {
                paintFlags |= KoPathPoint::ControlPoint1;
            }
            d->activePoint->paint(painter, d->handleRadius, paintFlags, onlyPaintActivePoints);
        }


        // check if we have to color the first point
        if (d->mouseOverFirstPoint)
        {
            painter.setBrush(Qt::red);    //TODO make configurable
        }
        else
        {
            painter.setBrush(Qt::white);    //TODO make configurable
        }

        d->firstPoint->paint(painter, d->handleRadius, KoPathPoint::Node);

        painter.restore();
    }

    if (d->hoveredPoint)
    {
        painter.save();
        painter.setTransform(d->hoveredPoint->parent()->absoluteTransformation(&converter), true);
        KoShape::applyConversion(painter, converter);
        painter.setPen(QPen(Qt::blue, 0));
        painter.setBrush(Qt::white);   //TODO make configurable
        d->hoveredPoint->paint(painter, d->handleRadius, KoPathPoint::Node);
        painter.restore();
    }
    painter.save();
    KoShape::applyConversion(painter, converter);
    canvas()->snapGuide()->paint(painter, converter);
    painter.restore();
}

void KoCreatePathTool::paintPath(KoPathShape& pathShape, QPainter &painter, const KoViewConverter &converter)
{
    Q_D(KoCreatePathTool);
    painter.setTransform(pathShape.absoluteTransformation(&converter) * painter.transform());
    painter.save();

    KoShapePaintingContext paintContext; //FIXME
    pathShape.paint(painter, converter, paintContext);
    painter.restore();
    if (pathShape.stroke())
    {
        painter.save();
        pathShape.stroke()->paint(d->shape, painter, converter);
        painter.restore();
    }
}

void KoCreatePathTool::mousePressEvent(KoPointerEvent *event)
{
    Q_D(KoCreatePathTool);

    //Right click removes last point
    if (event->button() == Qt::RightButton)
    {
        removeLastPoint();
        return;
    }

    const bool isOverFirstPoint = d->shape &&
                                  handleGrabRect(d->firstPoint->point()).contains(event->point);
    bool haveCloseModifier = (listeningToModifiers() && (event->modifiers() & Qt::ShiftModifier));

    if ((event->button() == Qt::LeftButton) && haveCloseModifier && !isOverFirstPoint)
    {
        endPathWithoutLastPoint();
        return;
    }

    d->finishAfterThisPoint = false;

    if (pathStarted())
    {
        if (isOverFirstPoint)
        {
            d->activePoint->setPoint(d->firstPoint->point());
            canvas()->updateCanvas(d->shape->boundingRect());
            canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());

            if (haveCloseModifier)
            {
                d->shape->closeMerge();
                // we are closing the path, so reset the existing start path point
                d->existingStartPoint = 0;
                // finish path
                endPath();
            }
            else
            {
                // the path shape will get closed when the user releases
                // the mouse button
                d->finishAfterThisPoint = true;
            }
        }
        else
        {
            canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());

            QPointF point = canvas()->snapGuide()->snap(event->point, event->modifiers());

            // check whether we hit an start/end node of an existing path
            d->existingEndPoint = d->endPointAtPosition(point);
            if (d->existingEndPoint.isValid() && d->existingEndPoint != d->existingStartPoint)
            {
                point = d->existingEndPoint.path->shapeToDocument(d->existingEndPoint.point->point());
                d->activePoint->setPoint(point);
                // finish path
                endPath();
            }
            else
            {
                d->activePoint->setPoint(point);
                canvas()->updateCanvas(d->shape->boundingRect());
                canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());
            }
        }
    }
    else
    {
        KoPathShape *pathShape = new KoPathShape();
        d->shape=pathShape;
        pathShape->setShapeId(KoPathShapeId);

        KoShapeStroke *stroke = new KoShapeStroke(canvas()->resourceManager()->activeStroke());
        stroke->setColor(canvas()->resourceManager()->foregroundColor().toQColor());

        pathShape->setStroke(stroke);
        canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());
        QPointF point = canvas()->snapGuide()->snap(event->point, event->modifiers());

        // check whether we hit an start/end node of an existing path
        d->existingStartPoint = d->endPointAtPosition(point);
        if (d->existingStartPoint.isValid())
        {
            point = d->existingStartPoint.path->shapeToDocument(d->existingStartPoint.point->point());
        }
        d->activePoint = pathShape->moveTo(point);
        d->firstPoint = d->activePoint;
        canvas()->updateCanvas(handlePaintRect(point));
        canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());

        canvas()->snapGuide()->setEditedShape(pathShape);

        d->angleSnapStrategy = new AngleSnapStrategy(d->angleSnappingDelta, d->angleSnapStatus);
        canvas()->snapGuide()->addCustomSnapStrategy(d->angleSnapStrategy);
    }

    if (d->angleSnapStrategy)
    {
        d->angleSnapStrategy->setStartPoint(d->activePoint->point());
    }
}

bool KoCreatePathTool::listeningToModifiers()
{
    Q_D(KoCreatePathTool);
    return d->listeningToModifiers;
}

bool KoCreatePathTool::pathStarted()
{
    Q_D(KoCreatePathTool);
    return ((bool) d->shape);
}

void KoCreatePathTool::mouseDoubleClickEvent(KoPointerEvent *event)
{
    //remove handle
    canvas()->updateCanvas(handlePaintRect(event->point));

    endPathWithoutLastPoint();
}

void KoCreatePathTool::mouseMoveEvent(KoPointerEvent *event)
{
    Q_D(KoCreatePathTool);

    KoPathPoint *endPoint = d->endPointAtPosition(event->point);
    if (d->hoveredPoint != endPoint)
    {
        if (d->hoveredPoint)
        {
            QPointF nodePos = d->hoveredPoint->parent()->shapeToDocument(d->hoveredPoint->point());
            canvas()->updateCanvas(handlePaintRect(nodePos));
        }
        d->hoveredPoint = endPoint;
        if (d->hoveredPoint)
        {
            QPointF nodePos = d->hoveredPoint->parent()->shapeToDocument(d->hoveredPoint->point());
            canvas()->updateCanvas(handlePaintRect(nodePos));
        }
    }

    if (!pathStarted())
    {
        canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());
        canvas()->snapGuide()->snap(event->point, event->modifiers());
        canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());

        d->mouseOverFirstPoint = false;
        return;
    }

    d->mouseOverFirstPoint = handleGrabRect(d->firstPoint->point()).contains(event->point);

    canvas()->updateCanvas(d->shape->boundingRect());
    canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());
    QPointF snappedPosition = canvas()->snapGuide()->snap(event->point, event->modifiers());

    d->repaintActivePoint();
    if (event->buttons() & Qt::LeftButton)
    {
        d->pointIsDragged = true;
        QPointF offset = snappedPosition - d->activePoint->point();
        d->activePoint->setControlPoint2(d->activePoint->point() + offset);
        // pressing <alt> stops controls points moving symmetrically
        if ((event->modifiers() & Qt::AltModifier) == 0)
        {
            d->activePoint->setControlPoint1(d->activePoint->point() - offset);
        }
        d->repaintActivePoint();
    }
    else
    {
        d->activePoint->setPoint(snappedPosition);
    }

    canvas()->updateCanvas(d->shape->boundingRect());
    canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());
}

void KoCreatePathTool::mouseReleaseEvent(KoPointerEvent *event)
{
    Q_D(KoCreatePathTool);

    if (! d->shape || (event->buttons() & Qt::RightButton))
    {
        return;
    }

    d->listeningToModifiers = true; // After the first press-and-release
    d->repaintActivePoint();
    d->pointIsDragged = false;
    KoPathPoint *lastActivePoint = d->activePoint;

    if (!d->finishAfterThisPoint)
    {
        d->activePoint = d->shape->lineTo(event->point);
        canvas()->snapGuide()->setIgnoredPathPoints((QList<KoPathPoint*>()<<d->activePoint));
    }

    // apply symmetric point property if applicable
    if (lastActivePoint->activeControlPoint1() && lastActivePoint->activeControlPoint2())
    {
        QPointF diff1 = lastActivePoint->point() - lastActivePoint->controlPoint1();
        QPointF diff2 = lastActivePoint->controlPoint2() - lastActivePoint->point();
        if (qFuzzyCompare(diff1.x(), diff2.x()) && qFuzzyCompare(diff1.y(), diff2.y()))
        {
            lastActivePoint->setProperty(KoPathPoint::IsSymmetric);
        }
    }

    if (d->finishAfterThisPoint)
    {

        d->firstPoint->setControlPoint1(d->activePoint->controlPoint1());
        delete d->shape->removePoint(d->shape->pathPointIndex(d->activePoint));
        d->activePoint = d->firstPoint;
        d->shape->closeMerge();

        // we are closing the path, so reset the existing start path point
        d->existingStartPoint = 0;
        // finish path
        endPath();
    }

    if (d->angleSnapStrategy && lastActivePoint->activeControlPoint2())
    {
        d->angleSnapStrategy->deactivate();
    }
}

void KoCreatePathTool::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        emit done();
    }
    else
    {
        event->ignore();
    }
}

void KoCreatePathTool::endPath()
{
    Q_D(KoCreatePathTool);

    d->addPathShape();
}

void KoCreatePathTool::endPathWithoutLastPoint()
{
    Q_D(KoCreatePathTool);

    if (d->shape)
    {
        QRectF dirtyRect = d->shape->boundingRect();
        delete d->shape->removePoint(d->shape->pathPointIndex(d->activePoint));
        canvas()->updateCanvas(dirtyRect);

        d->addPathShape();
    }
}

void KoCreatePathTool::cancelPath()
{
    Q_D(KoCreatePathTool);

    if (d->shape)
    {
        canvas()->updateCanvas(handlePaintRect(d->firstPoint->point()));
        canvas()->updateCanvas(d->shape->boundingRect());
        d->firstPoint = 0;
        d->activePoint = 0;
    }
    d->cleanUp();
}

void KoCreatePathTool::removeLastPoint()
{
    Q_D(KoCreatePathTool);

    if ((d->shape))
    {
        KoPathPointIndex lastPointIndex = d->shape->pathPointIndex(d->activePoint);

        if (lastPointIndex.second > 1)
        {
            lastPointIndex.second--;
            delete d->shape->removePoint(lastPointIndex);

            d->hoveredPoint = 0;

            d->repaintActivePoint();
            canvas()->updateCanvas(d->shape->boundingRect());
        }
    }
}

void KoCreatePathTool::activate(ToolActivation, const QSet<KoShape*> &)
{
    Q_D(KoCreatePathTool);
    useCursor(Qt::ArrowCursor);

    // retrieve the actual global handle radius
    d->handleRadius = handleRadius();

    // reset snap guide
    canvas()->updateCanvas(canvas()->snapGuide()->boundingRect());
    canvas()->snapGuide()->reset();
}

void KoCreatePathTool::deactivate()
{
    cancelPath();
}

void KoCreatePathTool::documentResourceChanged(int key, const QVariant & res)
{
    Q_D(KoCreatePathTool);

    switch (key)
    {
        case KoDocumentResourceManager::HandleRadius:
        {
            d->handleRadius = res.toUInt();
        }
        break;
        default:
            return;
    }
}

void KoCreatePathTool::addPathShape(KoPathShape *pathShape)
{
    Q_D(KoCreatePathTool);

    KoPathShape *startShape = 0;
    KoPathShape *endShape = 0;
    pathShape->normalize();

    // check if existing start/end points are still valid
    d->existingStartPoint.validate(canvas());
    d->existingEndPoint.validate(canvas());

    pathShape->setStroke(createStroke());
    if (d->connectPaths(pathShape, d->existingStartPoint, d->existingEndPoint))
    {
        if (d->existingStartPoint.isValid())
        {
            startShape = d->existingStartPoint.path;
        }
        if (d->existingEndPoint.isValid() && d->existingEndPoint != d->existingStartPoint)
        {
            endShape = d->existingEndPoint.path;
        }
    }

    KUndo2Command *cmd = canvas()->shapeController()->addShape(pathShape);
    if (cmd)
    {
        KoSelection *selection = canvas()->shapeManager()->selection();
        selection->deselectAll();
        selection->select(pathShape);
        if (startShape)
        {
            canvas()->shapeController()->removeShape(startShape, cmd);
        }
        if (endShape && startShape != endShape)
        {
            canvas()->shapeController()->removeShape(endShape, cmd);
        }
        canvas()->addCommand(cmd);
    }
    else
    {
        canvas()->updateCanvas(pathShape->boundingRect());
        delete pathShape;
    }
}

QList<QPointer<QWidget> > KoCreatePathTool::createOptionWidgets()
{
    Q_D(KoCreatePathTool);

    QList<QPointer<QWidget> > list;

    QWidget *angleWidget = new QWidget();
    angleWidget->setObjectName("Angle Constraints");
    QGridLayout *layout = new QGridLayout(angleWidget);
    layout->addWidget(new QLabel(i18n("Angle snapping delta:"), angleWidget), 0, 0);
    QSpinBox *angleEdit = new QSpinBox(angleWidget);
    angleEdit->setValue(d->angleSnappingDelta);
    angleEdit->setRange(1, 360);
    angleEdit->setSingleStep(1);
    angleEdit->setSuffix(QChar(Qt::Key_degree));
    layout->addWidget(angleEdit, 0, 1);
    layout->addWidget(new QLabel(i18n("Activate angle snap:"), angleWidget), 1, 0);
    QCheckBox *angleSnap = new QCheckBox(angleWidget);
    angleSnap->setChecked(false);
    angleSnap->setCheckable(true);
    layout->addWidget(angleSnap, 1, 1);
    QWidget *specialSpacer = new QWidget();
    specialSpacer->setObjectName("SpecialSpacer");
    layout->addWidget(specialSpacer, 2, 1);
    angleWidget->setWindowTitle(i18n("Angle Constraints"));
    list.append(angleWidget);

    d->strokeWidget = new KoStrokeConfigWidget(0);
    d->strokeWidget->setWindowTitle(i18n("Line"));
    d->strokeWidget->setCanvas(canvas());
    d->strokeWidget->setActive(false);
    list.append(d->strokeWidget);


    connect(angleEdit, SIGNAL(valueChanged(int)), this, SLOT(angleDeltaChanged(int)));
    connect(angleSnap, SIGNAL(stateChanged(int)), this, SLOT(angleSnapChanged(int)));

    return list;
}

KoShapeStroke *KoCreatePathTool::createStroke()
{
    Q_D(KoCreatePathTool);

    KoShapeStroke *stroke = 0;
    if (d->strokeWidget)
    {
        stroke = d->strokeWidget->createShapeStroke();
    }
    return stroke;
}

//have to include this because of Q_PRIVATE_SLOT
//#include <moc_KoCreatePathTool.cpp>
