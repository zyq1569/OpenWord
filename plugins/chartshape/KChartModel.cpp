/* This file is part of the KDE project

   Copyright 2008 Johannes Simon <johannes.simon@gmail.com>
   Copyright 2009 Inge Wallin    <inge@lysator.liu.se>
   Copyright (C) 2010 Carlos Licea <carlos@kdab.com>
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
#include "KChartModel.h"

// KoChart
#include "DataSet.h"
#include "PlotArea.h"
#include "ChartDebug.h"

// KChart
#include <KChartGlobal>
#include <KChartPieAttributes>
#include <KChartDataValueAttributes>

using namespace KoChart;

/**
 * Method for debugging purposes.
 */
QString roleToString(int role)
{
    switch (role) {
        case Qt::DisplayRole:
            return "Qt::DisplayRole";
        case KChart::DatasetBrushRole:
            return "KChart::DatasetBrushRole";
        case KChart::DatasetPenRole:
            return "KChart::DatasetPenRole";
        case KChart::PieAttributesRole:
            return "KChart::PieAttributesRole";
        case KChart::DataValueLabelAttributesRole:
            return "KChart::DataValueLabelAttributesRole";
        case KChart::ThreeDAttributesRole:
            return "KChart::ThreeDAttributesRole";
        case KChart::LineAttributesRole:
            return "KChart::LineAttributesRole";
        case KChart::ThreeDLineAttributesRole:
            return "KChart::ThreeDLineAttributesRole";
        case KChart::BarAttributesRole:
            return "KChart::BarAttributesRole";
        case KChart::StockBarAttributesRole:
            return "KChart::StockBarAttributesRole";
        case KChart::ThreeDBarAttributesRole:
            return "KChart::ThreeDBarAttributesRole";
        case KChart::ThreeDPieAttributesRole:
            return "KChart::ThreeDPieAttributesRole";
        case KChart::DataHiddenRole:
            return "KChart::DataHiddenRole";
        case KChart::ValueTrackerAttributesRole:
            return "KChart::ValueTrackerAttributesRole";
        case KChart::CommentRole:
            return "KChart::CommentRole";
    }
    return "Unknown DataRole";
}

class KChartModel::Private {
public:
    Private(KChartModel *parent, PlotArea *plotArea);
    ~Private();

    KChartModel *const q;
    PlotArea *const plotArea;

    /**
     * Returns the index of a given dataSet. If it is not present in
     * this model (i.e. not attached, thus not in dataSets), an index
     * is returned before which this dataSet should be inserted.
     */
    int  dataSetIndex(DataSet *dataSet) const;

    /**
     * Returns the cached (!) max size of all data sets in this model.
     */
    int  maxDataSetSize() const;

    /**
     * Calculates the maximum size of all data sets in the passed list.
     */
    int  calcMaxDataSetSize(QList<DataSet*> list) const;

    /**
     * Only calculates the new size for the current data set list,
     * but does not update it.
     */
    int  calcMaxDataSetSize() const;

    /**
     * Returns the first model index a certain data point of a data occupies
     * in this model.
     *
     * Note that dataPointFirstModelIndex(..) == dataPointLastModelIndex(..)
     * in case we have only one data dimension.
     */
    QModelIndex dataPointFirstModelIndex(int dataSetNumber, int index);

    /**
     * Returns the last model index a certain data point of a data occupies
     * in this model.
     */
    QModelIndex dataPointLastModelIndex(int dataSetNumber, int index);

    bool isKnownDataRole(int role) const;

    int             dataDimensions;
    int             biggestDataSetSize;
    QList<DataSet*> dataSets;

    Qt::Orientation dataDirection;
};


KChartModel::Private::Private(KChartModel *parent, PlotArea *_plotArea)
    : q(parent)
    , plotArea(_plotArea)
{
    dataDimensions      = 1;
    dataDirection       = Qt::Vertical;
    biggestDataSetSize  = 0;
}

KChartModel::Private::~Private()
{
}

