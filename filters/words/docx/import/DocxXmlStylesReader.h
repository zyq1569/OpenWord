/*
 * This file is part of Office 2007 Filters for Calligra
 *
 * Copyright (C) 2009-2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Suresh Chande suresh.chande@nokia.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifndef DOCXXMLSTYLESREADER_H
#define DOCXXMLSTYLESREADER_H

#include <QMap>

#include "DocxXmlDocumentReader.h"
#include <MsooXmlDrawingTableStyle.h>

#include <KoGenStyle.h>
#include <KoCharacterStyle.h>

//! A class reading MSOOXML DOCX markup - styles.xml part.
/*! @todo generalize for other MSOOXML subformats.
 */
class DocxXmlStylesReader : public DocxXmlDocumentReader
{
public:
    explicit DocxXmlStylesReader(KoOdfWriters *writers);

    ~DocxXmlStylesReader() override;

    //! Reads/parses the file. The output goes mainly to KoGenStyles* KoOdfWriters::mainStyles
    KoFilter::ConversionStatus read(MSOOXML::MsooXmlReaderContext* context = 0) override;

protected:
    KoFilter::ConversionStatus read_docDefaults();
    KoFilter::ConversionStatus read_pPrDefault();
    KoFilter::ConversionStatus read_rPrDefault();
    KoFilter::ConversionStatus read_style();
    KoFilter::ConversionStatus read_name();
    KoFilter::ConversionStatus read_tblStylePr();

    QMap<QByteArray, KoGenStyle*> m_defaultStyles;
    void createDefaultStyle(KoGenStyle::Type type, const char* family);

    QString m_name; //!< set by read_name()

    MSOOXML::DrawingTableStyle* m_currentStyle;

///add openword
protected:
    //KoFilter::ConversionStatus read_basedOn();
    QString m_basedOn; //!add openword

private:
    void init();
//#include <MsooXmlCommonReaderMethods.h>
};

#endif
