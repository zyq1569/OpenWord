/* This file is part of the KDE project
 * Copyright (C) 2007 Jan Hambrecht <jaham@gmx.net>
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

#ifndef _KARBONBOOLEANCOMMAND_H_
#define _KARBONBOOLEANCOMMAND_H_

#include <karboncommon_export.h>
#include <kundo2command.h>

class KoShapeBasedDocumentBase;
class KoPathShape;

class KARBONCOMMON_EXPORT KarbonBooleanCommand : public KUndo2Command
{
public:
    enum BooleanOperation {
        Intersection, ///< the intersection of A and B
        Subtraction,  ///< the subtraction A - B
        Union,        ///< the union A + B
        Exclusion
    };

    /**
     * Command for doing a boolean operation on two given path shapes.
     * @param controller the controller to used for removing/inserting.
     * @param pathA the first operand
     * @param pathB the second operand
     * @param operation the booelan operation to execute
     * @param parent the parent command used for macro commands
     */
    explicit KarbonBooleanCommand(KoShapeBasedDocumentBase *controller, KoPathShape* pathA, KoPathShape * pathB,
                                  BooleanOperation operation, KUndo2Command *parent = 0);
    ~KarbonBooleanCommand() override;
    /// redo the command
    void redo() override;
    /// revert the actions done in redo
    void undo() override;
private:
    class Private;
    Private * const d;
};

#include <KoShapeContainer.h>
class Q_DECL_HIDDEN KarbonBooleanCommand::Private
{
public:
    Private(KoShapeBasedDocumentBase * c)
            : shapeBasedDocument(c), pathA(0), pathB(0), resultingPath(0)
            , resultParent(0), resultParentCmd(0)
            , operation(Intersection), isExecuted(false)
    {}

    ~Private()
    {
        if (! isExecuted)
            delete resultingPath;
    }

    KoShapeBasedDocumentBase *shapeBasedDocument;
    KoPathShape * pathA;
    KoPathShape * pathB;
    KoPathShape * resultingPath;
    KoShapeContainer * resultParent;
    KUndo2Command * resultParentCmd;
    BooleanOperation operation;
    bool isExecuted;
};
#endif // _KARBONBOOLEANCOMMAND_H_
