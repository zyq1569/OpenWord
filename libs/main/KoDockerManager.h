/* This file is part of the KDE project
 *
 * Copyright (c) 2008 C. Boemann <cbo@boemann.dk>
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

#ifndef KODOCKERMANAGER_H
#define KODOCKERMANAGER_H

#include "komain_export.h"

#include <QObject>
#include <QPointer>

class KoMainWindow;

/**
   The docker manager makes sure that tool option widgets are shown at the right time.
 */
class KOMAIN_EXPORT KoDockerManager : public QObject
{
    Q_OBJECT
public:
    explicit KoDockerManager(KoMainWindow* mainWindow);
    ~KoDockerManager() override;

    void resetToolDockerWidgets();

    void removeToolOptionsDocker();

    /// sets the visibility of the tab and lock icons
    void setIcons(bool enabled);

public Q_SLOTS:
    /**
     * Update the option widgets to the argument ones, removing the currently set widgets.
     */
    void newOptionWidgets(const QList<QPointer<QWidget> > & optionWidgetList);


private:
    Q_PRIVATE_SLOT(d, void restoringDone())
    class Private;
    Private * const d;
};

#include "KoToolDocker.h"

//#include "KoView.h"
#include "KoMainWindow.h"

class Q_DECL_HIDDEN KoDockerManager::Private
{
public:
    Private(KoMainWindow *mw) :
        mainWindow(mw)
        ,ignore(true)
        ,showOptionsDocker(true)
    {
    }

    KoToolDocker *toolOptionsDocker;
    KoMainWindow *mainWindow;
    bool ignore;
    bool showOptionsDocker;

    void restoringDone()
    {
        if (ignore) {
            ignore = false;
            toolOptionsDocker->setVisible(showOptionsDocker);
        }
    }
};

#endif
