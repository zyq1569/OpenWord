/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpg
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
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

#ifndef __LIBWPG_UTILS_H__
#define __LIBWPG_UTILS_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>

#include <librevenge-stream/librevenge-stream.h>

#if defined(HAVE_FUNC_ATTRIBUTE_FORMAT)
#define WPG_ATTRIBUTE_PRINTF(fmt, arg) __attribute__((format(printf, fmt, arg)))
#else
#define WPG_ATTRIBUTE_PRINTF(fmt, arg)
#endif

// do nothing with debug messages in a release compile
#ifdef DEBUG

namespace libwpg
{
void debugPrint(const char *format, ...) WPG_ATTRIBUTE_PRINTF(1, 2);
}

#define WPG_DEBUG_MSG(M) libwpg::debugPrint M
#define WPG_DEBUG(M) M

#else

#define WPG_DEBUG_MSG(M)
#define WPG_DEBUG(M)

#endif

namespace libwpg
{

struct WPGDummyDeleter
{
	void operator()(void *) const {}
};

unsigned long getRemainingLength(librevenge::RVNGInputStream *input);

struct EndOfStreamException
{
};

}

#endif // __LIBWPG_UTILS_H__
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
