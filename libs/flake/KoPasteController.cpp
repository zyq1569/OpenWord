/* This file is part of the KDE project
 * Copyright (C) 2006-2007 Thomas Zander <zander@kde.org>
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

#include "KoPasteController_p.h"
#include "KoPasteController.h"

#include <KoCanvasBase.h>
#include <KoToolProxy.h>

#include <FlakeDebug.h>
#include <QAction>

KoPasteController::KoPasteController(KoCanvasBase *canvas, QAction *pasteAction)
    : QObject(pasteAction),
      d(new Private(this, canvas, pasteAction))
{
    //connect(canvas->toolProxy(), SIGNAL(selectionChanged(bool)), this, SLOT(selectionChanged(bool)));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
}

KoPasteController::~KoPasteController()
{
    delete d;
}

//have to include this because of Q_PRIVATE_SLOT
//#include "moc_KoPasteController.cpp"
