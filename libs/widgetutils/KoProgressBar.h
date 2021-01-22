/* This file is part of the KDE project
 * Copyright (C) Boudewijn Rempt <boud@valdyas.org>, (C) 2009
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

#ifndef KOPROGRESSBAR_H
#define KOPROGRESSBAR_H

#include <QProgressBar>
#include <KoProgressProxy.h>
#include "kowidgetutils_export.h"

/**
 * KoProgressBar is a thin wrapper around QProgressBar that also implements
 * the abstract base class KoProgressProxy. Use this class, not QProgressBar
 * to pass to KoProgressUpdater.
 */
class KOWIDGETUTILS_EXPORT KoProgressBar : public QProgressBar, public KoProgressProxy
{
    Q_OBJECT
public:

    explicit KoProgressBar(QWidget *parent = 0);

    ~KoProgressBar() override;

    int maximum() const override;
    void setValue(int value) override;
    void setRange(int minimum, int maximum) override;
    void setFormat(const QString &format) override;

Q_SIGNALS:

    void done();
};

#endif
