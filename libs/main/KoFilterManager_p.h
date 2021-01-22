/* This file is part of the KDE project
   Copyright (C) 2003 Clarence Dang <dang@kde.org>
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

#ifndef __koFilterManager_p_h__
#define __koFilterManager_p_h__

#include "KoFilterManager.h"

#include <QUrl>
#include <KoDialog.h>
#include <KoProgressUpdater.h>

#include <QString>
#include <QStringList>
#include <QPointer>

class QListWidget;

class Q_DECL_HIDDEN KoFilterManager::Private
{
public:
    bool batch;
    QByteArray importMimeType;
    QPointer<KoProgressUpdater> progressUpdater;

    Private(KoProgressUpdater *progressUpdater_ = 0)
        : progressUpdater(progressUpdater_)
    {
    }

};

class KoFilterChooser : public KoDialog
{
    Q_OBJECT

public:
    KoFilterChooser(QWidget *parent, const QStringList &mimeTypes,
                    const QString &nativeFormat = QString(), const QUrl &url = QUrl());
    ~KoFilterChooser() override;

    QString filterSelected();

private:
    QStringList m_mimeTypes;
    QListWidget *m_filterList;
};

#endif
