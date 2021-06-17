/* This file is part of the KDE project
 * SPDX-FileCopyrightText: 2007 Boudewijn Rempt <boud@kde.org>
 * SPDX-FileCopyrightText: 2007, 2009 Thorsten Zachmann <zachmann@kde.org>
 * SPDX-FileCopyrightText: 2007, 2009, 2010 Jan Hambrecht <jaham@gmx.net>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "KoConnectionShape.h"
#include "KoConnectionShape_p.h"

#include "KoViewConverter.h"
#include "KoShapeLoadingContext.h"
#include "KoShapeSavingContext.h"
#include "KoConnectionShapeLoadingUpdater.h"
#include "KoPathShapeLoader.h"
#include "KoPathPoint.h"
#include "KoShapeBackground.h"
#include <KoXmlReader.h>
#include <KoXmlWriter.h>
#include <KoXmlNS.h>
#include <KoUnit.h>
#include <QPainter>
#include <QPainterPath>

#include <FlakeDebug.h>

KoConnectionShapePrivate::KoConnectionShapePrivate(KoConnectionShape *q)
    : KoParameterShapePrivate(q),
      shape1(0),
      shape2(0),
      connectionPointId1(-1),
      connectionPointId2(-1),
      connectionType(KoConnectionShape::Standard),
      forceUpdate(false),
      hasCustomPath(false)
{
}

QPointF KoConnectionShapePrivate::escapeDirection(int handleId) const
{
    Q_Q(const KoConnectionShape);
    QPointF direction;
    if (handleConnected(handleId))
    {
        KoShape *attachedShape = handleId == KoConnectionShape::StartHandle ? shape1 : shape2;
        int connectionPointId = handleId == KoConnectionShape::StartHandle ? connectionPointId1 : connectionPointId2;
        KoConnectionPoint::EscapeDirection ed = attachedShape->connectionPoint(connectionPointId).escapeDirection;
        if (ed == KoConnectionPoint::AllDirections)
        {
            QPointF handlePoint = q->shapeToDocument(handles[handleId]);
            QPointF centerPoint = attachedShape->absolutePosition(KoFlake::CenteredPosition);

            /*
             * Determine the best escape direction from the position of the handle point
             * and the position and orientation of the attached shape.
             * The idea is to define 4 sectors, one for each edge of the attached shape.
             * Each sector starts at the center point of the attached shape and has it
             * left and right edge going through the two points which define the edge.
             * Then we check which sector contains our handle point, for which we can
             * simply calculate the corresponding direction which is orthogonal to the
             * corresponding bounding box edge.
             * From that we derive the escape direction from looking at the main coordinate
             * of the orthogonal direction.
             */
            // define our edge points in the right order
            const KoFlake::Position corners[4] =
            {
                KoFlake::BottomRightCorner,
                KoFlake::BottomLeftCorner,
                KoFlake::TopLeftCorner,
                KoFlake::TopRightCorner
            };

            QPointF vHandle = handlePoint-centerPoint;
            for (int i = 0; i < 4; ++i)
            {
                // first point of bounding box edge
                QPointF p1 = attachedShape->absolutePosition(corners[i]);
                // second point of bounding box edge
                QPointF p2 = attachedShape->absolutePosition(corners[(i+1)%4]);
                // check on which side of the first sector edge our second sector edge is
                const qreal c0 = crossProd(p1-centerPoint, p2-centerPoint);
                // check on which side of the first sector edge our handle point is
                const qreal c1 = crossProd(p1-centerPoint, vHandle);
                // second egde and handle point must be on the same side of first edge
                if ((c0 < 0 && c1 > 0) || (c0 > 0 && c1 < 0))
                {
                    continue;
                }
                // check on which side of the handle point our second sector edge is
                const qreal c2 = crossProd(vHandle, p2-centerPoint);
                // second edge must be on the same side of the handle point as on first edge
                if ((c0 < 0 && c2 > 0) || (c0 > 0 && c2 < 0))
                {
                    continue;
                }
                // now we found the correct edge
                QPointF vDir = 0.5 *(p1+p2) - centerPoint;
                // look at coordinate with the greatest absolute value
                // and construct our escape direction accordingly
                const qreal xabs = qAbs<qreal>(vDir.x());
                const qreal yabs = qAbs<qreal>(vDir.y());
                if (xabs > yabs)
                {
                    direction.rx() = vDir.x() > 0 ? 1.0 : -1.0;
                    direction.ry() = 0.0;
                }
                else
                {
                    direction.rx() = 0.0;
                    direction.ry() = vDir.y() > 0 ? 1.0 : -1.0;
                }
                break;
            }
        }
        else if (ed == KoConnectionPoint::HorizontalDirections)
        {
            QPointF handlePoint = q->shapeToDocument(handles[handleId]);
            QPointF centerPoint = attachedShape->absolutePosition(KoFlake::CenteredPosition);
            // use horizontal direction pointing away from center point
            if (handlePoint.x() < centerPoint.x())
            {
                direction = QPointF(-1.0, 0.0);
            }
            else
            {
                direction = QPointF(1.0, 0.0);
            }
        }
        else if (ed == KoConnectionPoint::VerticalDirections)
        {
            QPointF handlePoint = q->shapeToDocument(handles[handleId]);
            QPointF centerPoint = attachedShape->absolutePosition(KoFlake::CenteredPosition);
            // use vertical direction pointing away from center point
            if (handlePoint.y() < centerPoint.y())
            {
                direction = QPointF(0.0, -1.0);
            }
            else
            {
                direction = QPointF(0.0, 1.0);
            }
        }
        else if (ed == KoConnectionPoint::LeftDirection)
        {
            direction = QPointF(-1.0, 0.0);
        }
        else if (ed == KoConnectionPoint::RightDirection)
        {
            direction = QPointF(1.0, 0.0);
        }
        else if (ed == KoConnectionPoint::UpDirection)
        {
            direction = QPointF(0.0, -1.0);
        }
        else if (ed == KoConnectionPoint::DownDirection)
        {
            direction = QPointF(0.0, 1.0);
        }

        // transform escape direction by using our own transformation matrix
        QTransform invMatrix = q->absoluteTransformation(0).inverted();
        direction = invMatrix.map(direction) - invMatrix.map(QPointF());
        direction /= sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    }

    return direction;
}

