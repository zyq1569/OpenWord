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

#include "FillManager.hxx"

#include <librevenge/librevenge.h>

#include "FilterInternal.hxx"
#include "DocumentElement.hxx"

void FillManager::clean()
{
	mBitmapStyles.clear();
	mGradientStyles.clear();
	mHatchStyles.clear();
	mOpacityStyles.clear();

	mBitmapNameMap.clear();
	mGradientNameMap.clear();
	mDisplayGradientNameMap.clear();
	mHatchNameMap.clear();
	mDisplayHatchNameMap.clear();
	mOpacityNameMap.clear();
	mDisplayOpacityNameMap.clear();
}

void FillManager::write(OdfDocumentHandler *pHandler) const
{
	for (const auto &bitmapStyle : mBitmapStyles)
		bitmapStyle->write(pHandler);
	for (const auto &gradientStyle : mGradientStyles)
		gradientStyle->write(pHandler);
	for (const auto &hatchStyle : mHatchStyles)
		hatchStyle->write(pHandler);
	for (const auto &opacityStyle : mOpacityStyles)
		opacityStyle->write(pHandler);
}

librevenge::RVNGString FillManager::getStyleNameForBitmap(librevenge::RVNGString const &bitmap)
{
	if (bitmap.empty())
		return "";
	if (mBitmapNameMap.find(bitmap) != mBitmapNameMap.end())
		return mBitmapNameMap.find(bitmap)->second;

	librevenge::RVNGString name;
	name.sprintf("Bitmap_%i", (int) mBitmapNameMap.size());
	mBitmapNameMap[bitmap]=name;

	auto openElement = std::make_shared<TagOpenElement>("draw:fill-image");
	openElement->addAttribute("draw:name", name);
	mBitmapStyles.push_back(openElement);
	mBitmapStyles.push_back(std::make_shared<TagOpenElement>("office:binary-data"));
	mBitmapStyles.push_back(std::make_shared<CharDataElement>(bitmap));
	mBitmapStyles.push_back(std::make_shared<TagCloseElement>("office:binary-data"));
	mBitmapStyles.push_back(std::make_shared<TagCloseElement>("draw:fill-image"));
	return name;
}

