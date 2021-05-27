/* This file is part of the KDE project
   Copyright (C) 2005-2006 Peter Simonsson <psn@linux.se>
   Copyright 2012 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "KoRecentDocumentsPane.h"

#include <kundo2command.h>
#include <QFile>
#include <QStandardItemModel>
#include <QUrl>

#include <KSharedConfig>
#include <KConfigGroup>
#include <kfileitem.h>
#include <kio/previewjob.h>

#include <KoIcon.h>


static const int MAX_RECENTFILES_ENTRIES = 20;//recent files


enum KoRecentDocumentRoles
{
    PreviewRole = Qt::UserRole
};

class KoFileListItem : public QStandardItem
{
public:
    KoFileListItem(const QIcon &icon, const QString &text, const KFileItem& item)
        : QStandardItem(icon, text)
        , m_fileItem(item)
    {
    }

    ~KoFileListItem() override
    {
    }

    const KFileItem &fileItem() const
    {
        return m_fileItem;
    }

private:
    KFileItem m_fileItem;
};


class KoRecentDocumentsPanePrivate
{
public:
    KoRecentDocumentsPanePrivate()
    {
    }

    ~KoRecentDocumentsPanePrivate()
    {
        foreach(KJob* job, m_previewJobs)
        {
            job->kill();
        }
    }

    QList<KJob*> m_previewJobs;
};


KoRecentDocumentsPane::KoRecentDocumentsPane(QWidget* parent, const QString& header)
    : KoDetailsPane(parent, header)
    , d(new KoRecentDocumentsPanePrivate)
{
    setFocusProxy(m_documentList);
    m_openButton->setText(/*kundo2_i18n*/("Open This Document"));
    m_openButton->setIcon(koIcon("document-open"));

    m_alwaysUseCheckBox->hide();

    model()->setSortRole(0); // Disable sorting

    // load list of recent files from config
    KConfigGroup config(KSharedConfig::openConfig(), "RecentFiles");

    QString fileKey;
    QString fileValue;
    QUrl url;
    QString nameValue;
    KFileItemList fileList;
    QStandardItem* rootItem = model()->invisibleRootItem();

    for (int i = 1; i <= MAX_RECENTFILES_ENTRIES; ++i)
    {
        fileValue = config.readPathEntry(QString("File%1").arg(i), QString());

        // ignore empty entries
        if (fileValue.isEmpty())
        {
            continue;
        }

        url = QUrl::fromUserInput(fileValue);

        // ignore entries for files known to no longer exist
        if (url.isLocalFile() && !QFile::exists(url.toLocalFile()))
        {
            continue;
        }
        // ignore duplicated entries
        if (!fileList.findByUrl(url).isNull())
        {
            continue;
        }

        nameValue = config.readPathEntry(QString("Name%1").arg(i), QString());
        // handle name entries with empty strings
        if (nameValue.isEmpty())
        {
            nameValue = url.fileName();
        }

        KFileItem fileItem(url);
        fileList.prepend(fileItem);
        const QIcon icon = QIcon::fromTheme(fileItem.iconName());
        KoFileListItem* item = new KoFileListItem(icon, nameValue, fileItem);
        item->setEditable(false);
        rootItem->insertRow(0, item);
    }


    //Select the first file
    QModelIndex firstIndex = model()->indexFromItem(model()->item(0));
    m_documentList->selectionModel()->select(firstIndex, QItemSelectionModel::Select);
    m_documentList->selectionModel()->setCurrentIndex(firstIndex, QItemSelectionModel::Select);

    QStringList availablePlugins = KIO::PreviewJob::availablePlugins();
    KIO::PreviewJob *previewJob = KIO::filePreview(fileList, QSize(IconExtent, IconExtent), &availablePlugins);

    d->m_previewJobs.append(previewJob);
    connect(previewJob, SIGNAL(result(KJob*)), SLOT(previewResult(KJob*)));
    connect(previewJob, SIGNAL(gotPreview(KFileItem,QPixmap)),
            SLOT(updateIcon(KFileItem,QPixmap)));
}

KoRecentDocumentsPane::~KoRecentDocumentsPane()
{
    delete d;
}

