/* This file is part of the KDE project
 * Copyright (C) 2010 Gopalakrishna Bhat A <gopalakbhat@gmail.com>
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

#ifndef KPRPRESENTATIONTOOLEVENTFORWARDER_H
#define KPRPRESENTATIONTOOLEVENTFORWARDER_H

#include <QWidget>

class KoPACanvasBase;

class KPrPresentationToolEventForwarder : public QWidget
{
    Q_OBJECT

public:
    explicit KPrPresentationToolEventForwarder(KoPACanvasBase *canvas);
    ~KPrPresentationToolEventForwarder() override;

    void receiveMousePressEvent(QMouseEvent *event);
    void receiveMouseMoveEvent(QMouseEvent *event);
    void receiveMouseReleaseEvent(QMouseEvent *event);
};

#endif
