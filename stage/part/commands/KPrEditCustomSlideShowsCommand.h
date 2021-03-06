/* This file is part of the KDE project
* Copyright (C) 2011 Paul Mendez <paulestebanms@gmail.com>
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

#ifndef KPREDITCUSTOMSLIDESHOWSCOMMAND_H
#define KPREDITCUSTOMSLIDESHOWSCOMMAND_H

#include <kundo2command.h>
class KPrDocument;
class KoPAPageBase;

#include <stage_export.h>

class STAGE_TEST_EXPORT KPrEditCustomSlideShowsCommand: public KUndo2Command
{
public:
    KPrEditCustomSlideShowsCommand(KPrDocument *doc, const QString &name, QList<KoPAPageBase *> newCustomShow, KUndo2Command *parent = 0);

    ~KPrEditCustomSlideShowsCommand() override;

    /// redo the command
    void redo() override;
    /// revert the actions done in redo
    void undo() override;

private:
    KPrDocument *m_doc;
    QString m_name;
    QList<KoPAPageBase *> m_newCustomShow;
    QList<KoPAPageBase *> m_oldCustomShow;
};

#endif // KPREDITCUSTOMSLIDESHOWSCOMMAND_H