librevenge::RVNGString FillManager::getStyleNameForGradient(librevenge::RVNGPropertyList const &style,
                                                            bool &needCreateOpacityStyle)
{
	needCreateOpacityStyle=false;

	bool isStyle=style["style:display-name"]!=nullptr;
	bool hasParent=style["librevenge:parent-display-name"]!=nullptr;
	bool checkEmpty=isStyle || hasParent;
	librevenge::RVNGPropertyList pList;
	if (!checkEmpty)
	{
		// default value
		pList.insert("draw:style", "linear");
		pList.insert("draw:border", "0%");
		pList.insert("draw:start-intensity", "100%");
		pList.insert("draw:end-intensity", "100%");
	}
	// property rename
	if (style["svg:cx"])
		pList.insert("draw:cx", style["svg:cx"]->getStr());
	if (style["svg:cy"])
		pList.insert("draw:cy", style["svg:cy"]->getStr());
	// prepare angle: ODG angle unit is 0.1 degree
	librevenge::RVNGString angleValue;
	if (!checkEmpty || style["draw:angle"])
	{
		double angle = style["draw:angle"] ? style["draw:angle"]->getDouble() : 0.0;
		while (angle < 0)
			angle += 360;
		while (angle > 360)
			angle -= 360;
		angleValue.sprintf("%i", (unsigned)(angle*10));
		pList.insert("draw:angle", angleValue);
	}
	// gradient vector
	const librevenge::RVNGPropertyListVector *gradient = style.child("svg:linearGradient");
	if (!gradient)
		gradient = style.child("svg:radialGradient");
	if (gradient) pList.insert("svg:linearGradient", *gradient);
	char const *wh[] =
	{
		"draw:border", "draw:cx", "draw:cy", "draw:end-color", "draw:end-intensity",
		"draw:start-color", "draw:start-intensity", "draw:style"
	};
	for (auto &i : wh)
	{
		if (style[i])
			pList.insert(i, style[i]->getStr());
	}
	if (pList.empty())
	{
		if (isStyle && hasParent)
		{
			librevenge::RVNGString pName=style["librevenge:parent-display-name"]->getStr();
			if (mDisplayGradientNameMap.find(pName)!=mDisplayGradientNameMap.end())
				mDisplayGradientNameMap[style["style:display-name"]->getStr()]=mDisplayGradientNameMap.find(pName)->second;
		}
		return "";
	}
	librevenge::RVNGString hashKey = pList.getPropString();
	if (mGradientNameMap.find(hashKey) != mGradientNameMap.end())
		return mGradientNameMap.find(hashKey)->second;

	librevenge::RVNGString name;
	name.sprintf("Gradient_%i", (int) mGradientNameMap.size());
	mGradientNameMap[hashKey]=name;
	if (isStyle) mDisplayGradientNameMap[style["style:display-name"]->getStr()]=name;

	std::shared_ptr<TagOpenElement> openElement(std::make_shared<TagOpenElement>("draw:gradient"));
	openElement->addAttribute("draw:name", name);
	if (hasParent)
	{
		librevenge::RVNGString pName=style["librevenge:parent-display-name"]->getStr();
		if (mDisplayGradientNameMap.find(pName)!=mDisplayGradientNameMap.end())
			openElement->addAttribute("style:parent-style-name", mDisplayGradientNameMap.find(pName)->second);
	}
	if (pList["draw:style"])
		openElement->addAttribute("draw:style", pList["draw:style"]->getStr());
	if (!angleValue.empty())
		openElement->addAttribute("draw:angle", angleValue);
	if (pList["draw:cx"])
		openElement->addAttribute("draw:cx", pList["draw:cx"]->getStr());
	if (pList["draw:cy"])
		openElement->addAttribute("draw:cy", pList["draw:cy"]->getStr());

	if (!gradient || !gradient->count())
	{
		char const *attrib[] =
		{
			"draw:start-color", "draw:end-color", "draw:border", "draw:start-intensity", "draw:end-intensity"
		};
		for (auto &i : attrib)
		{
			if (pList[i])
				openElement->addAttribute(i, pList[i]->getStr());
		}

		// Work around a mess in LibreOffice where both opacities of 100% are interpreted as complete transparency
		// Nevertheless, when one is different, immediately, they are interpreted correctly
		if (style["librevenge:start-opacity"] && style["librevenge:end-opacity"]
		        && (style["librevenge:start-opacity"]->getDouble() < 1.0 || style["librevenge:end-opacity"]->getDouble() < 1.0))
			needCreateOpacityStyle=true;
	}
	else if (gradient->count() >= 2)
	{
		if ((*gradient)[1]["svg:stop-color"])
			openElement->addAttribute("draw:start-color", (*gradient)[1]["svg:stop-color"]->getStr());
		if ((*gradient)[0]["svg:stop-color"])
			openElement->addAttribute("draw:end-color", (*gradient)[0]["svg:stop-color"]->getStr());
		if ((*gradient)[0]["svg:stop-opacity"] || (*gradient)[1]["svg:stop-opacity"])
			needCreateOpacityStyle=true;
		openElement->addAttribute("draw:border", "0%");
	}
	else
	{
		return "";
	}

	mGradientStyles.push_back(openElement);
	mGradientStyles.push_back(std::make_shared<TagCloseElement>("draw:gradient"));
	return name;
}

librevenge::RVNGString FillManager::getStyleNameForHatch(librevenge::RVNGPropertyList const &style)
{
	librevenge::RVNGPropertyList pList;
	bool isStyle=style["style:display-name"]!=nullptr;
	bool hasParent=style["librevenge:parent-display-name"]!=nullptr;
	// basic data
	char const *wh[] = { "draw:color", "draw:distance", "draw:rotation", "draw:style" };
	for (auto &i : wh)
	{
		if (style[i])
			pList.insert(i, style[i]->getStr());
	}
	if (pList.empty() && (isStyle || hasParent))
	{
		if (isStyle && hasParent)
		{
			librevenge::RVNGString pName=style["librevenge:parent-display-name"]->getStr();
			if (mDisplayHatchNameMap.find(pName)!=mDisplayHatchNameMap.end())
				mDisplayHatchNameMap[style["style:display-name"]->getStr()]=mDisplayHatchNameMap.find(pName)->second;
		}
		return "";
	}
	librevenge::RVNGString hashKey = pList.getPropString();
	if (mHatchNameMap.find(hashKey) != mHatchNameMap.end())
		return mHatchNameMap.find(hashKey)->second;

	librevenge::RVNGString name;
	name.sprintf("Hatch_%i", (int) mHatchNameMap.size());
	mHatchNameMap[hashKey]=name;
	if (isStyle) mDisplayHatchNameMap[style["style:display-name"]->getStr()]=name;

	auto openElement = std::make_shared<TagOpenElement>("draw:hatch");
	openElement->addAttribute("draw:name", name);
	if (hasParent)
	{
		librevenge::RVNGString pName=style["librevenge:parent-display-name"]->getStr();
		if (mDisplayHatchNameMap.find(pName)!=mDisplayHatchNameMap.end())
			openElement->addAttribute("style:parent-style-name", mDisplayHatchNameMap.find(pName)->second);
	}
	if (style["draw:color"])
		openElement->addAttribute("draw:color", style["draw:color"]->getStr());
	if (style["draw:distance"])
		openElement->addAttribute("draw:distance", style["draw:distance"]->getStr());
	if (style["draw:style"])
		openElement->addAttribute("draw:style", style["draw:style"]->getStr());
	// prepare angle: ODG angle unit is 0.1 degree
	double rotation = style["draw:rotation"] ? style["draw:rotation"]->getDouble() : 0.0;
	while (rotation < 0)
		rotation += 360;
	while (rotation > 360)
		rotation -= 360;
	librevenge::RVNGString sValue;
	sValue.sprintf("%i", (unsigned)(rotation*10));
	openElement->addAttribute("draw:rotation", sValue);

	mHatchStyles.push_back(openElement);
	mHatchStyles.push_back(std::make_shared<TagCloseElement>("draw:hatch"));
	return name;
}

