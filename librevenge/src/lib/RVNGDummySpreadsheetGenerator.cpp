/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#include <librevenge-generators/RVNGDummySpreadsheetGenerator.h>

namespace librevenge
{

RVNGDummySpreadsheetGenerator::RVNGDummySpreadsheetGenerator()
{
}

RVNGDummySpreadsheetGenerator::~RVNGDummySpreadsheetGenerator()
{
}

void RVNGDummySpreadsheetGenerator::setDocumentMetaData(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::defineEmbeddedFont(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::startDocument(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::endDocument()
{
}

//
// Sheet
//
void RVNGDummySpreadsheetGenerator::defineSheetNumberingStyle(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::openSheet(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeSheet()
{
}

void RVNGDummySpreadsheetGenerator::openSheetRow(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeSheetRow()
{
}

void RVNGDummySpreadsheetGenerator::openSheetCell(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeSheetCell()
{
}

//
// Chart
//
void RVNGDummySpreadsheetGenerator::defineChartStyle(const RVNGPropertyList &)
{
}
void RVNGDummySpreadsheetGenerator::openChart(const RVNGPropertyList &)
{
}
void RVNGDummySpreadsheetGenerator::closeChart()
{
}
void RVNGDummySpreadsheetGenerator::openChartTextObject(const RVNGPropertyList &)
{
}
void RVNGDummySpreadsheetGenerator::closeChartTextObject()
{
}
void RVNGDummySpreadsheetGenerator::openChartPlotArea(const RVNGPropertyList &)
{
}
void RVNGDummySpreadsheetGenerator::closeChartPlotArea()
{
}
void RVNGDummySpreadsheetGenerator::insertChartAxis(const RVNGPropertyList &)
{
}
void RVNGDummySpreadsheetGenerator::openChartSerie(const RVNGPropertyList &)
{
}
void RVNGDummySpreadsheetGenerator::closeChartSerie()
{
}

//
// Graphic
//
void RVNGDummySpreadsheetGenerator::openGroup(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeGroup()
{
}

void RVNGDummySpreadsheetGenerator::defineGraphicStyle(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::drawRectangle(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::drawEllipse(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::drawPolygon(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::drawPolyline(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::drawPath(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::drawConnector(const RVNGPropertyList &)
{
}

//
//
//

void RVNGDummySpreadsheetGenerator::definePageStyle(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::openPageSpan(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closePageSpan()
{
}

void RVNGDummySpreadsheetGenerator::openHeader(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeHeader()
{
}

void RVNGDummySpreadsheetGenerator::openFooter(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeFooter()
{
}

void RVNGDummySpreadsheetGenerator::defineParagraphStyle(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::openParagraph(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeParagraph()
{
}

void RVNGDummySpreadsheetGenerator::defineCharacterStyle(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::openSpan(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeSpan()
{
}

void RVNGDummySpreadsheetGenerator::openLink(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeLink()
{
}

void RVNGDummySpreadsheetGenerator::defineSectionStyle(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::openSection(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeSection()
{
}

void RVNGDummySpreadsheetGenerator::insertTab()
{
}

void RVNGDummySpreadsheetGenerator::insertSpace()
{
}

void RVNGDummySpreadsheetGenerator::insertText(const RVNGString &)
{
}

void RVNGDummySpreadsheetGenerator::insertLineBreak()
{
}

void RVNGDummySpreadsheetGenerator::insertField(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::openOrderedListLevel(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::openUnorderedListLevel(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeOrderedListLevel()
{
}

void RVNGDummySpreadsheetGenerator::closeUnorderedListLevel()
{
}

void RVNGDummySpreadsheetGenerator::openListElement(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeListElement()
{
}

void RVNGDummySpreadsheetGenerator::openFootnote(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeFootnote()
{
}

void RVNGDummySpreadsheetGenerator::openEndnote(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeEndnote()
{
}

void RVNGDummySpreadsheetGenerator::openComment(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeComment()
{
}

void RVNGDummySpreadsheetGenerator::openTextBox(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeTextBox()
{
}

void RVNGDummySpreadsheetGenerator::openTable(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::openTableRow(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeTableRow()
{
}

void RVNGDummySpreadsheetGenerator::openTableCell(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeTableCell()
{
}

void RVNGDummySpreadsheetGenerator::insertCoveredTableCell(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeTable()
{
}

void RVNGDummySpreadsheetGenerator::openFrame(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::closeFrame()
{
}

void RVNGDummySpreadsheetGenerator::insertBinaryObject(const RVNGPropertyList &)
{
}

void RVNGDummySpreadsheetGenerator::insertEquation(const RVNGPropertyList &)
{
}

}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
