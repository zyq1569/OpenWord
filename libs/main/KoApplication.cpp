/* This file is part of the KDE project
   Copyright (C) 1998, 1999 Torben Weis <weis@kde.org>
   Copyright (C) 2009 Thomas Zander <zander@kde.org>
   Copyright (C) 2012 Boudewijn Rempt <boud@valdyas.org>

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



#include "KoApplication.h"

#include "KoGlobal.h"

#ifndef QT_NO_DBUS
#include "KoApplicationAdaptor.h"
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusConnectionInterface>
#endif

#include "KoPrintJob.h"
#include "KoDocumentEntry.h"
#include "KoDocument.h"
#include "KoMainWindow.h"
#include "KoAutoSaveRecoveryDialog.h"
#include <KoDpi.h>
#include "KoPart.h"
#include <KoPluginLoader.h>
#include <KoConfig.h>
#include <KoResourcePaths.h>
#include <KoComponentData.h>

#include <klocalizedstring.h>
#include <kdesktopfile.h>
#include <kmessagebox.h>
#include <kiconloader.h>
#include <MainDebug.h>
#include <kconfig.h>
#include <kconfiggroup.h>
#include <krecentdirs.h>
#include <KAboutData>
#include <KSharedConfig>
#include <KDBusService>

#include <QFile>
#include <QWidget>
#include <QSysInfo>
#include <QStringList>
#include <QProcessEnvironment>
#include <QDir>
#include <QPluginLoader>
#include <QCommandLineParser>
#include <QMimeDatabase>
#include <QTimer>

#include <stdlib.h>

#ifdef Q_OS_WIN
#include <windows.h>
#include <tchar.h>
#endif


#include "MainDebug.h"
#include <QDesktopWidget>

KoApplication* KoApplication::KoApp = 0;

namespace
{
const QTime appStartTime(QTime::currentTime());
}

class KoApplicationPrivate
{
public:
    KoApplicationPrivate()
        : splashScreen(0)
    {}
    QByteArray nativeMimeType;
    QWidget *splashScreen;
    QList<KoPart *> partList;
    QString roundtripFileName;
    QString pdfFileName;
};

class KoApplication::ResetStarting
{
public:
    ResetStarting(QWidget *splash = 0)
        : m_splash(splash)
    {
    }

    ~ResetStarting()
    {
        if (m_splash)
        {

            KConfigGroup cfg( KSharedConfig::openConfig(), "SplashScreen");
            bool hideSplash = cfg.readEntry("HideSplashAfterStartup", false);
            if (hideSplash)
            {
                m_splash->hide();
            }
            else
            {
                m_splash->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
                QRect r(QPoint(), m_splash->size());
                m_splash->move(QApplication::desktop()->screenGeometry().center() - r.center());
                m_splash->setWindowTitle(qAppName());
                foreach(QObject *o, m_splash->children())
                {
                    QWidget *w = qobject_cast<QWidget*>(o);
                    if (w && w->isHidden())
                    {
                        w->setVisible(true);
                    }
                }

                m_splash->show();
            }
        }
    }

    QWidget *m_splash;
};


KoApplication::KoApplication(const QByteArray &nativeMimeType,
                             const QString &windowIconName,
                             AboutDataGenerator aboutDataGenerator,
                             int &argc, char **argv)
    : QApplication(argc, argv)
    , d(new KoApplicationPrivate())
{

    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    QScopedPointer<KAboutData> aboutData(aboutDataGenerator());
    KAboutData::setApplicationData(*aboutData);

    setWindowIcon(QIcon::fromTheme(windowIconName, windowIcon()));

    KoApplication::KoApp = this;

    d->nativeMimeType = nativeMimeType;
    DEBUG_LOG("Tell the iconloader about share/apps/calligra/icons : KIconLoader::global()->addAppDir(\"calligra\")");
    // Tell the iconloader about share/apps/calligra/icons
    KIconLoader::global()->addAppDir("calligra");

    // Initialize all Calligra directories etc.
    KoGlobal::initialize();

#ifndef QT_NO_DBUS
    if (_WIN32 || _WIN64)
    {
        ERROR_LOG( "KDBusService service(KDBusService::Multiple); error! in windows!");
        errorMain << "KDBusService service(KDBusService::Multiple); error! in windows!" << endl;
    }
    else
    {
        ///----- openword : not start ???? why (in windows)???
        KDBusService service(KDBusService::Multiple);
        new KoApplicationAdaptor(this);
        QDBusConnection::sessionBus().registerObject("/application", this);
    }

#endif

#ifdef Q_OS_MACX
    if ( QSysInfo::MacintoshVersion > QSysInfo::MV_10_8 )
    {
        // fix Mac OS X 10.9 (mavericks) font issue
        // https://bugreports.qt-project.org/browse/QTBUG-32789
        QFont::insertSubstitution(".Lucida Grande UI", "Lucida Grande");
    }

    setAttribute(Qt::AA_DontShowIconsInMenus, true);
#endif
}

#if defined(Q_OS_WIN) && defined(ENV32BIT)
typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

LPFN_ISWOW64PROCESS fnIsWow64Process;

BOOL isWow64()
{
    BOOL bIsWow64 = FALSE;

    //IsWow64Process is not available on all supported versions of Windows.
    //Use GetModuleHandle to get a handle to the DLL that contains the function
    //and GetProcAddress to get a pointer to the function if available.

    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
                           GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

    if(0 != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}
#endif

bool KoApplication::start()
{
    KAboutData aboutData = KAboutData::applicationData();
    // process commandline parameters
    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("print"), i18n("Only print and exit")));
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("template"), i18n("Open a new document based on the given template (desktopfile name)")));
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("new"), i18n("Open a new document based on the given template file")));
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("dpi"), i18n("Override display DPI"), QStringLiteral("dpiX,dpiY")));
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("export-pdf"), i18n("Only export to PDF and exit")));
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("export-filename"), i18n("Filename for export-pdf"), QStringLiteral("filename")));
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("benchmark-loading"), i18n("just load the file and then exit")));
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("benchmark-loading-show-window"), i18n("load the file, show the window and progressbar and then exit")));
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("profile-filename"), i18n("Filename to write profiling information into."), QStringLiteral("filename")));
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("roundtrip-filename"), i18n("Load a file and save it as an ODF file. Meant for debugging."), QStringLiteral("filename")));
    parser.addPositionalArgument(QStringLiteral("[file(s)]"), i18n("File(s) or URL(s) to open"));

    parser.process(*this);

    aboutData.processCommandLine(&parser);

#if defined(Q_OS_WIN) || defined (Q_OS_MACX)
#ifdef ENV32BIT
    if (isWow64())
    {
        KMessageBox::information(0,
                                 i18n("You are running a 32 bits build on a 64 bits Windows.\n"
                                      "This is not recommended.\n"
                                      "Please download and install the x64 build instead."),
                                 qApp->applicationName(),
                                 "calligra_32_on_64_warning");

    }
#endif
    QDir appdir(applicationDirPath());
    appdir.cdUp();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if (!env.contains("XDG_DATA_DIRS"))
    {
        qputenv("XDG_DATA_DIRS", QFile::encodeName(appdir.absolutePath() + "/share"));
    }
    qputenv("PATH", QFile::encodeName(appdir.absolutePath() + "/bin" + ";"
                                      + appdir.absolutePath() + "/lib" + ";"
                                      + appdir.absolutePath() + "/lib/kde4" + ";"
                                      + appdir.absolutePath() + "/Frameworks" + ";"
                                      + appdir.absolutePath()));
#endif

    if (d->splashScreen)
    {
        d->splashScreen->show();
        d->splashScreen->repaint();
        processEvents();
    }

    ResetStarting resetStarting(d->splashScreen); // remove the splash when done
    Q_UNUSED(resetStarting);

    // Find the part component file corresponding to the application instance name
    /// 2021-01-08 plugin error? --->json??
    KoDocumentEntry entry;
    QList<QPluginLoader*> pluginLoaders = KoPluginLoader::pluginLoaders("calligra/parts", d->nativeMimeType);
    Q_FOREACH (QPluginLoader *loader, pluginLoaders)
    {
        if (loader->fileName().contains(applicationName()+QString("part")))
        {
            entry = KoDocumentEntry(loader);
            pluginLoaders.removeOne(loader);
            break;
        }
    }
    qDeleteAll(pluginLoaders);

    if (entry.isEmpty())
    {
        QMessageBox::critical(0, i18n("%1: Critical Error", applicationName()), i18n("Essential application components could not be found.\n"
                              "This might be an installation issue.\n"
                              "Try restarting or reinstalling."));
        return false;
    }

    // Get the command line arguments which we have to parse
    QString dpiValues = parser.value("dpi");
    if (!dpiValues.isEmpty())
    {
        int sep = dpiValues.indexOf(QRegExp("[x, ]"));
        int dpiX;
        int dpiY = 0;
        bool ok = true;
        if (sep != -1)
        {
            dpiY = dpiValues.mid(sep + 1).toInt(&ok);
            dpiValues.truncate(sep);
        }
        if (ok)
        {
            dpiX = dpiValues.toInt(&ok);
            if (ok)
            {
                if (!dpiY)
                {
                    dpiY = dpiX;
                }
                KoDpi::setDPI(dpiX, dpiY);
            }
        }
    }
    // No argument -> create an empty document
    const QStringList fileUrls = parser.positionalArguments();

    if (fileUrls.isEmpty())
    {
        // if there's no document, add the current working directory
        // to the recent dirs so the open dialog and open pane show
        // the directory from where the app was started, instead of
        // the last directory from where we opened a file
        KRecentDirs::add(":OpenDialog", QDir::currentPath());
        QString errorMsg;
        KoPart *part = entry.createKoPart(&errorMsg);
        d->partList << part;

        if (!part)
        {
            if (!errorMsg.isEmpty())
            {
                KMessageBox::error(0, errorMsg);
            }
            return false;
        }

        // XXX: the document should be separate plugin
        KoDocument *doc = part->document();

        KoMainWindow *mainWindow = part->createMainWindow();
        ///mainWindow->setWindowTitle("Test Openword");
        ///mainWindow->setCaption("Test Openword",true);
        mainWindow->show();
        QObject::connect(doc, SIGNAL(sigProgress(int)), mainWindow, SLOT(slotProgress(int)));
        // for initDoc to fill in the recent docs list
        // and for KoDocument::slotStarted
        part->addMainWindow(mainWindow);

        // Check for autosave files from a previous run. There can be several, and
        // we want to offer a restore for every one. Including a nice thumbnail!
        QStringList autoSaveFiles;

        // get all possible autosave files in the home dir, this is for unsaved document autosave files
        // Using the extension allows to avoid relying on the mime magic when opening
        QMimeType mimeType = QMimeDatabase().mimeTypeForName(doc->nativeFormatMimeType());
        if (!mimeType.isValid())
        {
            qFatal("It seems your installation is broken/incomplete because we failed to load the native mimetype \"%s\".", doc->nativeFormatMimeType().constData());
            FATAL_LOG(QString("It seems your installation is broken/incomplete because we failed to load the native mimetype \"%s\". ").
                      arg(doc->nativeFormatMimeType().constData()));
        }
        const QString extension = mimeType.preferredSuffix();

        QStringList filters;
        filters << QString(".%1-%2-%3-autosave%4").arg(part->componentData().componentName()).arg("*").arg("*").arg(extension);

#ifdef Q_OS_WIN
        QDir autosaveDir = QDir::tempPath();
#else
        QDir autosaveDir = QDir::home();
#endif
        // all autosave files for our application
        autoSaveFiles = autosaveDir.entryList(filters, QDir::Files | QDir::Hidden);

        QStringList pids;
        QString ourPid;
        ourPid.setNum(applicationPid());

#ifndef QT_NO_DBUS
        // all running instances of our application -- bit hackish, but we cannot get at the dbus name here, for some reason
        ///QDBusReply<QStringList> reply = QDBusConnection::sessionBus().interface()->registeredServiceNames();
        //foreach (const QString &name, reply.value()) ///openword
        //{
        //    if (name.contains(part->componentData().componentName())) {
        //        // we got another instance of ourselves running, let's get the pid
        //        QString pid = name.split('-').last();
        //        if (pid != ourPid) {
        //            pids << pid;
        //        }
        //    }
        //}
#endif

        // remove the autosave files that are saved for other, open instances of ourselves
        foreach(const QString &autoSaveFileName, autoSaveFiles)
        {
            if (!QFile::exists(autosaveDir.absolutePath() + QDir::separator() + autoSaveFileName))
            {
                autoSaveFiles.removeAll(autoSaveFileName);
                continue;
            }
            QStringList split = autoSaveFileName.split('-');
            if (split.size() == 4)
            {
                if (pids.contains(split[1]))
                {
                    // We've got an active, owned autosave file. Remove.
                    autoSaveFiles.removeAll(autoSaveFileName);
                }
            }
        }

        // Allow the user to make their selection
        if (autoSaveFiles.size() > 0)
        {
            KoAutoSaveRecoveryDialog dlg(autoSaveFiles);
            if (dlg.exec() == QDialog::Accepted)
            {
                QStringList filesToRecover = dlg.recoverableFiles();
                foreach (const QString &autoSaveFileName, autoSaveFiles)
                {
                    if (!filesToRecover.contains(autoSaveFileName))
                    {
                        // remove the files the user didn't want to recover
                        QFile::remove(autosaveDir.absolutePath() + QDir::separator() + autoSaveFileName);
                    }
                }
                autoSaveFiles = filesToRecover;
            }
            else
            {
                // don't recover any of the files, but don't delete them either
                autoSaveFiles.clear();
            }
        }

        if (autoSaveFiles.size() > 0)
        {
            short int numberOfOpenDocuments = 0; // number of documents open
            // bah, we need to re-use the document that was already created
            QUrl url = QUrl::fromLocalFile(autosaveDir.absolutePath() + QDir::separator() + autoSaveFiles.takeFirst());
            if (mainWindow->openDocument(part, url))
            {
                doc->resetURL();
                doc->setModified(true);
                // TODO: what if the app crashes immediately, before another autosave was made? better keep & rename
                QFile::remove(url.toLocalFile());
                numberOfOpenDocuments++;
            }

            // And then for the other autosave files, we copy & paste the code
            // and loop through them.
            foreach(const QString &autoSaveFile, autoSaveFiles)
            {
                // For now create an empty document
                QString errorMsg;
                KoPart *part = entry.createKoPart(&errorMsg);
                d->partList << part;
                if (part)
                {
                    url = QUrl::fromLocalFile(autosaveDir.absolutePath() + QDir::separator() + autoSaveFile);

                    KoMainWindow *mainWindow = part->createMainWindow();
                    mainWindow->show();
                    if (mainWindow->openDocument(part, url))
                    {
                        doc->resetURL();
                        doc->setModified(true);
                        // TODO: what if the app crashes immediately, before another autosave was made? better keep & rename
                        QFile::remove(url.toLocalFile());
                        numberOfOpenDocuments++;
                    }
                }
            }
            return (numberOfOpenDocuments > 0);
        }
        else
        {
            part->showStartUpWidget(mainWindow);
        }

    }
    else
    {
        const bool print = parser.isSet("print");
        const bool exportAsPdf = parser.isSet("export-pdf");
        d->pdfFileName = parser.value("export-filename");
        d->roundtripFileName = parser.value("roundtrip-filename");
        const bool doTemplate = parser.isSet("template");
        const bool doNew = parser.isSet("new");
        const bool benchmarkLoading = parser.isSet("benchmark-loading")
                                      || parser.isSet("benchmark-loading-show-window")
                                      || !d->roundtripFileName.isEmpty();
        // only show the mainWindow when no command-line mode option is passed
        const bool showmainWindow =
            parser.isSet("benchmark-loading-show-window") || (
                parser.isSet("export-pdf")) || (
                !parser.isSet("benchmark-loading")
                && !parser.isSet("roundtrip-filename")
                && d->roundtripFileName.isEmpty());
        const QString profileFileName = parser.value("profile-filename");

        QTextStream profileoutput;
        QFile profileFile(profileFileName);
        if (!profileFileName.isEmpty()
                && profileFile.open(QFile::WriteOnly | QFile::Truncate))
        {
            profileoutput.setDevice(&profileFile);
        }

        // Loop through arguments

        short int numberOfOpenDocuments = 0; // number of documents open
        short int nPrinted = 0;
        // TODO: remove once Qt has proper handling itself
        const QRegExp withProtocolChecker( QStringLiteral("^[a-zA-Z]+:") );
        for (int argNumber = 0; argNumber < fileUrls.size(); ++argNumber)
        {
            const QString fileUrl = fileUrls.at(argNumber);
            // convert to an url
            const bool startsWithProtocol = (withProtocolChecker.indexIn(fileUrl) == 0);
            const QUrl url = startsWithProtocol ?
                             QUrl::fromUserInput(fileUrl) :
                             QUrl::fromLocalFile(QDir::current().absoluteFilePath(fileUrl));

            // For now create an empty document
            QString errorMsg;
            KoPart *part = entry.createKoPart(&errorMsg);
            d->partList << part;
            if (part)
            {
                KoDocument *doc = part->document();
                // show a mainWindow asap
                KoMainWindow *mainWindow = part->createMainWindow();
                if (showmainWindow)
                {
                    mainWindow->show();
                }
                if (benchmarkLoading)
                {
                    doc->setReadWrite(false);
                }

                if (profileoutput.device())
                {
                    doc->setProfileStream(&profileoutput);
                    profileoutput << "KoApplication::start\t"
                                  << appStartTime.msecsTo(QTime::currentTime())
                                  <<"\t0" << endl;
                    doc->setAutoErrorHandlingEnabled(false);
                }
                doc->setProfileReferenceTime(appStartTime);

                // are we just trying to open a Calligra-style template?
                if (doTemplate)
                {
                    QString templatePath;
                    if (url.isLocalFile() && QFile::exists(url.toLocalFile()))
                    {
                        templatePath = url.toLocalFile();
                        debugMain << "using full path...";
                        DEBUG_LOG("using full path...:"+templatePath);
                    }
                    else
                    {
                        QString desktopName(fileUrls.at(argNumber));
                        const QString templatesResourcePath = part->templatesResourcePath();

                        QStringList paths = KoResourcePaths::findAllResources("data", templatesResourcePath + "*/" + desktopName);
                        if (paths.isEmpty())
                        {
                            paths = KoResourcePaths::findAllResources("data", templatesResourcePath + desktopName);
                        }
                        if (paths.isEmpty())
                        {
                            KMessageBox::error(0, i18n("No template found for: %1", desktopName));
                            delete mainWindow;
                        }
                        else if (paths.count() > 1)
                        {
                            KMessageBox::error(0, i18n("Too many templates found for: %1", desktopName));
                            delete mainWindow;
                        }
                        else
                        {
                            templatePath = paths.at(0);
                        }
                    }

                    if (!templatePath.isEmpty())
                    {
                        QUrl templateBase;
                        templateBase.setPath(templatePath);
                        KDesktopFile templateInfo(templatePath);

                        QString templateName = templateInfo.readUrl();
                        QUrl templateURL;
                        templateURL.setPath(templateBase.adjusted(QUrl::RemoveFilename|QUrl::StripTrailingSlash).path() + '/' + templateName);
                        if (mainWindow->openDocument(part, templateURL))
                        {
                            doc->resetURL();
                            doc->setEmpty();
                            doc->setTitleModified();
                            debugMain << "Template loaded...";
                            DEBUG_LOG("using full path...:" + templateURL.toString());
                            numberOfOpenDocuments++;
                        }
                        else
                        {
                            KMessageBox::error(0, i18n("Template %1 failed to load.", templateURL.toDisplayString()));
                            delete mainWindow;
                        }
                    }
                    // now try to load
                }
                else if (doNew)
                {
                    if (url.isLocalFile() && !QFile::exists(url.toLocalFile()))
                    {
                        KMessageBox::error(0, i18n("No template found at: %1", url.toDisplayString()));
                        delete mainWindow;
                    }
                    else
                    {
                        if (mainWindow->openDocument(part, url))
                        {
                            doc->resetURL();
                            doc->setEmpty();
                            doc->setTitleModified();
                            debugMain << "Template loaded...";
                            numberOfOpenDocuments++;
                        }
                        else
                        {
                            KMessageBox::error(0, i18n("Template %1 failed to load.", url.toDisplayString()));
                            delete mainWindow;
                        }
                    }
                }
                else
                {
                    if (print)
                    {
                        connect( mainWindow, SIGNAL(loadCompleted(KoMainWindow *)),
                                 this, SLOT(slotFilePrint(KoMainWindow *)));
                    }
                    else if (exportAsPdf)
                    {
                        connect(mainWindow, SIGNAL(loadCompleted(KoMainWindow*)),
                                this, SLOT(slotExportToPdf(KoMainWindow*)));
                    }
                    if (mainWindow->openDocument(part, url))
                    {
                        if (benchmarkLoading)
                        {
                            if (profileoutput.device())
                            {
                                profileoutput << "KoApplication::start\t"
                                              << appStartTime.msecsTo(QTime::currentTime())
                                              <<"\t100" << endl;
                            }
                            QTimer::singleShot(0, this, SLOT(benchmarkLoadingFinished()));
                            return true; // only load one document!
                        }
                        if (print || exportAsPdf)
                        {
                            nPrinted++;
                        }
                        else
                        {
                            numberOfOpenDocuments++;
                        }
                    }
                    else
                    {
                        // .... if failed
                        // delete doc; done by openDocument
                        // delete mainWindow; done by ~KoDocument
                    }
                }

                if (profileoutput.device())
                {
                    profileoutput << "KoApplication::start\t"
                                  << appStartTime.msecsTo(QTime::currentTime())
                                  <<"\t100" << endl;
                }

            }
        }
        if (benchmarkLoading)
        {
            return false; // no valid urls found.
        }
        if (print || exportAsPdf)
        {
            return nPrinted > 0;
        }
        if (numberOfOpenDocuments == 0) // no doc, e.g. all URLs were malformed
        {
            return false;
        }
    }

    // not calling this before since the program will quit there.
    return true;
}

