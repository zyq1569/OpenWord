// Own
#include "odfdrawreaderdocxbackend.h"

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
//                 class OdfDrawReaderDocxBackend

OdfDrawReaderDocxBackend::OdfDrawReaderDocxBackend()
    :OdfDrawReaderBackend()
    , m_currentParagraphTextProperties(0)
{

}

OdfDrawReaderDocxBackend::~OdfDrawReaderDocxBackend()
{

}

void OdfDrawReaderDocxBackend::elementDrawFrame(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();

    elementDrawFrameImage(reader, context);
}

void OdfDrawReaderDocxBackend::elementDrawFrameImage(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();
    OdfReaderDocxContext *docxContext = dynamic_cast<OdfReaderDocxContext*>(context);
    if (!docxContext)
    {
        return;
    }

    KoXmlWriter *writer = docxContext->m_documentWriter;

    if (reader.isStartElement())
    {
        KoXmlStreamAttributes attributes = reader.attributes();

        writer->startElement("w:p");

        writer->startElement("w:pPr");
        //<w:pStyle w:val="Standard"/>
        //writer->addAttribute("w:pStyle","Standard");
        QString textStyle = attributes.value("draw:style-name").toString();
        if (!textStyle.isEmpty())
        {
            KoOdfStyle *style = docxContext->styleManager()->style(textStyle, "paragraph");
            //KoOdfStyleProperties *parProperties = style->properties("style:paragraph-properties");
            m_currentParagraphTextProperties = style->properties("style:text-properties");
            m_currentParagraphParent = style->parent();
            if (!m_currentParagraphParent.isEmpty())
            {
                writer->startElement("w:pStyle");
                writer->addAttribute("w:val", m_currentParagraphParent);
                writer->endElement(); // w:pStyle
            }
            //DocxStyleHelper::handleParagraphStyles(parProperties, writer);
            //writer->startElement("w:rPr");
            //DocxStyleHelper::handleTextStyles(m_currentParagraphTextProperties, writer);
        }

        writer->endElement();//"w:pPr"

        writer->startElement("<w:r>");
        QString svgwidth  = attributes.value("svg:width").toString();

        writer->startElement("<w:r>");

        writer->endElement();//("w:p");
    }
}
