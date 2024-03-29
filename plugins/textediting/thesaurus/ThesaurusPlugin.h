/* This file is part of the KDE project
 * Copyright (C) 2007 Fredy Yanardi <fyanardi@gmail.com>
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

#ifndef THESAURUSPLUGIN_H
#define THESAURUSPLUGIN_H

#include <kpluginfactory.h>
#include <QObject>
#include <QVariant>

class ThesaurusPlugin : public QObject
{
    Q_OBJECT

public:
    ThesaurusPlugin(QObject * parent,  const QVariantList &);
    ~ThesaurusPlugin() override {}
};


class ThesaurusPluginFactory : public KPluginFactory
{
    Q_OBJECT
    Q_INTERFACES(KPluginFactory)
    Q_PLUGIN_METADATA(IID KPluginFactory_iid FILE "calligra_textediting_thesaurus.json")
public:
    explicit ThesaurusPluginFactory();
    ~ThesaurusPluginFactory();
};
#endif
