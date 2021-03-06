/* This file is part of the KDE project
 * Copyright (C) 2006-2007 Thomas Zander <zander@kde.org>
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

#include "KoTextEditingRegistry.h"

#include <KoPluginLoader.h>
#include <QGlobalStatic>

Q_GLOBAL_STATIC(KoTextEditingRegistry, s_instance)

void KoTextEditingRegistry::init()
{
    KoPluginLoader::PluginsConfig config;
    config.whiteList = "TextEditingPlugins";
    config.blacklist = "TextEditingPluginsDisabled";
    config.group = "calligra";
    KoPluginLoader::load(QStringLiteral("calligra/textediting"), config);
}

KoTextEditingRegistry* KoTextEditingRegistry::instance()
{
    if (!s_instance.exists())
    {
        s_instance->init();
    }
    return s_instance;
}

KoTextEditingRegistry::~KoTextEditingRegistry()
{
    qDeleteAll(doubleEntries());
    qDeleteAll(values());
}
