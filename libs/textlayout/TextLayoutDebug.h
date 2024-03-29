﻿/*
 *  Copyright (c) 2015 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef TEXT_LAYOUT_DEBUG_H_
#define TEXT_LAYOUT_DEBUG_H_

#include <QDebug>
#include <QLoggingCategory>
#include <kotextlayout_export.h>

#include "logging.h"

extern const KOTEXTLAYOUT_EXPORT QLoggingCategory &TEXT_LAYOUT_LOG();

#define debugTextLayout qCDebug(TEXT_LAYOUT_LOG)
#define warnTextLayout qCWarning(TEXT_LAYOUT_LOG)
#define errorTextLayout qCCritical(TEXT_LAYOUT_LOG)

#endif
