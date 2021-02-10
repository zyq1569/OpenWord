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

#ifndef ANGLESNAPSTRATEGY_H
#define ANGLESNAPSTRATEGY_H

#include "KoSnapStrategy.h"
#include <QPainterPath>
class AngleSnapStrategy : public KoSnapStrategy
{
public:
    explicit AngleSnapStrategy( qreal angleStep, bool active);

    void setStartPoint(const QPointF &startPoint);

    void setAngleStep(qreal angleStep);

    bool snap(const QPointF &mousePosition, KoSnapProxy * proxy, qreal maxSnapDistance) override;

    QPainterPath decoration(const KoViewConverter &converter) const override;

    void deactivate();

    void activate();

private:
    QPointF m_startPoint;
    qreal m_angleStep;
    bool m_active;
};



#endif // ANGLESNAPSTRATEGY_H
