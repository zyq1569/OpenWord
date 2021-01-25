/* This file is part of the KDE project
 * Copyright (C) 2007 Thomas Zander <zander@kde.org>
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
#ifndef KORULERCONTROLLER_H
#define KORULERCONTROLLER_H

#include <QObject>
#include "kowidgets_export.h"

class KoRuler;
class KoCanvasResourceManager;

/**
 * This class combines text options with the KoRuler object.
 * Any usage of a horizontal ruler should consider using this class to show the
 * text indent and tabs on the ruler, and allow to edit them.
 * The code to do this is pretty trivial; just instantiate this class and you can
 * forget about it.  It'll do what you want.
 */
class KOWIDGETS_EXPORT KoRulerController : public QObject
{
    Q_OBJECT
public:
    /**
     * Constructor.
     * @param horizontalRuler the ruler to monitor and update.
     *  Will also be used as QObject parent for memory management purposes.
     * @param crp the resource provider for the canvas this ruler and the text tool belong to.
     */
    KoRulerController(KoRuler *horizontalRuler, KoCanvasResourceManager *crp);
    ~KoRulerController() override;

private:
    class Private;
    Private * const d;

    Q_PRIVATE_SLOT(d, void canvasResourceChanged(int))
    Q_PRIVATE_SLOT(d, void indentsChanged())
    Q_PRIVATE_SLOT(d, void tabChanged(int, KoRuler::Tab *tab))
    Q_PRIVATE_SLOT(d, void tabChangeInitiated())
};


#include "KoText.h"
#include "styles/KoParagraphStyle.h"
#include <KoCanvasResourceManager.h>
#include <KoTextDocument.h>
#include <WidgetsDebug.h>
//#include <QVariant>
//#include <QTextOption>
#include <QTextDocument>
#include <QTextBlock>
//#include <QTextBlockFormat>
//#include <QTextLayout>
//#include <QTextCursor>
#include <QLocale>
#include <KoRuler.h>
//#include <algorithm>

static int compareTabs(KoText::Tab &tab1, KoText::Tab &tab2)
{
    return tab1.position < tab2.position;
}

class Q_DECL_HIDDEN KoRulerController::Private
{
public:
    Private(KoRuler *r, KoCanvasResourceManager *crp)
            : ruler(r),
            resourceManager(crp),
            lastPosition(-1),
            originalTabIndex(-2),
            currentTabIndex(-2) {
    }

    void canvasResourceChanged(int key) {
        if (key != KoText::CurrentTextPosition && key != KoText::CurrentTextDocument
            && key != KoCanvasResourceManager::ActiveRange)
            return;

        QTextBlock block = currentBlock();
        if (! block.isValid()) {
            ruler->setShowIndents(false);
            ruler->setShowTabs(false);
            return;
        }

        QRectF activeRange = resourceManager->resource(KoCanvasResourceManager::ActiveRange).toRectF();
        ruler->setOverrideActiveRange(activeRange.left(), activeRange.right());
        lastPosition = block.position();
        currentTabIndex = -2;
        tabList.clear();

        QTextBlockFormat format = block.blockFormat();
        ruler->setRightToLeft(block.layout()->textOption().textDirection() == Qt::RightToLeft);
        ruler->setParagraphIndent(format.leftMargin());
        ruler->setFirstLineIndent(format.textIndent());
        ruler->setEndIndent(format.rightMargin());
        ruler->setRelativeTabs(relativeTabs());

        QList<KoRuler::Tab> tabs;
        QVariant variant = format.property(KoParagraphStyle::TabPositions);
        if (! variant.isNull()) {
            foreach(const QVariant & var, qvariant_cast<QList<QVariant> >(variant)) {
                KoText::Tab textTab = var.value<KoText::Tab>();
                KoRuler::Tab tab;
                tab.position = textTab.position;
                tab.type = textTab.type;
                tabs.append(tab);
            }
        }
        qreal tabStopDistance = format.doubleProperty(KoParagraphStyle::TabStopDistance);
/*        if (tabStopDistance <= 0) {
// kotextdocumentlayout hardly reachable from here :(
    tabStopDistance = block.document()->documentLayout()->defaultTabSpacing();
        } */
        ruler->updateTabs(tabs, tabStopDistance);

        ruler->setShowIndents(true);
        ruler->setShowTabs(true);
    }

