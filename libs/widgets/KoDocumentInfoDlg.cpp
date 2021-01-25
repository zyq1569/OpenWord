/* This file is part of the KDE project
   Copyright (c) 2000 Simon Hausmann <hausmann@kde.org>
                 2006 Martin Pfeiffer <hubipete@gmx.net>

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

#include "KoDocumentInfoDlg.h"

#include "ui_koDocumentInfoAboutWidget.h"
#include "ui_koDocumentInfoAuthorWidget.h"

#include "KoDocumentInfo.h"
#include "KoDocumentBase.h"
#include "KoGlobal.h"
#include <KoEncryptionChecker.h>
#include "KoPageWidgetItem.h"
#include <KoDocumentRdfBase.h>
#include <KoIcon.h>

#include <klocalizedstring.h>
#include <kiconloader.h>

#include <kmessagebox.h>
#include <kmainwindow.h>
#include <KoDialog.h>

#include <QUrl>
#include <QLineEdit>
#include <QDateTime>
#include <QMimeDatabase>
#include <QMimeType>


// see KoIcon.h
//enum Group {
//    /// No group
//    NoGroup = -1,
//    /// Desktop icons
//    Desktop = 0,
//    /// First group
//    FirstGroup = 0,
//    /// Toolbar icons
//    Toolbar,
//    /// Main toolbar icons
//    MainToolbar,
//    /// Small icons, e.g. for buttons
//    Small,
//    /// Panel (Plasma Taskbar) icons
//    Panel,
//    /// Icons for use in dialog titles, page lists, etc
//    Dialog,
//    /// Last group
//    LastGroup,
//    /// User icons
//    User
//};
//#define koSmallIcon(name) (SmallIcon(QStringLiteral(name)))
//#define koSmallIcon(name) (KIconLoader::loadIcon(QStringLiteral(name)))
#define koSmallIcon(name) (KIconLoader::global()->loadIcon(QStringLiteral(name),(KIconLoader::Group)(0)))



class KoPageWidgetItemAdapter : public KPageWidgetItem
{
//Q_OBJECT
public:
    KoPageWidgetItemAdapter(KoPageWidgetItem *item)
      : KPageWidgetItem(item->widget(), item->name())
      , m_item(item)
    {
        setHeader(item->name());
        setIcon(QIcon::fromTheme(item->iconName()));
    }
    ~KoPageWidgetItemAdapter() override { delete m_item; }

    bool shouldDialogCloseBeVetoed() { return m_item->shouldDialogCloseBeVetoed(); }
    void apply() { m_item->apply(); }

private:
    KoPageWidgetItem * const m_item;
};


class KoDocumentInfoDlg::KoDocumentInfoDlgPrivate
{
public:
    KoDocumentInfoDlgPrivate() :
        toggleEncryption(false),
        applyToggleEncryption(false),
        documentSaved(false) {}
    ~KoDocumentInfoDlgPrivate() = default;

    KoDocumentInfo* info;
    QList<KPageWidgetItem*> pages;
    Ui::KoDocumentInfoAboutWidget* aboutUi;
    Ui::KoDocumentInfoAuthorWidget* authorUi;

    bool toggleEncryption;
    bool applyToggleEncryption;
    bool documentSaved;
};


KoDocumentInfoDlg::KoDocumentInfoDlg(QWidget* parent, KoDocumentInfo* docInfo)
    : KPageDialog(parent)
    , d(new KoDocumentInfoDlgPrivate)
{
    d->info = docInfo;

    setWindowTitle(/*i18n*/("Document Information"));
