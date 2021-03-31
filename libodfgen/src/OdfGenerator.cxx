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

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "OdfGenerator.hxx"

#include <math.h>

#include <cctype>
#include <limits>
#include <memory>
#include <string>
#include <stack>

#include <librevenge/librevenge.h>

#include <libxml/parser.h>

#include "DocumentElement.hxx"
#include "GraphicFunctions.hxx"
#include "InternalHandler.hxx"
#include "ListStyle.hxx"
#include "TableStyle.hxx"

using namespace libodfgen;

namespace
{

static void appendUnicodeTo(unsigned long val, librevenge::RVNGString &buffer)
{
	uint8_t first;
	int len;
	if (val < 0x80)
	{
		first = 0;
		len = 1;
	}
	else if (val < 0x800)
	{
		first = 0xc0;
		len = 2;
	}
	else if (val < 0x10000)
	{
		first = 0xe0;
		len = 3;
	}
	else if (val < 0x200000)
	{
		first = 0xf0;
		len = 4;
	}
	else if (val < 0x4000000)
	{
		first = 0xf8;
		len = 5;
	}
	else
		throw "unicode value is too big";

	char outbuf[7];
	int i;
	for (i = len - 1; i > 0; --i)
	{
		outbuf[i] = char((val & 0x3f) | 0x80);
		val >>= 6;
	}
	outbuf[0] = char(val | first);
	outbuf[len] = 0;
	buffer.append(outbuf);
}

struct XMLException {};

const char *xmlCast(const xmlChar *const str)
{
	return reinterpret_cast<const char *>(str);
}

static void addAttributes(xmlAttributePtr attr, std::shared_ptr<TagOpenElement> &element)
{
	for (; attr; attr = xmlAttributePtr(attr->next))
	{
		std::string value;

		for (xmlNodePtr node = attr->children; node; node = node->next)
			if (node->type == XML_TEXT_NODE)
				value += xmlCast(node->content);
		element->addAttribute(xmlCast(attr->name), value.c_str());
	}
}

static void appendNameSpace(xmlNsPtr nSpace, std::shared_ptr<TagOpenElement> &element)
{
	if (nSpace->type==XML_NAMESPACE_DECL && nSpace->href)
	{
		std::string tag("xmlns");
		if (nSpace->prefix) tag+=std::string(":")+xmlCast(nSpace->prefix);
		std::string value(xmlCast(nSpace->href));
		element->addAttribute(tag.c_str(), value.c_str());
		// FIXME: look also next to check if there is other namespace
	}
}

static void appendElements(xmlNodePtr node, DocumentElementVector &out, bool rootNode=false)
{
	for (; node; node = node->next)
	{
		switch (node->type)
		{
		case XML_ELEMENT_NODE:
		{
			auto element = xmlElementPtr(node);
			auto tag = std::make_shared<TagOpenElement>(xmlCast(element->name));
			out.push_back(tag);
			if (rootNode && node->nsDef) appendNameSpace(node->nsDef, tag);
			addAttributes(element->attributes, tag);
			appendElements(element->children, out);
			out.push_back(std::make_shared<TagCloseElement>(xmlCast(element->name)));
			break;
		}
		case XML_TEXT_NODE:
			out.push_back(std::make_shared<CharDataElement>(xmlCast(node->content)));
			break;
		default:
			break;
		}
	}
}

void appendXML(const std::string &data, DocumentElementVector &out)
{
	std::unique_ptr<xmlDoc, void(*)(xmlDocPtr)> doc
	{
		// FIXME: coverity warns that using XML_PARSE_RECOVER is unsafe,
		// but libstaroffice generates &alpha; , so we must first fix libstaroffice before removing XML_PARSE_RECOVER
		xmlReadDoc(reinterpret_cast<const xmlChar *>(data.c_str()), "", nullptr,
		           XML_PARSE_RECOVER | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_NONET | XML_PARSE_NOCDATA | XML_PARSE_NSCLEAN),
		xmlFreeDoc};
	if (!doc)
		throw XMLException();

	appendElements(doc->children, out, true);
}

}

OdfGenerator::OdfGenerator()
	: mpCurrentStorage()
	, mStorageStack()
	, mMetaDataStorage()
	, mpBodyStorage(new libodfgen::DocumentElementVector())
	, mPageSpanManager()
	, mFontManager()
	, mFillManager()
	, mGraphicManager(mFillManager)
	, mSpanManager()
	, mParagraphManager()
	, mNumberingManager()
	, mListManager()
	, mTableManager()
	, mbInHeaderFooter(false)
	, mbInMasterPage(false)
	, mIdSpanMap()
	, mIdSpanNameMap()
	, mLastSpanName("")
	, mIdParagraphMap()
	, mIdParagraphNameMap()
	, mLastParagraphName("")
	, miFrameNumber(0)
	, mFrameNameIdMap()
	, mLayerNameStack()
	, mLayerNameSet()
	, mLayerNameMap()
	, mGraphicStyle()
	, mIdChartMap()
	, mIdChartNameMap()
	, mDocumentStreamHandlers()
	, miObjectNumber(1)
	, mNameObjectMap()
	, mImageHandlers()
	, mObjectHandlers()
	, mParagraphHeadingStack()
	, mXmlToUnicodeMap()
{
	mpCurrentStorage = mpBodyStorage;
}

OdfGenerator::~OdfGenerator()
{
	mNumberingManager.clean();
	mParagraphManager.clean();
	mSpanManager.clean();
	mFontManager.clean();
	mFillManager.clean();
	mGraphicManager.clean();
	mTableManager.clean();
}

std::string OdfGenerator::getDocumentType(OdfStreamType streamType)
{
	switch (streamType)
	{
	case ODF_FLAT_XML:
		return "office:document";
	case ODF_CONTENT_XML:
		return "office:document-content";
	case ODF_STYLES_XML:
		return "office:document-styles";
	case ODF_SETTINGS_XML:
		return "office:document-settings";
	case ODF_META_XML:
		return "office:document-meta";
	case ODF_MANIFEST_XML:
	default:
		return "office:document";
	}
}

void OdfGenerator::setDocumentMetaData(const librevenge::RVNGPropertyList &propList)
{
	std::string generator;

	librevenge::RVNGPropertyList::Iter i(propList);
	for (i.rewind(); i.next();)
	{
		if (i()->getStr().empty()) continue;
		// filter out librevenge elements
		if (strncmp(i.key(), "librevenge:", 11) && strncmp(i.key(), "dcterms:", 8))
		{
			if (strncmp(i.key(), "meta:generator", 14))
			{
				mMetaDataStorage.push_back(std::make_shared<TagOpenElement>(i.key()));
				mMetaDataStorage.push_back(std::make_shared<CharDataElement>(i()->getStr().cstr()));
				mMetaDataStorage.push_back(std::make_shared<TagCloseElement>(i.key()));
			}
			else
			{
				generator = i()->getStr().cstr();
			}
		}
		else if (strncmp(i.key(), "librevenge:template", 19) == 0)
		{
			librevenge::RVNGString elementName = "meta:template";
			auto element = std::make_shared<TagOpenElement>(elementName);
			element->addAttribute("xlink:type", "simple");
			element->addAttribute("xlink:actuate", "onRequest");
			element->addAttribute("xlink:title", i()->getStr().cstr());
			element->addAttribute("xlink:href", "");
			mMetaDataStorage.push_back(element);
			mMetaDataStorage.push_back(std::make_shared<TagCloseElement>(elementName));
		}
		else if (strncmp(i.key(), "librevenge:", 11) == 0)
		{
			// convert to <meta:user-defined meta:name="some_metadata">
			librevenge::RVNGString elementName = "meta:user-defined";
			auto element = std::make_shared<TagOpenElement>(elementName);
			std::string user_defined(i.key());
			size_t found = user_defined.find_last_of(":");
			if (found != std::string::npos)
				user_defined = user_defined.substr(found+1);
			element->addAttribute("meta:name", user_defined.c_str());
			mMetaDataStorage.push_back(element);
			mMetaDataStorage.push_back(std::make_shared<CharDataElement>(i()->getStr().cstr()));
			mMetaDataStorage.push_back(std::make_shared<TagCloseElement>(elementName));
		}
	}

#ifdef VERSION
	const std::string version(VERSION);
#else
	const std::string version("unknown");
#endif
	if (generator.empty())
	{
		generator = "libodfgen/" + version;
	}
	else
	{
		generator += " (";
		generator += "libodfgen/" + version;
		generator += ")";
	}

	mMetaDataStorage.push_back(std::make_shared<TagOpenElement>("meta:generator"));
	mMetaDataStorage.push_back(std::make_shared<CharDataElement>(generator.c_str()));
	mMetaDataStorage.push_back(std::make_shared<TagCloseElement>("meta:generator"));
}

void OdfGenerator::writeDocumentMetaData(OdfDocumentHandler *pHandler)
{
	if (mMetaDataStorage.empty()) return;
	TagOpenElement("office:meta").write(pHandler);
	sendStorage(&mMetaDataStorage, pHandler);
	pHandler->endElement("office:meta");
}

void OdfGenerator::appendFilesInManifest(OdfDocumentHandler *pHandler)
{
	std::map<OdfStreamType, OdfDocumentHandler *>::const_iterator iter = mDocumentStreamHandlers.begin();
	for (; iter != mDocumentStreamHandlers.end(); ++iter)
	{
		std::string name("");
		switch (iter->first)
		{
		case ODF_CONTENT_XML:
			name="content.xml";
			break;
		case ODF_META_XML:
			name="meta.xml";
			break;
		case ODF_STYLES_XML:
			name="styles.xml";
			break;
		case ODF_SETTINGS_XML:
			name="settings.xml";
			break;
		case ODF_FLAT_XML:
		case ODF_MANIFEST_XML:
		default:
			break;
		}
		if (name.empty())
			continue;

		TagOpenElement file("manifest:file-entry");
		file.addAttribute("manifest:media-type","text/xml");
		file.addAttribute("manifest:full-path", name.c_str());
		file.write(pHandler);
		TagCloseElement("manifest:file-entry").write(pHandler);
	}
	for (auto &oIt : mNameObjectMap)
	{
		if (!oIt.second) continue;

		TagOpenElement file("manifest:file-entry");
		file.addAttribute("manifest:media-type",oIt.second->mType);
		file.addAttribute("manifest:full-path", oIt.first);
		file.write(pHandler);
		TagCloseElement("manifest:file-entry").write(pHandler);
	}

}

void OdfGenerator::initStateWith(OdfGenerator const &orig)
{
	mImageHandlers=orig.mImageHandlers;
	mObjectHandlers=orig.mObjectHandlers;
	mIdSpanMap=orig.mIdSpanMap;
	mIdParagraphMap=orig.mIdParagraphMap;
	mIdChartMap=orig.mIdChartMap;
}

void OdfGenerator::appendBodySettings(const librevenge::RVNGPropertyList &propList)
{
	const librevenge::RVNGPropertyListVector *childs=propList.child("librevenge:childs");
	if (!childs) return;
	for (unsigned long c=0; c< childs->count(); ++c)
	{
		auto const &child=(*childs)[c];
		if (!child["librevenge:type"])
		{
			ODFGEN_DEBUG_MSG(("OdfGenerator::appendBodySettings: find a child without any type\n"));
			continue;
		}
		if (child["librevenge:type"]->getStr()=="table:calculation-settings")
		{
			auto calcSetting=std::make_shared<TagOpenElement>("table:calculation-settings");
			char const *wh[]= { "table:automatic-find-labels", "table:case-sensitive", "table:null-year",
			                    "table:precision-as-shown", "table:search-criteria-must-apply-to-whole-cell",
			                    "table:use-regular-expressions", "table:use-wildcards"
			                  };
			// checkme: had also childs elements: table:iteration, table:null-date
			for (auto &i : wh)
			{
				if (child[i])
					calcSetting->addAttribute(i, child[i]->getStr());
			}
			mpBodyStorage->push_back(calcSetting);
			mpBodyStorage->push_back(std::make_shared<TagCloseElement>("table:calculation-settings"));
		}
		else
		{
			if (!child["librevenge:type"]->getStr().empty())
			{
				ODFGEN_DEBUG_MSG(("OdfGenerator::appendBodySettings: find a child with unknown \"%s\" type\n",
				                  child["librevenge:type"]->getStr().cstr()));
			}
			else
			{
				ODFGEN_DEBUG_MSG(("OdfGenerator::appendBodySettings: find a child with an empty type\n"));
			}
		}
	}

}
////////////////////////////////////////////////////////////
// object
////////////////////////////////////////////////////////////
OdfGenerator::ObjectContainer::~ObjectContainer()
{
}

OdfGenerator::ObjectContainer &OdfGenerator::createObjectFile
(librevenge::RVNGString const &objectName, librevenge::RVNGString const &objectType, bool isDir)
{
	std::unique_ptr<ObjectContainer> res{new ObjectContainer(objectType, isDir)};
	auto ret = mNameObjectMap.insert(std::make_pair(objectName, std::move(res)));
	return *ret.first->second;
}

librevenge::RVNGStringVector OdfGenerator::getObjectNames() const
{
	librevenge::RVNGStringVector res;
	for (const auto &it : mNameObjectMap)
	{
		if (!it.second || it.second->mIsDir) continue;
		res.append(it.first);
	}
	return res;
}

bool OdfGenerator::getObjectContent(librevenge::RVNGString const &objectName, OdfDocumentHandler *pHandler)
{
	if (!pHandler) return false;
	auto it=mNameObjectMap.find(objectName);
	if (it==mNameObjectMap.end() || !it->second)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::getObjectContent: can not find object %s\n", objectName.cstr()));
		return false;
	}
	pHandler->startDocument();
	ObjectContainer &object=*(it->second);
	for (auto &i : object.mStorage)
	{
		if (!i) continue;
		i->write(pHandler);
	}
	pHandler->endDocument();
	return true;
}

////////////////////////////////////////////////////////////
// storage
////////////////////////////////////////////////////////////
void OdfGenerator::sendStorage(libodfgen::DocumentElementVector const *storage, OdfDocumentHandler *pHandler)
{
	if (!storage)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::sendStorage: called without storage\n"));
		return;
	}
	for (const auto &i : *storage)
	{
		if (i)i->write(pHandler);
	}
}

void OdfGenerator::pushStorage(const std::shared_ptr<libodfgen::DocumentElementVector> &newStorage)
{
	if (!newStorage)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::pushStorage: called without storage\n"));
		return;
	}
	mStorageStack.push(mpCurrentStorage);
	mpCurrentStorage=newStorage;
}

bool OdfGenerator::popStorage()
{
	if (mStorageStack.empty())
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::popStorage: the stack is empty\n"));
		return false;
	}
	mpCurrentStorage=mStorageStack.top();
	mStorageStack.pop();
	return false;
}

////////////////////////////////////////////////////////////
// document handler
////////////////////////////////////////////////////////////
void OdfGenerator::addDocumentHandler(OdfDocumentHandler *pHandler, const OdfStreamType streamType)
{
	if (!pHandler)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::addDocumentHandler: called without handler\n"));
		return;
	}
	mDocumentStreamHandlers[streamType] = pHandler;
}

void  OdfGenerator::writeTargetDocuments()
{
	std::map<OdfStreamType, OdfDocumentHandler *>::const_iterator iter = mDocumentStreamHandlers.begin();
	for (; iter != mDocumentStreamHandlers.end(); ++iter)
		writeTargetDocument(iter->second, iter->first);
}

////////////////////////////////////////////////////////////
// embedded
////////////////////////////////////////////////////////////
OdfEmbeddedObject OdfGenerator::findEmbeddedObjectHandler(const librevenge::RVNGString &mimeType) const
{
	auto i = mObjectHandlers.find(mimeType);
	if (i != mObjectHandlers.end())
		return i->second;

	return nullptr;
}

OdfEmbeddedImage OdfGenerator::findEmbeddedImageHandler(const librevenge::RVNGString &mimeType) const
{
	auto i = mImageHandlers.find(mimeType);
	if (i != mImageHandlers.end())
		return i->second;

	return nullptr;
}

void OdfGenerator::registerEmbeddedObjectHandler(const librevenge::RVNGString &mimeType, OdfEmbeddedObject objectHandler)
{
	mObjectHandlers[mimeType]=objectHandler;
}

void OdfGenerator::registerEmbeddedImageHandler(const librevenge::RVNGString &mimeType, OdfEmbeddedImage imageHandler)
{
	mImageHandlers[mimeType]=imageHandler;
}

////////////////////////////////////////////////////////////
// page function
////////////////////////////////////////////////////////////
void OdfGenerator::startHeaderFooter(bool, const librevenge::RVNGPropertyList &)
{
	if (mbInHeaderFooter)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::startHeaderFooter: a master page is already open\n"));
		return;
	}
	mbInHeaderFooter=true;
}

void OdfGenerator::endHeaderFooter()
{
	if (!mbInHeaderFooter)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::endHeaderFooter: can not find any open master page\n"));
		return;
	}
	mbInHeaderFooter=false;
}

