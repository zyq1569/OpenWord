/* This file is part of the KDE project
 * Copyright (C) 2006-2007 Thomas Zander <zander@kde.org>
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

#ifndef SHAPERESIZESTRATEGY_H
#define SHAPERESIZESTRATEGY_H

#include <KoInteractionStrategy.h>
#include <KoFlake.h>

#include <QPointF>
#include <QList>
#include <QMap>
#include <QTransform>

class KoToolBase;
class KoShape;

class ChartResizeStrategy;

/**
 * A strategy for the KoInteractionTool.
 * This strategy is invoked when the user starts a resize of a selection of objects,
 * the strategy will then resize the objects interactively and provide a command afterwards.
 */
class ShapeResizeStrategy : public KoInteractionStrategy
{
public:
    /**
     * Constructor
     */
    ShapeResizeStrategy(KoToolBase *tool, const QPointF &clicked, KoFlake::SelectionHandle direction);
    ~ShapeResizeStrategy() override;

    void handleMouseMove(const QPointF &mouseLocation, Qt::KeyboardModifiers modifiers) override;
    KUndo2Command* createCommand() override;
    void finishInteraction(Qt::KeyboardModifiers modifiers) override;
    void paint( QPainter &painter, const KoViewConverter &converter) override;
    void handleCustomEvent( KoPointerEvent * event ) override;
private:
    void resizeBy( const QPointF &center, qreal zoomX, qreal zoomY );

    QPointF m_start;
    QVector<QPointF> m_startPositions;
    QVector<QSizeF> m_startSizes;
    bool m_top, m_left, m_bottom, m_right;
    QTransform m_unwindMatrix, m_windMatrix;
    QSizeF m_initialSize;
    QPointF m_initialPosition;
    QTransform m_scaleMatrix;
    QVector<QTransform> m_oldTransforms;
    QVector<QTransform> m_transformations;
    QPointF m_lastScale;
    QList<KoShape*> m_selectedShapes;
    QMap<KoShape*, ChartResizeStrategy*> m_chartShapes;
};

#endif

