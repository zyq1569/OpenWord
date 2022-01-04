/* This file is part of the KDE project

   Copyright (C) 2013 Inge Wallin            <inge@lysator.liu.se>

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
#include "OdfTextReaderDocxBackend.h"

// Qt
#include <QtGlobal>

// Calligra
#include <KoXmlWriter.h>
#include <KoOdfStyle.h>
#include <KoOdfStyleManager.h>
#include <KoOdfStyleProperties.h>

// This filter
#include "OdfReaderDocxContext.h"
#include "DocxStyleHelper.h"
#include "DocxExportDebug.h"

#if 0
#define DEBUG_BACKEND() \
    debugDocx << (reader.isStartElement() ? "start": (reader.isEndElement() ? "end" : "other")) \
    << reader.qualifiedName().toString()
#else
#define DEBUG_BACKEND() \
    //NOTHING
#endif


// ================================================================
//                 class OdfTextReaderDocxBackend


OdfTextReaderDocxBackend::OdfTextReaderDocxBackend()
    : OdfTextReaderBackend()
    , m_insideSpanLevel(0)
    , m_currentOutlineLevel(-1)
    , m_commentIndex(0)
    , m_writeComment(false)
    , m_insideComment(false)
    , m_insideDcCreator(false)
    , m_insideDcDate(false)
    , m_insidetable(false)
    , m_currentParagraphTextProperties(0)
{
}

OdfTextReaderDocxBackend::~OdfTextReaderDocxBackend()
{
}


// ----------------------------------------------------------------
// Text level functions: paragraphs, headings, sections, frames, objects, etc

void OdfTextReaderDocxBackend::elementOfficeAnnotation(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }
    KoXmlWriter *writer = docxContext->m_commentsWriter;

    if (reader.isStartElement())
    {
        m_writeComment = true;
        m_insideComment = true;
        writer->startElement("w:comment");
        writer->addAttribute("w:id", m_commentIndex);
    }
    else
    {
        writer->endElement(); // w:comment
        m_insideComment = false;
    }
    Q_UNUSED(reader);
}

void OdfTextReaderDocxBackend::elementDcCreator(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    Q_UNUSED(reader);
    Q_UNUSED(context);
    if (reader.isStartElement())
    {
        m_insideDcCreator = true;
    }
    else
    {
        m_insideDcCreator = false;
    }
}

void OdfTextReaderDocxBackend::elementDcDate(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    Q_UNUSED(reader);
    Q_UNUSED(context);
    if (reader.isStartElement())
    {
        m_insideDcDate = true;
    }
    else
    {
        m_insideDcDate = false;
    }
}

void OdfTextReaderDocxBackend::elementTextH(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    KoXmlStreamAttributes attributes = reader.attributes();
    m_currentOutlineLevel = attributes.value("text:outline-level").toString().toInt();
    elementTextP(reader, context);
}

void OdfTextReaderDocxBackend::elementTextP(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }

    m_currentParagraphTextProperties = 0;
    m_currentParagraphParent.clear();

    KoXmlWriter *writer = docxContext->m_documentWriter;
    if (m_insideComment)
    {
        writer = docxContext->m_commentsWriter;
    }
    if (reader.isStartElement())
    {
        writer->startElement("w:p");
        if (m_insidetable)
        {
            return;
        }
        // FIXME: Add paragraph attributes here
        writer->startElement("w:pPr");
        if (m_currentOutlineLevel >= 1)
        {
            writer->startElement("w:outlineLvl");
            writer->addAttribute("w:val", m_currentOutlineLevel);
            writer->endElement(); // w:outlineLvl
        }
        KoXmlStreamAttributes attributes = reader.attributes();
        QString textStyle = attributes.value("text:style-name").toString();
        if (!textStyle.isEmpty())
        {
            KoOdfStyle *style = docxContext->styleManager()->style(textStyle, "paragraph");
            KoOdfStyleProperties *parProperties = style->properties("style:paragraph-properties");
            m_currentParagraphTextProperties = style->properties("style:text-properties");
            m_currentParagraphParent = style->parent();
            if (!m_currentParagraphParent.isEmpty())
            {
                writer->startElement("w:pStyle");
                if (m_currentParagraphParent.contains("_20"))
                {
                    QString stylenamenew = m_currentParagraphParent;
                    writer->addAttribute("w:val", stylenamenew.replace(QLatin1String("_20"), QLatin1String("")));
                }
                else
                {
                    writer->addAttribute("w:val", m_currentParagraphParent);
                }
                writer->endElement(); // w:pStyle
            }
            DocxStyleHelper::handleParagraphStyles(parProperties, writer);
            writer->startElement("w:rPr");
            DocxStyleHelper::handleTextStyles(m_currentParagraphTextProperties, writer);
            writer->endElement(); // w:rPr
        }
        // FIXME: Add paragraph properties (styling) here
        writer->endElement(); // w:pPr
    }
    else
    {
        writer->endElement(); // w:p
    }
}


///---------------------------- TableTable
void OdfTextReaderDocxBackend::elementTableTable(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }
    KoXmlWriter *writer = docxContext->m_documentWriter;
    if (m_insideComment)
    {
        writer = docxContext->m_commentsWriter;
    }
    if (reader.isStartElement())
    {
        m_insidetable = true;
        writer->startElement("w:tbl");

        writer->startElement("w:tblPr");
        // eg:
        // <w:tblW w:w="5000" w:type="pct"/>
        // <w:tblInd w:w="100" w:type="dxa"/>
        // <w:tblCellMar>
        //     <w:left w:w="10" w:type="dxa"/>
        //     <w:right w:w="10" w:type="dxa"/>
        // </w:tblCellMar>
        // <w:tblLook w:val="0000" w:firstRow="0" w:lastRow="0" w:firstColumn="0" w:lastColumn="0" w:noHBand="0" w:noVBand="0"/>
        writer->startElement("w:tblW");
        writer->addAttribute("w:w","5000");
        writer->addAttribute("w:type","pct");
        writer->endElement();//w:tblW

        writer->startElement("w:tblInd");
        writer->addAttribute("w:w","100");
        writer->addAttribute("w:type","dxa");
        writer->endElement();//w:tblInd

        writer->startElement("w:tblCellMar");
        writer->startElement("w:left");
        writer->addAttribute("w:w","10");
        writer->addAttribute("w:type","dxa");
        writer->endElement();//w:left
        writer->startElement("w:right");
        writer->addAttribute("w:w","10");
        writer->addAttribute("w:type","dxa");
        writer->endElement();//w:right
        writer->endElement();//w:tblCellMar

        writer->startElement("w:tblLook");
        writer->addAttribute("w:val","0000");
        writer->addAttribute("w:firstRow","0");
        writer->addAttribute("w:lastRow","0");
        writer->addAttribute("w:firstColumn","0");
        writer->addAttribute("w:lastColumn","0");
        writer->addAttribute("w:noHBand","0");
        writer->addAttribute("w:noVBand","0");
        writer->endElement();//w:tblLook
        writer->endElement(); // w:tblPr

    }
    else
    {
        writer->endElement();//"w:tbl"
        m_insidetable = false;
    }

}

/// odf : eg <table:table-column table:style-name="Table1.A" table:number-columns-repeated="4"/>
void OdfTextReaderDocxBackend::elementTableTableColumn(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }
    KoXmlWriter *writer = docxContext->m_documentWriter;
    if (m_insideComment)
    {
        writer = docxContext->m_commentsWriter;
    }
    if (reader.isStartElement())
    {
        writer->startElement("w:tblGrid");
        ///------------------------------
        KoXmlStreamAttributes attributes = reader.attributes();
        int number_columns = attributes.value("table:number-columns-repeated").toString().toInt();
        writer->startElement("w:gridCol");
        writer->addAttribute("w:w","2110");
        writer->endElement();//w:gridCol
        for (int i=1; i<number_columns; i++)
        {
            writer->startElement("w:gridCol");
            writer->addAttribute("w:w","2490");
            writer->endElement();//w:gridCol
        }
    }
    else
    {
        writer->endElement();//"w:tblGrid"
    }
}


void OdfTextReaderDocxBackend::elementTableTableColumns(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }
    KoXmlWriter *writer = docxContext->m_documentWriter;
    if (m_insideComment)
    {
        writer = docxContext->m_commentsWriter;
    }
    // docx eg:
    //<w:tblGrid>
    //    <w:gridCol w:w="2110"/>
    //    <w:gridCol w:w="2490"/>
    //    <w:gridCol w:w="2490"/>
    //    <w:gridCol w:w="2490"/>
    //</w:tblGrid>
    if (reader.isStartElement())
    {
        writer->startElement("w:tblGrid");
        KoXmlStreamAttributes attributes = reader.attributes();
        int number_columns = attributes.value("table:number-columns-repeated").toString().toInt();
        writer->startElement("w:gridCol");
        writer->addAttribute("w:w","2110");
        writer->endElement();//w:gridCol
        for (int i=1; i<number_columns; i++)
        {
            writer->startElement("w:gridCol");
            writer->addAttribute("w:w","2490");
            writer->endElement();//w:gridCol
        }
    }
    else
    {
        writer->endElement();//"w:tblGrid"
    }
}


void OdfTextReaderDocxBackend::elementTableTableRow(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }
    KoXmlWriter *writer = docxContext->m_documentWriter;
    if (m_insideComment)
    {
        writer = docxContext->m_commentsWriter;
    }
    // docx eg:
    //<w:tr
    //  <w:tblPrEx>
    //      <w:tblCellMar>
    //          <w:top w:w="0" w:type="dxa"/>
    //          <w:bottom w:w="0" w:type="dxa"/>
    //      </w:tblCellMar>
    //  </w:tblPrEx>
    //...
    //</w:tr>
    if (reader.isStartElement())
    {
        writer->startElement("w:tr");

        writer->startElement("w:tblPrEx");
        writer->startElement("w:tblCellMar");
        writer->startElement("w:top");
        writer->addAttribute("w:w","0");
        writer->addAttribute("w:type","dxa");
        writer->endElement();//w:top
        writer->startElement("w:bottom");
        writer->addAttribute("w:w","0");
        writer->addAttribute("w:type","dxa");
        writer->endElement();//w:bottom
        writer->endElement();// <w:tblCellMar>
        writer->endElement();//<w:tblPrEx>
    }
    else
    {
        writer->endElement();//"w:tr"
    }
}


void OdfTextReaderDocxBackend::elementTableTableCell(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }
    KoXmlWriter *writer = docxContext->m_documentWriter;
    if (m_insideComment)
    {
        writer = docxContext->m_commentsWriter;
    }
    //<w:tc>
    //    <w:tcPr>
    //        <w:tcW w:w="0" w:type="auto"/>
    //        <w:tcBorders>
    //            <w:top w:val="single" w:sz="18" w:space="0" w:color="000000"/>
    //            <w:left w:val="single" w:sz="18" w:space="0" w:color="000000"/>
    //            <w:bottom w:val="single" w:sz="18" w:space="0" w:color="000000"/>
    //            <w:right w:val="single" w:sz="18" w:space="0" w:color="000000"/>
    //        </w:tcBorders>
    //        <w:tcMar>
    //            <w:top w:w="100" w:type="dxa"/>
    //            <w:left w:w="100" w:type="dxa"/>
    //            <w:bottom w:w="100" w:type="dxa"/>
    //            <w:right w:w="100" w:type="dxa"/>
    //        </w:tcMar>
    //    </w:tcPr>
    //    <w:p w14:paraId="6F0111A3" w14:textId="77777777" w:rsidR="000B243E" w:rsidRDefault="00A21553">
    //        <w:r>
    //            <w:t>序号</w:t>
    //        </w:r>
    //    </w:p>
    //</w:tc>

    if (reader.isStartElement())
    {
        writer->startElement("w:tc");

        writer->startElement("w:tcPr");

        writer->startElement("w:tcW");
        writer->addAttribute("w:w","0");
        writer->addAttribute("w:type","auto");
        writer->endElement();//w:tcW

        writer->startElement("w:tcBorders");
        writer->startElement("w:top");
        writer->addAttribute("w:val","single");
        writer->addAttribute("w:sz","18");
        writer->addAttribute("w:space","0");
        writer->addAttribute("w:color","000000");
        writer->endElement();//w:top
        writer->startElement("w:left");
        writer->addAttribute("w:val","single");
        writer->addAttribute("w:sz","18");
        writer->addAttribute("w:space","0");
        writer->addAttribute("w:color","000000");
        writer->endElement();//w:left
        writer->startElement("w:bottom");
        writer->addAttribute("w:val","single");
        writer->addAttribute("w:sz","18");
        writer->addAttribute("w:space","0");
        writer->addAttribute("w:color","000000");
        writer->endElement();//w:bottom
        writer->startElement("w:right");
        writer->addAttribute("w:val","single");
        writer->addAttribute("w:sz","18");
        writer->addAttribute("w:space","0");
        writer->addAttribute("w:color","000000");
        writer->endElement();//w:right
        writer->endElement();//w:tcBorders

        writer->startElement("w:tcMar");
        writer->startElement("w:top");
        writer->addAttribute("w:w","100");
        writer->addAttribute("w:type","dxa");
        writer->endElement();//w:top
        writer->startElement("w:left");
        writer->addAttribute("w:w","100");
        writer->addAttribute("w:type","dxa");
        writer->endElement();//w:left
        writer->startElement("w:bottom");
        writer->addAttribute("w:w","100");
        writer->addAttribute("w:type","dxa");
        writer->endElement();//w:bottom
        writer->startElement("w:right");
        writer->addAttribute("w:w","100");
        writer->addAttribute("w:type","dxa");
        writer->endElement();//w:right
        writer->endElement();//w:tcMar

        writer->endElement();//<w:tcPr>

    }
    else
    {
        writer->endElement();//"w:tc"
    }
}

// ----------------------------------------------------------------
// Paragraph level functions: spans, annotations, notes, text content itself, etc.


void OdfTextReaderDocxBackend::elementTextSpan(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }

    if (reader.isStartElement())
    {
        startRun(reader, docxContext);
        ++m_insideSpanLevel;
    }
    else
    {
        endRun(docxContext);
        --m_insideSpanLevel;
    }
}

void OdfTextReaderDocxBackend::elementTextS(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    if (!reader.isStartElement())
    {
        return;
    }

    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }

#if 0
    QString dummy = element.attribute("text:c", "1");
    bool ok;
    int  numSpaces = dummy.toUInt(&ok);
    if (!ok)
    {
        numSpaces = 1;
    }

    // At the end of a paragraph, output two newlines.
    docxContext->outStream << "\n\n";
#endif
}


void OdfTextReaderDocxBackend::characterData(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }
    //debugDocx << reader.text().toString();

    if (m_insideDcCreator)
    {
        KoXmlWriter *commentsWriter = docxContext->m_commentsWriter;
        commentsWriter->addAttribute("w:author", reader.text().toString());
    }
    else if (m_insideDcDate)
    {
        //KoXmlWriter *commentsWriter = docxContext->m_commentsWriter;
        // todo, convert the date and add as attribute
    }
    else
    {
        // In docx, a text always has to be inside a run (w:r). This is
        // created when a text:span is encountered in odf but text nodes
        // can exist also without a text:span surrounding it.
        KoXmlWriter  *writer = docxContext->m_documentWriter;
        if (m_insideComment)
        {
            writer = docxContext->m_commentsWriter;
        }

        if (m_insideSpanLevel == 0)
        {
            startRun(reader, docxContext);
        }

        writer->startElement("w:t");
        writer->addTextNode(reader.text().toString());
        writer->endElement(); // w:t

        if (m_insideSpanLevel == 0)
        {
            endRun(docxContext);
        }
    }
}


// ----------------------------------------------------------------
//                         Private functions


void OdfTextReaderDocxBackend::startRun(const KoXmlStreamReader &reader, OdfReaderDocxContext *docxContext)
{
    KoXmlWriter *writer = docxContext->m_documentWriter;
    if (m_insideComment)
    {
        writer = docxContext->m_commentsWriter;
    }

    if (m_writeComment && !m_insideComment)
    {
        writer->startElement("w:commentRangeStart");
        writer->addAttribute("w:id", m_commentIndex);
        writer->endElement(); // w:commentRangeStart
    }
    writer->startElement("w:r");
    if (!m_insidetable)
    {
        writer->startElement("w:rPr");
    }
    KoXmlStreamAttributes attributes = reader.attributes();
    KoOdfStyleProperties properties;
    if (!m_currentParagraphParent.isEmpty())
    {
        DocxStyleHelper::inheritTextStyles(&properties, m_currentParagraphParent, docxContext->styleManager());
    }
    if (m_currentParagraphTextProperties != 0)
    {
        properties.copyPropertiesFrom(*m_currentParagraphTextProperties);
    }

    QString textStyle = attributes.value("text:style-name").toString();
    if (!textStyle.isEmpty())
    {
        KoOdfStyle *style = docxContext->styleManager()->style(textStyle, "text");
        KoOdfStyleProperties *textProperties = style->properties("style:text-properties");
        if (textProperties != 0)
        {
            properties.copyPropertiesFrom(*textProperties);
        }
        QString parent = style->parent();
        if (!parent.isEmpty())
        {
            writer->startElement("w:rStyle");
            writer->addAttribute("w:val", parent);
            writer->endElement(); // w:rStyle
        }
    }
    DocxStyleHelper::handleTextStyles(&properties, writer);
    if (!m_insidetable)
    {
        writer->endElement();    // w:rPr
    }
}

void OdfTextReaderDocxBackend::endRun(OdfReaderDocxContext *docxContext)
{
    // FIXME: More here?
    KoXmlWriter  *writer = docxContext->m_documentWriter;
    if (m_insideComment)
    {
        writer = docxContext->m_commentsWriter;
    }

    writer->endElement(); // w:r
    if (m_writeComment && !m_insideComment && !m_insidetable)
    {
        writer->startElement("w:commentRangeEnd");
        writer->addAttribute("w:id", m_commentIndex);
        writer->endElement(); // w:commentRangeEnd
        writer->startElement("w:r");
        writer->startElement("w:commentReference");
        writer->addAttribute("w:id", m_commentIndex);
        writer->endElement(); // w:commentReference
        writer->endElement(); // w:r
        ++m_commentIndex;
        m_writeComment = false;
    }
}
