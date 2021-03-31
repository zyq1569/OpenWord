/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libodfgen
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2002-2004 William Lachance (wrlach@gmail.com)
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

#include "SheetStyle.hxx"

#include <math.h>
#ifdef _MSC_VER
# include <minmax.h>
#endif
#include <string.h>

#include <sstream>
#include <string>

#include "DocumentElement.hxx"
#include "FilterInternal.hxx"
#include "NumberingStyle.hxx"
#include "TextRunStyle.hxx"

namespace libodfgen
{
static std::string getColumnName(int col)
{
	// note: we can also limit the maximal number of column. However,
	// in this case, the current code must generate a valid string ;
	// of course, the resulting formula will be invalid when col is
	// too big (which seems ok and the best that we can do)
	if (col<0)
	{
		ODFGEN_DEBUG_MSG(("libodfgen::getColumnName[SheetStyle.cxx]: called with invalid column %d\n", col));
		return "ZZZZ"; // we must return something, ZZZZ must make the formula invalid...
	}
	std::string name(1, char(col%26+'A'));
	col /= 26;
	while (col>0)
	{
		--col;
		name.insert(0, std::string(1,char(col%26+'A')));
		col /= 26;
	}
	return name;
}
}
SheetCellStyle::SheetCellStyle(const librevenge::RVNGPropertyList &xPropList, const char *psName) :
	Style(psName),
	mPropList(xPropList)
{
}

void SheetCellStyle::writeStyle(OdfDocumentHandler *pHandler, SheetManager const &manager) const
{
	TagOpenElement styleOpen("style:style");
	styleOpen.addAttribute("style:name", getName());
	if (mPropList["style:parent-style-name"])
		styleOpen.addAttribute("style:parent-style-name", mPropList["style:parent-style-name"]->getStr());
	styleOpen.addAttribute("style:family", "table-cell");
	if (mPropList["librevenge:numbering-name"])
	{
		librevenge::RVNGString numberingName=
		    manager.getNumberingManager().getStyleName(mPropList["librevenge:numbering-name"]->getStr());
		if (numberingName.empty())
		{
			ODFGEN_DEBUG_MSG(("SheetCellStyle::writeStyle can not find numbering style %s\n", mPropList["librevenge:numbering-name"]->getStr().cstr()));
		}
		else
			styleOpen.addAttribute("style:data-style-name", numberingName.cstr());
	}
	styleOpen.write(pHandler);

	librevenge::RVNGPropertyList textProp;
	SpanStyleManager::addSpanProperties(mPropList, textProp);
	if (!textProp.empty())
	{
		pHandler->startElement("style:text-properties", textProp);
		pHandler->endElement("style:text-properties");
	}
	// WLACH_REFACTORING: Only temporary.. a much better solution is to
	// generalize this sort of thing into the "Style" superclass
	librevenge::RVNGPropertyList stylePropList;
	librevenge::RVNGPropertyList paragPropList;
	librevenge::RVNGPropertyList::Iter i(mPropList);
	bool paddingSet=false;
	for (i.rewind(); i.next();)
	{
		auto len = (int) strlen(i.key());
		if (i.child())
			continue;
		if (len > 3 && strncmp(i.key(), "fo:", 3)==0)
		{
			if (len==13 && !strcmp(i.key(), "fo:text-align"))
			{
				paragPropList.insert("fo:text-align", mPropList["fo:text-align"]->clone());
				if (!mPropList["fo:margin-left"])
					paragPropList.insert("fo:margin-left", "0cm");
			}
			else if (len==14 && !strcmp(i.key(), "fo:margin-left"))
				paragPropList.insert("fo:margin-left", mPropList["fo:margin-left"]->clone());
			else
			{
				if (len>=9 && strncmp(i.key(), "fo:padding", 9)==0)
					paddingSet=true;
				stylePropList.insert(i.key(), i()->clone());
			}
		}
		else if (len>6 && strncmp(i.key(), "style:", 6)==0)
		{
			if (len > 22  && !strncmp(i.key(), "style:border-line-width", 23))
			{
				if (!strcmp(i.key(), "style:border-line-width") ||
				        !strcmp(i.key(), "style:border-line-width-left") ||
				        !strcmp(i.key(), "style:border-line-width-right") ||
				        !strcmp(i.key(), "style:border-line-width-top")||
				        !strcmp(i.key(), "style:border-line-width-bottom"))
					stylePropList.insert(i.key(), i()->clone());
			}
			else if (len == 23 && !strcmp(i.key(), "style:text-align-source"))
				stylePropList.insert(i.key(), i()->clone());
			else if (len == 18 && !strcmp(i.key(), "style:cell-protect"))
				stylePropList.insert(i.key(), i()->clone());
			else if (len == 15 && !strcmp(i.key(), "style:direction"))
				stylePropList.insert(i.key(), i()->clone());
			else if (len == 18 && !strcmp(i.key(), "style:print-content"))
				stylePropList.insert(i.key(), i()->clone());
			else if (len == 20 && !strcmp(i.key(), "style:repeat-content"))
				stylePropList.insert(i.key(), i()->clone());
			else if (len == 20 && !strcmp(i.key(), "style:rotation-align"))
				stylePropList.insert(i.key(), i()->clone());
			else if (len == 20 && !strcmp(i.key(), "style:rotation-angle"))
				stylePropList.insert(i.key(), i()->clone());
			else if (len == 12 && !strcmp(i.key(), "style:shadow"))
				stylePropList.insert(i.key(), i()->clone());
			else if (len == 20 && !strcmp(i.key(), "style:vertical-align"))
				stylePropList.insert(i.key(), i()->clone());
			else if (len == 18 && !strcmp(i.key(), "style:writing-mode"))
				stylePropList.insert(i.key(), i()->clone());
		}
	}
	if (!paddingSet)
		stylePropList.insert("fo:padding", "0.0382in");
	pHandler->startElement("style:table-cell-properties", stylePropList);
	pHandler->endElement("style:table-cell-properties");
	if (!paragPropList.empty())
	{
		pHandler->startElement("style:paragraph-properties", paragPropList);
		pHandler->endElement("style:paragraph-properties");
	}
	pHandler->endElement("style:style");
}

