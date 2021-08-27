/* This file is part of the KDE project
   Copyright (C) 1998, 1999 Torben Weis <weis@kde.org>
   Copyright (C) 2000-2004 David Faure <faure@kde.org>

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
   Boston, MA 02110-1301, USA.
*/

#ifndef KOMAINWINDOW_H
#define KOMAINWINDOW_H

#include "komain_export.h"

#include <QSharedMemory>
#include <kxmlguiwindow.h>
#include <KoCanvasObserverBase.h>
#include <KoCanvasSupervisor.h>

class KoMainWindowPrivate;
class KoDocument;
class KoPart;
class KoView;
class KoPrintJob;
class KoDockFactoryBase;
class KRecentFilesAction;
class KoComponentData;
class QDockWidget;

struct KoPageLayout;

// Calligra class but not in main module
class KoDockerManager;
class QUrl;

/**
 * @brief Main window for a Calligra application
 *
 * This class is used to represent a main window
 * of a Calligra component. Each main window contains
 * a menubar and some toolbars.
 *
 * @note This class does NOT need to be subclassed in your application.
 */
class KOMAIN_EXPORT KoMainWindow : public KXmlGuiWindow, public KoCanvasSupervisor
{
    Q_OBJECT
public:

    /**
     *  Constructor.
     *
     *  Initializes a Calligra main window (with its basic GUI etc.).
     */
    explicit KoMainWindow(const QByteArray &nativeMimeType, const KoComponentData &instance);

    /**
     *  Destructor.
     */
    ~KoMainWindow() override;

    // If noCleanup is set, KoMainWindow will not delete the root document
    // or part manager on destruction.
    void setNoCleanup(bool noCleanup);

    /**
     * Called when a document is assigned to this mainwindow.
     * This creates a view for this document, makes it the active part, etc.
     */
    void setRootDocument(KoDocument *doc, KoPart *part = 0, bool deletePrevious = true);

    /**
     * This is used to handle the document used at start up before it actually
     * added as root document.
     */
    void setPartToOpen(KoPart *part);

    /**
     * Update caption from document info - call when document info
     * (title in the about page) changes.
     */
    void updateCaption();

    KoComponentData componentData() const;
    void setComponentData(const KoComponentData &componentData);

    /**
     *  Retrieves the document that is displayed in the mainwindow.
     */
    KoDocument *rootDocument() const;
    KoView *rootView() const;

    /**
     * The application should call this to show or hide a toolbar.
     * It also takes care of the corresponding action in the settings menu.
     */
    void showToolbar(const char * tbName, bool shown);

    /**
     * @return TRUE if the toolbar @p tbName is visible
     */
    bool toolbarIsVisible(const char *tbName);

    /**
     * Sets the maximum number of recent documents entries.
     */
    void setMaxRecentItems(uint _number);

    /**
     * The document opened a URL -> store into recent documents list.
     */
    void addRecentURL(const QUrl &url);

    /**
     * Load the desired document and show it.
     * @param url the URL to open
     *
     * @return TRUE on success.
     */
    bool openDocument(const QUrl &url);

    /**
     * Load the URL into this document (and make it root doc after loading)
     *
     * Special method for KoApplication::start, don't use.
     */
    bool openDocument(KoPart *newPart, const QUrl &url);

    /**
     * Reloads the recent documents list.
     */
    void reloadRecentFileList();

    /**
     * Updates the window caption based on the document info and path.
     */
    void updateCaption(const QString & caption, bool mod);
    void updateReloadFileAction(KoDocument *doc);
    void updateVersionsFileAction(KoDocument *doc);

    void setReadWrite(bool readwrite);

    /**
     * Returns the dockwidget specified by the @p factory. If the dock widget doesn't exist yet it's created.
     * Add a "view_palette_action_menu" action to your view menu if you want to use closable dock widgets.
     * @param factory the factory used to create the dock widget if needed
     * @return the dock widget specified by @p factory (may be 0)
     */
    QDockWidget* createDockWidget(KoDockFactoryBase* factory);

    /// Return the list of dock widgets belonging to this main window.
    QList<QDockWidget*> dockWidgets() const;

    QList<KoCanvasObserverBase*> canvasObservers() const override;