int KChartModel::Private::maxDataSetSize() const
{
    return biggestDataSetSize;
}

int KChartModel::Private::calcMaxDataSetSize(QList<DataSet*> list) const
{
    int maxSize = 0;
    foreach (DataSet *dataSet, list)
        maxSize = qMax(maxSize, dataSet->size());
    return maxSize;
}

int KChartModel::Private::calcMaxDataSetSize() const
{
    return calcMaxDataSetSize(dataSets);
}

int KChartModel::Private::dataSetIndex(DataSet *dataSet) const
{
    // If data set is not in our list yet, find out where to insert it
    if (!dataSets.contains(dataSet)) {
        for (int i = 0; i < dataSets.size(); i++) {
            if (dataSet->number() < dataSets[i]->number())
                return i;
        }

        return dataSets.size();
    }

    // Otherwise simply return its index
    return dataSets.indexOf(dataSet);
}

QModelIndex KChartModel::Private::dataPointFirstModelIndex(int dataSetNumber, int index)
{
    // Use the first row or column this data set occupies, assuming the data
    // direction is horizontal or vertical, respectively.
    int dataSetRowOrCol = dataSetNumber * dataDimensions;
    if (dataDirection == Qt::Vertical)
        return q->index(index, dataSetRowOrCol);
    return q->index(dataSetRowOrCol, index);
}

QModelIndex KChartModel::Private::dataPointLastModelIndex(int dataSetNumber, int index)
{
    // Use the last row or column this data set occupies, assuming the data
    // direction is horizontal or vertical, respectively.
    int dataSetRowOrCol = (dataSetNumber + 1) * dataDimensions - 1;
    if (dataDirection == Qt::Vertical)
        return q->index(index, dataSetRowOrCol);
    return q->index(dataSetRowOrCol, index);
}


// ================================================================
//                     class KChartModel


KChartModel::KChartModel(PlotArea *plotArea, QObject *parent)
    : QAbstractItemModel(parent),
      d(new Private(this, plotArea))
{
}

KChartModel::~KChartModel()
{
    delete d;
}


void KChartModel::setDataDirection(Qt::Orientation direction)
{
    d->dataDirection = direction;
}

Qt::Orientation KChartModel::dataDirection() const
{
    return d->dataDirection;
}

Qt::Orientation KChartModel::categoryDirection() const
{
    return d->dataDirection == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal;
}

QVariant KChartModel::data(const QModelIndex &index,
                            int role /* = Qt::DisplayRole */) const
{
    if (!index.isValid() ||
         !d->isKnownDataRole(role)) {
        return QVariant();
    }
//     if (!role == Qt::DisplayRole) {qInfo()<<Q_FUNC_INFO<<index.row()<<roleToString(role);}
    int dataSetNumber, section;
    // Offset from the data set's row or column (depending on the data direction).
    // With one data dimension, it's always 0. Otherwise it's 1 for y data, and
    // in all other cases 0 as well.
    // In other words, with one data dimension, there's only y data. With two data
    // dimensions, there's x and y data, and the x data comes before the y data,
    // each data set thus occupying two rows/columns.
    // With three data dimensions there will be
    // x, y and some kind of custom data. Like the size of a bubble in a bubble chart.
    int dataSection;

    if (dataDirection() == Qt::Horizontal) {
        dataSetNumber = index.row() / d->dataDimensions;
        dataSection = index.row() % d->dataDimensions;
        section = index.column();
    } else {
        dataSetNumber = index.column() / d->dataDimensions;
        dataSection = index.column() % d->dataDimensions;
        section = index.row();
    }

    if (dataSetNumber >= d->dataSets.size())
        return QVariant();

    DataSet *dataSet = d->dataSets[dataSetNumber];
    switch (role) {
    case Qt::DisplayRole:
        if (d->dataDimensions > 1 && dataSection == 0)
            return dataSet->xData(section);
        else if (d->dataDimensions > 2 && dataSection == 2)
            return dataSet->customData(section);
        else
            return dataSet->yData(section);
    case KChart::DatasetBrushRole:
        return dataSet->brush(section);
    case KChart::DatasetPenRole:
        return dataSet->pen(section);
    case KChart::PieAttributesRole:
        return QVariant::fromValue(dataSet->pieAttributes(section));
    case KChart::DataValueLabelAttributesRole:
        return QVariant::fromValue(dataSet->dataValueAttributes(section));
    }

    // TODO (Johannes): Support for third data dimension
    // We need to implement zData in Dataset first.

    Q_ASSERT("Error: Known data role wasn't handled.");
    return QVariant();
}


