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

///
///  DocxNumberingWriter::read
//<w:abstractNum w:abstractNumId="2" w15:restartNumberingAfterBreak="0">
//<w:nsid w:val="2185199F"/>
//<w:multiLevelType w:val="multilevel"/>
//<w:tmpl w:val="5DBC47C6"/>
//<w:styleLink w:val="O"/>
//<w:lvl w:ilvl="0">
//    <w:start w:val="1"/>
//    <w:numFmt w:val="decimal"/>
//    <w:pStyle w:val="Head1"/>
//    <w:lvlText w:val="%1."/>
//    <w:lvlJc w:val="left"/>
//</w:lvl>
//<w:lvl w:ilvl="1">
//    <w:start w:val="1"/>
//    <w:numFmt w:val="decimal"/>
//    <w:pStyle w:val="Head2"/>
//    <w:lvlText w:val="%1.%2."/>
//    <w:lvlJc w:val="left"/>
//</w:lvl>
//<w:lvl w:ilvl="2">
//    <w:start w:val="1"/>
//    <w:numFmt w:val="decimal"/>
//    <w:pStyle w:val="Head3"/>
//    <w:lvlText w:val="%1.%2.%3."/>
//    <w:lvlJc w:val="left"/>
//</w:lvl>
//<w:lvl w:ilvl="3">
//    <w:start w:val="1"/>
//    <w:numFmt w:val="none"/>
//    <w:lvlText w:val=""/>
//    <w:lvlJc w:val="left"/>
//</w:lvl>
//<w:lvl w:ilvl="4">
//    <w:start w:val="1"/>
//    <w:numFmt w:val="none"/>
//    <w:lvlText w:val=""/>
//    <w:lvlJc w:val="left"/>
//</w:lvl>
//</w:abstractNum>
///
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

    int index=0;
    bool outline = false;
    QList<QString> key = manager->getKoOdfListStyleKey();
    for (int i=0; i<key.size(); i++)
    {
        QString listKey = key[i];
        DEBUG_LOG("manager->getKoOdfListStyleKey key:" + listKey);
        //listLevelType == "text:outline-style"
        KoOdfListStyle* styles = manager->listStyle(listKey);
        if (styles)
        {
            if (styles->listLevelStyleType() == "text:outline-style")
            {
                outline = true;
            }
        }
        /// "O" == listKey考虑到名称判断的准确性
        if (outline)//in void KoStyleManager::saveOdf(KoShapeSavingContext &context) set:
        {
            m_documentWriter->startElement("w:abstractNum");
            m_documentWriter->addAttribute("w:abstractNumId",index);
            m_documentWriter->addAttribute("w15:restartNumberingAfterBreak",index);
            index++;
            m_documentWriter->startElement("w:nsid");
            m_documentWriter->addAttribute("w:val",index+1000);
            m_documentWriter->endElement();//w:nsid

            //KoOdfListStyle* styles = manager->listStyle(key[i]);
            QString listLevelStyleType = styles->listLevelStyleType();
            DEBUG_LOG("manager->getKoOdfListStyleKey outline listLevelStyleType" + listLevelStyleType);

            QHash<int, AttributeSet> outlineNumber = styles->getOutLineAttributeSet();
            int size = outlineNumber.size();
            AttributeSet multi = outlineNumber.value(size - 1);
            int display_lev =multi.value("text:display-levels").toInt();
            if (display_lev > 1)
            {
                m_documentWriter->startElement("w:multiLevelType");
                m_documentWriter->addAttribute("w:val","multilevel");
                m_documentWriter->endElement();//w:multiLevelType
            }
            else
            {
                m_documentWriter->startElement("w:multiLevelType");
                m_documentWriter->addAttribute("w:val","singleLevel");
                m_documentWriter->endElement();//w:multiLevelType
            }


            QString lvlText;
            for (int id = 0; id<size; id++)
            {
                AttributeSet atts = outlineNumber.value(id);

                m_documentWriter->startElement("w:lvl");
                m_documentWriter->addAttribute("w:ilvl",id);

                m_documentWriter->startElement("w:start");
                m_documentWriter->addAttribute("w:val",atts.value("text:start-value"));
                m_documentWriter->endElement();
                m_documentWriter->startElement("w:numFmt");
                m_documentWriter->addAttribute("w:val",atts.value("style:num-format"));
                m_documentWriter->endElement();

                m_documentWriter->startElement("w:lvlText");
                if (display_lev > 1)
                {
                    lvlText += atts.value("style:num-prefix")+"%"+QString::number(id+1);
                }
                else
                {
                    lvlText = atts.value("style:num-prefix")+"%"+QString::number(id+1);
                }
                lvlText += atts.value("style:num-suffix");
                m_documentWriter->addAttribute("w:val",lvlText);
                m_documentWriter->endElement();

                m_documentWriter->startElement("w:lvlJc");
                m_documentWriter->addAttribute("w:val","left");
                m_documentWriter->endElement();

                m_documentWriter->endElement();//w:lvl
            }
            m_documentWriter->endElement();///w:abstractNum
            break;
        }

    }