bool KoConnectionShapePrivate::intersects(const QPointF &p1, const QPointF &d1, const QPointF &p2, const QPointF &d2, QPointF &isect)
{
    qreal sp1 = scalarProd(d1, p2 - p1);
    if (sp1 < 0.0)
    {
        return false;
    }

    qreal sp2 = scalarProd(d2, p1 - p2);
    if (sp2 < 0.0)
    {
        return false;
    }

    // use cross product to check if rays intersects at all
    qreal cp = crossProd(d1, d2);
    if (cp == 0.0)
    {
        // rays are parallel or coincident
        if (p1.x() == p2.x() && d1.x() == 0.0 && d1.y() != d2.y())
        {
            // vertical, coincident
            isect = 0.5 * (p1 + p2);
        }
        else if (p1.y() == p2.y() && d1.y() == 0.0 && d1.x() != d2.x())
        {
            // horizontal, coincident
            isect = 0.5 * (p1 + p2);
        }
        else
        {
            return false;
        }
    }
    else
    {
        // they are intersecting normally
        isect = p1 + sp1 * d1;
    }

    return true;
}

QPointF KoConnectionShapePrivate::perpendicularDirection(const QPointF &p1, const QPointF &d1, const QPointF &p2)
{
    QPointF perpendicular(d1.y(), -d1.x());
    qreal sp = scalarProd(perpendicular, p2 - p1);
    if (sp < 0.0)
    {
        perpendicular *= -1.0;
    }

    return perpendicular;
}

