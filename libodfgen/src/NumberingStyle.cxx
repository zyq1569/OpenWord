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

#include "NumberingStyle.hxx"

#include <math.h>
#ifdef _MSC_VER
# include <minmax.h>
#endif
#include <string.h>

#include <sstream>
#include <string>

#include "DocumentElement.hxx"

#include "SheetStyle.hxx"

NumberingStyle::NumberingStyle(const librevenge::RVNGPropertyList &xPropList, const librevenge::RVNGString &psName)
	: Style(psName), mPropList(xPropList)
{
}

void NumberingStyle::writeCondition(librevenge::RVNGPropertyList const &propList, OdfDocumentHandler *pHandler, NumberingManager const &manager)
{
	librevenge::RVNGString applyName("");
	librevenge::RVNGPropertyListVector const *formula=propList.child("librevenge:formula");
	librevenge::RVNGString formulaString("");
	if (!formula||!propList["librevenge:name"]||
	        (applyName=manager.getStyleName(propList["librevenge:name"]->getStr())).empty() ||
	        (formulaString=SheetManager::convertFormula(*formula)).empty())
	{
		ODFGEN_DEBUG_MSG(("NumberingStyle::writeCondition: can not find condition data\n"));
		return;
	}
	TagOpenElement mapOpen("style:map");
	mapOpen.addAttribute("style:condition",formulaString);
	mapOpen.addAttribute("style:apply-style-name",applyName);
	mapOpen.write(pHandler);
	TagCloseElement("style:map").write(pHandler);
}

