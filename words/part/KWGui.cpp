/* This file is part of the KDE project
 * Copyright (C) 2001 David Faure <faure@kde.org>
 * Copyright (C) 2005-2007, 2009 Thomas Zander <zander@kde.org>
 * Copyright (C) 2010 Boudewijn Rempt <boud@kogmbh.com>
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
 * Boston, MA 02110-1301, USA
 */

#include "KWGui.h"
#include "KWView.h"
#include "KWDocument.h"
#include "KWCanvas.h"
#include "KWPage.h"

#include <KoCanvasControllerWidget.h>
#include <KoToolManager.h>
#include <KoShapeManager.h>
#include <KoShape.h>
#include <KoFlake.h>
#include <KoSelection.h>
#include <KoDockerManager.h>
#include <KoRuler.h>
#include <KoUnit.h>
#include <KoModeBoxFactory.h>
#include <KoRulerController.h>
#include <kactioncollection.h>

#include <QGridLayout>
#include <QTimer>
#include <QAction>
#include <QScrollBar>
#include <KoMainWindow.h>

//static Qt::ArrowType sg_arrowType = Qt::ArrowType::NoArrow;
static QString sg_iconname = "none";
KWGui::KWGui(const QString &viewMode, KWView *parent)
    : QWidget(parent),
      m_view(parent)
{
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);

    setMouseTracking(true);

    // Ruler
    m_horizontalRuler = new KoRuler(this, Qt::Horizontal, m_view->viewConverter());
    m_horizontalRuler->setShowMousePosition(true);
    m_horizontalRuler->setUnit(m_view->kwdocument()->unit());
    m_verticalRuler = new KoRuler(this, Qt::Vertical, m_view->viewConverter());
    m_verticalRuler->setUnit(m_view->kwdocument()->unit());
    m_verticalRuler->setShowMousePosition(true);

    m_canvas = new KWCanvas(viewMode, static_cast<KWDocument*>(m_view->koDocument()), m_view, this);
    ///滚动条控制
    KoCanvasControllerWidget *canvasController = new KoCanvasControllerWidget(m_view->actionCollection(), this);
    m_canvasController = canvasController;
    // We need to set this as QDeclarativeView sets them a bit different from QAbstractScrollArea
    canvasController->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    canvasController->setFocusPolicy(Qt::NoFocus);
    //setScene(0);

    canvasController->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_canvasController->setMargin(9);///文本文档区域和周围距离
    m_canvasController->setCanvas(m_canvas);
    m_canvasController->setCanvasMode(KoCanvasController::AlignTop);
    KoToolManager::instance()->addController(m_canvasController);
    KoToolManager::instance()->registerTools(m_view->actionCollection(), m_canvasController);

    if (m_view->mainWindow())
    {
        KoModeBoxFactory modeBoxFactory(canvasController, qApp->applicationName(), i18n("Tools"));
        QDockWidget* modeBox = m_view->mainWindow()->createDockWidget(&modeBoxFactory);//create 的对象 QDockWidget KoModeBoxDocker存在KoMainWindow
        m_view->mainWindow()->dockerManager()->removeToolOptionsDocker();
        dynamic_cast<KoCanvasObserverBase*>(modeBox)->setObservedCanvas(m_canvas);
    }

    gridLayout->addWidget(m_horizontalRuler->tabChooser(), 0, 0);///是什么控件???
    gridLayout->addWidget(m_horizontalRuler, 0, 1);
    gridLayout->addWidget(m_verticalRuler, 1, 0);
    gridLayout->addWidget(canvasController, 1, 1);
    //openword------------
    ///需要改善为类似LibreOffice方式伸缩工具箱
    /// to do  定制化QWidget 的QToolButton
    m_showtoolbox = new QToolButton();
    if (m_showtoolbox)
    {
        m_showtoolbox->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
        m_showtoolbox->setIcon(QIcon(":/images/right.png"));
        m_showtoolbox->setAutoRaise(true);
        m_showtoolbox->setFixedSize(9,120);
        //QSize size(12, 12);
        //m_showtoolbox->setIconSize(size);
        m_showtoolbox->setStyleSheet("QToolButton{background-color:rgb(105,105,105)}QToolButton:hover{background-color:rgb(97,225,248)}");
        gridLayout->addWidget(m_showtoolbox, 1, 2);
        connect(m_showtoolbox,SIGNAL(clicked(bool)),this,SLOT(visibleDockWidget(bool)));
    }
    //openword-------------

    new KoRulerController(m_horizontalRuler, m_canvas->resourceManager());
    connect(m_view->kwdocument(), SIGNAL(unitChanged(KoUnit)), m_horizontalRuler, SLOT(setUnit(KoUnit)));
    connect(m_view->kwdocument(), SIGNAL(unitChanged(KoUnit)), m_verticalRuler, SLOT(setUnit(KoUnit)));
    connect(m_view->kwdocument(), SIGNAL(pageSetupChanged()), this, SLOT(pageSetupChanged()));

    connect(m_canvasController->proxyObject, SIGNAL(canvasOffsetXChanged(int)), m_horizontalRuler, SLOT(setOffset(int)));
    connect(m_canvasController->proxyObject, SIGNAL(canvasOffsetYChanged(int)), m_verticalRuler, SLOT(setOffset(int)));
    connect(m_canvasController->proxyObject, SIGNAL(canvasOffsetYChanged(int)), parent, SLOT(offsetInDocumentMoved(int)));
    connect(m_canvasController->proxyObject, SIGNAL(canvasMousePositionChanged(QPoint)), this, SLOT(updateMousePos(QPoint)));
    connect(m_canvasController->proxyObject, SIGNAL(moveDocumentOffset(QPoint)), m_canvas, SLOT(setDocumentOffset(QPoint)));

    connect(m_canvas->shapeManager()->selection(), SIGNAL(selectionChanged()), this, SLOT(shapeSelectionChanged()));

    m_verticalRuler->createGuideToolConnection(m_canvas);
    m_horizontalRuler->createGuideToolConnection(m_canvas);

    pageSetupChanged();

    QTimer::singleShot(0, this, SLOT(setupUnitActions()));
    m_initDockWidget = true;
    visibleDockWidget(true);
}

