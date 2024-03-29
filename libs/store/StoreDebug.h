/*
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
#ifndef STORE_DEBUG_H_
#define STORE_DEBUG_H_

#include <QDebug>
#include <QLoggingCategory>
#include <kostore_export.h>
#include "logging.h"
extern const KOSTORE_EXPORT QLoggingCategory &STORE_LOG();

#define debugStore qCDebug(STORE_LOG)
#define warnStore qCWarning(STORE_LOG)
#define errorStore qCCritical(STORE_LOG)

#endif
