/* This file is part of the KDE project
 *
 * Copyright (c) 2008-2012 C. Boemann <cbo@boemann.dk>
 * Copyright (c) 2009 Cyrille Berger <cberger@cberger.net>
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

#include "KoDockerManager.h"
//#include "KoDockerManager_p.h"
#include "KoDockFactoryBase.h"

#include <klocalizedstring.h>
#include <kconfig.h>
#include <kconfiggroup.h>
#include <MainDebug.h>

#include "KoToolDocker.h"
#include "KoDockRegistry.h"

#include "KoView.h"
#include "KoMainWindow.h"

#include <QFontDatabase>

class ToolDockerFactory : public KoDockFactoryBase
{
public:
    ToolDockerFactory() : KoDockFactoryBase() { }

    QString id() const override {
        return "sharedtooldocker";
    }

    QDockWidget* createDockWidget() override {
        KoToolDocker * dockWidget = new KoToolDocker();
        return dockWidget;
    }

    DockPosition defaultDockPosition() const override {
        return DockRight;
    }
};

KoDockerManager::KoDockerManager(KoMainWindow *mainWindow)
    : QObject(mainWindow), d( new Private(mainWindow) )
{
    ToolDockerFactory toolDockerFactory;
    d->toolOptionsDocker =
            qobject_cast<KoToolDocker*>(mainWindow->createDockWidget(&toolDockerFactory));
    Q_ASSERT(d->toolOptionsDocker);
    d->toolOptionsDocker->setVisible(false);

    connect(mainWindow, SIGNAL(restoringDone()), this, SLOT(restoringDone()));
}

KoDockerManager::~KoDockerManager()
{
    delete d;
}

void KoDockerManager::newOptionWidgets(const QList<QPointer<QWidget> > &optionWidgetList)
{
    d->toolOptionsDocker->setOptionWidgets(optionWidgetList);
    QFont dockWidgetFont = KoDockRegistry::dockFont();

    foreach(QWidget *w, optionWidgetList) {
#ifdef Q_OS_MAC
        w->setAttribute(Qt::WA_MacSmallSize, true);
#endif
        w->setFont(dockWidgetFont);
    }



}

void KoDockerManager::removeToolOptionsDocker()
{
    d->toolOptionsDocker->setVisible(false);
    d->showOptionsDocker = false;
}

void KoDockerManager::setIcons(bool enabled)
{
    d->toolOptionsDocker->setTabEnabled(enabled);
}

void KoDockerManager::resetToolDockerWidgets()
{
    d->toolOptionsDocker->resetWidgets();
}

// have to include this because of Q_PRIVATE_SLOT
//#include <moc_KoDockerManager.cpp>
