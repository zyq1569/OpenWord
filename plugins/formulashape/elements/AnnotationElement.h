/* This file is part of the KDE project

   Copyright (C) 2010 Inge Wallin <inge@lysator.liu.se>

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

#ifndef ANNOTATIONELEMENT_H
#define ANNOTATIONELEMENT_H

#include "BasicElement.h"
#include "koformula_export.h"

/**
 * @short Implementation of the MathML annotation element
 *
 * Support for annotation elements in MathML. 
 */

class KOFORMULA_EXPORT AnnotationElement : public BasicElement {
public:
    /// The standard constructor
    explicit AnnotationElement(BasicElement *parent = 0);

    void setContent(const QString& content);
    QString content() const;
    
    /// @return The element's ElementType
    ElementType elementType() const override;
    
    bool readMathMLContent(const KoXmlElement& element) override;
    void writeMathMLContent(KoXmlWriter* writer, const QString& ns) const override;
private:
    QString m_content;
};

#endif // ANNOTATIONELEMENT_H
