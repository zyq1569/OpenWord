/* This file is part of the KDE project

   Copyright (C) 2012-2014 Inge Wallin            <inge@lysator.liu.se>

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
   Boston, MA 02110-1301, USA.
*/


// Own
#include "OdtReader.h"

// Qt
#include <QStringList>
#include <QBuffer>

// KF5
#include <klocalizedstring.h>

// Calligra
#include <KoStore.h>
#include <KoXmlStreamReader.h>
#include <KoXmlNS.h>

// Reader library
#include "OdtReaderBackend.h"
#include "OdfReaderContext.h"
#include "OdfTextReader.h"
#include "OdfReaderDebug.h"


#if 0
static int debugIndent = 0;
#define DEBUGSTART() \
    ++debugIndent; \
    DEBUG_READING("entering")
#define DEBUGEND() \
    DEBUG_READING("exiting"); \
    --debugIndent
#define DEBUG_READING(param) \
    debugOdfReader << QString("%1").arg(" ", debugIndent * 2) << param << ": " \
    << (reader.isStartElement() ? "start": (reader.isEndElement() ? "end" : "other")) \
    << reader.qualifiedName().toString()
#else
#define DEBUGSTART() \
    // NOTHING
#define DEBUGEND() \
    // NOTHING
#define DEBUG_READING(param) \
    // NOTHING
#endif


OdtReader::OdtReader()
    : OdfReader()
{
}

OdtReader::~OdtReader()
{
}

#if 0
// This is a template function for the reader library.
// Copy this one and change the name and fill in the code.
void OdtReader::readElementNamespaceTagname(KoXmlStreamReader &reader)
{
    DEBUGSTART();

    // <namespace:tagname> has the following children in ODF 1.2:
    //   FILL IN THE CHILDREN LIKE THIS EXAMPLE (taken from office:document-content):
    //          <office:automatic-styles> 3.15.3
    //          <office:body> 3.3
    //          <office:font-face-decls> 3.14
    //          <office:scripts> 3.12.
    while (reader.readNextStartElement())
    {
        QString tagName = reader.qualifiedName().toString();

        if (tagName == "office:automatic-styles")
        {
            // FIXME: NYI
        }
        else if (tagName == "office:body")
        {
            readElementOfficeBody(reader);
        }
        ...  MORE else if () HERE
            else
            {
                reader.skipCurrentElement();
            }
    }

    m_backend->elementNamespaceTagname(reader, m_context);
    DEBUGEND();
}
#endif

// Reimplemented from OdfReader
void OdtReader::readElementOfficeText(KoXmlStreamReader &reader)
{
    DEBUGSTART();
    OdtReaderBackend *backend = dynamic_cast<OdtReaderBackend *>(m_backend);
    backend->elementOfficeText(reader, m_context);

    // <office:text> has the following children in ODF 1.2:
    //
    // In addition to the text level tags like <text:p> etc that can
    // be found in any textbox, table cell or similar, it has the
    // following text document children:
    //
    //          <office:forms> 13.2
    //          <table:calculation-settings> 9.4.1
    //          <table:consolidation> 9.7
    //          <table:content-validations> 9.4.4
    //          <table:database-ranges> 9.4.14
    //          <table:data-pilot-tables> 9.6.2
    //          <table:dde-links> 9.8
    //          <table:label-ranges> 9.4.10
    //          <table:named-expressions> 9.4.11
    //          <text:alphabetical-index-auto-mark-file> 8.8.3
    //          <text:dde-connection-decls> 14.6.2
    //          <text:page-sequence> 5.2
    //          <text:sequence-decls> 7.4.11
    //          <text:tracked-changes> 5.5.1
    //          <text:user-field-decls> 7.4.7
    //          <text:variable-decls> 7.4.2
    //
    // FIXME: For now, none of these are handled
    while (reader.readNextStartElement())
    {
        DEBUG_READING("loop-start");

        QString tagName = reader.qualifiedName().toString();
        if (tagName == "office:forms")
        {
            // FIXME: NYI
            reader.skipCurrentElement();
        }
        else if (tagName == "table:calculation-settings")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "table:consolidation")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "table:content-validation")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "table:database-ranges")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "table:data-pilot-tables")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "table:dde-links")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "table:label-ranges")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "table:named-expressions")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "text:alphabetical-index-auto-mark-file")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "text:dde-connection-decls")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "text:page-sequence")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "text:sequence-decls")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "text:tracked-changes")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "text:user-field-decls")
        {
            reader.skipCurrentElement();
        }
        else if (tagName == "text:variable-decls")
        {
            reader.skipCurrentElement();
        }
        else
        {
            if (m_textReader)
            {
                m_textReader->readTextLevelElement(reader);
            }
            else
            {
                reader.skipCurrentElement();
            }
        }
        DEBUG_READING("loop-end");
    }

    backend->elementOfficeText(reader, m_context);
    DEBUGEND();
}


// ----------------------------------------------------------------
//                             Other functions