void NumberingStyle::writeStyle(OdfDocumentHandler *pHandler, NumberingManager const &manager) const
{
	if (!mPropList["librevenge:value-type"])
	{
		ODFGEN_DEBUG_MSG(("NumberingStyle::writeStyle: can not find value type\n"));
		return;
	}
	std::string type(mPropList["librevenge:value-type"]->getStr().cstr());
	librevenge::RVNGString what("");
	if (type.substr(0,7)=="number:") type=type.substr(7);
	size_t len=type.length();
	if (len>5 && type.substr(len-5)=="-type") type=type.substr(0,len-5);
	if (type=="float" || type=="double") type="number";
	else if (type=="percent") type="percentage";
	else if (type=="bool") type="boolean";
	if (type=="number" || type=="fraction" || type=="percentage" || type=="scientific")
	{
		what.sprintf("number:%s-style", type=="percentage" ? "percentage" : "number");
		TagOpenElement styleOpen(what);
		styleOpen.addAttribute("style:name", getName());
		styleOpen.write(pHandler);
		librevenge::RVNGString subWhat;
		subWhat.sprintf("number:%s", type=="percentage" ? "number" : type=="scientific" ? "scientific-number" : type.c_str());
		TagOpenElement number(subWhat);
		if (mPropList["number:decimal-places"])
			number.addAttribute("number:decimal-places", mPropList["number:decimal-places"]->getStr());
		if (mPropList["number:min-integer-digits"])
			number.addAttribute("number:min-integer-digits", mPropList["number:min-integer-digits"]->getStr());
		else
			number.addAttribute("number:min-integer-digits", "1");
		if (mPropList["number:grouping"])
			number.addAttribute("number:grouping", mPropList["number:grouping"]->getStr());
		if (type=="scientific")
		{
			if (mPropList["number:min-exponent-digits"])
				number.addAttribute("number:min-exponent-digits", mPropList["number:min-exponent-digits"]->getStr());
			else
				number.addAttribute("number:min-exponent-digits", "2");
		}
		else if (type=="fraction")
		{
			if (mPropList["number:min-numerator-digits"])
				number.addAttribute("number:min-numerator-digits", mPropList["number:min-numerator-digits"]->getStr());
			if (mPropList["number:min-denominator-digits"])
				number.addAttribute("number:min-denominator-digits", mPropList["number:min-denominator-digits"]->getStr());
		}
		number.write(pHandler);
		TagCloseElement(subWhat).write(pHandler);
		if (type=="percentage")
		{
			TagOpenElement("number:text").write(pHandler);
			pHandler->characters("%");
			TagCloseElement("number:text").write(pHandler);
		}
	}
	else if (type=="boolean")
	{
		what="number:boolean-style";
		TagOpenElement styleOpen(what);
		styleOpen.addAttribute("style:name", getName());
		styleOpen.write(pHandler);
		TagOpenElement("number:boolean").write(pHandler);
		TagCloseElement("number:boolean").write(pHandler);
	}
	else if (type=="time" || type=="date")
	{
		what.sprintf("number:%s-style", type.c_str());
		TagOpenElement styleOpen(what);
		styleOpen.addAttribute("style:name", getName());
		if (mPropList["number:language"])
			styleOpen.addAttribute("number:language", mPropList["number:language"]->getStr());
		if (mPropList["number:country"])
			styleOpen.addAttribute("number:country", mPropList["number:country"]->getStr());
		if (type=="date" && mPropList["number:automatic-order"])
			styleOpen.addAttribute("number:automatic-order", mPropList["number:automatic-order"]->getStr());
		styleOpen.write(pHandler);
	}
	else if (type=="currency")
	{
		what = "number:currency-style";
		TagOpenElement styleOpen(what);
		styleOpen.addAttribute("style:name", getName());
		styleOpen.write(pHandler);
	}
	else
	{
		ODFGEN_DEBUG_MSG(("NumberingStyle::writeStyle: unexpected value type %s\n", type.c_str()));
		return;
	}
	librevenge::RVNGPropertyListVector const *format=mPropList.child("librevenge:format");
	// now read the potential formats sub list
	for (unsigned long f=0; format && f < format->count(); ++f)
	{
		librevenge::RVNGPropertyList const &prop=(*format)[f];
		if (!prop["librevenge:value-type"])
		{
			ODFGEN_DEBUG_MSG(("NumberingStyle::writeStyle: can not find format type[%d]\n", int(f)));
			continue;
		}
		std::string wh=prop["librevenge:value-type"]->getStr().cstr();
		if (wh.substr(0,7)=="number:") wh=wh.substr(7);

		if (wh=="number")
		{
			TagOpenElement formatOpen("number:number");
			if (prop["number:decimal-places"])
				formatOpen.addAttribute("number:decimal-places", prop["number:decimal-places"]->getStr());
			if (prop["number:min-integer-digits"])
				formatOpen.addAttribute("number:min-integer-digits", prop["number:min-integer-digits"]->getStr());
			else
				formatOpen.addAttribute("number:min-integer-digits", "1");
			if (prop["number:grouping"])
				formatOpen.addAttribute("number:grouping", prop["number:grouping"]->getStr());
			formatOpen.write(pHandler);
			TagCloseElement("number:number").write(pHandler);
		}
		else if (wh=="year" || wh=="month" || wh=="day" || wh=="day-of-week" || wh=="quarter" || wh=="week-of-year" ||
		         wh=="hours" || wh=="minutes" || wh=="seconds" || wh=="am-pm" || wh=="era")
		{
			librevenge::RVNGString subWhat;
			subWhat.sprintf("number:%s", wh.c_str());
			TagOpenElement formatOpen(subWhat);
			if (prop["number:style"])
				formatOpen.addAttribute("number:style", prop["number:style"]->getStr());
			if (prop["number:textual"])
				formatOpen.addAttribute("number:textual", prop["number:textual"]->getStr());
			if (wh=="seconds" && prop["number:decimal-places"])
				formatOpen.addAttribute("number:decimal-places", prop["number:decimal-places"]->getStr());
			formatOpen.write(pHandler);
			TagCloseElement(subWhat).write(pHandler);
		}
		else if (wh=="text")
		{
			if (prop["librevenge:text"])
			{
				TagOpenElement("number:text").write(pHandler);
				pHandler->characters(prop["librevenge:text"]->getStr());
				TagCloseElement("number:text").write(pHandler);
			}
			else
			{
				ODFGEN_DEBUG_MSG(("NumberingStyle::writeStyle: can not find text data\n"));
			}
		}
		else if (wh=="currency-symbol")
		{
			if (prop["librevenge:currency"])
			{
				TagOpenElement currency("number:currency-symbol");
				if (prop["number:language"])
					currency.addAttribute("number:language", prop["number:language"]->getStr());
				if (prop["number:country"])
					currency.addAttribute("number:country", prop["number:country"]->getStr());
				currency.write(pHandler);
				pHandler->characters(prop["librevenge:currency"]->getStr());
				TagCloseElement("number:currency-symbol").write(pHandler);
			}
			else
			{
				ODFGEN_DEBUG_MSG(("NumberingStyle::writeStyle: can not find currency data\n"));
			}
		}
		else
		{
			ODFGEN_DEBUG_MSG(("NumberingStyle::writeStyle: find unexpected format type:%s\n", wh.c_str()));
		}
	}

	librevenge::RVNGPropertyListVector const *conditions=mPropList.child("librevenge:conditions");
	for (unsigned long c=0; c < (conditions ? conditions->count() : 0); ++c)
		writeCondition((*conditions)[c], pHandler, manager);
	TagCloseElement(what).write(pHandler);
}

