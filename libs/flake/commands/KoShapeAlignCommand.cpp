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

#include "KoShapeAlignCommand.h"
#include "KoShape.h"
#include "KoShapeGroup.h"
#include "commands/KoShapeMoveCommand.h"

#include <klocalizedstring.h>
// #include <FlakeDebug.h>

class Q_DECL_HIDDEN KoShapeAlignCommand::Private
{
public:
    Private() : command(0) {}
    ~Private() {
        delete command;
    }
    KoShapeMoveCommand *command;
};

KoShapeAlignCommand::KoShapeAlignCommand(const QList<KoShape*> &shapes, Align align, const QRectF &boundingRect, KUndo2Command *parent)
        : KUndo2Command(parent),
        d(new Private())
{
    QVector<QPointF> previousPositions;
    QVector<QPointF> newPositions;
    QPointF position;
    QPointF delta;
    QRectF bRect;
    const int shapesCount = shapes.count();
    previousPositions.reserve(shapesCount);
    newPositions.reserve(shapesCount);
    foreach(KoShape *shape, shapes) {
//   if (dynamic_cast<KoShapeGroup*> (shape))
//       debugFlake <<"Found Group";
//   else if (dynamic_cast<KoShapeContainer*> (shape))
//       debugFlake <<"Found Container";
//   else
//       debugFlake <<"Found shape";
        position = shape->position();
        previousPositions  << position;
        bRect = shape->boundingRect();
        switch (align) {
        case HorizontalLeftAlignment:
            delta = QPointF(boundingRect.left(), bRect.y()) - bRect.topLeft();
            break;
        case HorizontalCenterAlignment:
            delta = QPointF(boundingRect.center().x() - bRect.width() / 2, bRect.y()) - bRect.topLeft();
            break;
        case HorizontalRightAlignment:
            delta = QPointF(boundingRect.right() - bRect.width(), bRect.y()) - bRect.topLeft();
            break;
        case VerticalTopAlignment:
            delta = QPointF(bRect.x(), boundingRect.top()) - bRect.topLeft();
            break;
        case VerticalCenterAlignment:
            delta = QPointF(bRect.x(), boundingRect.center().y() - bRect.height() / 2) - bRect.topLeft();
            break;
        case VerticalBottomAlignment:
            delta = QPointF(bRect.x(), boundingRect.bottom() - bRect.height()) - bRect.topLeft();
            break;
        };
        newPositions  << position + delta;
//debugFlake <<"-> moving" <<  position.x() <<"," << position.y() <<" to" <<
//        (position + delta).x() << ", " << (position+delta).y() << endl;
    }
    d->command = new KoShapeMoveCommand(shapes, previousPositions, newPositions);

    setText(kundo2_i18n("Align shapes"));
}

KoShapeAlignCommand::~KoShapeAlignCommand()
{
    delete d;
}

void KoShapeAlignCommand::redo()
{
    KUndo2Command::redo();
    d->command->redo();
}

void KoShapeAlignCommand::undo()
{
    KUndo2Command::undo();
    d->command->undo();
}