    void indentsChanged() {
        QTextBlock block = currentBlock();
        if (! block.isValid())
            return;
        QTextCursor cursor(block);
        QTextBlockFormat bf = cursor.blockFormat();
        bf.setLeftMargin(ruler->paragraphIndent());
        bf.setTextIndent(ruler->firstLineIndent());
        bf.setRightMargin(ruler->endIndent());
        cursor.setBlockFormat(bf);
    }

    void tabChanged(int originalIndex, KoRuler::Tab *tab) {
        QVariant docVar = resourceManager->resource(KoText::CurrentTextDocument);
        if (docVar.isNull())
            return;
        QTextDocument *doc = static_cast<QTextDocument*>(docVar.value<void*>());
        if (doc == nullptr)
            return;
        const int position = resourceManager->intResource(KoText::CurrentTextPosition);
        const int anchor = resourceManager->intResource(KoText::CurrentTextAnchor);

        QTextCursor cursor(doc);
        cursor.setPosition(anchor);
        cursor.setPosition(position, QTextCursor::KeepAnchor);

        if (originalTabIndex == -2 || originalTabIndex != originalIndex) {
            originalTabIndex = originalIndex;
            KoParagraphStyle style(cursor.blockFormat(), cursor.blockCharFormat());
            tabList = style.tabPositions();
            if (originalTabIndex >= 0) { // modification
                currentTab = tabList[originalTabIndex];
                currentTabIndex = originalTabIndex;
            } else if (originalTabIndex == -1 && tab) { // new tab.
                currentTab = KoText::Tab();
                currentTab.type = tab->type;
                if (tab->type == QTextOption::DelimiterTab)
                    currentTab.delimiter = QLocale::system().decimalPoint(); // TODO check language of text
                currentTabIndex = tabList.count();
                tabList << currentTab;
            } else {
                warnWidgets << "Unexpected input from tabChanged signal";
                Q_ASSERT(false);
                return;
            }
        }

        if (tab) {
            currentTab.position = tab->position;
            currentTab.type = tab->type;
            if (currentTabIndex == -2) { // add the new tab to the list, sorting in.
                currentTabIndex = tabList.count();
                tabList << currentTab;
            } else
                tabList.replace(currentTabIndex, currentTab);
        } else if (currentTabIndex >= 0) { // lets remove it.
            tabList.removeAt(currentTabIndex);
            currentTabIndex = -2;
        }

        QTextBlockFormat bf;
        QVector<KoText::Tab> sortedList = tabList;
        std::sort(sortedList.begin(), sortedList.end(), compareTabs);
        QList<QVariant> list;
        foreach(const KoText::Tab & tab, sortedList) {
            QVariant v;
            v.setValue(tab);
            list.append(v);
        }
        bf.setProperty(KoParagraphStyle::TabPositions, list);
        cursor.mergeBlockFormat(bf);
    }

    QTextBlock currentBlock() {
        QVariant docVar = resourceManager->resource(KoText::CurrentTextDocument);
        if (docVar.isNull())
            return QTextBlock();
        QTextDocument *doc = static_cast<QTextDocument*>(docVar.value<void*>());
        if (doc == nullptr)
            return QTextBlock();
        return doc->findBlock(resourceManager->intResource(KoText::CurrentTextPosition));
    }

    bool relativeTabs() {
        QVariant docVar = resourceManager->resource(KoText::CurrentTextDocument);
        if (docVar.isNull())
            return false;
        QTextDocument *doc = static_cast<QTextDocument*>(docVar.value<void*>());
        if (doc == nullptr)
            return false;
        return KoTextDocument(doc).relativeTabs();
    }

    void tabChangeInitiated() {
        tabList.clear();
        originalTabIndex = -2;
    }

private:
    KoRuler *ruler;
    KoCanvasResourceManager *resourceManager;
    int lastPosition; // the last position in the text document.
    QVector<KoText::Tab> tabList;
    KoText::Tab currentTab;
    int originalTabIndex, currentTabIndex;
};

#endif