librevenge::RVNGString FillManager::getStyleNameForOpacity(librevenge::RVNGPropertyList const &style)
{
	bool isStyle=style["style:display-name"]!=nullptr;
	bool hasParent=style["librevenge:parent-display-name"]!=nullptr;
	bool checkEmpty=isStyle || hasParent;

	librevenge::RVNGPropertyList pList;
	// default value
	if (!checkEmpty)
	{
		pList.insert("draw:border", "0%");
		pList.insert("draw:start", "100%");
		pList.insert("draw:end", "100%");
	}
	// property rename
	if (style["svg:cx"])
		pList.insert("draw:cx", style["svg:cx"]->getStr());
	if (style["svg:cy"])
		pList.insert("draw:cy", style["svg:cy"]->getStr());
	if (style["draw:start-intensity"])
		pList.insert("draw:start", style["draw:start-intensity"]->getStr());
	if (style["draw:end-intensity"])
		pList.insert("draw:end", style["draw:end-intensity"]->getStr());
	// data in gradient vector
	const librevenge::RVNGPropertyListVector *gradient = style.child("svg:linearGradient");
	if (!gradient)
		gradient = style.child("svg:radialGradient");
	if (gradient && gradient->count() >= 2)
	{
		if ((*gradient)[1]["svg:stop-opacity"])
			pList.insert("draw:start", (*gradient)[1]["svg:stop-opacity"]->getStr());
		if ((*gradient)[0]["svg:stop-opacity"])
			pList.insert("draw:end", (*gradient)[0]["svg:stop-opacity"]->getStr());
	}
	// prepare angle: ODG angle unit is 0.1 degree
	librevenge::RVNGString angleValue;
	if (!checkEmpty || style["draw:angle"])
	{
		double angle = style["draw:angle"] ? style["draw:angle"]->getDouble() : 0.0;
		while (angle < 0)
			angle += 360;
		while (angle > 360)
			angle -= 360;
		angleValue.sprintf("%i", (unsigned)(angle*10));
		pList.insert("draw:angle", angleValue);
	}
	// basic data
	char const *wh[] = { "draw:border", "draw:cx", "draw:cy"	};
	for (auto &i : wh)
	{
		if (style[i])
			pList.insert(i, style[i]->getStr());
	}
	if (pList.empty())
	{
		if (isStyle && hasParent)
		{
			librevenge::RVNGString pName=style["librevenge:parent-display-name"]->getStr();
			if (mDisplayOpacityNameMap.find(pName)!=mDisplayOpacityNameMap.end())
				mDisplayOpacityNameMap[style["style:display-name"]->getStr()]=mDisplayOpacityNameMap.find(pName)->second;
		}
		return "";
	}
	librevenge::RVNGString hashKey = pList.getPropString();
	if (mOpacityNameMap.find(hashKey) != mOpacityNameMap.end())
		return mOpacityNameMap.find(hashKey)->second;

	librevenge::RVNGString name;
	name.sprintf("Transparency_%i", (int) mOpacityNameMap.size());
	mOpacityNameMap[hashKey]=name;
	if (isStyle) mDisplayOpacityNameMap[style["style:display-name"]->getStr()]=name;

	auto openElement = std::make_shared<TagOpenElement>("draw:opacity");
	openElement->addAttribute("draw:name", name);
	if (hasParent)
	{
		librevenge::RVNGString pName=style["librevenge:parent-display-name"]->getStr();
		if (mDisplayOpacityNameMap.find(pName)!=mDisplayOpacityNameMap.end())
			openElement->addAttribute("style:parent-style-name", mDisplayOpacityNameMap.find(pName)->second);
	}
	if (!angleValue.empty())
		openElement->addAttribute("draw:angle", angleValue);
	if (pList["draw:border"])
		openElement->addAttribute("draw:border", pList["draw:border"]->getStr());
	if (pList["draw:cx"])
		openElement->addAttribute("draw:cx", pList["draw:cx"]->getStr());
	if (pList["draw:cy"])
		openElement->addAttribute("draw:cy", pList["draw:cy"]->getStr());
	if (pList["draw:start"])
		openElement->addAttribute("draw:start", pList["draw:start"]->getStr());
	if (pList["draw:end"])
		openElement->addAttribute("draw:end", pList["draw:end"]->getStr());

	mOpacityStyles.push_back(openElement);
	mOpacityStyles.push_back(std::make_shared<TagCloseElement>("draw:opacity"));
	return name;
}

