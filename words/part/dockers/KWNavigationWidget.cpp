/* This file is part of the KDE project
 * Copyright (C) 2014 Denis Kuplyakov <dener.kup@gmail.com>
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

#include "KWNavigationWidget.h"

#include "Words.h"
#include "KWDocument.h"
#include "frames/KWFrame.h"
#include "frames/KWFrameSet.h"
#include "frames/KWTextFrameSet.h"
#include <KWView.h>
#include <KoParagraphStyle.h>
#include <KoTextDocument.h>
#include <KoTextLayoutRootArea.h>
#include <KoTextEditor.h>

#include <QStack>
#include <QTextDocument>
#include <QTextBlock>
#include <QHeaderView>

QString g_NumberH1PreIndex[21] =
{
    "一",     "二",   "三",   "四",   "五",   "六",   "七",   "八",   "九", "十",
    "十一", "十二", "十三", "十四", "十五", "十六", "十七", "十八", "十九", "二十"
};
QString g_NumberH3PreIndex[21] =
{
    "1",   "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9", "10",
    "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"
};

KWNavigationWidget::KWNavigationWidget(QWidget *parent)
    : QWidget(parent)
    , m_document(0)
    , m_canvas(0)
    , m_layout(0)
    , m_updateTimer(new QTimer(this))
{
    m_model = new QStandardItemModel(this);

    m_updateTimer->setSingleShot(true);

    initUi();
    initLayout();
}

KWNavigationWidget::~KWNavigationWidget()
{
}

void KWNavigationWidget::initUi()
{
    m_treeView = new QTreeView;
    m_treeView->setModel(m_model);
    //m_treeView->setItemsExpandable(false);///del openword 20210804
    m_treeView->setExpandsOnDoubleClick(false);///add openword 20210804
    m_treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_treeView->setSelectionMode(QAbstractItemView::SingleSelection/*NoSelection*/);///openword 20210804

    //connect(m_treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(navigationClicked(QModelIndex)));
    ///replace by doubleClicked  20210804
    connect(m_treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(navigationClicked(QModelIndex)));
}

void KWNavigationWidget::initLayout()
{
    QHBoxLayout *mainBox = new QHBoxLayout(this);
    mainBox->addWidget(m_treeView);

    m_treeView->header()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setLayout(mainBox); // FIXME: Is this necessary?
}

void KWNavigationWidget::navigationClicked(QModelIndex idx)
{
    if (idx.column() == 0)
    {
        QTextDocument *doc = static_cast<QTextDocument *>(
                                 m_model->itemFromIndex(idx)->data(Qt::UserRole + 2).value<void *>());

        int position = m_model->itemFromIndex(idx)->data(Qt::UserRole + 1).toInt();

        KoTextDocument(doc).textEditor()->setPosition(position); // placing cursor
        m_canvas->view()->setFocus(); // passing focus

        KoTextLayoutRootArea *a = m_layout->rootAreaForPosition(position);
        m_canvas->view()->goToPage(*(static_cast<KWPage *>(a->page()))); // showing needed page
    }
}

QString KWNavigationWidget::updateLevel(QString title, int level)
{
    int index = 0;
    if (m_NavInfo.size() > 0)
    {
        while (m_NavInfo.top().second > level)
        {
            m_NavInfo.pop();
        }
        if (m_NavInfo.top().second == level)
        {
            index = m_NavInfo.top().first + 1;
        }
    }
    if (index > 20)//目前只设置了19个长度,需要自己增加
    {
        return title;
    }

    if (level == 1)
    {
        title = g_NumberH1PreIndex[index] +  "、 " + title;
    }
    else if (level == 2)
    {
        title = "("+g_NumberH1PreIndex[index] +  ") " + title;
    }
    else if (level == 3)
    {
        title = g_NumberH3PreIndex[index] +  ". " + title;
    }
    m_NavInfo.push(QPair<int, int>(index, level));
    return title;
}

void KWNavigationWidget::updateData()
{
    if (!isVisible())
    {
        return;
    }

    // don't refresh too often
    if (m_updateTimer->isActive())
    {
        return;
    }

    m_model->clear();

    QStringList head;
    head << i18n("Section") << i18n("Page #");
    m_model->setHorizontalHeaderLabels(head);
    m_model->setColumnCount(2);

    m_treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_treeView->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_treeView->header()->setStretchLastSection(false);

    QStack< QPair<QStandardItem *, int> > curChain;
    curChain.push(QPair<QStandardItem *, int>(m_model->invisibleRootItem(), 0));

    m_NavInfo.clear();

    foreach (KWFrameSet *fs, m_document->frameSets())
    {
        KWTextFrameSet *tfs = dynamic_cast<KWTextFrameSet*>(fs);
        if (tfs == 0)
        {
            continue;
        }

        tfs->wordsDocument();
        QTextDocument *doc = tfs->document();
        QTextBlock block = doc->begin();

        while (block.isValid())
        {
            int blockLevel = block.blockFormat().intProperty(KoParagraphStyle::OutlineLevel);
            if (!blockLevel)
            {
                block = block.next();
                continue;
            }
            QString title = block.text();
            static int len = QString("?目录").length();
            static QString spestr = "目录";
            if (title.length())///add:去掉空
            {
                //20211012 openword 临时办法解决docx中文档索引中的 "目录" 问题，当前无法确定
                //KoParagraphStyle::OutlineLevel 哪儿设置改变成值 1了???
                if (title.length() <= len+1 && title.contains(spestr/*QLatin1String("目录")*/) && blockLevel == 1)
                {
                    // to do????
                }
                else
                {
                    title = updateLevel(title,blockLevel);
                    QStandardItem *item = new QStandardItem(title/*block.text()*/);
                    item->setData(block.position(), Qt::UserRole + 1);
                    item->setData(/*qVariantFromValue*/QVariant::fromValue((void *)doc), Qt::UserRole + 2);
                    QList< QStandardItem *> buf;

                    KoTextLayoutRootArea *a = m_layout->rootAreaForPosition(block.position());
                    buf.append(item);
                    //add pagenuber 第几页
                    buf.append(new QStandardItem(QString::number(a->page()->visiblePageNumber())));

                    while (curChain.top().second >= blockLevel)
                    {
                        curChain.pop();
                    }
                    curChain.top().first->appendRow(buf);
                    curChain.push(QPair<QStandardItem *, int>(item, blockLevel));
                }

            }

            block = block.next();
        }
    }
    m_treeView->expandAll();
    m_treeView->resizeColumnToContents(1);

    m_updateTimer->start(300);
}

void KWNavigationWidget::setCanvas(KWCanvas* canvas)
{
    if (!canvas)
    {
        return;
    }
    m_document = canvas->document();
    if (m_layout)
    {
        disconnect(m_layout, SIGNAL(finishedLayout()), this, SLOT(updateData()));
    }
    if (m_document->mainFrameSet())
    {
        m_layout = qobject_cast<KoTextDocumentLayout *>(
                       m_document->mainFrameSet()->document()->documentLayout());
        connect(m_layout, SIGNAL(finishedLayout()), this, SLOT(updateData()));
    }
    else
    {
        m_layout = 0;
    }
    m_canvas = canvas;
}

void KWNavigationWidget::unsetCanvas()
{
    m_document = 0;
    if (m_layout)
    {
        disconnect(m_layout, SIGNAL(finishedLayout()), this, SLOT(updateData()));
    }
    m_layout = 0;
}
