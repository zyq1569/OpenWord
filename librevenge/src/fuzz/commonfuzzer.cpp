/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
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
 */

#include "commonfuzzer.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

namespace fuzz
{

namespace
{

unsigned long getLength(librevenge::RVNGInputStream &input)
{
	const long pos = input.tell();
	if (0 > pos)
		return 0;

	long end = 0;

	if (0 == input.seek(0, librevenge::RVNG_SEEK_END))
		end = input.tell();
	if ((0 != input.seek(pos, librevenge::RVNG_SEEK_SET)) || (0 > end))
		return 0;

	return static_cast<unsigned long>(end);
}

void testRead(librevenge::RVNGInputStream &input, std::vector<unsigned char> &buf)
{
	const unsigned long size = getLength(input);
	unsigned long readBytes = 0;
	const unsigned char *data = input.read(size, readBytes);
	buf.resize(size_t(size));
	std::copy_n(data, size, std::back_inserter(buf));
}

}

void testStructuredStream(librevenge::RVNGInputStream &input)
{
	std::vector<unsigned char> buf;

	for (unsigned i = 0, ssc = input.subStreamCount(); i < ssc; ++i)
	{
		std::unique_ptr<librevenge::RVNGInputStream> subStream(input.getSubStreamById(i));
		if (bool(subStream))
			testRead(*subStream, buf);

		const char *const name = input.subStreamName(i);
		std::unique_ptr<librevenge::RVNGInputStream> namedSubStream(input.getSubStreamByName(name));
		if (bool(namedSubStream))
			testRead(*namedSubStream, buf);
	}
}

}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
