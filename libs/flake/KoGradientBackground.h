/* This file is part of the KDE project
 * Copyright (C) 2008 Jan Hambrecht <jaham@gmx.net>
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

#ifndef KOGRADIENTBACKGROUND_H
#define KOGRADIENTBACKGROUND_H

#include "KoShapeBackground.h"
#include "flake_export.h"

#include <QTransform>

class QGradient;
class KoGradientBackgroundPrivate;

/// A gradient shape background
class FLAKE_EXPORT KoGradientBackground : public KoShapeBackground
{
public:
    /**
     * Creates new gradient background from given gradient.
     * The background takes ownership of the given gradient.
     */
    explicit KoGradientBackground(QGradient *gradient, const QTransform &matrix = QTransform());

    /**
     * Create new gradient background from the given gradient.
     * A clone of the given gradient is used.
     */
    explicit KoGradientBackground(const QGradient &gradient, const QTransform &matrix = QTransform());

    /// Destroys the background
    ~KoGradientBackground() override;

    /// Sets the transform matrix
    void setTransform(const QTransform &matrix);

    /// Returns the transform matrix
    QTransform transform() const;

    /**
     * Sets a new gradient.
     * A clone of the given gradient is used.
     */
    void setGradient(const QGradient &gradient);

    /// Returns the gradient
    const QGradient *gradient() const;

    /// reimplemented from KoShapeBackground
    void paint(QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &context, const QPainterPath &fillPath) const override;
    /// reimplemented from KoShapeBackground
    void fillStyle(KoGenStyle &style, KoShapeSavingContext &context) override;
    /// reimplemented from KoShapeBackground
    bool loadStyle(KoOdfLoadingContext &context, const QSizeF &shapeSize) override;

private:
    Q_DECLARE_PRIVATE(KoGradientBackground)
    Q_DISABLE_COPY(KoGradientBackground)
};

#endif // KOGRADIENTBACKGROUND_H
