/* This file is part of the KDE project
 * Copyright (C) 2007 Jan Hambrecht <jaham@gmx.net>
 * Copyright (C) 2007 Thomas Zander <zander@kde.org>
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

#ifndef KOSHAPETRANSFORMCOMMAND_H
#define KOSHAPETRANSFORMCOMMAND_H

#include "flake_export.h"
#include <kundo2command.h>

class KoShape;
class QTransform;

/**
 * A command to transform a selection of shapes with the same transformation.
 */
class FLAKE_EXPORT KoShapeTransformCommand : public KUndo2Command
{
public:

    /**
     * A command to transform a selection of shapes to the new state.
     * Each shape passed has an old state and a new state of transformation passed in.
     * @param shapes all the shapes that should be transformed
     * @param oldState the old shapes transformations
     * @param newState the new shapes transformations
     * @see KoShape::transformation()
     * @see KoShape::setTransformation()
     */
    KoShapeTransformCommand(const QList<KoShape*> &shapes, const QVector<QTransform> &oldState, const QVector<QTransform> &newState, KUndo2Command * parent = 0);
    ~KoShapeTransformCommand() override;
    /// redo the command
    void redo() override;
    /// revert the actions done in redo
    void undo() override;

private:
    class Private;
    Private * const d;
};

#endif // KOSHAPETRANSFORMCOMMAND_H
