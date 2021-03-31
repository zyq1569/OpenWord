/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpg
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2006 Ariya Hidayat (ariya@kde.org)
 * Copyright (C) 2004 Marc Oude Kotte (marc@solcon.nl)
 * Copyright (C) 2005 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#include "WPGTextDataHandler.h"

namespace
{

static void separateTabsAndInsertText(librevenge::RVNGDrawingInterface *iface, const librevenge::RVNGString &text)
{
	if (!iface || text.empty())
		return;
	librevenge::RVNGString tmpText;
	librevenge::RVNGString::Iter i(text);
	for (i.rewind(); i.next();)
	{
		if (*(i()) == '\t')
		{
			if (!tmpText.empty())
			{
				if (iface)
					iface->insertText(tmpText);
				tmpText.clear();
			}

			if (iface)
				iface->insertTab();
		}
		else if (*(i()) == '\n')
		{
			if (!tmpText.empty())
			{
				if (iface)
					iface->insertText(tmpText);
				tmpText.clear();
			}

			if (iface)
				iface->insertLineBreak();
		}
		else
		{
			tmpText.append(i());
		}
	}
	if (iface && !tmpText.empty())
		iface->insertText(tmpText);
}

static void separateSpacesAndInsertText(librevenge::RVNGDrawingInterface *iface, const librevenge::RVNGString &text)
{
	if (!iface)
		return;
	if (text.empty())
	{
		iface->insertText(text);
		return;
	}
	librevenge::RVNGString tmpText;
	int numConsecutiveSpaces = 0;
	librevenge::RVNGString::Iter i(text);
	for (i.rewind(); i.next();)
	{
		if (*(i()) == ' ')
			numConsecutiveSpaces++;
		else
			numConsecutiveSpaces = 0;

		if (numConsecutiveSpaces > 1)
		{
			if (!tmpText.empty())
			{
				separateTabsAndInsertText(iface, tmpText);
				tmpText.clear();
			}

			if (iface)
				iface->insertSpace();
		}
		else
		{
			tmpText.append(i());
		}
	}
	separateTabsAndInsertText(iface, tmpText);
}

} // anonymous namespace

void WPGTextDataHandler::openParagraph(const librevenge::RVNGPropertyList &propList)
{
	m_painter->openParagraph(propList);
}

void WPGTextDataHandler::closeParagraph()
{
	m_painter->closeParagraph();
}

void WPGTextDataHandler::openSpan(const librevenge::RVNGPropertyList &propList)
{
	m_painter->openSpan(propList);
}

void WPGTextDataHandler::closeSpan()
{
	m_painter->closeSpan();
}

void WPGTextDataHandler::insertTab()
{
	m_painter->insertTab();
}

void WPGTextDataHandler::insertSpace()
{
	m_painter->insertSpace();
}

void WPGTextDataHandler::insertText(const librevenge::RVNGString &text)
{
	separateSpacesAndInsertText(m_painter, text);
}

void WPGTextDataHandler::insertLineBreak()
{
	m_painter->insertLineBreak();
}

void WPGTextDataHandler::openListElement(const librevenge::RVNGPropertyList &propList)
{
	m_painter->openListElement(propList);
}

void WPGTextDataHandler::closeListElement()
{
	m_painter->closeListElement();
}
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
