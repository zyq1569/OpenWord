/* This file is part of the KDE project
   Copyright (C) 1998, 1999 Torben Weis <weis@kde.org>

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

#ifndef __ko_app_h__
#define __ko_app_h__

#include "logging.h"
#include <QApplication>

#include "komain_export.h"
#include "KoMainWindow.h"

class KoPart;

class KoApplicationPrivate;
class KAboutData;

class QWidget;
class QStringList;

//class Hsharedmemory;
///add 20220714
#include "Hsharedmemory.h"
class HreadThread;
#include <KoFilterManager.h>

#define koApp KoApplication::koApplication()

typedef KAboutData* (*AboutDataGenerator)();

/**
 *  @brief Base class for all %Calligra apps
 *
 *  This class handles arguments given on the command line and
 *  shows a generic about dialog for all Calligra apps.
 *
 *  In addition it adds the standard directories where Calligra applications
 *  can find their images etc.
 *
 *  If the last mainwindow becomes closed, KoApplication automatically
 *  calls QApplication::quit.
 */
class KOMAIN_EXPORT KoApplication : public QApplication
{
    Q_OBJECT

public:
    /**
     * Creates an application object, adds some standard directories and
     * initializes kimgio.
     *
     * @param nativeMimeType: the nativeMimeType of the Calligra application
     * @param windowIconName xdg-spec name of the icon to be set for windows
     * @param aboutDataGenerator method to create the KAboutData for the app
     * @param argc number of commandline argument strings in @c argv
     * @param argv array of commandline argument strings
     */
    explicit KoApplication(const QByteArray &nativeMimeType, const QString &windowIconName,  AboutDataGenerator aboutDataGenerator, int &argc, char **argv);

    /**
     *  Destructor.
     */
    ~KoApplication() override;

    /**
     * Call this to start the application.
     *
     * Parses command line arguments and creates the initial main windows and docs
     * from them (or an empty doc if no cmd-line argument is specified ).
     *
     * You must call this method directly before calling QApplication::exec.
     *
     * It is valid behaviour not to call this method at all. In this case you
     * have to process your command line parameters by yourself.
     */
    virtual bool start();

    bool startHEditor();

    /**
     * Tell KoApplication to show this splashscreen when you call start();
     * when start returns, the splashscreen is hidden. Use KSplashScreen
     * to have the splash show correctly on Xinerama displays. 
     */
    void setSplashScreen(QWidget *splash);


    QList<KoPart*> partList() const;

    /**
     * return a list of mimetypes this application supports.
     */
    QStringList mimeFilter(KoFilterManager::Direction direction) const;

    // Overridden to handle exceptions from event handlers.
    bool notify(QObject *receiver, QEvent *event) override;

    /**
     * Returns the current application object.
     *
     * This is similar to the global QApplication pointer qApp. It
     * allows access to the single global KoApplication object, since
     * more than one cannot be created in the same application. It
     * saves you the trouble of having to pass the pointer explicitly
     * to every function that may require it.
     * @return the current application object
     */
    static KoApplication* koApplication();

Q_SIGNALS:

    /// KoPart needs to be able to emit document signals from here. These
    /// signals are used for the dbus interface of stage, see commit
    /// d102d9beef80cc93fc9c130b0ad5fe1caf238267
    friend class KoPart;

    /**
     * emitted when a new document is opened.
     */
    void documentOpened(const QString &ref);

    /**
     * emitted when an old document is closed.
     */
    void documentClosed(const QString &ref);

private Q_SLOTS:
    void benchmarkLoadingFinished();
    void slotFilePrint(KoMainWindow *view);
    void slotExportToPdf(KoMainWindow *view);

protected:
    // Current application object.
    static KoApplication *KoApp;

private:
    bool initHack();
    KoApplicationPrivate * const d;
    class ResetStarting;
    friend class ResetStarting;

    ///to do: 改成非成员变量
private:
    Hsharedmemory m_sharedmemory;
    HreadThread *m_hreadThread;
};

#endif
