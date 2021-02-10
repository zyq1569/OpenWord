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

#ifndef PATHCONNECTIONPOINT_H
#define PATHCONNECTIONPOINT_H

#include "KoPathPoint.h"

#include "KoCanvasBase.h"

#include "KoPathPoint.h"
#include "KoPathPointData.h"
#include "KoPathPointMergeCommand.h"

/// Small helper to keep track of a path point and its parent path shape
struct PathConnectionPoint {
    PathConnectionPoint();
    // reset state to invalid
    void reset();
    PathConnectionPoint& operator =(KoPathPoint * pathPoint);
    bool operator != (const PathConnectionPoint &rhs) const;
    bool operator == (const PathConnectionPoint &rhs) const;
    bool isValid() const;
    // checks if the path and point are still valid
    void validate(KoCanvasBase *canvas);
    KoPathShape * path;
    KoPathPoint * point;
};

#endif // PATHCONNECTIONPOINT_H
