/* This file is part of the KDE project
   Copyright (C) 2005 Peter Simonsson <psn@linux.se>

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

#include "KoOpenPane.h"

#include <QLayout>
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QSize>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStyledItemDelegate>
#include <QLinearGradient>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>

#include <klocalizedstring.h>
#include <MainDebug.h>

#include <KoFileDialog.h>
#include <KoIcon.h>
#include "KoTemplateTree.h"
#include "KoTemplateGroup.h"
#include "KoTemplate.h"
#include "KoDetailsPane.h"
#include "KoTemplatesPane.h"
#include "KoRecentDocumentsPane.h"
#include "ui_KoOpenPaneBase.h"

#include <limits.h>
#include <KSharedConfig>
#include <KConfigGroup>

class KoSectionListItem : public QTreeWidgetItem
{
public:
    KoSectionListItem(QTreeWidget* treeWidget, const QString& name, int sortWeight, int widgetIndex = -1)
            : QTreeWidgetItem(treeWidget, QStringList() << name), m_sortWeight(sortWeight), m_widgetIndex(widgetIndex) {
        Qt::ItemFlags newFlags = Qt::NoItemFlags;

        if(m_widgetIndex >= 0)
            newFlags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;

        setFlags(newFlags);
    }

    bool operator<(const QTreeWidgetItem & other) const override {
        const KoSectionListItem* item = dynamic_cast<const KoSectionListItem*>(&other);

        if (!item)
            return 0;

        return ((item->sortWeight() - sortWeight()) < 0);
    }

    int sortWeight() const {
        return m_sortWeight;
    }

    int widgetIndex() const {
        return m_widgetIndex;
    }

private:
    int m_sortWeight;
    int m_widgetIndex;
};


class KoSectionListDelegate : public QStyledItemDelegate
{
public:
    KoSectionListDelegate(QObject* parent = 0) : QStyledItemDelegate(parent) { }

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        QStyledItemDelegate::paint(painter, option, index);

        if(!(option.state & (int)(QStyle::State_Active && QStyle::State_Enabled)))
        {
            int ypos = option.rect.y() + ((option.rect.height() - 2) / 2);
            QRect lineRect(option.rect.left(), ypos, option.rect.width(), 2);
            QLinearGradient gradient(option.rect.topLeft(), option.rect.bottomRight());
            gradient.setColorAt(option.direction == Qt::LeftToRight ? 0 : 1, option.palette.color(QPalette::Text));
            gradient.setColorAt(option.direction == Qt::LeftToRight ? 1 : 0, Qt::transparent);

            painter->fillRect(lineRect, gradient);
        }
    }
};


class KoOpenPanePrivate : public Ui_KoOpenPaneBase
{
public:
    KoOpenPanePrivate() :
            Ui_KoOpenPaneBase() {
        m_customWidgetsSeparator = 0;
        m_templatesSeparator = 0;
    }

    int m_freeCustomWidgetIndex;
    KoSectionListItem* m_customWidgetsSeparator;
    KoSectionListItem* m_templatesSeparator;
};

KoOpenPane::KoOpenPane(QWidget *parent, const QStringList& mimeFilter, const QString& templatesResourcePath)
        : QWidget(parent)
        , d(new KoOpenPanePrivate)
{
    d->setupUi(this);

    m_mimeFilter = mimeFilter;
    d->m_openExistingButton->setText(i18n("Open Existing Document"));

    connect(d->m_openExistingButton, SIGNAL(clicked()),
            this, SLOT(openFileDialog()));

    KoSectionListDelegate* delegate = new KoSectionListDelegate(d->m_sectionList);
    d->m_sectionList->setItemDelegate(delegate);

    connect(d->m_sectionList, SIGNAL(itemSelectionChanged()),
            this, SLOT(updateSelectedWidget()));
    connect(d->m_sectionList, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(itemClicked(QTreeWidgetItem*)));
    connect(d->m_sectionList, SIGNAL(itemActivated(QTreeWidgetItem*,int)),
            this, SLOT(itemClicked(QTreeWidgetItem*)));

    initRecentDocs();
    initTemplates(templatesResourcePath);

    d->m_freeCustomWidgetIndex = 4;

    if (!d->m_sectionList->selectedItems().isEmpty())
    {
        KoSectionListItem* selectedItem = static_cast<KoSectionListItem*>(d->m_sectionList->selectedItems().first());

        if (selectedItem) {
            d->m_widgetStack->widget(selectedItem->widgetIndex())->setFocus();
        }
    }

    QList<int> sizes;

    // Set the sizes of the details pane splitters
    KConfigGroup cfgGrp(KSharedConfig::openConfig(), "TemplateChooserDialog");
    sizes = cfgGrp.readEntry("DetailsPaneSplitterSizes", sizes);

    if (!sizes.isEmpty())
        emit splitterResized(0, sizes);

    connect(this, SIGNAL(splitterResized(KoDetailsPane*,QList<int>)),
            this, SLOT(saveSplitterSizes(KoDetailsPane*,QList<int>)));

    setAcceptDrops(true);
}

KoOpenPane::~KoOpenPane()
{
    if (!d->m_sectionList->selectedItems().isEmpty())
    {
        KoSectionListItem* item = dynamic_cast<KoSectionListItem*>(d->m_sectionList->selectedItems().first());

        if (item) {
            if (!qobject_cast<KoDetailsPane*>(d->m_widgetStack->widget(item->widgetIndex()))) {
                KConfigGroup cfgGrp(KSharedConfig::openConfig(), "TemplateChooserDialog");
                cfgGrp.writeEntry("LastReturnType", item->text(0));
            }
        }
    }

    delete d;
}

void KoOpenPane::openFileDialog()
{
    KoFileDialog dialog(this, KoFileDialog::OpenFile, "OpenDocument");
    dialog.setCaption(i18n("Open Existing Document"));
    dialog.setDefaultDir(qApp->applicationName().contains("karbon")
                          ? QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)
                          : QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    dialog.setMimeTypeFilters(m_mimeFilter);
    dialog.setHideNameFilterDetailsOption();
    QUrl url = QUrl::fromUserInput(dialog.filename());
    emit openExistingFile(url);
}

void KoOpenPane::initRecentDocs()
{
    QString header = i18n("Recent Documents");
    KoRecentDocumentsPane* recentDocPane = new KoRecentDocumentsPane(this, header);
    connect(recentDocPane, SIGNAL(openUrl(QUrl)), this, SIGNAL(openExistingFile(QUrl)));
    QTreeWidgetItem* item = addPane(header, koIconName("document-open"), recentDocPane, 0);
    connect(recentDocPane, SIGNAL(splitterResized(KoDetailsPane*,QList<int>)),
            this, SIGNAL(splitterResized(KoDetailsPane*,QList<int>)));
    connect(this, SIGNAL(splitterResized(KoDetailsPane*,QList<int>)),
            recentDocPane, SLOT(resizeSplitter(KoDetailsPane*,QList<int>)));

    if (KSharedConfig::openConfig()->hasGroup("RecentFiles")) {
        d->m_sectionList->setCurrentItem(item, 0, QItemSelectionModel::ClearAndSelect);
    }
}

void KoOpenPane::initTemplates(const QString& templatesResourcePath)
{
    QTreeWidgetItem* selectItem = 0;
    QTreeWidgetItem* firstItem = 0;
    const int templateOffset = 1000;

    if (!templatesResourcePath.isEmpty()) {
        KoTemplateTree templateTree(templatesResourcePath, true);

        foreach (KoTemplateGroup *group, templateTree.groups()) {
            if (group->isHidden()) {
                continue;
            }

            if (!d->m_templatesSeparator) {
                d->m_templatesSeparator = new KoSectionListItem(d->m_sectionList, "", 999);
            }

            KoTemplatesPane* pane = new KoTemplatesPane(this, group->name(),
                    group, templateTree.defaultTemplate());
            connect(pane, SIGNAL(openUrl(QUrl)), this, SIGNAL(openTemplate(QUrl)));
            connect(pane, SIGNAL(alwaysUseChanged(KoTemplatesPane*,QString)),
                    this, SIGNAL(alwaysUseChanged(KoTemplatesPane*,QString)));
            connect(this, SIGNAL(alwaysUseChanged(KoTemplatesPane*,QString)),
                    pane, SLOT(changeAlwaysUseTemplate(KoTemplatesPane*,QString)));
            connect(pane, SIGNAL(splitterResized(KoDetailsPane*,QList<int>)),
                    this, SIGNAL(splitterResized(KoDetailsPane*,QList<int>)));
            connect(this, SIGNAL(splitterResized(KoDetailsPane*,QList<int>)),
                    pane, SLOT(resizeSplitter(KoDetailsPane*,QList<int>)));
            QTreeWidgetItem* item = addPane(group->name(), group->templates().first()->loadPicture(),
                                           pane, group->sortingWeight() + templateOffset);

            if (!firstItem) {
                firstItem = item;
            }

            if (group == templateTree.defaultGroup()) {
                firstItem = item;
            }

            if (pane->isSelected()) {
                selectItem = item;
            }
        }
    } else {
        firstItem = d->m_sectionList->topLevelItem(0);
    }

    KConfigGroup cfgGrp(KSharedConfig::openConfig(), "TemplateChooserDialog");

    if (selectItem && (cfgGrp.readEntry("LastReturnType") == "Template")) {
        d->m_sectionList->setCurrentItem(selectItem, 0, QItemSelectionModel::ClearAndSelect);
    } else if (d->m_sectionList->selectedItems().isEmpty() && firstItem) {
        d->m_sectionList->setCurrentItem(firstItem, 0, QItemSelectionModel::ClearAndSelect);
    }
}

void KoOpenPane::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->accept();
    }
}

void KoOpenPane::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls() && event->mimeData()->urls().size() > 0) {
        // XXX: when the MVC refactoring is done, this can open a bunch of
        //      urls, but since the part/document combination is still 1:1
        //      that won't work for now.
        emit openExistingFile(event->mimeData()->urls().first());

    }
}

void KoOpenPane::addCustomDocumentWidget(QWidget *widget, const QString& title, const QString& icon)
{
    Q_ASSERT(widget);

    if (!d->m_customWidgetsSeparator) {
        d->m_customWidgetsSeparator = new KoSectionListItem(d->m_sectionList, "", 3);
    }

    QString realtitle = title;

    if (realtitle.isEmpty())
        realtitle = i18n("Custom Document");

    QTreeWidgetItem* item = addPane(realtitle, icon, widget, d->m_freeCustomWidgetIndex);
    ++d->m_freeCustomWidgetIndex;
    KConfigGroup cfgGrp(KSharedConfig::openConfig(), "TemplateChooserDialog");

    QString lastActiveItem = cfgGrp.readEntry("LastReturnType");
    bool showCustomItemByDefault = cfgGrp.readEntry("ShowCustomDocumentWidgetByDefault", false);
    if (lastActiveItem == realtitle || (lastActiveItem.isEmpty() && showCustomItemByDefault)) {
        d->m_sectionList->setCurrentItem(item, 0, QItemSelectionModel::ClearAndSelect);
        KoSectionListItem* selectedItem = static_cast<KoSectionListItem*>(item);
        d->m_widgetStack->widget(selectedItem->widgetIndex())->setFocus();
    }
}

QTreeWidgetItem* KoOpenPane::addPane(const QString &title, const QString &iconName, QWidget *widget, int sortWeight)
{
    if (!widget) {
        return 0;
    }

    int id = d->m_widgetStack->addWidget(widget);
    KoSectionListItem* listItem = new KoSectionListItem(d->m_sectionList, title, sortWeight, id);
    listItem->setIcon(0, QIcon::fromTheme(iconName));

    return listItem;
}

QTreeWidgetItem* KoOpenPane::addPane(const QString& title, const QPixmap& icon, QWidget* widget, int sortWeight)
{
    if (!widget) {
        return 0;
    }

    int id = d->m_widgetStack->addWidget(widget);
    KoSectionListItem* listItem = new KoSectionListItem(d->m_sectionList, title, sortWeight, id);

    if (!icon.isNull()) {
        QImage image = icon.toImage();

        if ((image.width() > 48) || (image.height() > 48)) {
            image = image.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }

        image = image.convertToFormat(QImage::Format_ARGB32);
        image = image.copy((image.width() - 48) / 2, (image.height() - 48) / 2, 48, 48);
        listItem->setIcon(0, QIcon(QPixmap::fromImage(image)));
    }

    return listItem;
}

void KoOpenPane::updateSelectedWidget()
{
    if(!d->m_sectionList->selectedItems().isEmpty())
    {
        KoSectionListItem* section = dynamic_cast<KoSectionListItem*>(d->m_sectionList->selectedItems().first());

        if (!section)
            return;

        d->m_widgetStack->setCurrentIndex(section->widgetIndex());
    }
}

void KoOpenPane::saveSplitterSizes(KoDetailsPane* sender, const QList<int>& sizes)
{
    Q_UNUSED(sender);
    KConfigGroup cfgGrp(KSharedConfig::openConfig(), "TemplateChooserDialog");
    cfgGrp.writeEntry("DetailsPaneSplitterSizes", sizes);
}

void KoOpenPane::itemClicked(QTreeWidgetItem* item)
{
    KoSectionListItem* selectedItem = static_cast<KoSectionListItem*>(item);

    if (selectedItem && selectedItem->widgetIndex() >= 0) {
        d->m_widgetStack->widget(selectedItem->widgetIndex())->setFocus();
    }
}