KoApplication::~KoApplication()
{
    delete d;
}

void KoApplication::benchmarkLoadingFinished()
{
    KoPart *part = d->partList.value(0);
    if (!part)
    {
        return;
    }
    KoMainWindow *mainWindow = part->mainWindows().value(0);
    if (!mainWindow)
    {
        return;
    }
    if (!d->roundtripFileName.isEmpty())
    {
        part->document()->saveAs(QUrl("file:" + d->roundtripFileName));
    }
    // close the document
    mainWindow->slotFileQuit();
}

void KoApplication::setSplashScreen(QWidget *splashScreen)
{
    d->splashScreen = splashScreen;
}

QList<KoPart*> KoApplication::partList() const
{
    return d->partList;
}

QStringList KoApplication::mimeFilter(KoFilterManager::Direction direction) const
{
    KoDocumentEntry entry = KoDocumentEntry::queryByMimeType(d->nativeMimeType);
    QJsonObject json = entry.metaData();
#ifdef CALLIGRA_OLD_PLUGIN_METADATA

    QStringList mimeTypes = json.value("X-KDE-ExtraNativeMimeTypes").toString().split(',');

#else

    QStringList mimeTypes = json.value("X-KDE-ExtraNativeMimeTypes").toVariant().toStringList();

#endif

    return KoFilterManager::mimeFilter(d->nativeMimeType, direction, mimeTypes);
}


bool KoApplication::notify(QObject *receiver, QEvent *event)
{
    try
    {
        return QApplication::notify(receiver, event);
    }
    catch (std::exception &e)
    {
        qWarning("Error %s sending event %i to object %s",
                 e.what(), event->type(), qPrintable(receiver->objectName()));
    }
    catch (...)
    {
        qWarning("Error <unknown> sending event %i to object %s",
                 event->type(), qPrintable(receiver->objectName()));
    }
    return false;

}

void KoApplication::slotFilePrint(KoMainWindow *mainWindow)
{
    mainWindow->slotFilePrint();
    //delete mainWindow; done by ~KoDocument
}

void KoApplication::slotExportToPdf(KoMainWindow *mainWindow)
{
    KoPrintJob *job = mainWindow->exportToPdf(d->pdfFileName);
    // TODO: exit if all jobs over
}

KoApplication *KoApplication::koApplication()
{
    return KoApp;
}