SheetRowStyle::SheetRowStyle(const librevenge::RVNGPropertyList &propList, const char *psName) :
	Style(psName),
	mPropList(propList)
{
}

void SheetRowStyle::writeStyle(OdfDocumentHandler *pHandler, SheetManager const &) const
{
	TagOpenElement styleOpen("style:style");
	styleOpen.addAttribute("style:name", getName());
	styleOpen.addAttribute("style:family", "table-row");
	styleOpen.write(pHandler);

	TagOpenElement stylePropertiesOpen("style:table-row-properties");
	if (mPropList["style:row-height"])
		stylePropertiesOpen.addAttribute("style:row-height", mPropList["style:row-height"]->getStr());
	else if (mPropList["style:min-row-height"]) // min-row does not seem to work
		stylePropertiesOpen.addAttribute("style:row-height", mPropList["style:min-row-height"]->getStr());
	if (mPropList["style:use-optimal-row-height"])
		stylePropertiesOpen.addAttribute("style:use-optimal-row-height", mPropList["style:use-optimal-row-height"]->getStr());
	stylePropertiesOpen.addAttribute("fo:keep-together", "auto");
	stylePropertiesOpen.write(pHandler);
	pHandler->endElement("style:table-row-properties");

	pHandler->endElement("style:style");
}


SheetStyle::SheetStyle(const librevenge::RVNGPropertyList &xPropList, const char *psName, Style::Zone zone) :
	Style(psName, zone), mPropList(xPropList), mColumns(nullptr),
	mRowNameHash(), mRowStyleHash(), mCellNameHash(), mCellStyleHash()
{
	mColumns = mPropList.child("librevenge:columns");
}

SheetStyle::~SheetStyle()
{
}

