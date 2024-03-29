/* This file is part of the KDE project

   Copyright (C) 2014 Lassi Nieminen <lassniem@gmail.com>

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
#include "DocxStyleWriter.h"

// Qt
#include <QByteArray>
#include <QBuffer>

// Calligra
#include <KoXmlWriter.h>
#include <OdfReaderContext.h>
#include <KoOdfStyleManager.h>
#include <KoOdfStyle.h>
#include <KoOdfStyleProperties.h>

// This filter
#include "DocxStyleHelper.h"

// ----------------------------------------------------------------
//                     class DocxStyleWriter

DocxStyleWriter::DocxStyleWriter(OdfReaderContext *context)
    : m_readerContext(context)
    , m_documentContent()
    , m_documentIO(&m_documentContent)
{
    m_documentWriter = new KoXmlWriter(&m_documentIO);
}

DocxStyleWriter::~DocxStyleWriter()
{
    delete m_documentWriter;
}

QByteArray DocxStyleWriter::documentContent() const
{
    return m_documentContent;
}

void DocxStyleWriter::read()
{
    KoOdfStyleManager *manager = m_readerContext->styleManager();
    m_documentWriter->startDocument(0,0,0);
    m_documentWriter->startElement("w:styles");
    //m_documentWriter->addAttribute("xmlns:r", "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    //m_documentWriter->addAttribute("xmlns:w", "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    ///----------------MSword2016----------------------------------------------
    m_documentWriter->addAttribute("xmlns:mc","http://schemas.openxmlformats.org/markup-compatibility/2006");
    m_documentWriter->addAttribute("xmlns:r","http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    m_documentWriter->addAttribute("xmlns:w","http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    m_documentWriter->addAttribute("xmlns:w14","http://schemas.microsoft.com/office/word/2010/wordml");
    m_documentWriter->addAttribute("xmlns:w15","http://schemas.microsoft.com/office/word/2012/wordml");
    m_documentWriter->addAttribute("xmlns:w16cex","http://schemas.microsoft.com/office/word/2018/wordml/cex");
    m_documentWriter->addAttribute("xmlns:w16cid","http://schemas.microsoft.com/office/word/2016/wordml/cid");
    m_documentWriter->addAttribute("xmlns:w16","http://schemas.microsoft.com/office/word/2018/wordml");
    m_documentWriter->addAttribute("xmlns:w16sdtdh","http://schemas.microsoft.com/office/word/2020/wordml/sdtdatahash");
    m_documentWriter->addAttribute("xmlns:w16se","http://schemas.microsoft.com/office/word/2015/wordml/symex");
    m_documentWriter->addAttribute("mc:Ignorable","w14 w15 w16se w16cid w16 w16cex w16sdtdh");
    ///-------------------------------------------------------------------------

    QList<KoOdfStyle*> defaultStyles = manager->defaultStyles();
    m_documentWriter->startElement("w:docDefaults");
    foreach (KoOdfStyle* style, defaultStyles)
    {
        if (!style->isFromStylesXml())
        {
            continue;
        }
        QString family = style->family();
        if (family == "paragraph")
        {
            m_documentWriter->startElement("w:pPrDefault");
            m_documentWriter->startElement("w:pPr");
            KoOdfStyleProperties *paragraphProperties = style->properties("style:paragraph-properties");
            DocxStyleHelper::handleParagraphStyles(paragraphProperties, m_documentWriter);
            KoOdfStyleProperties *textProperties = style->properties("style:text-properties");
            m_documentWriter->startElement("w:rPr");
            DocxStyleHelper::handleTextStyles(textProperties, m_documentWriter);
            m_documentWriter->endElement(); // w:rPr
            m_documentWriter->endElement(); // w:pPr
            m_documentWriter->endElement(); // w:pPrDefault
        }
        else if (family == "text")
        {
            m_documentWriter->startElement("w:rPrDefault");
            m_documentWriter->startElement("w:rPr");
            KoOdfStyleProperties *textProperties = style->properties("style:text-properties");
            DocxStyleHelper::handleTextStyles(textProperties, m_documentWriter);
            m_documentWriter->endElement(); // w:rPr
            m_documentWriter->endElement(); // w:rPrDefault
        }
    }
    m_documentWriter->endElement(); // w:docDefaults

    QList<KoOdfStyle*> styles = manager->styles();
    foreach (KoOdfStyle* style, styles)
    {
        if (!style->isFromStylesXml())
        {
            continue;
        }
        QString family = style->family();
        QString parent = style->parent();

        if (family == "paragraph")
        {
            m_documentWriter->startElement("w:style");
            m_documentWriter->addAttribute("w:type", "paragraph");
            //openword : addd 20211227
            if ( style->name().contains("_20"))
            {
                QString stylenamenew = style->name();
                m_documentWriter->addAttribute("w:styleId", stylenamenew.replace(QLatin1String("_20"), QLatin1String("")));
            }
            else
            {
                m_documentWriter->addAttribute("w:styleId", style->name());
            }

            m_documentWriter->startElement("w:name");
            QString displayName = style->displayName();
            if (displayName.isEmpty())
            {
                displayName = style->name();
            }
            m_documentWriter->addAttribute("w:val", displayName);
            m_documentWriter->endElement(); // w:name
            if (!parent.isEmpty())
            {
                m_documentWriter->startElement("w:basedOn");
                m_documentWriter->addAttribute("w:val", parent);
                m_documentWriter->endElement(); // w:basedOn
            }
            m_documentWriter->startElement("w:pPr");
            ///openword add :20211230
            /// eg:/// w:styleId="Head2">
            //<w:numPr>
            //    <w:ilvl w:val="1"/>
            //    <w:numId w:val="1"/>
            //</w:numPr>
            //<w:outlineLvl w:val="1"/>
            //if ()
            if (displayName.contains("Head"))
            {
                QString outlineLvl = displayName.right(1);
                if (!outlineLvl.isEmpty())
                {
                    int docxOutlineLvl = outlineLvl.toInt();
                    m_documentWriter->startElement("w:numPr");

                    m_documentWriter->startElement("w:ilvl");
                    m_documentWriter->addAttribute("w:val", docxOutlineLvl-1);
                    m_documentWriter->endElement();

                    m_documentWriter->startElement("w:numId");
                    m_documentWriter->addAttribute("w:val", 1);
                    m_documentWriter->endElement();// w:numId

                    m_documentWriter->endElement();//"w:numPr"
                }
            }
            ///
            ///
            KoOdfStyleProperties *paragraphProperties = style->properties("style:paragraph-properties");
            DocxStyleHelper::handleParagraphStyles(paragraphProperties, m_documentWriter);
            m_documentWriter->endElement(); // w:pPr
            KoOdfStyleProperties *textProperties = style->properties("style:text-properties");
            m_documentWriter->startElement("w:rPr");
            KoOdfStyleProperties properties;
            if (!parent.isEmpty())
            {
                DocxStyleHelper::inheritTextStyles(&properties, parent, manager);
            }
            if (textProperties != 0)
            {
                properties.copyPropertiesFrom(*textProperties);
            }
            DocxStyleHelper::handleTextStyles(&properties, m_documentWriter);
            m_documentWriter->endElement(); // w:rPr
            m_documentWriter->endElement(); // w:style
        }
        else if (family == "text")
        {
            m_documentWriter->startElement("w:style");
            m_documentWriter->addAttribute("w:type", "character");
            //openword : addd 20211227s
            if (style->name().contains("_20"))
            {
                QString stylenamenew = style->name();
                m_documentWriter->addAttribute("w:styleId", stylenamenew.replace(QLatin1String("_20"), QLatin1String("")));
            }
            else
            {
                m_documentWriter->addAttribute("w:styleId", style->name());
            }
            m_documentWriter->startElement("w:name");
            QString displayName = style->displayName();
            if (displayName.isEmpty())
            {
                displayName = style->name();
            }
            m_documentWriter->addAttribute("w:val", displayName);
            m_documentWriter->endElement(); // w:name
            if (!parent.isEmpty())
            {
                m_documentWriter->startElement("w:basedOn");
                m_documentWriter->addAttribute("w:val", parent);
                m_documentWriter->endElement(); // w:basedOn
            }
            KoOdfStyleProperties *textProperties = style->properties("style:text-properties");
            m_documentWriter->startElement("w:rPr");
            DocxStyleHelper::handleTextStyles(textProperties, m_documentWriter);
            m_documentWriter->endElement(); // w:rPr
            m_documentWriter->endElement(); // w:style
        }
    }

    m_documentWriter->endElement(); // w:styles
    m_documentWriter->endDocument();
}