KWGui::~KWGui()
{
    //-----m_showtoolbox->deleteLater();
    delete m_showtoolbox;//openword
    m_showtoolbox = 0;
    //-----------------------------
}

int KWGui::visibleWidth() const
{
    return m_canvasController->visibleWidth();
}

int KWGui::visibleHeight() const
{
    return m_canvasController->visibleHeight();
}

QSize KWGui::viewportSize() const
{
    return m_canvasController->viewportSize();
}


bool KWGui::horizontalScrollBarVisible()
{
    return static_cast<KoCanvasControllerWidget*>(m_canvasController)->horizontalScrollBar() &&
           static_cast<KoCanvasControllerWidget*>(m_canvasController)->horizontalScrollBar()->isVisible();
}

void KWGui::pageSetupChanged()
{
    const KWPageManager *pm = m_view->kwdocument()->pageManager();
    const KWPage firstPage = pm->begin();
    const KWPage lastPage = pm->last();
    int height = 0;
    if (lastPage.isValid())
    {
        height = lastPage.offsetInDocument() + lastPage.height();
    }
    m_verticalRuler->setRulerLength(height);
    updateRulers();
    int width = 0;
    if (firstPage.isValid())
    {
        width = firstPage.width();
    }
    m_horizontalRuler->setRulerLength(width);
    m_horizontalRuler->setActiveRange(0, width);
    m_verticalRuler->setActiveRange(0, height);
    updateRulers();
}

void KWGui::updateMousePos(const QPoint &point)
{
    QPoint canvasOffset(m_canvasController->canvasOffsetX(), m_canvasController->canvasOffsetY());
    // the offset is positive it the canvas is shown fully visible
    canvasOffset.setX(canvasOffset.x() < 0 ? canvasOffset.x() : 0);
    canvasOffset.setY(canvasOffset.y() < 0 ? canvasOffset.y() : 0);
    QPoint viewPos = point - canvasOffset;
    m_horizontalRuler->updateMouseCoordinate(viewPos.x());
    m_verticalRuler->updateMouseCoordinate(viewPos.y());
}