void SheetStyle::addColumnDefinitions(libodfgen::DocumentElementVector &storage) const
{
	if (!mColumns) return;
	int col=1;
	librevenge::RVNGPropertyListVector::Iter j(*mColumns);
	for (j.rewind(); j.next(); ++col)
	{
		auto pTableColumnOpenElement = std::make_shared<TagOpenElement>("table:table-column");
		librevenge::RVNGString sColumnStyleName;
		sColumnStyleName.sprintf("%s_col%i", getName().cstr(), col);
		pTableColumnOpenElement->addAttribute("table:style-name", sColumnStyleName);
		if (j()["table:number-columns-repeated"] && j()["table:number-columns-repeated"]->getInt()>1)
			pTableColumnOpenElement->addAttribute("table:number-columns-repeated",
			                                      j()["table:number-columns-repeated"]->getStr());

		storage.push_back(pTableColumnOpenElement);

		storage.push_back(std::make_shared<TagCloseElement>("table:table-column"));
	}
}

void SheetStyle::writeStyle(OdfDocumentHandler *pHandler, SheetManager const &manager) const
{
	TagOpenElement styleOpen("style:style");
	styleOpen.addAttribute("style:name", getName());
	styleOpen.addAttribute("style:family", "table");
	if (mPropList["style:master-page-name"])
		styleOpen.addAttribute("style:master-page-name", mPropList["style:master-page-name"]->getStr());
	styleOpen.write(pHandler);

	TagOpenElement stylePropertiesOpen("style:table-properties");
	stylePropertiesOpen.addAttribute("table:display", "true");
	if (mPropList["table:align"])
		stylePropertiesOpen.addAttribute("table:align", mPropList["table:align"]->getStr());
	if (mPropList["fo:margin-left"])
		stylePropertiesOpen.addAttribute("fo:margin-left", mPropList["fo:margin-left"]->getStr());
	if (mPropList["fo:margin-right"])
		stylePropertiesOpen.addAttribute("fo:margin-right", mPropList["fo:margin-right"]->getStr());
	if (mPropList["style:width"])
		stylePropertiesOpen.addAttribute("style:width", mPropList["style:width"]->getStr());
	if (mPropList["fo:break-before"])
		stylePropertiesOpen.addAttribute("fo:break-before", mPropList["fo:break-before"]->getStr());
	if (mPropList["table:border-model"])
		stylePropertiesOpen.addAttribute("table:border-model", mPropList["table:border-model"]->getStr());
	stylePropertiesOpen.write(pHandler);

	pHandler->endElement("style:table-properties");

	pHandler->endElement("style:style");

	if (mColumns)
	{
		librevenge::RVNGPropertyListVector::Iter j(*mColumns);
		int col=1;
		for (j.rewind(); j.next(); ++col)
		{
			TagOpenElement columnStyleOpen("style:style");
			librevenge::RVNGString sColumnName;
			sColumnName.sprintf("%s_col%i", getName().cstr(), col);
			columnStyleOpen.addAttribute("style:name", sColumnName);
			columnStyleOpen.addAttribute("style:family", "table-column");
			columnStyleOpen.write(pHandler);

			librevenge::RVNGPropertyList columnProperties(j());
			if (columnProperties["table:number-columns-repeated"])
				columnProperties.remove("table:number-columns-repeated");
			pHandler->startElement("style:table-column-properties", columnProperties);
			pHandler->endElement("style:table-column-properties");

			pHandler->endElement("style:style");
		}
	}

	std::map<librevenge::RVNGString, std::shared_ptr<SheetRowStyle> >::const_iterator rIt;
	for (rIt=mRowStyleHash.begin(); rIt!=mRowStyleHash.end(); ++rIt)
	{
		if (!rIt->second) continue;
		rIt->second->writeStyle(pHandler, manager);
	}

	std::map<librevenge::RVNGString, std::shared_ptr<SheetCellStyle> >::const_iterator cIt;
	for (cIt=mCellStyleHash.begin(); cIt!=mCellStyleHash.end(); ++cIt)
	{
		if (!cIt->second) continue;
		cIt->second->writeStyle(pHandler, manager);
	}
}

