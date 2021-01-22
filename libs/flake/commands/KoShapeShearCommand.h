/* This file is part of the KDE project
 * Copyright (C) 2006 Thomas Zander <zander@kde.org>
 * Copyright (C) 2006 Jan Hambrecht <jaham@gmx.net>
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

#ifndef KOSHAPESHEARCOMMAND_H
#define KOSHAPESHEARCOMMAND_H

#include "flake_export.h"

#include <kundo2command.h>
#include <QList>

class KoShape;
class KoShapeShearCommandPrivate;

/// The undo / redo command for shape shearing.
class FLAKE_EXPORT KoShapeShearCommand : public KUndo2Command
{
public:
    /**
     * Command to rotate a selection of shapes.  Note that it just alters the rotated
     * property of those shapes, and nothing more.
     * @param shapes all the shapes that should be rotated
     * @param previousShearXs a list with the same amount of items as shapes with the
     *        old shearX values
     * @param previousShearYs a list with the same amount of items as shapes with the
     *        old shearY values
     * @param newShearXs a list with the same amount of items as shapes with the new values.
     * @param newShearYs a list with the same amount of items as shapes with the new values.
     * @param parent the parent command used for macro commands
     */
    KoShapeShearCommand(const QList<KoShape*> &shapes, const QList<qreal> &previousShearXs, const QList<qreal> &previousShearYs, const QList<qreal> &newShearXs, const QList<qreal> &newShearYs, KUndo2Command *parent = 0);

    ~KoShapeShearCommand() override;
    /// redo the command
    void redo() override;
    /// revert the actions done in redo
    void undo() override;

private:
    KoShapeShearCommandPrivate * const d;
};

#endif
