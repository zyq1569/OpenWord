/*
 * This file is part of Office 2007 Filters for Calligra
 * Copyright (C) 2002 Laurent Montel <lmontel@mandrakesoft.com>
 * Copyright (C) 2003 David Faure <faure@kde.org>
 * Copyright (C) 2002, 2003, 2004 Nicolas GOUTTE <goutte@kde.org>
 * Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Suresh Chande suresh.chande@nokia.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifndef DOCXIMPORT_H
#define DOCXIMPORT_H

#include <kpluginfactory.h>

#include <MsooXmlImport.h>
#include <QVariantList>

//! DOCX to ODT import filter
class DocxImport : public MSOOXML::MsooXmlImport
{
    Q_OBJECT
public:
    DocxImport(QObject * parent, const QVariantList &);
    ~DocxImport() override;

    /// Access the content defined within the words/settings.xml configuration-file.
    QMap<QString, QVariant> documentSettings() const;
    QVariant documentSetting(const QString& name) const;

protected:
    bool acceptsSourceMimeType(const QByteArray& mime) const override;

    bool acceptsDestinationMimeType(const QByteArray& mime) const override;

    KoFilter::ConversionStatus parseParts(KoOdfWriters *writers, MSOOXML::MsooXmlRelationships *relationships,
            QString& errorMessage) override;

    void writeConfigurationSettings(KoXmlWriter* settings) const override;

    class Private;
    Private * const d;
};


class DocxImportFactory : public KPluginFactory
{
    Q_OBJECT
    Q_INTERFACES(KPluginFactory)
    Q_PLUGIN_METADATA(IID KPluginFactory_iid FILE  "calligra_filter_docx2odt.json")
public:
    explicit DocxImportFactory();
    ~DocxImportFactory();
};



#endif