librevenge::RVNGString SheetStyle::addRow(const librevenge::RVNGPropertyList &propList)
{
	// first remove unused data
	librevenge::RVNGPropertyList pList;
	librevenge::RVNGPropertyList::Iter i(propList);
	for (i.rewind(); i.next();)
	{
		if (strncmp(i.key(), "librevenge:", 11)==0 ||
		        strcmp(i.key(), "table:number-rows-repeated")==0 || i.child())
			continue;
		pList.insert(i.key(),i()->clone());
	}
	librevenge::RVNGString hashKey = pList.getPropString();
	std::map<librevenge::RVNGString, librevenge::RVNGString>::const_iterator iter =
	    mRowNameHash.find(hashKey);
	if (iter!=mRowNameHash.end()) return iter->second;

	librevenge::RVNGString name;
	name.sprintf("%s_row%i", getName().cstr(), (int) mRowStyleHash.size());
	mRowNameHash[hashKey]=name;
	mRowStyleHash[name]=std::shared_ptr<SheetRowStyle>(new SheetRowStyle(propList, name.cstr()));
	return name;
}

librevenge::RVNGString SheetStyle::addCell(const librevenge::RVNGPropertyList &propList)
{
	// first remove unused data
	librevenge::RVNGPropertyList pList;
	librevenge::RVNGPropertyList::Iter i(propList);
	for (i.rewind(); i.next();)
	{
		if (strncmp(i.key(), "librevenge:", 11)==0 &&
		        strncmp(i.key(), "librevenge:numbering-name", 24)!=0)
			continue;
		if (strncmp(i.key(), "table:number-", 13)==0 &&
		        (strcmp(i.key(), "table:number-columns-repeated")==0 ||
		         strcmp(i.key(), "table:number-columns-spanned")==0 ||
		         strcmp(i.key(), "table:number-rows-spanned")==0 ||
		         strcmp(i.key(), "table:number-matrix-columns-spanned")==0 ||
		         strcmp(i.key(), "table:number-matrix-rows-spanned")==0))
			continue;
		if (i.child())
			continue;

		pList.insert(i.key(),i()->clone());
	}
	librevenge::RVNGString hashKey = pList.getPropString();
	std::map<librevenge::RVNGString, librevenge::RVNGString>::const_iterator iter =
	    mCellNameHash.find(hashKey);
	if (iter!=mCellNameHash.end()) return iter->second;

	librevenge::RVNGString name;
	name.sprintf("%s_cell%i", getName().cstr(), (int) mCellStyleHash.size());
	mCellNameHash[hashKey]=name;
	mCellStyleHash[name]=std::shared_ptr<SheetCellStyle>(new SheetCellStyle(propList, name.cstr()));
	return name;
}

SheetManager::SheetManager(NumberingManager &numberingManager) :
	mpNumberingManager(numberingManager), mbSheetOpened(false), mSheetStyles()
{
}

SheetManager::~SheetManager()
{
}

void SheetManager::clean()
{
	mSheetStyles.clear();
}

bool SheetManager::openSheet(const librevenge::RVNGPropertyList &xPropList, Style::Zone zone)
{
	if (mbSheetOpened)
	{
		ODFGEN_DEBUG_MSG(("SheetManager::oops: a sheet is already open\n"));
		return false;
	}
	mbSheetOpened=true;
	if (zone==Style::Z_Unknown)
		zone=Style::Z_ContentAutomatic;

	librevenge::RVNGString sTableName;
	if (zone==Style::Z_StyleAutomatic)
		sTableName.sprintf("Sheet_M%i", (int) mSheetStyles.size());
	else
		sTableName.sprintf("Sheet%i", (int) mSheetStyles.size());
	std::shared_ptr<SheetStyle> sheet(new SheetStyle(xPropList, sTableName.cstr(), zone));
	mSheetStyles.push_back(sheet);
	return true;
}

bool SheetManager::closeSheet()
{
	if (!mbSheetOpened)
	{
		ODFGEN_DEBUG_MSG(("SheetManager::oops: no sheet are opened\n"));
		return false;
	}
	mbSheetOpened=false;
	return true;
}

