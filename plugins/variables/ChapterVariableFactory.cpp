/* This file is part of the KDE project
 * Copyright (C) 2011 Sebastian Sauer <mail@dipe.org>
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

#include "ChapterVariableFactory.h"
#include "ChapterVariable.h"
#include "VariablesDebug.h"

#include <KoProperties.h>
#include <KoXmlNS.h>

#include <klocalizedstring.h>

ChapterVariableFactory::ChapterVariableFactory()
    : KoInlineObjectFactoryBase("chapter", TextVariable)
{
    KoInlineObjectTemplate var1;
    var1.id = "chapter";
    var1.name = i18n("Chapter");
    KoProperties *props = new KoProperties();
    props->setProperty("vartype", KoInlineObject::Chapter);
    props->setProperty("format", 2);
    props->setProperty("level", 1);
    var1.properties = props;
    addTemplate(var1);

    QStringList elementNames;
    elementNames << "chapter";
    setOdfElementNames(KoXmlNS::text, elementNames);
}

KoInlineObject *ChapterVariableFactory::createInlineObject(const KoProperties *properties) const
{
    ChapterVariable *var = new ChapterVariable();
    if (properties)
        var->readProperties(properties);
    return var;
}