void KoRecentDocumentsPane::selectionChanged(const QModelIndex& index)
{
    if (index.isValid())
    {
        KoFileListItem* item = static_cast<KoFileListItem*>(model()->itemFromIndex(index));
        const KFileItem fileItem = item->fileItem();

        m_openButton->setEnabled(true);
        m_titleLabel->setText(item->data(Qt::DisplayRole).toString());

        QPixmap preview = item->data(PreviewRole).value<QPixmap>();
        if (preview.isNull())
        {
            // need to fetch preview
            const KFileItemList fileList = KFileItemList() << fileItem;
            QStringList availablePlugins = KIO::PreviewJob::availablePlugins();
            KIO::PreviewJob *previewJob = KIO::filePreview(fileList, QSize(PreviewExtent, PreviewExtent), &availablePlugins);

            d->m_previewJobs.append(previewJob);
            connect(previewJob, SIGNAL(result(KJob*)), SLOT(previewResult(KJob*)));
            connect(previewJob, SIGNAL(gotPreview(KFileItem,QPixmap)),
                    SLOT(updatePreview(KFileItem,QPixmap)));

            // for now set preview to icon
            preview = item->icon().pixmap(PreviewExtent);
            if (preview.width() < PreviewExtent && preview.height() < PreviewExtent)
            {
                preview = preview.scaled(PreviewExtent, PreviewExtent, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
        }
        m_previewLabel->setPixmap(preview);

        if (!fileItem.isNull())
        {
            // TODO: think about not displaying Modified/Accessed if not available
//            QString details = QString("<center>%1<br>").arg(fileItem.url().toDisplayString(QUrl::PreferLocalFile)) +
//                "<table border=\"0\">" +
//                kundo2_i18nc("File modification date and time. %1 is date time",
//                      "<tr><td><b>Modified:</b></td><td>%1</td></tr>",
//                      QString(fileItem.timeString(KFileItem::ModificationTime))) +
//                kundo2_i18nc("File access date and time. %1 is date time",
//                      "<tr><td><b>Accessed:</b></td><td>%1</td></tr>",
//                      QString(fileItem.timeString(KFileItem::AccessTime))) +
//                "</table></center>";
            QString details = QString("<center>%1<br>").arg(fileItem.url().toDisplayString(QUrl::PreferLocalFile)) +
                              "<table border=\"0\">" +
                              ("File modification date and time. %1 is date time",
                               "<tr><td><b>Modified:</b></td><td>%1</td></tr>",
                               QString(fileItem.timeString(KFileItem::ModificationTime))) +
                              ("File access date and time. %1 is date time",
                               "<tr><td><b>Accessed:</b></td><td>%1</td></tr>",
                               QString(fileItem.timeString(KFileItem::AccessTime))) +
                              "</table></center>";
            m_detailsLabel->setHtml(details);
        }
        else
        {
            m_detailsLabel->clear();
        }
    }
    else
    {
        m_openButton->setEnabled(false);
        m_titleLabel->clear();
        m_previewLabel->setPixmap(QPixmap());
        m_detailsLabel->clear();
    }
}

void KoRecentDocumentsPane::openFile()
{
    KoDetailsPane::openFile();
}

void KoRecentDocumentsPane::openFile(const QModelIndex& index)
{
    if (!index.isValid())
    {
        return;
    }

    KConfigGroup cfgGrp(KSharedConfig::openConfig(), "TemplateChooserDialog");
    cfgGrp.writeEntry("LastReturnType", "File");

    KoFileListItem* item = static_cast<KoFileListItem*>(model()->itemFromIndex(index));
    KFileItem fileItem = item->fileItem();

    if (!fileItem.isNull())
    {
        emit openUrl(fileItem.url());
    }
}

void KoRecentDocumentsPane::previewResult(KJob* job)
{
    d->m_previewJobs.removeOne(job);
}

void KoRecentDocumentsPane::updatePreview(const KFileItem& fileItem, const QPixmap& preview)
{
    if (preview.isNull())
    {
        return;
    }

    QStandardItem* rootItem = model()->invisibleRootItem();

    for (int i = 0; i < rootItem->rowCount(); ++i)
    {
        KoFileListItem* item = static_cast<KoFileListItem*>(rootItem->child(i));
        if (item->fileItem().url() == fileItem.url())
        {
            item->setData(preview, PreviewRole);

            if (m_documentList->selectionModel()->currentIndex() == item->index())
            {
                m_previewLabel->setPixmap(preview);
            }

            break;
        }
    }
}

void KoRecentDocumentsPane::updateIcon(const KFileItem& fileItem, const QPixmap& pixmap)
{
    if (pixmap.isNull())
    {
        return;
    }

    QStandardItem *rootItem = model()->invisibleRootItem();

    for (int i = 0; i < rootItem->rowCount(); ++i)
    {
        KoFileListItem *item = static_cast<KoFileListItem*>(rootItem->child(i));
        if (item->fileItem().url() == fileItem.url())
        {
            // ensure squareness
            QImage icon = pixmap.toImage();
            icon = icon.convertToFormat(QImage::Format_ARGB32);
            icon = icon.copy((icon.width() - IconExtent) / 2, (icon.height() - IconExtent) / 2, IconExtent, IconExtent);

            item->setIcon(QIcon(QPixmap::fromImage(icon)));

            break;
        }
    }
}