void KoConnectionShapePrivate::normalPath(const qreal MinimumEscapeLength)
{
    // Clear the path to build it again.
    path.clear();
    path.append(handles[KoConnectionShape::StartHandle]);

    QVector<QPointF> edges1;
    QVector<QPointF> edges2;

    QPointF direction1 = escapeDirection(KoConnectionShape::StartHandle);
    QPointF direction2 = escapeDirection(KoConnectionShape::EndHandle);

    QPointF edgePoint1 = handles[KoConnectionShape::StartHandle] + MinimumEscapeLength * direction1;
    QPointF edgePoint2 = handles[KoConnectionShape::EndHandle] + MinimumEscapeLength * direction2;

    edges1.append(edgePoint1);
    edges2.prepend(edgePoint2);

    if (handleConnected(KoConnectionShape::StartHandle) && handleConnected(KoConnectionShape::EndHandle))
    {
        QPointF intersection;
        bool connected = false;
        do
        {
            // first check if directions from current edge points intersect
            if (intersects(edgePoint1, direction1, edgePoint2, direction2, intersection))
            {
                // directions intersect, we have another edge point and be done
                edges1.append(intersection);
                break;
            }

            // check if we are going toward the other handle
            qreal sp = scalarProd(direction1, edgePoint2 - edgePoint1);
            if (sp >= 0.0)
            {
                // if we are having the same direction, go all the way toward
                // the other handle, else only go half the way
                if (direction1 == direction2)
                {
                    edgePoint1 += sp * direction1;
                }
                else
                {
                    edgePoint1 += 0.5 * sp * direction1;
                }
                edges1.append(edgePoint1);
                // switch direction
                direction1 = perpendicularDirection(edgePoint1, direction1, edgePoint2);
            }
            else
            {
                // we are not going into the same direction, so switch direction
                direction1 = perpendicularDirection(edgePoint1, direction1, edgePoint2);
            }
        }
        while (! connected);
    }

    path.append(edges1);
    path.append(edges2);

    path.append(handles[KoConnectionShape::EndHandle]);
}

qreal KoConnectionShapePrivate::scalarProd(const QPointF &v1, const QPointF &v2) const
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}

qreal KoConnectionShapePrivate::crossProd(const QPointF &v1, const QPointF &v2) const
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}

bool KoConnectionShapePrivate::handleConnected(int handleId) const
{
    if (handleId == KoConnectionShape::StartHandle && shape1 && connectionPointId1 >= 0)
    {
        return true;
    }
    if (handleId == KoConnectionShape::EndHandle && shape2 && connectionPointId2 >= 0)
    {
        return true;
    }

    return false;
}

void KoConnectionShape::updateConnections()
{
    Q_D(KoConnectionShape);
    bool updateHandles = false;

    if (d->handleConnected(StartHandle))
    {
        if (d->shape1->hasConnectionPoint(d->connectionPointId1))
        {
            // map connection point into our shape coordinates
            QPointF p = documentToShape(d->shape1->absoluteTransformation(0).map(d->shape1->connectionPoint(d->connectionPointId1).position));
            if (d->handles[StartHandle] != p)
            {
                d->handles[StartHandle] = p;
                updateHandles = true;
            }
        }
    }
    if (d->handleConnected(EndHandle))
    {
        if (d->shape2->hasConnectionPoint(d->connectionPointId2))
        {
            // map connection point into our shape coordinates
            QPointF p = documentToShape(d->shape2->absoluteTransformation(0).map(d->shape2->connectionPoint(d->connectionPointId2).position));
            if (d->handles[EndHandle] != p)
            {
                d->handles[EndHandle] = p;
                updateHandles = true;
            }
        }
    }

    if (updateHandles || d->forceUpdate)
    {
        update(); // ugly, for repainting the connection we just changed
        updatePath(QSizeF());
        update(); // ugly, for repainting the connection we just changed
        d->forceUpdate = false;
    }
}

KoConnectionShape::KoConnectionShape()
    : KoParameterShape(*(new KoConnectionShapePrivate(this)))
{
    Q_D(KoConnectionShape);
    d->handles.push_back(QPointF(0, 0));
    d->handles.push_back(QPointF(140, 140));

    moveTo(d->handles[StartHandle]);
    lineTo(d->handles[EndHandle]);

    updatePath(QSizeF(140, 140));

    clearConnectionPoints();
}

KoConnectionShape::~KoConnectionShape()
{
    Q_D(KoConnectionShape);
    if (d->shape1)
    {
        d->shape1->removeDependee(this);
    }
    if (d->shape2)
    {
        d->shape2->removeDependee(this);
    }
}

