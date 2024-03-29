
/*
 * This file is part of Office 2007 Filters for Calligra
 *
 * Copyright (C) 2009-2010 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef MSOOXMLRELATIONSHIPS_H
#define MSOOXMLRELATIONSHIPS_H

#include "komsooxml_export.h"

struct KoOdfWriters;
class QString;

namespace MSOOXML
{
class MsooXmlImport;

//! Global document relationships handler.
/*! It supports delayed loading of any *.xml.rels file. */
//! @todo add write methods and saving support
class KOMSOOXML_EXPORT MsooXmlRelationships
{
public:
    explicit MsooXmlRelationships(MsooXmlImport& importer, KoOdfWriters *writers, QString& errorMessage);

    ~MsooXmlRelationships();

    QString target(const QString& path, const QString& file, const QString& id);

    QString targetForType(const QString& path, const QString& file, const QString& relType);

    unsigned targetCountWithWord(const QString& searchTerm);

private:
    class Private;
    Private* const d;
};

namespace Relationships
{
static const char comments[] = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/comments";
static const char commentAuthors[] = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/commentAuthors";
static const char tableStyles[] = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/tableStyles";
}

}

#endif //MSOOXMLRELATIONSHIPSREADER_H
