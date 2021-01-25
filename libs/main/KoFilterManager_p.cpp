/* This file is part of the KDE project
   Copyright (C) 1998, 1999 Torben Weis <weis@kde.org>
                 2000, 2001 Werner Trobin <trobin@kde.org>
   Copyright (C) 2004 Nicolas Goutte <goutte@kde.org>
   Copyright (C) 2009 Thomas Zander <zander@kde.org>

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

#include "KoFilterManager_p.h"

#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMimeDatabase>

#include <klocalizedstring.h>
#include <ksqueezedtextlabel.h>

#include <unistd.h>

KoFilterChooser::KoFilterChooser(QWidget *parent, const QStringList &mimeTypes, const QString &/*nativeFormat*/, const QUrl &url)
        : KoDialog(parent),
        m_mimeTypes(mimeTypes)
{
    setObjectName("kofilterchooser");
    setInitialSize(QSize(300, 350));
    setButtons(KoDialog::Ok|KoDialog::Cancel);
    setDefaultButton(KoDialog::Ok);
    setCaption(i18n("Choose Filter"));
    setModal(true);

    QWidget *page = new QWidget(this);
    setMainWidget(page);

    QVBoxLayout *layout = new QVBoxLayout(page);
    if (url.isValid()) {
        KSqueezedTextLabel *l = new KSqueezedTextLabel(url.path(), page);
        layout->addWidget(l);
    }
    m_filterList = new QListWidget(page);
    layout->addWidget(m_filterList);
    page->setLayout(layout);

    Q_ASSERT(!m_mimeTypes.isEmpty());
    QMimeDatabase db;
    for (QStringList::ConstIterator it = m_mimeTypes.constBegin();
            it != m_mimeTypes.constEnd();
            ++it) {

        QMimeType mime = db.mimeTypeForName(*it);
        const QString name = mime.isValid() ? mime.comment() : *it;
        if (! name.isEmpty()) {
            QListWidgetItem *item = new QListWidgetItem(name, m_filterList);
            item->setData(32, *it);
        }
    }

    m_filterList->sortItems();

    if (m_filterList->currentRow() == -1)
        m_filterList->setCurrentRow(0);

    m_filterList->setFocus();

    connect(m_filterList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(accept()));
    resize(QSize(520, 400));//.expandedTo(minimumSizeHint()));
}

KoFilterChooser::~KoFilterChooser()
{
}

QString KoFilterChooser::filterSelected()
{
    QListWidgetItem *item = m_filterList->currentItem();
    return item->data(32).toString();
}
