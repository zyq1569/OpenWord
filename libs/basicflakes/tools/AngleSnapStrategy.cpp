#include "AngleSnapStrategy.h"

AngleSnapStrategy::AngleSnapStrategy( qreal angleStep, bool active)
    : KoSnapStrategy(KoSnapGuide::CustomSnapping), m_angleStep(angleStep), m_active(active)
{
}

void AngleSnapStrategy::setStartPoint(const QPointF &startPoint)
{
    m_startPoint = startPoint;
}

void AngleSnapStrategy::setAngleStep(qreal angleStep)
{
    m_angleStep = qAbs(angleStep);
}

bool AngleSnapStrategy::snap(const QPointF &mousePosition, KoSnapProxy * proxy, qreal maxSnapDistance)
{
    Q_UNUSED(proxy);

    if (!m_active)
        return false;

    QLineF line(m_startPoint, mousePosition);
    qreal currentAngle = line.angle();
    int prevStep = qAbs(currentAngle / m_angleStep);
    int nextStep = prevStep + 1;
    qreal prevAngle = prevStep*m_angleStep;
    qreal nextAngle = nextStep*m_angleStep;

    if (qAbs(currentAngle - prevAngle) <= qAbs(currentAngle - nextAngle)) {
        line.setAngle(prevAngle);
    } else {
        line.setAngle(nextAngle);
    }

    qreal maxSquareSnapDistance = maxSnapDistance*maxSnapDistance;
    qreal snapDistance = squareDistance(mousePosition, line.p2());
    if (snapDistance > maxSquareSnapDistance)
        return false;

    setSnappedPosition(line.p2());
    return true;
}

QPainterPath AngleSnapStrategy::decoration(const KoViewConverter &converter) const
{
    Q_UNUSED(converter);

    QPainterPath decoration;
    decoration.moveTo(m_startPoint);
    decoration.lineTo(snappedPosition());
    return decoration;
}

void AngleSnapStrategy::deactivate()
{
    m_active = false;
}

void AngleSnapStrategy::activate()
{
    m_active = true;
}
