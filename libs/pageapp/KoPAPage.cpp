/* This file is part of the KDE project
   Copyright (C) 2006-2009 Thorsten Zachmann <zachmann@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#include "KoPAPage.h"

#include <QPainter>
#include <PageAppDebug.h>

#include <KoShapePainter.h>
#include <KoShapeSavingContext.h>
#include <KoOdfLoadingContext.h>
#include <KoStyleStack.h>
#include <KoXmlWriter.h>
#include <KoXmlNS.h>
#include <KoZoomHandler.h>
#include <KoShapePaintingContext.h>

#include "KoPAMasterPage.h"
#include "KoPASavingContext.h"
#include "KoPALoadingContext.h"


KoPAPage::KoPAPage( KoPAMasterPage * masterPage )
: KoPAPageBase()
, m_masterPage( masterPage )
, m_pageProperties( UseMasterBackground | DisplayMasterBackground | DisplayMasterShapes )
{
    Q_ASSERT(masterPage);
}

KoPAPage::~KoPAPage()
{
}

void KoPAPage::saveOdf( KoShapeSavingContext & context ) const
{
    KoPASavingContext &paContext = static_cast<KoPASavingContext&>( context );
    paContext.xmlWriter().startElement( "draw:page" );
    paContext.xmlWriter().addAttribute( "draw:name", paContext.pageName( this ) );
    if (!name().isEmpty() && name() != paContext.pageName( this )) {
        paContext.xmlWriter().addAttribute( "calligra:name", name() );
    }
    paContext.xmlWriter().addAttribute( "draw:id", "page" + QString::number( paContext.page() ) );
    paContext.xmlWriter().addAttribute( "xml:id", "page" + QString::number( paContext.page() ) );
    paContext.xmlWriter().addAttribute( "draw:master-page-name", paContext.masterPageName( m_masterPage ) );
    paContext.xmlWriter().addAttribute( "draw:style-name", saveOdfPageStyle( paContext ) );

    saveOdfPageContent( paContext );

    paContext.xmlWriter().endElement();
}

KoPageLayout & KoPAPage::pageLayout()
{
    Q_ASSERT( m_masterPage );

    return m_masterPage->pageLayout();
}

const KoPageLayout & KoPAPage::pageLayout() const
{
    Q_ASSERT( m_masterPage );

    return m_masterPage->pageLayout();
}

void KoPAPage::loadOdfPageTag( const KoXmlElement &element, KoPALoadingContext &loadingContext )
{
    QString master = element.attributeNS (KoXmlNS::draw, "master-page-name" );
    KoPAMasterPage *masterPage = loadingContext.masterPageByName(master);
    if (masterPage)
        setMasterPage(masterPage);
#ifndef NDEBUG
    else
        warnPageApp << "Loading didn't provide a page under name; " << master;
#endif
    KoStyleStack& styleStack = loadingContext.odfLoadingContext().styleStack();
    int pageProperties = UseMasterBackground | DisplayMasterShapes | DisplayMasterBackground;
    if ( styleStack.hasProperty( KoXmlNS::draw, "fill" ) ) {
        KoPAPageBase::loadOdfPageTag( element, loadingContext );
        pageProperties = DisplayMasterShapes;
    }
    m_pageProperties = pageProperties;
    QString name;
    if ( element.hasAttributeNS( KoXmlNS::draw, "name" ) ) {
        name = element.attributeNS( KoXmlNS::draw, "name" );
        loadingContext.addPage( name, this );
    }
    if ( element.hasAttributeNS( KoXmlNS::calligra, "name" ) ) {
        name = element.attributeNS( KoXmlNS::calligra, "name" );
    }
    setName( name );
}

void KoPAPage::setMasterPage( KoPAMasterPage * masterPage )
{
    Q_ASSERT(masterPage);
    m_masterPage = masterPage;
    pageUpdated();
}

void KoPAPage::paintBackground( QPainter & painter, const KoViewConverter & converter, KoShapePaintingContext &paintContext )
{
    if ( m_pageProperties & UseMasterBackground ) {
        if ( m_pageProperties & DisplayMasterBackground ) {
            Q_ASSERT( m_masterPage );
            m_masterPage->paintBackground( painter, converter, paintContext );
        }
    }
    else {
        KoPAPageBase::paintBackground( painter, converter, paintContext );
    }
}

bool KoPAPage::displayMasterShapes()
{
    return m_pageProperties & DisplayMasterShapes;
}

void KoPAPage::setDisplayMasterShapes( bool display )
{
    if ( display ) {
        m_pageProperties |= DisplayMasterShapes;
    }
    else {
        m_pageProperties &= ~DisplayMasterShapes;
    }
}

bool KoPAPage::displayMasterBackground()
{
    return m_pageProperties & UseMasterBackground;
}

void KoPAPage::setDisplayMasterBackground( bool display )
{
    if ( display ) {
        m_pageProperties |= UseMasterBackground;
    }
    else {
        m_pageProperties &= ~UseMasterBackground;
    }
}

bool KoPAPage::displayShape(KoShape *shape) const
{
    Q_UNUSED(shape);
    return true;
}

void KoPAPage::paintPage( QPainter & painter, KoZoomHandler & zoomHandler )
{
    KoShapePaintingContext context;
    paintBackground( painter, zoomHandler, context );

    KoShapePainter shapePainter( getPaintingStrategy() );
    if ( displayMasterShapes() ) {
        shapePainter.setShapes( masterPage()->shapes() );
        shapePainter.paint(painter, zoomHandler);
    }
    shapePainter.setShapes( shapes() );
    shapePainter.paint(painter, zoomHandler);
}

void KoPAPage::saveOdfPageStyleData( KoGenStyle &style, KoPASavingContext &paContext ) const
{
    if ( ( m_pageProperties & UseMasterBackground ) == 0 ) {
        KoPAPageBase::saveOdfPageStyleData( style, paContext );
    }
}