void KoConnectionShape::saveOdf(KoShapeSavingContext & context) const
{
    Q_D(const KoConnectionShape);
    context.xmlWriter().startElement("draw:connector");
    saveOdfAttributes(context, OdfMandatories | OdfAdditionalAttributes);

    switch (d->connectionType)
    {
        case Lines:
            context.xmlWriter().addAttribute("draw:type", "lines");
            break;
        case Straight:
            context.xmlWriter().addAttribute("draw:type", "line");
            break;
        case Curve:
            context.xmlWriter().addAttribute("draw:type", "curve");
            break;
        default:
            context.xmlWriter().addAttribute("draw:type", "standard");
            break;
    }

    if (d->shape1)
    {
        context.xmlWriter().addAttribute("draw:start-shape", context.xmlid(d->shape1, "shape", KoElementReference::Counter).toString());
        context.xmlWriter().addAttribute("draw:start-glue-point", d->connectionPointId1);
    }
    else
    {
        QPointF p(shapeToDocument(d->handles[StartHandle]) * context.shapeOffset(this));
        context.xmlWriter().addAttributePt("svg:x1", p.x());
        context.xmlWriter().addAttributePt("svg:y1", p.y());
    }
    if (d->shape2)
    {
        context.xmlWriter().addAttribute("draw:end-shape", context.xmlid(d->shape2, "shape", KoElementReference::Counter).toString());
        context.xmlWriter().addAttribute("draw:end-glue-point", d->connectionPointId2);
    }
    else
    {
        QPointF p(shapeToDocument(d->handles[EndHandle]) * context.shapeOffset(this));
        context.xmlWriter().addAttributePt("svg:x2", p.x());
        context.xmlWriter().addAttributePt("svg:y2", p.y());
    }

    // write the path data
    context.xmlWriter().addAttribute("svg:d", toString());
    saveOdfAttributes(context, OdfViewbox);

    saveOdfCommonChildElements(context);
    saveText(context);

    context.xmlWriter().endElement();
}

