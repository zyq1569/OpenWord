/* This file is part of the KDE project
   Copyright (C) 1998, 1999 Torben Weis <weis@kde.org>
   Copyright (C) 2007 Thomas Zander <zander@kde.org>
   Copyright (C) 2010 Benjamin Port <port.benjamin@gmail.com>

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

#include "KoView.h"

// local directory
#include "KoView_p.h"

#include "KoPart.h"
#include "KoDockRegistry.h"
#include "KoDocument.h"
#include "KoMainWindow.h"

#ifndef QT_NO_DBUS
#include "KoViewAdaptor.h"
#include <QDBusConnection>
#endif

#include "KoDockFactoryBase.h"
#include "KoUndoStackAction.h"
#include "KoGlobal.h"
#include "KoPageLayout.h"
#include "KoPrintJob.h"
#include "KoDocumentInfo.h"

#include <KoIcon.h>

#include <kactioncollection.h>
#include <klocalizedstring.h>
#include <MainDebug.h>
#include <kmessagebox.h>
#include <KoNetAccess.h>
#include <kselectaction.h>
#include <kconfiggroup.h>
#include <KSharedConfig>

#include <QStatusBar>
#include <QDockWidget>
#include <QApplication>
#include <QList>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QImage>
#include <QUrl>
#include <QPrintDialog>

//static
QString KoView::newObjectName()
{
    static int s_viewIFNumber = 0;
    QString name; name.setNum(s_viewIFNumber++); name.prepend("view_");
    return name;
}


class KoViewPrivate
{
public:
    KoViewPrivate() {
        tempActiveWidget = 0;
        documentDeleted = false;
        actionAuthor = 0;
    }
    ~KoViewPrivate() {
    }

    QPointer<KoDocument> document; // our KoDocument
    QPointer<KoPart> part; // our part
    QWidget *tempActiveWidget;
    bool documentDeleted; // true when document gets deleted [can't use document==0
    // since this only happens in ~QObject, and views
    // get deleted by ~KoDocument].


    // Hmm sorry for polluting the private class with such a big inner class.
    // At the beginning it was a little struct :)
    class StatusBarItem
    {
    public:
        StatusBarItem() // for QValueList
            : m_widget(0),
              m_connected(false),
              m_hidden(false) {}

        StatusBarItem(QWidget * widget, int stretch, bool permanent)
            : m_widget(widget),
              m_stretch(stretch),
              m_permanent(permanent),
              m_connected(false),
              m_hidden(false) {}

        bool operator==(const StatusBarItem& rhs) {
            return m_widget == rhs.m_widget;
        }

        bool operator!=(const StatusBarItem& rhs) {
            return m_widget != rhs.m_widget;
        }

        QWidget * widget() const {
            return m_widget;
        }

        void ensureItemShown(QStatusBar * sb) {
            Q_ASSERT(m_widget);
            if (!m_connected) {
                if (m_permanent)
                    sb->addPermanentWidget(m_widget, m_stretch);
                else
                    sb->addWidget(m_widget, m_stretch);

                if(!m_hidden)
                    m_widget->show();

                m_connected = true;
            }
        }
        void ensureItemHidden(QStatusBar * sb) {
            if (m_connected) {
                m_hidden = m_widget->isHidden();
                sb->removeWidget(m_widget);
                m_widget->hide();
                m_connected = false;
            }
        }
    private:
        QWidget * m_widget;
        int m_stretch;
        bool m_permanent;
        bool m_connected;
        bool m_hidden;
    };

    QList<StatusBarItem> statusBarItems; // Our statusbar items
    bool inOperation; //in the middle of an operation (no screen refreshing)?
    KSelectAction *actionAuthor; // Select action for author profile.
};

KoView::KoView(KoPart *part, KoDocument *document, QWidget *parent)
        : QWidget(parent)
        , d(new KoViewPrivate)
{
    Q_ASSERT(document);
    Q_ASSERT(part);

    setObjectName(newObjectName());

#ifndef QT_NO_DBUS
    new KoViewAdaptor(this);
    QDBusConnection::sessionBus().registerObject('/' + objectName(), this);
#endif

    d->document = document;
    d->part = part;

    setFocusPolicy(Qt::StrongFocus);

    setupGlobalActions();

    QStatusBar * sb = statusBar();
    if (sb) { // No statusbar in e.g. konqueror
        connect(d->document, SIGNAL(statusBarMessage(QString)),
                this, SLOT(slotActionStatusText(QString)));
        connect(d->document, SIGNAL(clearStatusBarMessage()),
                this, SLOT(slotClearStatusText()));
    }

    // add all plugins.
    foreach(const QString & docker, KoDockRegistry::instance()->keys()) {
        KoDockFactoryBase *factory = KoDockRegistry::instance()->value(docker);
        if (mainWindow())
            mainWindow()->createDockWidget(factory);
    }

    actionCollection()->addAssociatedWidget(this);

    /**
     * WARNING: This code changes the context of global shortcuts
     *          only. All actions added later will have the default
     *          context, which is Qt::WindowShortcut!
     */
    foreach(QAction* action, actionCollection()->actions()) {
        action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    }
}

