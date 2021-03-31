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

#ifndef _SHEETSTYLE_HXX_
#define _SHEETSTYLE_HXX_
#include <librevenge/librevenge.h>
#include <map>
#include <string>
#include <vector>

#include "FilterInternal.hxx"

#include "Style.hxx"

class OdfDocumentHandler;
class NumberingManager;
class SheetManager;
class SheetStyle;

class SheetCellStyle : public Style
{
public:
	~SheetCellStyle() override {};
	SheetCellStyle(const librevenge::RVNGPropertyList &xPropList, const char *psName);
	virtual void writeStyle(OdfDocumentHandler *pHandler, SheetManager const &manager) const;
private:
	librevenge::RVNGPropertyList mPropList;
};

class SheetRowStyle : public Style
{
public:
	~SheetRowStyle() override {};
	SheetRowStyle(const librevenge::RVNGPropertyList &propList, const char *psName);
	virtual void writeStyle(OdfDocumentHandler *pHandler, SheetManager const &manager) const;
private:
	librevenge::RVNGPropertyList mPropList;
};

class SheetStyle : public Style
{
public:
	SheetStyle(const librevenge::RVNGPropertyList &xPropList, const char *psName, Style::Zone zone);
	~SheetStyle() override;
	virtual void writeStyle(OdfDocumentHandler *pHandler, SheetManager const &manager) const;
	/** add the sheet's column definitions in given storage.

		\note can be call after opening <table:table>
	 */
	void addColumnDefinitions(libodfgen::DocumentElementVector &storage) const;

	int getNumColumns() const
	{
		return mColumns ? (int)mColumns->count() : 0;
	}

	librevenge::RVNGString addCell(const librevenge::RVNGPropertyList &propList);
	librevenge::RVNGString addRow(const librevenge::RVNGPropertyList &propList);

private:
	librevenge::RVNGPropertyList mPropList;
	librevenge::RVNGPropertyListVector const *mColumns;

	// hash key -> row style name
	std::map<librevenge::RVNGString, librevenge::RVNGString> mRowNameHash;
	// style name -> SheetRowStyle
	std::map<librevenge::RVNGString, std::shared_ptr<SheetRowStyle> > mRowStyleHash;
	// hash key -> cell style name
	std::map<librevenge::RVNGString, librevenge::RVNGString> mCellNameHash;
	// style name -> SheetCellStyle
	std::map<librevenge::RVNGString, std::shared_ptr<SheetCellStyle> > mCellStyleHash;

	// Disable copying
	SheetStyle(const SheetStyle &);
	SheetStyle &operator=(const SheetStyle &);
};

/** main class to create/store/write the sheet styles */
class SheetManager
{
public:
	//! constructor
	explicit SheetManager(NumberingManager &numberingManager);
	//! destructor
	virtual ~SheetManager();
	//! clean all data
	void clean();
	//! write all
	virtual void write(OdfDocumentHandler *pHandler) const
	{
		write(pHandler, Style::Z_StyleAutomatic);
		write(pHandler, Style::Z_ContentAutomatic);
	}
	//! write automatic/named/... style
	void write(OdfDocumentHandler *pHandler, Style::Zone zone) const;
	//! return true if the last sheet was not closed
	bool isSheetOpened() const
	{
		return mbSheetOpened;
	}
	//! return the last opened sheet
	SheetStyle *actualSheet()
	{
		if (!mbSheetOpened || !mSheetStyles.back()) return nullptr;
		return mSheetStyles.back().get();
	}
	//! open a sheet and update the list of elements
	bool openSheet(const librevenge::RVNGPropertyList &xPropList, Style::Zone zone);
	//! close the last sheet
	bool closeSheet();
	//! returns the numbering manager
	NumberingManager &getNumberingManager()
	{
		return mpNumberingManager;
	}
	//! returns the numbering manager
	const NumberingManager &getNumberingManager() const
	{
		return mpNumberingManager;
	}

	static librevenge::RVNGString convertFormula(const librevenge::RVNGPropertyListVector &formatsList);
	static librevenge::RVNGString convertCellRange(const librevenge::RVNGPropertyList &cell);
	static librevenge::RVNGString convertCellsRange(const librevenge::RVNGPropertyList &cells);
	static librevenge::RVNGString convertRowOrColumnCellsRange(const librevenge::RVNGPropertyList &cells);

private:
	//! the numbering manager
	NumberingManager &mpNumberingManager;
	//! flag to know if the last sheet is opened or closed
	bool mbSheetOpened;
	//! the list of style
	std::vector<std::shared_ptr<SheetStyle> > mSheetStyles;
};
#endif

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
