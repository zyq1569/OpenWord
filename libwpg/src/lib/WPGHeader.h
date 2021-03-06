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

#ifndef __WPGHEADER_H__
#define __WPGHEADER_H__

#include <librevenge-stream/librevenge-stream.h>

class WPGHeader
{
public:
	WPGHeader();

	bool load(librevenge::RVNGInputStream *input);

	bool isSupported() const;

	unsigned long startOfDocument() const;

	int majorVersion() const;

private:
	unsigned char m_identifier[4];          // should always be 0xFF followed by "WPC"
	unsigned long m_startOfDocument;        // index into file
	unsigned char m_productType;            // should always be 1 for WPG files
	unsigned char m_fileType;               // should always be 22 for WPG files
	unsigned char m_majorVersion;           // 2 for WPG 8.0 files
	unsigned char m_minorVersion;           // 0 for WPG 8.0 files
	unsigned int  m_encryptionKey;          // 0 when not encrypted
	unsigned int  m_startOfPacketData;      // unused, since according to the docs no packets are defined
};

#endif // WPGHEADER
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
