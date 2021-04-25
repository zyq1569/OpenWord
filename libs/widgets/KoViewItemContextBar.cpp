/* This file is part of the KDE project
*
* Copyright (C) 2008 Peter Penz <peter.penz19@gmail.com>
* Copyright (C) 2011 Paul Mendez <paulestebanms@gmail.com>
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

#include "KoViewItemContextBar.h"

//Calligra headers
#include "KoContextBarButton.h"
#include <KoIcon.h>

// KF5
#include <klocalizedstring.h>

//Qt Headers
#include <QAbstractItemView>
#include <QModelIndex>
#include <QApplication>
#include <QHBoxLayout>
#include <QHoverEvent>

/** Space between the item outer rect and the context bar */
const int CONTEXTBAR_MARGIN = 4;
const int MIN_BUTTON_WIDTH = 24;

KoViewItemContextBar::KoViewItemContextBar(QAbstractItemView *parent)
    : QObject(parent)
    , m_view(parent)
    , m_enabled(true)
    , m_showToggleButton(true)
{
    connect(parent, SIGNAL(entered(QModelIndex)),
            this, SLOT(slotEntered(QModelIndex)));
    connect(parent, SIGNAL(viewportEntered()),
            this, SLOT(slotViewportEntered()));

    m_ContextBar = new QWidget(m_view->viewport());
    m_ContextBar->hide();
    m_ToggleSelectionButton = new KoContextBarButton(koIconName("list-add"));

    m_Layout = new QHBoxLayout(m_ContextBar);
    m_Layout->setMargin(2);
    m_Layout->setSpacing(2);
    m_Layout->addWidget(m_ToggleSelectionButton);

    connect(m_ToggleSelectionButton, SIGNAL(clicked()),
            this, SLOT(setItemSelected()));
    // Hides context bar if item removed
    connect(m_view->model(), SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this, SLOT(slotRowsRemoved(QModelIndex,int,int)));

    connect(m_view->model(), SIGNAL(modelReset()), this, SLOT(slotModelReset()));

    m_ContextBar->installEventFilter(this);
    m_view->viewport()->installEventFilter(this);
    m_view->setMouseTracking(true);
}

bool KoViewItemContextBar::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_view->viewport()) {
        switch (event->type()) {
        case QEvent::Leave:
            if (m_ContextBar->isVisible()) {
                m_ContextBar->hide();
            }
            break;
        default:
            break;
        }
    }
    return QObject::eventFilter(watched, event);
}

void KoViewItemContextBar::slotEntered(const QModelIndex &index)
{
    const bool isSelectionCandidate = index.isValid() &&
            (QApplication::mouseButtons() == Qt::NoButton);

    if (!m_ContextBar || !m_enabled) {
        return;
    }

    m_ContextBar->hide();
    if (isSelectionCandidate) {
        updateHoverUi(index);
    }
    else {
        updateHoverUi(QModelIndex());
    }
}

void KoViewItemContextBar::updateHoverUi(const QModelIndex &index)
{
    QModelIndex oldIndex = m_IndexUnderCursor;
    m_IndexUnderCursor = index;
    m_view->update(oldIndex);

    const bool isSelectionCandidate = index.isValid();

    m_ContextBar->hide();
    if (isSelectionCandidate) {
        updateToggleSelectionButton();
        const QRect rect = m_view->visualRect(m_IndexUnderCursor);
        showContextBar(rect);
        m_view->update(m_IndexUnderCursor);
    } else {
        m_ContextBar->hide();
    }
}

