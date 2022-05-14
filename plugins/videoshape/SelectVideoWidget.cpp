/* This file is part of the KDE project
 * Copyright (C) 2008 Jan Hambrecht <jaham@gmx.net>
 * Copyright (C) 2012 Gopalakrishna Bhat A <gopalakbhat@gmail.com>
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

#include "SelectVideoWidget.h"

#include <klocalizedstring.h>
//#include <kfilewidget.h>
//#include <phonon/BackendCapabilities>
#include "KoFileDialog.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QUrl>

///
#include <QApplication>
#include <QStandardPaths>
///
SelectVideoWidget::SelectVideoWidget(QWidget *parent) : QWidget(parent)
{
    //QVBoxLayout *layout = new QVBoxLayout(this);
    //m_fileWidget = new KFileWidget(QUrl(/*QT5TODO:"kfiledialog:///OpenVideoDialog"*/), this);
    //m_fileWidget->setOperationMode(KFileWidget::Opening);
    //m_fileWidget->setMimeFilter(Phonon::BackendCapabilities::availableMimeTypes());
    //layout->addWidget(m_fileWidget);

    //m_saveEmbedded = new QCheckBox(i18n("Save as part of document"));
    //m_fileWidget->setCustomWidget("", m_saveEmbedded);
    //setLayout(layout);
    /////----------------

    m_saveEmbedded = new QCheckBox(i18n("Save as part of document"));
    m_fileDialog = new QFileDialog(this, Qt::SubWindow | Qt::FramelessWindowHint);
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_fileDialog->setOption(QFileDialog::DontUseNativeDialog,true);
    m_fileDialog->setOption(QFileDialog::ReadOnly, true);
    m_fileDialog->setWindowTitle(i18n("Open Video"));
    m_fileDialog->setDirectory(".");
    layout->addWidget(m_fileDialog);
    layout->addWidget(m_saveEmbedded);
    setLayout(layout);
    //////----------------
}

SelectVideoWidget::~SelectVideoWidget()
{

}

void SelectVideoWidget::accept()
{
    //m_fileWidget->slotOk();
    //m_fileWidget->accept();
    m_filename = m_fileDialog->selectedFiles()[0];
}

void SelectVideoWidget::cancel()
{
    //m_fileWidget->slotCancel();
}


QUrl SelectVideoWidget::selectedUrl() const
{
    QUrl url =  QUrl::fromUserInput(m_filename);
    return url;//m_fileWidget->selectedUrl();
}

bool SelectVideoWidget::saveEmbedded()
{
    return m_saveEmbedded->isChecked();
}

//QFileDialog* f = new QFileDialog();
//f->setOption(QFileDialog::DontUseNativeDialog, true);
//QGridLayout *layout = static_cast<QGridLayout*>(f->layout());
//QList< QPair<QLayoutItem*, QList<int> > > moved_items;
//f->show();
//for(int i = 0; i < layout->count(); i++) {
//int row, column, rowSpan, columnSpan;
//layout->getItemPosition(i, &row, &column, &rowSpan, &columnSpan);
//if (row >= 2) {
//QList<int> list;
//list << (row + 1) << column << rowSpan << columnSpan;
//moved_items << qMakePair(layout->takeAt(i), list);
//i--; // takeAt has shifted the rest items
//}
//}
//for(int i = 0; i < moved_items.count(); i++) {
//layout->addItem(moved_items[i].first,
//moved_items[i].second[0],
//moved_items[i].second[1],
//moved_items[i].second[2],
//moved_items[i].second[3]);
//}
//QTableWidget* tableWidget = new QTableWidget();
//layout->addWidget(tableWidget, 2, 0, 1, 4);
