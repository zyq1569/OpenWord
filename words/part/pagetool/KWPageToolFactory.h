/* This file is part of the KDE project
 *
 *  Copyright (C) 2008 C. Boemann <cbo@boemann.dk>
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
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KWPAGETOOLFACTORY_H
#define KWPAGETOOLFACTORY_H
#include "words_export.h"
#include <KoToolFactoryBase.h>

/// Factory for the KWPageTool
class WORDS_EXPORT KWPageToolFactory : public KoToolFactoryBase {
public:
    /// constructor
    KWPageToolFactory();
    ~KWPageToolFactory() override;

    KoToolBase* createTool(KoCanvasBase *canvas) override;
};
#endif
