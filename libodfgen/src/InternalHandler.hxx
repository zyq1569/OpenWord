/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libodfgen
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2007 Fridrich Strba (fridrich.strba@bluewin.ch)
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

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef _INTERNALHANDLER_HXX_
#define _INTERNALHANDLER_HXX_

#include <librevenge/librevenge.h>
#include <libodfgen/libodfgen.hxx>
#include "DocumentElement.hxx"

#include "FilterInternal.hxx"

class InternalHandler : public OdfDocumentHandler
{
public:
	explicit InternalHandler(libodfgen::DocumentElementVector *elements) :mpElements(elements)
	{
	}
	~InternalHandler() override {};

	void startDocument() override {};
	void endDocument() override {};
	void startElement(const char *psName, const librevenge::RVNGPropertyList &xPropList) override;
	void endElement(const char *psName) override;
	void characters(const librevenge::RVNGString &sCharacters) override;
private:
	InternalHandler(const InternalHandler &);
	InternalHandler &operator=(const InternalHandler &);
	libodfgen::DocumentElementVector *mpElements;
};
#endif

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
