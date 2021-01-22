/* This file is part of the KDE project
   Copyright 2012 Brijesh Patel <brijesh3105@gmail.com>

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
   Boston, MA 02110-1301, USA.
*/

#ifndef KCHART_LEGEND_COMMAND
#define KCHART_LEGEND_COMMAND

// Qt
#include <kundo2command.h>

// KoChart
#include "kochart_global.h"


#if 0
namespace KChart
{
class AbstractCoordinatePlane;
class AbstractDiagram;
class Chart;
}
#endif


namespace KoChart
{

class Legend;
class ChartShape;

class LegendCommand : public KUndo2Command
{
public:
    /**
     * Constructor.
     */
    explicit LegendCommand(Legend *legend);

    /**
     * Destructor.
     */
    virtual ~LegendCommand();

    /**
     * Executes the actual operation.
     */
    void redo() override;

    /**
     * Executes the actual operation in reverse order.
     */
    void undo() override;

    void setLegendTitle(const QString &title);
    void setLegendFont(const QFont &font);
    void setLegendFontSize(int size);
    void setLegendExpansion(LegendExpansion expansion);
    /*void setLegendAlignment(Qt::Alignment);
    void setLegendFixedPosition(Position);
    void setLegendBackgroundColor(QColor &color);
    void setLegendFrameColor(QColor &color);*/

private:
    Legend *m_legend;
    QString m_oldTitle;
    QString m_newTitle;
    QFont m_oldFont;
    QFont m_newFont;
    int m_oldFontSize;
    int m_newFontSize;
    LegendExpansion m_oldExpansion;
    LegendExpansion m_newExpansion;
    ChartShape *m_chart;
};

} // namespace KoChart

#endif // KCHART_LEGEND_COMMAND
