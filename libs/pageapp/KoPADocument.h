/* This file is part of the KDE project
   Copyright (C) 2006-2010 Thorsten Zachmann <zachmann@kde.org>

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

#ifndef KOPADOCUMENT_H
#define KOPADOCUMENT_H

#include <KoOdf.h>
#include <KoDocument.h>
#include <KoShapeBasedDocumentBase.h>
#include "KoPageApp.h"
#include "kopageapp_export.h"

class KoPAPage;
class KoPAPageBase;
class KoPAMasterPage;
class KoPALoadingContext;
class KoPASavingContext;

class KoInlineTextObjectManager;

/// Document class that stores KoPAPage and KoPAMasterPage objects
class KOPAGEAPP_EXPORT KoPADocument : public KoDocument, public KoShapeBasedDocumentBase
{
    Q_OBJECT
public:

    explicit KoPADocument(KoPart *part);
    ~KoPADocument() override;

    QPixmap generatePreview(const QSize& size) override;
    void paintContent( QPainter &painter, const QRect &rect) override;

    bool loadXML( const KoXmlDocument & doc, KoStore *store ) override;
    bool loadOdf( KoOdfReadStore & odfStore ) override;

    bool saveOdf( SavingContext & documentContext ) override;

    /**
     * The tag the body is saved in
     */
    virtual const char *odfTagName( bool withNamespace ) = 0;

    /**
     * Load master pages
     *
     * @param masterStyles
     * @param context
     */
    QList<KoPAPageBase *> loadOdfMasterPages( const QHash<QString, KoXmlElement*> masterStyles, KoPALoadingContext & context );

    /**
     * Save pages
     *
     * This is used by saveOdf and for copy and paste of pages.
     *
     * For all pages that are specified also the master slide has to be specified.
     */
    bool saveOdfPages( KoPASavingContext & paContext, QList<KoPAPageBase *> &pages, QList<KoPAPageBase *> &masterPages );

    /**
     * Save document styles
     */
    virtual void saveOdfDocumentStyles( KoPASavingContext & context );

    /**
     * Load document styles
     */
    virtual bool loadOdfDocumentStyles( KoPALoadingContext & context );

    /**
     * Get page by index.
     *
     * @param index of the page
     * @param masterPage if true return a masterPage, if false a normal page
     */
    KoPAPageBase* pageByIndex( int index, bool masterPage ) const;

    /// reimplemnted
    int pageCount() const override;

    /**
     * Get the index of the page
     *
     * @param page The page you want to get the index for
     *
     * @return The index of the page or -1 if the page is not found
     */
    int pageIndex( KoPAPageBase * page ) const;

    /**
     * Get page by navigation
     *
     * @param currentPage the current page
     * @param pageNavigation how to navigate from the current page
     *
     * @return the page which is reached by pageNavigation
     */
    KoPAPageBase* pageByNavigation( KoPAPageBase * currentPage, KoPageApp::PageNavigation pageNavigation ) const;

    /**
     * Insert page to the document at index
     *
     * The function checks if it is a normal or a master page and puts it in
     * the correct list.
     *
     * @param page to insert to document
     * @param index where the page will be inserted.
     */
    void insertPage( KoPAPageBase* page, int index );

    /**
     * Insert @p page to the document after page @p before
     *
     * The function checks if it is a normal or a master page and puts it in
     * the correct list.
     *
     * @param page to insert to document
     * @param after the page which the inserted page should come after. Set after to 0 to add at the beginning
     */
    void insertPage( KoPAPageBase* page, KoPAPageBase* after );

    /**
     * Take @page from the page
     *
     * @param page taken from the document
     * @return the position of the page was taken from the document, or -1 if the page was not found
     */
    int takePage( KoPAPageBase *page );

    /**
     * Remove the page from the document
     *
     * This generates the command and adds the command that deletes the page
     *
     * @param page The page that gets removed
     */
    virtual void removePage( KoPAPageBase * page );

    /**
     * Remove the given pages from the document
     *
     * This generates the command and adds the command that deletes the pages
     *
     * @param pages The list of pages that gets removed
     */
    virtual void removePages(QList<KoPAPageBase*> &pages);

    void addShape( KoShape *shape ) override;
    void removeShape( KoShape* shape ) override;

    QList<KoPAPageBase*> pages( bool masterPages = false ) const;

    /**
     * Get a new page for inserting into the document
     *
     * The page is created with new.
     *
     * Reimplement when you need a derived class in your kopageapplication
     */
    virtual KoPAPage *newPage(KoPAMasterPage *masterPage);

    /**
     * Get a new master page for inserting into the document
     *
     * The page is created with new.
     *
     * Reimplement when you need a derived class in your kopageapplication
     */
    virtual KoPAMasterPage * newMasterPage();

    /**
     * Get the type of the document
     */
    virtual KoOdf::DocumentType documentType() const = 0;


    /// return the inlineTextObjectManager for this document.
    KoInlineTextObjectManager *inlineTextObjectManager() const;

    void setRulersVisible(bool visible);
    bool rulersVisible() const;

    /**
     * Get the page on which the shape is located
     *
     * @param shape The shape for which the page should be found
     * @return The page on which the shape is located
     */
    KoPAPageBase * pageByShape( KoShape * shape ) const;

    /**
     * Get the page type used in the document
     *
     * The default page type KoPageApp::Page is returned
     */
    virtual KoPageApp::PageType pageType() const;

    /**
     * Get the thumbnail for the page.
     *
     * Use this method instead the one in the pages directly
     */
    QPixmap pageThumbnail(KoPAPageBase* page, const QSize& size);

    QImage pageThumbImage(KoPAPageBase* page, const QSize& size);

    void emitUpdate(KoPAPageBase *page) {emit update(page);}

    /**
     * Sets where "defaultstyles.xml" can be found in the "data" locations.
     * Needs to be set before the document is loaded.
     * @param defaultStylesResourcePath the relative path from the data locations
     */
    void setDefaultStylesResourcePath(const QString &defaultStylesResourcePath);
    QString defaultStylesResourcePath() const;

    void setShowPageMargins(bool state);
    bool showPageMargins() const;

