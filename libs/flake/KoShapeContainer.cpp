/* This file is part of the KDE project
 * SPDX-FileCopyrightText: 2006-2010 Thomas Zander <zander@kde.org>
 * SPDX-FileCopyrightText: 2007 Jan Hambrecht <jaham@gmx.net>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#include "KoShapeContainer.h"
#include "KoShapeContainer_p.h"
#include "KoShapeContainerModel.h"
#include "KoShapeStrokeModel.h"
#include "KoShapeContainerDefaultModel.h"
#include "KoShapeSavingContext.h"

#include <QPointF>
#include <QPainter>
#include <QPainterPath>

#include <algorithm>

KoShapeContainerPrivate::KoShapeContainerPrivate(KoShapeContainer *q)
    : KoShapePrivate(q),
      model(0)
{
}

KoShapeContainerPrivate::~KoShapeContainerPrivate()
{
    delete model;
}

KoShapeContainer::KoShapeContainer(KoShapeContainerModel *model)
    : KoShape(*(new KoShapeContainerPrivate(this)))
{
    Q_D(KoShapeContainer);
    d->model = model;
}

KoShapeContainer::KoShapeContainer(KoShapeContainerPrivate &dd)
    : KoShape(dd)
{
}

KoShapeContainer::~KoShapeContainer()
{
    Q_D(KoShapeContainer);
    if (d->model)
    {
        foreach(KoShape *shape, d->model->shapes())
        {
            delete shape;
        }
    }
}

void KoShapeContainer::addShape(KoShape *shape)
{
    Q_D(KoShapeContainer);
    Q_ASSERT(shape);
    if (shape->parent() == this && shapes().contains(shape))
    {
        return;
    }
    // TODO add a method to create a default model depending on the shape container
    if (d->model == 0)
    {
        d->model = new KoShapeContainerDefaultModel();
    }
    if (shape->parent() && shape->parent() != this)
    {
        shape->parent()->removeShape(shape);
    }
    d->model->add(shape);
    shape->setParent(this);
}

void KoShapeContainer::removeShape(KoShape *shape)
{
    Q_D(KoShapeContainer);
    Q_ASSERT(shape);
    if (d->model == 0)
    {
        return;
    }
    d->model->remove(shape);
    shape->setParent(0);

    KoShapeContainer * grandparent = parent();
    if (grandparent)
    {
        grandparent->model()->childChanged(this, KoShape::ChildChanged);
    }
}

void KoShapeContainer::removeAllShapes()
{
    Q_D(KoShapeContainer);
    if (d->model == 0)
    {
        return;
    }
    for(int i = d->model->shapes().count() - 1; i >= 0; --i)
    {
        KoShape *shape = d->model->shapes().at(i);
        d->model->remove(shape);
        shape->setParent(0);
    }

    KoShapeContainer * grandparent = parent();
    if (grandparent)
    {
        grandparent->model()->childChanged(this, KoShape::ChildChanged);
    }
}

int  KoShapeContainer::shapeCount() const
{
    Q_D(const KoShapeContainer);
    if (d->model == 0)
    {
        return 0;
    }
    return d->model->count();
}

bool KoShapeContainer::isChildLocked(const KoShape *child) const
{
    Q_D(const KoShapeContainer);
    if (d->model == 0)
    {
        return false;
    }
    return d->model->isChildLocked(child);
}

KoShape::AllowedInteractions KoShapeContainer::allowedInteractions(const KoShape *child) const
{
    Q_D(const KoShapeContainer);
    if (!d->model)
    {
        return child->allowedInteractions(false);
    }
    return d->model->allowedInteractions(child);
}

void KoShapeContainer::setClipped(const KoShape *child, bool clipping)
{
    Q_D(KoShapeContainer);
    if (d->model == 0)
    {
        return;
    }
    d->model->setClipped(child, clipping);
}

void KoShapeContainer::setInheritsTransform(const KoShape *shape, bool inherit)
{
    Q_D(KoShapeContainer);
    if (d->model == 0)
    {
        return;
    }
    d->model->setInheritsTransform(shape, inherit);
}

bool KoShapeContainer::inheritsTransform(const KoShape *shape) const
{
    Q_D(const KoShapeContainer);
    if (d->model == 0)
    {
        return false;
    }
    return d->model->inheritsTransform(shape);
}

void KoShapeContainer::paint(QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &paintcontext)
{
    Q_D(KoShapeContainer);
    painter.save();
    paintComponent(painter, converter, paintcontext);
    painter.restore();
    if (d->model == 0 || d->model->count() == 0)
    {
        return;
    }

    QList<KoShape*> sortedObjects = d->model->shapes();
    std::sort(sortedObjects.begin(), sortedObjects.end(), KoShape::compareShapeZIndex);

    // Do the following to revert the absolute transformation of the container
    // that is re-applied in shape->absoluteTransformation() later on. The transformation matrix
    // of the container has already been applied once before this function is called.
    QTransform baseMatrix = absoluteTransformation(&converter).inverted() * painter.transform();

    // clip the children to the parent outline.
    QTransform m;
    qreal zoomX, zoomY;
    converter.zoom(&zoomX, &zoomY);
    m.scale(zoomX, zoomY);
    painter.setClipPath(m.map(outline()), Qt::IntersectClip);

    QRectF toPaintRect = converter.viewToDocument(painter.clipRegion().boundingRect());
    toPaintRect = transform().mapRect(toPaintRect);
    // We'll use this clipRect to see if our child shapes lie within it.
    // Because shape->boundingRect() uses absoluteTransformation(0) we'll
    // use that as well to have the same (absolute) reference transformation
    // of our and the child's bounding boxes.
    QTransform absTrans = absoluteTransformation(0);
    QRectF clipRect = absTrans.map(outline()).boundingRect();


    foreach(KoShape *shape, sortedObjects)
    {
        //debugFlake <<"KoShapeContainer::painting shape:" << shape->shapeId() <<"," << shape->boundingRect();
        if (!shape->isVisible())
        {
            continue;
        }
        if (!isClipped(shape))  // the shapeManager will have to draw those, or else we can't do clipRects
        {
            continue;
        }
        // don't try to draw a child shape that is not in the clipping rect of the painter.
        if (!clipRect.intersects(shape->boundingRect()))

        {
            continue;
        }

        painter.save();
        painter.setTransform(shape->absoluteTransformation(&converter) * baseMatrix);
        shape->paint(painter, converter, paintcontext);
        painter.restore();
        if (shape->stroke())
        {
            painter.save();
            painter.setTransform(shape->absoluteTransformation(&converter) * baseMatrix);
            shape->stroke()->paint(shape, painter, converter);
            painter.restore();
        }
    }
}

void KoShapeContainer::shapeChanged(ChangeType type, KoShape* shape)
{
    Q_UNUSED(shape);
    Q_D(KoShapeContainer);
    if (d->model == 0)
    {
        return;
    }
    if (!(type == RotationChanged || type == ScaleChanged || type == ShearChanged
            || type == SizeChanged || type == PositionChanged || type == GenericMatrixChange))
    {
        return;
    }
    d->model->containerChanged(this, type);
    foreach(KoShape *shape, d->model->shapes())
    {
        shape->notifyChanged();
    }
}

bool KoShapeContainer::isClipped(const KoShape *child) const
{
    Q_D(const KoShapeContainer);
    if (d->model == 0) // throw exception??
    {
        return false;
    }
    return d->model->isClipped(child);
}

void KoShapeContainer::update() const
{
    Q_D(const KoShapeContainer);
    KoShape::update();
    if (d->model)
        foreach(KoShape *shape, d->model->shapes())
        {
            shape->update();
        }
}

QList<KoShape*> KoShapeContainer::shapes() const
{
    Q_D(const KoShapeContainer);
    if (d->model == 0)
    {
        return QList<KoShape*>();
    }

    return d->model->shapes();
}

KoShapeContainerModel *KoShapeContainer::model() const
{
    Q_D(const KoShapeContainer);
    return d->model;
}
