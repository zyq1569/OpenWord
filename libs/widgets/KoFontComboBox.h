/*
 * Copyright (c) 2014 Dmitry Kazakov <dimula73@gmail.com>
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
#ifndef _KO_FONT_COMBO_BOX_H_
#define _KO_FONT_COMBO_BOX_H_

#include "kowidgets_export.h"
#include <QFontComboBox>

/**
 * This class is neccessary to work around a suspected bug in QFontComboBox.
 * 
 * When setCurrentFont() is called, QFontComboBox seems to regenerate
 * the list of fonts and resets its model in the process, while the reset signal is blocked.
 * Anyhow, the result is that the QAccessible framework tries to use
 * an invalid index (which it does not check for validity!),
 * and this leads to a crash.
 */
class KOWIDGETS_EXPORT KoFontComboBox : public QFontComboBox
{
    Q_OBJECT
public:
    KoFontComboBox(QWidget *parent = nullptr);

public Q_SLOTS:
    void setCurrentFont(const QFont &font);
};

#endif // _KO_FONT_COMBO_BOX_H_
