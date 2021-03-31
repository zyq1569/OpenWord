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

#ifndef __WPGXPARSER_H__
#define __WPGXPARSER_H__

#include <map>

#include <librevenge/librevenge.h>

#include <librevenge-stream/librevenge-stream.h>

#include "WPGColor.h"

class WPGXParser
{
public:
	WPGXParser(librevenge::RVNGInputStream *input, librevenge::RVNGDrawingInterface *painter);
	WPGXParser(const WPGXParser &parser);
	virtual ~WPGXParser() {}
	virtual bool parse() = 0;

	unsigned char readU8();
	unsigned short readU16();
	unsigned int readU32();
	short readS16();
	int readS32();
	unsigned int readVariableLengthInteger();
	WPGXParser &operator=(const WPGXParser &parser);

protected:
	librevenge::RVNGInputStream *m_input;
	librevenge::RVNGDrawingInterface *m_painter;
	std::map<int,libwpg::WPGColor> m_colorPalette;
};

#endif // __WPGXPARSER_H__
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
