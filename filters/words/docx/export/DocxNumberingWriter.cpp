#include "DocxNumberingWriter.h"


// Qt
#include <QByteArray>
#include <QBuffer>

// Calligra
#include <KoXmlWriter.h>
#include <OdfReaderContext.h>
#include <KoOdfStyleManager.h>
#include <KoOdfStyle.h>
#include <KoOdfStyleProperties.h>
#include <KoOdfListStyle.h>

//3th
#include "logging.h"

// This filter
#include "DocxStyleHelper.h"


DocxNumberingWriter::DocxNumberingWriter(OdfReaderContext *context)
    : m_readerContext(context)
    , m_numberingContent()
    , m_documentIO(&m_numberingContent)
{
    m_documentWriter = new KoXmlWriter(&m_documentIO);
}


DocxNumberingWriter::~DocxNumberingWriter()
{
    delete m_documentWriter;
}

QByteArray DocxNumberingWriter::documentContent() const
{
    return m_numberingContent;
}

void DocxNumberingWriter::read()
{
    KoOdfStyleManager *manager = m_readerContext->styleManager();
    m_documentWriter->startDocument(0,0,0);
    m_documentWriter->startElement("w:numbering");
    ///----------------MSword2016----------------------------------------------
    m_documentWriter->addAttribute("xmlns:wpc","http://schemas.microsoft.com/office/word/2010/wordprocessingCanvas");
    m_documentWriter->addAttribute("xmlns:cx","http://schemas.microsoft.com/office/drawing/2014/chartex");
    m_documentWriter->addAttribute("xmlns:cx1","http://schemas.microsoft.com/office/drawing/2015/9/8/chartex");
    m_documentWriter->addAttribute("xmlns:cx2","http://schemas.microsoft.com/office/drawing/2015/10/21/chartex");
    m_documentWriter->addAttribute("xmlns:cx3","http://schemas.microsoft.com/office/drawing/2016/5/9/chartex");
    m_documentWriter->addAttribute("xmlns:cx4","http://schemas.microsoft.com/office/drawing/2016/5/10/chartex");
    m_documentWriter->addAttribute("xmlns:cx5","http://schemas.microsoft.com/office/drawing/2016/5/11/chartex");
    m_documentWriter->addAttribute("xmlns:cx6","http://schemas.microsoft.com/office/drawing/2016/5/12/chartex");
    m_documentWriter->addAttribute("xmlns:cx7","http://schemas.microsoft.com/office/drawing/2016/5/13/chartex");
    m_documentWriter->addAttribute("xmlns:cx8","http://schemas.microsoft.com/office/drawing/2016/5/14/chartex");
    m_documentWriter->addAttribute("xmlns:mc","http://schemas.openxmlformats.org/markup-compatibility/2006");
    m_documentWriter->addAttribute("xmlns:aink","http://schemas.microsoft.com/office/drawing/2016/ink");
    m_documentWriter->addAttribute("xmlns:am3d","http://schemas.microsoft.com/office/drawing/2017/model3d");
    m_documentWriter->addAttribute("xmlns:o","urn:schemas-microsoft-com:office:office");
    m_documentWriter->addAttribute("xmlns:r","http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    m_documentWriter->addAttribute("xmlns:m","http://schemas.openxmlformats.org/officeDocument/2006/math");
    m_documentWriter->addAttribute("xmlns:v","urn:schemas-microsoft-com:vml");
    m_documentWriter->addAttribute("xmlns:wp14","http://schemas.microsoft.com/office/word/2010/wordprocessingDrawing");
    m_documentWriter->addAttribute("xmlns:wp","http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing");
    m_documentWriter->addAttribute("xmlns:w10","urn:schemas-microsoft-com:office:word");
    m_documentWriter->addAttribute("xmlns:w","http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    m_documentWriter->addAttribute("xmlns:w14","http://schemas.microsoft.com/office/word/2010/wordml");
    m_documentWriter->addAttribute("xmlns:w15","http://schemas.microsoft.com/office/word/2012/wordml");
    m_documentWriter->addAttribute("xmlns:w16cex","http://schemas.microsoft.com/office/word/2018/wordml/cex");
    m_documentWriter->addAttribute("xmlns:w16cid","http://schemas.microsoft.com/office/word/2016/wordml/cid");
    m_documentWriter->addAttribute("xmlns:w16","http://schemas.microsoft.com/office/word/2018/wordml");
    m_documentWriter->addAttribute("xmlns:w16sdtdh","http://schemas.microsoft.com/office/word/2020/wordml/sdtdatahash");
    m_documentWriter->addAttribute("xmlns:w16se","http://schemas.microsoft.com/office/word/2015/wordml/symex");
    m_documentWriter->addAttribute("xmlns:wpg","http://schemas.microsoft.com/office/word/2010/wordprocessingGroup");
    m_documentWriter->addAttribute("xmlns:wpi","http://schemas.microsoft.com/office/word/2010/wordprocessingInk");
    m_documentWriter->addAttribute("xmlns:wne","http://schemas.microsoft.com/office/word/2006/wordml");
    m_documentWriter->addAttribute("xmlns:wps","http://schemas.microsoft.com/office/word/2010/wordprocessingShape");
    m_documentWriter->addAttribute("mc:Ignorable","w14 w15 w16se w16cid w16 w16cex w16sdtdh wp14");
    ///-------------------------------------------------------------------------

    //QList<KoOdfStyle*> defaultStyles = manager->defaultStyles();

    int i=0;
    m_documentWriter->startElement("w:abstractNum");
    m_documentWriter->addAttribute("w:abstractNumId",i);
    m_documentWriter->addAttribute("w15:restartNumberingAfterBreak",i);
    i++;
    m_documentWriter->startElement("w:nsid");
    m_documentWriter->addAttribute("w:val",i+1000);
    m_documentWriter->endElement();//w:nsid
    m_documentWriter->startElement("w:multiLevelType");
    m_documentWriter->addAttribute("w:val","multilevel");
    m_documentWriter->endElement();//w:multiLevelType
    m_documentWriter->startElement("w:tmpl");
    m_documentWriter->addAttribute("w:val","multilevel");
    m_documentWriter->endElement();//w:multiLevelType


    m_documentWriter->endElement();///w:abstractNum


    QList<QString> key = manager->getKoOdfListStyleKey();
    for (int i=0; i<key.size(); i++)
    {
        if ("O" == key[i])
        {
            KoOdfListStyle* styles = manager->listStyle(key[i]);
            QString listLevelStyleType = styles->listLevelStyleType();
            DEBUG_LOG(listLevelStyleType);
        }
    }



    m_documentWriter->endElement(); // w:numbering
}
