/* This file is part of the KDE project

   Copyright (C) 2012 Inge Wallin            <inge@lysator.liu.se>

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
 * Boston, MA 02110-1301, USA.
*/


// Own
#include "OpcContentTypes.h"

// Qt
#include <QString>

// Calligra
#include <KoXmlWriter.h>
#include <KoStore.h>
#include <KoStoreDevice.h>

// This filter
#include "DocxExportDebug.h"


// ================================================================
//                         class OpcContentTypes

OpcContentTypes::OpcContentTypes()
{
}

OpcContentTypes::~OpcContentTypes()
{
}


void OpcContentTypes::addDefault(const QString &extension, const QString &contentType)
{
    defaults[extension] = contentType;
}

void OpcContentTypes::addFile(const QString &partName, const QString &contentType)
{
    parts[partName] = contentType;
}


KoFilter::ConversionStatus OpcContentTypes::writeToStore(KoStore *opcStore)
{
    // We can hardcode this one.
    if (!opcStore->open("[Content_Types].xml"))
    {
        debugDocx << "Can not to open [Content_Types].xml.";
        return KoFilter::CreationError;
    }

    KoStoreDevice metaDevice(opcStore);
    KoXmlWriter writer(&metaDevice);

    writer.startDocument(0, 0, 0/*, true*/);
    writer.startElement("Types");
    writer.addAttribute("xmlns", "http://schemas.openxmlformats.org/package/2006/content-types");

    // Write defaults
    foreach (const QString &def, defaults.keys())
    {
        writer.startElement("Default");
        writer.addAttribute("Extension", def);
        writer.addAttribute("ContentType", defaults.value(def));
        writer.endElement(); // Default
    }

    // Write overrides.  Only write those which don't fit the defaults.
    foreach (const QString &part, parts.keys())
    {
        bool found = false;
        foreach (const QString &extension, defaults.keys())
        {
            if (part.endsWith(extension) && parts.value(part) == defaults.value(extension))
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            // No need to write this one
            continue;
        }

        writer.startElement("Override");
        writer.addAttribute("PartName", part);
        writer.addAttribute("ContentType", parts.value(part));
        writer.endElement(); // Override
    }
    //    docxFile.addContentFile("", "/word/numbering.xml",
    //                            "application/vnd.openxmlformats-officedocument.wordprocessingml.numbering+xml",
    //                            docxBackendContext.documentContent());
    // openword add:
    writer.startElement("Override");
    writer.addAttribute("PartName", "/word/numbering.xml");
    writer.addAttribute("ContentType", "application/vnd.openxmlformats-officedocument.wordprocessingml.numbering+xml");
    writer.endElement(); // Default


    writer.endElement();  // Types
    writer.endDocument();

    opcStore->close();
    return KoFilter::OK;
}


///
///
///
// ================================================================
//                         class DocPropsFiles

DocPropsFiles::DocPropsFiles(QString filename)
{
    m_filename = filename;
}

DocPropsFiles::~DocPropsFiles()
{
}

void DocPropsFiles::setFilename( QString filename)
{
    if (filename.length() > 0)
    {
        m_filename = filename;
    }
}

void DocPropsFiles::addDefault(const QString &extension, const QString &contentType)
{
    defaults[extension] = contentType;
}

void DocPropsFiles::addFile(const QString &partName, const QString &contentType)
{
    parts[partName] = contentType;
}


