/* This file is part of the KDE project
   Copyright 2009 Johannes Simon <johannes.simon@gmail.com>

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

#ifndef SHEETACCESSMODEL_H
#define SHEETACCESSMODEL_H

#include <QStandardItemModel>

#include "Sheet.h"

namespace Calligra
{
namespace Sheets
{

class Damage;
class Map;
class Sheet;

/**
 * @brief Class that can be used by any shape embedded in Calligra Sheets to access sheet data,
 * without the need to link against Calligra Sheets. It is available through the Doc's data center map,
 * or KoShapeLoadingContext::dataCenterMap() in the process of loading a shape from ODF.
 *
 * Essentially, this model is a list of models to access a sheet's data. It contains a single row,
 * and has exactly one sheet model per column. In short, a model containing models.
 *
 * To allow name-based referencing of a sheet's data (e.g. in an ODF-conform cell region like "Table1.A1:B2")
 * each column's header contains the name of the sheet returned by KSpread::Sheet::sheetName() .
 *
 * To access the QAbstractItemModel instance for a sheet's data, take the following code as example:
 * @code
 * QAbstractItemModel *sheetAccessModel = dynamic_cast<QAbstractItemModel*>( dataCenterMap["SheetAccessModel"] );
 * QModelIndex firstSheetIndex = sheetAccessModel->index( 0, 0 );
 * QPointer<QAbstractItemModel> firstSheet = sheetAccessModel->data( firstSheetIndex ).value< QPointer<QAbstractItemModel> >();
 * view->setModel( firstSheet.data() );
 * @endcode
 */
class SheetAccessModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit SheetAccessModel(Map *map);
    ~SheetAccessModel() override;

public Q_SLOTS:
    void slotSheetAdded(Sheet *sheet);
    void slotSheetRemoved(Sheet *sheet);
        void handleDamages(const QList<Damage*> &damages);

private:
    class Private;
    Private * const d;
};

} // namespace Sheets
} // namespace Calligra

#endif