void KWGui::updateRulers() const
{
    m_verticalRuler->setVisible(m_view->kwdocument()->config().viewRulers());
    m_horizontalRuler->setVisible(m_view->kwdocument()->config().viewRulers());
}

void KWGui::shapeSelectionChanged()
{
}

void KWGui::setupUnitActions()
{
    QList<QAction*> unitActions = m_view->createChangeUnitActions();
    QAction *separator = new QAction(this);
    separator->setSeparator(true);
    unitActions.append(separator);
    unitActions.append(m_view->actionCollection()->action("format_page"));
    m_horizontalRuler->setPopupActionList(unitActions);
}


void KWGui::mouseMoveEvent(QMouseEvent *e)
{
    m_view->viewMouseMoveEvent(e);
    //setToolTip(QString::number( e->x()) + "|" + QString::number(e->y()));
}

void KWGui::visibleDockWidget(bool checked)
{
    static  QString showTip("show"), hideTip("hide");
    static  bool initLang = true;

    if (initLang)
    {
        static const QString langName = QLocale::system().name();
        if (langName == "zh_CN")
        {
            showTip = "显示工具箱";
            hideTip = "隐藏工具箱";
        }
        initLang=  false;
    }

    bool visible = false;
    foreach (QDockWidget *dock, m_view->mainWindow()->dockWidgets())
    {
        QString str = dock->windowTitle();
        if (!str.contains("Options") && !str.contains("Stencil"))
        {
            if (dock->isVisible())
            {
                visible = true;
                break;
            }
        }
    }

    if (m_initDockWidget)
    {
        m_initDockWidget = false;
        foreach (QDockWidget *dock, m_view->mainWindow()->dockWidgets())
        {
            dock->setFeatures(dock->features()&~QDockWidget::DockWidgetMovable);
        }

        //if (sg_arrowType != Qt::ArrowType::NoArrow)//如果已经有打开的则只需要使用最后一个打开的状态即可
        if (sg_iconname != "none")
        {
            //m_showtoolbox->setArrowType(sg_arrowType);
            m_showtoolbox->setIcon(QIcon(":/images/"+sg_iconname+".png"));
            m_showtoolbox->setToolTip(hideTip);
            //if (sg_arrowType == Qt::ArrowType::LeftArrow)
            if (sg_iconname == "right")
            {
                m_showtoolbox->setToolTip(showTip);
            }
            return;
        }

        if (visible)
        {
            sg_iconname = "right";
            //m_showtoolbox->setArrowType(Qt::ArrowType::RightArrow);
            //sg_arrowType = Qt::ArrowType::RightArrow;
            m_showtoolbox->setToolTip(hideTip);
        }
        else
        {
            sg_iconname = "left";
            //m_showtoolbox->setArrowType(Qt::ArrowType::LeftArrow);
            //sg_arrowType = Qt::ArrowType::LeftArrow;
            m_showtoolbox->setToolTip(showTip);
        }
        m_showtoolbox->setIcon(QIcon(":/images/"+sg_iconname+".png"));
        return;
    }

    //todo: 须要调整为控件隐藏2个状态 和显示2个状态
    foreach (QDockWidget *dock, m_view->mainWindow()->dockWidgets())
    {
        QString str = dock->windowTitle();
        if (!str.contains("Options") /*!= "Tool Options"*/ && !str.contains("Stencil")/* !=  "&Stencil Box"*/)
        {
            if (visible)
            {
                dock->setVisible(false);
            }
            else
            {
                dock->setVisible(true);
            }
        }
    }
    if (visible)
    {
        //m_showtoolbox->setArrowType(Qt::ArrowType::LeftArrow);
        //sg_arrowType = Qt::ArrowType::LeftArrow;
        //m_showtoolbox->setIcon(QIcon(":/images/right.png"));
        sg_iconname = "left";
        m_showtoolbox->setToolTip(showTip);
    }
    else
    {
        //m_showtoolbox->setArrowType(Qt::ArrowType::RightArrow);
        //m_showtoolbox->setIcon(QIcon(":/images/right.png"));
        //sg_arrowType = Qt::ArrowType::RightArrow;
        sg_iconname = "right";
        m_showtoolbox->setToolTip(hideTip);
    }
    m_showtoolbox->setIcon(QIcon(":/images/"+sg_iconname+".png"));

}
