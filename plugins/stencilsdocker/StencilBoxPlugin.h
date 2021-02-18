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

#ifndef STENCIL_BOX_PLUGIN_H
#define STENCIL_BOX_PLUGIN_H

#include <QObject>
#include <QVariantList>
#include <kpluginfactory.h>
class StencilBoxPlugin : public QObject {
    Q_OBJECT

public:
    StencilBoxPlugin(QObject * parent, const QVariantList & );
    ~StencilBoxPlugin() override {}
};

class PluginFactory : public KPluginFactory
{
    Q_OBJECT
    Q_INTERFACES(KPluginFactory)
    Q_PLUGIN_METADATA(IID KPluginFactory_iid FILE "calligra_docker_stencils.json")
public:
    explicit PluginFactory();
    ~PluginFactory();
};

#endif