librevenge::RVNGString NumberingStyle::getHashName(const librevenge::RVNGPropertyList &propList)
{
	librevenge::RVNGPropertyList pList;
	librevenge::RVNGPropertyList::Iter i(propList);
	for (i.rewind(); i.next();)
	{
		if (i.child())
		{
			if (strcmp(i.key(),"librevenge:format")==0 || strcmp(i.key(),"librevenge:conditions")==0)
				pList.insert(i.key(), *i.child());
		}
		else if (strncmp(i.key(), "number:", 7)==0 || strcmp(i.key(), "librevenge:value-type"))
			pList.insert(i.key(), i()->clone());
	}
	return pList.getPropString();
}

NumberingManager::NumberingManager() : mHashNameMap(), mNumberingHash()
{
}

NumberingManager::~NumberingManager()
{
}

void NumberingManager::clean()
{
	mNumberingHash.clear();
}

librevenge::RVNGString NumberingManager::getStyleName(librevenge::RVNGString const &localName) const
{
	auto it = mNumberingHash.find(localName);
	if (it==mNumberingHash.end() || !it->second)
	{
		ODFGEN_DEBUG_MSG(("NumberingManager::getStyleName: can not find %s\n", localName.cstr()));
		return librevenge::RVNGString("");
	}
	return it->second->getName();
}

void NumberingManager::addStyle(const librevenge::RVNGPropertyList &xPropList)
{
	if (!xPropList["librevenge:name"] || xPropList["librevenge:name"]->getStr().len()==0)
	{
		ODFGEN_DEBUG_MSG(("NumberingManager::addStyle: can not find the style name\n"));
		return;
	}
	librevenge::RVNGString name(xPropList["librevenge:name"]->getStr());
	librevenge::RVNGString finalName;
	if (mNumberingHash.find(name)!=mNumberingHash.end() && mNumberingHash.find(name)->second)
		finalName=mNumberingHash.find(name)->second->getName();
	else
		finalName.sprintf("Numbering_num%i", (int) mNumberingHash.size());

	std::shared_ptr<NumberingStyle> style(new NumberingStyle(xPropList, finalName));
	mHashNameMap[NumberingStyle::getHashName(xPropList)]=finalName;
	mNumberingHash[name]=style;
}

librevenge::RVNGString NumberingManager::findOrAdd(const librevenge::RVNGPropertyList &propList)
{
	librevenge::RVNGString hashKey = NumberingStyle::getHashName(propList);
	std::map<librevenge::RVNGString, librevenge::RVNGString>::const_iterator iter =
	    mHashNameMap.find(hashKey);
	if (iter!=mHashNameMap.end()) return iter->second;

	// ok create a new list
	librevenge::RVNGString finalName;
	finalName.sprintf("Numbering_num%i", (int) mNumberingHash.size());
	std::shared_ptr<NumberingStyle> style(new NumberingStyle(propList, finalName));
	mNumberingHash[finalName]=style;
	mHashNameMap[hashKey]=finalName;
	return finalName;
}

void NumberingManager::write(OdfDocumentHandler *pHandler, Style::Zone zone) const
{
	if (zone!=Style::Z_ContentAutomatic)
		return;
	std::map<librevenge::RVNGString, std::shared_ptr<NumberingStyle> >::const_iterator nIt;
	for (nIt=mNumberingHash.begin(); nIt!=mNumberingHash.end(); ++nIt)
	{
		if (!nIt->second) continue;
		nIt->second->writeStyle(pHandler, *this);
	}
}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