void FillManager::addProperties(librevenge::RVNGPropertyList const &style, librevenge::RVNGPropertyList &element)
{
	bool sendAll=false;
	if (style["style:display-name"])
		sendAll=true;
	else if (!style["draw:fill"])
	{
		if (!style["librevenge:parent-display-name"])
			return;
		else
			sendAll=true;
	}
	const librevenge::RVNGString &fill = style["draw:fill"] ?  style["draw:fill"]->getStr() : "";
	if (fill == "none")
		element.insert("draw:fill", "none");
	if (sendAll || (fill == "bitmap" && style["draw:fill-image"] && style["librevenge:mime-type"]))
	{
		librevenge::RVNGString name=style["draw:fill-image"] ? getStyleNameForBitmap(style["draw:fill-image"]->getStr()) : "";
		if (sendAll || !name.empty())
		{
			if (fill=="bitmap")
				element.insert("draw:fill", "bitmap");
			if (!name.empty())
				element.insert("draw:fill-image-name", name);
			if (style["draw:fill-image-width"])
				element.insert("draw:fill-image-width", style["draw:fill-image-width"]->getStr());
			else if (style["svg:width"])
				element.insert("draw:fill-image-width", style["svg:width"]->getStr());
			if (style["draw:fill-image-height"])
				element.insert("draw:fill-image-height", style["draw:fill-image-height"]->getStr());
			else if (style["svg:height"])
				element.insert("draw:fill-image-height", style["svg:height"]->getStr());
			if (style["style:repeat"])
				element.insert("style:repeat", style["style:repeat"]->getStr());
			if (style["draw:fill-image-ref-point"])
				element.insert("draw:fill-image-ref-point", style["draw:fill-image-ref-point"]->getStr());
			if (style["draw:fill-image-ref-point-x"])
				element.insert("draw:fill-image-ref-point-x", style["draw:fill-image-ref-point-x"]->getStr());
			if (style["draw:fill-image-ref-point-y"])
				element.insert("draw:fill-image-ref-point-y", style["draw:fill-image-ref-point-y"]->getStr());
			if (style["draw:opacity"])
				element.insert("draw:opacity", style["draw:opacity"]->getStr());
		}
		else
			element.insert("draw:fill", "none");
	}
	if (sendAll || fill == "gradient")
	{
		librevenge::RVNGString gradientName(""), opacityName("");
		bool bUseOpacityGradient = false;
		gradientName=getStyleNameForGradient(style, bUseOpacityGradient);
		if (!gradientName.empty())
		{
			if (fill=="gradient")
				element.insert("draw:fill", "gradient");
			element.insert("draw:fill-gradient-name", gradientName);
			if (bUseOpacityGradient)
			{
				opacityName=getStyleNameForOpacity(style);
				if (!opacityName.empty())
					element.insert("draw:opacity-name", opacityName);
			}
		}
		else if (!sendAll)
		{
			element.insert("draw:fill", "solid");
			// try to use the gradient to define the color
			const librevenge::RVNGPropertyListVector *gradient = style.child("svg:linearGradient");
			if (!gradient)
				gradient = style.child("svg:radialGradient");
			if (gradient && gradient->count() >= 1 && (*gradient)[0]["svg:stop-color"])
				element.insert("draw:fill-color", (*gradient)[0]["svg:stop-color"]->getStr());
		}
	}
	if (sendAll || fill == "hatch")
	{
		const librevenge::RVNGString hatchName(getStyleNameForHatch(style));
		if (sendAll || !hatchName.empty())
		{
			if (fill=="hatch")
				element.insert("draw:fill", "hatch");
			if (!hatchName.empty())
				element.insert("draw:fill-hatch-name", hatchName);
			if (style["draw:fill-color"])
				element.insert("draw:fill-color", style["draw:fill-color"]->getStr());
			if (style["draw:opacity"])
				element.insert("draw:opacity", style["draw:opacity"]->getStr());
			if (style["draw:fill-hatch-solid"])
				element.insert("draw:fill-hatch-solid", style["draw:fill-hatch-solid"]->getStr());
		}
		else
		{
			element.insert("draw:fill", "none");
		}
	}
	if (sendAll || fill == "solid")
	{
		if (fill=="solid")
			element.insert("draw:fill", "solid");
		if (style["draw:fill-color"])
			element.insert("draw:fill-color", style["draw:fill-color"]->getStr());
		if (style["draw:opacity"])
			element.insert("draw:opacity", style["draw:opacity"]->getStr());
	}
}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