void KoViewItemContextBar::showContextBar(const QRect &rect)
{
    // Center bar in FullContextBar mode, left align in
    // SelectionOnlyContextBar mode
    const int posX = 0;
    const int posY = CONTEXTBAR_MARGIN / 4;
    int numButtons = 0;
    m_ContextBar->move(rect.topLeft() + QPoint(posX, posY));
    //Hide buttons if item is too small
    int width = m_ToggleSelectionButton->width();
    if (!m_showToggleButton) {
        m_ToggleSelectionButton->setVisible(false);
        width = qMin(m_contextBarButtons.at(0)->width(), MIN_BUTTON_WIDTH);
    }
    for (int i=m_contextBarButtons.size()-1; i>=0; --i) {
        if ((rect.width() - 2 * CONTEXTBAR_MARGIN) > ((i + 1) * width)) {
            m_contextBarButtons.at(i)->setVisible(true);
            numButtons++;
            continue;
        }
        m_contextBarButtons.at(i)->setVisible(false);
    }
    m_ContextBar->adjustSize();
    if (numButtons > 0) {
        const int centerX = (rect.width() - m_ContextBar->rect().width()) / 2;
        m_ContextBar->move(rect.topLeft() + QPoint(centerX, posY));
    }
    m_ContextBar->show();
}

void KoViewItemContextBar::slotViewportEntered()
{
    m_ContextBar->hide();
}

void KoViewItemContextBar::setItemSelected()
{
    emit selectionChanged();

    if (m_IndexUnderCursor.isValid()) {
        QItemSelectionModel *selModel = m_view->selectionModel();
        if (!selModel->isSelected(m_IndexUnderCursor)) {
            selModel->select(m_IndexUnderCursor, QItemSelectionModel::Select);
        }
        else {
            selModel->select(m_IndexUnderCursor, QItemSelectionModel::Deselect);
        }
        selModel->setCurrentIndex(m_IndexUnderCursor, QItemSelectionModel::Current);
    }
    updateHoverUi(m_IndexUnderCursor);
}

void KoViewItemContextBar::slotRowsRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
    if (m_ContextBar) {
        m_ContextBar->hide();
    }
}

void KoViewItemContextBar::updateToggleSelectionButton()
{
    const bool isHoveredIndexSelected = m_view->selectionModel()->isSelected(m_IndexUnderCursor);
    const char *const iconName = (isHoveredIndexSelected ? koIconNameCStr("list-remove") : koIconNameCStr("list-add"));

    m_ToggleSelectionButton->setIcon(QIcon::fromTheme(QLatin1String(iconName)));
    m_ToggleSelectionButton->setToolTip(isHoveredIndexSelected ? i18n("deselect item") : i18n("select item"));
}

void KoViewItemContextBar::update()
{
    // Check if the current index is still valid and then update the context bar
    if (m_view->model()->index(currentIndex().row(), currentIndex().column(), currentIndex().parent()).isValid()) {
        updateHoverUi(currentIndex());
    }
    else {
        updateHoverUi(QModelIndex());
    }
}

QToolButton * KoViewItemContextBar::addContextButton(const QString &text, const QString &iconName)
{
    KoContextBarButton *newContexButton = new KoContextBarButton(iconName);
    newContexButton->setToolTip(text);
    m_Layout->addWidget(newContexButton);
    m_contextBarButtons.append(newContexButton);
    return newContexButton;
}

QModelIndex KoViewItemContextBar::currentIndex()
{
    return m_IndexUnderCursor;
}

int KoViewItemContextBar::preferredWidth()
{
    return ((m_contextBarButtons.count()+1)*m_ToggleSelectionButton->sizeHint().width() + 2*CONTEXTBAR_MARGIN);
}

void KoViewItemContextBar::setShowSelectionToggleButton(bool enabled)
{
    m_showToggleButton = enabled;
}

void KoViewItemContextBar::reset()
{
    if (m_ContextBar) {
        m_ContextBar->hide();
    }
}

void KoViewItemContextBar::slotModelReset()
{
    // reset the model index so it does no longer point to suff no longer available.
    m_IndexUnderCursor = QModelIndex();
}

void KoViewItemContextBar::enableContextBar()
{
    m_enabled = true;
}

void KoViewItemContextBar::disableContextBar()
{
    m_enabled = false;
}
