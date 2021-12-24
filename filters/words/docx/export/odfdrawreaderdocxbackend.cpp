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
        writer->addAttribute("w14:paraId", "5ec3232323");
        writer->addAttribute("w14:textId", "77777777");
        writer->addAttribute("w14:rsidR", "000B243E");
        writer->addAttribute("w:rsidRDefault", "00A21553");

        writer->startElement("w:pPr");  //<w:pStyle w:val="Standard"/>   //writer->addAttribute("w:pStyle","Standard");
        QString textStyleName = reader.getcurrentTextStylename();
        QString drawStyleName = attributes.value("draw:style-name").toString();
        if (!textStyleName.isEmpty())
        {
            KoOdfStyle *style = docxContext->styleManager()->style(textStyleName, "paragraph");
            //KoOdfStyleProperties *parProperties = style->properties("style:paragraph-properties");
            m_currentParagraphTextProperties = style->properties("style:text-properties");
            m_currentParagraphParent = style->parent();

            KoOdfStyle *drawStyle = docxContext->styleManager()->style(drawStyleName, "graphic");
            KoOdfStyleProperties *drawStylePro =  drawStyle->properties("style:graphic-properties");
            QString style_wrap_contour_mode = drawStylePro->attribute("style:wrap-contour-mode");
            if (!m_currentParagraphParent.isEmpty())
            {
                writer->startElement("w:pStyle");
                writer->addAttribute("w:val", m_currentParagraphParent);
                writer->endElement(); // w:pStyle
            }
        }
        reader.readNext();
        attributes = reader.attributes();
        ///<draw:image xlink:type="simple" xlink:show="embed" xlink:actuate="onLoad" xlink:href="Pictures/image1.png"/>
        QString tagName = reader.qualifiedName().toString();
        if (tagName == "draw:image")
        {
            QString xlink_type      = attributes.value("xlink:type").toString();
            QString xlink_show      = attributes.value("xlink:show").toString();
            QString xlink_actuate   = attributes.value("xlink:actuate").toString();
            QString xlink_href      = attributes.value("xlink:href").toString();
            QString destinationName = xlink_href.mid(xlink_href.lastIndexOf('/') + 1);
            destinationName         = "word/media/" + destinationName;
            addImageInfo(xlink_href, destinationName);
        }

        writer->endElement();//"w:pPr"

        writer->startElement("w:r");

        ///start------------- "w:rPr"---------
        writer->startElement("w:rPr");

        writer->startElement("w:noProof");
        writer->endElement();

        writer->endElement();
        ///end ---------------"w:rPr"--------

        ///start------------ w:drawing--------
        writer->startElement("w:drawing");
        //start wp:inline
        writer->startElement("wp:inline");
        writer->addAttribute("distT", "0");
        writer->addAttribute("distB", "0");
        writer->addAttribute("distL", "0");
        writer->addAttribute("distR", "0");
        writer->addAttribute("wp14:anchorId", "150CC466");
        writer->addAttribute("wp14:editId", "25D73062");

        //start wp:extent
        writer->startElement("wp:extent");
        writer->addAttribute("cx", "4299209");
        writer->addAttribute("cy", "1913129");
        writer->endElement();
        //end wp:extent

        //start wp:effectExtent
        writer->startElement("wp:effectExtent");
        writer->addAttribute("l", "0");
        writer->addAttribute("t", "0");
        writer->addAttribute("r", "6091");
        writer->addAttribute("b", "0");
        writer->endElement();
        //end wp:effectExtent

        //start wp:docPr
        writer->startElement("wp:docPr");
        writer->addAttribute("id", "1");
        writer->addAttribute("name", "图片 1");
        writer->endElement();
        //end  wp:docPr

        //start wp:cNvGraphicFramePr
        writer->startElement("wp:cNvGraphicFramePr");
        writer->endElement();
        //end  wp:cNvGraphicFramePr

        //start wp:graphic
        writer->startElement("wp:graphic");
        writer->addAttribute("xmlns:a", "http://schemas.openxmlformats.org/drawingml/2006/main");

        //start wp:graphicData
        writer->startElement("a:graphicData");
        writer->addAttribute("uri", "http://schemas.openxmlformats.org/drawingml/2006/picture");

        //start pic:pic
        writer->startElement("pic:pic");
        writer->addAttribute("xmlns:pic", "http://schemas.openxmlformats.org/drawingml/2006/picture");

        //start pic:nvPicPr
        writer->startElement("pic:nvPicPr");
        writer->startElement("pic:cNvPr ");
        writer->addAttribute("id","0");
        writer->addAttribute("name","");
        writer->endElement();
        writer->startElement("pic:cNvPicPr ");
        writer->endElement();
        writer->endElement();
        //end pic:nvPicPr

        //start pic:blipFill
        writer->startElement("pic:blipFill");
        writer->startElement("a:blip ");
        writer->addAttribute("r:embed","rId7");
        writer->endElement();
        writer->startElement("a:stretch");
        writer->startElement("a:fillRect");
        writer->endElement();
        writer->endElement();
        writer->endElement();
        //end pic:blipFill

        //-----start pic:spPr
        writer->startElement("pic:spPr");
        //a:xfrm
        writer->startElement("a:xfrm");
        writer->startElement("a:off");
        writer->addAttribute("x","0");
        writer->addAttribute("y","0");
        writer->endElement();
        writer->startElement("a:ext");
        writer->addAttribute("cx","4299209");
        writer->addAttribute("cy","1913129");;
        writer->endElement();
        writer->endElement();
        //a:xfrm
        //a:prstGeom
        writer->startElement("a:prstGeom");
        writer->startElement("a:avLst");
        writer->endElement();
        writer->endElement();
        writer->startElement("a:noFill");
        writer->endElement();
        writer->startElement("a:ln");
        writer->startElement("a:noFill");
        writer->endElement();
        writer->endElement();
        writer->endElement();
        //-----end pic:spPr

        writer->endElement();
       //-----end pic:pic

        writer->endElement();
       //-----end a:graphicData

        writer->endElement();
        //end  wp:graphic

        writer->endElement();
        //end  wp:inline

        writer->endElement();
        //end  w:drawing

        writer->endElement();
        //end  w:r

        writer->endElement();//("w:p");
    }
    elementDrawFrameImage(reader, context);
}

void OdfDrawReaderDocxBackend::elementDrawFrameImage(KoXmlStreamReader &reader, OdfReaderContext *context)
{
    DEBUG_BACKEND();

}
