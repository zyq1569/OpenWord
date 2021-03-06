/* libwpd
 * Copyright (C) 2007 Fridrich Strba (fridrich.strba@bluewin.ch)
 * Copyright (C) 2007 Novell, Inc. (http://www.novell.com)
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

#include "WP5IndentGroup.h"
#include "WP5FileStructure.h"
#include "libwpd_internal.h"
#include "WP5Listener.h"
#include "WPXFileStructure.h"

WP5IndentGroup::WP5IndentGroup(WPXInputStream *input, WPXEncryption *encryption, uint8_t groupID) :
	WP5FixedLengthGroup(groupID),
	m_indentType(0),
	m_indentPosition(0.0)
{
	_read(input, encryption);
}

void WP5IndentGroup::_readContents(WPXInputStream *input, WPXEncryption *encryption)
{
	m_indentType = readU8(input, encryption);
	input->seek(4, WPX_SEEK_CUR);
	uint16_t tmpIndentWPU = readU16(input, encryption);
	m_indentPosition = (double)tmpIndentWPU/(double)WPX_NUM_WPUS_PER_INCH;
}

void WP5IndentGroup::parse(WP5Listener *listener)
{
	listener->insertIndent(m_indentType, m_indentPosition);
}