//    setInitialSize(QSize(500, 500));
    setFaceType(KPageDialog::List);
    setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    button(QDialogButtonBox::Ok)->setDefault(true);

    d->aboutUi = new Ui::KoDocumentInfoAboutWidget();
    QWidget *infodlg = new QWidget();
    d->aboutUi->setupUi(infodlg);
    if (!KoEncryptionChecker::isEncryptionSupported()) {
        d->aboutUi->lblEncryptedDesc->setVisible(false);
        d->aboutUi->lblEncrypted->setVisible(false);
        d->aboutUi->pbEncrypt->setVisible(false);
        d->aboutUi->lblEncryptedPic->setVisible(false);
    }
    d->aboutUi->cbLanguage->addItems(KoGlobal::listOfLanguages());
    d->aboutUi->cbLanguage->setCurrentIndex(-1);

    KPageWidgetItem *page = new KPageWidgetItem(infodlg, /*i18n*/("General"));
    page->setHeader(/*i18n*/("General"));

    // Ugly hack, the mimetype should be a parameter, instead
    KoDocumentBase* doc = dynamic_cast< KoDocumentBase* >(d->info->parent());
    if (doc) {
        QMimeDatabase db;
        QMimeType mime = db.mimeTypeForName(doc->mimeType());
        if (mime.isValid()) {
            page->setIcon(QIcon::fromTheme(mime.iconName()));
        }
    } else {
        // hide all entries not used in pages for KoDocumentInfoPropsPage
        d->aboutUi->filePathInfoLabel->setVisible(false);
        d->aboutUi->filePathLabel->setVisible(false);
        d->aboutUi->filePathSeparatorLine->setVisible(false);
        d->aboutUi->lblTypeDesc->setVisible(false);
        d->aboutUi->lblType->setVisible(false);
    }
    addPage(page);
    d->pages.append(page);

    initAboutTab();

    d->authorUi = new Ui::KoDocumentInfoAuthorWidget();
    QWidget *authordlg = new QWidget();
    d->authorUi->setupUi(authordlg);
    page = new KPageWidgetItem(authordlg, /*i18n*/("Author"));
    page->setHeader(/*i18n*/("Last saved by"));
    page->setIcon(koIcon("user-identity"));
    addPage(page);
    d->pages.append(page);

    initAuthorTab();
}

KoDocumentInfoDlg::~KoDocumentInfoDlg()
{
    delete d->authorUi;
    delete d->aboutUi;
    delete d;
}

void KoDocumentInfoDlg::accept()
{
    // check if any pages veto the close
    foreach(KPageWidgetItem* item, d->pages) {
        KoPageWidgetItemAdapter *page = dynamic_cast<KoPageWidgetItemAdapter*>(item);
        if (page) {
            if (page->shouldDialogCloseBeVetoed()) {
                return;
            }
        }
    }

    // all fine, go and apply
    saveAboutData();
    foreach(KPageWidgetItem* item, d->pages) {
        KoPageWidgetItemAdapter *page = dynamic_cast<KoPageWidgetItemAdapter*>(item);
        if (page) {
            page->apply();
        }
    }

    KPageDialog::accept();
}

bool KoDocumentInfoDlg::isDocumentSaved()
{
    return d->documentSaved;
}

