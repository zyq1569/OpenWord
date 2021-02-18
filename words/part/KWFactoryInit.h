/* This file is part of the KDE project
 * Copyright (C) 2013 Boudewijn Rempt <boud@valdyas.org>
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
#ifndef KWFACTORYINIT_H
#define KWFACTORYINIT_H

#include "KWFactory.h"

class KWFactoryInit : public KWFactory
{
    Q_OBJECT
    ///openword
    Q_PLUGIN_METADATA(IID KPluginFactory_iid FILE "wordspart.json")
    Q_INTERFACES(KPluginFactory)

public:
    explicit KWFactoryInit() : KWFactory() {}
    ~KWFactoryInit() override;// {}

};

#endif // KWFACTORYINIT_H
