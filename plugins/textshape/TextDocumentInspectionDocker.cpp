/* This file is part of the Calligra project, made within the KDE community.
 *
 * Copyright (C) 2013 Friedrich W. H. Kossebau <friedrich@kogmbh.com>
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

#include "TextDocumentInspectionDocker.h"

#include "TextDocumentStructureModel.h"
#include "TextShape.h"
#include "KoTextShapeData.h"
//
#include <KoShapeManager.h>
#include <KoCanvasBase.h>
#include <KoSelection.h>
// Qt
#include <QDebug>
#include <QTreeView>


const int MsecsThresholdForMergingCommands = 2000;


TextDocumentInspectionDocker::TextDocumentInspectionDocker(QWidget * parent)
    : QDockWidget(parent)
    , m_canvas(0)
    , m_mainWidget(new QTreeView(this))
    , m_textDocumentStructureModel(new TextDocumentStructureModel(this))
{
    setWindowTitle(QLatin1String("TextDocument Inspector"));
    setWidget(m_mainWidget);

//     m_mainWidget->setRootIsDecorated(false);
    m_mainWidget->setAllColumnsShowFocus(true);
    m_mainWidget->setUniformRowHeights(true);
    m_mainWidget->setAlternatingRowColors(true);
    m_mainWidget->setModel(m_textDocumentStructureModel);
}

TextDocumentInspectionDocker::~TextDocumentInspectionDocker()
{
}


void TextDocumentInspectionDocker::setCanvas(KoCanvasBase *canvas)
{
    setEnabled(canvas != 0);

    if (m_canvas) {
        m_canvas->disconnectCanvasObserver(this);
    }

    m_canvas = canvas;
    if (! m_canvas) {
        m_textDocumentStructureModel->setTextDocument(0);
        return;
    }

    connect(m_canvas->shapeManager(), SIGNAL(selectionChanged()),
            this, SLOT(onShapeSelectionChanged()));

    onShapeSelectionChanged();
}

void TextDocumentInspectionDocker::unsetCanvas()
{
    setEnabled(false);
    m_textDocumentStructureModel->setTextDocument(0);
    m_canvas = 0;
}

void TextDocumentInspectionDocker::onShapeSelectionChanged()
{
    QTextDocument* textDocument = 0;

    // TODO: big fail: shapeManager of a canvas still emits signals after unsetCanvas()
    // was called on us. And at least by the current API dox there is no way in unsetCanvas()
    // to get the shapeManager anymore, as "it's dead".
    // So we need to guard us here, this can be called when we officially are not
    // connected to any canvas.
    // Cmp. StrokeDocker::selectionChanged()
    if (m_canvas) {
        KoShape *shape = m_canvas->shapeManager()->selection()->firstSelectedShape();
        if (shape) {
            TextShape *textShape = dynamic_cast<TextShape*>(shape);
            if (textShape) {
                textDocument = textShape->textShapeData()->document();
            }
        }
    }

    m_textDocumentStructureModel->setTextDocument(textDocument);
    m_mainWidget->expandToDepth(1);
}
