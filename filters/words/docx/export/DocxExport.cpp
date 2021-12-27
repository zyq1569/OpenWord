/* This file is part of the KDE project
   Copyright (C) 1998, 1999 Reginald Stadlbauer <reggie@kde.org>
   Copyright (C) 2000 Michael Johnson <mikej@xnet.com>
   Copyright (C) 2001, 2002, 2004 Nicolas GOUTTE <goutte@kde.org>
   Copyright (C) 2010-2011 Thorsten Zachmann <zachmann@kde.org>
   Copyright (C) 2010 Christoph Cullmann <cullmann@kde.org>
   Copyright (C) 2013-2014 Inge Wallin <inge@lysator.liu.se>

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

#include "DocxExport.h"

#include <QFile>

// KF5
//#include <kpluginfactory.h>

// Calligra
#include <KoStore.h>
#include <KoFilterChain.h>
#include <KoXmlWriter.h>

// Filter libraries
#include "OdtReader.h"

// This filter
#include "DocxFile.h"
#include "DocxStyleWriter.h"
#include "OdfReaderDocxContext.h"
#include "OdtReaderDocxBackend.h"
///
#include "odfdrawreaderdocxbackend.h"
#include "OdfReaderContext.h"
///
#include "OdfTextReaderDocxBackend.h"
#include "OdfDrawReader.h"

#include "DocxExportDebug.h"

///openword
//K_PLUGIN_FACTORY_WITH_JSON(DocxExportFactory, "calligra_filter_odt2docx.json",
//                           registerPlugin<DocxExport>();)

// Needed to instantiate the plugin factory.
//#include "DocxExport.moc"

DocxExportFactory::DocxExportFactory()
{
    registerPlugin<DocxExport>();
}

DocxExportFactory::~DocxExportFactory()
{
}


///-------------------------------------------------------------------------------------------------
DocxExport::DocxExport(QObject *parent, const QVariantList &)
    : KoFilter(parent)
{
}

DocxExport::~DocxExport()
{
}

KoFilter::ConversionStatus DocxExport::convert(const QByteArray& from, const QByteArray& to)
{
    // Check for types
    if (from != "application/vnd.oasis.opendocument.text"
            || to != "application/vnd.openxmlformats-officedocument.wordprocessingml.document")
    {
        return KoFilter::NotImplemented;
    }

    // Open the infile and return an error if it fails.
    KoStore *odfStore = KoStore::createStore(m_chain->inputFile(), KoStore::Read,
                        "", KoStore::Auto);
    if (!odfStore->open("mimetype"))
    {
        errorDocx << "Unable to open input file!" << endl;
        delete odfStore;
        return KoFilter::FileNotFound;
    }
    odfStore->close();

    // Start the conversion

    // Collects all the parts of the docx file and writes the result at the end.
    DocxFile docxFile;

    OdfReaderDocxContext      docxBackendContext(odfStore, &docxFile);

    // The backends
    OdtReaderDocxBackend      docxBackend;
    OdfTextReaderDocxBackend  docxTextBackend;

    /// OdfDrawReader
    OdfDrawReader            odfDrawReader;
    OdfDrawReaderDocxBackend  OdfDrawDocxbackend;

    // The readers
    OdtReader                 odtReader;
    OdfTextReader             odfTextReader;

    odfTextReader.setBackend(&docxTextBackend);
    odtReader.setTextReader(&odfTextReader);

    odfDrawReader.setBackend(&OdfDrawDocxbackend);
    odtReader.setDrawReader(&odfDrawReader);

    if (!odtReader.analyzeContent(&docxBackendContext))
    {
        return KoFilter::ParsingError;
    }

    DocxStyleWriter           styleWriter(&docxBackendContext);
    styleWriter.read();

    // Add the styles to the docx file.
    docxFile.addContentFile("", "/word/styles.xml",
                            "application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml",
                            styleWriter.documentContent());

    /// body ?document.xml
    if (!odtReader.readContent(&docxBackend, &docxBackendContext))
    {
        return KoFilter::ParsingError;
    }

    bool commentsExist = !docxBackendContext.commentsContent().isEmpty();

    if (commentsExist)
    {
        // Add comments file
        QByteArray tempArray;
        QBuffer tempBuffer(&tempArray);
        KoXmlWriter commentWriter(&tempBuffer);
        commentWriter.startDocument(0);
        commentWriter.startElement("w:comments");
        commentWriter.addAttribute("xmlns:w", "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
        commentWriter.addCompleteElement(docxBackendContext.commentsContent());
        commentWriter.endElement(); // w:comments
        commentWriter.endDocument();
        docxFile.addContentFile("", "/word/comments.xml",
                                "application/vnd.openxmlformats-officedocument.wordprocessingml.comments+xml",
                                tempArray);
    }

    // Add the newly converted document contents to the docx file.
    docxFile.addContentFile("", "/word/document.xml",
                            "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml",
                            docxBackendContext.documentContent());

    //add openword
//    docxFile.addContentFile("", "/docProps/app.xml",
//                            "application/vnd.openxmlformats-officedocument.extended-properties+xml",
//                            docxBackendContext.documentContent());

//    docxFile.addContentFile("", "/docProps/core.xml",
//                            "application/vnd.openxmlformats-package.core-properties+xml",
//                            docxBackendContext.documentContent());

//    docxFile.addContentFile("", "/word/numbering.xml",
//                            "application/vnd.openxmlformats-officedocument.wordprocessingml.numbering+xml",
//                            docxBackendContext.documentContent());

//    docxFile.addContentFile("", "/word/settings.xml",
//                            "application/vnd.openxmlformats-officedocument.wordprocessingml.settings+xml",
//                            docxBackendContext.documentContent());

//    docxFile.addContentFile("", "/word/fontTable.xml",
//                            "application/vnd.openxmlformats-officedocument.wordprocessingml.fontTable+xml",
//                            docxBackendContext.documentContent());

//    docxFile.addContentFile("", "/word/webSettings.xml",
//                            "application/vnd.openxmlformats-officedocument.wordprocessingml.webSettings+xml",
//                            docxBackendContext.documentContent());

//    docxFile.addContentFile("", "/word/theme/theme1.xml",
//                            "application/vnd.openxmlformats-officedocument.theme+xml",
//                            docxBackendContext.documentContent());

    //docxFile.addContentFile("", "/docProps/custom.xml",
    //                        "application/vnd.openxmlformats-officedocument.custom-properties+xml",
    //                        docxBackendContext.documentContent());

    docxFile.setOdfDrawReaderBackend(&OdfDrawDocxbackend);
    // Write the output file.
    return docxFile.writeDocx(m_chain->inputFile(), m_chain->outputFile(), to, docxBackendContext, commentsExist);
}