void OdfGenerator::startMasterPage(const librevenge::RVNGPropertyList &)
{
	if (mbInMasterPage)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::startMasterPage: a master page is already open\n"));
		return;
	}
	mbInMasterPage=true;
}

void OdfGenerator::endMasterPage()
{
	if (!mbInMasterPage)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::endMasterPage: can not find any open master page\n"));
		return;
	}
	mbInMasterPage=false;
}

////////////////////////////////////////////////////////////
// frame/group
////////////////////////////////////////////////////////////
void OdfGenerator::openFrame(const librevenge::RVNGPropertyList &propList)
{
	// First, let's create a basic Style for this box
	librevenge::RVNGPropertyList style;
	if (propList["style:horizontal-pos"])
		style.insert("style:horizontal-pos", propList["style:horizontal-pos"]->getStr());
	else
		style.insert("style:horizontal-rel", "left");
	if (propList["style:horizontal-rel"])
		style.insert("style:horizontal-rel", propList["style:horizontal-rel"]->getStr());
	else
		style.insert("style:horizontal-rel", "paragraph");
	if (propList["style:vertical-pos"])
		style.insert("style:vertical-pos", propList["style:vertical-pos"]->getStr());
	else
		style.insert("style:vertical-rel", "top");
	if (propList["style:vertical-rel"])
		style.insert("style:vertical-rel", propList["style:vertical-rel"]->getStr());
	else
		style.insert("style:vertical-rel", "page-content");
	librevenge::RVNGString frameStyleName=mGraphicManager.findOrAdd(style, Style::Z_Style);

	librevenge::RVNGPropertyList graphic;
	mGraphicManager.addGraphicProperties(propList, graphic);
	// we do not want to add the default solid stroke if there are some double/... borders
	if (!propList["draw:stroke"])
		graphic.remove("draw:stroke");
	GraphicStyleManager::addFrameProperties(propList, graphic);
	graphic.insert("style:parent-style-name", frameStyleName);
	graphic.insert("draw:ole-draw-aspect", "1");
	librevenge::RVNGString frameAutomaticStyleName=
	    mGraphicManager.findOrAdd(graphic, useStyleAutomaticZone() ? Style::Z_StyleAutomatic : Style::Z_ContentAutomatic);

	// And write the frame itself
	unsigned objectId = 0;
	if (propList["librevenge:frame-name"])
		objectId= getFrameId(propList["librevenge:frame-name"]->getStr());
	else
		objectId= getFrameId("");
	auto drawFrameOpenElement = std::make_shared<TagOpenElement>("draw:frame");
	drawFrameOpenElement->addAttribute("draw:style-name", frameAutomaticStyleName);
	librevenge::RVNGString objectName;
	objectName.sprintf("Object%i", objectId);
	drawFrameOpenElement->addAttribute("draw:name", objectName);
	if (propList["svg:x"])
		drawFrameOpenElement->addAttribute("svg:x", propList["svg:x"]->getStr());
	if (propList["svg:y"])
		drawFrameOpenElement->addAttribute("svg:y", propList["svg:y"]->getStr());
	addFrameProperties(propList, *drawFrameOpenElement);
	mpCurrentStorage->push_back(drawFrameOpenElement);
}

void OdfGenerator::closeFrame()
{
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:frame"));
}

void OdfGenerator::addFrameProperties(const librevenge::RVNGPropertyList &propList, TagOpenElement &element) const
{
	static char const *frameAttrib[] =
	{
		"draw:z-index",
		"fo:max-width", "fo:max-height",
		"style:rel-width", "style:rel-height", // checkme
		"text:anchor-page-number", "text:anchor-type",
		"table:end-cell-address",
		"table:table-background"
	};
	for (auto &i : frameAttrib)
	{
		if (propList[i])
			element.addAttribute(i, propList[i]->getStr());
	}

	if (propList["svg:width"])
		element.addAttribute("svg:width", propList["svg:width"]->getStr());
	else if (propList["fo:min-width"]) // fixme: must be an attribute of draw:text-box
		element.addAttribute("fo:min-width", propList["fo:min-width"]->getStr());
	if (propList["svg:height"])
		element.addAttribute("svg:height", propList["svg:height"]->getStr());
	else if (propList["fo:min-height"]) // fixme: must be an attribute of draw:text-box
		element.addAttribute("fo:min-height", propList["fo:min-height"]->getStr());
	element.addAttribute("draw:layer", getLayerName(propList));
}

unsigned OdfGenerator::getFrameId(librevenge::RVNGString val)
{
	bool hasLabel = val.cstr() && val.len();
	if (hasLabel && mFrameNameIdMap.find(val) != mFrameNameIdMap.end())
		return mFrameNameIdMap.find(val)->second;
	unsigned id=miFrameNumber++;
	if (hasLabel)
		mFrameNameIdMap[val]=id;
	return id;
}

void OdfGenerator::openGroup(const librevenge::RVNGPropertyList &propList)
{
	auto groupElement=std::make_shared<TagOpenElement>("draw:g");
	addFrameProperties(propList, *groupElement);
	mpCurrentStorage->push_back(groupElement);
}

void OdfGenerator::closeGroup()
{
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:g"));
}

librevenge::RVNGString OdfGenerator::getLayerName(const librevenge::RVNGPropertyList &propList) const
{
	// layer does not seems to works in masterpage
	if (inMasterPage())
		return "layout";

	if (propList["draw:layer"] && !propList["draw:layer"]->getStr().empty())
	{
		librevenge::RVNGString layer;
		layer.appendEscapedXML(propList["draw:layer"]->getStr());
		if (mLayerNameMap.find(layer)!=mLayerNameMap.end())
			return mLayerNameMap.find(layer)->second;
		ODFGEN_DEBUG_MSG(("OdfGenerator::getLayerName: called with not existing layer, returns the current layer name\n"));
	}
	if (mLayerNameStack.empty())
		return "layout";
	return mLayerNameStack.top();
}

void OdfGenerator::openLayer(const librevenge::RVNGPropertyList &propList)
{
	if (inMasterPage())
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::openLayer: can not create layer in master page\n"));
		mLayerNameStack.push("layout");
		return;
	}
	librevenge::RVNGString layerName("");
	if (propList["draw:layer"])
		layerName=propList["draw:layer"]->getStr();
	else if (propList["svg:id"])
		layerName=propList["svg:id"]->getStr();
	if (layerName.empty())
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::openLayer: can not find the layer name\n"));
		mLayerNameStack.push("layout");
		return;
	}
	librevenge::RVNGString layer;
	layer.appendEscapedXML(layerName);
	if (mLayerNameSet.find(layer)!=mLayerNameSet.end())
	{
		// try to find a new name
		ODFGEN_DEBUG_MSG(("OdfGenerator::openLayer: called with an existing name, try to find a new name\n"));
		bool ok=false;
		for (int i=0; i<100; ++i)
		{
			librevenge::RVNGString suffix;
			suffix.sprintf("#%d", i);
			librevenge::RVNGString newName(layer);
			newName.append(suffix);
			if (mLayerNameSet.find(newName)!=mLayerNameSet.end())
				continue;
			mLayerNameMap[layer]=newName;
			layer=newName;
			ok=true;
			break;
		}
		if (!ok)
		{
			ODFGEN_DEBUG_MSG(("OdfGenerator::openLayer: can not find a new name, used old\n"));
		}
	}
	else
		mLayerNameMap[layer]=layer;
	mLayerNameSet.insert(layer);
	mLayerNameStack.push(layer);
}

void OdfGenerator::closeLayer()
{
	if (mLayerNameStack.empty())
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::closeLayer: open layer is not called\n"));
		return;
	}
	mLayerNameStack.pop();
}

void OdfGenerator::appendLayersMasterStyles(OdfDocumentHandler *pHandler)
{
	if (mLayerNameSet.empty()) return;

	TagOpenElement("draw:layer-set").write(pHandler);

	TagOpenElement layer("draw:layer");

	// add the default layers
	for (int i=0; i<5; ++i)
	{
		static char const *defaults[] = {"layout", "background", "backgroundobjects", "controls", "measurelines"};
		if (mLayerNameSet.find(defaults[i])!=mLayerNameSet.end())
			continue;
		layer.addAttribute("draw:name", defaults[i]);
		layer.write(pHandler);
		TagCloseElement("draw:layer").write(pHandler);
	}
	for (const auto &layerName : mLayerNameSet)
	{
		layer.addAttribute("draw:name", layerName);
		layer.write(pHandler);
		TagCloseElement("draw:layer").write(pHandler);
	}
	TagCloseElement("draw:layer-set").write(pHandler);
}

////////////////////////////////////////////////////////////
// span/paragraph
////////////////////////////////////////////////////////////
void OdfGenerator::insertTab()
{
	mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("text:tab"));
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("text:tab"));
}

void OdfGenerator::insertSpace()
{
	mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("text:s"));
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("text:s"));
}

void OdfGenerator::insertLineBreak(bool forceParaClose)
{
	if (!forceParaClose)
	{
		mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("text:line-break"));
		mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("text:line-break"));
		return;
	}
	closeSpan();
	closeParagraph();

	auto pParagraphOpenElement = std::make_shared<TagOpenElement>("text:p");
	if (!mLastParagraphName.empty())
		pParagraphOpenElement->addAttribute("text:style-name", mLastParagraphName.cstr());
	mpCurrentStorage->push_back(pParagraphOpenElement);
	mParagraphHeadingStack.push(false);

	auto pSpanOpenElement = std::make_shared<TagOpenElement>("text:span");
	if (!mLastSpanName.empty())
		pSpanOpenElement->addAttribute("text:style-name", mLastSpanName.cstr());
	mpCurrentStorage->push_back(pSpanOpenElement);

}