void KoDocumentInfoDlg::initAboutTab()
{
    KoDocumentBase* doc = dynamic_cast< KoDocumentBase* >(d->info->parent());

    if (doc) {
        d->aboutUi->filePathLabel->setText(doc->localFilePath());
    }

    d->aboutUi->leTitle->setText(d->info->aboutInfo("title"));
    d->aboutUi->leSubject->setText(d->info->aboutInfo("subject"));
    QString language = KoGlobal::languageFromTag(d->info->aboutInfo("language"));
    d->aboutUi->cbLanguage->setCurrentIndex(d->aboutUi->cbLanguage->findText(language));

    d->aboutUi->leKeywords->setToolTip(/*i18n*/("Use ';' (Example: Office;KDE;Calligra)"));
    if (!d->info->aboutInfo("keyword").isEmpty())
        d->aboutUi->leKeywords->setText(d->info->aboutInfo("keyword"));

    d->aboutUi->meComments->setPlainText(d->info->aboutInfo("description"));
    if (doc && !doc->mimeType().isEmpty()) {
        QMimeDatabase db;
        QMimeType docmime = db.mimeTypeForName(doc->mimeType());
        if (docmime.isValid())
            d->aboutUi->lblType->setText(docmime.comment());
    }
    if (!d->info->aboutInfo("creation-date").isEmpty()) {
        QDateTime t = QDateTime::fromString(d->info->aboutInfo("creation-date"),
                                            Qt::ISODate);
        QString s = QLocale().toString(t);
        d->aboutUi->lblCreated->setText(s + ", " +
                                        d->info->aboutInfo("initial-creator"));
    }

    if (!d->info->aboutInfo("date").isEmpty()) {
        QDateTime t = QDateTime::fromString(d->info->aboutInfo("date"), Qt::ISODate);
        QString s = QLocale().toString(t);
        d->aboutUi->lblModified->setText(s + ", " + d->info->authorInfo("creator"));
    }

    d->aboutUi->lblRevision->setText(d->info->aboutInfo("editing-cycles"));

    if (doc && (doc->supportedSpecialFormats() & KoDocumentBase::SaveEncrypted)) {
        if (doc->specialOutputFlag() == KoDocumentBase::SaveEncrypted) {
            if (d->toggleEncryption) {
                d->aboutUi->lblEncrypted->setText(/*i18n*/("This document will be decrypted"));
                d->aboutUi->lblEncryptedPic->setPixmap(koSmallIcon("object-unlocked"));
                d->aboutUi->pbEncrypt->setText(/*i18n*/("Do not decrypt"));
            } else {
                d->aboutUi->lblEncrypted->setText(/*i18n*/("This document is encrypted"));
                d->aboutUi->lblEncryptedPic->setPixmap(koSmallIcon("object-locked"));
                d->aboutUi->pbEncrypt->setText(/*i18n*/("D&ecrypt"));
            }
        } else {
            if (d->toggleEncryption) {
                d->aboutUi->lblEncrypted->setText(/*i18n*/("This document will be encrypted."));
                d->aboutUi->lblEncryptedPic->setPixmap(koSmallIcon("object-locked"));
                d->aboutUi->pbEncrypt->setText(/*i18n*/("Do not encrypt"));
            } else {
                d->aboutUi->lblEncrypted->setText(/*i18n*/("This document is not encrypted"));
                d->aboutUi->lblEncryptedPic->setPixmap(koSmallIcon("object-unlocked"));
                d->aboutUi->pbEncrypt->setText(/*i18n*/("&Encrypt"));
            }
        }
    } else {
        d->aboutUi->lblEncrypted->setText(/*i18n*/("This document does not support encryption"));
        d->aboutUi->pbEncrypt->setEnabled( false );
    }
    connect(d->aboutUi->pbReset, SIGNAL(clicked()),
            this, SLOT(slotResetMetaData()));
    connect(d->aboutUi->pbEncrypt, SIGNAL(clicked()),
            this, SLOT(slotToggleEncryption()));
}

void KoDocumentInfoDlg::initAuthorTab()
{
    d->authorUi->fullName->setText(d->info->authorInfo("creator"));
    d->authorUi->initials->setText(d->info->authorInfo("initial"));
    d->authorUi->title->setText(d->info->authorInfo("author-title"));
    d->authorUi->company->setText(d->info->authorInfo("company"));
    d->authorUi->email->setText(d->info->authorInfo("email"));
    d->authorUi->phoneWork->setText(d->info->authorInfo("telephone-work"));
    d->authorUi->phoneHome->setText(d->info->authorInfo("telephone"));
    d->authorUi->fax->setText(d->info->authorInfo("fax"));
    d->authorUi->country->setText(d->info->authorInfo("country"));
    d->authorUi->postal->setText(d->info->authorInfo("postal-code"));
    d->authorUi->city->setText(d->info->authorInfo("city"));
    d->authorUi->street->setText(d->info->authorInfo("street"));
    d->authorUi->position->setText(d->info->authorInfo("position"));
}

void KoDocumentInfoDlg::saveAboutData()
{
    d->info->setAboutInfo("keyword", d->aboutUi->leKeywords->text());
    d->info->setAboutInfo("title", d->aboutUi->leTitle->text());
    d->info->setAboutInfo("subject", d->aboutUi->leSubject->text());
    d->info->setAboutInfo("description", d->aboutUi->meComments->toPlainText());
    d->info->setAboutInfo("language", KoGlobal::tagOfLanguage(d->aboutUi->cbLanguage->currentText()));
    d->applyToggleEncryption = d->toggleEncryption;
}

