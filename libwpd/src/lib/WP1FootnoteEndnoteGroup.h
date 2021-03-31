/* libwpd
 * Copyright (C) 2006 Fridrich Strba (fridrich.strba@bluewin.ch)
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
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

#ifndef WP1FOOTNOTEENDNOTEGROUP_H
#define WP1FOOTNOTEENDNOTEGROUP_H

#include "WP1VariableLengthGroup.h"
#include "libwpd_internal.h"

class WP1SubDocument;

class WP1FootnoteEndnoteGroup : public WP1VariableLengthGroup
{
public:
	WP1FootnoteEndnoteGroup(WPXInputStream *input, WPXEncryption *encryption, uint8_t group);
	~WP1FootnoteEndnoteGroup();	
	void _readContents(WPXInputStream *input, WPXEncryption *encryption);
	void parse(WP1Listener *listener);

private:
	WP1FootnoteEndnoteGroup(const WP1FootnoteEndnoteGroup&);
	WP1FootnoteEndnoteGroup& operator=(const WP1FootnoteEndnoteGroup&);
	WPXNoteType m_noteType;
	uint16_t m_noteNumber;
	WP1SubDocument *m_subDocument;
};

#endif /* WP1FOOTNOTEENDNOTEGROUP_H */
