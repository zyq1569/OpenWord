/* This file is part of the KDE project
 * Copyright (C) 2007-2008 Thorsten Zachmann <zachmann@kde.org>
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

#include "KoPAViewModeNormal.h"

#include <QKeyEvent>
#include <QPainter>

#include <KoToolProxy.h>
#include <KoShapeManager.h>
#include <KoShapePaintingContext.h>
#include <KoGridData.h>
#include <KoGuidesData.h>
#include "KoPACanvasBase.h"
#include "KoPADocument.h"
#include "KoPAPage.h"
#include "KoPAMasterPage.h"
#include "KoPAViewBase.h"
#include "commands/KoPAChangePageLayoutCommand.h"

KoPAViewModeNormal::KoPAViewModeNormal( KoPAViewBase * view, KoPACanvasBase * canvas )
: KoPAViewMode( view, canvas )
, m_masterMode( false )
, m_savedPage( 0 )
{
}

KoPAViewModeNormal::~KoPAViewModeNormal()
{
}

void KoPAViewModeNormal::paint(KoPACanvasBase* canvas, QPainter& painter, const QRectF &paintRect)
{
#ifdef NDEBUG
    Q_UNUSED(canvas)
#else
    Q_ASSERT( m_canvas == canvas );
#endif

    painter.translate( -m_canvas->documentOffset() );
    painter.setRenderHint( QPainter::Antialiasing );
    QRect clipRect = paintRect.translated( m_canvas->documentOffset() ).toRect();
    painter.setClipRect( clipRect );

    painter.translate( m_canvas->documentOrigin().x(), m_canvas->documentOrigin().y() );

    KoViewConverter * converter = m_view->viewConverter( m_canvas );
    QRectF updateRect = converter->viewToDocument( m_canvas->widgetToView( clipRect ) );
    KoShapePaintingContext context;
    m_view->activePage()->paintBackground( painter, *converter, context );

    const KoPageLayout &layout = activePageLayout();
    QSizeF pageSize(layout.width, layout.height);
    QRectF gridRect = QRectF(QPointF(), pageSize).intersected(updateRect);
    if (m_canvas->document()->gridData().paintGridInBackground()) {
        painter.setRenderHint(QPainter::Antialiasing, false);
        m_canvas->document()->gridData().paintGrid(painter, *converter, gridRect );
    }

    // paint the page margins
    paintMargins( painter, *converter );

    painter.setRenderHint( QPainter::Antialiasing );

    // paint the shapes
    if ( m_view->activePage()->displayMasterShapes() ) {
        m_canvas->masterShapeManager()->paint( painter, *converter, false );
    }
    m_canvas->shapeManager()->paint( painter, *converter, false );

    painter.setRenderHint( QPainter::Antialiasing, false );

    if (!m_canvas->document()->gridData().paintGridInBackground()) {
        m_canvas->document()->gridData().paintGrid(painter, *converter, gridRect);
    }
    m_canvas->document()->guidesData().paintGuides(painter, *converter, updateRect);

    painter.setRenderHint(QPainter::Antialiasing);
    m_toolProxy->paint(painter, *converter);
}

void KoPAViewModeNormal::tabletEvent( QTabletEvent *event, const QPointF &point )
{
    m_toolProxy->tabletEvent( event, point );
}

void KoPAViewModeNormal::mousePressEvent( QMouseEvent *event, const QPointF &point )
{
    m_toolProxy->mousePressEvent( event, point );
}

void KoPAViewModeNormal::mouseDoubleClickEvent( QMouseEvent *event, const QPointF &point )
{
    m_toolProxy->mouseDoubleClickEvent( event, point );
}

void KoPAViewModeNormal::mouseMoveEvent( QMouseEvent *event, const QPointF &point )
{
    m_toolProxy->mouseMoveEvent( event, point );
}

void KoPAViewModeNormal::mouseReleaseEvent( QMouseEvent *event, const QPointF &point )
{
    m_toolProxy->mouseReleaseEvent( event, point );
}

void KoPAViewModeNormal::shortcutOverrideEvent( QKeyEvent *event )
{
    m_toolProxy->shortcutOverrideEvent( event );
}

void KoPAViewModeNormal::keyPressEvent( QKeyEvent *event )
{
    m_toolProxy->keyPressEvent( event );

    if ( ! event->isAccepted() ) {
        event->accept();

        switch ( event->key() )
        {
            case Qt::Key_Home:
                m_view->navigatePage( KoPageApp::PageFirst );
                break;
            case Qt::Key_PageUp:
                m_view->navigatePage( KoPageApp::PagePrevious );
                break;
            case Qt::Key_PageDown:
                m_view->navigatePage( KoPageApp::PageNext );
                break;
            case Qt::Key_End:
                m_view->navigatePage( KoPageApp::PageLast );
                break;
            default:
                event->ignore();
                break;
        }
    }
}

void KoPAViewModeNormal::keyReleaseEvent( QKeyEvent *event )
{
    m_toolProxy->keyReleaseEvent( event );
}

void KoPAViewModeNormal::wheelEvent( QWheelEvent * event, const QPointF &point )
{
    m_toolProxy->wheelEvent( event, point );
}

void KoPAViewModeNormal::setMasterMode( bool master )
{
    m_masterMode = master;
    KoPAPage * page = dynamic_cast<KoPAPage *>( m_view->activePage() );
    if ( m_masterMode ) {
        if ( page ) {
            m_view->doUpdateActivePage( page->masterPage() );
            m_savedPage = page;
        }
    }
    else if ( m_savedPage ) {
        m_view->doUpdateActivePage( m_savedPage );
        m_savedPage = 0;
    }
}

bool KoPAViewModeNormal::masterMode()
{
    return m_masterMode;
}

void KoPAViewModeNormal::addShape( KoShape *shape )
{
    // the KoShapeController sets the active layer as parent
    KoPAPageBase * page( m_view->kopaDocument()->pageByShape( shape ) );

    bool isMaster = dynamic_cast<KoPAMasterPage*>( page ) != 0;

    KoPAPage * p;
    if ( page == m_view->activePage() ) {
        m_view->kopaCanvas()->shapeManager()->addShape( shape );
    }
    else if ( isMaster && ( p = dynamic_cast<KoPAPage*>( m_view->activePage() ) ) != 0 ) {
        if ( p->masterPage() == page ) {
            m_view->kopaCanvas()->masterShapeManager()->addShape( shape );
        }
    }
}

void KoPAViewModeNormal::removeShape( KoShape *shape )
{
    KoPAPageBase * page( m_view->kopaDocument()->pageByShape( shape ) );

    bool isMaster = dynamic_cast<KoPAMasterPage*>( page ) != 0;

    KoPAPage * p;
    if ( page == m_view->activePage() ) {
        m_view->kopaCanvas()->shapeManager()->remove( shape );
    }
    else if ( isMaster && ( p = dynamic_cast<KoPAPage*>( m_view->activePage() ) ) != 0 ) {
        if ( p->masterPage() == page ) {
            m_view->kopaCanvas()->masterShapeManager()->remove( shape );
        }
    }
}

void KoPAViewModeNormal::changePageLayout( const KoPageLayout &pageLayout, bool applyToDocument, KUndo2Command *parent )
{
    KoPAPageBase *page = m_view->activePage();
    KoPAMasterPage *masterPage = dynamic_cast<KoPAMasterPage *>( page );
    if ( !masterPage ) {
        masterPage = static_cast<KoPAPage *>( page )->masterPage();
    }

    new KoPAChangePageLayoutCommand( m_canvas->document(), masterPage, pageLayout, applyToDocument, parent );
}

void KoPAViewModeNormal::paintMargins( QPainter &painter, const KoViewConverter &converter )
{
    if (!canvas()->showPageMargins()) {
        return;
    }
    KoPAPageBase *page = m_view->activePage();
    KoPageLayout pl = page->pageLayout();

    QSizeF pageSize = QSizeF( pl.width, pl.height );
    QRectF marginRect( pl.leftMargin, pl.topMargin,
                       pageSize.width() - pl.leftMargin - pl.rightMargin,
                       pageSize.height() - pl.topMargin - pl.bottomMargin );

    QPen pen(Qt::gray, 0);
    painter.setPen( pen );
    painter.drawRect( converter.documentToView( marginRect ) );
}

