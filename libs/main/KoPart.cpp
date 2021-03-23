/* This file is part of the KDE project
 * Copyright (C) 1998, 1999 Torben Weis <weis@kde.org>
 * Copyright (C) 2000-2005 David Faure <faure@kde.org>
 * Copyright (C) 2007-2008 Thorsten Zachmann <zachmann@kde.org>
 * Copyright (C) 2010-2012 Boudewijn Rempt <boud@kogmbh.com>
 * Copyright (C) 2011 Inge Wallin <ingwa@kogmbh.com>
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

#include "KoPart.h"

#include "KoApplication.h"
#include "KoMainWindow.h"
#include "KoDocument.h"
#include "KoView.h"
#include "KoOpenPane.h"
#include "KoFilterManager.h"
#include <KoComponentData.h>

#include <KoCanvasController.h>
#include <KoCanvasControllerWidget.h>
#include <KoResourcePaths.h>

#include <MainDebug.h>
#include <kxmlguifactory.h>
#include <kdesktopfile.h>
#include <kconfiggroup.h>
#include <ksharedconfig.h>

#include <QFileInfo>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QMimeDatabase>

#ifndef QT_NO_DBUS
#include <QDBusConnection>
#include "KoPartAdaptor.h"
#endif

class Q_DECL_HIDDEN KoPart::Private
{
public:
    Private(const KoComponentData &componentData_, KoPart *_parent)
        : parent(_parent)
        , document(0)
        , proxyWidget(0)
        , startUpWidget(0)
        , componentData(componentData_)
    {
    }

    ~Private()
    {
        delete proxyWidget;
    }

    KoPart *parent;

    QList<KoView*> views;
    QList<KoMainWindow*> mainWindows;
    KoDocument *document;
    QList<KoDocument*> documents;
    QPointer<QGraphicsProxyWidget> proxyWidget;
    QPointer<KoOpenPane> startUpWidget;
    QString templatesResourcePath;

    KoComponentData componentData;
};


KoPart::KoPart(const KoComponentData &componentData, QObject *parent)
    : QObject(parent)
    , d(new Private(componentData, this))
{
#ifndef QT_NO_DBUS
    new KoPartAdaptor(this);
    QDBusConnection::sessionBus().registerObject('/' + objectName(), this);
#endif
}

KoPart::~KoPart()
{
    // Tell our views that the document is already destroyed and
    // that they shouldn't try to access it.
    foreach(KoView *view, views())
    {
        view->setDocumentDeleted();
    }

    while (!d->mainWindows.isEmpty())
    {
        delete d->mainWindows.takeFirst();
    }

    delete d->startUpWidget;
    d->startUpWidget = 0;

    delete d;
}

KoComponentData KoPart::componentData() const
{
    return d->componentData;
}

void KoPart::setDocument(KoDocument *document)
{
    Q_ASSERT(document);
    d->document = document;
}

KoDocument *KoPart::document() const
{
    return d->document;
}

KoView *KoPart::createView(KoDocument *document, QWidget *parent)
{
    KoView *view = createViewInstance(document, parent);
    addView(view, document);
    if (!d->documents.contains(document))
    {
        d->documents.append(document);
    }
    return view;
}

void KoPart::addView(KoView *view, KoDocument *document)
{
    if (!view)
    {
        return;
    }

    if (!d->views.contains(view))
    {
        d->views.append(view);
    }
    if (!d->documents.contains(document))
    {
        d->documents.append(document);
    }

    view->updateReadWrite(document->isReadWrite());

    if (d->views.size() == 1)
    {
        KoApplication *app = qobject_cast<KoApplication*>(qApp);
        if (0 != app)
        {
            emit app->documentOpened('/'+objectName());
        }
    }
}

void KoPart::removeView(KoView *view)
{
    d->views.removeAll(view);

    if (d->views.isEmpty())
    {
        KoApplication *app = qobject_cast<KoApplication*>(qApp);
        if (0 != app)
        {
            emit app->documentClosed('/'+objectName());
        }
    }
}

QList<KoView*> KoPart::views() const
{
    return d->views;
}

int KoPart::viewCount() const
{
    return d->views.count();
}

QGraphicsItem *KoPart::canvasItem(KoDocument *document, bool create)
{
    if (create && !d->proxyWidget)
    {
        return createCanvasItem(document);
    }
    return d->proxyWidget;
}

QGraphicsItem *KoPart::createCanvasItem(KoDocument *document)
{
    KoView *view = createView(document);
    d->proxyWidget = new QGraphicsProxyWidget();
    QWidget *canvasController = view->findChild<KoCanvasControllerWidget*>();
    d->proxyWidget->setWidget(canvasController);
    return d->proxyWidget;
}

void KoPart::addMainWindow(KoMainWindow *mainWindow)
{
    if (d->mainWindows.indexOf(mainWindow) == -1)
    {
        debugMain <<"mainWindow" << (void*)mainWindow <<"added to doc" << this;
        d->mainWindows.append(mainWindow);
    }
}

void KoPart::removeMainWindow(KoMainWindow *mainWindow)
{
    debugMain <<"mainWindow" << (void*)mainWindow <<"removed from doc" << this;
    if (mainWindow)
    {
        d->mainWindows.removeAll(mainWindow);
    }
}

const QList<KoMainWindow*>& KoPart::mainWindows() const
{
    return d->mainWindows;
}

int KoPart::mainwindowCount() const
{
    return d->mainWindows.count();
}


KoMainWindow *KoPart::currentMainwindow() const
{
    QWidget *widget = qApp->activeWindow();
    KoMainWindow *mainWindow = qobject_cast<KoMainWindow*>(widget);
    while (!mainWindow && widget)
    {
        widget = widget->parentWidget();
        mainWindow = qobject_cast<KoMainWindow*>(widget);
    }

    if (!mainWindow && mainWindows().size() > 0)
    {
        mainWindow = mainWindows().first();
    }
    return mainWindow;

}

void KoPart::openExistingFile(const QUrl &url)
{
    QApplication::setOverrideCursor(Qt::BusyCursor);
    d->document->openUrl(url);
    d->document->setModified(false);
    QApplication::restoreOverrideCursor();
}

void KoPart::openTemplate(const QUrl &url)
{
    QApplication::setOverrideCursor(Qt::BusyCursor);
    bool ok = d->document->loadNativeFormat(url.toLocalFile());
    d->document->setModified(false);
    d->document->undoStack()->clear();

    if (ok)
    {
        QString mimeType = QMimeDatabase().mimeTypeForUrl(url).name();
        // in case this is a open document template remove the -template from the end
        mimeType.remove( QRegExp( "-template$" ) );
        d->document->setMimeTypeAfterLoading(mimeType);
        deleteOpenPane();
        d->document->resetURL();
        d->document->setEmpty();
    }
    else
    {
        d->document->showLoadingErrorDialog();
        d->document->initEmpty();
    }
    QApplication::restoreOverrideCursor();
}

void KoPart::addRecentURLToAllMainWindows(const QUrl &url)
{
    // Add to recent actions list in our mainWindows
    foreach(KoMainWindow *mainWindow, d->mainWindows)
    {
        mainWindow->addRecentURL(url);
    }

}

void KoPart::showStartUpWidget(KoMainWindow *mainWindow, bool alwaysShow)
{
#ifndef NDEBUG
    if (d->templatesResourcePath.isEmpty())
    {
        debugMain << "showStartUpWidget called, but setTemplatesResourcePath() never called. This will not show a lot";
    }
#endif
    if (!alwaysShow)
    {
        KConfigGroup cfgGrp(componentData().config(), "TemplateChooserDialog");
        QString fullTemplateName = cfgGrp.readPathEntry("AlwaysUseTemplate", QString());
        if (!fullTemplateName.isEmpty())
        {
            QFileInfo fi(fullTemplateName);
            if (!fi.exists())
            {
                const QString templatesResourcePath = this->templatesResourcePath();
                QString desktopfile = KoResourcePaths::findResource("data", templatesResourcePath + "*/" + fullTemplateName);
                if (desktopfile.isEmpty())
                {
                    desktopfile = KoResourcePaths::findResource("data", templatesResourcePath + fullTemplateName);
                }
                if (desktopfile.isEmpty())
                {
                    fullTemplateName.clear();
                }
                else
                {
                    QUrl templateURL;
                    KDesktopFile f(desktopfile);
                    templateURL.setPath(QFileInfo(desktopfile).absolutePath() + '/' + f.readUrl());
                    fullTemplateName = templateURL.toLocalFile();
                }
            }
            if (!fullTemplateName.isEmpty())
            {
                openTemplate(QUrl::fromUserInput(fullTemplateName));
                mainWindows().first()->setRootDocument(d->document, this);
                return;
            }
        }
    }

    mainWindow->factory()->container("mainToolBar", mainWindow)->hide();

    if (d->startUpWidget)
    {
        d->startUpWidget->show();
    }
    else
    {
        d->startUpWidget = createOpenPane(mainWindow, d->templatesResourcePath);
        mainWindow->setCentralWidget(d->startUpWidget);
    }

    mainWindow->setPartToOpen(this);
}