librevenge::RVNGString SheetManager::convertFormula(const librevenge::RVNGPropertyListVector &formula)
{
	char const *operators[] =
	{
		"(", ")", "+", "-", "*", "/", "=", "<>",  ";", "<", ">", "<=", ">=", "^", "&", "!", "~", ":", "%", "{", "}", "|"
	};
	librevenge::RVNGString res("");
	std::stringstream s;
	s << "of:=";
	for (unsigned long i=0; i<formula.count(); ++i)
	{
		librevenge::RVNGPropertyList const &list=formula[i];
		if (!list["librevenge:type"])
		{
			ODFGEN_DEBUG_MSG(("SheetManager::convertFormula can not find %s formula type !!!\n", s.str().c_str()));
			return res;
		}
		std::string type(list["librevenge:type"]->getStr().cstr());
		if (type=="librevenge-operator")
		{
			if (!list["librevenge:operator"])
			{
				ODFGEN_DEBUG_MSG(("SheetManager::convertFormula can not find operator for formula[%s]!!!\n", s.str().c_str()));
				return res;
			}
			std::string oper(list["librevenge:operator"]->getStr().cstr());
			bool find=false;
			for (auto &w : operators)
			{
				if (oper!=w) continue;
				s << oper;
				find=true;
				break;
			}
			if (!find)
			{
				ODFGEN_DEBUG_MSG(("SheetManager::convertFormula find unknown operator for formula[%s]!!!\n", s.str().c_str()));
				return res;
			}
		}
		else if (type=="librevenge-function")
		{
			if (!list["librevenge:function"])
			{
				ODFGEN_DEBUG_MSG(("SheetManager::convertFormula can not find value for formula[%s]!!!\n", s.str().c_str()));
				return res;
			}
			s << list["librevenge:function"]->getStr().cstr();
		}
		else if (type=="librevenge-number")
		{
			if (!list["librevenge:number"])
			{
				ODFGEN_DEBUG_MSG(("SheetManager::convertFormula can not find value for formula[%s]!!!\n", s.str().c_str()));
				return res;
			}
			s << list["librevenge:number"]->getStr().cstr();
		}
		else if (type=="librevenge-text")
		{
			if (!list["librevenge:text"])
			{
				ODFGEN_DEBUG_MSG(("SheetManager::convertFormula can not find text for formula[%s]!!!\n", s.str().c_str()));
				return res;
			}
			librevenge::RVNGString escaped;
			escaped.appendEscapedXML(list["librevenge:text"]->getStr());
			s << "\"" << escaped.cstr() << "\"";
		}
		else if (type=="librevenge-cell")
		{
			librevenge::RVNGString range=convertCellRange(list);
			if (range.empty())
			{
				// look for special case: a complete row or column
				if ((list["librevenge:column"] && list["librevenge:row"]) ||
				        (!list["librevenge:column"] && !list["librevenge:row"]))
					return res;
				if (i+2<formula.count() &&
				        formula[i+1]["librevenge:operator"] && formula[i+1]["librevenge:operator"]->getStr()==":" &&
				        formula[i+2]["librevenge:type"] && formula[i+2]["librevenge:type"]->getStr()=="librevenge-cell")
				{
					// cell followed by a range's operator and a cell, recreate the range cells...
					auto rList(list);
					if (list["librevenge:column"]) rList.insert("librevenge:start-column", list["librevenge:column"]->getStr());
					if (list["librevenge:column-absolute"]) rList.insert("librevenge:start-column-absolute", list["librevenge:column-absolute"]->getStr());
					if (list["librevenge:row"]) rList.insert("librevenge:start-row", list["librevenge:row"]->getStr());
					if (list["librevenge:row-absolute"]) rList.insert("librevenge:start-row-absolute", list["librevenge:row-absolute"]->getStr());
					if (formula[i+2]["librevenge:column"]) rList.insert("librevenge:end-column", formula[i+2]["librevenge:column"]->getStr());
					if (formula[i+2]["librevenge:column-absolute"]) rList.insert("librevenge:end-column-absolute", formula[i+2]["librevenge:column-absolute"]->getStr());
					if (formula[i+2]["librevenge:row"]) rList.insert("librevenge:end-row", formula[i+2]["librevenge:row"]->getStr());
					if (formula[i+2]["librevenge:row-absolute"]) rList.insert("librevenge:end-row-absolute", formula[i+2]["librevenge:row-absolute"]->getStr());
					i += 2;
					range=convertRowOrColumnCellsRange(rList);
				}
				else
				{
					// isolated cell, recreate a range cells
					auto rList(list);
					if (list["librevenge:column"])
					{
						rList.insert("librevenge:start-column", list["librevenge:column"]->getStr());
						rList.insert("librevenge:end-column", list["librevenge:column"]->getStr());
					}
					if (list["librevenge:column-absolute"])
					{
						rList.insert("librevenge:start-column-absolute", list["librevenge:column-absolute"]->getStr());
						rList.insert("librevenge:end-column-absolute", list["librevenge:column-absolute"]->getStr());
					}
					if (list["librevenge:row"])
					{
						rList.insert("librevenge:start-row", list["librevenge:row"]->getStr());
						rList.insert("librevenge:end-row", list["librevenge:row"]->getStr());
					}
					if (list["librevenge:row-absolute"])
					{
						rList.insert("librevenge:start-row-absolute", list["librevenge:row-absolute"]->getStr());
						rList.insert("librevenge:end-row-absolute", list["librevenge:row-absolute"]->getStr());
					}
					range=convertRowOrColumnCellsRange(rList);
				}
				if (range.empty()) return res;
			}
			s << "[" << range.cstr() << "]";
		}
		else if (type=="librevenge-cells")
		{
			librevenge::RVNGString ranges=convertCellsRange(list);
			if (ranges.empty()) ranges=convertRowOrColumnCellsRange(list); // check for columns or rows ranges
			if (ranges.empty()) return res;
			s << "[" << ranges.cstr() << "]";
		}
		else
		{
			ODFGEN_DEBUG_MSG(("SheetManager::convertFormula find unknown type %s!!!\n", type.c_str()));
			return res;
		}
	}
	return librevenge::RVNGString::escapeXML(s.str().c_str());
}