void KoDocumentInfoDlg::hideEvent( QHideEvent *event )
{
    Q_UNUSED(event);

    // Saving encryption implies saving the document, this is done after closing the dialog
    // TODO: shouldn't this be skipped if cancel is pressed?
    saveEncryption();
}

void KoDocumentInfoDlg::slotResetMetaData()
{
    d->info->resetMetaData();

    if (!d->info->aboutInfo("creation-date").isEmpty()) {
        QDateTime t = QDateTime::fromString(d->info->aboutInfo("creation-date"),
                                            Qt::ISODate);
        QString s = QLocale().toString(t);
        d->aboutUi->lblCreated->setText(s + ", " +
                                        d->info->aboutInfo("initial-creator"));
    }

    if (!d->info->aboutInfo("date").isEmpty()) {
        QDateTime t = QDateTime::fromString(d->info->aboutInfo("date"), Qt::ISODate);
        QString s = QLocale().toString(t);
        d->aboutUi->lblModified->setText(s + ", " + d->info->authorInfo("creator"));
    }

    d->aboutUi->lblRevision->setText(d->info->aboutInfo("editing-cycles"));
}

void KoDocumentInfoDlg::slotToggleEncryption()
{
    KoDocumentBase* doc = dynamic_cast< KoDocumentBase* >(d->info->parent());
    if (!doc)
        return;

    d->toggleEncryption = !d->toggleEncryption;

    if (doc->specialOutputFlag() == KoDocumentBase::SaveEncrypted) {
        if (d->toggleEncryption) {
            d->aboutUi->lblEncrypted->setText(/*i18n*/("This document will be decrypted"));
            d->aboutUi->lblEncryptedPic->setPixmap(koSmallIcon("object-unlocked"));
            d->aboutUi->pbEncrypt->setText(/*i18n*/("Do not decrypt"));
        } else {
            d->aboutUi->lblEncrypted->setText(/*i18n*/("This document is encrypted"));
            d->aboutUi->lblEncryptedPic->setPixmap(koSmallIcon("object-locked"));
            d->aboutUi->pbEncrypt->setText(/*i18n*/("D&ecrypt"));
        }
    } else {
        if (d->toggleEncryption) {
            d->aboutUi->lblEncrypted->setText(/*i18n*/("This document will be encrypted."));
            d->aboutUi->lblEncryptedPic->setPixmap(koSmallIcon("object-locked"));
            d->aboutUi->pbEncrypt->setText(/*i18n*/("Do not encrypt"));
        } else {
            d->aboutUi->lblEncrypted->setText(/*i18n*/("This document is not encrypted"));
            d->aboutUi->lblEncryptedPic->setPixmap(koSmallIcon("object-unlocked"));
            d->aboutUi->pbEncrypt->setText(/*i18n*/("&Encrypt"));
        }
    }
}

