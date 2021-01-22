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

#ifndef PICTURESHAPECONFIGWIDGET_H
#define PICTURESHAPECONFIGWIDGET_H

#include <KoShapeConfigWidgetBase.h>
#include <QWidget>

class PictureShape;
class KFileWidget;
class KJob;

class PictureShapeConfigWidget : public KoShapeConfigWidgetBase
{
    Q_OBJECT
public:
    PictureShapeConfigWidget();
    ~PictureShapeConfigWidget() override;

    /// reimplemented from KoShapeConfigWidgetBase
    void open(KoShape *shape) override;
    /// reimplemented from KoShapeConfigWidgetBase
    void save() override;
    /// reimplemented from KoShapeConfigWidgetBase
    bool showOnShapeCreate() override;
    /// reimplemented from KoShapeConfigWidgetBase
    bool showOnShapeSelect() override;

private:
    PictureShape *m_shape;
    KFileWidget *m_fileWidget;
};

class PictureShapeLoadWaiter : public QObject
{
    Q_OBJECT
public:
    explicit PictureShapeLoadWaiter(PictureShape *shape) : m_pictureShape(shape) { }

public Q_SLOTS:
    void setImageData(KJob *job);

private:
    PictureShape *m_pictureShape;
};

#endif //PICTURESHAPECONFIGWIDGET_H