librevenge::RVNGString SheetManager::convertCellRange(const librevenge::RVNGPropertyList &list)
{
	std::stringstream s;
	librevenge::RVNGString res("");
	if (!list["librevenge:row"]||!list["librevenge:column"])
	{
		ODFGEN_DEBUG_MSG(("SheetManager::convertCellRange can not find cordinate!!!\n"));
		return res;
	}
	int column=list["librevenge:column"]->getInt();
	int row=list["librevenge:row"]->getInt();
	if (column<0 || row<0)
	{
		ODFGEN_DEBUG_MSG(("SheetManager::convertCellRange: find bad coordinate!!!\n"));
		return res;
	}
	if (list["librevenge:sheet-name"] || list["librevenge:sheet"])
	{
		if (list["librevenge:file-name"]) s << "'" << list["librevenge:file-name"]->getStr().cstr() << "'#";
		if (list["librevenge:sheet-name"])
			s << list["librevenge:sheet-name"]->getStr().cstr();
		else
			s << list["librevenge:sheet"]->getStr().cstr();
	}
	s << ".";
	if (list["librevenge:column-absolute"] && list["librevenge:column-absolute"]->getInt()) s << "$";
	s << libodfgen::getColumnName(column);
	if (list["librevenge:row-absolute"] && list["librevenge:row-absolute"]->getInt()) s << "$";
	s << row+1;
	return s.str().c_str();
}

