/*
    Copyright (c) 2007 Sven Langkamp <sven.langkamp@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef KOSTOPGRADIENT_H
#define KOSTOPGRADIENT_H

#include <QPair>
#include <QGradient>

#include "KoColor.h"
#include "KoAbstractGradient.h"
#include "KoResource.h"
#include <pigment_export.h>


typedef QPair<qreal, KoColor> KoGradientStop;

/**
 * Resource for colorstop based gradients like Karbon gradients and SVG gradients
 */
class PIGMENTCMS_EXPORT KoStopGradient : public KoAbstractGradient
{

public:
    explicit KoStopGradient(const QString &filename);
    ~KoStopGradient() override;

    KoAbstractGradient* clone() const override;

    bool load() override;
    bool loadFromDevice(QIODevice *dev) override;
    bool save() override;
    bool saveToDevice(QIODevice* dev) const override;

    /// reimplemented
    QGradient* toQGradient() const override;

    /// reimplemented
    void colorAt(KoColor&, qreal t) const override;

    /// Creates KoStopGradient from a QGradient
    static KoStopGradient * fromQGradient(QGradient * gradient);
    
    /// Sets the gradient stops
    void setStops(QList<KoGradientStop> stops);
    QList<KoGradientStop> stops() const;

    /// reimplemented
    QString defaultFileExtension() const override;

protected:

    QList<KoGradientStop> m_stops;
    QPointF m_start;
    QPointF m_stop;
    QPointF m_focalPoint;

private:

    mutable KoColor buffer;

private:

    void loadKarbonGradient(QIODevice *file);
    void parseKarbonGradient(const QDomElement& element);

    void loadSvgGradient(QIODevice *file);
    void parseSvgGradient(const QDomElement& element);
    void parseSvgColor(QColor &color, const QString &s);
};

#endif // KOSTOPGRADIENT_H