void OdfGenerator::insertField(const librevenge::RVNGPropertyList &propList)
{
	if (!propList["librevenge:field-type"] || propList["librevenge:field-type"]->getStr().empty())
		return;

	const librevenge::RVNGString &type = propList["librevenge:field-type"]->getStr();

	auto openElement = std::make_shared<TagOpenElement>(type);
	if (type == "text:page-number")
		openElement->addAttribute("text:select-page", propList["text:select-page"] ? propList["text:select-page"]->getStr() : "current");
	else if (type == "text:chapter")
	{
		for (int i=0; i<2; ++i)
		{
			char const *wh[]= {"text:display", "text:outline-level"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], propList[wh[i]]->getStr());
		}
	}
	else if (type == "text:conditional-text")
	{
		for (int i=0; i<4; ++i)
		{
			char const *wh[]= {"text:condition", "text:current-value", "text:string-value-if-false", "text:string-value-if-true"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:date" || type == "text:time")
	{
		// TODO: create a library function to avoid dupplicated code with OdsGenerator::openSheetCell
		if (type == "text:date" && propList["librevenge:day"] && propList["librevenge:month"] && propList["librevenge:year"])
		{
			librevenge::RVNGString date;
			if (propList["librevenge:hours"])
			{
				int minute=propList["librevenge:minutes"] ? propList["librevenge:minutes"]->getInt() : 0;
				int second=propList["librevenge:seconds"] ? propList["librevenge:seconds"]->getInt() : 0;
				date.sprintf("%04d-%02d-%02dT%02d:%02d:%02d", propList["librevenge:year"]->getInt(),
				             propList["librevenge:month"]->getInt(),  propList["librevenge:day"]->getInt(),
				             propList["librevenge:hours"]->getInt(), minute, second);
			}
			else
				date.sprintf("%04d-%02d-%02d", propList["librevenge:year"]->getInt(),
				             propList["librevenge:month"]->getInt(),  propList["librevenge:day"]->getInt());
			openElement->addAttribute("text:date-value", date);
		}
		else if (type == "text:time" && propList["librevenge:hours"])
		{
			int minute=propList["librevenge:minutes"] ? propList["librevenge:minutes"]->getInt() : 0;
			int second=propList["librevenge:seconds"] ? propList["librevenge:seconds"]->getInt() : 0;
			librevenge::RVNGString time;
			time.sprintf("PT%02dH%02dM%02dS", propList["librevenge:hours"]->getInt(), minute, second);
			openElement->addAttribute("office:time-value", time);
		}

		if (propList["librevenge:value-type"])
		{
			librevenge::RVNGString numberingName=mNumberingManager.findOrAdd(propList);
			if (!numberingName.empty())
				openElement->addAttribute("style:data-style-name", numberingName.cstr());
		}
		if (propList["text:fixed"])
			openElement->addAttribute("text:fixed", propList["text:fixed"]->getStr());
	}
	else if (type == "text:file-name" || type=="text:template-name")
	{
		if (propList["text:display"])
			openElement->addAttribute("text:display", propList["text:display"]->getStr());
	}
	else if (type == "text:hidden-paragraph")
	{
		for (int i=0; i<2; ++i)
		{
			char const *wh[]= {"text:condition", "text:is-hidden"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:placeholder")
	{
		for (int i=0; i<2; ++i)
		{
			char const *wh[]= {"text:description", "text:placeholder-type"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:reference-mark" || type == "text:reference-mark-start" || type == "text:reference-mark-end" ||
	         type == "text:bookmark-start" || type == "text:bookmark-end")
	{
		for (int i=0; i<1; ++i)
		{
			char const *wh[]= {"text:name"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:reference-ref")
	{
		for (int i=0; i<2; ++i)
		{
			char const *wh[]= {"text:reference-format", "text:ref-name"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:sequence")
	{
		for (int i=0; i<3; ++i)
		{
			char const *wh[]= {"text:formula", "text:name", "text:ref-name"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:text-input")
	{
		for (int i=0; i<1; ++i)
		{
			char const *wh[]= {"text:description"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:user-defined")
	{
		for (int i=0; i<3; ++i)
		{
			char const *wh[]= {"office:string-value", "office:value", "text:name"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:variable-get")
	{
		for (int i=0; i<2; ++i)
		{
			char const *wh[]= {"text:display", "text:name"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:variable-set" || type == "text:expression")
	{
		for (int i=0; i<5; ++i)
		{
			char const *wh[]= {"text:formula", "text:name", "office:string-value", "office:value", "office:value-type"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	// the database field
	else if (type == "text:database-display")
	{
		for (int i=0; i<4; ++i)
		{
			char const *wh[]= {"text:column-name", "text:database-name", "text:table-name", "text:table-type"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:database-name")
	{
		for (int i=0; i<3; ++i)
		{
			char const *wh[]= {"text:database-name", "text:table-name", "text:table-type"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	else if (type == "text:database-row-select")
	{
		for (int i=0; i<5; ++i)
		{
			char const *wh[]= {"text:condition", "text:database-name", "text:row-number", "text:table-name", "text:table-type"};
			if (propList[wh[i]])
				openElement->addAttribute(wh[i], librevenge::RVNGString::escapeXML(propList[wh[i]]->getStr()));
		}
	}
	if (propList["style:num-format"])
		openElement->addAttribute("style:num-format", propList["style:num-format"]->getStr());

	mpCurrentStorage->push_back(openElement);
	if (propList["librevenge:field-content"])
		mpCurrentStorage->push_back(std::make_shared<CharDataElement>(propList["librevenge:field-content"]->getStr()));
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>(type));
}

void OdfGenerator::insertText(const librevenge::RVNGString &text)
{
	if (!text.empty())
		mpCurrentStorage->push_back(std::make_shared<TextElement>(text));
}

void OdfGenerator::defineCharacterStyle(const librevenge::RVNGPropertyList &propList)
{
	if (!propList["librevenge:span-id"])
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::defineCharacterStyle: called without id\n"));
		return;
	}
	mIdSpanMap[propList["librevenge:span-id"]->getInt()]=propList;
}

void OdfGenerator::openSpan(const librevenge::RVNGPropertyList &propList)
{
	librevenge::RVNGString sName("");
	librevenge::RVNGPropertyList pList(propList);
	if (pList["librevenge:span-id"])
	{
		int id=pList["librevenge:span-id"]->getInt();
		if (mIdSpanNameMap.find(id)!=mIdSpanNameMap.end())
			sName=mIdSpanNameMap.find(id)->second;
		else if (mIdSpanMap.find(id)!=mIdSpanMap.end())
			pList=mIdSpanMap.find(id)->second;
		else
		{
			ODFGEN_DEBUG_MSG(("OdfGenerator::openSpan: can not find the style %d\n", id));
			pList.clear();
		}
	}

	if (sName.empty())
	{
		if (pList["style:font-name"])
			mFontManager.findOrAdd(pList["style:font-name"]->getStr().cstr());
		sName = mSpanManager.findOrAdd(pList, useStyleAutomaticZone() ? Style::Z_StyleAutomatic : Style::Z_Unknown);
		if (pList["librevenge:span-id"])
			mIdSpanNameMap[pList["librevenge:span-id"]->getInt()]=sName;
	}
	auto pSpanOpenElement = std::make_shared<TagOpenElement>("text:span");
	pSpanOpenElement->addAttribute("text:style-name", sName.cstr());
	mpCurrentStorage->push_back(pSpanOpenElement);
	mLastSpanName=sName;
}

void OdfGenerator::closeSpan()
{
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("text:span"));
}

void OdfGenerator::openLink(const librevenge::RVNGPropertyList &propList)
{
	if (!propList["librevenge:type"])
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::openLink: linked type is not defined, assume link\n"));
	}
	auto pLinkOpenElement = std::make_shared<TagOpenElement>("text:a");
	librevenge::RVNGPropertyList::Iter i(propList);
	for (i.rewind(); i.next();)
	{
		if (!i.child()) // write out simple properties only
			// The string we get here might be url decoded, so
			// sscape characters that might mess up the resulting xml
			pLinkOpenElement->addAttribute(i.key(), librevenge::RVNGString::escapeXML(i()->getStr()));
	}
	mpCurrentStorage->push_back(pLinkOpenElement);
}

void OdfGenerator::closeLink()
{
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("text:a"));
}

void OdfGenerator::defineParagraphStyle(const librevenge::RVNGPropertyList &propList)
{
	if (!propList["librevenge:paragraph-id"])
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::defineParagraphStyle: called without id\n"));
		return;
	}
	mIdParagraphMap[propList["librevenge:paragraph-id"]->getInt()]=propList;
}

void OdfGenerator::openParagraph(const librevenge::RVNGPropertyList &propList)
{
	librevenge::RVNGPropertyList pList(propList);
	librevenge::RVNGString paragraphName("");
	bool isMasterPage=(propList["style:master-page-name"]!=nullptr);

	if (propList["text:outline-level"])
		pList.insert("style:default-outline-level", propList["text:outline-level"]->clone());
	if (pList["librevenge:paragraph-id"])
	{
		int id=pList["librevenge:paragraph-id"]->getInt();
		if (mIdParagraphNameMap.find(id)!=mIdParagraphNameMap.end())
			paragraphName=mIdParagraphNameMap.find(id)->second;
		else if (mIdParagraphMap.find(id)!=mIdParagraphMap.end())
			pList=mIdParagraphMap.find(id)->second;
		else
		{
			ODFGEN_DEBUG_MSG(("OdfGenerator::openParagraph: can not find the style %d\n", id));
			pList.clear();
		}
		if (isMasterPage)
			pList.insert("style:master-page-name", propList["style:master-page-name"]->clone());
	}

	if (paragraphName.empty() || isMasterPage)
	{
		if (pList["style:font-name"])
			mFontManager.findOrAdd(pList["style:font-name"]->getStr().cstr());
		paragraphName = mParagraphManager.findOrAdd(pList, useStyleAutomaticZone() ? Style::Z_StyleAutomatic : Style::Z_Unknown);
		if (pList["librevenge:paragraph-id"] && !isMasterPage)
			mIdParagraphNameMap[pList["librevenge:paragraph-id"]->getInt()]=paragraphName;
	}

	// create a document element corresponding to the paragraph, and append it to our list of document elements
	std::shared_ptr<TagOpenElement> pParagraphOpenElement;

	if (propList["text:outline-level"])
	{
		mParagraphHeadingStack.push(true);
		pParagraphOpenElement = std::make_shared<TagOpenElement>("text:h");
		pParagraphOpenElement->addAttribute("text:outline-level", propList["text:outline-level"]->getStr());
	}
	else
	{
		mParagraphHeadingStack.push(false);
		pParagraphOpenElement = std::make_shared<TagOpenElement>("text:p");
	}
	pParagraphOpenElement->addAttribute("text:style-name", paragraphName);
	mpCurrentStorage->push_back(pParagraphOpenElement);
	mLastParagraphName=paragraphName;
}

void OdfGenerator::closeParagraph()
{
	if (mParagraphHeadingStack.empty())
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::closeParagraph: can not find any opened paragraph\n"));
		return;
	}
	mpCurrentStorage->push_back(mParagraphHeadingStack.top() ? std::make_shared<TagCloseElement>("text:h") : std::make_shared<TagCloseElement>("text:p"));
	mParagraphHeadingStack.pop();
}

////////////////////////////////////////////////////////////
// list
////////////////////////////////////////////////////////////
void OdfGenerator::popListState()
{
	mListManager.popState();
}

void OdfGenerator::pushListState()
{
	mListManager.pushState();
}

void OdfGenerator::openListLevel(const librevenge::RVNGPropertyList &propList, bool ordered)
{
	ListManager::State &state=mListManager.getState();
	if (state.mbListElementParagraphOpened)
	{
		closeParagraph();
		state.mbListElementParagraphOpened = false;
	}
	librevenge::RVNGPropertyList pList(propList);
	if (!pList["librevenge:level"])
		pList.insert("librevenge:level", int(state.mbListElementOpened.size())+1);
	if (pList["style:font-name"])
		mFontManager.findOrAdd(pList["style:font-name"]->getStr().cstr());
	mListManager.defineLevel(pList, ordered, useStyleAutomaticZone() ? Style::Z_StyleAutomatic : Style::Z_Unknown);

	auto pListLevelOpenElement = std::make_shared<TagOpenElement>("text:list");
	if (!state.mbListElementOpened.empty() && !state.mbListElementOpened.top())
	{
		mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("text:list-item"));
		state.mbListElementOpened.top() = true;
	}

	state.mbListElementOpened.push(false);
	if (state.mbListElementOpened.size() == 1)
	{
		// add a sanity check ( to avoid a crash if mpCurrentListStyle is NULL)
		if (state.mpCurrentListStyle)
			pListLevelOpenElement->addAttribute("text:style-name", state.mpCurrentListStyle->getName());
	}
	if (ordered && state.mbListContinueNumbering)
		pListLevelOpenElement->addAttribute("text:continue-numbering", "true");
	mpCurrentStorage->push_back(pListLevelOpenElement);
}

void OdfGenerator::closeListLevel()
{
	ListManager::State &state=mListManager.getState();
	if (state.mbListElementOpened.empty())
	{
		// this implies that openListLevel was not called, so it is better to stop here
		ODFGEN_DEBUG_MSG(("OdfGenerator: Attempting to close an unexisting level\n"));
		return;
	}
	if (state.mbListElementOpened.top())
	{
		mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("text:list-item"));
		state.mbListElementOpened.top() = false;
	}

	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("text:list"));
	state.mbListElementOpened.pop();
}

void OdfGenerator::openListElement(const librevenge::RVNGPropertyList &propList)
{
	ListManager::State &state=mListManager.getState();
	state.miLastListLevel = state.miCurrentListLevel;
	if (state.miCurrentListLevel == 1)
		state.miLastListNumber++;

	if (state.mbListElementOpened.top())
	{
		mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("text:list-item"));
		state.mbListElementOpened.top() = false;
	}

	librevenge::RVNGPropertyList finalPropList(propList);
#if 0
	// this property is ignored in TextRunStyle.c++
	if (state.mpCurrentListStyle)
		finalPropList.insert("style:list-style-name", state.mpCurrentListStyle->getName());
#endif
	finalPropList.insert("style:parent-style-name", "Standard");
	librevenge::RVNGString paragName =mParagraphManager.findOrAdd(finalPropList, useStyleAutomaticZone() ? Style::Z_StyleAutomatic : Style::Z_Unknown);

	auto pOpenListItem = std::make_shared<TagOpenElement>("text:list-item");
	if (propList["text:start-value"] && propList["text:start-value"]->getInt() > 0)
		pOpenListItem->addAttribute("text:start-value", propList["text:start-value"]->getStr());
	mpCurrentStorage->push_back(pOpenListItem);

	auto pOpenListElementParagraph = std::make_shared<TagOpenElement>("text:p");
	pOpenListElementParagraph->addAttribute("text:style-name", paragName);
	if (propList["style:master-page-name"])
		pOpenListElementParagraph->addAttribute("style:master-page-name",propList["style:master-page-name"]->getStr());
	mpCurrentStorage->push_back(pOpenListElementParagraph);
	mParagraphHeadingStack.push(false);

	state.mbListElementOpened.top() = true;
	state.mbListElementParagraphOpened = true;
	state.mbListContinueNumbering = false;
}

void OdfGenerator::closeListElement()
{
	// this code is kind of tricky, because we don't actually close the list element (because this list element
	// could contain another list level in OOo's implementation of lists). that is done in the closeListLevel
	// code (or when we open another list element)
	if (mListManager.getState().mbListElementParagraphOpened)
	{
		closeParagraph();
		mListManager.getState().mbListElementParagraphOpened = false;
	}
}


////////////////////////////////////////////////////////////
// table
////////////////////////////////////////////////////////////
void OdfGenerator::openTable(const librevenge::RVNGPropertyList &propList)
{
	mTableManager.openTable(propList, useStyleAutomaticZone() ? Style::Z_StyleAutomatic : Style::Z_ContentAutomatic);

	Table *table=mTableManager.getActualTable();
	if (!table)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::openTable: can not retrieve the table data\n"));
		return;
	}
	librevenge::RVNGString tableName=table->getName();

	auto pTableOpenElement = std::make_shared<TagOpenElement>("table:table");
	pTableOpenElement->addAttribute("table:name", tableName.cstr());
	pTableOpenElement->addAttribute("table:style-name", tableName.cstr());
	mpCurrentStorage->push_back(pTableOpenElement);

	for (int i=0; i<table->getNumColumns(); ++i)
	{
		auto pTableColumnOpenElement = std::make_shared<TagOpenElement>("table:table-column");
		librevenge::RVNGString sColumnStyleName;
		sColumnStyleName.sprintf("%s.Column%i", tableName.cstr(), (i+1));
		pTableColumnOpenElement->addAttribute("table:style-name", sColumnStyleName.cstr());
		mpCurrentStorage->push_back(pTableColumnOpenElement);

		auto pTableColumnCloseElement = std::make_shared<TagCloseElement>("table:table-column");
		mpCurrentStorage->push_back(pTableColumnCloseElement);
	}
}

void OdfGenerator::closeTable()
{
	if (!mTableManager.getActualTable())
		return;
	mTableManager.closeTable();
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("table:table"));
}

bool OdfGenerator::openTableRow(const librevenge::RVNGPropertyList &propList, bool compatibleOdp)
{
	Table *table=mTableManager.getActualTable();
	if (!table)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::openTableRow called with no table\n"));
		return false;
	}
	librevenge::RVNGString rowName=table->openRow(propList, compatibleOdp);
	if (rowName.empty())
		return false;
	bool inHeader=false;
	if (table->isRowOpened(inHeader) && inHeader)
		mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("table:table-header-rows"));

	auto pTableRowOpenElement = std::make_shared<TagOpenElement>("table:table-row");
	pTableRowOpenElement->addAttribute("table:style-name", rowName);
	mpCurrentStorage->push_back(pTableRowOpenElement);
	return true;
}

void OdfGenerator::closeTableRow()
{
	Table *table=mTableManager.getActualTable();
	if (!table) return;
	bool inHeader=false;
	if (!table->isRowOpened(inHeader) || !table->closeRow()) return;
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("table:table-row"));
	if (inHeader)
		mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("table:table-header-rows"));
}

bool OdfGenerator::isInTableRow(bool &inHeaderRow) const
{
	Table const *table=mTableManager.getActualTable();
	if (!table) return false;
	return table->isRowOpened(inHeaderRow);
}

bool OdfGenerator::openTableCell(const librevenge::RVNGPropertyList &propList)
{
	Table *table=mTableManager.getActualTable();
	if (!table)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::openTableCell called with no table\n"));
		return false;
	}

	librevenge::RVNGString cellName = table->openCell(propList);
	if (cellName.empty())
		return false;

	auto pTableCellOpenElement = std::make_shared<TagOpenElement>("table:table-cell");
	pTableCellOpenElement->addAttribute("table:style-name", cellName);
	if (propList["table:number-columns-spanned"])
		pTableCellOpenElement->addAttribute("table:number-columns-spanned",
		                                    propList["table:number-columns-spanned"]->getStr().cstr());
	if (propList["table:number-rows-spanned"])
		pTableCellOpenElement->addAttribute("table:number-rows-spanned",
		                                    propList["table:number-rows-spanned"]->getStr().cstr());
	// pTableCellOpenElement->addAttribute("table:value-type", "string");
	mpCurrentStorage->push_back(pTableCellOpenElement);
	return true;
}

void OdfGenerator::closeTableCell()
{
	if (!mTableManager.getActualTable() || !mTableManager.getActualTable()->closeCell())
		return;

	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("table:table-cell"));
}

void OdfGenerator::insertCoveredTableCell(const librevenge::RVNGPropertyList &propList)
{
	if (!mTableManager.getActualTable() ||
	        !mTableManager.getActualTable()->insertCoveredCell(propList))
		return;

	mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("table:covered-table-cell"));
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("table:covered-table-cell"));
}

////////////////////////////////////////////////////////////
// image/embedded
////////////////////////////////////////////////////////////
void OdfGenerator::insertEquation(const librevenge::RVNGPropertyList &propList)
{
	if ((!propList["librevenge:data"] && !propList["office:binary-data"]) || !propList["librevenge:mime-type"])
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::insertEquation: imcomplete property list\n"));
		return;
	}
	if (propList["librevenge:mime-type"]->getStr()!="application/mathml-presentation+xml" &&
	        propList["librevenge:mime-type"]->getStr()!="application/mathml+xml")
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::insertEquation: unexpected mime type \n"));
		return;
	}

	std::string data;
	if (propList["librevenge:data"])
		data=propList["librevenge:data"]->getStr().cstr();
	else
	{
		librevenge::RVNGBinaryData binaryData(propList["office:binary-data"]->getStr());
		if (!binaryData.empty())
			data.append((char const *) binaryData.getDataBuffer(), size_t(binaryData.size()));
	}
	if (data.empty())
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::insertEquation: can not find the data\n"));
		return;
	}

	try
	{
		std::vector<std::shared_ptr<DocumentElement>> elementStack;
		elementStack.push_back(std::make_shared<TagOpenElement>("draw:object"));
		appendXML(data, elementStack);
		elementStack.push_back(std::make_shared<TagCloseElement>("draw:object"));
		mpCurrentStorage->insert(mpCurrentStorage->end(), elementStack.begin(), elementStack.end());
	}
	catch (...)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::insertEquation: ARGHH, catch an exception when decoding picture!!!\n"));
	}
}

void OdfGenerator::insertBinaryObject(const librevenge::RVNGPropertyList &propList)
{
	if (!propList["office:binary-data"] || !propList["librevenge:mime-type"])
	{
		// check for xlink
		if (propList["librevenge:xlink"])
		{
			auto openElement = std::make_shared<TagOpenElement>("draw:image");

			openElement->addAttribute("xlink:href", propList["librevenge:xlink"]->getStr());
			openElement->addAttribute("xlink:type", "simple");
			openElement->addAttribute("xlink:show", "embed");

			mpCurrentStorage->push_back(openElement);
			mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:image"));

			librevenge::RVNGPropertyListVector const *replacements=propList.child("librevenge:replacement-objects");
			if (!replacements)
				return;
			for (unsigned long c=0; c < replacements->count(); ++c)
				insertBinaryObject((*replacements)[c]);
			return;
		}
		ODFGEN_DEBUG_MSG(("OdfGenerator::addDocumentHandler: can not find data or mimetype\n"));
		return;
	}
	if (propList["librevenge:mime-type"]->getStr()=="application/mathml-presentation+xml" ||
	        propList["librevenge:mime-type"]->getStr()=="application/mathml+xml")
	{
		insertEquation(propList);
		return;
	}
	OdfEmbeddedObject tmpObjectHandler = findEmbeddedObjectHandler(propList["librevenge:mime-type"]->getStr());
	OdfEmbeddedImage tmpImageHandler = findEmbeddedImageHandler(propList["librevenge:mime-type"]->getStr());

	if (tmpObjectHandler || tmpImageHandler)
	{
		try
		{
			librevenge::RVNGBinaryData data(propList["office:binary-data"]->getStr());
			if (tmpObjectHandler)
			{
				DocumentElementVector tmpContentElements;
				InternalHandler tmpHandler(&tmpContentElements);


				if (tmpObjectHandler(data, &tmpHandler, ODF_FLAT_XML) && !tmpContentElements.empty())
				{
					mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("draw:object"));
					mpCurrentStorage->insert(mpCurrentStorage->end(), tmpContentElements.begin(), tmpContentElements.end());
					mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:object"));
				}
			}
			if (tmpImageHandler)
			{
				librevenge::RVNGBinaryData output;
				if (tmpImageHandler(data, output))
				{
					mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("draw:image"));

					mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("office:binary-data"));
					librevenge::RVNGString binaryBase64Data = output.getBase64Data();

					mpCurrentStorage->push_back(std::make_shared<CharDataElement>(binaryBase64Data.cstr()));

					mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("office:binary-data"));

					mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:image"));
				}
			}
		}
		catch (...)
		{
			ODFGEN_DEBUG_MSG(("OdfGenerator::insertBinaryObject: ARGHH, catch an exception when decoding data!!!\n"));
		}
	}
	else
		// assuming we have a binary image or a object_ole that we can just insert as it is
	{
		if (propList["librevenge:mime-type"]->getStr() == "object/ole")
			mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("draw:object-ole"));
		else
			mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("draw:image"));

		mpCurrentStorage->push_back(std::make_shared<TagOpenElement>("office:binary-data"));
		try
		{
			mpCurrentStorage->push_back(std::make_shared<CharDataElement>(propList["office:binary-data"]->getStr().cstr()));
		}
		catch (...)
		{
			ODFGEN_DEBUG_MSG(("OdfGenerator::insertBinaryObject: ARGHH, catch an exception when decoding picture!!!\n"));
		}
		mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("office:binary-data"));

		if (propList["librevenge:mime-type"]->getStr() == "object/ole")
			mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:object-ole"));
		else
			mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:image"));
	}

	librevenge::RVNGPropertyListVector const *replacements=propList.child("librevenge:replacement-objects");
	if (!replacements)
		return;
	for (unsigned long c=0; c < replacements->count(); ++c)
		insertBinaryObject((*replacements)[c]);
}

////////////////////////////////////////////////////////////
// graphic
////////////////////////////////////////////////////////////
void OdfGenerator::defineGraphicStyle(const librevenge::RVNGPropertyList &propList)
{
	mGraphicStyle=propList;
	if (propList["style:display-name"]) // force the style to be defined
		getCurrentGraphicStyleName();
}

librevenge::RVNGString OdfGenerator::getCurrentGraphicStyleName()
{
	librevenge::RVNGPropertyList styleList;
	mGraphicManager.addGraphicProperties(mGraphicStyle,styleList);
	if (mGraphicStyle["style:display-name"])
		GraphicStyleManager::addFrameProperties(mGraphicStyle,styleList);
	return mGraphicManager.findOrAdd(styleList, useStyleAutomaticZone() ? Style::Z_StyleAutomatic : Style::Z_ContentAutomatic);
}

librevenge::RVNGString OdfGenerator::getCurrentGraphicStyleName(const librevenge::RVNGPropertyList &shapeList)
{
	librevenge::RVNGPropertyList styleList;
	mGraphicManager.addGraphicProperties(shapeList,styleList);
	// check that no default are set, there will can be set with mGraphicStyle, if needed
	for (int i=0; i<3; ++i)
	{
		char const *wh[]= {"draw:fill","draw:shadow","draw:stroke"};
		if (!shapeList[wh[i]] && styleList[wh[i]])
			styleList.remove(wh[i]);
	}
	mGraphicManager.addGraphicProperties(mGraphicStyle,styleList);
	return mGraphicManager.findOrAdd(styleList, useStyleAutomaticZone() ? Style::Z_StyleAutomatic : Style::Z_ContentAutomatic);
}

void OdfGenerator::drawEllipse(const librevenge::RVNGPropertyList &propList)
{
	if (!propList["svg:rx"] || !propList["svg:ry"] || !propList["svg:cx"] || !propList["svg:cy"])
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::drawEllipse: position undefined\n"));
		return;
	}
	double rx=0, ry=0, cx=0, cy=0;
	if (!getInchValue(*propList["svg:rx"], rx) || !getInchValue(*propList["svg:ry"], ry) ||
	        !getInchValue(*propList["svg:cx"], cx) || !getInchValue(*propList["svg:cy"], cy))
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::drawEllipse: can not read position\n"));
		return;
	}
	librevenge::RVNGString sValue=getCurrentGraphicStyleName(propList);
	auto pDrawEllipseElement = std::make_shared<TagOpenElement>("draw:ellipse");
	pDrawEllipseElement->addAttribute("draw:style-name", sValue);
	addFrameProperties(propList, *pDrawEllipseElement);
	sValue = doubleToString(2 * rx);
	sValue.append("in");
	pDrawEllipseElement->addAttribute("svg:width", sValue);
	sValue = doubleToString(2 * ry);
	sValue.append("in");
	pDrawEllipseElement->addAttribute("svg:height", sValue);
	for (int i=0; i<4; ++i)
	{
		char const *wh[]= {"draw:kind", "draw:start-angle", "draw:end-angle", "draw:transform"};
		if (propList[wh[i]])
			pDrawEllipseElement->addAttribute(wh[i], propList[wh[i]]->getStr());
	}
	if (propList["librevenge:rotate"] &&
	        (propList["librevenge:rotate"]->getDouble() < 0 || propList["librevenge:rotate"]->getDouble() > 0))
	{
		double rotation = propList["librevenge:rotate"]->getDouble();
		while (rotation < -180)
			rotation += 360;
		while (rotation > 180)
			rotation -= 360;
		double radrotation = rotation*M_PI/180.0;
		double deltax = sqrt(pow(rx, 2.0) + pow(ry, 2.0))*cos(atan(ry/rx)-radrotation) - rx;
		double deltay = sqrt(pow(rx, 2.0) + pow(ry, 2.0))*sin(atan(ry/rx)- radrotation) - ry;
		sValue = "rotate(";
		sValue.append(doubleToString(radrotation));
		sValue.append(") ");
		sValue.append("translate(");
		sValue.append(doubleToString(cx - rx - deltax));
		sValue.append("in, ");
		sValue.append(doubleToString(cy - ry - deltay));
		sValue.append("in)");
		pDrawEllipseElement->addAttribute("draw:transform", sValue);
	}
	else
	{
		sValue = doubleToString(cx-rx);
		sValue.append("in");
		pDrawEllipseElement->addAttribute("svg:x", sValue);
		sValue = doubleToString(cy-ry);
		sValue.append("in");
		pDrawEllipseElement->addAttribute("svg:y", sValue);
	}

	if (propList["draw:display"])
		pDrawEllipseElement->addAttribute("draw:display", propList["draw:display"]->getStr());

	mpCurrentStorage->push_back(pDrawEllipseElement);
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:ellipse"));
}