librevenge::RVNGString SheetManager::convertRowOrColumnCellsRange(const librevenge::RVNGPropertyList &list)
{
	std::stringstream s;
	librevenge::RVNGString res("");
	bool isColumn=true;
	if (list["librevenge:start-row"]) // check if this is a row ranges
	{
		if (!list["librevenge:end-row"] || list["librevenge:start-column"]) return res;
		isColumn=false;
	}
	else if (!list["librevenge:start-column"] || !list["librevenge:end-column"])
		return res;
	int dim1=list[isColumn ? "librevenge:start-column" : "librevenge:start-row"]->getInt();
	int dim2=list[isColumn ? "librevenge:end-column" : "librevenge:end-row"]->getInt();
	if (dim1<0 || dim2<dim1)
	{
		ODFGEN_DEBUG_MSG(("SheetManager::convertRowOrColumnCellsRange: find bad coordinates!!!\n"));
		return res;
	}
	if (list["librevenge:sheet-name"] || list["librevenge:start-sheet-name"])
	{
		if (list["librevenge:file-name"]) s << "'" << list["librevenge:file-name"]->getStr().cstr() << "'#";
		if (list["librevenge:sheet-name"])
			s << list["librevenge:sheet-name"]->getStr().cstr();
		else
			s << list["librevenge:start-sheet-name"]->getStr().cstr();
	}
	s << ".";
	if (isColumn)
	{
		if (list["librevenge:start-column-absolute"] && list["librevenge:start-column-absolute"]->getInt()) s << "$";
		s << libodfgen::getColumnName(dim1);
		s << ":";
		if (list["librevenge:end-sheet-name"])
		{
			if (list["librevenge:file-name"]) s << "'" << list["librevenge:file-name"]->getStr().cstr() << "'#";
			s << list["librevenge:end-sheet-name"]->getStr().cstr();
		}
		s << ".";
		if (list["librevenge:end-column-absolute"] && list["librevenge:end-column-absolute"]->getInt()) s << "$";
		s << libodfgen::getColumnName(dim2);
	}
	else
	{
		if (list["librevenge:start-row-absolute"] && list["librevenge:start-row-absolute"]->getInt()) s << "$";
		s << dim1+1 << ":";
		if (list["librevenge:end-sheet-name"])
		{
			if (list["librevenge:file-name"]) s << "'" << list["librevenge:file-name"]->getStr().cstr() << "'#";
			s << list["librevenge:end-sheet-name"]->getStr().cstr();
		}
		s << ".";
		if (list["librevenge:end-row-absolute"] && list["librevenge:end-row-absolute"]->getInt()) s << "$";
		s << dim2+1;
	}
	return s.str().c_str();
}

librevenge::RVNGString SheetManager::convertCellsRange(const librevenge::RVNGPropertyList &list)
{
	std::stringstream s;
	librevenge::RVNGString res("");
	if (!list["librevenge:start-row"]||!list["librevenge:start-column"])
	{
		ODFGEN_DEBUG_MSG(("SheetManager::convertCellsRange can not find cordinate!!!\n"));
		return res;
	}
	int column=list["librevenge:start-column"]->getInt();
	int row=list["librevenge:start-row"]->getInt();
	if (column<0 || row<0)
	{
		ODFGEN_DEBUG_MSG(("SheetManager::convertCellsRange: find bad coordinate1!!!\n"));
		return res;
	}
	if (list["librevenge:sheet-name"] || list["librevenge:start-sheet-name"])
	{
		if (list["librevenge:file-name"]) s << "'" << list["librevenge:file-name"]->getStr().cstr() << "'#";
		if (list["librevenge:sheet-name"])
			s << list["librevenge:sheet-name"]->getStr().cstr();
		else
			s << list["librevenge:start-sheet-name"]->getStr().cstr();
	}
	s << ".";
	if (list["librevenge:start-column-absolute"] && list["librevenge:start-column-absolute"]->getInt()) s << "$";
	s << libodfgen::getColumnName(column);
	if (list["librevenge:start-row-absolute"] && list["librevenge:start-row-absolute"]->getInt()) s << "$";
	s << row+1 << ":";
	if (list["librevenge:end-sheet-name"])
	{
		if (list["librevenge:file-name"]) s << "'" << list["librevenge:file-name"]->getStr().cstr() << "'#";
		s << list["librevenge:end-sheet-name"]->getStr().cstr();
	}
	s << ".";
	if (list["librevenge:end-column"])
		column=list["librevenge:end-column"]->getInt();
	if (list["librevenge:end-row"])
		row=list["librevenge:end-row"]->getInt();
	if (column<0 || row<0)
	{
		ODFGEN_DEBUG_MSG(("SheetManager::convertCellsRange: find bad coordinate2!!!\n"));
		return res;
	}
	if (list["librevenge:end-column-absolute"] && list["librevenge:end-column-absolute"]->getInt()) s << "$";
	s << libodfgen::getColumnName(column);
	if (list["librevenge:end-row-absolute"] && list["librevenge:end-row-absolute"]->getInt()) s << "$";
	s << row+1;
	return s.str().c_str();
}

void SheetManager::write(OdfDocumentHandler *pHandler, Style::Zone zone) const
{
	for (const auto &sheetStyle : mSheetStyles)
	{
		if (sheetStyle && sheetStyle->getZone()==zone)
			sheetStyle->writeStyle(pHandler, *this);
	}
}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
