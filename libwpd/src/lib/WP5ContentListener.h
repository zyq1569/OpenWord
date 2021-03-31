/* libwpd
 * Copyright (C) 2003 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2003 Marc Maurer (uwog@uwog.net)
 * Copyright (C) 2005-2007 Fridrich Strba (fridrich.strba@bluewin.ch)
 * Copyright (C) 2007 Novell, Inc. (http://www.novell.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef WP5CONTENTLISTENER_H
#define WP5CONTENTLISTENER_H

#include "WP5Listener.h"
#include "WPXContentListener.h"
#include "WP5SubDocument.h"
#include "WPXString.h"
#include "libwpd_internal.h"
#include "WPXDocumentInterface.h"
#include <vector>

typedef struct _WP5ContentParsingState WP5ContentParsingState;
struct _WP5ContentParsingState
{
	_WP5ContentParsingState();
	~_WP5ContentParsingState();
	WPXString m_textBuffer;
	WPXString m_noteReference;

	WPXTableList m_tableList;

	bool m_isFrameOpened;
};

class WP5ContentListener : public WP5Listener, protected WPXContentListener
{
public:
	WP5ContentListener(std::list<WPXPageSpan> &pageList, std::vector<WP5SubDocument *> &subDocuments, WPXDocumentInterface *documentInterface);
	~WP5ContentListener();

	void startDocument() { WPXContentListener::startDocument(); };
	void startSubDocument() { WPXContentListener::startSubDocument(); };
	void setFont(const WPXString &fontName, double fontSize);
	void setTabs(const std::vector<WPXTabStop> &tabStops, uint16_t tabOffset);
	void insertCharacter(uint16_t character);
	void insertTab(uint8_t tabType, double tabPosition);
	void insertIndent(uint8_t indentType, double indentPosition);
	void insertEOL();
	void insertBreak(uint8_t breakType) { WPXContentListener::insertBreak(breakType); };
	void lineSpacingChange(double lineSpacing) { WPXContentListener::lineSpacingChange(lineSpacing); };
	void justificationChange(uint8_t justification) { WPXContentListener::justificationChange(justification); };
	void characterColorChange(uint8_t red, uint8_t green, uint8_t blue);
	void attributeChange(bool isOn, uint8_t attribute);
	void pageMarginChange(uint8_t /* side */, uint16_t /* margin */) {};
	void pageFormChange(uint16_t /* length */, uint16_t /* width */, WPXFormOrientation /* orientation */) {};
	void marginChange(uint8_t side, uint16_t margin);
	void paragraphMarginChange(uint8_t /* side */, int16_t /* margin */) {};
	void endDocument() { WPXContentListener::endDocument(); };
	void endSubDocument() { WPXContentListener::endSubDocument(); };

	void defineTable(uint8_t position, uint16_t leftOffset);
	void addTableColumnDefinition(uint32_t width, uint32_t leftGutter, uint32_t rightGutter,
				uint32_t attributes, uint8_t alignment);
	void startTable();
 	void insertRow(uint16_t rowHeight, bool isMinimumHeight, bool isHeaderRow);
 	void insertCell(uint8_t colSpan, uint8_t rowSpan, uint8_t borderBits,
				const RGBSColor * cellFgColor, const RGBSColor * cellBgColor, 
				const RGBSColor * cellBorderColor, WPXVerticalAlignment cellVerticalAlignment, 
				bool useCellAttributes, uint32_t cellAttributes);
 	void endTable();

	void insertNoteReference(const WPXString &noteReference);
	void insertNote(WPXNoteType noteType, const WP5SubDocument *subDocument);
	void headerFooterGroup(uint8_t headerFooterType, uint8_t occurenceBits, WP5SubDocument *subDocument);
	void suppressPageCharacteristics(uint8_t /* suppressCode */) {};
	
	void setDefaultFont(const WPXString &fontName, double fontSize);
	
	void boxOn(uint8_t positionAndType, uint8_t alignment, uint16_t width, uint16_t height, uint16_t x, uint16_t y);
	virtual void boxOff();
	virtual void insertGraphicsData(const WPXBinaryData *data);

protected:
	void _handleSubDocument(const WPXSubDocument *subDocument, WPXSubDocumentType subDocumentType, WPXTableList tableList, int nextTableIndice = 0);

	void _flushText();
	void _changeList() {};

private:
	WP5ContentListener(const WP5ContentListener&);
	WP5ContentListener& operator=(const WP5ContentListener&);
	WP5ContentParsingState *m_parseState;
	std::vector<WP5SubDocument *> &m_subDocuments;
	double m_defaultFontSize;
	WPXString m_defaultFontName;
};

#endif /* WP5CONTENTLISTENER_H */
