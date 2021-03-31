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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include <librevenge/librevenge.h>

#include <librevenge-stream/librevenge-stream.h>

#include <libwpg/libwpg.h>

namespace
{

int printUsage()
{
	printf("`wpg2svg' converts WordPerfect Graphics images to SVG.\n");
	printf("\n");
	printf("Usage: wpg2svg [OPTION] FILE\n");
	printf("\n");
	printf("Options:\n");
	printf("\t--help                show this help message\n");
	printf("\t--version             show version information and exit\n");
	printf("\n");
	printf("Report bugs to <https://sourceforge.net/p/libwpg/tickets/> or <https://bugs.documentfoundation.org/>.\n");
	return -1;
}

int printVersion()
{
	printf("wpg2svg " VERSION "\n");
	return 0;
}

} // anonymous namespace

int main(int argc, char *argv[])
{
	if (argc < 2)
		return printUsage();

	char *file = nullptr;

	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "--version"))
			return printVersion();
		else if (!file && strncmp(argv[i], "--", 2))
			file = argv[i];
		else
			return printUsage();
	}

	if (!file)
		return printUsage();

	librevenge::RVNGFileStream input(file);

	if (!libwpg::WPGraphics::isSupported(&input))
	{
		std::cerr << "ERROR: Unsupported file format (unsupported version) or file is encrypted!" << std::endl;
		return 1;
	}

	librevenge::RVNGStringVector vec;
	librevenge::RVNGSVGDrawingGenerator generator(vec, "");
	bool result = libwpg::WPGraphics::parse(&input, &generator);
	if (!result || vec.empty() || vec[0].empty())
	{
		std::cerr << "ERROR: SVG Generation failed!" << std::endl;
		return 1;
	}

#if 1
	std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
	std::cout << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"";
	std::cout << " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
#endif
	std::cout << vec[0].cstr() << std::endl;
	return 0;
}
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
