/* This file is part of the KDE project

   Copyright 2011 Boudewijn Rempt <boud@valdyas.org>

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
   Boston, MA 02110-1301, USA.
*/

#include "VectorToolFactory.h"

#include "VectorShape.h"
#include "VectorTool.h"

#include <KoIcon.h>
#include <klocalizedstring.h>


VectorToolFactory::VectorToolFactory()
    : KoToolFactoryBase("VectorToolFactoryId")
{
    setToolTip(i18n("Vector Image (EMF/WMF/SVM/SVG) tool"));
    setIconName(koIconNameNeededWithSubs("a generic vector image icon", "x-shape-vectorimage", "application-x-wmf"));
    setToolType( dynamicToolType() );
    setPriority( 1 );
    setActivationShapeId( VectorShape_SHAPEID );
}

VectorToolFactory::~VectorToolFactory()
{
}

KoToolBase* VectorToolFactory::createTool( KoCanvasBase* canvas )
{
    return new VectorTool( canvas );
}