bool KoConnectionShape::loadOdf(const KoXmlElement & element, KoShapeLoadingContext &context)
{
    Q_D(KoConnectionShape);
    loadOdfAttributes(element, context, OdfMandatories | OdfCommonChildElements | OdfAdditionalAttributes);

    QString type = element.attributeNS(KoXmlNS::draw, "type", "standard");
    if (type == "lines")
    {
        d->connectionType = Lines;
    }
    else if (type == "line")
    {
        d->connectionType = Straight;
    }
    else if (type == "curve")
    {
        d->connectionType = Curve;
    }
    else
    {
        d->connectionType = Standard;
    }

    // reset connection point indices
    d->connectionPointId1 = -1;
    d->connectionPointId2 = -1;
    // reset connected shapes
    d->shape1 = 0;
    d->shape2 = 0;

    if (element.hasAttributeNS(KoXmlNS::draw, "start-shape"))
    {
        d->connectionPointId1 = element.attributeNS(KoXmlNS::draw, "start-glue-point", QString()).toInt();
        QString shapeId1 = element.attributeNS(KoXmlNS::draw, "start-shape", QString());
        debugFlake << "references start-shape" << shapeId1 << "at glue-point" << d->connectionPointId1;
        d->shape1 = context.shapeById(shapeId1);
        if (d->shape1)
        {
            debugFlake << "start-shape was already loaded";
            d->shape1->addDependee(this);
            if (d->shape1->hasConnectionPoint(d->connectionPointId1))
            {
                debugFlake << "connecting to start-shape";
                d->handles[StartHandle] = d->shape1->absoluteTransformation(0).map(d->shape1->connectionPoint(d->connectionPointId1).position);
                debugFlake << "start handle position =" << d->handles[StartHandle];
            }
        }
        else
        {
            debugFlake << "start-shape not loaded yet, deferring connection";
            context.updateShape(shapeId1, new KoConnectionShapeLoadingUpdater(this, KoConnectionShapeLoadingUpdater::First));
        }
    }
    else
    {
        d->handles[StartHandle].setX(KoUnit::parseValue(element.attributeNS(KoXmlNS::svg, "x1", QString())));
        d->handles[StartHandle].setY(KoUnit::parseValue(element.attributeNS(KoXmlNS::svg, "y1", QString())));
    }

    if (element.hasAttributeNS(KoXmlNS::draw, "end-shape"))
    {
        d->connectionPointId2 = element.attributeNS(KoXmlNS::draw, "end-glue-point", "").toInt();
        QString shapeId2 = element.attributeNS(KoXmlNS::draw, "end-shape", "");
        debugFlake << "references end-shape " << shapeId2 << "at glue-point" << d->connectionPointId2;
        d->shape2 = context.shapeById(shapeId2);
        if (d->shape2)
        {
            debugFlake << "end-shape was already loaded";
            d->shape2->addDependee(this);
            if (d->shape2->hasConnectionPoint(d->connectionPointId2))
            {
                debugFlake << "connecting to end-shape";
                d->handles[EndHandle] = d->shape2->absoluteTransformation(0).map(d->shape2->connectionPoint(d->connectionPointId2).position);
                debugFlake << "end handle position =" << d->handles[EndHandle];
            }
        }
        else
        {
            debugFlake << "end-shape not loaded yet, deferring connection";
            context.updateShape(shapeId2, new KoConnectionShapeLoadingUpdater(this, KoConnectionShapeLoadingUpdater::Second));
        }
    }
    else
    {
        d->handles[EndHandle].setX(KoUnit::parseValue(element.attributeNS(KoXmlNS::svg, "x2", QString())));
        d->handles[EndHandle].setY(KoUnit::parseValue(element.attributeNS(KoXmlNS::svg, "y2", QString())));
    }

    QString skew = element.attributeNS(KoXmlNS::draw, "line-skew", QString());
    QStringList skewValues = skew.simplified().split(' ', QString::SkipEmptyParts);
    // TODO apply skew values once we support them

    // load the path data if there is any
    d->hasCustomPath = element.hasAttributeNS(KoXmlNS::svg, "d");
    if (d->hasCustomPath)
    {
        KoPathShapeLoader loader(this);
        loader.parseSvg(element.attributeNS(KoXmlNS::svg, "d"), true);
        if (m_subpaths.size() > 0)
        {
            QRectF viewBox = loadOdfViewbox(element);
            if (viewBox.isEmpty())
            {
                // there should be a viewBox to transform the path data
                // if there is none, use the bounding rectangle of the parsed path
                viewBox = outline().boundingRect();
            }
            // convert path to viewbox coordinates to have a bounding rect of (0,0 1x1)
            // which can later be fitted back into the target rect once we have all
            // the required information
            QTransform viewMatrix;
            viewMatrix.scale(viewBox.width() ? static_cast<qreal>(1.0) / viewBox.width() : 1.0,
                             viewBox.height() ? static_cast<qreal>(1.0) / viewBox.height() : 1.0);
            viewMatrix.translate(-viewBox.left(), -viewBox.top());
            d->map(viewMatrix);

            // trigger finishing the connections in case we have all data
            // otherwise it gets called again once the shapes we are
            // connected to are loaded
        }
        else
        {
            d->hasCustomPath = false;
        }
        finishLoadingConnection();
    }
    else
    {
        d->forceUpdate = true;
        updateConnections();
    }

    loadText(element, context);

    return true;
}

