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
 * Copyright (C) 2007 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#include <memory>
#include <sstream>

#include <libwpg/libwpg.h>

#include "WPG1Parser.h"
#include "WPG2Parser.h"
#include "WPGHeader.h"
#include "WPGXParser.h"
#include "libwpg_utils.h"

/**
Analyzes the content of an input stream to see if it can be parsed
\param input The input stream
\return A value that indicates whether the content from the input
stream is a WordPerfect Graphics that libwpg is able to parse
*/
WPGAPI bool libwpg::WPGraphics::isSupported(librevenge::RVNGInputStream *input)
{
	if (!input)
		return false;

	std::shared_ptr<librevenge::RVNGInputStream> graphics;

	if (input->isStructured())
	{
		graphics.reset(input->getSubStreamByName("PerfectOffice_MAIN"));
		if (!graphics)
			return false;
	}
	else
		graphics.reset(input, WPGDummyDeleter());

	graphics->seek(0, librevenge::RVNG_SEEK_SET);

	WPGHeader header;
	if (header.load(graphics.get()))
		return header.isSupported();

	return false;
}

/**
Parses the input stream content. It will make callbacks to the functions provided by a
librevenge::RVNGDrawingInterface class implementation when needed. This is often commonly called the
'main parsing routine'.
\param input The input stream
\param drawingInterface A WPGPainterInterface implementation
\return A value that indicates whether the parsing was successful
*/
WPGAPI bool libwpg::WPGraphics::parse(librevenge::RVNGInputStream *input, ::librevenge::RVNGDrawingInterface *drawingInterface, libwpg::WPGFileFormat fileFormat)
{
	if (!input || !drawingInterface)
		return false;

	std::shared_ptr<librevenge::RVNGInputStream> graphics;

	if (input->isStructured())
	{
		graphics.reset(input->getSubStreamByName("PerfectOffice_MAIN"));
		if (!graphics)
			return false;
	}
	else
		graphics.reset(input, WPGDummyDeleter());

	graphics->seek(0, librevenge::RVNG_SEEK_SET);

	WPG_DEBUG_MSG(("Loading header...\n"));
	unsigned char tmpMajorVersion = 0x00;
	if (fileFormat == WPG_WPG1)
		tmpMajorVersion = 0x01;
	else if (fileFormat == WPG_WPG2)
		tmpMajorVersion = 0x02;
	WPGHeader header;
	if (!header.load(graphics.get()))
		return false;

	if (!header.isSupported() && (fileFormat == WPG_AUTODETECT))
	{
		WPG_DEBUG_MSG(("Unsupported file format!\n"));
		return false;
	}
	else if (header.isSupported())
	{
		// seek to the start of document
		graphics->seek((long)header.startOfDocument(), librevenge::RVNG_SEEK_SET);
		tmpMajorVersion = (unsigned char)(header.majorVersion());
		if (tmpMajorVersion == 0x01)
		{
			unsigned long returnPosition = header.startOfDocument();
			/* Due to a bug in dumping mechanism, we produced
			 * invalid WPG files by prepending a WPG1 header
			 * to a valid WP file. Let us check this kind of files,
			 * so that we can load our own mess too. */
			if (header.load(graphics.get()) && header.isSupported())
			{
				WPG_DEBUG_MSG(("An invalid graphics we produced :(\n"));
				graphics->seek((long) header.startOfDocument() + 16, librevenge::RVNG_SEEK_SET);
				tmpMajorVersion = (unsigned char)(header.majorVersion());
			}
			else
				graphics->seek((long) returnPosition, librevenge::RVNG_SEEK_SET);

		}
	}
	else
		// here we force parsing of headerless pictures
		graphics->seek(0, librevenge::RVNG_SEEK_SET);

	std::unique_ptr<WPGXParser> parser;
	switch (tmpMajorVersion)
	{
	case 0x01: // WPG1
		WPG_DEBUG_MSG(("Parsing WPG1\n"));
		parser.reset(new WPG1Parser(graphics.get(), drawingInterface));
		return parser->parse();
	case 0x02: // WPG2
		WPG_DEBUG_MSG(("Parsing WPG2\n"));
		parser.reset(new WPG2Parser(graphics.get(), drawingInterface));
		return parser->parse();
	default: // other :-)
		WPG_DEBUG_MSG(("Unknown format\n"));
		return false;
	}
}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
