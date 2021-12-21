#ifndef ODFDRAWREADERDOCXBACKEND_H
#define ODFDRAWREADERDOCXBACKEND_H

// Calligra
#include <KoXmlStreamReader.h>
#include <KoFilter.h>
#include <OdfDrawReaderBackend.h>

class KoOdfStyleProperties;
class OdfReaderContext;
class OdfReaderDocxContext;

class OdfDrawReaderDocxBackend : public OdfDrawReaderBackend
{
public:
    OdfDrawReaderDocxBackend();
    ~OdfDrawReaderDocxBackend() override;

    // ----------------------------------------------------------------
    // , etc

    void elementDrawFrame(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    void elementDrawFrameImage(KoXmlStreamReader &reader, OdfReaderContext *context) override;

private:
    //int m_insideSpanLevel;    // Number of nexted <text:span> levels.
    //int m_currentOutlineLevel;
    //int m_commentIndex;
    //bool m_writeComment;
    //bool m_insideComment;
    //bool m_insideDcCreator;
    //bool m_insideDcDate;
    KoOdfStyleProperties *m_currentParagraphTextProperties;
    QString m_currentParagraphParent;
};

#endif // ODFDRAWREADERDOCXBACKEND_H