void KoConnectionShape::finishLoadingConnection()
{
    Q_D(KoConnectionShape);

    if (d->hasCustomPath)
    {
        const bool loadingFinished1 = d->connectionPointId1 >= 0 ? d->shape1 != 0 : true;
        const bool loadingFinished2 = d->connectionPointId2 >= 0 ? d->shape2 != 0 : true;
        if (loadingFinished1 && loadingFinished2)
        {
            QPointF p1, p2;
            if (d->handleConnected(StartHandle))
            {
                if (d->shape1->hasConnectionPoint(d->connectionPointId1))
                {
                    p1 = d->shape1->absoluteTransformation(0).map(d->shape1->connectionPoint(d->connectionPointId1).position);
                }
            }
            else
            {
                p1 = d->handles[StartHandle];
            }
            if (d->handleConnected(EndHandle))
            {
                if (d->shape2->hasConnectionPoint(d->connectionPointId2))
                {
                    p2 = d->shape2->absoluteTransformation(0).map(d->shape2->connectionPoint(d->connectionPointId2).position);
                }
            }
            else
            {
                p2 = d->handles[EndHandle];
            }

            QPointF relativeBegin = m_subpaths.first()->first()->point();
            QPointF relativeEnd = m_subpaths.last()->last()->point();

            QPointF diffRelative(relativeBegin - relativeEnd);
            QPointF diffAbsolute(p1 - p2);

            qreal factorX = diffRelative.x() ? diffAbsolute.x() / diffRelative.x(): 1.0;
            qreal factorY = diffRelative.y() ? diffAbsolute.y() / diffRelative.y(): 1.0;

            p1.setX(p1.x() - relativeBegin.x() * factorX);
            p1.setY(p1.y() - relativeBegin.y() * factorY);
            p2.setX(p2.x() + (1 - relativeEnd.x()) * factorX);
            p2.setY(p2.y() + (1 - relativeEnd.y()) * factorY);

            QRectF targetRect = QRectF(p1, p2).normalized();

            // transform the normalized coordinates back to our target rectangle
            QTransform viewMatrix;
            viewMatrix.translate(targetRect.x(), targetRect.y());
            viewMatrix.scale(targetRect.width(), targetRect.height());
            d->map(viewMatrix);

            // pretend we are during a forced update, so normalize()
            // will not trigger an updateConnections() call
            d->forceUpdate = true;
            normalize();
            d->forceUpdate = false;
        }
    }
    else
    {
        updateConnections();
    }
}

void KoConnectionShape::moveHandleAction(int handleId, const QPointF &point, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);
    Q_D(KoConnectionShape);

    if (handleId >= d->handles.size())
    {
        return;
    }

    d->handles[handleId] = point;
}

void KoConnectionShape::updatePath(const QSizeF &size)
{
    Q_UNUSED(size);
    Q_D(KoConnectionShape);

    clear();
    // Do not create a path when all handles point to the same point.
    bool equal = true;
    const QPointF first = d->handles.value(0);
    for (int i = 1; equal && i < d->handles.count(); ++i)
    {
        equal = d->handles[i] == first;
    }
    if (equal)
    {
        return;
    }
    const qreal MinimumEscapeLength = (qreal)20.;
    switch (d->connectionType)
    {
        case Standard:
        {
            d->normalPath(MinimumEscapeLength);
            if (d->path.count() != 0)
            {
                moveTo(d->path[0]);
                for (int index = 1; index < d->path.count(); ++index)
                {
                    lineTo(d->path[index]);
                }
            }

            break;
        }
        case Lines:
        {
            QPointF direction1 = d->escapeDirection(0);
            QPointF direction2 = d->escapeDirection(d->handles.count() - 1);
            moveTo(d->handles[StartHandle]);
            if (! direction1.isNull())
            {
                lineTo(d->handles[StartHandle] + MinimumEscapeLength * direction1);
            }
            if (! direction2.isNull())
            {
                lineTo(d->handles[EndHandle] + MinimumEscapeLength * direction2);
            }
            lineTo(d->handles[EndHandle]);
            break;
        }
        case Straight:
            moveTo(d->handles[StartHandle]);
            lineTo(d->handles[EndHandle]);
            break;
        case Curve:
            // TODO
            QPointF direction1 = d->escapeDirection(0);
            QPointF direction2 = d->escapeDirection(d->handles.count() - 1);
            moveTo(d->handles[StartHandle]);
            if (! direction1.isNull() && ! direction2.isNull())
            {
                QPointF curvePoint1 = d->handles[StartHandle] + 5.0 * MinimumEscapeLength * direction1;
                QPointF curvePoint2 = d->handles[EndHandle] + 5.0 * MinimumEscapeLength * direction2;
                curveTo(curvePoint1, curvePoint2, d->handles[EndHandle]);
            }
            else
            {
                lineTo(d->handles[EndHandle]);
            }
            break;
    }
    normalize();
}

