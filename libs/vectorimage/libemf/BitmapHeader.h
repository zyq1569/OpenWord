/*
  Copyright 2008 Brad Hards <bradh@frogmouth.net>
  Copyright 2010 Inge Wallin <inge@lysator.liu.se>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either 
  version 2.1 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public 
  License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EMFBITMAPHEADER_H
#define EMFBITMAPHEADER_H


#include <Qt>                   // For qint, etc.

class QDataStream;

/**
 * @file
 *
 * definitions for Device Independent Bitmaps, as used in both WMF and EMF files.
*/



/// Namespace for Enhanced Metafile (EMF) classes

namespace Libemf
{

/**
 * @class BitmapHeader
 *
 * Representation of a bitmap header, including the following formats:
 *  - BitmapInfoHeader [MS-WMF].pdf 2.2.2.3
 *  - BitmapV4Header   [MS-WMF].pdf 2.2.2.4
 *  - BitmapV5Header   [MS-WMF].pdf 2.2.2.5
 */
class BitmapHeader 
{
public:
    typedef enum {
        //BitmapCoreHeader,   Not yet supported
        BitmapInfoHeader,
        BitmapV4Header,
        BitmapV5Header
    } Type;

    /**
     * Constructor
     *
     * The header structure is built from the specified stream.
     *
     * \param stream the data stream to read from.
     * \param size the size of the header. This decides what type it is.
     */
    BitmapHeader( QDataStream &stream, int size );
    ~BitmapHeader();

    /**
       The width of the bitmap, in pixels
    */
    qint32 width() const { return m_width; };

    /**
       The height of the bitmap, in pixels
    */
    qint32 height() const { return m_height; };

    /**
       The number of bits that make up a pixel

       This is an enumerated type - see the BitCount enum
    */
    quint16 bitCount() const { return m_bitCount; };

    /**
       The type of compression used in the image

       This is an enumerated type
    */
    quint32 compression() const { return m_compression; };

//private:
    Type  m_headerType;         /// Which header type that is represented.

    // Data to be found in a BitmapInfoHeader
    quint32 m_headerSize;
    qint32  m_width;
    qint32  m_height;
    quint16 m_planes;
    quint16 m_bitCount;
    quint32 m_compression;
    quint32 m_imageSize;
    qint32  m_xPelsPerMeter;
    qint32  m_yPelsPerMeter;
    quint32 m_colorUsed;
    quint32 m_colorImportant;

    // Additional data to be found in a BitmapV4Header
    quint32 m_redMask;
    quint32 m_greenMask;
    quint32 m_blueMask;
    quint32 m_alphaMask;
    quint32 m_colorSpaceType;
    quint32 m_endpoints[9];     // Actually a CIEXYZTriple
    qint32  m_gammaRed;
    qint32  m_gammaGreen;
    qint32  m_gammaBlue;

    // Additional data to be found in a BitmapV5Header
    quint32 m_intent;
    quint32 m_profileData;
    quint32 m_profileSize;
    quint32 m_reserved;
};
 


} // namespace Libemf

#endif