KoView::~KoView()
{
    if (!d->documentDeleted) {
        if (d->document) {
            d->part->removeView(this);
        }
    }
    delete d;
}


void KoView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasImage()
            || event->mimeData()->hasUrls()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void KoView::dropEvent(QDropEvent *event)
{
    // we can drop a list of urls from, for instance dolphin
    QVector<QImage> images;

    if (event->mimeData()->hasImage()) {
        QImage image = event->mimeData()->imageData().value<QImage>();
        if (!image.isNull()) {
            // apparently hasImage() && imageData().value<QImage>().isNull()
            // can hold sometimes (Qt bug?).
            images << image;
        }
    }
    else if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        foreach (const QUrl &url, urls) {
            QImage image;
            QUrl kurl(url);
            // make sure we download the files before inserting them
            if (!kurl.isLocalFile()) {
                QString tmpFile;
                if( KIO::NetAccess::download(kurl, tmpFile, this)) {
                    image.load(tmpFile);
                    KIO::NetAccess::removeTempFile(tmpFile);
                } else {
                    KMessageBox::error(this, KIO::NetAccess::lastErrorString());
                }
            }
            else {
                image.load(kurl.toLocalFile());
            }
            if (!image.isNull()) {
                images << image;
            }
        }
    }

    if (!images.isEmpty()) {
        addImages(images, event->pos());
    }
}


void KoView::addImages(const QVector<QImage> &, const QPoint &)
{
    // override in your application
}

KoDocument *KoView::koDocument() const
{
    return d->document;
}

void KoView::setDocumentDeleted()
{
    d->documentDeleted = true;
}

void KoView::addStatusBarItem(QWidget * widget, int stretch, bool permanent)
{
    KoViewPrivate::StatusBarItem item(widget, stretch, permanent);
    QStatusBar * sb = statusBar();
    if (sb) {
        item.ensureItemShown(sb);
    }
    d->statusBarItems.append(item);
}

void KoView::removeStatusBarItem(QWidget *widget)
{
    QStatusBar *sb = statusBar();

    int itemCount = d->statusBarItems.count();
    for (int i = itemCount-1; i >= 0; --i) {
        KoViewPrivate::StatusBarItem &sbItem = d->statusBarItems[i];
        if (sbItem.widget() == widget) {
            if (sb) {
                sbItem.ensureItemHidden(sb);
            }
            d->statusBarItems.removeOne(sbItem);
            break;
        }
    }
}

KoPrintJob * KoView::createPrintJob()
{
    warnMain << "Printing not implemented in this application";
    return 0;
}

KoPrintJob * KoView::createPdfPrintJob()
{
    return createPrintJob();
}

KoPageLayout KoView::pageLayout() const
{
    return koDocument()->pageLayout();
}

