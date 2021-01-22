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
#include "Plugin.h"
#include "PictureShapeFactory.h"
#include "PictureToolFactory.h"

#include <QPixmapCache>

#include <KoToolRegistry.h>
#include <KoShapeRegistry.h>

#include <kpluginfactory.h>

#define CACHE_SIZE 40960 //5 images of 2048x1024 at 32bpp

K_PLUGIN_FACTORY_WITH_JSON(PluginFactory, "calligra_shape_picture.json",
                           registerPlugin<Plugin>();)

Plugin::Plugin(QObject *parent, const QVariantList &)
    : QObject(parent)
{
    if(QPixmapCache::cacheLimit() < CACHE_SIZE) {
        QPixmapCache::setCacheLimit(CACHE_SIZE);
    }

    KoShapeRegistry::instance()->add( new PictureShapeFactory() );
    KoToolRegistry::instance()->add( new PictureToolFactory() );
}

#include <Plugin.moc>

