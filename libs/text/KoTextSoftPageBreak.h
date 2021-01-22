/* This file is part of the KDE project
 * Copyright (C) 2011 Thorsten Zachmann <zachmann@kde.org>
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

#ifndef KOTEXTSOFTPAGEBREAK_H
#define KOTEXTSOFTPAGEBREAK_H

#include "KoInlineObject.h"

#include "kotext_export.h"

/**
 * This class defines a soft page break as defined in odf
 * <text:soft-page-break>
 *
 * The class does not have members as it's presence is enough.
 */
class KOTEXT_EXPORT KoTextSoftPageBreak : public KoInlineObject
{
    Q_OBJECT
public:
    KoTextSoftPageBreak();
    ~KoTextSoftPageBreak() override;

    bool loadOdf(const KoXmlElement &element, KoShapeLoadingContext &context) override;

    void saveOdf(KoShapeSavingContext &context) override;

    void updatePosition(const QTextDocument *document,
                                int posInDocument, const QTextCharFormat &format) override;

    void resize(const QTextDocument *document, QTextInlineObject &object,
                        int posInDocument, const QTextCharFormat &format, QPaintDevice *pd) override;

    void paint(QPainter &painter, QPaintDevice *pd, const QTextDocument *document,
                       const QRectF &rect, const QTextInlineObject &object, int posInDocument, const QTextCharFormat &format) override;
};

#endif /* KOTEXTSOFTPAGEBREAK_H */