void KChartModel::dataSetChanged(DataSet *dataSet)
{
    Q_ASSERT(d->dataSets.contains(dataSet));
    if (!d->dataSets.contains(dataSet))
        return;

    int dataSetNumber = d->dataSetIndex(dataSet);

    // Header data that belongs to this data set (e.g. label)
    int first = dataSetNumber * dataDimensions();
    int last = first + dataDimensions() - 1;
    emit headerDataChanged(dataDirection(), first, last);
}

void KChartModel::dataSetChanged(DataSet *dataSet, DataRole /*role*/,
                                  int first /* = -1 */, int last /* = -1 */)
{
    Q_ASSERT(d->dataSets.contains(dataSet));
    if (!d->dataSets.contains(dataSet))
        return;

    const int lastIndex = d->biggestDataSetSize - 1;
    // be sure the 'first' and 'last' referenced rows are within our boundaries
    first = qMin(first, lastIndex);
    last = qMin(last, lastIndex);
    // 'first' defaults to -1, which means that all data points changed.
    if (first == -1) {
        first = 0;
        last = lastIndex;
    }
    // 'last' defaults to -1, which means only one column was changed.
    else if (last == -1)
        last = first;
    // 'first' can be negative either cause rowCount()==0 or cause it
    // still contains the default value of -1. In both cases we abort
    // and don't progress the update-request future. Same is true for
    // last which should at this point contain a valid row index too.
    if (first < 0 || last < 0)
        return;
    // be sure we are not dealing with inverse order
    if (last < first)
        qSwap(first, last);

    int dataSetNumber = d->dataSetIndex(dataSet);
    emit dataChanged(d->dataPointFirstModelIndex(dataSetNumber, first),
                     d->dataPointLastModelIndex(dataSetNumber, last));
}

void KChartModel::dataSetSizeChanged(DataSet *dataSet, int newSize)
{
    Q_UNUSED(newSize);

    int dataSetIndex = d->dataSets.indexOf(dataSet);
    if (dataSetIndex < 0) {
        warnChart << "KChartModel::dataSetSizeChanged(): The data set is not assigned to this model.";
        return;
    }

    // Old max data set size is cached.
    const int oldMaxSize = d->maxDataSetSize();
    // Determine new max data set size (the size of dataSet has been changed already)
    const int newMaxSize = d->calcMaxDataSetSize();

    // Columns/rows have been added
    if (newMaxSize > oldMaxSize) {
        if (d->dataDirection == Qt::Horizontal)
            beginInsertColumns(QModelIndex(), oldMaxSize, newMaxSize - 1);
        else
            beginInsertRows(QModelIndex(), oldMaxSize, newMaxSize - 1);

        d->biggestDataSetSize = d->calcMaxDataSetSize();

        if (d->dataDirection == Qt::Horizontal)
            endInsertColumns();
        else
            endInsertRows();
        // Columns/rows have been removed
    } else if (newMaxSize < oldMaxSize) {
        if (d->dataDirection == Qt::Horizontal)
            beginRemoveColumns(QModelIndex(), newMaxSize, oldMaxSize - 1);
        else
            beginRemoveRows(QModelIndex(), newMaxSize, oldMaxSize - 1);

        d->biggestDataSetSize = d->calcMaxDataSetSize();

        if (d->dataDirection == Qt::Horizontal)
            endRemoveColumns();
        else
            endRemoveRows();
    }
}