    /**
     * @return the KoDockerManager which is assigned
     * WARNING: this could be 0, if no docker have been assigned yet. In that case create one
      * and assign it.
     * Note This should only be called by KoView
     * setDockerManager to assign it.
     */
    KoDockerManager * dockerManager() const;

Q_SIGNALS:
    /**
     * This signal is emitted if the document has been saved successfully.
     */
    void documentSaved();
    /// This signals is emitted before the save dialog is shown
    void saveDialogShown();

    /// This signal is emitted right after the docker states have been successfully restored from config
    void restoringDone();

    /// This signal is emitted when this windows has finished loading of a
    /// document. The document may be opened in another window in the end.
    /// In this case, the signal means there is no link between the window
    /// and the document anymore.
    void loadCompleted(KoMainWindow *);

    /// This signal is emitted when this windows has canceled loading of a document.
    void loadCanceled();

    /// This signal is emitted when the color theme changes
    void themeChanged();

    /// This signal is emitted when the shortcut key configuration has changed
    void keyBindingsChanged();

public Q_SLOTS:

    /**
     * Slot for eMailing the document using KMail
     *
     * This is a very simple extension that will allow any document
     * that is currently being edited to be emailed using KMail.
     */
    void slotEmailFile();

    /**
     *  Slot for opening a new document.
     *
     *  If the current document is empty, the new document replaces it.
     *  If not, a new mainwindow will be opened for showing the document.
     */
    void slotFileNew();

    /**
     *  Slot for opening a saved file.
     *
     *  If the current document is empty, the opened document replaces it.
     *  If not a new mainwindow will be opened for showing the opened file.
     */
    void slotFileOpen();

    /**
     *  Slot for opening a file among the recently opened files.
     *
     *  If the current document is empty, the opened document replaces it.
     *  If not a new mainwindow will be opened for showing the opened file.
     */
    void slotFileOpenRecent(const QUrl &);

    /**
     *  Saves the current document with the current name.
     */
    void slotFileSave();

    /**
     *  Saves the current document with a new name.
     */
    void slotFileSaveAs();

    /**
     *  Prints the actual document.
     */
    void slotFilePrint();
    void slotFilePrintPreview();

    KoPrintJob* exportToPdf(const QString &pdfFileName = QString());
    KoPrintJob* exportToPdf(const KoPageLayout &pageLayout, const QString &pdfFileName = QString());

    /**
     * Show a dialog with author and document information.
     */
    void slotDocumentInfo();

    /**
     *  Closes the document.
     */
    void slotFileClose();

    /**
     *  Closes the mainwindow.
     */
    void slotFileQuit();

    /**
     *  Configure key bindings.
     */
    void slotConfigureKeys();

    /**
     *  Configure toolbars.
     */
    void slotConfigureToolbars();

    /**
     *  Post toolbar config.
     * (Plug action lists back in, etc.)
     */
    void slotNewToolbarConfig();

    /**
     *  Shows or hides a toolbar
     */
    void slotToolbarToggled(bool toggle);

    /**
     * Toggle full screen on/off.
     */
    void viewFullscreen(bool fullScreen);

    /**
     * Toggle docker titlebars on/off.
     */
    void showDockerTitleBars(bool show);

    /**
     * Reload file
     */
    void slotReloadFile();

    /**
     * This will call a dialogbox to add version to list of files
     */
    void slotVersionsFile();

    /**
     * File --> Import
     *
     * This will call slotFileOpen().  To differentiate this from an ordinary
     * call to slotFileOpen() call isImporting().
     */
    void slotImportFile();

    /**
     * File --> Export
     *
     * This will call slotFileSaveAs().  To differentiate this from an ordinary
     * call to slotFileSaveAs() call isExporting().
     */
    void slotExportFile();

    void slotEncryptDocument();
    void slotUncompressToDir();

    void slotProgress(int value);

    /**
     * Hide the dockers
     */
    void toggleDockersVisibility(bool visible);