void OdfGenerator::drawPath(const librevenge::RVNGPropertyList &propList)
{
	const librevenge::RVNGPropertyListVector *path = propList.child("svg:d");
	if (!path) return;
	drawPath(*path, propList);
}

void OdfGenerator::drawPath(const librevenge::RVNGPropertyListVector &path, const librevenge::RVNGPropertyList &propList)
{
	if (!path.count())
		return;

	double px = 0.0, py = 0.0, qx = 0.0, qy = 0.0;
	if (!libodfgen::getPathBBox(path, px, py, qx, qy))
		return;

	librevenge::RVNGString sValue=getCurrentGraphicStyleName(propList);
	auto pDrawPathElement = std::make_shared<TagOpenElement>("draw:path");
	pDrawPathElement->addAttribute("draw:style-name", sValue);
	addFrameProperties(propList, *pDrawPathElement);
	sValue = doubleToString(px);
	sValue.append("in");
	pDrawPathElement->addAttribute("svg:x", sValue);
	sValue = doubleToString(py);
	sValue.append("in");
	pDrawPathElement->addAttribute("svg:y", sValue);
	sValue = doubleToString((qx - px));
	sValue.append("in");
	pDrawPathElement->addAttribute("svg:width", sValue);
	sValue = doubleToString((qy - py));
	sValue.append("in");
	pDrawPathElement->addAttribute("svg:height", sValue);
	sValue.sprintf("%i %i %i %i", 0, 0, (unsigned)(2540*(qx - px)), (unsigned)(2540*(qy - py)));
	pDrawPathElement->addAttribute("svg:viewBox", sValue);

	if (propList["draw:display"])
		pDrawPathElement->addAttribute("draw:display", propList["draw:display"]->getStr());

	pDrawPathElement->addAttribute("svg:d", libodfgen::convertPath(path, px, py));
	mpCurrentStorage->push_back(pDrawPathElement);
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:path"));
}

void OdfGenerator::drawPolySomething(const librevenge::RVNGPropertyList &propList, bool isClosed)
{
	const librevenge::RVNGPropertyListVector *vertices = propList.child("svg:points");
	if (!vertices || vertices->count() < 2)
		return;

	if (vertices->count() == 2)
	{
		if (!(*vertices)[0]["svg:x"]||!(*vertices)[0]["svg:y"]||!(*vertices)[1]["svg:x"]||!(*vertices)[1]["svg:y"])
		{
			ODFGEN_DEBUG_MSG(("OdfGenerator::drawPolySomething: some vertices are not defined\n"));
			return;
		}
		librevenge::RVNGString sValue=getCurrentGraphicStyleName(propList);
		bool isMeasure=(propList["draw:show-unit"] && propList["draw:show-unit"]->getStr()=="true");
		librevenge::RVNGString what= isMeasure ? "draw:measure" : "draw:line";

		auto pDrawLineElement = std::make_shared<TagOpenElement>(what);
		addFrameProperties(propList, *pDrawLineElement);
		pDrawLineElement->addAttribute("draw:style-name", sValue);
		pDrawLineElement->addAttribute("svg:x1", (*vertices)[0]["svg:x"]->getStr());
		pDrawLineElement->addAttribute("svg:y1", (*vertices)[0]["svg:y"]->getStr());
		pDrawLineElement->addAttribute("svg:x2", (*vertices)[1]["svg:x"]->getStr());
		pDrawLineElement->addAttribute("svg:y2", (*vertices)[1]["svg:y"]->getStr());
		if (propList["draw:display"])
			pDrawLineElement->addAttribute("draw:display", propList["draw:display"]->getStr());
		mpCurrentStorage->push_back(pDrawLineElement);
		mpCurrentStorage->push_back(std::make_shared<TagCloseElement>(what));
	}
	else
	{
		librevenge::RVNGPropertyListVector path;
		librevenge::RVNGPropertyList element;

		for (unsigned long ii = 0; ii < vertices->count(); ++ii)
		{
			element = (*vertices)[ii];
			if (ii == 0)
				element.insert("librevenge:path-action", "M");
			else
				element.insert("librevenge:path-action", "L");
			path.append(element);
			element.clear();
		}
		if (isClosed)
		{
			element.insert("librevenge:path-action", "Z");
			path.append(element);
		}
		drawPath(path,propList);
	}
}

void OdfGenerator::drawRectangle(const librevenge::RVNGPropertyList &propList)
{
	if (!propList["svg:x"] || !propList["svg:y"] ||
	        !propList["svg:width"] || !propList["svg:height"])
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::drawRectangle: position undefined\n"));
		return;
	}
	librevenge::RVNGString sValue=getCurrentGraphicStyleName(propList);
	librevenge::RVNGPropertyList frame(propList);
	frame.remove("svg:height");
	frame.remove("svg:width");
	auto pDrawRectElement = std::make_shared<TagOpenElement>("draw:rect");
	addFrameProperties(frame, *pDrawRectElement);
	pDrawRectElement->addAttribute("draw:style-name", sValue);
	pDrawRectElement->addAttribute("svg:x", propList["svg:x"]->getStr());
	pDrawRectElement->addAttribute("svg:y", propList["svg:y"]->getStr());
	pDrawRectElement->addAttribute("svg:width", propList["svg:width"]->getStr());
	pDrawRectElement->addAttribute("svg:height", propList["svg:height"]->getStr());
	// FIXME: what to do when rx != ry ?
	if (propList["svg:rx"])
		pDrawRectElement->addAttribute("draw:corner-radius", propList["svg:rx"]->getStr());
	else
		pDrawRectElement->addAttribute("draw:corner-radius", "0.0000in");
	if (propList["draw:transform"])
		pDrawRectElement->addAttribute("draw:transform", propList["draw:transform"]->getStr());
	if (propList["draw:display"])
		pDrawRectElement->addAttribute("draw:display", propList["draw:display"]->getStr());

	mpCurrentStorage->push_back(pDrawRectElement);
	mpCurrentStorage->push_back(std::make_shared<TagCloseElement>("draw:rect"));
}

void OdfGenerator::drawConnector(const librevenge::RVNGPropertyList &propList)
{
	const librevenge::RVNGPropertyListVector *path = propList.child("svg:d");
	if (!path) return;
	drawPath(*path, propList);
}

////////////////////////////////////////////////////////////
// chart
////////////////////////////////////////////////////////////
void OdfGenerator::defineChartStyle(const librevenge::RVNGPropertyList &propList)
{
	int chartId=-1;
	if (propList["librevenge:chart-id"])
		chartId=propList["librevenge:chart-id"]->getInt();
	else
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::defineChartStyle: called without id\n"));
	}
	mIdChartMap[chartId]=propList;
	mIdChartNameMap.erase(chartId);
}

////////////////////////////////////////////////////////////
// font
////////////////////////////////////////////////////////////

void OdfGenerator::defineEmbeddedFont(const librevenge::RVNGPropertyList &propList)
{
	// AbiWord rejects such ODF files (rightfully, as office:binary-data is not allowed in
	// svg:font-face-uri). So only do this for Flat ODF, until we have a way to insert binary
	// files into the output archive (which is not possible without an API change).
	if (!((mDocumentStreamHandlers.size() == 1) && (mDocumentStreamHandlers.begin()->first == ODF_FLAT_XML)))
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::defineEmbeddedFont: embedded fonts are only handled for Flat ODF currently\n"));
		return;
	}
	if (!propList["office:binary-data"] || !propList["librevenge:mime-type"] || !propList["librevenge:name"])
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::defineEmbeddedFont: can not find data, mimetype, or name\n"));
		return;
	}

	try
	{
		const librevenge::RVNGString name(propList["librevenge:name"]->getStr());
		const librevenge::RVNGString mimeType(propList["librevenge:mime-type"]->getStr());
		const librevenge::RVNGBinaryData data(propList["office:binary-data"]->getStr());

		OdfEmbeddedImage imageHandler = findEmbeddedImageHandler(mimeType);
		if (imageHandler)
		{
			librevenge::RVNGBinaryData output;
			if (imageHandler(data, output))
				mFontManager.setEmbedded(name, "application/x-font-ttf", output);
		}
		else
		{
			mFontManager.setEmbedded(name, mimeType, data);
		}
	}
	catch (...)
	{
		ODFGEN_DEBUG_MSG(("OdfGenerator::defineEmbeddedFont: ARGHH, catch an exception when decoding font!!!\n"));
	}
}

static const unsigned char librvng_utf8_skip_data[256] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,6,6,1,1
};

#define librvng_utf8_next_char(p) ((p) + librvng_utf8_skip_data[*reinterpret_cast<unsigned char const *>(p)])