public Q_SLOTS:
    /// reimplemented
    void initEmpty() override;

Q_SIGNALS:
    void shapeAdded(KoShape* shape);
    void shapeRemoved(KoShape* shape);
    void pageAdded(KoPAPageBase* page);

    /// This is a general signal to tell you a page was removed
    void pageRemoved(KoPAPageBase* page, int index = -1);

    /// when page is removed this signal indicates you should replace it if it was active
    void replaceActivePage(KoPAPageBase *page, KoPAPageBase *newActivePage);

    /**
     * Update all views this document is displayed on
     *
     * @param page specify a page to be updated, all views with this page as active page will be updated.
     */
    void update(KoPAPageBase *page);

    /**
     * @brief Tells if an action is possible or not
     *
     * The actions are of Type KoPAAction
     *
     * @param actions bitwise or of which actions should be enabled/disabled
     * @param possible new state of the actions
     */
    void actionsPossible(int actions, bool enable);

protected:
    /**
     * Load the presentation declaration
     *
     * The default implementation is empty
     */
    virtual bool loadOdfProlog( const KoXmlElement & body, KoPALoadingContext & context );


    /**
     * Load the epilogue
     *
     * The default implementation is empty
     */
    virtual bool loadOdfEpilogue( const KoXmlElement & body, KoPALoadingContext & context );

    /**
     * Save the prologue
     *
     * The default implementation is empty
     */
    virtual bool saveOdfProlog( KoPASavingContext & paContext );

    /**
     * Save the epilogue
     *
     * The default implementation is empty
     */
    virtual bool saveOdfEpilogue( KoPASavingContext & paContext );

    /**
     * Save settings
     */
    bool saveOdfSettings( KoStore * store );

    /**
     * Load settings
     */
    void loadOdfSettings( const KoXmlDocument & settingsDoc );

    /**
     * This function is called by at the end of addShape. This is used
     * e.g. for doing work on the application which is in the KoShapeAppData.
     *
     * The default implementation does nothing
     */
    virtual void postAddShape( KoPAPageBase * page, KoShape * shape );

    /**
     * This function is called by at the end of removeShape. This is used
     * e.g. for doing work on the application which is in the KoShapeAppData.
     *
     * The default implementation does nothing
     */
    virtual void postRemoveShape( KoPAPageBase * page, KoShape * shape );

    /**
     * This function is called with the command that will remove the page
     * given.
     * The default implementation is empty.
     *
     * @param page The page that will be removed
     * @param parent The command that will be used to delete the page
     */
    virtual void pageRemoved( KoPAPageBase * page, KUndo2Command * parent );

    /// Load the configuration
    void loadConfig();
    /// Save the configuration
    void saveConfig();

    /// set the page count so it gets shown correctly in variables
    void updatePageCount();

    /// set the url so it gets shown correctly in variables
    void updateDocumentURL();

    void setupOpenFileSubProgress() override;

private:

    friend class KoPAPastePage;
    /**
     * Load pages
     *
     * @param body
     * @param context
     */
    QList<KoPAPageBase *> loadOdfPages( const KoXmlElement & body, KoPALoadingContext & context );


private:
    class Private;
    Private * const d;
};

#include "KoPAPageProvider.h"
class Q_DECL_HIDDEN KoPADocument::Private
{
public:
    QList<KoPAPageBase*> pages;
    QList<KoPAPageBase*> masterPages;
    KoInlineTextObjectManager *inlineTextObjectManager;
    bool rulersVisible;
    KoPAPageProvider *pageProvider;
    QPointer<KoUpdater> odfProgressUpdater;
    QPointer<KoUpdater> odfMasterPageProgressUpdater;
    QPointer<KoUpdater> odfPageProgressUpdater;
    QString defaultStylesResourcePath;
    bool showPageMargins;
};

#endif /* KOPADOCUMENT_H */