void KChartModel::slotColumnsInserted(const QModelIndex& parent, int start, int end)
{
    if (d->dataDirection == Qt::Horizontal) {
        beginInsertColumns(parent, start, end);
        endInsertColumns();
    } else {
        beginInsertRows(parent, start, end);
        endInsertRows();
    }
}

bool KChartModel::Private::isKnownDataRole(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case KChart::DatasetPenRole:
    case KChart::DatasetBrushRole:
    case KChart::PieAttributesRole:
    case KChart::DataValueLabelAttributesRole:
        return true;
    }

    return false;
}

QVariant KChartModel::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role /* = Qt::DisplayRole */) const
{
    if (!d->isKnownDataRole(role)) {
        return QVariant();
    }

    if (d->dataSets.isEmpty()) {
        warnChart << "KChartModel::headerData(): Attempting to request header, but model has no datasets assigned to it.";
        return QVariant();
    }

    if (orientation != d->dataDirection) {
        int dataSetNumber = section / d->dataDimensions;
        if (d->dataSets.count() <= dataSetNumber || dataSetNumber < 0) {
            warnChart << "KChartModel::headerData(): trying to get more datasets than we have.";
            return QVariant();
        }

        DataSet *dataSet  = d->dataSets[dataSetNumber];

        switch (role) {
        case Qt::DisplayRole:
            return dataSet->labelData();
        case KChart::DatasetBrushRole:
            return dataSet->brush();
        case KChart::DatasetPenRole:
            return dataSet->pen();
        case KChart::PieAttributesRole:
            return QVariant::fromValue(dataSet->pieAttributes());
        case KChart::DataValueLabelAttributesRole:
            return QVariant::fromValue(dataSet->dataValueAttributes());
        }
    }
    /* else if (orientation == d->dataDirection) { */
    // FIXME: Find a way to *not* use the first data set, but some method
    // to set category data (including category pen and brush) properly
    // (Setter methods in this class?)
    DataSet *dataSet = d->dataSets[0];
    switch (role) {
    case Qt::DisplayRole:
        return dataSet->categoryData(section);
    case KChart::DatasetBrushRole:
        return dataSet->brush(section);
    case KChart::DatasetPenRole:
        return dataSet->pen(section);
    case KChart::PieAttributesRole:
        return QVariant::fromValue(dataSet->pieAttributes(section));
    }
    /* } */

    // Do return something even though we should never get to this point.
    return QVariant();
}

QModelIndex KChartModel::index(int row, int column,
                                 const QModelIndex &parent) const
{
    // Seems following can happen in which case we shouldn't return a
    // QModelIndex with an invalid position cause else other things
    // may go wrong.
    if(row >= rowCount(parent) || column >= columnCount(parent)) {
        return QModelIndex();
    }

    return createIndex(row, column, static_cast<quintptr>(0));
}

QModelIndex KChartModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

int KChartModel::rowCount(const QModelIndex &parent /* = QModelIndex() */) const
{
    Q_UNUSED(parent);

    int rows;
    if (d->dataDirection == Qt::Vertical)
        rows = d->maxDataSetSize();
    else
        rows = d->dataSets.size() * d->dataDimensions;
    return rows;
}

int KChartModel::columnCount(const QModelIndex &parent /* = QModelIndex() */) const
{
    Q_UNUSED(parent);

    int columns;
    if (d->dataDirection == Qt::Vertical) {
        columns = d->dataSets.size() * d->dataDimensions;
    }
    else
        columns = d->maxDataSetSize();

    return columns;
}

void KChartModel::setDataDimensions(int dataDimensions)
{
    d->dataDimensions = dataDimensions;
}

int KChartModel::dataDimensions() const
{
    return d->dataDimensions;
}