void OdfGenerator::unescapeXML(const char *s, const unsigned long sz, librevenge::RVNGString &res)
{
	if (mXmlToUnicodeMap.empty())
	{
		mXmlToUnicodeMap=
		{
			/*{"Tab",0x00009}, {"NewLine",0x0000A},*/ {"excl",0x00021}, {"quot",0x00022}, {"QUOT",0x00022},
			{"num",0x00023}, {"dollar",0x00024}, {"percnt",0x00025}, {"amp",0x00026}, {"AMP",0x00026},
			{"apos",0x00027}, {"lpar",0x00028}, {"rpar",0x00029}, {"ast",0x0002A}, {"midast",0x0002A},
			{"plus",0x0002B}, {"comma",0x0002C}, {"period",0x0002E}, {"sol",0x0002F}, {"colon",0x0003A},
			{"semi",0x0003B}, {"lt",0x0003C}, {"LT",0x0003C}, {"equals",0x0003D}, {"gt",0x0003E},
			{"GT",0x0003E}, {"quest",0x0003F}, {"commat",0x00040}, {"lsqb",0x0005B}, {"lbrack",0x0005B},
			{"bsol",0x0005C}, {"rsqb",0x0005D}, {"rbrack",0x0005D}, {"Hat",0x0005E}, {"lowbar",0x0005F},
			{"grave",0x00060}, {"DiacriticalGrave",0x00060}, {"lcub",0x0007B}, {"lbrace",0x0007B}, {"verbar",0x0007C},
			{"vert",0x0007C}, {"VerticalLine",0x0007C}, {"rcub",0x0007D}, {"rbrace",0x0007D}, {"nbsp",0x000A0},
			{"NonBreakingSpace",0x000A0}, {"iexcl",0x000A1}, {"cent",0x000A2}, {"pound",0x000A3}, {"curren",0x000A4},
			{"yen",0x000A5}, {"brvbar",0x000A6}, {"sect",0x000A7}, {"Dot",0x000A8}, {"die",0x000A8},
			{"DoubleDot",0x000A8}, {"uml",0x000A8}, {"copy",0x000A9}, {"COPY",0x000A9}, {"ordf",0x000AA},
			{"laquo",0x000AB}, {"not",0x000AC}, {"shy",0x000AD}, {"reg",0x000AE}, {"circledR",0x000AE},
			{"REG",0x000AE}, {"macr",0x000AF}, {"OverBar",0x000AF}, {"strns",0x000AF}, {"deg",0x000B0},
			{"plusmn",0x000B1}, {"pm",0x000B1}, {"PlusMinus",0x000B1}, {"sup2",0x000B2}, {"sup3",0x000B3},
			{"acute",0x000B4}, {"DiacriticalAcute",0x000B4}, {"micro",0x000B5}, {"para",0x000B6}, {"middot",0x000B7},
			{"centerdot",0x000B7}, {"CenterDot",0x000B7}, {"cedil",0x000B8}, {"Cedilla",0x000B8}, {"sup1",0x000B9},
			{"ordm",0x000BA}, {"raquo",0x000BB}, {"frac14",0x000BC}, {"frac12",0x000BD}, {"half",0x000BD},
			{"frac34",0x000BE}, {"iquest",0x000BF}, {"Agrave",0x000C0}, {"Aacute",0x000C1}, {"Acirc",0x000C2},
			{"Atilde",0x000C3}, {"Auml",0x000C4}, {"Aring",0x000C5}, {"AElig",0x000C6}, {"Ccedil",0x000C7},
			{"Egrave",0x000C8}, {"Eacute",0x000C9}, {"Ecirc",0x000CA}, {"Euml",0x000CB}, {"Igrave",0x000CC},
			{"Iacute",0x000CD}, {"Icirc",0x000CE}, {"Iuml",0x000CF}, {"ETH",0x000D0}, {"Ntilde",0x000D1},
			{"Ograve",0x000D2}, {"Oacute",0x000D3}, {"Ocirc",0x000D4}, {"Otilde",0x000D5}, {"Ouml",0x000D6},
			{"times",0x000D7}, {"Oslash",0x000D8}, {"Ugrave",0x000D9}, {"Uacute",0x000DA}, {"Ucirc",0x000DB},
			{"Uuml",0x000DC}, {"Yacute",0x000DD}, {"THORN",0x000DE}, {"szlig",0x000DF}, {"agrave",0x000E0},
			{"aacute",0x000E1}, {"acirc",0x000E2}, {"atilde",0x000E3}, {"auml",0x000E4}, {"aring",0x000E5},
			{"aelig",0x000E6}, {"ccedil",0x000E7}, {"egrave",0x000E8}, {"eacute",0x000E9}, {"ecirc",0x000EA},
			{"euml",0x000EB}, {"igrave",0x000EC}, {"iacute",0x000ED}, {"icirc",0x000EE}, {"iuml",0x000EF},
			{"eth",0x000F0}, {"ntilde",0x000F1}, {"ograve",0x000F2}, {"oacute",0x000F3}, {"ocirc",0x000F4},
			{"otilde",0x000F5}, {"ouml",0x000F6}, {"divide",0x000F7}, {"div",0x000F7}, {"oslash",0x000F8},
			{"ugrave",0x000F9}, {"uacute",0x000FA}, {"ucirc",0x000FB}, {"uuml",0x000FC}, {"yacute",0x000FD},
			{"thorn",0x000FE}, {"yuml",0x000FF}, {"Amacr",0x00100}, {"amacr",0x00101}, {"Abreve",0x00102},
			{"abreve",0x00103}, {"Aogon",0x00104}, {"aogon",0x00105}, {"Cacute",0x00106}, {"cacute",0x00107},
			{"Ccirc",0x00108}, {"ccirc",0x00109}, {"Cdot",0x0010A}, {"cdot",0x0010B}, {"Ccaron",0x0010C},
			{"ccaron",0x0010D}, {"Dcaron",0x0010E}, {"dcaron",0x0010F}, {"Dstrok",0x00110}, {"dstrok",0x00111},
			{"Emacr",0x00112}, {"emacr",0x00113}, {"Edot",0x00116}, {"edot",0x00117}, {"Eogon",0x00118},
			{"eogon",0x00119}, {"Ecaron",0x0011A}, {"ecaron",0x0011B}, {"Gcirc",0x0011C}, {"gcirc",0x0011D},
			{"Gbreve",0x0011E}, {"gbreve",0x0011F}, {"Gdot",0x00120}, {"gdot",0x00121}, {"Gcedil",0x00122},
			{"Hcirc",0x00124}, {"hcirc",0x00125}, {"Hstrok",0x00126}, {"hstrok",0x00127}, {"Itilde",0x00128},
			{"itilde",0x00129}, {"Imacr",0x0012A}, {"imacr",0x0012B}, {"Iogon",0x0012E}, {"iogon",0x0012F},
			{"Idot",0x00130}, {"imath",0x00131}, {"inodot",0x00131}, {"IJlig",0x00132}, {"ijlig",0x00133},
			{"Jcirc",0x00134}, {"jcirc",0x00135}, {"Kcedil",0x00136}, {"kcedil",0x00137}, {"kgreen",0x00138},
			{"Lacute",0x00139}, {"lacute",0x0013A}, {"Lcedil",0x0013B}, {"lcedil",0x0013C}, {"Lcaron",0x0013D},
			{"lcaron",0x0013E}, {"Lmidot",0x0013F}, {"lmidot",0x00140}, {"Lstrok",0x00141}, {"lstrok",0x00142},
			{"Nacute",0x00143}, {"nacute",0x00144}, {"Ncedil",0x00145}, {"ncedil",0x00146}, {"Ncaron",0x00147},
			{"ncaron",0x00148}, {"napos",0x00149}, {"ENG",0x0014A}, {"eng",0x0014B}, {"Omacr",0x0014C},
			{"omacr",0x0014D}, {"Odblac",0x00150}, {"odblac",0x00151}, {"OElig",0x00152}, {"oelig",0x00153},
			{"Racute",0x00154}, {"racute",0x00155}, {"Rcedil",0x00156}, {"rcedil",0x00157}, {"Rcaron",0x00158},
			{"rcaron",0x00159}, {"Sacute",0x0015A}, {"sacute",0x0015B}, {"Scirc",0x0015C}, {"scirc",0x0015D},
			{"Scedil",0x0015E}, {"scedil",0x0015F}, {"Scaron",0x00160}, {"scaron",0x00161}, {"Tcedil",0x00162},
			{"tcedil",0x00163}, {"Tcaron",0x00164}, {"tcaron",0x00165}, {"Tstrok",0x00166}, {"tstrok",0x00167},
			{"Utilde",0x00168}, {"utilde",0x00169}, {"Umacr",0x0016A}, {"umacr",0x0016B}, {"Ubreve",0x0016C},
			{"ubreve",0x0016D}, {"Uring",0x0016E}, {"uring",0x0016F}, {"Udblac",0x00170}, {"udblac",0x00171},
			{"Uogon",0x00172}, {"uogon",0x00173}, {"Wcirc",0x00174}, {"wcirc",0x00175}, {"Ycirc",0x00176},
			{"ycirc",0x00177}, {"Yuml",0x00178}, {"Zacute",0x00179}, {"zacute",0x0017A}, {"Zdot",0x0017B},
			{"zdot",0x0017C}, {"Zcaron",0x0017D}, {"zcaron",0x0017E}, {"fnof",0x00192}, {"imped",0x001B5},
			{"gacute",0x001F5}, {"jmath",0x00237}, {"circ",0x002C6}, {"caron",0x002C7}, {"Hacek",0x002C7},
			{"breve",0x002D8}, {"Breve",0x002D8}, {"dot",0x002D9}, {"DiacriticalDot",0x002D9}, {"ring",0x002DA},
			{"ogon",0x002DB}, {"tilde",0x002DC}, {"DiacriticalTilde",0x002DC}, {"dblac",0x002DD}, {"DiacriticalDoubleAcute",0x002DD},
			{"DownBreve",0x00311}, {"UnderBar",0x00332}, {"Alpha",0x00391}, {"Beta",0x00392}, {"Gamma",0x00393},
			{"Delta",0x00394}, {"Epsilon",0x00395}, {"Zeta",0x00396}, {"Eta",0x00397}, {"Theta",0x00398},
			{"Iota",0x00399}, {"Kappa",0x0039A}, {"Lambda",0x0039B}, {"Mu",0x0039C}, {"Nu",0x0039D},
			{"Xi",0x0039E}, {"Omicron",0x0039F}, {"Pi",0x003A0}, {"Rho",0x003A1}, {"Sigma",0x003A3},
			{"Tau",0x003A4}, {"Upsilon",0x003A5}, {"Phi",0x003A6}, {"Chi",0x003A7}, {"Psi",0x003A8},
			{"Omega",0x003A9}, {"alpha",0x003B1}, {"beta",0x003B2}, {"gamma",0x003B3}, {"delta",0x003B4},
			{"epsiv",0x003B5}, {"varepsilon",0x003B5}, {"epsilon",0x003B5}, {"zeta",0x003B6}, {"eta",0x003B7},
			{"theta",0x003B8}, {"iota",0x003B9}, {"kappa",0x003BA}, {"lambda",0x003BB}, {"mu",0x003BC},
			{"nu",0x003BD}, {"xi",0x003BE}, {"omicron",0x003BF}, {"pi",0x003C0}, {"rho",0x003C1},
			{"sigmav",0x003C2}, {"varsigma",0x003C2}, {"sigmaf",0x003C2}, {"sigma",0x003C3}, {"tau",0x003C4},
			{"upsi",0x003C5}, {"upsilon",0x003C5}, {"phi",0x003C6}, {"phiv",0x003C6}, {"varphi",0x003C6},
			{"chi",0x003C7}, {"psi",0x003C8}, {"omega",0x003C9}, {"thetav",0x003D1}, {"vartheta",0x003D1},
			{"thetasym",0x003D1}, {"Upsi",0x003D2}, {"upsih",0x003D2}, {"straightphi",0x003D5}, {"piv",0x003D6},
			{"varpi",0x003D6}, {"Gammad",0x003DC}, {"gammad",0x003DD}, {"digamma",0x003DD}, {"kappav",0x003F0},
			{"varkappa",0x003F0}, {"rhov",0x003F1}, {"varrho",0x003F1}, {"epsi",0x003F5}, {"straightepsilon",0x003F5},
			{"bepsi",0x003F6}, {"backepsilon",0x003F6}, {"IOcy",0x00401}, {"DJcy",0x00402}, {"GJcy",0x00403},
			{"Jukcy",0x00404}, {"DScy",0x00405}, {"Iukcy",0x00406}, {"YIcy",0x00407}, {"Jsercy",0x00408},
			{"LJcy",0x00409}, {"NJcy",0x0040A}, {"TSHcy",0x0040B}, {"KJcy",0x0040C}, {"Ubrcy",0x0040E},
			{"DZcy",0x0040F}, {"Acy",0x00410}, {"Bcy",0x00411}, {"Vcy",0x00412}, {"Gcy",0x00413},
			{"Dcy",0x00414}, {"IEcy",0x00415}, {"ZHcy",0x00416}, {"Zcy",0x00417}, {"Icy",0x00418},
			{"Jcy",0x00419}, {"Kcy",0x0041A}, {"Lcy",0x0041B}, {"Mcy",0x0041C}, {"Ncy",0x0041D},
			{"Ocy",0x0041E}, {"Pcy",0x0041F}, {"Rcy",0x00420}, {"Scy",0x00421}, {"Tcy",0x00422},
			{"Ucy",0x00423}, {"Fcy",0x00424}, {"KHcy",0x00425}, {"TScy",0x00426}, {"CHcy",0x00427},
			{"SHcy",0x00428}, {"SHCHcy",0x00429}, {"HARDcy",0x0042A}, {"Ycy",0x0042B}, {"SOFTcy",0x0042C},
			{"Ecy",0x0042D}, {"YUcy",0x0042E}, {"YAcy",0x0042F}, {"acy",0x00430}, {"bcy",0x00431},
			{"vcy",0x00432}, {"gcy",0x00433}, {"dcy",0x00434}, {"iecy",0x00435}, {"zhcy",0x00436},
			{"zcy",0x00437}, {"icy",0x00438}, {"jcy",0x00439}, {"kcy",0x0043A}, {"lcy",0x0043B},
			{"mcy",0x0043C}, {"ncy",0x0043D}, {"ocy",0x0043E}, {"pcy",0x0043F}, {"rcy",0x00440},
			{"scy",0x00441}, {"tcy",0x00442}, {"ucy",0x00443}, {"fcy",0x00444}, {"khcy",0x00445},
			{"tscy",0x00446}, {"chcy",0x00447}, {"shcy",0x00448}, {"shchcy",0x00449}, {"hardcy",0x0044A},
			{"ycy",0x0044B}, {"softcy",0x0044C}, {"ecy",0x0044D}, {"yucy",0x0044E}, {"yacy",0x0044F},
			{"iocy",0x00451}, {"djcy",0x00452}, {"gjcy",0x00453}, {"jukcy",0x00454}, {"dscy",0x00455},
			{"iukcy",0x00456}, {"yicy",0x00457}, {"jsercy",0x00458}, {"ljcy",0x00459}, {"njcy",0x0045A},
			{"tshcy",0x0045B}, {"kjcy",0x0045C}, {"ubrcy",0x0045E}, {"dzcy",0x0045F}, {"ensp",0x02002},
			{"emsp",0x02003}, {"emsp13",0x02004}, {"emsp14",0x02005}, {"numsp",0x02007}, {"puncsp",0x02008},
			{"thinsp",0x02009}, {"ThinSpace",0x02009}, {"hairsp",0x0200A}, {"VeryThinSpace",0x0200A}, {"ZeroWidthSpace",0x0200B},
			{"NegativeVeryThinSpace",0x0200B}, {"NegativeThinSpace",0x0200B}, {"NegativeMediumSpace",0x0200B}, {"NegativeThickSpace",0x0200B}, {"zwnj",0x0200C},
			{"zwj",0x0200D}, {"lrm",0x0200E}, {"rlm",0x0200F}, {"hyphen",0x02010}, {"dash",0x02010},
			{"ndash",0x02013}, {"mdash",0x02014}, {"horbar",0x02015}, {"Verbar",0x02016}, {"Vert",0x02016},
			{"lsquo",0x02018}, {"OpenCurlyQuote",0x02018}, {"rsquo",0x02019}, {"rsquor",0x02019}, {"CloseCurlyQuote",0x02019},
			{"lsquor",0x0201A}, {"sbquo",0x0201A}, {"ldquo",0x0201C}, {"OpenCurlyDoubleQuote",0x0201C}, {"rdquo",0x0201D},
			{"rdquor",0x0201D}, {"CloseCurlyDoubleQuote",0x0201D}, {"ldquor",0x0201E}, {"bdquo",0x0201E}, {"dagger",0x02020},
			{"Dagger",0x02021}, {"ddagger",0x02021}, {"bull",0x02022}, {"bullet",0x02022}, {"nldr",0x02025},
			{"hellip",0x02026}, {"mldr",0x02026}, {"permil",0x02030}, {"pertenk",0x02031}, {"prime",0x02032},
			{"Prime",0x02033}, {"tprime",0x02034}, {"bprime",0x02035}, {"backprime",0x02035}, {"lsaquo",0x02039},
			{"rsaquo",0x0203A}, {"oline",0x0203E}, {"caret",0x02041}, {"hybull",0x02043}, {"frasl",0x02044},
			{"bsemi",0x0204F}, {"qprime",0x02057}, {"MediumSpace",0x0205F}, {"NoBreak",0x02060}, {"ApplyFunction",0x02061},
			{"af",0x02061}, {"InvisibleTimes",0x02062}, {"it",0x02062}, {"InvisibleComma",0x02063}, {"ic",0x02063},
			{"euro",0x020AC}, {"tdot",0x020DB}, {"TripleDot",0x020DB}, {"DotDot",0x020DC}, {"Copf",0x02102},
			{"complexes",0x02102}, {"incare",0x02105}, {"gscr",0x0210A}, {"hamilt",0x0210B}, {"HilbertSpace",0x0210B},
			{"Hscr",0x0210B}, {"Hfr",0x0210C}, {"Poincareplane",0x0210C}, {"quaternions",0x0210D}, {"Hopf",0x0210D},
			{"planckh",0x0210E}, {"planck",0x0210F}, {"hbar",0x0210F}, {"plankv",0x0210F}, {"hslash",0x0210F},
			{"Iscr",0x02110}, {"imagline",0x02110}, {"image",0x02111}, {"Im",0x02111}, {"imagpart",0x02111},
			{"Ifr",0x02111}, {"Lscr",0x02112}, {"lagran",0x02112}, {"Laplacetrf",0x02112}, {"ell",0x02113},
			{"Nopf",0x02115}, {"naturals",0x02115}, {"numero",0x02116}, {"copysr",0x02117}, {"weierp",0x02118},
			{"wp",0x02118}, {"Popf",0x02119}, {"primes",0x02119}, {"rationals",0x0211A}, {"Qopf",0x0211A},
			{"Rscr",0x0211B}, {"realine",0x0211B}, {"real",0x0211C}, {"Re",0x0211C}, {"realpart",0x0211C},
			{"Rfr",0x0211C}, {"reals",0x0211D}, {"Ropf",0x0211D}, {"rx",0x0211E}, {"trade",0x02122},
			{"TRADE",0x02122}, {"integers",0x02124}, {"Zopf",0x02124}, {"ohm",0x02126}, {"mho",0x02127},
			{"Zfr",0x02128}, {"zeetrf",0x02128}, {"iiota",0x02129}, {"angst",0x0212B}, {"bernou",0x0212C},
			{"Bernoullis",0x0212C}, {"Bscr",0x0212C}, {"Cfr",0x0212D}, {"Cayleys",0x0212D}, {"escr",0x0212F},
			{"Escr",0x02130}, {"expectation",0x02130}, {"Fscr",0x02131}, {"Fouriertrf",0x02131}, {"phmmat",0x02133},
			{"Mellintrf",0x02133}, {"Mscr",0x02133}, {"order",0x02134}, {"orderof",0x02134}, {"oscr",0x02134},
			{"alefsym",0x02135}, {"aleph",0x02135}, {"beth",0x02136}, {"gimel",0x02137}, {"daleth",0x02138},
			{"CapitalDifferentialD",0x02145}, {"DD",0x02145}, {"DifferentialD",0x02146}, {"dd",0x02146}, {"ExponentialE",0x02147},
			{"exponentiale",0x02147}, {"ee",0x02147}, {"ImaginaryI",0x02148}, {"ii",0x02148}, {"frac13",0x02153},
			{"frac23",0x02154}, {"frac15",0x02155}, {"frac25",0x02156}, {"frac35",0x02157}, {"frac45",0x02158},
			{"frac16",0x02159}, {"frac56",0x0215A}, {"frac18",0x0215B}, {"frac38",0x0215C}, {"frac58",0x0215D},
			{"frac78",0x0215E}, {"larr",0x02190}, {"leftarrow",0x02190}, {"LeftArrow",0x02190}, {"slarr",0x02190},
			{"ShortLeftArrow",0x02190}, {"uarr",0x02191}, {"uparrow",0x02191}, {"UpArrow",0x02191}, {"ShortUpArrow",0x02191},
			{"rarr",0x02192}, {"rightarrow",0x02192}, {"RightArrow",0x02192}, {"srarr",0x02192}, {"ShortRightArrow",0x02192},
			{"darr",0x02193}, {"downarrow",0x02193}, {"DownArrow",0x02193}, {"ShortDownArrow",0x02193}, {"harr",0x02194},
			{"leftrightarrow",0x02194}, {"LeftRightArrow",0x02194}, {"varr",0x02195}, {"updownarrow",0x02195}, {"UpDownArrow",0x02195},
			{"nwarr",0x02196}, {"UpperLeftArrow",0x02196}, {"nwarrow",0x02196}, {"nearr",0x02197}, {"UpperRightArrow",0x02197},
			{"nearrow",0x02197}, {"searr",0x02198}, {"searrow",0x02198}, {"LowerRightArrow",0x02198}, {"swarr",0x02199},
			{"swarrow",0x02199}, {"LowerLeftArrow",0x02199}, {"nlarr",0x0219A}, {"nleftarrow",0x0219A}, {"nrarr",0x0219B},
			{"nrightarrow",0x0219B}, {"rarrw",0x0219D}, {"rightsquigarrow",0x0219D}, {"Larr",0x0219E}, {"twoheadleftarrow",0x0219E},
			{"Uarr",0x0219F}, {"Rarr",0x021A0}, {"twoheadrightarrow",0x021A0}, {"Darr",0x021A1}, {"larrtl",0x021A2},
			{"leftarrowtail",0x021A2}, {"rarrtl",0x021A3}, {"rightarrowtail",0x021A3}, {"LeftTeeArrow",0x021A4}, {"mapstoleft",0x021A4},
			{"UpTeeArrow",0x021A5}, {"mapstoup",0x021A5}, {"map",0x021A6}, {"RightTeeArrow",0x021A6}, {"mapsto",0x021A6},
			{"DownTeeArrow",0x021A7}, {"mapstodown",0x021A7}, {"larrhk",0x021A9}, {"hookleftarrow",0x021A9}, {"rarrhk",0x021AA},
			{"hookrightarrow",0x021AA}, {"larrlp",0x021AB}, {"looparrowleft",0x021AB}, {"rarrlp",0x021AC}, {"looparrowright",0x021AC},
			{"harrw",0x021AD}, {"leftrightsquigarrow",0x021AD}, {"nharr",0x021AE}, {"nleftrightarrow",0x021AE}, {"lsh",0x021B0},
			{"Lsh",0x021B0}, {"rsh",0x021B1}, {"Rsh",0x021B1}, {"ldsh",0x021B2}, {"rdsh",0x021B3},
			{"crarr",0x021B5}, {"cularr",0x021B6}, {"curvearrowleft",0x021B6}, {"curarr",0x021B7}, {"curvearrowright",0x021B7},
			{"olarr",0x021BA}, {"circlearrowleft",0x021BA}, {"orarr",0x021BB}, {"circlearrowright",0x021BB}, {"lharu",0x021BC},
			{"LeftVector",0x021BC}, {"leftharpoonup",0x021BC}, {"lhard",0x021BD}, {"leftharpoondown",0x021BD}, {"DownLeftVector",0x021BD},
			{"uharr",0x021BE}, {"upharpoonright",0x021BE}, {"RightUpVector",0x021BE}, {"uharl",0x021BF}, {"upharpoonleft",0x021BF},
			{"LeftUpVector",0x021BF}, {"rharu",0x021C0}, {"RightVector",0x021C0}, {"rightharpoonup",0x021C0}, {"rhard",0x021C1},
			{"rightharpoondown",0x021C1}, {"DownRightVector",0x021C1}, {"dharr",0x021C2}, {"RightDownVector",0x021C2}, {"downharpoonright",0x021C2},
			{"dharl",0x021C3}, {"LeftDownVector",0x021C3}, {"downharpoonleft",0x021C3}, {"rlarr",0x021C4}, {"rightleftarrows",0x021C4},
			{"RightArrowLeftArrow",0x021C4}, {"udarr",0x021C5}, {"UpArrowDownArrow",0x021C5}, {"lrarr",0x021C6}, {"leftrightarrows",0x021C6},
			{"LeftArrowRightArrow",0x021C6}, {"llarr",0x021C7}, {"leftleftarrows",0x021C7}, {"uuarr",0x021C8}, {"upuparrows",0x021C8},
			{"rrarr",0x021C9}, {"rightrightarrows",0x021C9}, {"ddarr",0x021CA}, {"downdownarrows",0x021CA}, {"lrhar",0x021CB},
			{"ReverseEquilibrium",0x021CB}, {"leftrightharpoons",0x021CB}, {"rlhar",0x021CC}, {"rightleftharpoons",0x021CC}, {"Equilibrium",0x021CC},
			{"nlArr",0x021CD}, {"nLeftarrow",0x021CD}, {"nhArr",0x021CE}, {"nLeftrightarrow",0x021CE}, {"nrArr",0x021CF},
			{"nRightarrow",0x021CF}, {"lArr",0x021D0}, {"Leftarrow",0x021D0}, {"DoubleLeftArrow",0x021D0}, {"uArr",0x021D1},
			{"Uparrow",0x021D1}, {"DoubleUpArrow",0x021D1}, {"rArr",0x021D2}, {"Rightarrow",0x021D2}, {"Implies",0x021D2},
			{"DoubleRightArrow",0x021D2}, {"dArr",0x021D3}, {"Downarrow",0x021D3}, {"DoubleDownArrow",0x021D3}, {"hArr",0x021D4},
			{"Leftrightarrow",0x021D4}, {"DoubleLeftRightArrow",0x021D4}, {"iff",0x021D4}, {"vArr",0x021D5}, {"Updownarrow",0x021D5},
			{"DoubleUpDownArrow",0x021D5}, {"nwArr",0x021D6}, {"neArr",0x021D7}, {"seArr",0x021D8}, {"swArr",0x021D9},
			{"lAarr",0x021DA}, {"Lleftarrow",0x021DA}, {"rAarr",0x021DB}, {"Rrightarrow",0x021DB}, {"zigrarr",0x021DD},
			{"larrb",0x021E4}, {"LeftArrowBar",0x021E4}, {"rarrb",0x021E5}, {"RightArrowBar",0x021E5}, {"duarr",0x021F5},
			{"DownArrowUpArrow",0x021F5}, {"loarr",0x021FD}, {"roarr",0x021FE}, {"hoarr",0x021FF}, {"forall",0x02200},
			{"ForAll",0x02200}, {"comp",0x02201}, {"complement",0x02201}, {"part",0x02202}, {"PartialD",0x02202},
			{"exist",0x02203}, {"Exists",0x02203}, {"nexist",0x02204}, {"NotExists",0x02204}, {"nexists",0x02204},
			{"empty",0x02205}, {"emptyset",0x02205}, {"emptyv",0x02205}, {"varnothing",0x02205}, {"nabla",0x02207},
			{"Del",0x02207}, {"isin",0x02208}, {"isinv",0x02208}, {"Element",0x02208}, {"in",0x02208},
			{"notin",0x02209}, {"NotElement",0x02209}, {"notinva",0x02209}, {"niv",0x0220B}, {"ReverseElement",0x0220B},
			{"ni",0x0220B}, {"SuchThat",0x0220B}, {"notni",0x0220C}, {"notniva",0x0220C}, {"NotReverseElement",0x0220C},
			{"prod",0x0220F}, {"Product",0x0220F}, {"coprod",0x02210}, {"Coproduct",0x02210}, {"sum",0x02211},
			{"Sum",0x02211}, {"minus",0x02212}, {"mnplus",0x02213}, {"mp",0x02213}, {"MinusPlus",0x02213},
			{"plusdo",0x02214}, {"dotplus",0x02214}, {"setmn",0x02216}, {"setminus",0x02216}, {"Backslash",0x02216},
			{"ssetmn",0x02216}, {"smallsetminus",0x02216}, {"lowast",0x02217}, {"compfn",0x02218}, {"SmallCircle",0x02218},
			{"radic",0x0221A}, {"Sqrt",0x0221A}, {"prop",0x0221D}, {"propto",0x0221D}, {"Proportional",0x0221D},
			{"vprop",0x0221D}, {"varpropto",0x0221D}, {"infin",0x0221E}, {"angrt",0x0221F}, {"ang",0x02220},
			{"angle",0x02220}, {"angmsd",0x02221}, {"measuredangle",0x02221}, {"angsph",0x02222}, {"mid",0x02223},
			{"VerticalBar",0x02223}, {"smid",0x02223}, {"shortmid",0x02223}, {"nmid",0x02224}, {"NotVerticalBar",0x02224},
			{"nsmid",0x02224}, {"nshortmid",0x02224}, {"par",0x02225}, {"parallel",0x02225}, {"DoubleVerticalBar",0x02225},
			{"spar",0x02225}, {"shortparallel",0x02225}, {"npar",0x02226}, {"nparallel",0x02226}, {"NotDoubleVerticalBar",0x02226},
			{"nspar",0x02226}, {"nshortparallel",0x02226}, {"and",0x02227}, {"wedge",0x02227}, {"or",0x02228},
			{"vee",0x02228}, {"cap",0x02229}, {"cup",0x0222A}, {"int",0x0222B}, {"Integral",0x0222B},
			{"Int",0x0222C}, {"tint",0x0222D}, {"iiint",0x0222D}, {"conint",0x0222E}, {"oint",0x0222E},
			{"ContourIntegral",0x0222E}, {"Conint",0x0222F}, {"DoubleContourIntegral",0x0222F}, {"Cconint",0x02230}, {"cwint",0x02231},
			{"cwconint",0x02232}, {"ClockwiseContourIntegral",0x02232}, {"awconint",0x02233}, {"CounterClockwiseContourIntegral",0x02233}, {"there4",0x02234},
			{"therefore",0x02234}, {"Therefore",0x02234}, {"becaus",0x02235}, {"because",0x02235}, {"Because",0x02235},
			{"ratio",0x02236}, {"Colon",0x02237}, {"Proportion",0x02237}, {"minusd",0x02238}, {"dotminus",0x02238},
			{"mDDot",0x0223A}, {"homtht",0x0223B}, {"sim",0x0223C}, {"Tilde",0x0223C}, {"thksim",0x0223C},
			{"thicksim",0x0223C}, {"bsim",0x0223D}, {"backsim",0x0223D}, {"ac",0x0223E}, {"mstpos",0x0223E},
			{"acd",0x0223F}, {"wreath",0x02240}, {"VerticalTilde",0x02240}, {"wr",0x02240}, {"nsim",0x02241},
			{"NotTilde",0x02241}, {"esim",0x02242}, {"EqualTilde",0x02242}, {"eqsim",0x02242}, {"sime",0x02243},
			{"TildeEqual",0x02243}, {"simeq",0x02243}, {"nsime",0x02244}, {"nsimeq",0x02244}, {"NotTildeEqual",0x02244},
			{"cong",0x02245}, {"TildeFullEqual",0x02245}, {"simne",0x02246}, {"ncong",0x02247}, {"NotTildeFullEqual",0x02247},
			{"asymp",0x02248}, {"ap",0x02248}, {"TildeTilde",0x02248}, {"approx",0x02248}, {"thkap",0x02248},
			{"thickapprox",0x02248}, {"nap",0x02249}, {"NotTildeTilde",0x02249}, {"napprox",0x02249}, {"ape",0x0224A},
			{"approxeq",0x0224A}, {"apid",0x0224B}, {"bcong",0x0224C}, {"backcong",0x0224C}, {"asympeq",0x0224D},
			{"CupCap",0x0224D}, {"bump",0x0224E}, {"HumpDownHump",0x0224E}, {"Bumpeq",0x0224E}, {"bumpe",0x0224F},
			{"HumpEqual",0x0224F}, {"bumpeq",0x0224F}, {"esdot",0x02250}, {"DotEqual",0x02250}, {"doteq",0x02250},
			{"eDot",0x02251}, {"doteqdot",0x02251}, {"efDot",0x02252}, {"fallingdotseq",0x02252}, {"erDot",0x02253},
			{"risingdotseq",0x02253}, {"colone",0x02254}, {"coloneq",0x02254}, {"Assign",0x02254}, {"ecolon",0x02255},
			{"eqcolon",0x02255}, {"ecir",0x02256}, {"eqcirc",0x02256}, {"cire",0x02257}, {"circeq",0x02257},
			{"wedgeq",0x02259}, {"veeeq",0x0225A}, {"trie",0x0225C}, {"triangleq",0x0225C}, {"equest",0x0225F},
			{"questeq",0x0225F}, {"ne",0x02260}, {"NotEqual",0x02260}, {"equiv",0x02261}, {"Congruent",0x02261},
			{"nequiv",0x02262}, {"NotCongruent",0x02262}, {"le",0x02264}, {"leq",0x02264}, {"ge",0x02265},
			{"GreaterEqual",0x02265}, {"geq",0x02265}, {"lE",0x02266}, {"LessFullEqual",0x02266}, {"leqq",0x02266},
			{"gE",0x02267}, {"GreaterFullEqual",0x02267}, {"geqq",0x02267}, {"lnE",0x02268}, {"lneqq",0x02268},
			{"gnE",0x02269}, {"gneqq",0x02269}, {"Lt",0x0226A}, {"NestedLessLess",0x0226A}, {"ll",0x0226A},
			{"Gt",0x0226B}, {"NestedGreaterGreater",0x0226B}, {"gg",0x0226B}, {"twixt",0x0226C}, {"between",0x0226C},
			{"NotCupCap",0x0226D}, {"nlt",0x0226E}, {"NotLess",0x0226E}, {"nless",0x0226E}, {"ngt",0x0226F},
			{"NotGreater",0x0226F}, {"ngtr",0x0226F}, {"nle",0x02270}, {"NotLessEqual",0x02270}, {"nleq",0x02270},
			{"nge",0x02271}, {"NotGreaterEqual",0x02271}, {"ngeq",0x02271}, {"lsim",0x02272}, {"LessTilde",0x02272},
			{"lesssim",0x02272}, {"gsim",0x02273}, {"gtrsim",0x02273}, {"GreaterTilde",0x02273}, {"nlsim",0x02274},
			{"NotLessTilde",0x02274}, {"ngsim",0x02275}, {"NotGreaterTilde",0x02275}, {"lg",0x02276}, {"lessgtr",0x02276},
			{"LessGreater",0x02276}, {"gl",0x02277}, {"gtrless",0x02277}, {"GreaterLess",0x02277}, {"ntlg",0x02278},
			{"NotLessGreater",0x02278}, {"ntgl",0x02279}, {"NotGreaterLess",0x02279}, {"pr",0x0227A}, {"Precedes",0x0227A},
			{"prec",0x0227A}, {"sc",0x0227B}, {"Succeeds",0x0227B}, {"succ",0x0227B}, {"prcue",0x0227C},
			{"PrecedesSlantEqual",0x0227C}, {"preccurlyeq",0x0227C}, {"sccue",0x0227D}, {"SucceedsSlantEqual",0x0227D}, {"succcurlyeq",0x0227D},
			{"prsim",0x0227E}, {"precsim",0x0227E}, {"PrecedesTilde",0x0227E}, {"scsim",0x0227F}, {"succsim",0x0227F},
			{"SucceedsTilde",0x0227F}, {"npr",0x02280}, {"nprec",0x02280}, {"NotPrecedes",0x02280}, {"nsc",0x02281},
			{"nsucc",0x02281}, {"NotSucceeds",0x02281}, {"sub",0x02282}, {"subset",0x02282}, {"sup",0x02283},
			{"supset",0x02283}, {"Superset",0x02283}, {"nsub",0x02284}, {"nsup",0x02285}, {"sube",0x02286},
			{"SubsetEqual",0x02286}, {"subseteq",0x02286}, {"supe",0x02287}, {"supseteq",0x02287}, {"SupersetEqual",0x02287},
			{"nsube",0x02288}, {"nsubseteq",0x02288}, {"NotSubsetEqual",0x02288}, {"nsupe",0x02289}, {"nsupseteq",0x02289},
			{"NotSupersetEqual",0x02289}, {"subne",0x0228A}, {"subsetneq",0x0228A}, {"supne",0x0228B}, {"supsetneq",0x0228B},
			{"cupdot",0x0228D}, {"uplus",0x0228E}, {"UnionPlus",0x0228E}, {"sqsub",0x0228F}, {"SquareSubset",0x0228F},
			{"sqsubset",0x0228F}, {"sqsup",0x02290}, {"SquareSuperset",0x02290}, {"sqsupset",0x02290}, {"sqsube",0x02291},
			{"SquareSubsetEqual",0x02291}, {"sqsubseteq",0x02291}, {"sqsupe",0x02292}, {"SquareSupersetEqual",0x02292}, {"sqsupseteq",0x02292},
			{"sqcap",0x02293}, {"SquareIntersection",0x02293}, {"sqcup",0x02294}, {"SquareUnion",0x02294}, {"oplus",0x02295},
			{"CirclePlus",0x02295}, {"ominus",0x02296}, {"CircleMinus",0x02296}, {"otimes",0x02297}, {"CircleTimes",0x02297},
			{"osol",0x02298}, {"odot",0x02299}, {"CircleDot",0x02299}, {"ocir",0x0229A}, {"circledcirc",0x0229A},
			{"oast",0x0229B}, {"circledast",0x0229B}, {"odash",0x0229D}, {"circleddash",0x0229D}, {"plusb",0x0229E},
			{"boxplus",0x0229E}, {"minusb",0x0229F}, {"boxminus",0x0229F}, {"timesb",0x022A0}, {"boxtimes",0x022A0},
			{"sdotb",0x022A1}, {"dotsquare",0x022A1}, {"vdash",0x022A2}, {"RightTee",0x022A2}, {"dashv",0x022A3},
			{"LeftTee",0x022A3}, {"top",0x022A4}, {"DownTee",0x022A4}, {"bottom",0x022A5}, {"bot",0x022A5},
			{"perp",0x022A5}, {"UpTee",0x022A5}, {"models",0x022A7}, {"vDash",0x022A8}, {"DoubleRightTee",0x022A8},
			{"Vdash",0x022A9}, {"Vvdash",0x022AA}, {"VDash",0x022AB}, {"nvdash",0x022AC}, {"nvDash",0x022AD},
			{"nVdash",0x022AE}, {"nVDash",0x022AF}, {"prurel",0x022B0}, {"vltri",0x022B2}, {"vartriangleleft",0x022B2},
			{"LeftTriangle",0x022B2}, {"vrtri",0x022B3}, {"vartriangleright",0x022B3}, {"RightTriangle",0x022B3}, {"ltrie",0x022B4},
			{"trianglelefteq",0x022B4}, {"LeftTriangleEqual",0x022B4}, {"rtrie",0x022B5}, {"trianglerighteq",0x022B5}, {"RightTriangleEqual",0x022B5},
			{"origof",0x022B6}, {"imof",0x022B7}, {"mumap",0x022B8}, {"multimap",0x022B8}, {"hercon",0x022B9},
			{"intcal",0x022BA}, {"intercal",0x022BA}, {"veebar",0x022BB}, {"barvee",0x022BD}, {"angrtvb",0x022BE},
			{"lrtri",0x022BF}, {"xwedge",0x022C0}, {"Wedge",0x022C0}, {"bigwedge",0x022C0}, {"xvee",0x022C1},
			{"Vee",0x022C1}, {"bigvee",0x022C1}, {"xcap",0x022C2}, {"Intersection",0x022C2}, {"bigcap",0x022C2},
			{"xcup",0x022C3}, {"Union",0x022C3}, {"bigcup",0x022C3}, {"diam",0x022C4}, {"diamond",0x022C4},
			{"Diamond",0x022C4}, {"sdot",0x022C5}, {"sstarf",0x022C6}, {"Star",0x022C6}, {"divonx",0x022C7},
			{"divideontimes",0x022C7}, {"bowtie",0x022C8}, {"ltimes",0x022C9}, {"rtimes",0x022CA}, {"lthree",0x022CB},
			{"leftthreetimes",0x022CB}, {"rthree",0x022CC}, {"rightthreetimes",0x022CC}, {"bsime",0x022CD}, {"backsimeq",0x022CD},
			{"cuvee",0x022CE}, {"curlyvee",0x022CE}, {"cuwed",0x022CF}, {"curlywedge",0x022CF}, {"Sub",0x022D0},
			{"Subset",0x022D0}, {"Sup",0x022D1}, {"Supset",0x022D1}, {"Cap",0x022D2}, {"Cup",0x022D3},
			{"fork",0x022D4}, {"pitchfork",0x022D4}, {"epar",0x022D5}, {"ltdot",0x022D6}, {"lessdot",0x022D6},
			{"gtdot",0x022D7}, {"gtrdot",0x022D7}, {"Ll",0x022D8}, {"Gg",0x022D9}, {"ggg",0x022D9},
			{"leg",0x022DA}, {"LessEqualGreater",0x022DA}, {"lesseqgtr",0x022DA}, {"gel",0x022DB}, {"gtreqless",0x022DB},
			{"GreaterEqualLess",0x022DB}, {"cuepr",0x022DE}, {"curlyeqprec",0x022DE}, {"cuesc",0x022DF}, {"curlyeqsucc",0x022DF},
			{"nprcue",0x022E0}, {"NotPrecedesSlantEqual",0x022E0}, {"nsccue",0x022E1}, {"NotSucceedsSlantEqual",0x022E1}, {"nsqsube",0x022E2},
			{"NotSquareSubsetEqual",0x022E2}, {"nsqsupe",0x022E3}, {"NotSquareSupersetEqual",0x022E3}, {"lnsim",0x022E6}, {"gnsim",0x022E7},
			{"prnsim",0x022E8}, {"precnsim",0x022E8}, {"scnsim",0x022E9}, {"succnsim",0x022E9}, {"nltri",0x022EA},
			{"ntriangleleft",0x022EA}, {"NotLeftTriangle",0x022EA}, {"nrtri",0x022EB}, {"ntriangleright",0x022EB}, {"NotRightTriangle",0x022EB},
			{"nltrie",0x022EC}, {"ntrianglelefteq",0x022EC}, {"NotLeftTriangleEqual",0x022EC}, {"nrtrie",0x022ED}, {"ntrianglerighteq",0x022ED},
			{"NotRightTriangleEqual",0x022ED}, {"vellip",0x022EE}, {"ctdot",0x022EF}, {"utdot",0x022F0}, {"dtdot",0x022F1},
			{"disin",0x022F2}, {"isinsv",0x022F3}, {"isins",0x022F4}, {"isindot",0x022F5}, {"notinvc",0x022F6},
			{"notinvb",0x022F7}, {"isinE",0x022F9}, {"nisd",0x022FA}, {"xnis",0x022FB}, {"nis",0x022FC},
			{"notnivc",0x022FD}, {"notnivb",0x022FE}, {"barwed",0x02305}, {"barwedge",0x02305}, {"Barwed",0x02306},
			{"doublebarwedge",0x02306}, {"lceil",0x02308}, {"LeftCeiling",0x02308}, {"rceil",0x02309}, {"RightCeiling",0x02309},
			{"lfloor",0x0230A}, {"LeftFloor",0x0230A}, {"rfloor",0x0230B}, {"RightFloor",0x0230B}, {"drcrop",0x0230C},
			{"dlcrop",0x0230D}, {"urcrop",0x0230E}, {"ulcrop",0x0230F}, {"bnot",0x02310}, {"profline",0x02312},
			{"profsurf",0x02313}, {"telrec",0x02315}, {"target",0x02316}, {"ulcorn",0x0231C}, {"ulcorner",0x0231C},
			{"urcorn",0x0231D}, {"urcorner",0x0231D}, {"dlcorn",0x0231E}, {"llcorner",0x0231E}, {"drcorn",0x0231F},
			{"lrcorner",0x0231F}, {"frown",0x02322}, {"sfrown",0x02322}, {"smile",0x02323}, {"ssmile",0x02323},
			{"cylcty",0x0232D}, {"profalar",0x0232E}, {"topbot",0x02336}, {"ovbar",0x0233D}, {"solbar",0x0233F},
			{"angzarr",0x0237C}, {"lmoust",0x023B0}, {"lmoustache",0x023B0}, {"rmoust",0x023B1}, {"rmoustache",0x023B1},
			{"tbrk",0x023B4}, {"OverBracket",0x023B4}, {"bbrk",0x023B5}, {"UnderBracket",0x023B5}, {"bbrktbrk",0x023B6},
			{"OverParenthesis",0x023DC}, {"UnderParenthesis",0x023DD}, {"OverBrace",0x023DE}, {"UnderBrace",0x023DF}, {"trpezium",0x023E2},
			{"elinters",0x023E7}, {"blank",0x02423}, {"oS",0x024C8}, {"circledS",0x024C8}, {"boxh",0x02500},
			{"HorizontalLine",0x02500}, {"boxv",0x02502}, {"boxdr",0x0250C}, {"boxdl",0x02510}, {"boxur",0x02514},
			{"boxul",0x02518}, {"boxvr",0x0251C}, {"boxvl",0x02524}, {"boxhd",0x0252C}, {"boxhu",0x02534},
			{"boxvh",0x0253C}, {"boxH",0x02550}, {"boxV",0x02551}, {"boxdR",0x02552}, {"boxDr",0x02553},
			{"boxDR",0x02554}, {"boxdL",0x02555}, {"boxDl",0x02556}, {"boxDL",0x02557}, {"boxuR",0x02558},
			{"boxUr",0x02559}, {"boxUR",0x0255A}, {"boxuL",0x0255B}, {"boxUl",0x0255C}, {"boxUL",0x0255D},
			{"boxvR",0x0255E}, {"boxVr",0x0255F}, {"boxVR",0x02560}, {"boxvL",0x02561}, {"boxVl",0x02562},
			{"boxVL",0x02563}, {"boxHd",0x02564}, {"boxhD",0x02565}, {"boxHD",0x02566}, {"boxHu",0x02567},
			{"boxhU",0x02568}, {"boxHU",0x02569}, {"boxvH",0x0256A}, {"boxVh",0x0256B}, {"boxVH",0x0256C},
			{"uhblk",0x02580}, {"lhblk",0x02584}, {"block",0x02588}, {"blk14",0x02591}, {"blk12",0x02592},
			{"blk34",0x02593}, {"squ",0x025A1}, {"square",0x025A1}, {"Square",0x025A1}, {"squf",0x025AA},
			{"squarf",0x025AA}, {"blacksquare",0x025AA}, {"FilledVerySmallSquare",0x025AA}, {"EmptyVerySmallSquare",0x025AB}, {"rect",0x025AD},
			{"marker",0x025AE}, {"fltns",0x025B1}, {"xutri",0x025B3}, {"bigtriangleup",0x025B3}, {"utrif",0x025B4},
			{"blacktriangle",0x025B4}, {"utri",0x025B5}, {"triangle",0x025B5}, {"rtrif",0x025B8}, {"blacktriangleright",0x025B8},
			{"rtri",0x025B9}, {"triangleright",0x025B9}, {"xdtri",0x025BD}, {"bigtriangledown",0x025BD}, {"dtrif",0x025BE},
			{"blacktriangledown",0x025BE}, {"dtri",0x025BF}, {"triangledown",0x025BF}, {"ltrif",0x025C2}, {"blacktriangleleft",0x025C2},
			{"ltri",0x025C3}, {"triangleleft",0x025C3}, {"loz",0x025CA}, {"lozenge",0x025CA}, {"cir",0x025CB},
			{"tridot",0x025EC}, {"xcirc",0x025EF}, {"bigcirc",0x025EF}, {"ultri",0x025F8}, {"urtri",0x025F9},
			{"lltri",0x025FA}, {"EmptySmallSquare",0x025FB}, {"FilledSmallSquare",0x025FC}, {"starf",0x02605}, {"bigstar",0x02605},
			{"star",0x02606}, {"phone",0x0260E}, {"female",0x02640}, {"male",0x02642}, {"spades",0x02660},
			{"spadesuit",0x02660}, {"clubs",0x02663}, {"clubsuit",0x02663}, {"hearts",0x02665}, {"heartsuit",0x02665},
			{"diams",0x02666}, {"diamondsuit",0x02666}, {"sung",0x0266A}, {"flat",0x0266D}, {"natur",0x0266E},
			{"natural",0x0266E}, {"sharp",0x0266F}, {"check",0x02713}, {"checkmark",0x02713}, {"cross",0x02717},
			{"malt",0x02720}, {"maltese",0x02720}, {"sext",0x02736}, {"VerticalSeparator",0x02758}, {"lbbrk",0x02772},
			{"rbbrk",0x02773}, {"lobrk",0x027E6}, {"LeftDoubleBracket",0x027E6}, {"robrk",0x027E7}, {"RightDoubleBracket",0x027E7},
			{"lang",0x027E8}, {"LeftAngleBracket",0x027E8}, {"langle",0x027E8}, {"rang",0x027E9}, {"RightAngleBracket",0x027E9},
			{"rangle",0x027E9}, {"Lang",0x027EA}, {"Rang",0x027EB}, {"loang",0x027EC}, {"roang",0x027ED},
			{"xlarr",0x027F5}, {"longleftarrow",0x027F5}, {"LongLeftArrow",0x027F5}, {"xrarr",0x027F6}, {"longrightarrow",0x027F6},
			{"LongRightArrow",0x027F6}, {"xharr",0x027F7}, {"longleftrightarrow",0x027F7}, {"LongLeftRightArrow",0x027F7}, {"xlArr",0x027F8},
			{"Longleftarrow",0x027F8}, {"DoubleLongLeftArrow",0x027F8}, {"xrArr",0x027F9}, {"Longrightarrow",0x027F9}, {"DoubleLongRightArrow",0x027F9},
			{"xhArr",0x027FA}, {"Longleftrightarrow",0x027FA}, {"DoubleLongLeftRightArrow",0x027FA}, {"xmap",0x027FC}, {"longmapsto",0x027FC},
			{"dzigrarr",0x027FF}, {"nvlArr",0x02902}, {"nvrArr",0x02903}, {"nvHarr",0x02904}, {"Map",0x02905},
			{"lbarr",0x0290C}, {"rbarr",0x0290D}, {"bkarow",0x0290D}, {"lBarr",0x0290E}, {"rBarr",0x0290F},
			{"dbkarow",0x0290F}, {"RBarr",0x02910}, {"drbkarow",0x02910}, {"DDotrahd",0x02911}, {"UpArrowBar",0x02912},
			{"DownArrowBar",0x02913}, {"Rarrtl",0x02916}, {"latail",0x02919}, {"ratail",0x0291A}, {"lAtail",0x0291B},
			{"rAtail",0x0291C}, {"larrfs",0x0291D}, {"rarrfs",0x0291E}, {"larrbfs",0x0291F}, {"rarrbfs",0x02920},
			{"nwarhk",0x02923}, {"nearhk",0x02924}, {"searhk",0x02925}, {"hksearow",0x02925}, {"swarhk",0x02926},
			{"hkswarow",0x02926}, {"nwnear",0x02927}, {"nesear",0x02928}, {"toea",0x02928}, {"seswar",0x02929},
			{"tosa",0x02929}, {"swnwar",0x0292A}, {"rarrc",0x02933}, {"cudarrr",0x02935}, {"ldca",0x02936},
			{"rdca",0x02937}, {"cudarrl",0x02938}, {"larrpl",0x02939}, {"curarrm",0x0293C}, {"cularrp",0x0293D},
			{"rarrpl",0x02945}, {"harrcir",0x02948}, {"Uarrocir",0x02949}, {"lurdshar",0x0294A}, {"ldrushar",0x0294B},
			{"LeftRightVector",0x0294E}, {"RightUpDownVector",0x0294F}, {"DownLeftRightVector",0x02950}, {"LeftUpDownVector",0x02951}, {"LeftVectorBar",0x02952},
			{"RightVectorBar",0x02953}, {"RightUpVectorBar",0x02954}, {"RightDownVectorBar",0x02955}, {"DownLeftVectorBar",0x02956}, {"DownRightVectorBar",0x02957},
			{"LeftUpVectorBar",0x02958}, {"LeftDownVectorBar",0x02959}, {"LeftTeeVector",0x0295A}, {"RightTeeVector",0x0295B}, {"RightUpTeeVector",0x0295C},
			{"RightDownTeeVector",0x0295D}, {"DownLeftTeeVector",0x0295E}, {"DownRightTeeVector",0x0295F}, {"LeftUpTeeVector",0x02960}, {"LeftDownTeeVector",0x02961},
			{"lHar",0x02962}, {"uHar",0x02963}, {"rHar",0x02964}, {"dHar",0x02965}, {"luruhar",0x02966},
			{"ldrdhar",0x02967}, {"ruluhar",0x02968}, {"rdldhar",0x02969}, {"lharul",0x0296A}, {"llhard",0x0296B},
			{"rharul",0x0296C}, {"lrhard",0x0296D}, {"udhar",0x0296E}, {"UpEquilibrium",0x0296E}, {"duhar",0x0296F},
			{"ReverseUpEquilibrium",0x0296F}, {"RoundImplies",0x02970}, {"erarr",0x02971}, {"simrarr",0x02972}, {"larrsim",0x02973},
			{"rarrsim",0x02974}, {"rarrap",0x02975}, {"ltlarr",0x02976}, {"gtrarr",0x02978}, {"subrarr",0x02979},
			{"suplarr",0x0297B}, {"lfisht",0x0297C}, {"rfisht",0x0297D}, {"ufisht",0x0297E}, {"dfisht",0x0297F},
			{"lopar",0x02985}, {"ropar",0x02986}, {"lbrke",0x0298B}, {"rbrke",0x0298C}, {"lbrkslu",0x0298D},
			{"rbrksld",0x0298E}, {"lbrksld",0x0298F}, {"rbrkslu",0x02990}, {"langd",0x02991}, {"rangd",0x02992},
			{"lparlt",0x02993}, {"rpargt",0x02994}, {"gtlPar",0x02995}, {"ltrPar",0x02996}, {"vzigzag",0x0299A},
			{"vangrt",0x0299C}, {"angrtvbd",0x0299D}, {"ange",0x029A4}, {"range",0x029A5}, {"dwangle",0x029A6},
			{"uwangle",0x029A7}, {"angmsdaa",0x029A8}, {"angmsdab",0x029A9}, {"angmsdac",0x029AA}, {"angmsdad",0x029AB},
			{"angmsdae",0x029AC}, {"angmsdaf",0x029AD}, {"angmsdag",0x029AE}, {"angmsdah",0x029AF}, {"bemptyv",0x029B0},
			{"demptyv",0x029B1}, {"cemptyv",0x029B2}, {"raemptyv",0x029B3}, {"laemptyv",0x029B4}, {"ohbar",0x029B5},
			{"omid",0x029B6}, {"opar",0x029B7}, {"operp",0x029B9}, {"olcross",0x029BB}, {"odsold",0x029BC},
			{"olcir",0x029BE}, {"ofcir",0x029BF}, {"olt",0x029C0}, {"ogt",0x029C1}, {"cirscir",0x029C2},
			{"cirE",0x029C3}, {"solb",0x029C4}, {"bsolb",0x029C5}, {"boxbox",0x029C9}, {"trisb",0x029CD},
			{"rtriltri",0x029CE}, {"LeftTriangleBar",0x029CF}, {"RightTriangleBar",0x029D0}, {"race",0x029DA}, {"iinfin",0x029DC},
			{"infintie",0x029DD}, {"nvinfin",0x029DE}, {"eparsl",0x029E3}, {"smeparsl",0x029E4}, {"eqvparsl",0x029E5},
			{"lozf",0x029EB}, {"blacklozenge",0x029EB}, {"RuleDelayed",0x029F4}, {"dsol",0x029F6}, {"xodot",0x02A00},
			{"bigodot",0x02A00}, {"xoplus",0x02A01}, {"bigoplus",0x02A01}, {"xotime",0x02A02}, {"bigotimes",0x02A02},
			{"xuplus",0x02A04}, {"biguplus",0x02A04}, {"xsqcup",0x02A06}, {"bigsqcup",0x02A06}, {"qint",0x02A0C},
			{"iiiint",0x02A0C}, {"fpartint",0x02A0D}, {"cirfnint",0x02A10}, {"awint",0x02A11}, {"rppolint",0x02A12},
			{"scpolint",0x02A13}, {"npolint",0x02A14}, {"pointint",0x02A15}, {"quatint",0x02A16}, {"intlarhk",0x02A17},
			{"pluscir",0x02A22}, {"plusacir",0x02A23}, {"simplus",0x02A24}, {"plusdu",0x02A25}, {"plussim",0x02A26},
			{"plustwo",0x02A27}, {"mcomma",0x02A29}, {"minusdu",0x02A2A}, {"loplus",0x02A2D}, {"roplus",0x02A2E},
			{"Cross",0x02A2F}, {"timesd",0x02A30}, {"timesbar",0x02A31}, {"smashp",0x02A33}, {"lotimes",0x02A34},
			{"rotimes",0x02A35}, {"otimesas",0x02A36}, {"Otimes",0x02A37}, {"odiv",0x02A38}, {"triplus",0x02A39},
			{"triminus",0x02A3A}, {"tritime",0x02A3B}, {"iprod",0x02A3C}, {"intprod",0x02A3C}, {"amalg",0x02A3F},
			{"capdot",0x02A40}, {"ncup",0x02A42}, {"ncap",0x02A43}, {"capand",0x02A44}, {"cupor",0x02A45},
			{"cupcap",0x02A46}, {"capcup",0x02A47}, {"cupbrcap",0x02A48}, {"capbrcup",0x02A49}, {"cupcup",0x02A4A},
			{"capcap",0x02A4B}, {"ccups",0x02A4C}, {"ccaps",0x02A4D}, {"ccupssm",0x02A50}, {"And",0x02A53},
			{"Or",0x02A54}, {"andand",0x02A55}, {"oror",0x02A56}, {"orslope",0x02A57}, {"andslope",0x02A58},
			{"andv",0x02A5A}, {"orv",0x02A5B}, {"andd",0x02A5C}, {"ord",0x02A5D}, {"wedbar",0x02A5F},
			{"sdote",0x02A66}, {"simdot",0x02A6A}, {"congdot",0x02A6D}, {"easter",0x02A6E}, {"apacir",0x02A6F},
			{"apE",0x02A70}, {"eplus",0x02A71}, {"pluse",0x02A72}, {"Esim",0x02A73}, {"Colone",0x02A74},
			{"Equal",0x02A75}, {"eDDot",0x02A77}, {"ddotseq",0x02A77}, {"equivDD",0x02A78}, {"ltcir",0x02A79},
			{"gtcir",0x02A7A}, {"ltquest",0x02A7B}, {"gtquest",0x02A7C}, {"les",0x02A7D}, {"LessSlantEqual",0x02A7D},
			{"leqslant",0x02A7D}, {"ges",0x02A7E}, {"GreaterSlantEqual",0x02A7E}, {"geqslant",0x02A7E}, {"lesdot",0x02A7F},
			{"gesdot",0x02A80}, {"lesdoto",0x02A81}, {"gesdoto",0x02A82}, {"lesdotor",0x02A83}, {"gesdotol",0x02A84},
			{"lap",0x02A85}, {"lessapprox",0x02A85}, {"gap",0x02A86}, {"gtrapprox",0x02A86}, {"lne",0x02A87},
			{"lneq",0x02A87}, {"gne",0x02A88}, {"gneq",0x02A88}, {"lnap",0x02A89}, {"lnapprox",0x02A89},
			{"gnap",0x02A8A}, {"gnapprox",0x02A8A}, {"lEg",0x02A8B}, {"lesseqqgtr",0x02A8B}, {"gEl",0x02A8C},
			{"gtreqqless",0x02A8C}, {"lsime",0x02A8D}, {"gsime",0x02A8E}, {"lsimg",0x02A8F}, {"gsiml",0x02A90},
			{"lgE",0x02A91}, {"glE",0x02A92}, {"lesges",0x02A93}, {"gesles",0x02A94}, {"els",0x02A95},
			{"eqslantless",0x02A95}, {"egs",0x02A96}, {"eqslantgtr",0x02A96}, {"elsdot",0x02A97}, {"egsdot",0x02A98},
			{"el",0x02A99}, {"eg",0x02A9A}, {"siml",0x02A9D}, {"simg",0x02A9E}, {"simlE",0x02A9F},
			{"simgE",0x02AA0}, {"LessLess",0x02AA1}, {"GreaterGreater",0x02AA2}, {"glj",0x02AA4}, {"gla",0x02AA5},
			{"ltcc",0x02AA6}, {"gtcc",0x02AA7}, {"lescc",0x02AA8}, {"gescc",0x02AA9}, {"smt",0x02AAA},
			{"lat",0x02AAB}, {"smte",0x02AAC}, {"late",0x02AAD}, {"bumpE",0x02AAE}, {"pre",0x02AAF},
			{"preceq",0x02AAF}, {"PrecedesEqual",0x02AAF}, {"sce",0x02AB0}, {"succeq",0x02AB0}, {"SucceedsEqual",0x02AB0},
			{"prE",0x02AB3}, {"scE",0x02AB4}, {"prnE",0x02AB5}, {"precneqq",0x02AB5}, {"scnE",0x02AB6},
			{"succneqq",0x02AB6}, {"prap",0x02AB7}, {"precapprox",0x02AB7}, {"scap",0x02AB8}, {"succapprox",0x02AB8},
			{"prnap",0x02AB9}, {"precnapprox",0x02AB9}, {"scnap",0x02ABA}, {"succnapprox",0x02ABA}, {"Pr",0x02ABB},
			{"Sc",0x02ABC}, {"subdot",0x02ABD}, {"supdot",0x02ABE}, {"subplus",0x02ABF}, {"supplus",0x02AC0},
			{"submult",0x02AC1}, {"supmult",0x02AC2}, {"subedot",0x02AC3}, {"supedot",0x02AC4}, {"subE",0x02AC5},
			{"subseteqq",0x02AC5}, {"supE",0x02AC6}, {"supseteqq",0x02AC6}, {"subsim",0x02AC7}, {"supsim",0x02AC8},
			{"subnE",0x02ACB}, {"subsetneqq",0x02ACB}, {"supnE",0x02ACC}, {"supsetneqq",0x02ACC}, {"csub",0x02ACF},
			{"csup",0x02AD0}, {"csube",0x02AD1}, {"csupe",0x02AD2}, {"subsup",0x02AD3}, {"supsub",0x02AD4},
			{"subsub",0x02AD5}, {"supsup",0x02AD6}, {"suphsub",0x02AD7}, {"supdsub",0x02AD8}, {"forkv",0x02AD9},
			{"topfork",0x02ADA}, {"mlcp",0x02ADB}, {"Dashv",0x02AE4}, {"DoubleLeftTee",0x02AE4}, {"Vdashl",0x02AE6},
			{"Barv",0x02AE7}, {"vBar",0x02AE8}, {"vBarv",0x02AE9}, {"Vbar",0x02AEB}, {"Not",0x02AEC},
			{"bNot",0x02AED}, {"rnmid",0x02AEE}, {"cirmid",0x02AEF}, {"midcir",0x02AF0}, {"topcir",0x02AF1},
			{"nhpar",0x02AF2}, {"parsim",0x02AF3}, {"parsl",0x02AFD}, {"fflig",0x0FB00}, {"filig",0x0FB01},
			{"fllig",0x0FB02}, {"ffilig",0x0FB03}, {"ffllig",0x0FB04}, {"Ascr",0x1D49C}, {"Cscr",0x1D49E},
			{"Dscr",0x1D49F}, {"Gscr",0x1D4A2}, {"Jscr",0x1D4A5}, {"Kscr",0x1D4A6}, {"Nscr",0x1D4A9},
			{"Oscr",0x1D4AA}, {"Pscr",0x1D4AB}, {"Qscr",0x1D4AC}, {"Sscr",0x1D4AE}, {"Tscr",0x1D4AF},
			{"Uscr",0x1D4B0}, {"Vscr",0x1D4B1}, {"Wscr",0x1D4B2}, {"Xscr",0x1D4B3}, {"Yscr",0x1D4B4},
			{"Zscr",0x1D4B5}, {"ascr",0x1D4B6}, {"bscr",0x1D4B7}, {"cscr",0x1D4B8}, {"dscr",0x1D4B9},
			{"fscr",0x1D4BB}, {"hscr",0x1D4BD}, {"iscr",0x1D4BE}, {"jscr",0x1D4BF}, {"kscr",0x1D4C0},
			{"lscr",0x1D4C1}, {"mscr",0x1D4C2}, {"nscr",0x1D4C3}, {"pscr",0x1D4C5}, {"qscr",0x1D4C6},
			{"rscr",0x1D4C7}, {"sscr",0x1D4C8}, {"tscr",0x1D4C9}, {"uscr",0x1D4CA}, {"vscr",0x1D4CB},
			{"wscr",0x1D4CC}, {"xscr",0x1D4CD}, {"yscr",0x1D4CE}, {"zscr",0x1D4CF}, {"Afr",0x1D504},
			{"Bfr",0x1D505}, {"Dfr",0x1D507}, {"Efr",0x1D508}, {"Ffr",0x1D509}, {"Gfr",0x1D50A},
			{"Jfr",0x1D50D}, {"Kfr",0x1D50E}, {"Lfr",0x1D50F}, {"Mfr",0x1D510}, {"Nfr",0x1D511},
			{"Ofr",0x1D512}, {"Pfr",0x1D513}, {"Qfr",0x1D514}, {"Sfr",0x1D516}, {"Tfr",0x1D517},
			{"Ufr",0x1D518}, {"Vfr",0x1D519}, {"Wfr",0x1D51A}, {"Xfr",0x1D51B}, {"Yfr",0x1D51C},
			{"afr",0x1D51E}, {"bfr",0x1D51F}, {"cfr",0x1D520}, {"dfr",0x1D521}, {"efr",0x1D522},
			{"ffr",0x1D523}, {"gfr",0x1D524}, {"hfr",0x1D525}, {"ifr",0x1D526}, {"jfr",0x1D527},
			{"kfr",0x1D528}, {"lfr",0x1D529}, {"mfr",0x1D52A}, {"nfr",0x1D52B}, {"ofr",0x1D52C},
			{"pfr",0x1D52D}, {"qfr",0x1D52E}, {"rfr",0x1D52F}, {"sfr",0x1D530}, {"tfr",0x1D531},
			{"ufr",0x1D532}, {"vfr",0x1D533}, {"wfr",0x1D534}, {"xfr",0x1D535}, {"yfr",0x1D536},
			{"zfr",0x1D537}, {"Aopf",0x1D538}, {"Bopf",0x1D539}, {"Dopf",0x1D53B}, {"Eopf",0x1D53C},
			{"Fopf",0x1D53D}, {"Gopf",0x1D53E}, {"Iopf",0x1D540}, {"Jopf",0x1D541}, {"Kopf",0x1D542},
			{"Lopf",0x1D543}, {"Mopf",0x1D544}, {"Oopf",0x1D546}, {"Sopf",0x1D54A}, {"Topf",0x1D54B},
			{"Uopf",0x1D54C}, {"Vopf",0x1D54D}, {"Wopf",0x1D54E}, {"Xopf",0x1D54F}, {"Yopf",0x1D550},
			{"aopf",0x1D552}, {"bopf",0x1D553}, {"copf",0x1D554}, {"dopf",0x1D555}, {"eopf",0x1D556},
			{"fopf",0x1D557}, {"gopf",0x1D558}, {"hopf",0x1D559}, {"iopf",0x1D55A}, {"jopf",0x1D55B},
			{"kopf",0x1D55C}, {"lopf",0x1D55D}, {"mopf",0x1D55E}, {"nopf",0x1D55F}, {"oopf",0x1D560},
			{"popf",0x1D561}, {"qopf",0x1D562}, {"ropf",0x1D563}, {"sopf",0x1D564}, {"topf",0x1D565},
			{"uopf",0x1D566}, {"vopf",0x1D567}, {"wopf",0x1D568}, {"xopf",0x1D569}, {"yopf",0x1D56A},
			{"zopf",0x1D56B}
		};
	}

	const char *p = s;
	const char *const end = p + sz;
	while (p != end)
	{
		const char *const next = librvng_utf8_next_char(p);
		if (next > end)
		{
			// oops, the string is invalid
			break;
		}
		if (p+4 <= end && p+1==next && *p=='&')
		{
			const char *q = p+1;
			if (q[0]=='#')
			{
				++q;
				unsigned long unicode=0;
				if (std::isdigit(*q))
				{
					for (int i=0; i<6; ++i)
					{
						if (q>=end || !std::isdigit(*q))
							break;
						unicode=10*unicode+(unsigned long)(*(q++)-'0');
					}
				}
				else if (*q=='x' && std::isalnum(q[1]))
				{
					++q;
					for (int i=0; i<6; ++i)
					{
						if (q>=end)
							break;
						if (std::isdigit(*q))
							unicode=16*unicode+(unsigned long)(*(q++)-'0');
						else if (*q>='a' && *q<='f')
							unicode=16*unicode+10+(unsigned long)(*(q++)-'a');
						else if (*q>='A' && *q<='F')
							unicode=16*unicode+10+(unsigned long)(*(q++)-'A');
						else
							break;
					}

				}
				if (q<end && unicode && *q==';')
				{
					appendUnicodeTo(unicode, res);
					p=q+1;
					continue;
				}
			}
			else if (std::isalpha(*q))
			{
				std::string str;
				while (q<end && std::isalnum(*q))
					str+=*q++;
				if (q<end && *q==';' && mXmlToUnicodeMap.find(str)!=mXmlToUnicodeMap.end())
				{
					appendUnicodeTo(mXmlToUnicodeMap.find(str)->second, res);
					p=q+1;
					continue;
				}
			}
		}

		while (p != next)
		{
			res.append(*p);
			++p;
		}
		p = next;
	}
}
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
