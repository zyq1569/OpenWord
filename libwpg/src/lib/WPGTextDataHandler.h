/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpg
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2006 Ariya Hidayat (ariya@kde.org)
 * Copyright (C) 2004 Marc Oude Kotte (marc@solcon.nl)
 * Copyright (C) 2005 Fridrich Strba (fridrich.strba@bluewin.ch)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpg.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef __WPGXTEXTDATAHANDLER_H__
#define __WPGXTEXTDATAHANDLER_H__

#include <librevenge/librevenge.h>

class WPGTextDataHandler : public librevenge::RVNGTextInterface
{
public:
	WPGTextDataHandler(librevenge::RVNGDrawingInterface *painter) :
		m_painter(painter),
		m_fontName("Times New Roman"),
		m_paragraphStyle(),
		m_textStyle() {}

	~WPGTextDataHandler() override {}
	void setDocumentMetaData(const librevenge::RVNGPropertyList & /* propList */) override {}

	void startDocument(const librevenge::RVNGPropertyList & /* propList */) override {}
	void endDocument() override {}

	void defineEmbeddedFont(const librevenge::RVNGPropertyList & /* propList */) override {}

	void definePageStyle(const librevenge::RVNGPropertyList & /* propList */) override {}
	void openPageSpan(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closePageSpan() override {}
	void openHeader(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeHeader() override {}
	void openFooter(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeFooter() override {}

	void defineParagraphStyle(const librevenge::RVNGPropertyList & /* propList */) override {}
	void openParagraph(const librevenge::RVNGPropertyList &propList) override;
	void closeParagraph() override;

	void defineCharacterStyle(const librevenge::RVNGPropertyList & /* propList */) override {}
	void openSpan(const librevenge::RVNGPropertyList &propList) override;
	void closeSpan() override;

	void openLink(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeLink() override {}

	void defineSectionStyle(const librevenge::RVNGPropertyList & /* propList */) override {}
	void openSection(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeSection() override {}

	void insertTab() override;
	void insertSpace() override;
	void insertText(const librevenge::RVNGString &text) override;
	void insertLineBreak() override;
	void insertField(const librevenge::RVNGPropertyList & /* propList */) override {}

	void openOrderedListLevel(const librevenge::RVNGPropertyList & /* propList */) override {}
	void openUnorderedListLevel(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeOrderedListLevel() override {}
	void closeUnorderedListLevel() override {}
	void openListElement(const librevenge::RVNGPropertyList &propList) override;
	void closeListElement() override;

	void openFootnote(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeFootnote() override {}
	void openEndnote(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeEndnote() override {}
	void openComment(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeComment() override {}
	void openTextBox(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeTextBox() override {}

	void openTable(const librevenge::RVNGPropertyList & /* propList */) override {}
	void openTableRow(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeTableRow() override {}
	void openTableCell(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeTableCell() override {}
	void insertCoveredTableCell(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeTable() override {}

	void openFrame(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeFrame() override {}

	void openGroup(const librevenge::RVNGPropertyList & /* propList */) override {}
	void closeGroup() override {}

	void defineGraphicStyle(const librevenge::RVNGPropertyList & /* propList */) override {}
	void drawRectangle(const librevenge::RVNGPropertyList & /* propList */) override {}
	void drawEllipse(const librevenge::RVNGPropertyList & /* propList */) override {}
	void drawPolygon(const librevenge::RVNGPropertyList & /* propList */) override {}
	void drawPolyline(const librevenge::RVNGPropertyList & /* propList */) override {}
	void drawPath(const librevenge::RVNGPropertyList & /* propList */) override {}
	void drawConnector(const librevenge::RVNGPropertyList & /* propList */) override {}

	void insertBinaryObject(const librevenge::RVNGPropertyList & /* propList */) override {}
	void insertEquation(const librevenge::RVNGPropertyList & /* propList */) override {}

private:
	librevenge::RVNGDrawingInterface *m_painter;
	librevenge::RVNGString m_fontName;
	librevenge::RVNGPropertyList m_paragraphStyle, m_textStyle;
	// Unimplemented to prevent compiler from creating crasher ones
	WPGTextDataHandler(const WPGTextDataHandler &);
	WPGTextDataHandler &operator=(const WPGTextDataHandler &);
};

#endif // __WPGXTEXTDATAHANDLER_H__

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
