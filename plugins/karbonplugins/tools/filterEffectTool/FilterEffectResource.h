/* This file is part of the KDE project
 * Copyright (c) 2009 Jan Hambrecht <jaham@gmx.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef FILTEREFFECTRESOURCE_H
#define FILTEREFFECTRESOURCE_H

#include "KoResource.h"
#include <KoXmlReader.h>

class KoFilterEffectStack;

class FilterEffectResource : public KoResource
{
public:
    explicit FilterEffectResource(const QString &filename);

    /// reimplemented from KoResource
    bool load() override;

    /// reimplemented from KoResource
    bool loadFromDevice(QIODevice *dev) override;

    /// reimplemented from KoResource
    bool save() override;

    /// reimplemented from KoResource
    bool saveToDevice(QIODevice* dev) const override;

    /// reimplemented from KoResource
    QString defaultFileExtension() const override;

    /// Creates resource from given filter effect stack
    static FilterEffectResource * fromFilterEffectStack(KoFilterEffectStack *filterStack);

    /// Creates a new filter stack from this filter resource
    KoFilterEffectStack * toFilterStack() const;
protected:
    QByteArray generateMD5() const override;
private:
    QDomDocument m_data;
};

#endif // FILTEREFFECTRESOURCE_H
