/* libwpd
 * Copyright (C) 2003-2005 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2003 Marc Maurer (uwog@uwog.net)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef WPDOCUMENT_H
#define WPDOCUMENT_H

/* The "WPD_CONFIDENCE_NONE=0" must not be removed for the type detection to work well */
enum WPDConfidence { WPD_CONFIDENCE_NONE=0, WPD_CONFIDENCE_UNSUPPORTED_ENCRYPTION, WPD_CONFIDENCE_SUPPORTED_ENCRYPTION, WPD_CONFIDENCE_EXCELLENT };
enum WPDResult { WPD_OK, WPD_FILE_ACCESS_ERROR, WPD_PARSE_ERROR, WPD_UNSUPPORTED_ENCRYPTION_ERROR, WPD_PASSWORD_MISSMATCH_ERROR, WPD_OLE_ERROR, WPD_UNKNOWN_ERROR };
enum WPDPasswordMatch { WPD_PASSWORD_MATCH_NONE, WPD_PASSWORD_MATCH_DONTKNOW, WPD_PASSWORD_MATCH_OK };
enum WPDFileFormat { WPD_FILE_FORMAT_WP6, WPD_FILE_FORMAT_WP5, WPD_FILE_FORMAT_WP42, WPD_FILE_FORMAT_WP3, WPD_FILE_FORMAT_WP1, WPD_FILE_FORMAT_UNKNOWN };

class WPXDocumentInterface;
class WPXInputStream;

/**
This class provides all the functions an application would need to parse
WordPerfect documents.
*/

class WPDocument
{
public:
    static WPDConfidence isFileFormatSupported(WPXInputStream *input);
    static WPDPasswordMatch verifyPassword(WPXInputStream *input, const char *password);
    static WPDResult parse(WPXInputStream *input, WPXDocumentInterface *documentInterface, const char *password);
    static WPDResult parseSubDocument(WPXInputStream *input, WPXDocumentInterface *documentInterface, WPDFileFormat fileFormat);
};

#endif /* WPDOCUMENT_H */
