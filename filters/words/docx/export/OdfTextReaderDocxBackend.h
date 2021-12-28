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

#ifndef ODFTEXTREADERDOCXBACKEND_H
#define ODFTEXTREADERDOCXBACKEND_H

// Calligra
#include <KoXmlStreamReader.h>
#include <KoFilter.h>
#include <OdfTextReaderBackend.h>



class KoOdfStyleProperties;
class OdfReaderContext;
class OdfReaderDocxContext;

class OdfTextReaderDocxBackend : public OdfTextReaderBackend
{
public:
    OdfTextReaderDocxBackend();
    ~OdfTextReaderDocxBackend() override;

    // ----------------------------------------------------------------
    // Text level functions: paragraphs, headings, sections, frames, objects, etc

    void elementTextH(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    void elementTextP(KoXmlStreamReader &reader, OdfReaderContext *context) override;

    // ----------------------------------------------------------------
    // Paragraph level functions: spans, annotations, notes, text content itself, etc.

    void elementOfficeAnnotation(KoXmlStreamReader &reader, OdfReaderContext *context) override;

    void elementDcCreator(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    void elementDcDate(KoXmlStreamReader &reader, OdfReaderContext *context) override;

    void elementTextSpan(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    void elementTextS(KoXmlStreamReader &reader, OdfReaderContext *context) override;

    void characterData(KoXmlStreamReader &reader, OdfReaderContext *context) override;

    ///openword add:
    //DECLARE_BACKEND_FUNCTION(TableTableColumnGroup);
    //DECLARE_BACKEND_FUNCTION(TableTableColumn);
    //DECLARE_BACKEND_FUNCTION(TableTableColumns);
    //DECLARE_BACKEND_FUNCTION(TableTableHeaderColumns);
    //DECLARE_BACKEND_FUNCTION(TableTableHeaderRows);
    //DECLARE_BACKEND_FUNCTION(TableTableRowGroup);
    //DECLARE_BACKEND_FUNCTION(TableTableRow);
    //DECLARE_BACKEND_FUNCTION(TableTableRows);
    //DECLARE_BACKEND_FUNCTION(TableTableCell);
    //DECLARE_BACKEND_FUNCTION(TableCoveredTableCell);
    //void elementTableTableColumnGroup(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    void elementTableTableColumn(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    void elementTableTableColumns(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    //void elementTableTableHeaderColumns(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    //void elementTableTableHeaderRows(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    //void elementTableTableRowGroup(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    void elementTableTableRow(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    //void elementTableTableRows(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    void elementTableTableCell(KoXmlStreamReader &reader, OdfReaderContext *context) override;
    //void elementTableCoveredTableCell(KoXmlStreamReader &reader, OdfReaderContext *context) override;

    void elementTableTable(KoXmlStreamReader &reader, OdfReaderContext *context) override;

private:
    void startRun(const KoXmlStreamReader &reader, OdfReaderDocxContext *context);
    void endRun(OdfReaderDocxContext *context);

private:
    int m_insideSpanLevel;    // Number of nexted <text:span> levels.
    int m_currentOutlineLevel;
    int m_commentIndex;
    bool m_writeComment;
    bool m_insideComment;
    bool m_insideDcCreator;
    bool m_insideDcDate;
    bool m_insidetable;
    KoOdfStyleProperties *m_currentParagraphTextProperties;
    QString m_currentParagraphParent;
};


#endif // ODFTEXTREADERDOCXBACKEND_H
