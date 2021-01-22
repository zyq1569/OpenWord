/* This file is part of the KDE project
 * Copyright (C) 2006-2010 Thomas Zander <zander@kde.org>
 * Copyright (C) 2010 KO GmbH <boud@kogmbh.com>
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

#ifndef KOTOOLBASE_P_H
#define KOTOOLBASE_P_H

#include "KoDocumentResourceManager.h"
#include "KoCanvasResourceManager.h"
#include "KoCanvasBase.h"
#include "KoShapeController.h"
#include <QMap>
#include <QHash>
#include <QWidget>
#include <QString>
#include <QSet>
#include <QPointer>
#include <string.h> // for the qt version check

class QWidget;
class QAction;
class KoToolBase;
class KoCanvasBase;

class KoToolBasePrivate
{
public:
    KoToolBasePrivate(KoToolBase *qq, KoCanvasBase *canvas_)
        : currentCursor(Qt::ArrowCursor),
        q(qq),
        canvas(canvas_),
        isInTextMode(false)
    {
    }

    ~KoToolBasePrivate()
    {
        foreach(QPointer<QWidget> optionWidget, optionWidgets) {
            if (optionWidget) {
                optionWidget->setParent(0);
                delete optionWidget;
            }
        }
        optionWidgets.clear();
    }

    void connectSignals()
    {
        if (canvas) { // in the case of KoToolManagers dummytool it can be zero :(
            KoCanvasResourceManager * crp = canvas->resourceManager();
            Q_ASSERT_X(crp, "KoToolBase::KoToolBase", "No Canvas KoResourceManager");
            if (crp)
                q->connect(crp, SIGNAL(canvasResourceChanged(int,QVariant)),
                        SLOT(canvasResourceChanged(int,QVariant)));

            // can be 0 in the case of Calligra Sheets
            KoDocumentResourceManager *scrm = canvas->shapeController()->resourceManager();
            if (scrm) {
                q->connect(scrm, SIGNAL(resourceChanged(int,QVariant)),
                        SLOT(documentResourceChanged(int,QVariant)));
            }
        }
    }

    QList<QPointer<QWidget> > optionWidgets; ///< the optionwidgets associated with this tool
    QCursor currentCursor;
    QHash<QString, QAction *> actionCollection;
    QString toolId;
    QList<QAction*> popupActionList;
    QSet<QAction *> readOnlyActions;
    KoToolBase *q;
    KoCanvasBase *canvas; ///< the canvas interface this tool will work for.
    bool isInTextMode;
};

#endif
