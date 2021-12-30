#ifndef DOCXNUMBERING_H
#define DOCXNUMBERING_H

// Qt
#include <QBuffer>

class QByteArray;

class KoXmlWriter;
class OdfReaderContext;

class DocxNumberingWriter
{
public:
    DocxNumberingWriter(OdfReaderContext *context);
    virtual ~DocxNumberingWriter();

    void read();

    QByteArray documentContent() const;

private:
    OdfReaderContext *m_readerContext;
    QByteArray   m_numberingContent; // m_documentWriter writes here;
    KoXmlWriter *m_documentWriter;  // XML writer for the document contents
    QBuffer      m_documentIO;      // IODevice for the XMl writer
};

#endif // DOCXNUMBERING_H