void KoPart::deleteOpenPane(bool closing)
{
    if (d->startUpWidget)
    {
        d->startUpWidget->hide();
        d->startUpWidget->deleteLater();

        if(!closing)
        {
            mainWindows().first()->setRootDocument(d->document, this);
            KoPart::mainWindows().first()->factory()->container("mainToolBar",
                    mainWindows().first())->show();
        }
    }
}

QList<KoPart::CustomDocumentWidgetItem> KoPart::createCustomDocumentWidgets(QWidget * /*parent*/)
{
    return QList<CustomDocumentWidgetItem>();
}

void KoPart::setTemplatesResourcePath(const QString &templatesResourcePath)
{
    Q_ASSERT(!templatesResourcePath.isEmpty());
    Q_ASSERT(templatesResourcePath.endsWith(QLatin1Char('/')));

    d->templatesResourcePath = templatesResourcePath;
}

QString KoPart::templatesResourcePath() const
{
    return d->templatesResourcePath;
}


void KoPart::startCustomDocument()
{
    deleteOpenPane();
}

KoOpenPane *KoPart::createOpenPane(QWidget *parent, const QString& templatesResourcePath)
{
    const QStringList mimeFilter = koApp->mimeFilter(KoFilterManager::Import);

    KoOpenPane *openPane = new KoOpenPane(parent, mimeFilter, templatesResourcePath);
    QList<CustomDocumentWidgetItem> widgetList = createCustomDocumentWidgets(openPane);
    foreach(const CustomDocumentWidgetItem & item, widgetList)
    {
        openPane->addCustomDocumentWidget(item.widget, item.title, item.icon);
        connect(item.widget, SIGNAL(documentSelected()), this, SLOT(startCustomDocument()));
    }
    openPane->show();

    connect(openPane, SIGNAL(openExistingFile(QUrl)), this, SLOT(openExistingFile(QUrl)));
    connect(openPane, SIGNAL(openTemplate(QUrl)), this, SLOT(openTemplate(QUrl)));

    return openPane;
}
