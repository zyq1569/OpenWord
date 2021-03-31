/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libodfgen
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2006 Ariya Hidayat (ariya@kde.org)
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
#ifndef LIBODFGEN_ODPGENERATOR_HXX_INCLUDED
#define LIBODFGEN_ODPGENERATOR_HXX_INCLUDED

#include <librevenge/librevenge.h>

#include "libodfgen-api.hxx"
#include "OdfDocumentHandler.hxx"

class OdfGenerator;
class OdpGeneratorPrivate;

/** A generator for presentations.
  *
  * See @c librevenge library for documentation of the
  * librevenge::KEYPresentationInterface interface.
  */
class ODFGENAPI OdpGenerator : public librevenge::RVNGPresentationInterface
{
public:
	OdpGenerator();
	~OdpGenerator() override;
	void addDocumentHandler(OdfDocumentHandler *pHandler, const OdfStreamType streamType);
	librevenge::RVNGStringVector getObjectNames() const;
	bool getObjectContent(librevenge::RVNGString const &objectName, OdfDocumentHandler *pHandler);

	void startDocument(const ::librevenge::RVNGPropertyList &propList) override;
	void endDocument() override;
	void setDocumentMetaData(const ::librevenge::RVNGPropertyList &propList) override;
	void defineEmbeddedFont(const librevenge::RVNGPropertyList &propList) override;
	void startSlide(const ::librevenge::RVNGPropertyList &propList) override;
	void endSlide() override;
	void startMasterSlide(const ::librevenge::RVNGPropertyList &propList) override;
	void endMasterSlide() override;
	void setSlideTransition(const ::librevenge::RVNGPropertyList &propList) override;
	void startLayer(const ::librevenge::RVNGPropertyList &propList) override;
	void endLayer() override;
	void startEmbeddedGraphics(const ::librevenge::RVNGPropertyList &propList) override;
	void endEmbeddedGraphics() override;
	void openGroup(const ::librevenge::RVNGPropertyList &propList) override;
	void closeGroup() override;

	void setStyle(const ::librevenge::RVNGPropertyList &propList) override;

	void drawRectangle(const ::librevenge::RVNGPropertyList &propList) override;
	void drawEllipse(const ::librevenge::RVNGPropertyList &propList) override;
	void drawPolyline(const ::librevenge::RVNGPropertyList &propList) override;
	void drawPolygon(const ::librevenge::RVNGPropertyList &propList) override;
	void drawPath(const ::librevenge::RVNGPropertyList &propList) override;
	void drawGraphicObject(const ::librevenge::RVNGPropertyList &propList) override;
	void drawConnector(const ::librevenge::RVNGPropertyList &propList) override;

	void startTextObject(const ::librevenge::RVNGPropertyList &propList) override;
	void endTextObject() override;
	void defineParagraphStyle(const librevenge::RVNGPropertyList &propList) override;
	void openParagraph(const ::librevenge::RVNGPropertyList &propList) override;
	void closeParagraph() override;
	void defineCharacterStyle(const librevenge::RVNGPropertyList &propList) override;
	void openSpan(const ::librevenge::RVNGPropertyList &propList) override;
	void closeSpan() override;

	void openLink(const librevenge::RVNGPropertyList &propList) override;
	void closeLink() override;

	void insertText(const ::librevenge::RVNGString &str) override;
	void insertTab() override;
	void insertSpace() override;
	void insertLineBreak() override;
	void insertField(const ::librevenge::RVNGPropertyList &propList) override;

	void openOrderedListLevel(const ::librevenge::RVNGPropertyList &propList) override;
	void openUnorderedListLevel(const ::librevenge::RVNGPropertyList &propList) override;
	void closeOrderedListLevel() override;
	void closeUnorderedListLevel() override;
	void openListElement(const ::librevenge::RVNGPropertyList &propList) override;
	void closeListElement() override;

	void startTableObject(const ::librevenge::RVNGPropertyList &propList) override;
	void openTableRow(const ::librevenge::RVNGPropertyList &propList) override;
	void closeTableRow() override;
	void openTableCell(const ::librevenge::RVNGPropertyList &propList) override;
	void closeTableCell() override;
	void insertCoveredTableCell(const ::librevenge::RVNGPropertyList &propList) override;
	void endTableObject() override;

	void startComment(const ::librevenge::RVNGPropertyList &propList) override;
	void endComment() override;

	void startNotes(const ::librevenge::RVNGPropertyList &propList) override;
	void endNotes() override;

	void defineChartStyle(const ::librevenge::RVNGPropertyList &propList) override;
	void openChart(const ::librevenge::RVNGPropertyList &propList) override;
	void closeChart() override;
	void openChartTextObject(const ::librevenge::RVNGPropertyList &propList) override;
	void closeChartTextObject() override;
	void openChartPlotArea(const ::librevenge::RVNGPropertyList &propList) override;
	void closeChartPlotArea() override;
	void insertChartAxis(const ::librevenge::RVNGPropertyList &propList) override;
	void openChartSeries(const ::librevenge::RVNGPropertyList &propList) override;
	void closeChartSeries() override;

	void openAnimationSequence(const ::librevenge::RVNGPropertyList &propList) override;
	void closeAnimationSequence() override;
	void openAnimationGroup(const ::librevenge::RVNGPropertyList &propList) override;
	void closeAnimationGroup() override;
	void openAnimationIteration(const ::librevenge::RVNGPropertyList &propList) override;
	void closeAnimationIteration() override;
	void insertMotionAnimation(const ::librevenge::RVNGPropertyList &propList) override;
	void insertColorAnimation(const ::librevenge::RVNGPropertyList &propList) override;
	void insertAnimation(const ::librevenge::RVNGPropertyList &propList) override;
	void insertEffect(const ::librevenge::RVNGPropertyList &propList) override;

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
	// disable copying
	OdpGenerator(OdpGenerator const &);
	OdpGenerator &operator=(OdpGenerator const &);

	OdpGeneratorPrivate *mpImpl;
};

#endif // LIBODFGEN_ODPGENERATOR_HXX_INCLUDED

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
