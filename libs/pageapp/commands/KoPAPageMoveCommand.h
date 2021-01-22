/* This file is part of the KDE project
 * Copyright ( C ) 2007 Thorsten Zachmann <zachmann@kde.org>
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

#ifndef KOPAPAGEMOVECOMMAND_H
#define KOPAPAGEMOVECOMMAND_H

#include <QMap>
#include <kundo2command.h>

#include "kopageapp_export.h"

class KoPADocument;
class KoPAPageBase;

/**
 * Command for moving a page in a document
 */
class KOPAGEAPP_TEST_EXPORT KoPAPageMoveCommand : public KUndo2Command
{
public:
    KoPAPageMoveCommand( KoPADocument *document, KoPAPageBase *page, KoPAPageBase *after, KUndo2Command *parent = 0 );
    KoPAPageMoveCommand( KoPADocument *document, const QList<KoPAPageBase *> &pages, KoPAPageBase *after, KUndo2Command *parent = 0 );
    void init( const QList<KoPAPageBase *> &pages );
    ~KoPAPageMoveCommand() override;

    /// redo the command
    void redo() override;
    /// revert the actions done in redo
    void undo() override;

private:
    KoPADocument * m_document;
    QMap<int, KoPAPageBase *> m_pageIndices;
    KoPAPageBase *m_after;
};

#endif // KOPAPAGEMOVECOMMAND_H

