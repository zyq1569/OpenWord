/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libodfgen
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2002-2004 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2004 Fridrich Strba (fridrich.strba@bluewin.ch)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef _ODSGENERATOR_HXX_
#define _ODSGENERATOR_HXX_

#include <librevenge/librevenge.h>

#include "libodfgen-api.hxx"
#include "OdfDocumentHandler.hxx"

class OdfGenerator;
class OdsGeneratorPrivate;

/** A generator for text documents.
  *
  * See @c libdocumentinterface library for documentation of the librevenge::RVNGSpreadsheetInterface
  * interface.
  */
class ODFGENAPI OdsGenerator : public librevenge::RVNGSpreadsheetInterface
{
public:
	OdsGenerator();
	~OdsGenerator() override;

	/** register an handler for a basic type of document */
	void addDocumentHandler(OdfDocumentHandler *pHandler, const OdfStreamType streamType);
	/** returns the list created embedded object (needed to create chart) */
	librevenge::RVNGStringVector getObjectNames() const;
	/** retrieve an embedded object content via a document handler */
	bool getObjectContent(librevenge::RVNGString const &objectName, OdfDocumentHandler *pHandler);

	void setDocumentMetaData(const librevenge::RVNGPropertyList &propList) override;
	void startDocument(const librevenge::RVNGPropertyList &) override;
	void endDocument() override;

	void defineEmbeddedFont(const librevenge::RVNGPropertyList &propList) override;

	void definePageStyle(const librevenge::RVNGPropertyList &) override {}
	void openPageSpan(const librevenge::RVNGPropertyList &propList) override;
	void closePageSpan() override;

	void defineSectionStyle(const librevenge::RVNGPropertyList &) override {}
	void openSection(const librevenge::RVNGPropertyList &propList) override;
	void closeSection() override;

	void openHeader(const librevenge::RVNGPropertyList &propList) override;
	void closeHeader() override;
	void openFooter(const librevenge::RVNGPropertyList &propList) override;
	void closeFooter() override;

	void defineSheetNumberingStyle(const librevenge::RVNGPropertyList &propList) override;
	void openSheet(const librevenge::RVNGPropertyList &propList) override;
	void closeSheet() override;
	void openSheetRow(const librevenge::RVNGPropertyList &propList) override;
	void closeSheetRow() override;
	void openSheetCell(const librevenge::RVNGPropertyList &propList) override;
	void closeSheetCell() override;

	void defineChartStyle(const librevenge::RVNGPropertyList &propList) override;
	void openChart(const librevenge::RVNGPropertyList &propList) override;
	void closeChart() override;
	void openChartTextObject(const librevenge::RVNGPropertyList &propList) override;
	void closeChartTextObject() override;
	void openChartPlotArea(const librevenge::RVNGPropertyList &propList) override;
	void closeChartPlotArea() override;
	void insertChartAxis(const librevenge::RVNGPropertyList &axis) override;
	void openChartSerie(const librevenge::RVNGPropertyList &series) override;
	void closeChartSerie() override;

	void defineParagraphStyle(const librevenge::RVNGPropertyList &propList) override;
	void openParagraph(const librevenge::RVNGPropertyList &propList) override;
	void closeParagraph() override;

	void defineCharacterStyle(const librevenge::RVNGPropertyList &propList) override;
	void openSpan(const librevenge::RVNGPropertyList &propList) override;
	void closeSpan() override;

	void openLink(const librevenge::RVNGPropertyList &propList) override;
	void closeLink() override;

	void insertTab() override;
	void insertSpace() override;
	void insertText(const librevenge::RVNGString &text) override;
	void insertLineBreak() override;
	void insertField(const librevenge::RVNGPropertyList &propList) override;

	void openOrderedListLevel(const librevenge::RVNGPropertyList &propList) override;
	void openUnorderedListLevel(const librevenge::RVNGPropertyList &propList) override;
	void closeOrderedListLevel() override;
	void closeUnorderedListLevel() override;
	void openListElement(const librevenge::RVNGPropertyList &propList) override;
	void closeListElement() override;

	void openFootnote(const librevenge::RVNGPropertyList &propList) override;
	void closeFootnote() override;

	void openComment(const librevenge::RVNGPropertyList &propList) override;
	void closeComment() override;
	void openTextBox(const librevenge::RVNGPropertyList &propList) override;
	void closeTextBox() override;

	void openTable(const librevenge::RVNGPropertyList &propList) override;
	void openTableRow(const librevenge::RVNGPropertyList &propList) override;
	void closeTableRow() override;
	void openTableCell(const librevenge::RVNGPropertyList &propList) override;
	void closeTableCell() override;
	void insertCoveredTableCell(const librevenge::RVNGPropertyList &propList) override;
	void closeTable() override;

	void openFrame(const librevenge::RVNGPropertyList &propList) override;
	void closeFrame() override;

	void insertBinaryObject(const librevenge::RVNGPropertyList &propList) override;

	//
	// simple Graphic
	//

	void openGroup(const librevenge::RVNGPropertyList &propList) override;
	void closeGroup() override;

	void defineGraphicStyle(const librevenge::RVNGPropertyList &propList) override;
	void drawRectangle(const librevenge::RVNGPropertyList &propList) override;
	void drawEllipse(const librevenge::RVNGPropertyList &propList) override;
	void drawPolygon(const librevenge::RVNGPropertyList &propList) override;
	void drawPolyline(const librevenge::RVNGPropertyList &propList) override;
	void drawPath(const librevenge::RVNGPropertyList &propList) override;
	void drawConnector(const librevenge::RVNGPropertyList &propList) override;

	void insertEquation(const librevenge::RVNGPropertyList &) override;

	/** Registers a handler for embedded images.
	  *
	  * @param[in] mimeType MIME type of the image
	  * @param[in] imageHandler a function that handles processing of
	  *		the image's data and generating output
	  */
	void registerEmbeddedImageHandler(const librevenge::RVNGString &mimeType, OdfEmbeddedImage imageHandler);
	/** Registers a handler for embedded objects.
	  *
	  * @param[in] mimeType MIME type of the object
	  * @param[in] objectHandler a function that handles processing of
	  *		the object's data and generating output
	  */
	void registerEmbeddedObjectHandler(const librevenge::RVNGString &mimeType, OdfEmbeddedObject objectHandler);

	//! retrieve data from another odfgenerator ( the list and the embedded handler)
	void initStateWith(OdfGenerator const &orig);

private:
	OdsGenerator(OdsGenerator const &);
	OdsGenerator &operator=(OdsGenerator const &);

	OdsGeneratorPrivate *mpImpl;
};
#endif

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
