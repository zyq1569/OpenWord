/* This file is part of the KDE project
 *
 * Copyright (C) 2010 Thorsten Zachmann <zachmann@kde.org>
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

#ifndef KPRFADEOVERCOLORSTRATEGY_H
#define KPRFADEOVERCOLORSTRATEGY_H

#include "pageeffects/KPrPageEffectStrategy.h"

#include <QColor>

class KPrFadeOverColorStrategy : public KPrPageEffectStrategy
{
public:
    KPrFadeOverColorStrategy();
    ~KPrFadeOverColorStrategy() override;

    void setup( const KPrPageEffect::Data &data, QTimeLine &timeLine ) override;

    void paintStep( QPainter &p, int currPos, const KPrPageEffect::Data &data ) override;

    void next( const KPrPageEffect::Data &data ) override;

    void finish(const KPrPageEffect::Data &data) override;

    // reimplemented
    void saveOdfSmilAttributes(KoXmlWriter & xmlWriter) const override;

    // reimplemented
    void saveOdfSmilAttributes(KoGenStyle & style) const override;

    // reimplemented
    void loadOdfSmilAttributes(const KoXmlElement & element) override;

private:
    QColor m_fadeColor;
};

#endif /* KPRFADEOVERCOLORSTRATEGY_H */
