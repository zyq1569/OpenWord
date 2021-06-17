/* This file is part of the KDE project
 * SPDX-FileCopyrightText: 2006-2012 Jan Hambrecht <jaham@gmx.net>
 * SPDX-FileCopyrightText: 2006, 2007 Thorsten Zachmann <zachmann@kde.org>
 * SPDX-FileCopyrightText: 2007, 2010 Thomas Zander <zander@kde.org>
 * SPDX-FileCopyrightText: 2007 Boudewijn Rempt <boud@valdyas.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "KoPathTool.h"
#include "KoToolBase_p.h"
#include "KoPathShape_p.h"
#include "KoPathToolHandle.h"
#include "KoCanvasBase.h"
#include "KoShapeManager.h"
#include "KoDocumentResourceManager.h"
#include "KoViewConverter.h"
#include "KoSelection.h"
#include "KoPointerEvent.h"
#include "commands/KoPathPointTypeCommand.h"
#include "commands/KoPathPointInsertCommand.h"
#include "commands/KoPathPointRemoveCommand.h"
#include "commands/KoPathSegmentTypeCommand.h"
#include "commands/KoPathBreakAtPointCommand.h"
#include "commands/KoPathSegmentBreakCommand.h"
#include "commands/KoParameterToPathCommand.h"
#include "commands/KoSubpathJoinCommand.h"
#include "commands/KoPathPointMergeCommand.h"
#include "KoParameterShape.h"
#include "KoPathPoint.h"
#include "KoPathPointRubberSelectStrategy.h"
#include "KoPathSegmentChangeStrategy.h"
#include "KoPathConnectionPointStrategy.h"
#include "KoParameterChangeStrategy.h"
#include "PathToolOptionWidget.h"
#include "KoConnectionShape.h"
#include "KoSnapGuide.h"
#include "KoShapeController.h"

#include <KoIcon.h>

#include <QAction>
#include <FlakeDebug.h>
#include <klocalizedstring.h>
#include <QPainter>
#include <QPainterPath>
#include <QBitmap>
#include <QTabWidget>

#include <math.h>

static const unsigned char needle_bits[] = {
    0x00, 0x00, 0x10, 0x00, 0x20, 0x00, 0x60, 0x00, 0xc0, 0x00, 0xc0, 0x01,
    0x80, 0x03, 0x80, 0x07, 0x00, 0x0f, 0x00, 0x1f, 0x00, 0x3e, 0x00, 0x7e,
    0x00, 0x7c, 0x00, 0x1c, 0x00, 0x18, 0x00, 0x00
};

static const unsigned char needle_move_bits[] = {
    0x00, 0x00, 0x10, 0x00, 0x20, 0x00, 0x60, 0x00, 0xc0, 0x00, 0xc0, 0x01,
    0x80, 0x03, 0x80, 0x07, 0x10, 0x0f, 0x38, 0x1f, 0x54, 0x3e, 0xfe, 0x7e,
    0x54, 0x7c, 0x38, 0x1c, 0x10, 0x18, 0x00, 0x00
};

// helper function to calculate the squared distance between two points
qreal squaredDistance(const QPointF& p1, const QPointF &p2)
{
    qreal dx = p1.x()-p2.x();
    qreal dy = p1.y()-p2.y();
    return dx*dx + dy*dy;
}

struct KoPathTool::PathSegment {
    PathSegment()
        : path(0), segmentStart(0), positionOnSegment(0)
    {
    }

    bool isValid() {
        return  path && segmentStart;
    }

    KoPathShape *path;
    KoPathPoint *segmentStart;
    qreal positionOnSegment;
};

KoPathTool::KoPathTool(KoCanvasBase *canvas)
        : KoToolBase(canvas)
        , m_pointSelection(this)
        , m_activeHandle(0)
        , m_handleRadius(3)
        , m_activeSegment(0)
        , m_currentStrategy(0)
{
    QActionGroup *points = new QActionGroup(this);
    // m_pointTypeGroup->setExclusive(true);
    m_actionPathPointCorner = new QAction(koIcon("node-type-cusp"), i18n("Corner point"), this);
    addAction("pathpoint-corner", m_actionPathPointCorner);
    m_actionPathPointCorner->setData(KoPathPointTypeCommand::Corner);
    points->addAction(m_actionPathPointCorner);

    m_actionPathPointSmooth = new QAction(koIcon("node-type-smooth"), i18n("Smooth point"), this);
    addAction("pathpoint-smooth", m_actionPathPointSmooth);
    m_actionPathPointSmooth->setData(KoPathPointTypeCommand::Smooth);
    points->addAction(m_actionPathPointSmooth);

    m_actionPathPointSymmetric = new QAction(koIcon("node-type-symmetric"), i18n("Symmetric Point"), this);
    addAction("pathpoint-symmetric", m_actionPathPointSymmetric);
    m_actionPathPointSymmetric->setData(KoPathPointTypeCommand::Symmetric);
    points->addAction(m_actionPathPointSymmetric);

    m_actionCurvePoint = new QAction(koIcon("format-node-curve"), i18n("Make curve point"), this);
    addAction("pathpoint-curve", m_actionCurvePoint);
    connect(m_actionCurvePoint, &QAction::triggered, this, &KoPathTool::pointToCurve);

    m_actionLinePoint = new QAction(koIcon("format-node-line"), i18n("Make line point"), this);
    addAction("pathpoint-line", m_actionLinePoint);
    connect(m_actionLinePoint, &QAction::triggered, this, &KoPathTool::pointToLine);

    m_actionLineSegment = new QAction(koIcon("format-segment-line"), i18n("Segment to Line"), this);
    m_actionLineSegment->setShortcut(Qt::Key_F);
    addAction("pathsegment-line", m_actionLineSegment);
    connect(m_actionLineSegment, &QAction::triggered, this, &KoPathTool::segmentToLine);

    m_actionCurveSegment = new QAction(koIcon("format-segment-curve"), i18n("Segment to Curve"), this);
    m_actionCurveSegment->setShortcut(Qt::Key_C);
    addAction("pathsegment-curve", m_actionCurveSegment);
    connect(m_actionCurveSegment, &QAction::triggered, this, &KoPathTool::segmentToCurve);

    m_actionAddPoint = new QAction(koIcon("format-insert-node"), i18n("Insert point"), this);
    addAction("pathpoint-insert", m_actionAddPoint);
    m_actionAddPoint->setShortcut(Qt::Key_Insert);
    connect(m_actionAddPoint, &QAction::triggered, this, &KoPathTool::insertPoints);

    m_actionRemovePoint = new QAction(koIcon("format-remove-node"), i18n("Remove point"), this);
    m_actionRemovePoint->setShortcut(Qt::Key_Backspace);
    addAction("pathpoint-remove", m_actionRemovePoint);
    connect(m_actionRemovePoint, &QAction::triggered, this, &KoPathTool::removePoints);

    m_actionBreakPoint = new QAction(koIcon("format-break-node"), i18n("Break at point"), this);
    addAction("path-break-point", m_actionBreakPoint);
    connect(m_actionBreakPoint, &QAction::triggered, this, &KoPathTool::breakAtPoint);

    m_actionBreakSegment = new QAction(koIcon("format-disconnect-node"), i18n("Break at segment"), this);
    addAction("path-break-segment", m_actionBreakSegment);
    connect(m_actionBreakSegment, &QAction::triggered, this, &KoPathTool::breakAtSegment);

    m_actionJoinSegment = new QAction(koIcon("format-connect-node"), i18n("Join with segment"), this);
    m_actionJoinSegment->setShortcut(Qt::Key_J);
    addAction("pathpoint-join", m_actionJoinSegment);
    connect(m_actionJoinSegment, &QAction::triggered, this, &KoPathTool::joinPoints);

    m_actionMergePoints = new QAction(koIcon("format-join-node"), i18n("Merge points"), this);
    addAction("pathpoint-merge", m_actionMergePoints);
    connect(m_actionMergePoints, &QAction::triggered, this, &KoPathTool::mergePoints);

    m_actionConvertToPath = new QAction(koIcon("format-convert-to-path"), i18n("To Path"), this);
    m_actionConvertToPath->setShortcut(Qt::Key_P);
    addAction("convert-to-path", m_actionConvertToPath);
    connect(m_actionConvertToPath, &QAction::triggered, this, &KoPathTool::convertToPath);

    connect(points, &QActionGroup::triggered, this, &KoPathTool::pointTypeChanged);
    connect(&m_pointSelection, &KoPathToolSelection::selectionChanged, this, &KoPathTool::pointSelectionChanged);

    QBitmap b = QBitmap::fromData(QSize(16, 16), needle_bits);
    QBitmap m = b.createHeuristicMask(false);

    m_selectCursor = QCursor(b, m, 2, 0);

    b = QBitmap::fromData(QSize(16, 16), needle_move_bits);
    m = b.createHeuristicMask(false);

    m_moveCursor = QCursor(b, m, 2, 0);
}

KoPathTool::~KoPathTool()
{
    delete m_activeHandle;
    delete m_activeSegment;
    delete m_currentStrategy;
}

QList<QPointer<QWidget> >  KoPathTool::createOptionWidgets()
{
    QList<QPointer<QWidget> > list;

    PathToolOptionWidget * toolOptions = new PathToolOptionWidget(this);
    connect(this, &KoPathTool::typeChanged, toolOptions, &PathToolOptionWidget::setSelectionType);
    updateOptionsWidget();
    toolOptions->setWindowTitle(i18n("Line/Curve"));
    list.append(toolOptions);

    return list;
}

void KoPathTool::pointTypeChanged(QAction *type)
{
    Q_D(KoToolBase);
    if (m_pointSelection.hasSelection()) {
        QList<KoPathPointData> selectedPoints = m_pointSelection.selectedPointsData();
        QList<KoPathPointData> pointToChange;

        QList<KoPathPointData>::const_iterator it(selectedPoints.constBegin());
        for (; it != selectedPoints.constEnd(); ++it) {
            KoPathPoint *point = it->pathShape->pointByIndex(it->pointIndex);
            if (point) {
                if (point->activeControlPoint1() && point->activeControlPoint2()) {
                    pointToChange.append(*it);
                }
            }
        }

        if (!pointToChange.isEmpty()) {
            KoPathPointTypeCommand *cmd = new KoPathPointTypeCommand(pointToChange,
                    static_cast<KoPathPointTypeCommand::PointType>(type->data().toInt()));
            d->canvas->addCommand(cmd);
            updateActions();
        }
    }
}

void KoPathTool::insertPoints()
{
    Q_D(KoToolBase);
    if (m_pointSelection.size() > 1) {
        QList<KoPathPointData> segments(m_pointSelection.selectedSegmentsData());
        if (!segments.isEmpty()) {
            KoPathPointInsertCommand *cmd = new KoPathPointInsertCommand(segments, 0.5);
            d->canvas->addCommand(cmd);

            foreach (KoPathPoint * p, cmd->insertedPoints()) {
                m_pointSelection.add(p, false);
            }
            updateActions();
        }
    }
}

void KoPathTool::removePoints()
{
    Q_D(KoToolBase);
    // TODO finish current action or should this not possible during actions???
    if (m_pointSelection.size() > 0) {
        KUndo2Command *cmd = KoPathPointRemoveCommand::createCommand(m_pointSelection.selectedPointsData(), d->canvas->shapeController());
        PointHandle *pointHandle = dynamic_cast<PointHandle*>(m_activeHandle);
        if (pointHandle && m_pointSelection.contains(pointHandle->activePoint())) {
            delete m_activeHandle;
            m_activeHandle = 0;
        }
        m_pointSelection.clear();
        d->canvas->addCommand(cmd);
    }
}

void KoPathTool::pointToLine()
{
    Q_D(KoToolBase);
    if (m_pointSelection.hasSelection()) {
        QList<KoPathPointData> selectedPoints = m_pointSelection.selectedPointsData();
        QList<KoPathPointData> pointToChange;

        QList<KoPathPointData>::const_iterator it(selectedPoints.constBegin());
        for (; it != selectedPoints.constEnd(); ++it) {
            KoPathPoint *point = it->pathShape->pointByIndex(it->pointIndex);
            if (point && (point->activeControlPoint1() || point->activeControlPoint2()))
                pointToChange.append(*it);
        }

        if (! pointToChange.isEmpty()) {
            d->canvas->addCommand(new KoPathPointTypeCommand(pointToChange, KoPathPointTypeCommand::Line));
            updateActions();
        }
    }
}

void KoPathTool::pointToCurve()
{
    Q_D(KoToolBase);
    if (m_pointSelection.hasSelection()) {
        QList<KoPathPointData> selectedPoints = m_pointSelection.selectedPointsData();
        QList<KoPathPointData> pointToChange;

        QList<KoPathPointData>::const_iterator it(selectedPoints.constBegin());
        for (; it != selectedPoints.constEnd(); ++it) {
            KoPathPoint *point = it->pathShape->pointByIndex(it->pointIndex);
            if (point && (! point->activeControlPoint1() || ! point->activeControlPoint2()))
                pointToChange.append(*it);
        }

        if (! pointToChange.isEmpty()) {
            d->canvas->addCommand(new KoPathPointTypeCommand(pointToChange, KoPathPointTypeCommand::Curve));
            updateActions();
        }
    }
}

void KoPathTool::segmentToLine()
{
    Q_D(KoToolBase);
    if (m_pointSelection.size() > 1) {
        QList<KoPathPointData> segments(m_pointSelection.selectedSegmentsData());
        if (segments.size() > 0) {
            d->canvas->addCommand(new KoPathSegmentTypeCommand(segments, KoPathSegmentTypeCommand::Line));
            updateActions();
        }
    }
}

void KoPathTool::segmentToCurve()
{
    Q_D(KoToolBase);
    if (m_pointSelection.size() > 1) {
        QList<KoPathPointData> segments(m_pointSelection.selectedSegmentsData());
        if (segments.size() > 0) {
            d->canvas->addCommand(new KoPathSegmentTypeCommand(segments, KoPathSegmentTypeCommand::Curve));
            updateActions();
        }
    }
}

void KoPathTool::convertToPath()
{
    Q_D(KoToolBase);
    QList<KoParameterShape*> shapesToConvert;
    foreach(KoShape *shape, m_pointSelection.selectedShapes()) {
        KoParameterShape * parameterShape = dynamic_cast<KoParameterShape*>(shape);
        if (parameterShape && parameterShape->isParametricShape())
            shapesToConvert.append(parameterShape);
    }
    if (shapesToConvert.count())
        d->canvas->addCommand(new KoParameterToPathCommand(shapesToConvert));
    updateOptionsWidget();
}

void KoPathTool::joinPoints()
{
    Q_D(KoToolBase);
    if (m_pointSelection.objectCount() == 1 && m_pointSelection.size() == 2) {
        QList<KoPathPointData> pd(m_pointSelection.selectedPointsData());
        const KoPathPointData & pd1 = pd.at(0);
        const KoPathPointData & pd2 = pd.at(1);
        KoPathShape * pathShape = pd1.pathShape;
        if (!pathShape->isClosedSubpath(pd1.pointIndex.first) &&
                (pd1.pointIndex.second == 0 ||
                 pd1.pointIndex.second == pathShape->subpathPointCount(pd1.pointIndex.first) - 1) &&
                !pathShape->isClosedSubpath(pd2.pointIndex.first) &&
                (pd2.pointIndex.second == 0 ||
                 pd2.pointIndex.second == pathShape->subpathPointCount(pd2.pointIndex.first) - 1)) {
            KoSubpathJoinCommand *cmd = new KoSubpathJoinCommand(pd1, pd2);
            d->canvas->addCommand(cmd);
        }
        updateActions();
    }
}

void KoPathTool::mergePoints()
{
    Q_D(KoToolBase);
    if (m_pointSelection.objectCount() != 1 || m_pointSelection.size() != 2)
        return;

    QList<KoPathPointData> pointData = m_pointSelection.selectedPointsData();
    const KoPathPointData & pd1 = pointData.at(0);
    const KoPathPointData & pd2 = pointData.at(1);
    const KoPathPointIndex & index1 = pd1.pointIndex;
    const KoPathPointIndex & index2 = pd2.pointIndex;

    KoPathShape * path = pd1.pathShape;

    // check if subpaths are already closed
    if (path->isClosedSubpath(index1.first) || path->isClosedSubpath(index2.first))
        return;
    // check if first point is an endpoint
    if (index1.second != 0 && index1.second != path->subpathPointCount(index1.first)-1)
        return;
    // check if second point is an endpoint
    if (index2.second != 0 && index2.second != path->subpathPointCount(index2.first)-1)
        return;

    // now we can start merging the endpoints
    KoPathPointMergeCommand *cmd = new KoPathPointMergeCommand(pd1, pd2);
    d->canvas->addCommand(cmd);
    updateActions();
}

void KoPathTool::breakAtPoint()
{
    Q_D(KoToolBase);
    if (m_pointSelection.hasSelection()) {
        d->canvas->addCommand(new KoPathBreakAtPointCommand(m_pointSelection.selectedPointsData()));
        updateActions();
    }
}

void KoPathTool::breakAtSegment()
{
    Q_D(KoToolBase);
    // only try to break a segment when 2 points of the same object are selected
    if (m_pointSelection.objectCount() == 1 && m_pointSelection.size() == 2) {
        QList<KoPathPointData> segments(m_pointSelection.selectedSegmentsData());
        if (segments.size() == 1) {
            d->canvas->addCommand(new KoPathSegmentBreakCommand(segments.at(0)));
            updateActions();
        }
    }
}

void KoPathTool::paint(QPainter &painter, const KoViewConverter &converter)
{
    Q_D(KoToolBase);
    painter.setRenderHint(QPainter::Antialiasing, true);
    // use different colors so that it is also visible on a background of the same color
    painter.setBrush(Qt::white);   //TODO make configurable
    painter.setPen(QPen(Qt::blue, 0));

    foreach(KoPathShape *shape, m_pointSelection.selectedShapes()) {
        painter.save();
        painter.setTransform(shape->absoluteTransformation(&converter) * painter.transform());

        KoParameterShape * parameterShape = dynamic_cast<KoParameterShape*>(shape);
        if (parameterShape && parameterShape->isParametricShape()) {
            parameterShape->paintHandles(painter, converter, m_handleRadius);
        } else {
            shape->paintPoints(painter, converter, m_handleRadius);
        }

        painter.restore();
    }

    if (m_currentStrategy) {
        painter.save();
        m_currentStrategy->paint(painter, converter);
        painter.restore();
    }

    painter.setBrush(Qt::green);   // TODO make color configurable
    painter.setPen(QPen(Qt::blue, 0));

    m_pointSelection.paint(painter, converter);

    painter.setBrush(Qt::red);   // TODO make color configurable
    painter.setPen(QPen(Qt::blue, 0));

    if (m_activeHandle) {
        if (m_activeHandle->check(m_pointSelection.selectedShapes())) {
            m_activeHandle->paint(painter, converter);
        } else {
            delete m_activeHandle;
            m_activeHandle = 0;
        }
    }

    if (m_currentStrategy) {
        painter.save();
        KoShape::applyConversion(painter, converter);
        d->canvas->snapGuide()->paint(painter, converter);
        painter.restore();
    }
}

void KoPathTool::repaintDecorations()
{
    foreach(KoShape *shape, m_pointSelection.selectedShapes()) {
        repaint(shape->boundingRect());
    }

    m_pointSelection.repaint();
    updateOptionsWidget();
}

void KoPathTool::mousePressEvent(KoPointerEvent *event)
{
    // we are moving if we hit a point and use the left mouse button
    event->ignore();
    if (m_activeHandle) {
        m_currentStrategy = m_activeHandle->handleMousePress(event);
        event->accept();
    } else {
        if (event->button() & Qt::LeftButton) {

            // check if we hit a path segment
            if (m_activeSegment && m_activeSegment->isValid()) {
                KoPathPointIndex index = m_activeSegment->path->pathPointIndex(m_activeSegment->segmentStart);
                KoPathPointData data(m_activeSegment->path, index);
                m_currentStrategy = new KoPathSegmentChangeStrategy(this, event->point, data, m_activeSegment->positionOnSegment);
                event->accept();
                delete m_activeSegment;
                m_activeSegment = 0;
            } else {
                if ((event->modifiers() & Qt::ControlModifier) == 0) {
                    m_pointSelection.clear();
                }
                // start rubberband selection
                Q_ASSERT(m_currentStrategy == 0);
                m_currentStrategy = new KoPathPointRubberSelectStrategy(this, event->point);
                event->accept();
            }
        }
    }
}

void KoPathTool::mouseMoveEvent(KoPointerEvent *event)
{
    if (event->button() & Qt::RightButton)
        return;

    if (m_currentStrategy) {
        m_lastPoint = event->point;
        m_currentStrategy->handleMouseMove(event->point, event->modifiers());

        // repaint new handle positions
        m_pointSelection.repaint();
        if (m_activeHandle)
            m_activeHandle->repaint();
        return;
    }

    delete m_activeSegment;
    m_activeSegment = 0;

    foreach(KoPathShape *shape, m_pointSelection.selectedShapes()) {
        QRectF roi = handleGrabRect(shape->documentToShape(event->point));
        KoParameterShape * parameterShape = dynamic_cast<KoParameterShape*>(shape);
        if (parameterShape && parameterShape->isParametricShape()) {
            int handleId = parameterShape->handleIdAt(roi);
            if (handleId != -1) {
                useCursor(m_moveCursor);
                emit statusTextChanged(i18n("Drag to move handle."));
                if (m_activeHandle)
                    m_activeHandle->repaint();
                delete m_activeHandle;

                if (KoConnectionShape * connectionShape = dynamic_cast<KoConnectionShape*>(parameterShape)) {
                    //qDebug() << "handleId" << handleId;
                    m_activeHandle = new ConnectionHandle(this, connectionShape, handleId);
                    m_activeHandle->repaint();
                    return;
                } else {
                    //qDebug() << "handleId" << handleId;
                    m_activeHandle = new ParameterHandle(this, parameterShape, handleId);
                    m_activeHandle->repaint();
                    return;
                }
            }

        } else {
            QList<KoPathPoint*> points = shape->pointsAt(roi);
            if (! points.empty()) {
                // find the nearest control point from all points within the roi
                KoPathPoint * bestPoint = 0;
                KoPathPoint::PointType bestPointType = KoPathPoint::Node;
                qreal minDistance = HUGE_VAL;
                foreach(KoPathPoint *p, points) {
                    // the node point must be hit if the point is not selected yet
                    if (! m_pointSelection.contains(p) && ! roi.contains(p->point()))
                        continue;

                    // check for the control points first as otherwise it is no longer
                    // possible to change the control points when they are the same as the point
                    if (p->activeControlPoint1() && roi.contains(p->controlPoint1())) {
                        qreal dist = squaredDistance(roi.center(), p->controlPoint1());
                        if (dist < minDistance) {
                            bestPoint = p;
                            bestPointType = KoPathPoint::ControlPoint1;
                            minDistance = dist;
                        }
                    }

                    if (p->activeControlPoint2() && roi.contains(p->controlPoint2())) {
                        qreal dist = squaredDistance(roi.center(), p->controlPoint2());
                        if (dist < minDistance) {
                            bestPoint = p;
                            bestPointType = KoPathPoint::ControlPoint2;
                            minDistance = dist;
                        }
                    }

                    // check the node point at last
                    qreal dist = squaredDistance(roi.center(), p->point());
                    if (dist < minDistance) {
                        bestPoint = p;
                        bestPointType = KoPathPoint::Node;
                        minDistance = dist;
                    }
                }

                if (! bestPoint)
                    return;

                useCursor(m_moveCursor);
                if (bestPointType == KoPathPoint::Node)
                    emit statusTextChanged(i18n("Drag to move point. Shift click to change point type."));
                else
                    emit statusTextChanged(i18n("Drag to move control point."));

                PointHandle *prev = dynamic_cast<PointHandle*>(m_activeHandle);
                if (prev && prev->activePoint() == bestPoint && prev->activePointType() == bestPointType)
                    return; // no change;

                if (m_activeHandle)
                    m_activeHandle->repaint();
                delete m_activeHandle;
                m_activeHandle = new PointHandle(this, bestPoint, bestPointType);
                m_activeHandle->repaint();
                return;
            }
        }
    }

    useCursor(m_selectCursor);
    if (m_activeHandle)
        m_activeHandle->repaint();
    delete m_activeHandle;
    m_activeHandle = 0;

    PathSegment *hoveredSegment = segmentAtPoint(event->point);
    if(hoveredSegment) {
        useCursor(Qt::PointingHandCursor);
        emit statusTextChanged(i18n("Drag to change curve directly. Double click to insert new path point."));
        m_activeSegment = hoveredSegment;
    } else {
        uint selectedPointCount = m_pointSelection.size();
        if (selectedPointCount == 0)
            emit statusTextChanged("");
        else if (selectedPointCount == 1)
            emit statusTextChanged(i18n("Press B to break path at selected point."));
        else
            emit statusTextChanged(i18n("Press B to break path at selected segments."));
    }
}

void KoPathTool::mouseReleaseEvent(KoPointerEvent *event)
{
    Q_D(KoToolBase);
    if (m_currentStrategy) {
        const bool hadNoSelection = !m_pointSelection.hasSelection();
        m_currentStrategy->finishInteraction(event->modifiers());
        KUndo2Command *command = m_currentStrategy->createCommand();
        if (command)
            d->canvas->addCommand(command);
        if (hadNoSelection && dynamic_cast<KoPathPointRubberSelectStrategy*>(m_currentStrategy)
                && !m_pointSelection.hasSelection()) {
            // the click didn't do anything at all. Allow it to be used by others.
            event->ignore();
        }
        delete m_currentStrategy;
        m_currentStrategy = 0;

        if (m_pointSelection.selectedShapes().count() == 1)
            emit pathChanged(m_pointSelection.selectedShapes().constFirst());
        else
            emit pathChanged(0);
    }
}

void KoPathTool::keyPressEvent(QKeyEvent *event)
{
    Q_D(KoToolBase);
    if (m_currentStrategy) {
        switch (event->key()) {
        case Qt::Key_Control:
        case Qt::Key_Alt:
        case Qt::Key_Shift:
        case Qt::Key_Meta:
            if (! event->isAutoRepeat()) {
                m_currentStrategy->handleMouseMove(m_lastPoint, event->modifiers());
            }
            break;
        case Qt::Key_Escape:
            m_currentStrategy->cancelInteraction();
            delete m_currentStrategy;
            m_currentStrategy = 0;
            break;
        default:
            event->ignore();
            return;
        }
    } else {
        switch (event->key()) {
// TODO move these to the actions in the constructor.
        case Qt::Key_I: {
            KoDocumentResourceManager *rm = d->canvas->shapeController()->resourceManager();
            int handleRadius = rm->handleRadius();
            if (event->modifiers() & Qt::ControlModifier)
                handleRadius--;
            else
                handleRadius++;
            rm->setHandleRadius(handleRadius);
            break;
        }
#ifndef NDEBUG
        case Qt::Key_D:
            if (m_pointSelection.objectCount() == 1) {
                QList<KoPathPointData> selectedPoints = m_pointSelection.selectedPointsData();
                KoPathShapePrivate *p = static_cast<KoPathShapePrivate*>(selectedPoints[0].pathShape->priv());
                p->debugPath();
            }
            break;
#endif
        case Qt::Key_B:
            if (m_pointSelection.size() == 1)
                breakAtPoint();
            else if (m_pointSelection.size() >= 2)
                breakAtSegment();
            break;
        default:
            event->ignore();
            return;
        }
    }
    event->accept();
}

void KoPathTool::keyReleaseEvent(QKeyEvent *event)
{
    if (m_currentStrategy) {
        switch (event->key()) {
        case Qt::Key_Control:
        case Qt::Key_Alt:
        case Qt::Key_Shift:
        case Qt::Key_Meta:
            if (! event->isAutoRepeat()) {
                m_currentStrategy->handleMouseMove(m_lastPoint, Qt::NoModifier);
            }
            break;
        default:
            break;
        }
    }
    event->accept();
}

void KoPathTool::mouseDoubleClickEvent(KoPointerEvent *event)
{
    Q_D(KoToolBase);
    event->ignore();

    // check if we are doing something else at the moment
    if (m_currentStrategy)
        return;

    PathSegment *s = segmentAtPoint(event->point);
    if (!s)
        return;

    if (s->isValid()) {
        QList<KoPathPointData> segments;
        segments.append(KoPathPointData(s->path, s->path->pathPointIndex(s->segmentStart)));
        KoPathPointInsertCommand *cmd = new KoPathPointInsertCommand(segments, s->positionOnSegment);
        d->canvas->addCommand(cmd);

        foreach (KoPathPoint * p, cmd->insertedPoints()) {
            m_pointSelection.add(p, false);
        }
        updateActions();
        event->accept();
    }
    delete s;
}

KoPathTool::PathSegment* KoPathTool::segmentAtPoint(const QPointF &point)
{
    Q_D(KoToolBase);
    // TODO: use global click proximity once added to the canvas resource provider
    const int clickProximity = 5;

    // convert click proximity to point using the current zoom level
    QPointF clickOffset = d->canvas->viewConverter()->viewToDocument(QPointF(clickProximity, clickProximity));
    // the max allowed distance from a segment
    const qreal maxSquaredDistance = clickOffset.x()*clickOffset.x();

    PathSegment *segment = new PathSegment;

    foreach(KoPathShape *shape, m_pointSelection.selectedShapes()) {
        KoParameterShape * parameterShape = dynamic_cast<KoParameterShape*>(shape);
        if (parameterShape && parameterShape->isParametricShape())
            continue;

        // convert document point to shape coordinates
        QPointF p = shape->documentToShape(point);
        // our region of interest, i.e. a region around our mouse position
        QRectF roi(p - clickOffset, p + clickOffset);

        qreal minSqaredDistance = HUGE_VAL;
        // check all segments of this shape which intersect the region of interest
        QList<KoPathSegment> segments = shape->segmentsAt(roi);
        foreach (const KoPathSegment &s, segments) {
            qreal nearestPointParam = s.nearestPoint(p);
            QPointF nearestPoint = s.pointAt(nearestPointParam);
            QPointF diff = p - nearestPoint;
            qreal squaredDistance = diff.x()*diff.x() + diff.y()*diff.y();
            // are we within the allowed distance ?
            if (squaredDistance > maxSquaredDistance)
                continue;
            // are we closer to the last closest point ?
            if (squaredDistance < minSqaredDistance) {
                segment->path = shape;
                segment->segmentStart = s.first();
                segment->positionOnSegment = nearestPointParam;
            }
        }
    }

    if (!segment->isValid()) {
        delete segment;
        segment = 0;
    }

    return segment;
}

void KoPathTool::activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes)
{
    Q_D(KoToolBase);
    Q_UNUSED(toolActivation);
    // retrieve the actual global handle radius
    m_handleRadius = handleRadius();
    d->canvas->snapGuide()->reset();

    repaintDecorations();
    QList<KoPathShape*> selectedShapes;
    foreach(KoShape *shape, shapes) {
        KoPathShape *pathShape = dynamic_cast<KoPathShape*>(shape);

        if (shape->isEditable() && pathShape) {
            // as the tool is just in activation repaintDecorations does not yet get called
            // so we need to use repaint of the tool and it is only needed to repaint the
            // current canvas
            repaint(pathShape->boundingRect());
            selectedShapes.append(pathShape);
        }
    }
    if (selectedShapes.isEmpty()) {
        emit done();
        return;
    }
    m_pointSelection.setSelectedShapes(selectedShapes);
    useCursor(m_selectCursor);
    connect(d->canvas->shapeManager()->selection(), &KoSelection::selectionChanged, this, QOverload<>::of(&KoPathTool::activate));
    updateOptionsWidget();
    updateActions();
}

void KoPathTool::activate()
{
    Q_D(KoToolBase);
    QSet<KoShape*> shapes;
    foreach(KoShape *shape, d->canvas->shapeManager()->selection()->selectedShapes()) {
        QSet<KoShape*> delegates = shape->toolDelegates();
        if (delegates.isEmpty()) {
            shapes << shape;
        } else {
            shapes += delegates;
        }
    }
    activate(DefaultActivation, shapes);
}

void KoPathTool::updateOptionsWidget()
{
    PathToolOptionWidget::Types type;
    QList<KoPathShape*> selectedShapes = m_pointSelection.selectedShapes();
    foreach(KoPathShape *shape, selectedShapes) {
        KoParameterShape * parameterShape = dynamic_cast<KoParameterShape*>(shape);
        type |= parameterShape && parameterShape->isParametricShape() ?
                PathToolOptionWidget::ParametricShape : PathToolOptionWidget::PlainPath;
    }
    if (selectedShapes.count() == 1)
        emit pathChanged(selectedShapes.first());
    else
        emit pathChanged(0);
    emit typeChanged(type);
}

void KoPathTool::updateActions()
{
    const bool hasPointsSelected = m_pointSelection.hasSelection();
    m_actionPathPointCorner->setEnabled(hasPointsSelected);
    m_actionPathPointSmooth->setEnabled(hasPointsSelected);
    m_actionPathPointSymmetric->setEnabled(hasPointsSelected);
    m_actionRemovePoint->setEnabled(hasPointsSelected);
    m_actionBreakPoint->setEnabled(hasPointsSelected);
    m_actionCurvePoint->setEnabled(hasPointsSelected);
    m_actionLinePoint->setEnabled(hasPointsSelected);

    bool hasSegmentsSelected = false;
    if (hasPointsSelected && m_pointSelection.size() > 1)
        hasSegmentsSelected = !m_pointSelection.selectedSegmentsData().isEmpty();
    m_actionAddPoint->setEnabled(hasSegmentsSelected);
    m_actionLineSegment->setEnabled(hasSegmentsSelected);
    m_actionCurveSegment->setEnabled(hasSegmentsSelected);

    const uint objectCount = m_pointSelection.objectCount();
    const uint pointCount = m_pointSelection.size();
    m_actionBreakSegment->setEnabled(objectCount == 1 && pointCount == 2);
    m_actionJoinSegment->setEnabled(objectCount == 1 && pointCount == 2);
    m_actionMergePoints->setEnabled(objectCount == 1 && pointCount == 2);
}

void KoPathTool::deactivate()
{
    Q_D(KoToolBase);
    disconnect(d->canvas->shapeManager()->selection(), &KoSelection::selectionChanged, this, QOverload<>::of(&KoPathTool::activate));
    m_pointSelection.clear();
    m_pointSelection.setSelectedShapes(QList<KoPathShape*>());
    delete m_activeHandle;
    m_activeHandle = 0;
    delete m_activeSegment;
    m_activeSegment = 0;
    delete m_currentStrategy;
    m_currentStrategy = 0;
    d->canvas->snapGuide()->reset();
}

void KoPathTool::documentResourceChanged(int key, const QVariant & res)
{
    if (key == KoDocumentResourceManager::HandleRadius) {
        int oldHandleRadius = m_handleRadius;

        m_handleRadius = res.toUInt();

        // repaint with the bigger of old and new handle radius
        int maxRadius = qMax(m_handleRadius, oldHandleRadius);
        foreach(KoPathShape *shape, m_pointSelection.selectedShapes()) {
            QRectF controlPointRect = shape->absoluteTransformation(nullptr).map(shape->outline()).controlPointRect();
            repaint(controlPointRect.adjusted(-maxRadius, -maxRadius, maxRadius, maxRadius));
        }
    }
}

void KoPathTool::pointSelectionChanged()
{
    Q_D(KoToolBase);
    updateActions();
    d->canvas->snapGuide()->setIgnoredPathPoints(m_pointSelection.selectedPoints().values());
    emit selectionChanged(m_pointSelection.hasSelection());
}

void KoPathTool::repaint(const QRectF &repaintRect)
{
    Q_D(KoToolBase);
    //debugFlake <<"KoPathTool::repaint(" << repaintRect <<")" << m_handleRadius;
    // widen border to take antialiasing into account
    qreal radius = m_handleRadius + 1;
    d->canvas->updateCanvas(repaintRect.adjusted(-radius, -radius, radius, radius));
}

void KoPathTool::deleteSelection()
{
    removePoints();
}

KoToolSelection * KoPathTool::selection()
{
    return &m_pointSelection;
}
