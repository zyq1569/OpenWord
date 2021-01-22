/* This file is part of the KDE project
   Copyright (C) 2012 C. Boemann <cbo@kogmbh.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#include "ChartPart.h"
#include "ChartDocument.h"

#include <KoComponentData.h>

#include <calligraversion.h>

#include <KAboutData>


ChartPart::ChartPart(QObject *parent)
    : KoPart(KoComponentData(KAboutData(QStringLiteral("kochart"), QStringLiteral("KoChart"),
                                        QStringLiteral(CALLIGRA_VERSION_STRING))), parent)
{
}

ChartPart::~ChartPart()
{
}

KoView * ChartPart::createViewInstance(KoDocument *document, QWidget *parent)
{
    Q_UNUSED(document);
    Q_UNUSED(parent);

    return 0;
}

KoMainWindow *ChartPart::createMainWindow()
{
    return new KoMainWindow(CHART_MIME_TYPE, componentData());
}
