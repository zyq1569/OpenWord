/* This file is part of the KDE project

   Copyright (C) 2006 Jan Hambrecht <jaham@gmx.net>
   Copyright (C) 2006, 2010 Thomas Zander <zander@kde.org>
   Copyright (C) 2008 C. Boemann <cbo@boemann.dk>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#ifndef KOSHAPEBASEDDOCUMENTBASE_H
#define KOSHAPEBASEDDOCUMENTBASE_H

#include "flake_export.h"

#include <QList>

class KoShape;
class KoShapeBasedDocumentBasePrivate;
class KoDocumentResourceManager;
class KUndo2Command;

/**
 * The  KoShapeBasedDocumentBase is an abstract interface that the application's class
 * that owns the shapes should implement. This tends to be the document.
 * @see KoShapeDeleteCommand, KoShapeCreateCommand
 */
class FLAKE_EXPORT KoShapeBasedDocumentBase
{
public:
    KoShapeBasedDocumentBase();
    virtual ~KoShapeBasedDocumentBase();

    /**
     * Add a shape to the shape controller, allowing it to be seen and saved.
     * The controller should add the shape to the ShapeManager instance(s) manually
     * if the shape is one that should be currently shown on screen.
     * @param shape the new shape
     */
    virtual void addShape(KoShape *shape) = 0;

    /**
     * Remove a shape from the shape controllers control, allowing it to be deleted shortly after
     * The controller should remove the shape from all the ShapeManager instance(s) manually
     * @param shape the shape to remove
     */
    virtual void removeShape(KoShape *shape) = 0;

    /**
     * This method gets called after the KoShapeDeleteCommand is executed
     *
     * This passes the KoShapeDeleteCommand as the command parameter. This makes it possible
     * for applications that need to do something after the KoShapeDeleteCommand is done, e.g.
     * adding one commands that need to be executed when a shape was deleted.
     * The default implementation is empty.
     * @param shapes The list of shapes that got removed.
     * @param command The command that was used to remove the shapes from the document.
     */
    virtual void shapesRemoved(const QList<KoShape*> &shapes, KUndo2Command *command);

    /**
     * Return a pointer to the resource manager associated with the
     * shape-set (typically a document). The resource manager contains
     * document wide resources * such as variable managers, the image
     * collection and others.
     */
    virtual KoDocumentResourceManager *resourceManager() const;

private:
    KoShapeBasedDocumentBasePrivate * const d;
};

#endif
