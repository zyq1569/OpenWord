/* This file is part of the KDE project
   Copyright (C) 2006-2007 Alfredo Beaumont Sainz <alfredo.beaumont@gmail.com>

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

#ifndef ENCLOSEELEMENT_H
#define ENCLOSEELEMENT_H

#include "RowElement.h"
#include "koformula_export.h"
#include <QPainterPath>

/**
 * @short Implementation of the MathML menclose element
 */
class KOFORMULA_EXPORT EncloseElement : public RowElement {
public:
    /// The standard constructor
    explicit EncloseElement(BasicElement *parent = 0);

    /**
     * Render the element to the given QPainter
     * @param painter The QPainter to paint the element to
     * @param am AttributeManager containing style info
     */
    void paint( QPainter& painter, AttributeManager* am ) override;

    /**
     * Calculate the size of the element and the positions of its children
     * @param am The AttributeManager providing information about attributes values
     */
    void layout( const AttributeManager* am ) override;

    /// @return The element's ElementType
    ElementType elementType() const override;   

private:
    /// The QPainterPath holding what the enclose element has to paint
    QPainterPath m_enclosePath;
};

#endif // ENCLOSEELEMENT_H
