/* This file is part of the KDE project
  *
  * Copyright (C) 2013 Inge Wallin <inge@lysator.liu.se>
  * Copyright (C) 2013 Mojtaba Shahi Senobari <mojtaba.shahi3000@gmail.com>
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

// Own
#include "KoOdfListStyle.h"

// Qt
#include <QString>

// Odflib
#include "KoXmlStreamReader.h"
#include "KoXmlWriter.h"
#include "KoOdfStyleProperties.h"
#include "KoOdfTextProperties.h"
#include "KoOdfListLevelProperties.h"

#include "Odf2Debug.h"

// ================================================================
//                         class KoOdfListStyle

class Q_DECL_HIDDEN KoOdfListStyle::Private
{
public:
    Private();
    ~Private();

    QString name;
    QString displayName;
    QString listLevelType;
    bool    isDefaultStyle;
    bool    inUse;
    //
    QHash<QString, KoOdfStyleProperties*> properties;  // e.g. "text-properties",

    //open word : save AttributeSet list-level-style-number/bullet/image

    //<text:list-level-style-number text:start-value="1" text:display-levels="1" style:num-prefix="" style:num-suffix=")" style:num-format="a" text:level="1">
    //text:list-level-style-bullet text:bullet-char="●" text:level="1">
    AttributeSet tagAttributes;

    //save eg:text:outline-level-style
    //<text:outline-level-style text:start-value="1" text:display-levels="1" style:num-prefix="" style:num-suffix="." style:num-format="1" text:level="1">
    //    <style:list-level-properties text:list-level-position-and-space-mode="label-width-and-position" fo:text-align="start"/>
    //</text:outline-level-style>
    //<text:outline-level-style text:start-value="1" text:display-levels="2" style:num-prefix="" style:num-suffix="." style:num-format="1" text:level="2">
    //    <style:list-level-properties text:list-level-position-and-space-mode="label-width-and-position" fo:text-align="start"/>
    //</text:outline-level-style>
    //<text:outline-level-style text:start-value="1" text:display-levels="3" style:num-prefix="" style:num-suffix="." style:num-format="1" text:level="3">
    //    <style:list-level-properties text:list-level-position-and-space-mode="label-width-and-position" fo:text-align="start"/>
    //</text:outline-level-style>
    QHash<int, AttributeSet> outline_level_style;
};

KoOdfListStyle::Private::Private()
    : isDefaultStyle(false)
    , inUse(false)
{
}

KoOdfListStyle::Private::~Private()
{
    qDeleteAll(properties);
}

KoOdfListStyle::KoOdfListStyle()
    :d(new KoOdfListStyle::Private())
{
}

KoOdfListStyle::~KoOdfListStyle()
{
    delete d;
}

QString KoOdfListStyle::name() const
{
    return d->name;
}

void KoOdfListStyle::setName(QString &name)
{
    d->name = name;
}

QString KoOdfListStyle::displayName() const
{
    return d->displayName;
}

void KoOdfListStyle::setDisplayName(QString &name)
{
    d->displayName = name;
}

QString KoOdfListStyle::listLevelStyleType() const
{
    return d->listLevelType;
}

void KoOdfListStyle::setListLevelStyleType(QString &name)
{
    d->listLevelType = name;
}

bool KoOdfListStyle::inUse() const
{
    return d->inUse;
}

void KoOdfListStyle::setInUse(bool inUse)
{
    d->inUse = inUse;
}

QHash<QString, KoOdfStyleProperties*> KoOdfListStyle::properties()
{
    return d->properties;
}

KoOdfStyleProperties *KoOdfListStyle::properties(QString &name) const
{
    return d->properties.value(name, 0);
}

QString KoOdfListStyle::property(QString &propertySet, QString &property) const
{
    KoOdfStyleProperties *props = d->properties.value(propertySet, 0);
    if (props)
    {
        return props->attribute(property);
    }
    else
    {
        return QString();
    }
}

void KoOdfListStyle::setProperty(QString &propertySet, QString &property, QString &value)
{
    KoOdfStyleProperties *props = d->properties.value(propertySet);
    if (!props)
    {
        props = new KoOdfStyleProperties();
    }
    props->setAttribute(property, value);
}

bool KoOdfListStyle::readProperties(KoXmlStreamReader &reader)
{
    // Load child elements: property sets and other children.
    while (reader.readNextStartElement())
    {
        // So far we only have support for text-properties and list-level-properties.
        QString propertiesType = reader.qualifiedName().toString();
        debugOdf2 << "properties type: " << propertiesType;

        // Create a new propertyset variable depending on the type of properties.
        KoOdfStyleProperties *properties;
        if (propertiesType == "style:text-properties")
        {
            properties = new KoOdfTextProperties();
        }
        else if (propertiesType == "style:list-level-properties")
        {
            properties = new KoOdfListLevelProperties();
        }
        else
        {
            // FIXME: support office:binary-data
            // debugOdf2 << "Unsupported property type: " << propertiesType;
            reader.skipCurrentElement();
            continue;
        }

        if (!properties->readOdf(reader))
        {
            return false;
        }
        d->properties[propertiesType] = properties;
    }

    return true;
}

bool KoOdfListStyle::readOdf(KoXmlStreamReader &reader)
{
    // Load style attributes.
    KoXmlStreamAttributes  attrs = reader.attributes();
    QString dummy;              // Because the set*() methods take a QString &,

    dummy = attrs.value("style:name").toString();
    setName(dummy);
    dummy = attrs.value("style:display-name").toString();
    setDisplayName(dummy);

    debugOdf2 << "KoOdfListStyle::readOdf --Style:" << name() << displayName();

    QString listLevelType = reader.qualifiedName().toString();
    if (listLevelType == "text:outline-style" )
    {
        setListLevelStyleType(listLevelType);
        while (reader.readNextStartElement())
        {
            // So far we only have support for text-, paragraph- and graphic-properties
            // And ltext:outline-level-styl.
            listLevelType = reader.qualifiedName().toString();
            if (listLevelType == "text:outline-level-style")
            {
                KoXmlStreamAttributes attrs = reader.attributes();
                AttributeSet outAttributeSet;
                foreach (const KoXmlStreamAttribute &attr, attrs)
                {
                    outAttributeSet.insert(attr.qualifiedName().toString(), attr.value().toString());
                }
                if (reader.readNextStartElement())
                {
                    listLevelType = reader.qualifiedName().toString();
                    if (listLevelType == "style:list-level-properties")
                    {
                        attrs = reader.attributes();
                        foreach (const KoXmlStreamAttribute &attr, attrs)
                        {
                            outAttributeSet.insert(attr.qualifiedName().toString(), attr.value().toString());
                        }
                    }
                }
                int index = d->outline_level_style.size();
                d->outline_level_style.insert(index,outAttributeSet);
            }
            reader.readNext();//point end -Element:style:list-level-properties
            reader.readNext();//point end -Element:text:outline-level-style
        }
        return true;
    }
    // Load child elements: list-level-style-bullet, text:list-level-style-number, text:list-level-style-image
    while (reader.readNextStartElement())
    {
        QString tagName = reader.qualifiedName().toString();
        // So far we only have support for text-, paragraph- and graphic-properties
        // And list-level-style-bullet, list-level-style-image, list-level-style-number for List-style.
        /*QString*/ listLevelType = reader.qualifiedName().toString();
        setListLevelStyleType(listLevelType);
        if (listLevelType == "text:list-level-style-bullet"
                || listLevelType == "text:list-level-style-number"
                || listLevelType == "text:list-level-style-image")
        {

            //save eg.
            //<text:list-level-style-number text:start-value="1" text:display-levels="1" style:num-prefix="" style:num-suffix=")" style:num-format="a" text:level="1">
            KoXmlStreamAttributes attrs = reader.attributes();
            foreach (const KoXmlStreamAttribute &attr, attrs)
            {
                d->tagAttributes.insert(attr.qualifiedName().toString(), attr.value().toString());
            }
            if (!readProperties(reader))
            {
                return false;
            }
            return true;//20211231 openword add:是否源码错误还是修改问题,待进一步理解
        }
    }

    return true;
}

bool KoOdfListStyle::saveOdf(KoXmlWriter *writer)
{
    writer->startElement("text:list-style");
    // Write style attributes
    if (!d->displayName.isEmpty())
    {
        writer->addAttribute("style:display-name", d->displayName);
    }

    // Write child element
    writer->startElement(listLevelStyleType().toUtf8());
    // Write properties
    foreach(const QString &propertySet, d->properties.keys())
    {
        d->properties.value(propertySet)->saveOdf(propertySet, writer);
    }
    writer->endElement();

    writer->endElement();
    return true;
}

//openword add:
QHash<int, AttributeSet> KoOdfListStyle::getOutLineAttributeSet() const
{
    return d->outline_level_style;
}
