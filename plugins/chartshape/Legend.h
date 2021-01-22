/* This file is part of the KDE project

   Copyright 2007-2008 Johannes Simon <johannes.simon@gmail.com>
   Copyright 2010      Inge Wallin <inge@lysator.liu.se>

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
 * Boston, MA 02110-1301, USA.
*/

#ifndef KCHART_LEGEND_H
#define KCHART_LEGEND_H

// Qt
#include <QObject>

// Calligra
#include <KoShape.h>

// KoChart
#include "ChartShape.h"


namespace KoChart {

class Legend : public QObject, public KoShape
{
    Q_OBJECT

public:
    explicit Legend(ChartShape *parent);
    ~Legend();

    QString title() const;
    QFont font() const;
    qreal fontSize() const;
    QColor fontColor() const;
    QFont titleFont() const;
    qreal titleFontSize() const;
    LegendExpansion expansion() const;
    Qt::Alignment alignment() const;
    Position legendPosition() const;

    void setTitle(const QString &title);
    void setFont(const QFont &font);
    void setFontSize(qreal size);
    void setFontColor(const QColor &color);
    void setTitleFont(const QFont &font);
    void setTitleFontSize(qreal size);
    void setExpansion(LegendExpansion expansion);
    void setAlignment(Qt::Alignment alignment);
    void setLegendPosition(Position position);
    void setSize(const QSizeF &size) override;

    void paint(QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &paintcontext) override;
    void paintPixmap(QPainter &painter, const KoViewConverter &converter);

    bool loadOdf(const KoXmlElement &legendElement, KoShapeLoadingContext &context) override;
    void saveOdf(KoShapeSavingContext &context) const override;

    KChart::Legend *kdLegend() const;

    void rebuild();
    using KoShape::update;
    void update() const override;

Q_SIGNALS:
    void updateConfigWidget();

private Q_SLOTS:
    void slotChartTypeChanged(ChartType chartType );
    void slotKdLegendChanged();

private:
    class Private;
    Private *const d;
};

}

#endif // KCHART_LEGEND_H

