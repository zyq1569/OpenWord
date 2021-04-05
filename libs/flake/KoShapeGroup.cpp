/* This file is part of the KDE project
 * Copyright (C) 2006 Thomas Zander <zander@kde.org>
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

#include "KoShapeGroup.h"
#include "KoShapeContainerModel.h"
#include "KoShapeContainer_p.h"
#include "KoShapeLayer.h"
#include "SimpleShapeContainerModel.h"
#include "KoShapeSavingContext.h"
#include "KoShapeLoadingContext.h"
#include "KoXmlWriter.h"
#include "KoXmlReader.h"
#include "KoShapeRegistry.h"
#include "KoShapeStrokeModel.h"
#include "KoShapeShadow.h"
#include "KoInsets.h"

#include <FlakeDebug.h>

#include <QPainter>

#include <algorithm>

class ShapeGroupContainerModel : public SimpleShapeContainerModel
{
public:
    ShapeGroupContainerModel(KoShapeGroup *group) : m_group(group) {}
    ~ShapeGroupContainerModel() override {}

    void add(KoShape *child) override
    {
        SimpleShapeContainerModel::add(child);
        m_group->invalidateSizeCache();
    }

    void remove(KoShape *child) override
    {
        SimpleShapeContainerModel::remove(child);
        m_group->invalidateSizeCache();
    }

    void childChanged(KoShape *shape, KoShape::ChangeType type) override
    {
        SimpleShapeContainerModel::childChanged(shape, type);
        //debugFlake << type;
        switch (type)
        {
            case KoShape::PositionChanged:
            case KoShape::RotationChanged:
            case KoShape::ScaleChanged:
            case KoShape::ShearChanged:
            case KoShape::SizeChanged:
            case KoShape::GenericMatrixChange:
            case KoShape::ParameterChanged:
            case KoShape::ClipPathChanged :
                m_group->invalidateSizeCache();
                break;
            default:
                break;
        }
    }

private: // members
    KoShapeGroup * m_group;
};

class KoShapeGroupPrivate : public KoShapeContainerPrivate
{
public:
    KoShapeGroupPrivate(KoShapeGroup *q)
        : KoShapeContainerPrivate(q)
    {
        model = new ShapeGroupContainerModel(q);
    }

    ~KoShapeGroupPrivate() override
    {
    }

    mutable bool sizeCached;
};

KoShapeGroup::KoShapeGroup()
    : KoShapeContainer(*(new KoShapeGroupPrivate(this)))
{
    setSize(QSizeF(0, 0));
}

KoShapeGroup::~KoShapeGroup()
{
}

void KoShapeGroup::paintComponent(QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &)
{
    Q_UNUSED(painter);
    Q_UNUSED(converter);
}

bool KoShapeGroup::hitTest(const QPointF &position) const
{
    Q_UNUSED(position);
    return false;
}

QSizeF KoShapeGroup::size() const
{
    Q_D(const KoShapeGroup);
    //debugFlake << "size" << d->size;
    if (!d->sizeCached)
    {
        QRectF bound;
        foreach(KoShape *shape, shapes())
        {
            if (bound.isEmpty())
            {
                bound = shape->transformation().mapRect(shape->outlineRect());
            }
            else
            {
                bound |= shape->transformation().mapRect(shape->outlineRect());
            }
        }
        d->size = bound.size();
        d->sizeCached = true;
        debugFlake << "recalculated size" << d->size;
    }

    return d->size;
}

QRectF KoShapeGroup::boundingRect() const
{
    bool first = true;
    QRectF groupBound;
    foreach(KoShape* shape, shapes())
    {
        if (first)
        {
            groupBound = shape->boundingRect();
            first = false;
        }
        else
        {
            groupBound = groupBound.united(shape->boundingRect());
        }
    }

    if (shadow())
    {
        KoInsets insets;
        shadow()->insets(insets);
        groupBound.adjust(-insets.left, -insets.top, insets.right, insets.bottom);
    }
    return groupBound;
}

void KoShapeGroup::saveOdf(KoShapeSavingContext & context) const
{
    context.xmlWriter().startElement("draw:g");
    saveOdfAttributes(context, (OdfMandatories ^ (OdfLayer | OdfZIndex)) | OdfAdditionalAttributes);
    context.xmlWriter().addAttributePt("svg:y", position().y());

    QList<KoShape*> shapes = this->shapes();
    std::sort(shapes.begin(), shapes.end(), KoShape::compareShapeZIndex);

    foreach(KoShape* shape, shapes)
    {
        shape->saveOdf(context);
    }

    saveOdfCommonChildElements(context);
    context.xmlWriter().endElement();
}

bool KoShapeGroup::loadOdf(const KoXmlElement & element, KoShapeLoadingContext &context)
{
    Q_D(KoShapeGroup);
    loadOdfAttributes(element, context, OdfMandatories | OdfStyle | OdfAdditionalAttributes | OdfCommonChildElements);

    KoXmlElement child;
    QHash<KoShapeLayer*, int> usedLayers;
    forEachElement(child, element)
    {
        KoShape * shape = KoShapeRegistry::instance()->createShapeFromOdf(child, context);
        if (shape)
        {
            KoShapeLayer *layer = dynamic_cast<KoShapeLayer*>(shape->parent());
            if (layer)
            {
                usedLayers[layer]++;
            }
            addShape(shape);
        }
    }
    KoShapeLayer *parent = 0;
    int maxUseCount = 0;
    // find most used layer and use this as parent for the group
    for (QHash<KoShapeLayer*, int>::const_iterator it(usedLayers.constBegin()); it != usedLayers.constEnd(); ++it)
    {
        if (it.value() > maxUseCount)
        {
            maxUseCount = it.value();
            parent = it.key();
        }
    }
    setParent(parent);

    QRectF bound;
    bool boundInitialized = false;
    foreach(KoShape * shape, shapes())
    {
        if (! boundInitialized)
        {
            bound = shape->boundingRect();
            boundInitialized = true;
        }
        else
        {
            bound = bound.united(shape->boundingRect());
        }
    }

    setSize(bound.size());
    d->sizeCached = true;
    setPosition(bound.topLeft());

    foreach(KoShape * shape, shapes())
    {
        shape->setAbsolutePosition(shape->absolutePosition() - bound.topLeft());
    }

    return true;
}

void KoShapeGroup::shapeChanged(ChangeType type, KoShape *shape)
{
    Q_UNUSED(shape);
    KoShapeContainer::shapeChanged(type, shape);
    switch (type)
    {
        case KoShape::StrokeChanged:
        {
            KoShapeStrokeModel *str = stroke();
            if (str)
            {
                if (str->deref())
                {
                    delete str;
                }
                setStroke(0);
            }
            break;
        }
        default:
            break;
    }
}

void KoShapeGroup::invalidateSizeCache()
{
    Q_D(KoShapeGroup);
    d->sizeCached = false;
}

