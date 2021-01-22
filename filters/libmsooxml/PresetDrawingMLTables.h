/*
 * This file is part of Office 2007 Filters for Calligra
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Lassi Nieminen lassniem@gmail.com
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

QString getPresetTable(const QString& reference)
{
static const QMap<QString, QString> presetTables = {
{ QStringLiteral("{2D5ABB26-0587-4C30-8999-92F81FD0307C}"), QStringLiteral("\
<a:tblStyle styleId=\"{2D5ABB26-0587-4C30-8999-92F81FD0307C}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"tx1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
</a:tblStyle>\
") },
{ QStringLiteral("{3C2FFA5D-87B4-456A-9821-1D502468CF0F}"), QStringLiteral("\
<a:tblStyle styleId=\"{3C2FFA5D-87B4-456A-9821-1D502468CF0F}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"2\">\
<a:schemeClr val=\"accent1\"/>\
</a:fillRef>\
<a:effectRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{284E427A-3D55-4303-BF80-6455036E1DE7}"), QStringLiteral("\
<a:tblStyle styleId=\"{284E427A-3D55-4303-BF80-6455036E1DE7}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"2\">\
<a:schemeClr val=\"accent2\"/>\
</a:fillRef>\
<a:effectRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{69C7853C-536D-4A76-A0AE-DD22124D55A5}"), QStringLiteral("\
<a:tblStyle styleId=\"{69C7853C-536D-4A76-A0AE-DD22124D55A5}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"2\">\
<a:schemeClr val=\"accent3\"/>\
</a:fillRef>\
<a:effectRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{775DCB02-9BB8-47FD-8907-85C794F793BA}"), QStringLiteral("\
<a:tblStyle styleId=\"{775DCB02-9BB8-47FD-8907-85C794F793BA}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"2\">\
<a:schemeClr val=\"accent4\"/>\
</a:fillRef>\
<a:effectRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{35758FB7-9AC5-4552-8A53-C91805E547FA}"), QStringLiteral("\
<a:tblStyle styleId=\"{35758FB7-9AC5-4552-8A53-C91805E547FA}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"2\">\
<a:schemeClr val=\"accent5\"/>\
</a:fillRef>\
<a:effectRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{08FB837D-C827-4EFA-A057-4D05807E0F7C}"), QStringLiteral("\
<a:tblStyle styleId=\"{08FB837D-C827-4EFA-A057-4D05807E0F7C}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"2\">\
<a:schemeClr val=\"accent6\"/>\
</a:fillRef>\
<a:effectRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:alpha val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{5940675A-B579-460E-94D1-54222C63F5DA}"), QStringLiteral("\
<a:tblStyle styleId=\"{5940675A-B579-460E-94D1-54222C63F5DA}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"tx1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
</a:tblStyle>\
") },
{ QStringLiteral("{D113A9D2-9D6B-4929-AA2D-F23B5EE8CBE7}"), QStringLiteral("\
<a:tblStyle styleId=\"{D113A9D2-9D6B-4929-AA2D-F23B5EE8CBE7}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"3\">\
<a:schemeClr val=\"accent1\"/>\
</a:fillRef>\
<a:effectRef idx=\"3\">\
<a:schemeClr val=\"accent1\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:lnRef idx=\"3\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{18603FDC-E32A-4AB5-989C-0864C3EAD2B8}"), QStringLiteral("\
<a:tblStyle styleId=\"{18603FDC-E32A-4AB5-989C-0864C3EAD2B8}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"3\">\
<a:schemeClr val=\"accent2\"/>\
</a:fillRef>\
<a:effectRef idx=\"3\">\
<a:schemeClr val=\"accent2\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:lnRef idx=\"3\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{306799F8-075E-4A3A-A7F6-7FBC6576F1A4}"), QStringLiteral("\
<a:tblStyle styleId=\"{306799F8-075E-4A3A-A7F6-7FBC6576F1A4}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"3\">\
<a:schemeClr val=\"accent3\"/>\
</a:fillRef>\
<a:effectRef idx=\"3\">\
<a:schemeClr val=\"accent3\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:lnRef idx=\"3\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{E269D01E-BC32-4049-B463-5C60D7B0CCD2}"), QStringLiteral("\
<a:tblStyle styleId=\"{E269D01E-BC32-4049-B463-5C60D7B0CCD2}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"3\">\
<a:schemeClr val=\"accent4\"/>\
</a:fillRef>\
<a:effectRef idx=\"3\">\
<a:schemeClr val=\"accent4\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:lnRef idx=\"3\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{327F97BB-C833-4FB7-BDE5-3F7075034690}"), QStringLiteral("\
<a:tblStyle styleId=\"{327F97BB-C833-4FB7-BDE5-3F7075034690}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"3\">\
<a:schemeClr val=\"accent5\"/>\
</a:fillRef>\
<a:effectRef idx=\"3\">\
<a:schemeClr val=\"accent5\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:lnRef idx=\"3\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{638B1855-1B75-4FBE-930C-398BA8C253C6}"), QStringLiteral("\
<a:tblStyle styleId=\"{638B1855-1B75-4FBE-930C-398BA8C253C6}\" styleName=\"\">\
<a:tblBg>\
<a:fillRef idx=\"3\">\
<a:schemeClr val=\"accent6\"/>\
</a:fillRef>\
<a:effectRef idx=\"3\">\
<a:schemeClr val=\"accent6\"/>\
</a:effectRef>\
</a:tblBg>\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"50000\"/>\
</a:schemeClr>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"2\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:lnRef idx=\"3\">\
<a:schemeClr val=\"lt1\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{9D7B26C5-4107-4FEC-AEDC-1716B250A1EF}"), QStringLiteral("\
<a:tblStyle styleId=\"{9D7B26C5-4107-4FEC-AEDC-1716B250A1EF}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"tx1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"tx1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"tx1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{3B4B98B0-60AC-42C2-AFA5-B58CD77FA1E5}"), QStringLiteral("\
<a:tblStyle styleId=\"{3B4B98B0-60AC-42C2-AFA5-B58CD77FA1E5}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{0E3FDE45-AF77-4B5C-9715-49D594BDF05E}"), QStringLiteral("\
<a:tblStyle styleId=\"{0E3FDE45-AF77-4B5C-9715-49D594BDF05E}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent2\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{C083E6E3-FA7D-4D7B-A595-EF9225AFEA82}"), QStringLiteral("\
<a:tblStyle styleId=\"{C083E6E3-FA7D-4D7B-A595-EF9225AFEA82}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent3\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{D27102A9-8310-4765-A935-A1911B00CA55}"), QStringLiteral("\
<a:tblStyle styleId=\"{D27102A9-8310-4765-A935-A1911B00CA55}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent4\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{5FD0F851-EC5A-4D38-B0AD-8093EC10F338}"), QStringLiteral("\
<a:tblStyle styleId=\"{5FD0F851-EC5A-4D38-B0AD-8093EC10F338}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent5\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{68D230F3-CF80-4859-8CE7-A43EE81993B5}"), QStringLiteral("\
<a:tblStyle styleId=\"{68D230F3-CF80-4859-8CE7-A43EE81993B5}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent6\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{7E9639D4-E3E2-4D34-9284-5A2195B3D0D7}"), QStringLiteral("\
<a:tblStyle styleId=\"{7E9639D4-E3E2-4D34-9284-5A2195B3D0D7}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"tx1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"bg1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fillRef idx=\"1\">\
<a:schemeClr val=\"tx1\"/>\
</a:fillRef>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{69012ECD-51FC-41F1-AA8D-1B2483CD663E}"), QStringLiteral("\
<a:tblStyle styleId=\"{69012ECD-51FC-41F1-AA8D-1B2483CD663E}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"bg1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fillRef idx=\"1\">\
<a:schemeClr val=\"accent1\"/>\
</a:fillRef>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{72833802-FEF1-4C79-8D5D-14CF1EAF98D9}"), QStringLiteral("\
<a:tblStyle styleId=\"{72833802-FEF1-4C79-8D5D-14CF1EAF98D9}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent2\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"bg1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fillRef idx=\"1\">\
<a:schemeClr val=\"accent2\"/>\
</a:fillRef>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{F2DE63D5-997A-4646-A377-4702673A728D}"), QStringLiteral("\
<a:tblStyle styleId=\"{F2DE63D5-997A-4646-A377-4702673A728D}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent3\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"bg1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fillRef idx=\"1\">\
<a:schemeClr val=\"accent3\"/>\
</a:fillRef>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{17292A2E-F333-43FB-9621-5CBBE7FDCDCB}"), QStringLiteral("\
<a:tblStyle styleId=\"{17292A2E-F333-43FB-9621-5CBBE7FDCDCB}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent4\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"bg1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fillRef idx=\"1\">\
<a:schemeClr val=\"accent4\"/>\
</a:fillRef>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{5A111915-BE36-4E01-A7E5-04B1672EAD32}"), QStringLiteral("\
<a:tblStyle styleId=\"{5A111915-BE36-4E01-A7E5-04B1672EAD32}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent5\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"bg1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fillRef idx=\"1\">\
<a:schemeClr val=\"accent5\"/>\
</a:fillRef>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{912C8C85-51F0-491E-9774-3900AFEF0FD7}"), QStringLiteral("\
<a:tblStyle styleId=\"{912C8C85-51F0-491E-9774-3900AFEF0FD7}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent6\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:right>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:top>\
<a:bottom>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:bottom>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:left>\
<a:right>\
<a:lnRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:lnRef>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent6\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fillRef idx=\"1\">\
<a:schemeClr val=\"accent6\"/>\
</a:fillRef>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{616DA210-FB5B-4158-B5E0-FEB733F419BA}"), QStringLiteral("\
<a:tblStyle styleId=\"{616DA210-FB5B-4158-B5E0-FEB733F419BA}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"tx1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"tx1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"tx1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"tx1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{BC89EF96-8CEA-46FF-86C4-4CE0E7609802}"), QStringLiteral("\
<a:tblStyle styleId=\"{BC89EF96-8CEA-46FF-86C4-4CE0E7609802}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{5DA37D80-6434-44D0-A028-1B22A696006F}"), QStringLiteral("\
<a:tblStyle styleId=\"{5DA37D80-6434-44D0-A028-1B22A696006F}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent2\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{8799B23B-EC83-4686-B30A-512413B5E67A}"), QStringLiteral("\
<a:tblStyle styleId=\"{8799B23B-EC83-4686-B30A-512413B5E67A}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent3\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{ED083AE6-46FA-4A59-8FB0-9F97EB10719F}"), QStringLiteral("\
<a:tblStyle styleId=\"{ED083AE6-46FA-4A59-8FB0-9F97EB10719F}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent4\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{BDBED569-4797-4DF1-A0F4-6AAB3CD982D8}"), QStringLiteral("\
<a:tblStyle styleId=\"{BDBED569-4797-4DF1-A0F4-6AAB3CD982D8}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent5\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{E8B1032C-EA38-4F05-BA0D-38AFFFC7BED3}"), QStringLiteral("\
<a:tblStyle styleId=\"{E8B1032C-EA38-4F05-BA0D-38AFFFC7BED3}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent6\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:alpha val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:noFill/>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{793D81CF-94F2-401A-BA57-92F5A7B2D0C5}"), QStringLiteral("\
<a:tblStyle styleId=\"{793D81CF-94F2-401A-BA57-92F5A7B2D0C5}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{B301B821-A1FF-4177-AEE7-76D212191A09}"), QStringLiteral("\
<a:tblStyle styleId=\"{B301B821-A1FF-4177-AEE7-76D212191A09}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{9DCAF9ED-07DC-4A11-8D7F-57B35C25682E}"), QStringLiteral("\
<a:tblStyle styleId=\"{9DCAF9ED-07DC-4A11-8D7F-57B35C25682E}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent2\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{1FECB4D8-DB02-4DC6-A0A2-4F2EBAE1DC90}"), QStringLiteral("\
<a:tblStyle styleId=\"{1FECB4D8-DB02-4DC6-A0A2-4F2EBAE1DC90}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent3\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{1E171933-4619-4E11-9A3F-F7608DF75F80}"), QStringLiteral("\
<a:tblStyle styleId=\"{1E171933-4619-4E11-9A3F-F7608DF75F80}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent4\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{FABFCF23-3B69-468F-B69F-88F6DE6A72F2}"), QStringLiteral("\
<a:tblStyle styleId=\"{FABFCF23-3B69-468F-B69F-88F6DE6A72F2}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent5\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{10A1B5D5-9B99-4C35-A422-299274C87663}"), QStringLiteral("\
<a:tblStyle styleId=\"{10A1B5D5-9B99-4C35-A422-299274C87663}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent6\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{073A0DAA-6AF3-43AB-8588-CEC1D06C72B9}"), QStringLiteral("\
<a:tblStyle styleId=\"{073A0DAA-6AF3-43AB-8588-CEC1D06C72B9}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{5C22544A-7EE6-4342-B048-85BDC9FD1C3A}"), QStringLiteral("\
<a:tblStyle styleId=\"{5C22544A-7EE6-4342-B048-85BDC9FD1C3A}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{21E4AEA4-8DFA-4A89-87EB-49C32662AFE0}"), QStringLiteral("\
<a:tblStyle styleId=\"{21E4AEA4-8DFA-4A89-87EB-49C32662AFE0}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent2\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{F5AB1C69-6EDB-4FF4-983F-18BD219EF322}"), QStringLiteral("\
<a:tblStyle styleId=\"{F5AB1C69-6EDB-4FF4-983F-18BD219EF322}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent3\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{00A15C55-8517-42AA-B614-E9B94910E393}"), QStringLiteral("\
<a:tblStyle styleId=\"{00A15C55-8517-42AA-B614-E9B94910E393}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent4\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{7DF18680-E054-41AD-8BC1-D1AEF772440D}"), QStringLiteral("\
<a:tblStyle styleId=\"{7DF18680-E054-41AD-8BC1-D1AEF772440D}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent5\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{93296810-A885-4BE3-A3E7-6D5BEEA58F35}"), QStringLiteral("\
<a:tblStyle styleId=\"{93296810-A885-4BE3-A3E7-6D5BEEA58F35}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent6\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band2H>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:band2V>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:band2V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:prstClr val=\"black\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"38100\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{8EC20E35-A176-4012-BC5E-935CFFF8708E}"), QStringLiteral("\
<a:tblStyle styleId=\"{8EC20E35-A176-4012-BC5E-935CFFF8708E}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{6E25E649-3F16-4E02-A733-19D2CDBF48F0}"), QStringLiteral("\
<a:tblStyle styleId=\"{6E25E649-3F16-4E02-A733-19D2CDBF48F0}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{85BE263C-DBD7-4A20-BB59-AAB30ACAA65A}"), QStringLiteral("\
<a:tblStyle styleId=\"{85BE263C-DBD7-4A20-BB59-AAB30ACAA65A}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{EB344D84-9AFB-497E-A393-DC336BA19D2E}"), QStringLiteral("\
<a:tblStyle styleId=\"{EB344D84-9AFB-497E-A393-DC336BA19D2E}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{EB9631B5-78F2-41C9-869B-9F39066F8104}"), QStringLiteral("\
<a:tblStyle styleId=\"{EB9631B5-78F2-41C9-869B-9F39066F8104}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{74C1A8A3-306A-4EB7-A6B1-4F7E0EB9C5D6}"), QStringLiteral("\
<a:tblStyle styleId=\"{74C1A8A3-306A-4EB7-A6B1-4F7E0EB9C5D6}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{2A488322-F2BA-4B5B-9748-0D474271808F}"), QStringLiteral("\
<a:tblStyle styleId=\"{2A488322-F2BA-4B5B-9748-0D474271808F}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{D7AC3CCA-C797-4891-BE02-D94E43425B78}"), QStringLiteral("\
<a:tblStyle styleId=\"{D7AC3CCA-C797-4891-BE02-D94E43425B78}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{69CF1AB2-1976-4502-BF36-3FF5EA218861}"), QStringLiteral("\
<a:tblStyle styleId=\"{69CF1AB2-1976-4502-BF36-3FF5EA218861}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{8A107856-5554-42FB-B03E-39F5DBC370BA}"), QStringLiteral("\
<a:tblStyle styleId=\"{8A107856-5554-42FB-B03E-39F5DBC370BA}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent2\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{0505E3EF-67EA-436B-97B2-0124C06EBD24}"), QStringLiteral("\
<a:tblStyle styleId=\"{0505E3EF-67EA-436B-97B2-0124C06EBD24}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent3\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{C4B1156A-380E-4F78-BDF5-A606A8083BF9}"), QStringLiteral("\
<a:tblStyle styleId=\"{C4B1156A-380E-4F78-BDF5-A606A8083BF9}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent4\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{22838BEF-8BB2-4498-84A7-C5851F593DF1}"), QStringLiteral("\
<a:tblStyle styleId=\"{22838BEF-8BB2-4498-84A7-C5851F593DF1}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent5\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{16D9F66E-5EB9-4882-86FB-DCBF35E3C3E4}"), QStringLiteral("\
<a:tblStyle styleId=\"{16D9F66E-5EB9-4882-86FB-DCBF35E3C3E4}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"accent6\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln w=\"12700\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{E8034E78-7F5D-4C2E-B375-FC64B27BC917}"), QStringLiteral("\
<a:tblStyle styleId=\"{E8034E78-7F5D-4C2E-B375-FC64B27BC917}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
<a:nwCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:nwCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{125E5076-3810-47DD-B79F-674D7AD40C01}"), QStringLiteral("\
<a:tblStyle styleId=\"{125E5076-3810-47DD-B79F-674D7AD40C01}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:shade val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
<a:nwCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:nwCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{37CE84F3-28C3-443E-9E96-99CF82512B78}"), QStringLiteral("\
<a:tblStyle styleId=\"{37CE84F3-28C3-443E-9E96-99CF82512B78}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\">\
<a:shade val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
<a:nwCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:nwCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{D03447BB-5D67-496B-8E87-E561075AD55C}"), QStringLiteral("\
<a:tblStyle styleId=\"{D03447BB-5D67-496B-8E87-E561075AD55C}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:shade val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
<a:nwCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:nwCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{E929F9F4-4A8F-4326-A1B4-22849713DDAB}"), QStringLiteral("\
<a:tblStyle styleId=\"{E929F9F4-4A8F-4326-A1B4-22849713DDAB}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\">\
<a:shade val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
<a:nwCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:nwCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{8FD4443E-F989-4FC4-A0C8-D5A2AF1F390B}"), QStringLiteral("\
<a:tblStyle styleId=\"{8FD4443E-F989-4FC4-A0C8-D5A2AF1F390B}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:shade val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
<a:nwCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:nwCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{AF606853-7671-496A-8E4F-DF71F8EC918B}"), QStringLiteral("\
<a:tblStyle styleId=\"{AF606853-7671-496A-8E4F-DF71F8EC918B}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:left>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:right>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:shade val=\"60000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\">\
<a:shade val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:seCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:seCell>\
<a:swCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:swCell>\
<a:firstRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:bottom>\
<a:ln w=\"25400\" cmpd=\"sng\">\
<a:solidFill>\
<a:schemeClr val=\"lt1\"/>\
</a:solidFill>\
</a:ln>\
</a:bottom>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
<a:neCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
</a:tcBdr>\
</a:tcStyle>\
</a:neCell>\
<a:nwCell>\
<a:tcStyle>\
<a:tcBdr>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
</a:tcBdr>\
</a:tcStyle>\
</a:nwCell>\
</a:tblStyle>\
") },
{ QStringLiteral("{5202B0CA-FC54-4496-8BCA-5EF66A818D29}"), QStringLiteral("\
<a:tblStyle styleId=\"{5202B0CA-FC54-4496-8BCA-5EF66A818D29}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{0660B408-B3CF-4A94-85FC-2B1E0A45F4A2}"), QStringLiteral("\
<a:tblStyle styleId=\"{0660B408-B3CF-4A94-85FC-2B1E0A45F4A2}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent1\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent2\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{91EBBBCC-DAD2-459C-BE2E-F6DE35CF9A28}"), QStringLiteral("\
<a:tblStyle styleId=\"{91EBBBCC-DAD2-459C-BE2E-F6DE35CF9A28}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent3\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent4\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") },
{ QStringLiteral("{46F890A9-2807-4EBB-B81D-B2AA78EC7F39}"), QStringLiteral("\
<a:tblStyle styleId=\"{46F890A9-2807-4EBB-B81D-B2AA78EC7F39}\" styleName=\"\">\
<a:wholeTbl>\
<a:tcTxStyle>\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"dk1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr>\
<a:left>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:left>\
<a:right>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:right>\
<a:top>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:top>\
<a:bottom>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:bottom>\
<a:insideH>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideH>\
<a:insideV>\
<a:ln>\
<a:noFill/>\
</a:ln>\
</a:insideV>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:wholeTbl>\
<a:band1H>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1H>\
<a:band1V>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent5\">\
<a:tint val=\"40000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:band1V>\
<a:lastCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:lastCol>\
<a:firstCol>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr/>\
</a:tcStyle>\
</a:firstCol>\
<a:lastRow>\
<a:tcTxStyle b=\"on\"/>\
<a:tcStyle>\
<a:tcBdr>\
<a:top>\
<a:ln w=\"50800\" cmpd=\"dbl\">\
<a:solidFill>\
<a:schemeClr val=\"dk1\"/>\
</a:solidFill>\
</a:ln>\
</a:top>\
</a:tcBdr>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"dk1\">\
<a:tint val=\"20000\"/>\
</a:schemeClr>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:lastRow>\
<a:firstRow>\
<a:tcTxStyle b=\"on\">\
<a:fontRef idx=\"minor\">\
<a:scrgbClr r=\"0\" g=\"0\" b=\"0\"/>\
</a:fontRef>\
<a:schemeClr val=\"lt1\"/>\
</a:tcTxStyle>\
<a:tcStyle>\
<a:tcBdr/>\
<a:fill>\
<a:solidFill>\
<a:schemeClr val=\"accent6\"/>\
</a:solidFill>\
</a:fill>\
</a:tcStyle>\
</a:firstRow>\
</a:tblStyle>\
") }
};
return presetTables.value(reference);
}
