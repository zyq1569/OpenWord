/* This file is part of the KDE project
* Copyright (C) 2009-2010 Pierre Stirnweiss <pstirnweiss@googlemail.com>
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

#ifndef TRACKEDCHANGEMANAGER_H
#define TRACKEDCHANGEMANAGER_H

#include <ui_TrackedChangeManager.h>

//#include <KoDialog.h>
#include <QWidget>

class TrackedChangeModel;

class QModelIndex;

class TrackedChangeManager : public QWidget
{
    Q_OBJECT
public:
    explicit TrackedChangeManager(QWidget *parent=0);
    ~TrackedChangeManager() override;

    void setModel(TrackedChangeModel *model);

    void selectItem(const QModelIndex &newIndex);

Q_SIGNALS:
    void currentChanged(const QModelIndex &newIndex);

private Q_SLOTS:
    void currentChanged(const QModelIndex &newIndex, const QModelIndex &previousIndex);

private:
    Ui::trackedChange widget;
    TrackedChangeModel *m_model;
};

#endif // TRACKEDCHANGEMANAGER_H
