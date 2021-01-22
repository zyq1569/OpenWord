/* This file is part of the KDE project
   Copyright (C) 2002 Laurent Montel <lmontel@mandrakesoft.com>
   Copyright (C) 2006-2007 Jan Hambrecht <jaham@gmx.net>
   Copyright (C) 2009 Thorsten Zachmann <zachmann@kde.org>

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

#ifndef KOCONFIGMISCPAGE_H
#define KOCONFIGMISCPAGE_H

#include <KoVBox.h>

#include "komain_export.h"

class KoUnit;
class KoDocument;
class KoDocumentResourceManager;

class KOMAIN_EXPORT KoConfigMiscPage : public KoVBox
{
    Q_OBJECT

public:
    explicit KoConfigMiscPage(KoDocument* doc, KoDocumentResourceManager *documentResources, char* name = 0L);
    ~KoConfigMiscPage() override;

    void apply();

Q_SIGNALS:
    void unitChanged(const KoUnit &unit);

public Q_SLOTS:
    void slotDefault();
    void slotUnitChanged(int);

private:
    class Private;
    Private * const d;
};

#endif // KOCONFIGMISCPAGE_H