void KoDocumentInfoDlg::saveEncryption()
{
    if (!d->applyToggleEncryption)
        return;

    KoDocumentBase* doc = dynamic_cast< KoDocumentBase* >(d->info->parent());
    if (!doc)
        return;

    KMainWindow* mainWindow = dynamic_cast< KMainWindow* >(parent());

    if (doc->specialOutputFlag() == KoDocumentBase::SaveEncrypted) {
        // Decrypt
        if (KMessageBox::warningContinueCancel(
                    this,
                    /*i18n*/("<qt>Decrypting the document will remove the password protection from it."
                         "<p>Do you still want to decrypt the file?</qt>"),
                    /*i18n*/("Confirm Decrypt"),
                    KGuiItem(/*i18n*/("Decrypt")),
                    KStandardGuiItem::cancel(),
                    "DecryptConfirmation"
                    ) != KMessageBox::Continue) {
            return;
        }
        bool modified = doc->isModified();
        doc->setOutputMimeType(doc->outputMimeType(), doc->specialOutputFlag() & ~KoDocumentBase::SaveEncrypted);
        if (!mainWindow) {
            KMessageBox::information(
                        this,
                        /*i18n*/("<qt>Your document could not be saved automatically."
                             "<p>To complete the decryption, please save the document.</qt>"),
                        /*i18n*/("Save Document"),
                        "DecryptSaveMessage");
            return;
        }
        if (modified && KMessageBox::questionYesNo(
                    this,
                    /*i18n*/("<qt>The document has been changed since it was opened. To complete the decryption the document needs to be saved."
                         "<p>Do you want to save the document now?</qt>"),
                    /*i18n*/("Save Document"),
                    KStandardGuiItem::save(),
                    KStandardGuiItem::dontSave(),
                    "DecryptSaveConfirmation"
                    ) != KMessageBox::Yes) {
            return;
        }
    } else {
        // Encrypt
        bool modified = doc->isModified();
        if (!doc->url().isEmpty() && !(doc->mimeType().startsWith("application/vnd.oasis.opendocument.") && doc->specialOutputFlag() == 0)) {
            QMimeDatabase db;
            QMimeType mime = db.mimeTypeForName(doc->mimeType());
            QString comment = mime.isValid() ? mime.comment() : /*i18n*/("%1 (unknown file type)", QString::fromLatin1(doc->mimeType()));
            if (KMessageBox::warningContinueCancel(
                        this,
                        /*i18n*/("<qt>The document is currently saved as %1. The document needs to be changed to <b>OASIS OpenDocument</b> to be encrypted."
                             "<p>Do you want to change the file to OASIS OpenDocument?</qt>", QString("<b>%1</b>").arg(comment)),
                        /*i18n*/("Change Filetype"),
                        KGuiItem(/*i18n*/("Change")),
                        KStandardGuiItem::cancel(),
                        "EncryptChangeFiletypeConfirmation"
                        ) != KMessageBox::Continue) {
                return;
            }
            doc->resetURL();
        }
        doc->setMimeType(doc->nativeOasisMimeType());
        doc->setOutputMimeType(doc->nativeOasisMimeType(), KoDocumentBase::SaveEncrypted);
        if (!mainWindow) {
            KMessageBox::information(
                        this,
                        /*i18n*/("<qt>Your document could not be saved automatically."
                             "<p>To complete the encryption, please save the document.</qt>"),
                        /*i18n*/("Save Document"),
                        "EncryptSaveMessage");
            return;
        }
        if (modified && KMessageBox::questionYesNo(
                    this,
                    /*i18n*/("<qt>The document has been changed since it was opened. To complete the encryption the document needs to be saved."
                         "<p>Do you want to save the document now?</qt>"),
                    /*i18n*/("Save Document"),
                    KStandardGuiItem::save(),
                    KStandardGuiItem::dontSave(),
                    "EncryptSaveConfirmation"
                    ) != KMessageBox::Yes) {
            return;
        }
    }
    // Why do the dirty work ourselves?
    emit saveRequested();
    d->toggleEncryption = false;
    d->applyToggleEncryption = false;
    // Detects when the user cancelled saving
    d->documentSaved = !doc->url().isEmpty();
}

QList<KPageWidgetItem*> KoDocumentInfoDlg::pages() const
{
    return d->pages;
}

void KoDocumentInfoDlg::setReadOnly(bool ro)
{
    d->aboutUi->meComments->setReadOnly(ro);

    Q_FOREACH(KPageWidgetItem* page, d->pages) {
        Q_FOREACH(QLineEdit* le, page->widget()->findChildren<QLineEdit *>()) {
            le->setReadOnly(ro);
        }
        Q_FOREACH(QPushButton* le, page->widget()->findChildren<QPushButton *>()) {
            le->setDisabled(ro);
        }
    }
}

void KoDocumentInfoDlg::addPageItem(KoPageWidgetItem *item)
{
    KPageWidgetItem * page = new KoPageWidgetItemAdapter(item);

    addPage(page);
    d->pages.append(page);
}
//#include "KoDocumentInfoDlg.moc"