    /**
     * Saves the document, asking for a filename if necessary.
     *
     * @param saveas if set to TRUE the user is always prompted for a filename
     *
     * @param silent if set to TRUE rootDocument()->setTitleModified will not be called.
     *
     * @param specialOutputFlag set to enums defined in KoDocument if save to special output format
     *
     * @return TRUE on success, false on error or cancel
     *         (don't display anything in this case, the error dialog box is also implemented here
     *         but restore the original URL in slotFileSaveAs)
     */
    bool saveDocument(bool saveas = false, bool silent = false, int specialOutputFlag = 0);

private:

    /**
     * This setting indicates who is calling chooseNewDocument.
     * Usually the app will want to
     * - show the template dialog with 'everything' if InitDocAppStarting, InitDocFileClose or InitDocEmbedded
     * - show the template dialog with 'templates only' if InitDocFileNew
     * - create an empty document with default settings if InitDocEmpty
     */
    enum InitDocFlags { /*InitDocAppStarting, */ InitDocFileNew, InitDocFileClose /*, InitDocEmbedded, InitDocEmpty*/ };

    /// Helper method for slotFileNew and slotFileClose
    void chooseNewDocument(InitDocFlags initDocFlags);

    /**
     * Create a new empty document.
     */
    KoPart* createPart() const;

    void closeEvent(QCloseEvent * e) override;
    void resizeEvent(QResizeEvent * e) override;

    /**
     * Ask user about saving changes to the document upon exit.
     */
    bool queryClose() override;

    bool openDocumentInternal(const QUrl &url, KoPart *newpart = 0, KoDocument *newdoc = 0);

    /**
     * Returns whether or not the current slotFileSave[As]() or saveDocument()
     * call is actually an export operation (like File --> Export).
     *
     * If this is true, you must call KoDocument::export() instead of
     * KoDocument::save() or KoDocument::saveAs(), in any reimplementation of
     * saveDocument().
     */
    bool isExporting() const;

    /**
     * Returns whether or not the current slotFileOpen() or openDocument()
     * call is actually an import operation (like File --> Import).
     *
     * If this is true, you must call KoDocument::import() instead of
     * KoDocument::openUrl(), in any reimplementation of openDocument() or
     * openDocumentInternal().
     */
    bool isImporting() const;

    KRecentFilesAction *recentAction() const;

private Q_SLOTS:
    /**
     * Save the list of recent files.
     */
    void saveRecentFiles();

    void slotLoadCompleted();
    void slotLoadCanceled(const QString &);
    void slotSaveCompleted();
    void slotSaveCanceled(const QString &);
    void forceDockTabFonts();

    /**
     * Slot to create a new view for the currently activate @ref #koDocument.
     */
    virtual void newView();


// ---------------------  PartManager
private:

    friend class KoPart;
    /**
     * Removes a part from the manager (this does not delete the object) .
     *
     * Sets the active part to 0 if @p part is the activePart() .
     */
    virtual void removePart( KoPart *part );

    /**
     * Sets the active part.
     *
     * The active part receives activation events.
     *
     * @p widget can be used to specify which widget was responsible for the activation.
     * This is important if you have multiple views for a document/part , like in KOffice .
     */
    virtual void setActivePart(KoPart *part, QWidget *widget);

private Q_SLOTS:

    /**
     * @internal
     */
    void slotWidgetDestroyed();
    void slotDocumentTitleModified(const QString &caption, bool mod);

    ///----------------------------------------------------------------------
    ///---add----20210501--------------------------------
    ///
public Q_SLOTS:
    /**
     *  Slot for opening a saved file.
     *
     *
     *
     */
    void HealthFileOpen(QString FileName);
//private:
//    int m_timerID;
//    QSharedMemory m_sharedHealthApp;
    ///
    ///
//public:
//    void timerEvent(QTimerEvent *event) override;
    ///---add----20210501--------------------------------
    ///-----------------------------------------------------------------------

// ---------------------  PartManager

private:

    void createMainwindowGUI();

    /**
     * Asks the user if they really want to save the document.
     * Called only if outputFormat != nativeFormat.
     *
     * @return true if the document should be saved
     */
    bool exportConfirmation(const QByteArray &outputFormat);

    void saveWindowSettings();

    // retrieve the current KoView
    KoView* currentView() const;

private:

    KoMainWindowPrivate * const d;
};

#endif
