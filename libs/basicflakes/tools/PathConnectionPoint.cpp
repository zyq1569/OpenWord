
#include "PathConnectionPoint.h"
#include "KoShapeManager.h"

PathConnectionPoint::PathConnectionPoint()
    : path(0), point(0)
{
}

// reset state to invalid
void PathConnectionPoint::reset()
{
    path = 0;
    point = 0;
}

PathConnectionPoint& PathConnectionPoint::operator =(KoPathPoint * pathPoint)
{
    if (!pathPoint || ! pathPoint->parent()) {
        reset();
    } else {
        path = pathPoint->parent();
        point = pathPoint;
    }
    return *this;
}

bool PathConnectionPoint::operator != (const PathConnectionPoint &rhs) const
{
    return rhs.path != path || rhs.point != point;
}

bool PathConnectionPoint::operator == (const PathConnectionPoint &rhs) const
{
    return rhs.path == path && rhs.point == point;
}

bool PathConnectionPoint::isValid() const
{
    return path && point;
}

// checks if the path and point are still valid
void PathConnectionPoint::validate(KoCanvasBase *canvas)
{
    // no point in validating an already invalid state
    if (!isValid()) {
        return;
    }
    // we need canvas to validate
    if (!canvas) {
        reset();
        return;
    }
    // check if path is still part of the docment
    if (!canvas->shapeManager()->shapes().contains(path)) {
        reset();
        return;
    }
    // check if point is still part of the path
    if (path->pathPointIndex(point) == KoPathPointIndex(-1,-1)) {
        reset();
        return;
    }
}