void KChartModel::addDataSet(DataSet *dataSet)
{
    if (d->dataSets.contains(dataSet)) {
        warnChart << "KChartModel::addDataSet(): Attempting to insert already-contained data set";
        return;
    }
    dataSet->setKdChartModel(this);

    int dataSetIndex = d->dataSetIndex(dataSet);

    if (!d->dataSets.isEmpty()) {
        const int columnAboutToBeInserted = dataSetIndex * d->dataDimensions;
        if (d->dataDirection == Qt::Vertical) {
            beginInsertColumns(QModelIndex(), columnAboutToBeInserted,
                                columnAboutToBeInserted + d->dataDimensions - 1);
        }
        else
            beginInsertRows(QModelIndex(), columnAboutToBeInserted,
                             columnAboutToBeInserted + d->dataDimensions - 1);
        d->dataSets.insert(dataSetIndex, dataSet);

        if (d->dataDirection == Qt::Vertical)
            endInsertColumns();
        else
            endInsertRows();

        const int dataSetSize = dataSet->size();
        if (dataSetSize > d->maxDataSetSize()) {
            if (d->dataDirection == Qt::Vertical)
                beginInsertRows(QModelIndex(),
                                 d->maxDataSetSize(), dataSetSize - 1);
            else
                beginInsertColumns(QModelIndex(),
                                    d->maxDataSetSize(), dataSetSize - 1);
            d->biggestDataSetSize = d->calcMaxDataSetSize();
            if (d->dataDirection == Qt::Vertical)
                endInsertRows();
            else
                endInsertColumns();
        }
    }
    else {
        // If we had no datasets before, we haven't had a valid
        // structure yet.  Thus, emit the modelReset() signal.
        beginResetModel();
        d->dataSets.append(dataSet);
        d->biggestDataSetSize = d->calcMaxDataSetSize();
        endResetModel();
    }
}

void KChartModel::removeDataSet(DataSet *dataSet, bool silent)
{
    const int dataSetIndex = d->dataSets.indexOf(dataSet);
    if (dataSetIndex < 0)
        return;

    if (silent) {
        d->dataSets.removeAt(dataSetIndex);
        d->biggestDataSetSize = d->calcMaxDataSetSize();
    }
    else {
        // Simulate removing this dataSet without actually doing so
        // in order to calculate new max data set size
        QList<DataSet*> _dataSets(d->dataSets);
        _dataSets.removeAll(dataSet);
        // Cached size
        int oldMaxDataSetSize = d->maxDataSetSize();
        // Max size for new list
        int newMaxDataSetSize = d->calcMaxDataSetSize(_dataSets);

        if (newMaxDataSetSize < oldMaxDataSetSize) {
            if (d->dataDirection == Qt::Horizontal) {
                beginRemoveColumns(QModelIndex(), newMaxDataSetSize, oldMaxDataSetSize - 1);
            } else {
                beginRemoveRows(QModelIndex(), newMaxDataSetSize, oldMaxDataSetSize - 1);
            }
            d->dataSets = _dataSets;
            d->biggestDataSetSize = newMaxDataSetSize;
            if (d->dataDirection == Qt::Horizontal) {
                endRemoveColumns();
            } else {
                endRemoveRows();
            }
        }
        // If the dataSet has been removed above we cannot remove it again.
        // This should only happen when the last dataSet is removed
        if (d->dataSets.contains(dataSet)) {
            int first = dataSetIndex * d->dataDimensions;
            int last = first + d->dataDimensions - 1;
            if (d->dataDirection == Qt::Horizontal) {
                beginRemoveRows(QModelIndex(), first, last);
            } else {
                beginRemoveColumns(QModelIndex(), first, last);
            }
            d->dataSets.removeAt(dataSetIndex);
            if (d->dataDirection == Qt::Horizontal) {
                endRemoveRows();
            } else {
                endRemoveColumns();
            }
        } else {
            Q_ASSERT(d->dataSets.count() == 0);
            // tell consumers that there is nothing left
            beginResetModel();
            endResetModel();
        }
    }
}

QList<DataSet*> KChartModel::dataSets() const
{
    return d->dataSets;
}
