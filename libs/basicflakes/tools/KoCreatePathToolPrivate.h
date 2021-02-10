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

#ifndef KOCREATEPATHTOOLPRIVATE_H
#define KOCREATEPATHTOOLPRIVATE_H

#include "KoCreatePathTool.h"
#include "KoStrokeConfigWidget.h"
#include "KoPathPoint.h"
#include "KoPathPointData.h"
#include "KoPathPointMergeCommand.h"
#include "KoCanvasBase.h"
#include "KoParameterShape.h"
#include "KoViewConverter.h"
#include "KoShapeManager.h"
#include "KoSnapStrategy.h"
#include "KoToolBase_p.h"
#include "PathConnectionPoint.h"
#include "AngleSnapStrategy.h"
//#include <QPainterPath>

#include "math.h"

inline qreal squareDistance( const QPointF &p1, const QPointF &p2)
{
    qreal dx = p1.x()-p2.x();
    qreal dy = p1.y()-p2.y();
    return dx*dx + dy*dy;
}

class KoCreatePathToolPrivate : public KoToolBasePrivate {
    KoCreatePathTool * const q;
public:
    KoCreatePathToolPrivate(KoCreatePathTool * const qq, KoCanvasBase* canvas);
    KoPathShape *shape;
    KoPathPoint *activePoint;
    KoPathPoint *firstPoint;
    int handleRadius;
    bool mouseOverFirstPoint;
    bool pointIsDragged;
    bool finishAfterThisPoint;
    PathConnectionPoint existingStartPoint; ///< an existing path point we started a new path at
    PathConnectionPoint existingEndPoint;   ///< an existing path point we finished a new path at
    KoPathPoint *hoveredPoint; ///< an existing path end point the mouse is hovering on
    bool listeningToModifiers; //  Fine tune when to begin processing modifiers at the beginning of a stroke.
    AngleSnapStrategy *angleSnapStrategy;
    int angleSnappingDelta;
    bool angleSnapStatus;
    KoStrokeConfigWidget *strokeWidget;
    void repaintActivePoint() const;
    /// returns the nearest existing path point
    KoPathPoint* endPointAtPosition( const QPointF &position ) const;
    /// Connects given path with the ones we hit when starting/finishing
    bool connectPaths( KoPathShape *pathShape, const PathConnectionPoint &pointAtStart, const PathConnectionPoint &pointAtEnd ) const;
    void addPathShape();
    void cleanUp();
    void angleDeltaChanged(int value);
    void angleSnapChanged(int angleSnap);
};

#endif // KOCREATEPATHTOOLPRIVATE_H
