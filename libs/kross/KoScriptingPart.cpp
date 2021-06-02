/***************************************************************************
 * KoScriptingPart.cpp
 * This file is part of the KDE project
 * copyright (C) 2006-2007 Sebastian Sauer <mail@dipe.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 ***************************************************************************/

#include "KoScriptingPart.h"

#include "KoScriptingModule.h"
#include "KoScriptManager.h"
#include "KoScriptingDocker.h"
#include "KoKrossDebug.h"
// calligra
#include <KoView.h>
#include <KoMainWindow.h>
// KF5
#include <kactioncollection.h>
#include <klocalizedstring.h>
#include <kactionmenu.h>
#include <kmessagebox.h>
#include <kross/core/manager.h>
#include <kross/core/interpreter.h>
#include <kross/core/actioncollection.h>
// Qt
#include <QApplication>
#include <QStandardPaths>
#include <QDirIterator>
#include <QMenu>
#include <QFileDialog>


/// \internal d-pointer class.
class Q_DECL_HIDDEN KoScriptingPart::Private
{
public:
    /**
    * The \a KoScriptingModule instance that provides the base class for
    * Kross module functionality for Calligra applications.
    */
    QPointer<KoScriptingModule> module;

    /**
    * The \a KActionMenu instance that provides a menu of all enabled
    * collections and there actions as tree.
    */
    KActionMenu *scriptsmenu;

    /**
    * The list of \a Kross::Action instances this \a KoScriptingPart instance
    * owns. Each action is executed within a specific part instance where
    * each part has exactly one \a KoView instance. That way we are able to bind
    * a script explicit to a specific view.
    */
    QList<Kross::Action*> actions;
};

KoScriptingPart::KoScriptingPart(KoScriptingModule *const module)
    : d(new Private())
{
    d->module = module;
    Q_ASSERT(d->module);

    QAction *execAction  = new QAction(i18n("Execute Script File..."), this);
    actionCollection()->addAction("executescriptfile", execAction);
    connect(execAction, SIGNAL(triggered(bool)), this, SLOT(slotShowExecuteScriptFile()));

    d->scriptsmenu = new KActionMenu(i18n("Scripts"), this);
    actionCollection()->addAction("scripts", d->scriptsmenu);
    connect(d->scriptsmenu->menu(), SIGNAL(aboutToShow()), this, SLOT(slotMenuAboutToShow()));

    QAction *manageraction  = new QAction(i18n("Script Manager..."), this);
    actionCollection()->addAction("scriptmanager", manageraction);
    connect(manageraction, SIGNAL(triggered(bool)), this, SLOT(slotShowScriptManager()));

    connect(&Kross::Manager::self(), SIGNAL(started(Kross::Action*)), this, SLOT(slotStarted(Kross::Action*)));
    //connect(&Kross::Manager::self(), SIGNAL(finished(Kross::Action*)), this, SLOT(slotFinished(Kross::Action*)));

    if (Kross::Manager::self().property("configfile") == QVariant::Invalid)
    {
        QString file = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QStringLiteral("/scripts/scripts.rc");
        QStringList files;
        const QStringList dirs = QStandardPaths::locateAll(QStandardPaths::DataLocation, "scripts", QStandardPaths::LocateDirectory);
        foreach(const QString& dir, dirs)
        {
            QDirIterator it(dir, QStringList() << QStringLiteral("*.rc"));
            while (it.hasNext())
            {
                files.append(it.next());
            }
        }

        Kross::Manager::self().setProperty("configfile", file);
        Kross::Manager::self().setProperty("configfiles", files);

        if (QFileInfo(file).exists())
        {
            Kross::Manager::self().actionCollection()->readXmlFile(file);
        }
        else
        {
            foreach(const QString &f, files)
            {
                Kross::Manager::self().actionCollection()->readXmlFile(f);
            }
        }
    }

    KoView *view = d->module->view();
    KoMainWindow *mainwindow = view ? view->mainWindow() : 0;
    if (mainwindow)
    {
        KoScriptingDockerFactory factory(mainwindow);
        mainwindow->createDockWidget(&factory);
    }

    if (view)
    {
        if (Kross::ActionCollection *c = Kross::Manager::self().actionCollection()->collection("docker"))
        {
            foreach (Kross::Action *a, c->actions())
            {
                if (! a->isEnabled())
                {
                    continue;
                }
                a->addObject(d->module);
                KoScriptingDockerFactory f(view, d->module, a);
                if (mainwindow)
                {
                    mainwindow->createDockWidget(&f);
                }
                debugKoKross << "Adding scripting docker with id=" << f.id();
            }
        }
    }
}

