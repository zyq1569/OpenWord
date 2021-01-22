/* This file is part of the KDE project

   Copyright 2010 Johannes Simon <johannes.simon@gmail.com>
   Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
     Contact: Suresh Chande suresh.chande@nokia.com

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

// Own
#include "TestLoadingBase.h"

// Qt
#include <QTextDocument>
#include <QDir>

// Calligra
#include <KoStore.h>
#include <KoOdfReadStore.h>
#include <KoTextShapeDataBase.h>

// KoChart
#include "ChartShape.h"
#include "ChartProxyModel.h"
#include "ChartDocument.h"
#include "PlotArea.h"
#include "Legend.h"
#include "DataSet.h"
#include "TableSource.h"
#include "ChartTableModel.h"
#include "Axis.h"

// KD Chart
#include <KChartAbstractDiagram>
#include <KChartLegend>

using namespace KoChart;

TestLoadingBase::TestLoadingBase()
    : QObject()
{
    // No message boxes please.
    ChartShape::setEnableUserInteraction(false);
    m_chart = new ChartShape(0);
}

void TestLoadingBase::initTestCase()
{
    ChartDocument *document = m_chart->document();

    QDir srcdir(QFINDTESTDATA("doc"));
    QVERIFY(srcdir.exists());

    // Go back up, we only used the cd as a test.
    srcdir.cdUp();

    KoStore *store = KoStore::createStore(srcdir.absolutePath(), KoStore::Read);
    QVERIFY(store->enterDirectory("doc"));

    QString errorMsg;
    KoOdfReadStore odfReadStore(store);
    bool success = odfReadStore.loadAndParse(errorMsg);
    if (!success)
        qDebug() << "Error in odfReadStore.loadAndParse(): " << errorMsg;
    QVERIFY(success);
    QVERIFY(document->loadOdf(odfReadStore));
}

void TestLoadingBase::cleanupTestCase()
{
    delete m_chart;
}

LoadingTests::LoadingTests()
{
}

void LoadingTests::testElementIsVisible(KoShape *element, bool shouldBeVisible)
{
    QVERIFY(element);
    QCOMPARE(element->isVisible(), shouldBeVisible);
}

void LoadingTests::testLegendElements(QStringList labels)
{
    QVERIFY(m_chart->legend());
    QVERIFY(m_chart->legend()->kdLegend());
    QCOMPARE(m_chart->legend()->kdLegend()->datasetCount(),
              (unsigned int)labels.count());

    QList<KChart::AbstractDiagram*> diagrams = m_chart->legend()->kdLegend()->diagrams();
    foreach(KChart::AbstractDiagram *diagram, diagrams) {
        QVERIFY(diagram);
        QStringList diagramLabels = diagram->datasetLabels();
        foreach(const QString &diagramLabel, diagramLabels) {
            QVERIFY(!labels.isEmpty());
            QCOMPARE(diagramLabel, labels.takeFirst());
        }
    }
    QVERIFY(labels.isEmpty());
}

void LoadingTests::testDataSetCellRegions(int dataSetNr,
                                             CellRegion yDataRegion,
                                             CellRegion labelDataRegion,
                                             CellRegion categoryDataRegion,
                                             CellRegion xDataRegion,
                                             CellRegion customDataRegion)
{
    QVERIFY(m_chart->proxyModel());
    QList<DataSet*> dataSets = m_chart->proxyModel()->dataSets();
    QVERIFY(dataSetNr >= 0);
    QVERIFY(dataSets.count() > dataSetNr);
    DataSet *dataSet = dataSets[dataSetNr];
    QVERIFY(dataSet);

    int dataSetSize = 0;
    dataSetSize = qMax(dataSetSize, yDataRegion.cellCount());
    dataSetSize = qMax(dataSetSize, categoryDataRegion.cellCount());
    dataSetSize = qMax(dataSetSize, xDataRegion.cellCount());
    dataSetSize = qMax(dataSetSize, customDataRegion.cellCount());
    QCOMPARE(dataSet->size(), dataSetSize);

    QCOMPARE(dataSet->xDataRegion(),        xDataRegion);
    QCOMPARE(dataSet->yDataRegion(),        yDataRegion);
    QCOMPARE(dataSet->labelDataRegion(),    labelDataRegion);
    QCOMPARE(dataSet->categoryDataRegion(), categoryDataRegion);
    QCOMPARE(dataSet->customDataRegion(),   customDataRegion);
}

void LoadingTests::testHasOnlyInternalTable()
{
    QVERIFY(m_chart->usesInternalModelOnly());
    QVERIFY(internalTable());
}

void LoadingTests::testInternalTableSize(int rowCount, int colCount)
{
    QAbstractItemModel *model = m_chart->internalModel();
    QVERIFY(model);
    QVERIFY(m_chart->tableSource()->get(model));
    QCOMPARE(model->rowCount(), rowCount);
    QCOMPARE(model->columnCount(), colCount);
}

void LoadingTests::testTitleText(const QString &text)
{
    QVERIFY(m_chart->title());
    KoTextShapeDataBase *data = dynamic_cast<KoTextShapeDataBase*>(m_chart->title()->userData());
    QVERIFY(data);
    QVERIFY(data->document());
    QCOMPARE(data->document()->toPlainText(), text);
}

void LoadingTests::testSubTitleText(const QString &text)
{
    QVERIFY(m_chart->subTitle());
    KoTextShapeDataBase *data = dynamic_cast<KoTextShapeDataBase*>(m_chart->subTitle()->userData());
    QVERIFY(data);
    QVERIFY(data->document());
    QCOMPARE(data->document()->toPlainText(), text);
}

void LoadingTests::testFooterText(const QString &text)
{
    QVERIFY(m_chart->footer());
    KoTextShapeDataBase *data = dynamic_cast<KoTextShapeDataBase*>(m_chart->footer()->userData());
    QVERIFY(data);
    QVERIFY(data->document());
    QCOMPARE(data->document()->toPlainText(), text);
}

void LoadingTests::testAxisTitle(Axis *axis, const QString &text)
{
    QVERIFY(axis);
    QVERIFY(axis->title());
    KoTextShapeDataBase *data = dynamic_cast<KoTextShapeDataBase*>(axis->title()->userData());
    QVERIFY(data);
    QVERIFY(data->document());
    QCOMPARE(data->document()->toPlainText(), text);
}

Table *LoadingTests::internalTable()
{
    QAbstractItemModel *internalModel = m_chart->internalModel();
    if (!internalModel)
        return 0;
    return m_chart->tableSource()->get(internalModel);
}

TableSource *LoadingTests::tableSource()
{
    return m_chart->tableSource();
}

namespace QTest {
    template<>
    char *toString(const KoChart::CellRegion &region) {
        return qstrdup(region.toString().toLatin1());
    }
}
