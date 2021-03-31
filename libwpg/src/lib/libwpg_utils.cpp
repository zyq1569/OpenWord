/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpg
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
 *
 * For further information visit http://libwpg.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#include "libwpg_utils.h"

#include <cstdarg>

namespace libwpg
{

using librevenge::RVNGInputStream;

namespace
{

struct SeekFailedException
{
};

unsigned char readU8(RVNGInputStream *const input)
{
	if (!input || input->isEnd())
		throw EndOfStreamException();

	unsigned long numBytesRead;
	const unsigned char *const p = input->read(1, numBytesRead);

	if (p && numBytesRead == 1)
		return *(const unsigned char *)(p);
	throw EndOfStreamException();
}

void seek(RVNGInputStream *const input, const unsigned long pos)
{
	if (!input)
		throw EndOfStreamException();

	if (0 != input->seek(static_cast<long>(pos), librevenge::RVNG_SEEK_SET))
		throw SeekFailedException();
}

}

#ifdef DEBUG
void debugPrint(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}
#endif

unsigned long getRemainingLength(librevenge::RVNGInputStream *const input)
{
	if (!input)
		throw SeekFailedException();

	const auto begin = (unsigned long) input->tell();
	unsigned long end = 0;

	if (0 == input->seek(0, librevenge::RVNG_SEEK_END))
	{
		end = (unsigned long) input->tell();
	}
	else
	{
		// librevenge::RVNG_SEEK_END does not work. Use the harder way.
		while (!input->isEnd())
			readU8(input);
		end = input->tell();
	}

	seek(input, begin);

	return end - begin;
}

}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
