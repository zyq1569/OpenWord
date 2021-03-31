/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libodfgen
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2002-2003 William Lachance (wrlach@gmail.com)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpd.sourceforge.net
 */

#ifndef __FILTERINTERNAL_HXX__
#define __FILTERINTERNAL_HXX__

#include <assert.h> // for assert
#include <string.h> // for strcmp

#include <memory>
#include <vector>

#include <librevenge/librevenge.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if defined(HAVE_FUNC_ATTRIBUTE_FORMAT)
#  define ODFGEN_ATTRIBUTE_PRINTF(fmt, arg) __attribute__((format(printf, fmt, arg)))
#else
#  define ODFGEN_ATTRIBUTE_PRINTF(fmt, arg)
#endif

#ifdef DEBUG
#define ODFGEN_DEBUG_MSG(M) libodfgen::debugPrint M
#else
#define ODFGEN_DEBUG_MSG(M)
#endif

#define ODFGEN_N_ELEMENTS(m) sizeof(m)/sizeof(m[0])

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class DocumentElement;

namespace libodfgen
{

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct DummyDeleter
{
	void operator()(void *) {}
};

librevenge::RVNGString doubleToString(const double value);
bool getInchValue(librevenge::RVNGProperty const &prop, double &value);

typedef std::vector<std::shared_ptr<DocumentElement>> DocumentElementVector;

void debugPrint(const char *format, ...)  ODFGEN_ATTRIBUTE_PRINTF(1, 2);

} // namespace libodfgen

#endif
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