KoScriptingPart::~KoScriptingPart()
{
    foreach(Kross::Action *action, d->actions)
    {
        if (action)
        {
            action->finalize();
        }
    }
    delete d;
}

KoScriptingModule *KoScriptingPart::module() const
{
    return d->module;
}

bool KoScriptingPart::showExecuteScriptFile()
{
    QStringList mimetypes;
    foreach (const QString &interpretername, Kross::Manager::self().interpreters())
    {
        Kross::InterpreterInfo *info = Kross::Manager::self().interpreterInfo(interpretername);
        Q_ASSERT(info);
        mimetypes.append(info->mimeTypes());
    }
    QFileDialog filedialog;
    //QT5TODO: QUrl("kfiledialog:///KrossExecuteScript"), // startdir
    filedialog.setMimeTypeFilters(mimetypes);
    filedialog.setWindowTitle(i18n("Execute Script File"));
    filedialog.setFileMode(QFileDialog::ExistingFile);
    if (filedialog.exec())
    {
        Kross::Action action(this, "Execute Script File");
        action.addObject(d->module);

        action.setFile(filedialog.selectedUrls().at(0).path());
        action.trigger();

        return true;
    }

    return false;
}

void addMenu(QMenu *menu, Kross::ActionCollection *collection)
{
    foreach (Kross::Action *a, collection->actions())
    {
        if(a->isEnabled())
        {
            menu->addAction(a);
        }
    }
    foreach (const QString &collectionname, collection->collections())
    {
        Kross::ActionCollection *c = collection->collection(collectionname);
        if (c->isEnabled())
        {
            addMenu(menu->addMenu(c->text()), c);
        }
    }
}

void KoScriptingPart::slotMenuAboutToShow()
{
    d->scriptsmenu->menu()->clear();
    addMenu(d->scriptsmenu->menu(), Kross::Manager::self().actionCollection());
}

void KoScriptingPart::slotShowExecuteScriptFile()
{
    showExecuteScriptFile();
}

void KoScriptingPart::slotShowScriptManager()
{
    KoScriptManagerDialog *dialog = new KoScriptManagerDialog();
    dialog->exec();
    dialog->delayedDestruct();
}

void KoScriptingPart::slotStarted(Kross::Action *action)
{
    debugKoKross << "action=" << action->objectName();
    KoMainWindow *mainwin = dynamic_cast<KoMainWindow*>(qApp->activeWindow());
    KoView *view = d->module ? d->module->view() : 0;
    if (view && mainwin && view->mainWindow() == mainwin && view == mainwin->rootView())
    {
        action->addObject(d->module);
        d->actions.append(action);
        connect(action, SIGNAL(finished(Kross::Action*)), this, SLOT(slotFinished(Kross::Action*)));
        connect(action, SIGNAL(finalized(Kross::Action*)), this, SLOT(slotFinalized(Kross::Action*)));
        myStarted(action);
    }
}

void KoScriptingPart::slotFinished(Kross::Action *action)
{
    debugKoKross <<"KoScriptingPart::slotFinished action=" << action->objectName();
    disconnect(action, SIGNAL(finished(Kross::Action*)), this, SLOT(slotFinished(Kross::Action*)));
    if (d->module && d->module == action->object(d->module->objectName()))
    {
        //d->view->document()->setModified(true);
        //QApplication::restoreOverrideCursor();
        KoView *view = d->module ? d->module->view() : 0;
        if (view && view->mainWindow() /* && view == view->mainWindow()->rootView() */)
        {
            if (action->hadError())
            {
                if (action->errorTrace().isNull())
                {
                    KMessageBox::error(view, action->errorMessage());
                }
                else
                {
                    KMessageBox::detailedError(view, action->errorMessage(), action->errorTrace());
                }
            }
        }
        myFinished(action);
    }
}

void KoScriptingPart::slotFinalized(Kross::Action *action)
{
    debugKoKross << "action=" << action->objectName();
    disconnect(action, SIGNAL(finalized(Kross::Action*)), this, SLOT(slotFinalized(Kross::Action*)));
    d->actions.removeAll(action);
    if (d->module && d->module == action->object(d->module->objectName()))
    {
        myFinalized(action);
    }
}
