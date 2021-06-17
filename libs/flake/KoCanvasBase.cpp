/* This file is part of the KDE project

   SPDX-FileCopyrightText: 2006 Thorsten Zachmann <zachmann@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "KoCanvasBase.h"
#include "KoCanvasResourceManager.h"
#include "KoShapeController.h"
#include "KoCanvasController.h"
#include "KoViewConverter.h"
#include "KoSnapGuide.h"
#include "SnapGuideConfigWidget.h"
#include "KoShapeManager.h"
#include "KoToolProxy.h"
#include "KoSelection.h"

class Q_DECL_HIDDEN KoCanvasBase::Private
{
public:
    Private() : shapeController(0),
        resourceManager(0),
        isResourceManagerShared(false),
        controller(0),
        snapGuide(0)
    {
    }

    ~Private()
    {
        delete shapeController;
        if (!isResourceManagerShared)
        {
            delete resourceManager;
        }
        delete snapGuide;
    }
    KoShapeController *shapeController;
    KoCanvasResourceManager *resourceManager;
    bool isResourceManagerShared;
    KoCanvasController *controller;
    KoSnapGuide *snapGuide;
};

KoCanvasBase::KoCanvasBase(KoShapeBasedDocumentBase *shapeBasedDocument, KoCanvasResourceManager *sharedResourceManager)
    : d(new Private())
{
    d->resourceManager = sharedResourceManager ?
                         sharedResourceManager : new KoCanvasResourceManager();
    d->isResourceManagerShared = sharedResourceManager;

    d->shapeController = new KoShapeController(this, shapeBasedDocument);
    d->snapGuide = new KoSnapGuide(this);
}

KoCanvasBase::~KoCanvasBase()
{
    delete d;
}

QPointF KoCanvasBase::viewToDocument(const QPointF &viewPoint) const
{
    return viewConverter()->viewToDocument(viewPoint - documentOrigin());
}

KoShapeController *KoCanvasBase::shapeController() const
{
    return d->shapeController;
}

void KoCanvasBase::disconnectCanvasObserver(QObject *object)
{
    if (shapeManager())
    {
        shapeManager()->selection()->disconnect(object);
    }
    if (resourceManager())
    {
        resourceManager()->disconnect(object);
    }
    if (shapeManager())
    {
        shapeManager()->disconnect(object);
    }
    if (toolProxy())
    {
        toolProxy()->disconnect(object);
    }
}


KoCanvasResourceManager *KoCanvasBase::resourceManager() const
{
    return d->resourceManager;
}

void KoCanvasBase::ensureVisible(const QRectF &rect)
{
    if (d->controller && d->controller->canvas())
        d->controller->ensureVisible(
            d->controller->canvas()->viewConverter()->documentToView(rect));
}

void KoCanvasBase::setCanvasController(KoCanvasController *controller)
{
    d->controller = controller;
}

KoCanvasController *KoCanvasBase::canvasController() const
{
    return d->controller;
}

void KoCanvasBase::clipToDocument(const KoShape *, QPointF &) const
{
}

KoSnapGuide * KoCanvasBase::snapGuide() const
{
    return d->snapGuide;
}

KoGuidesData * KoCanvasBase::guidesData()
{
    return 0;
}

QWidget *KoCanvasBase::createSnapGuideConfigWidget() const
{
    return new SnapGuideConfigWidget(d->snapGuide);
}
