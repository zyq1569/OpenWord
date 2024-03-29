/* This file is part of the KDE project
 * Copyright (C) 2007 Thomas Zander <zander@kde.org>
 * Copyright (C) 2008 Thorsten Zachmann <zachmann@kde.org>
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

#include "InsertVariableAction_p.h"
#include "KoVariable.h"
#include "KoInlineObjectFactoryBase.h"
#include "KoText.h"

#include <KoCanvasBase.h>
#include <KoShapeController.h>
#include <KoInlineTextObjectManager.h>

#include <kpagedialog.h>

#include <klocalizedstring.h>
#include <QLayout>

InsertVariableAction::InsertVariableAction(KoCanvasBase *base, KoInlineObjectFactoryBase *factory, const KoInlineObjectTemplate &templ)
    : InsertInlineObjectActionBase(base, templ.name)
    , m_factory(factory)
    , m_templateId(templ.id)
    , m_properties(templ.properties)
    , m_templateName(templ.name)
{
}

KoInlineObject *InsertVariableAction::createInlineObject()
{
    KoInlineObject *io = m_factory->createInlineObject(m_properties);
    KoVariable *variable = dynamic_cast<KoVariable*>(io);
    Q_ASSERT(variable);
    KoInlineTextObjectManager *objManager = m_canvas->shapeController()->resourceManager()->resource(KoText::InlineTextObjectManager).value<KoInlineTextObjectManager*>();
    Q_ASSERT(objManager);
    variable->setManager(objManager);
    QWidget *widget = variable->createOptionsWidget();
    if (widget)
    {
        if (widget->layout())
        {
            widget->layout()->setMargin(0);
        }
        KPageDialog *dialog = new KPageDialog(m_canvas->canvasWidget());
        dialog->setWindowTitle(i18n("%1 Options", m_templateName));
        dialog->addPage(widget, QString());
        if (dialog->exec() != KPageDialog::Accepted)
        {
            delete variable;
            variable = 0;
        }
        delete dialog;
    }
    return variable;
}
