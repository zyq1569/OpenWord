/* This file is part of the KDE project
   Copyright 2007 Stefan Nikolaus <stefan.nikolaus@kdemail.net>

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

#ifndef KCHART_CHART_TYPE_COMMAND
#define KCHART_CHART_TYPE_COMMAND

// Qt
#include <kundo2command.h>

// KoChart
#include "kochart_global.h"
//#include "ChartShape.h"


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

class ChartShape;

/**
 * Chart type replacement command.
 */
class ChartTypeCommand : public KUndo2Command
{
public:
    /**
     * Constructor.
     */
    explicit ChartTypeCommand(ChartShape *chart);

    /**
     * Destructor.
     */
    virtual ~ChartTypeCommand();

    /**
     * Executes the actual operation.
     */
    void redo() override;

    /**
     * Executes the actual operation in reverse order.
     */
    void undo() override;

    /**
     * Sets the new chart type.
     */
    void setChartType(ChartType type, ChartSubtype subType);


private:
    ChartShape                        *m_chart;
    //KChart::Chart                    *m_chart;
    ChartType                       m_oldType;
    ChartType                       m_newType;
    ChartSubtype                    m_oldSubtype;
    ChartSubtype                    m_newSubtype;
    //KChart::AbstractCoordinatePlane  *m_oldCoordinatePlane;
    //KChart::AbstractDiagram          *m_oldDiagram;
};

} // namespace KoChart

#endif // KCHART_CHART_TYPE_COMMAND