//<w:num w:numId="1">
//    <w:abstractNumId w:val="2"/>
//</w:num>

    m_documentWriter->startElement("w:num");
    m_documentWriter->addAttribute("w:numId","1");
    m_documentWriter->startElement("w:abstractNumId");
    m_documentWriter->addAttribute("w:val","0");
    m_documentWriter->endElement();
    m_documentWriter->endElement();


    m_documentWriter->endElement(); // w:numbering
    m_documentWriter->endDocument();
}

///////////////////////////////////////
//////////-------webSettings.xml-------------////////////////////
///////////////////////////////////////
DocxWebSettings::DocxWebSettings(OdfReaderContext *context)
    : m_readerContext(context)
    , m_numberingContent()
    , m_documentIO(&m_numberingContent)
{
    m_documentWriter = new KoXmlWriter(&m_documentIO);
}


DocxWebSettings::~DocxWebSettings()
{
    delete m_documentWriter;
}

QByteArray DocxWebSettings::documentContent() const
{
    return m_numberingContent;
}

void DocxWebSettings::read()
{
    m_documentWriter->startDocument(0,0,0);
    m_documentWriter->startElement("w:webSettings");
    ///----------------MSword2016----------------------------------------------
    m_documentWriter->addAttribute("xmlns:mc","http://schemas.openxmlformats.org/markup-compatibility/2006");
    m_documentWriter->addAttribute("xmlns:r","http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    m_documentWriter->addAttribute("xmlns:w","http://schemas.openxmlformats.org/wordprocessingml/2006/main" );
    m_documentWriter->addAttribute("xmlns:w14","http://schemas.microsoft.com/office/word/2010/wordml" );
    m_documentWriter->addAttribute("xmlns:w15","http://schemas.microsoft.com/office/word/2012/wordml");
    m_documentWriter->addAttribute("xmlns:w16cex","http://schemas.microsoft.com/office/word/2018/wordml/cex");
    m_documentWriter->addAttribute("xmlns:w16cid","http://schemas.microsoft.com/office/word/2016/wordml/cid");
    m_documentWriter->addAttribute("xmlns:w16","http://schemas.microsoft.com/office/word/2018/wordml");
    m_documentWriter->addAttribute("xmlns:w16sdtdh","http://schemas.microsoft.com/office/word/2020/wordml/sdtdatahash");
    m_documentWriter->addAttribute("xmlns:w16se","http://schemas.microsoft.com/office/word/2015/wordml/symex");
    m_documentWriter->addAttribute("mc:Ignorable","w14 w15 w16se w16cid w16 w16cex w16sdtdh");
    /////////////////////////////////////////////////////////////////////////////
    m_documentWriter->endElement();
    m_documentWriter->endDocument();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DocxFontTable::DocxFontTable(OdfReaderContext *context)
    : m_readerContext(context)
    , m_numberingContent()
    , m_documentIO(&m_numberingContent)
{
    m_documentWriter = new KoXmlWriter(&m_documentIO);
}


DocxFontTable::~DocxFontTable()
{
    delete m_documentWriter;
}

QByteArray DocxFontTable::documentContent() const
{
    return m_numberingContent;
}

///
/// \brief DocxfontTable::read
///
//<w:font w:name="Times New Roman">
//    <w:panose1 w:val="02020603050405020304"/>
//    <w:charset w:val="86"/>
//    <w:family w:val="auto"/>
//    <w:pitch w:val="default"/>
//    <w:sig w:usb0="E0002EFF" w:usb1="C000785B" w:usb2="00000009" w:usb3="00000000" w:csb0="400001FF" w:csb1="FFFF0000"/>
//</w:font>
//<w:font w:name="宋体">
//    <w:panose1 w:val="02010600030101010101"/>
//    <w:charset w:val="88"/>
//    <w:family w:val="auto"/>
//    <w:pitch w:val="default"/>
//    <w:sig w:usb0="00000003" w:usb1="288F0000" w:usb2="00000006" w:usb3="00000000" w:csb0="00040001" w:csb1="00000000"/>
//</w:font>
//   <w:font w:name="黑体">
//       <w:panose1 w:val="02010609060101010101"/>
//       <w:charset w:val="86"/>
//       <w:family w:val="auto"/>
//       <w:pitch w:val="default"/>
//       <w:sig w:usb0="800002BF" w:usb1="38CF7CFA" w:usb2="00000016" w:usb3="00000000" w:csb0="00040001" w:csb1="00000000"/>
//</w:font>
//<w:font w:name="微软雅黑">
//   <w:panose1 w:val="020B0503020204020204"/>
//   <w:charset w:val="86"/>
//   <w:family w:val="swiss"/>
//   <w:pitch w:val="default"/>
//   <w:sig w:usb0="80000287" w:usb1="2ACF3C50" w:usb2="00000016" w:usb3="00000000" w:csb0="0004001F" w:csb1="00000000"/>
//</w:font>
//<w:font w:name="楷体_GB2312">
//   <w:altName w:val="楷体"/>
//   <w:panose1 w:val="00000000000000000000"/>
//   <w:charset w:val="86"/>
//   <w:family w:val="modern"/>


//<w:font w:name="仿宋">
//   <w:panose1 w:val="02010609060101010101"/>
//   <w:charset w:val="86"/>
//   <w:family w:val="modern"/>
//   <w:pitch w:val="default"/>
//   <w:sig w:usb0="800002BF" w:usb1="38CF7CFA" w:usb2="00000016" w:usb3="00000000" w:csb0="00040001" w:csb1="00000000"/>
//</w:font>
//<w:font w:name="Times New Roman">
//   <w:panose1 w:val="02020603050405020304"/>
//   <w:charset w:val="00"/>
//   <w:family w:val="roman"/>
//   <w:pitch w:val="variable"/>
//   <w:sig w:usb0="E0002EFF" w:usb1="C000785B" w:usb2="00000009" w:usb3="00000000" w:csb0="000001FF" w:csb1="00000000"/>
//</w:font>

//<w:font w:name="Sans Serif">
//    <w:altName w:val="Calibri"/>
//    <w:charset w:val="00"/>
//    <w:family w:val="auto"/>
//    <w:pitch w:val="default"/>
//</w:font>

//<w:font w:name="Times New Roman">
//    <w:panose1 w:val="02020603050405020304"/>
//    <w:charset w:val="00"/>
//    <w:family w:val="roman"/>
//    <w:pitch w:val="variable"/>
//    <w:sig w:usb0="E0002EFF" w:usb1="C000785B" w:usb2="00000009" w:usb3="00000000" w:csb0="000001FF" w:csb1="00000000"/>
//</w:font>

void DocxFontTable::read()
{
    m_documentWriter->startDocument(0,0,0);
    m_documentWriter->startElement("w:fonts");
    ///----------------MSword2016----------------------------------------------
    m_documentWriter->addAttribute("xmlns:mc","http://schemas.openxmlformats.org/markup-compatibility/2006");
    m_documentWriter->addAttribute("xmlns:r","http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    m_documentWriter->addAttribute("xmlns:w","http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    m_documentWriter->addAttribute("xmlns:w14","http://schemas.microsoft.com/office/word/2010/wordml");
    m_documentWriter->addAttribute("mc:Ignorable","w14");
    /////////////////////////////////////////////////////////////////////////////

    //<w:font w:name="MS Sans Serif">
    //   <w:altName w:val="微软雅黑"/>
    //   <w:panose1 w:val="020B0500000000000000"/>
    //   <w:charset w:val="00"/>
    //   <w:family w:val="auto"/>
    //   <w:pitch w:val="default"/>
    //   <w:sig w:usb0="00000000" w:usb1="00000000" w:usb2="00000010" w:usb3="00000000" w:csb0="00040001" w:csb1="00000000"/>
    //</w:font>
    //////////////////////font:"Sans Serif"///////////////////////////////////////
    m_documentWriter->startElement("w:font");
    m_documentWriter->addAttribute("w:name","Sans Serif");

    m_documentWriter->startElement("w:altName");m_documentWriter->addAttribute("w:val","Calibri"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:charset");m_documentWriter->addAttribute("w:val","00"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:family");m_documentWriter->addAttribute("w:val","auto"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:pitch");m_documentWriter->addAttribute("w:val","default");m_documentWriter->endElement();

    m_documentWriter->endElement();//w:font
    ///////////////////////////////////////////////////////////////
    /// //<w:font w:name="等线">
    //    <w:altName w:val="DengXian"/>
    //    <w:panose1 w:val="02010600030101010101"/>
    //    <w:charset w:val="86"/>
    //    <w:family w:val="auto"/>
    //    <w:pitch w:val="variable"/>
    //    <w:sig w:usb0="A00002BF" w:usb1="38CF7CFA" w:usb2="00000016" w:usb3="00000000" w:csb0="0004000F" w:csb1="00000000"/>
    //</w:font>
    //////////////////////font:"等线"///////////////////////////////////////
    m_documentWriter->startElement("w:font");
    m_documentWriter->addAttribute("w:name","等线");

    m_documentWriter->startElement("w:altName");m_documentWriter->addAttribute("w:val","DengXian"); m_documentWriter->endElement();
    m_documentWriter->startElement("w:panose1");m_documentWriter->addAttribute("w:val","02010600030101010101"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:charset");m_documentWriter->addAttribute("w:val","86"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:family");m_documentWriter->addAttribute("w:val","auto"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:pitch");m_documentWriter->addAttribute("w:val","variable");m_documentWriter->endElement();

    m_documentWriter->startElement("w:sig");
    m_documentWriter->addAttribute("w:usb0","A00002BF");    m_documentWriter->addAttribute("w:usb1","38CF7CFA");m_documentWriter->addAttribute("w:usb2","00000016");
    m_documentWriter->addAttribute("w:usb3","00000000");    m_documentWriter->addAttribute("w:csb0","0004000F");
    m_documentWriter->addAttribute("w:csb1","00000000");    m_documentWriter->endElement();

    m_documentWriter->endElement();//w:font
    ///////////////////////////////////////////////////////////////
    ///
    //////////////////////font:"Times New Roman"///////////////////////////////////////
    /////////////////////////////////////////////////////////////
    m_documentWriter->startElement("w:font");
    m_documentWriter->addAttribute("w:name","Times New Roman");

    m_documentWriter->startElement("w:panose1");m_documentWriter->addAttribute("w:val","02020603050405020304"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:charset");m_documentWriter->addAttribute("w:val","00"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:family");m_documentWriter->addAttribute("w:val","roman"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:pitch");m_documentWriter->addAttribute("w:val","variable");m_documentWriter->endElement();

    m_documentWriter->startElement("w:sig");
    m_documentWriter->addAttribute("w:usb0","E0002EFF");    m_documentWriter->addAttribute("w:usb1","C000785B");m_documentWriter->addAttribute("w:usb2","00000009");
    m_documentWriter->addAttribute("w:usb3","00000000");    m_documentWriter->addAttribute("w:csb0","000001FF");
    m_documentWriter->addAttribute("w:csb1","00000000");    m_documentWriter->endElement();

    m_documentWriter->endElement();//w:font
    ///////////////////////////////////////////////////////////////
    //<w:font w:name="等线 Light">
    //    <w:panose1 w:val="02010600030101010101"/>
    //    <w:charset w:val="86"/>
    //    <w:family w:val="auto"/>
    //    <w:pitch w:val="variable"/>
    //    <w:sig w:usb0="A00002BF" w:usb1="38CF7CFA" w:usb2="00000016" w:usb3="00000000" w:csb0="0004000F" w:csb1="00000000"/>
    //</w:font>
    /////////////////////////////////////////////////////////////
    m_documentWriter->startElement("w:font");
    m_documentWriter->addAttribute("w:name","等线 Light");

    m_documentWriter->startElement("w:panose1");m_documentWriter->addAttribute("w:val","02010600030101010101"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:charset");m_documentWriter->addAttribute("w:val","86"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:family");m_documentWriter->addAttribute("w:val","auto"); m_documentWriter->endElement();

    m_documentWriter->startElement("w:pitch");m_documentWriter->addAttribute("w:val","variable");m_documentWriter->endElement();

    m_documentWriter->startElement("w:sig");
    m_documentWriter->addAttribute("w:usb0","A00002BF");    m_documentWriter->addAttribute("w:usb1","38CF7CFA");m_documentWriter->addAttribute("w:usb2","00000016");
    m_documentWriter->addAttribute("w:usb3","00000000");    m_documentWriter->addAttribute("w:csb0","0004000F");
    m_documentWriter->addAttribute("w:csb1","00000000");    m_documentWriter->endElement();

    m_documentWriter->endElement();//w:font

    /////////////////////////////////////////////////////////////////////
    m_documentWriter->endElement();//"w:fonts"
    m_documentWriter->endDocument();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///footnotes.xml
///
DocxFootnotes::DocxFootnotes(OdfReaderContext *context)
    : m_readerContext(context)
    , m_numberingContent()
    , m_documentIO(&m_numberingContent)
{
    m_documentWriter = new KoXmlWriter(&m_documentIO);
}


DocxFootnotes::~DocxFootnotes()
{
    delete m_documentWriter;
}

QByteArray DocxFootnotes::documentContent() const
{
    return m_numberingContent;
}

void DocxFootnotes::read()
{
    m_documentWriter->startDocument(0,0,0);
    m_documentWriter->startElement("w:footnotes");
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
    /////////////////////////////////////////////////////////////////////////////

    //<w:footnote -1
    m_documentWriter->startElement("w:footnote");
    m_documentWriter->addAttribute("w:type","separator");
    m_documentWriter->addAttribute("w:id","-1");

    m_documentWriter->startElement("w:p");//w14:paraId="576B5E57" w14:textId="77777777" w:rsidR="00A21553" w:rsidRDefault="00A21553" w:rsidP="00220C41">
    m_documentWriter->startElement("w:pPr");
    m_documentWriter->startElement("w:rPr");

    m_documentWriter->startElement("w:rFonts");
    m_documentWriter->addAttribute("w:hint","eastAsia");
    m_documentWriter->endElement();

    m_documentWriter->endElement();//w:rPr
    m_documentWriter->endElement();//w:pPr

    m_documentWriter->startElement("w:r");
    m_documentWriter->startElement("w:separator");
    m_documentWriter->endElement();
    m_documentWriter->endElement();//w:r

    m_documentWriter->endElement();//w:p
    m_documentWriter->endElement();//w:footnote


    //<w:footnote 0
    m_documentWriter->startElement("w:footnote");
    m_documentWriter->addAttribute("w:type","continuationSeparator");
    m_documentWriter->addAttribute("w:id","0");

    m_documentWriter->startElement("w:p");//w14:paraId="576B5E57" w14:textId="77777777" w:rsidR="00A21553" w:rsidRDefault="00A21553" w:rsidP="00220C41">
    m_documentWriter->startElement("w:pPr");
    m_documentWriter->startElement("w:rPr");

    m_documentWriter->startElement("w:rFonts");
    m_documentWriter->addAttribute("w:hint","eastAsia");
    m_documentWriter->endElement();

    m_documentWriter->endElement();//w:rPr
    m_documentWriter->endElement();//w:pPr

    m_documentWriter->startElement("w:r");
    m_documentWriter->startElement("w:continuationSeparator");
    m_documentWriter->endElement();
    m_documentWriter->endElement();//w:r

    m_documentWriter->endElement();//w:p
    m_documentWriter->endElement();//w:footnote    m_documentWriter->endElement();
    ///////////////////////////////////////////////////////////////////////////////
    m_documentWriter->endElement();///w:footnotes"
    m_documentWriter->endDocument();
}