KoFilter::ConversionStatus DocPropsFiles::writeToStore(KoStore *docPropsFiles)
{
    // We can hardcode this one.
    if (!docPropsFiles->open(m_filename))
    {
        debugDocx << "Can not to open " + m_filename;
        return KoFilter::CreationError;
    }

    KoStoreDevice metaDevice(docPropsFiles);
    KoXmlWriter writer(&metaDevice);

    writer.startDocument(0, 0, 0/*, true*/);

    if (m_filename.contains("app.xml"))
    {
        writer.startElement("Properties");
        writer.addAttribute("xmlns",    "http://schemas.openxmlformats.org/officeDocument/2006/extended-properties");
        writer.addAttribute("xmlns:vt", "http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes");

        ///eg
        //<text:page-count>3</text:page-count>
        //startElement("text:page-count", false);
        //addTextNode(value());
        //endElement();
        writer.startElement("Template",false);
        writer.addTextNode("Normal");
        writer.endElement();

        writer.startElement("TotalTime",false);
        writer.addTextNode("0");
        writer.endElement();

        writer.startElement("Pages",false);
        writer.addTextNode("1");//Pages :
        writer.endElement();

        writer.startElement("Words",false);
        writer.addTextNode("1");//Words :
        writer.endElement();

        writer.startElement("Characters",false);
        writer.addTextNode("1");//Characters :
        writer.endElement();


        writer.startElement("Application",false);
        writer.addTextNode("Office Openword ");//Characters :
        writer.endElement();

        writer.startElement("DocSecurity",false);
        writer.addTextNode("0");//Characters :
        writer.endElement();

        writer.startElement("Lines",false);
        writer.addTextNode("1");
        writer.endElement();

        writer.startElement("Paragraphs",false);
        writer.addTextNode("1");
        writer.endElement();

        writer.startElement("ScaleCrop",false);
        writer.addTextNode("false");//Pages :
        writer.endElement();

        writer.startElement("Company",false);
        writer.addTextNode("Open");//Words :
        writer.endElement();

        writer.startElement("LinksUpToDate",false);
        writer.addTextNode("false");//Characters :
        writer.endElement();


        writer.startElement("CharactersWithSpaces",false);
        writer.addTextNode("1");//Characters :
        writer.endElement();

        writer.startElement("SharedDoc",false);
        writer.addTextNode("false");//Characters :
        writer.endElement();

        writer.startElement("HyperlinksChanged",false);
        writer.addTextNode("false");//Characters :
        writer.endElement();

        writer.startElement("AppVersion",false);
        writer.addTextNode("3.2.1.0");//Characters :
        writer.endElement();
    }
    else if (m_filename.contains("core.xml"))
    {
        writer.startElement("cp:coreProperties");
        writer.addAttribute("xmlns:cp", "http://schemas.openxmlformats.org/package/2006/metadata/core-properties");
        writer.addAttribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
        writer.addAttribute("xmlns:dcterms", "hthttp://purl.org/dc/terms/");
        writer.addAttribute("xmlns:dcmitype", "http://purl.org/dc/dcmitype/");
        writer.addAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");

        writer.startElement("dc:title");
        writer.endElement();

        writer.startElement("dc:subject");
        writer.endElement();

        writer.startElement("dc:creator",false);
        writer.addTextNode("created:pc name");
        writer.endElement();

        writer.startElement("cp:keywords");
        writer.endElement();

        writer.startElement("dc:description");
        writer.endElement();


        writer.startElement("cp:lastModifiedBy",false);
        writer.addTextNode("modified:pc name ");
        writer.endElement();

        writer.startElement("dcterms:created xsi:type=\"dcterms:W3CDTF\"",false);
        writer.addTextNode("2021-09-07T01:12:00Z");// create time
        writer.endElement();

        writer.startElement("dcterms:modified xsi:type=\"dcterms:W3CDTF\"",false);
        writer.addTextNode("2021-09-07T02:11:00Z");
        writer.endElement();
    }
    else if (m_filename.contains("custom.xml"))
    {
        writer.startElement("Properties");
        writer.addAttribute("xmlns", "http://schemas.openxmlformats.org/officeDocument/2006/custom-properties");
        writer.addAttribute("xmlns:vt", "http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes");

        writer.startElement("property",false);
        writer.addAttribute("fmtid", "{D5CDD505-2E9C-101B-9397-08002B2CF9AE}");
        writer.addAttribute("pid", "2");
        writer.addAttribute("name", "KSOProductBuildVer");

        writer.startElement("vt:lpwstr",false);
        writer.addTextNode("2052-11.1.0.8500");
        writer.endElement();

        writer.endElement();
    }

    writer.endElement();
    writer.endDocument();//startElement

    docPropsFiles->close();
    return KoFilter::OK;
}
