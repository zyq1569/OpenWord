#include "KoToolBoxScrollArea_p.h"

KoToolBoxScrollArea::KoToolBoxScrollArea(KoToolBox *toolBox, QWidget *parent)
    : QScrollArea(parent)
    , m_toolBox(toolBox)
    , m_orientation(Qt::Vertical)
    , m_scrollPrev(new QToolButton(this))
    , m_scrollNext(new QToolButton(this))
{
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_toolBox->setOrientation(m_orientation);
    setWidget(m_toolBox);

    m_scrollPrev->setAutoRepeat(true);
    m_scrollPrev->setAutoFillBackground(true);
    m_scrollPrev->setFocusPolicy(Qt::NoFocus);
    connect(m_scrollPrev, &QToolButton::clicked, this, &KoToolBoxScrollArea::doScrollPrev);
    m_scrollNext->setAutoRepeat(true);
    m_scrollNext->setAutoFillBackground(true);
    m_scrollNext->setFocusPolicy(Qt::NoFocus);
    connect(m_scrollNext, &QToolButton::clicked, this, &KoToolBoxScrollArea::doScrollNext);

    QScroller *scroller = KoKineticScroller::createPreconfiguredScroller(this);
    if (!scroller) {
        QScroller::grabGesture(viewport(), QScroller::MiddleMouseButtonGesture);
        QScroller *scroller = QScroller::scroller(viewport());
        QScrollerProperties sp = scroller->scrollerProperties();

        sp.setScrollMetric(QScrollerProperties::MaximumVelocity, 0.0);
        sp.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0.1);
        sp.setScrollMetric(QScrollerProperties::OvershootDragDistanceFactor, 0.1);
        sp.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0.0);
        sp.setScrollMetric(QScrollerProperties::OvershootScrollTime, 0.4);

        scroller->setScrollerProperties(sp);
    }
    connect(scroller, SIGNAL(stateChanged(QScroller::State)), this, SLOT(slotScrollerStateChange(QScroller::State)));
}

void KoToolBoxScrollArea::setOrientation(Qt::Orientation orientation)
{
    if (orientation == m_orientation) {
        return;
    }
    m_orientation = orientation;
    m_toolBox->setOrientation(orientation);
    layoutItems();
}

Qt::Orientation KoToolBoxScrollArea::orientation() const
{
    return m_orientation;
}

QSize KoToolBoxScrollArea::minimumSizeHint() const
{
    return m_toolBox->minimumSizeHint();
}

QSize KoToolBoxScrollArea::sizeHint() const
{
    return m_toolBox->sizeHint();
}


void KoToolBoxScrollArea::slotScrollerStateChange(QScroller::State state)
{
    KoKineticScroller::updateCursor(this, state);
}


bool KoToolBoxScrollArea::event(QEvent *event)
{
    if (event->type() == QEvent::LayoutRequest) {
        // LayoutRequest can be triggered by icon changes, so resize the toolbox
        layoutItems();
        // The toolbox might have changed the sizeHint and minimumSizeHint
        updateGeometry();
    }
    return QScrollArea::event(event);
}

void KoToolBoxScrollArea::resizeEvent(QResizeEvent *event)
{
    layoutItems();
    QScrollArea::resizeEvent(event);
    updateScrollButtons();
}

void KoToolBoxScrollArea::wheelEvent(QWheelEvent *event)
{
    if (m_orientation == Qt::Vertical) {
        QApplication::sendEvent(verticalScrollBar(), event);
    } else {
        QApplication::sendEvent(horizontalScrollBar(), event);
    }
}

void KoToolBoxScrollArea::scrollContentsBy(int dx, int dy)
{
    QScrollArea::scrollContentsBy(dx, dy);
    updateScrollButtons();
}

void KoToolBoxScrollArea::doScrollPrev()
{
    if (m_orientation == Qt::Vertical) {
        verticalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepSub);
    } else {
        horizontalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepSub);
    }
}

void KoToolBoxScrollArea::doScrollNext()
{
    if (m_orientation == Qt::Vertical) {
        verticalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepAdd);
    } else {
        horizontalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepAdd);
    }
}


int KoToolBoxScrollArea::scrollButtonWidth() const
{
    QStyleOption opt;
    opt.init(this);
    return style()->pixelMetric(QStyle::PM_TabBarScrollButtonWidth, &opt, this);
}

void KoToolBoxScrollArea::layoutItems()
{
    const KoToolBoxLayout *l = m_toolBox->toolBoxLayout();
    QSize newSize = viewport()->size();
    if (m_orientation == Qt::Vertical) {
        newSize.setHeight(l->heightForWidth(newSize.width()));
    } else {
        newSize.setWidth(l->widthForHeight(newSize.height()));
    }
    m_toolBox->resize(newSize);

    updateScrollButtons();
}

void KoToolBoxScrollArea::KoToolBoxScrollArea::updateScrollButtons()
{
    // We move the scroll buttons outside the widget rect instead of setting
    // the visibility, because setting the visibility triggers a relayout
    // of QAbstractScrollArea, which occasionally causes an offset bug when
    // QScroller performs the overshoot animation. (Overshoot is done by
    // moving the viewport widget, but the viewport position is reset during
    // a relayout.)
    const int scrollButtonWidth = this->scrollButtonWidth();
    if (m_orientation == Qt::Vertical) {
        m_scrollPrev->setArrowType(Qt::UpArrow);
        m_scrollPrev->setEnabled(verticalScrollBar()->value() != verticalScrollBar()->minimum());
        if (m_scrollPrev->isEnabled()) {
            m_scrollPrev->setGeometry(0, 0, width(), scrollButtonWidth);
        } else {
            m_scrollPrev->setGeometry(-width(), 0, width(), scrollButtonWidth);
        }
        m_scrollNext->setArrowType(Qt::DownArrow);
        m_scrollNext->setEnabled(verticalScrollBar()->value() != verticalScrollBar()->maximum());
        if (m_scrollNext->isEnabled()) {
            m_scrollNext->setGeometry(0, height() - scrollButtonWidth, width(), scrollButtonWidth);
        } else {
            m_scrollNext->setGeometry(-width(), height() - scrollButtonWidth, width(), scrollButtonWidth);
        }
    } else {
        m_scrollPrev->setArrowType(Qt::LeftArrow);
        m_scrollPrev->setEnabled(horizontalScrollBar()->value() != horizontalScrollBar()->minimum());
        if (m_scrollPrev->isEnabled()) {
            m_scrollPrev->setGeometry(0, 0, scrollButtonWidth, height());
        } else {
            m_scrollPrev->setGeometry(0, -height(), scrollButtonWidth, height());
        }
        m_scrollNext->setArrowType(Qt::RightArrow);
        m_scrollNext->setEnabled(horizontalScrollBar()->value() != horizontalScrollBar()->maximum());
        if (m_scrollNext->isEnabled()) {
            m_scrollNext->setGeometry(width() - scrollButtonWidth, 0, scrollButtonWidth, height());
        } else {
            m_scrollNext->setGeometry(width() - scrollButtonWidth, -height(), scrollButtonWidth, height());
        }
    }
}

