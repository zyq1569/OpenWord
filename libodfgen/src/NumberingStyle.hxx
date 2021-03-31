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
 * Copyright (C) 2004 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#ifndef _NUMBERINGSTYLE_HXX_
#define _NUMBERINGSTYLE_HXX_
#include <librevenge/librevenge.h>
#include <map>
#include <string>
#include <vector>

#include "FilterInternal.hxx"

#include "Style.hxx"

class OdfDocumentHandler;
class NumberingManager;

class NumberingStyle : public Style
{
public:
	//! constructor
	NumberingStyle(const librevenge::RVNGPropertyList &xPropList, const librevenge::RVNGString &psName);
	//! destructor
	~NumberingStyle() override {};
	//! write a style
	void writeStyle(OdfDocumentHandler *pHandler, NumberingManager const &manager) const;

	//! returns the hash name corresponding to a style
	static librevenge::RVNGString getHashName(const librevenge::RVNGPropertyList &xPropList);

private:
	static void writeCondition(librevenge::RVNGPropertyList const &propList, OdfDocumentHandler *pHandler, NumberingManager const &manager);

	librevenge::RVNGPropertyList mPropList;
};

/** main class to create/store/write the numbering styles */
class NumberingManager
{
public:
	//! constructor
	NumberingManager();
	//! destructor
	virtual ~NumberingManager();
	//! clean all data
	void clean();
	//! write all
	virtual void write(OdfDocumentHandler *pHandler) const
	{
		write(pHandler, Style::Z_ContentAutomatic);
	}
	//! write automatic/named/... style
	void write(OdfDocumentHandler *pHandler, Style::Zone zone) const;
	//! create a new numbering style
	void addStyle(const librevenge::RVNGPropertyList &xPropList);
	/* create a new style if it does not exists. In all case, returns the name of the style

	Note: using Numbering_num%i as new name*/
	librevenge::RVNGString findOrAdd(const librevenge::RVNGPropertyList &xPropList);
	//! return the style name corresponding to a local name
	librevenge::RVNGString getStyleName(librevenge::RVNGString const &localName) const;

private:
	//! hash key -> name
	std::map<librevenge::RVNGString, librevenge::RVNGString> mHashNameMap;
	//! style name -> NumberingStyle
	std::map<librevenge::RVNGString, std::shared_ptr<NumberingStyle> > mNumberingHash;
};
#endif

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