QPrintDialog *KoView::createPrintDialog(KoPrintJob *printJob, QWidget *parent)
{
    QPrintDialog *printDialog = new QPrintDialog(&printJob->printer(), parent);
    printDialog->setOptionTabs(printJob->createOptionWidgets());
    printDialog->setMinMax(printJob->printer().fromPage(), printJob->printer().toPage());
    printDialog->setEnabledOptions(printJob->printDialogOptions());
    return printDialog;
}

void KoView::setupGlobalActions()
{
    QAction *undo = actionCollection()->addAction("edit_undo", new KoUndoStackAction(d->document->undoStack(), KoUndoStackAction::UNDO));
    QAction *redo = actionCollection()->addAction("edit_redo", new KoUndoStackAction(d->document->undoStack(), KoUndoStackAction::RED0));

    actionCollection()->setDefaultShortcut(undo, QKeySequence::Undo);
    actionCollection()->setDefaultShortcut(redo, QKeySequence::Redo);
    d->actionAuthor  = new KSelectAction(koIcon("user-identity"), i18n("Active Author Profile"), this);
    connect(d->actionAuthor, SIGNAL(triggered(QString)), this, SLOT(changeAuthorProfile(QString)));
    actionCollection()->addAction("settings_active_author", d->actionAuthor);

    slotUpdateAuthorProfileActions();
}

void KoView::changeAuthorProfile(const QString &profileName)
{
    KConfigGroup appAuthorGroup( KSharedConfig::openConfig(), "Author");
    if (profileName.isEmpty()) {
        appAuthorGroup.writeEntry("active-profile", "");
    } else if (profileName == i18nc("choice for author profile", "Anonymous")) {
        appAuthorGroup.writeEntry("active-profile", "anonymous");
    } else {
        appAuthorGroup.writeEntry("active-profile", profileName);
    }
    appAuthorGroup.sync();
    d->document->documentInfo()->updateParameters();
}

KoMainWindow * KoView::mainWindow() const
{
    // It is possible (when embedded inside a Gemini window) that you have a KoMainWindow which
    // is not the top level window. The code below ensures you can still get access to it, even
    // in that case.
    KoMainWindow* mw = dynamic_cast<KoMainWindow *>(window());
    QWidget* parent = parentWidget();
    while (!mw) {
        mw = dynamic_cast<KoMainWindow*>(parent);
        parent = parent->parentWidget();
        if (!parent) {
            break;
        }
    }
    return mw;
}

QStatusBar * KoView::statusBar() const
{
    KoMainWindow *mw = mainWindow();
    return mw ? mw->statusBar() : 0;
}

void KoView::slotActionStatusText(const QString &text)
{
    QStatusBar *sb = statusBar();
    if (sb)
        sb->showMessage(text);
}

void KoView::slotClearStatusText()
{
    QStatusBar *sb = statusBar();
    if (sb)
        sb->clearMessage();
}

void KoView::slotUpdateAuthorProfileActions()
{
    Q_ASSERT(d->actionAuthor);
    if (!d->actionAuthor) {
        return;
    }
    d->actionAuthor->clear();
    d->actionAuthor->addAction(i18n("Default Author Profile"));
    d->actionAuthor->addAction(i18nc("choice for author profile", "Anonymous"));

    KConfigGroup authorGroup(KoGlobal::calligraConfig(), "Author");
    QStringList profiles = authorGroup.readEntry("profile-names", QStringList());
    foreach (const QString &profile , profiles) {
        d->actionAuthor->addAction(profile);
    }

    KConfigGroup appAuthorGroup( KSharedConfig::openConfig(), "Author");
    QString profileName = appAuthorGroup.readEntry("active-profile", "");
    if (profileName == "anonymous") {
        d->actionAuthor->setCurrentItem(1);
    } else if (profiles.contains(profileName)) {
        d->actionAuthor->setCurrentAction(profileName);
    } else {
        d->actionAuthor->setCurrentItem(0);
    }
}

QList<QAction*> KoView::createChangeUnitActions(bool addPixelUnit)
{
    UnitActionGroup* unitActions = new UnitActionGroup(d->document, addPixelUnit, this);
    return unitActions->actions();
}

void KoView::guiActivateEvent(bool activated)
{
    Q_UNUSED(activated);
}