bool KoConnectionShape::connectFirst(KoShape * shape1, int connectionPointId)
{
    Q_D(KoConnectionShape);
    // refuse to connect to a shape that depends on us (e.g. a artistic text shape)
    if (hasDependee(shape1))
    {
        return false;
    }

    if (shape1)
    {
        // check if the connection point does exist
        if (!shape1->hasConnectionPoint(connectionPointId))
        {
            return false;
        }
        // do not connect to the same connection point twice
        if (d->shape2 == shape1 && d->connectionPointId2 == connectionPointId)
        {
            return false;
        }
    }

    if (d->shape1)
    {
        d->shape1->removeDependee(this);
    }
    d->shape1 = shape1;
    if (d->shape1)
    {
        d->shape1->addDependee(this);
    }

    d->connectionPointId1 = connectionPointId;

    return true;
}

bool KoConnectionShape::connectSecond(KoShape * shape2, int connectionPointId)
{
    Q_D(KoConnectionShape);
    // refuse to connect to a shape that depends on us (e.g. a artistic text shape)
    if (hasDependee(shape2))
    {
        return false;
    }

    if (shape2)
    {
        // check if the connection point does exist
        if (!shape2->hasConnectionPoint(connectionPointId))
        {
            return false;
        }
        // do not connect to the same connection point twice
        if (d->shape1 == shape2 && d->connectionPointId1 == connectionPointId)
        {
            return false;
        }
    }

    if (d->shape2)
    {
        d->shape2->removeDependee(this);
    }
    d->shape2 = shape2;
    if (d->shape2)
    {
        d->shape2->addDependee(this);
    }

    d->connectionPointId2 = connectionPointId;

    return true;
}

KoShape *KoConnectionShape::firstShape() const
{
    Q_D(const KoConnectionShape);
    return d->shape1;
}

int KoConnectionShape::firstConnectionId() const
{
    Q_D(const KoConnectionShape);
    return d->connectionPointId1;
}

KoShape *KoConnectionShape::secondShape() const
{
    Q_D(const KoConnectionShape);
    return d->shape2;
}

int KoConnectionShape::secondConnectionId() const
{
    Q_D(const KoConnectionShape);
    return d->connectionPointId2;
}

KoConnectionShape::Type KoConnectionShape::type() const
{
    Q_D(const KoConnectionShape);
    return d->connectionType;
}

void KoConnectionShape::setType(Type connectionType)
{
    Q_D(KoConnectionShape);
    d->connectionType = connectionType;
    updatePath(size());
}

void KoConnectionShape::shapeChanged(ChangeType type, KoShape *shape)
{
    Q_D(KoConnectionShape);

    KoTosContainer::shapeChanged(type, shape);
    // check if we are during a forced update
    const bool updateIsActive = d->forceUpdate;

    switch (type)
    {
        case PositionChanged:
        case RotationChanged:
        case ShearChanged:
        case ScaleChanged:
        case GenericMatrixChange:
        case ParameterChanged:
            if (isParametricShape() && shape == 0)
            {
                d->forceUpdate = true;
            }
            break;
        case Deleted:
            if (shape != d->shape1 && shape != d->shape2)
            {
                return;
            }
            if (shape == d->shape1)
            {
                connectFirst(0, -1);
            }
            if (shape == d->shape2)
            {
                connectSecond(0, -1);
            }
            break;
        case ConnectionPointChanged:
            if (shape == d->shape1 && !shape->hasConnectionPoint(d->connectionPointId1))
            {
                connectFirst(0, -1);
            }
            else if ( shape == d->shape2 && !shape->hasConnectionPoint(d->connectionPointId2))
            {
                connectSecond(0, -1);
            }
            else
            {
                d->forceUpdate = true;
            }
            break;
        case BackgroundChanged:
        {
            // connection shape should not have a background
            QSharedPointer<KoShapeBackground> fill = background();
            if (fill)
            {
                setBackground(QSharedPointer<KoShapeBackground>(0));
            }
            return;
        }
        default:
            return;
    }

    // the connection was moved while it is connected to some other shapes
    const bool connectionChanged = !shape && (d->shape1 || d->shape2);
    // one of the connected shape has moved
    const bool connectedShapeChanged = shape && (shape == d->shape1 || shape == d->shape2);

    if (!updateIsActive && (connectionChanged || connectedShapeChanged) && isParametricShape())
    {
        updateConnections();
    }

    // reset the forced update flag
    d->forceUpdate = false;
}

QString KoConnectionShape::pathShapeId() const
{
    return KOCONNECTIONSHAPEID;
}
