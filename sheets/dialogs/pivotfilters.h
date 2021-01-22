/* This file is part of the KDE project
   Copyright (C) 2012-2013 Jigar Raisinghani <jigarraisinghani@gmail.com>

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

// Local

#ifndef PIVOTFILTERS_H
#define PIVOTFILTERS_H

#include <KoDialog.h>

#include<QtGui>
#include<QString>
#include<QVector>

class QComboBox;

namespace Calligra{
    namespace Sheets{

    class Selection;    
    class PivotFilters : public KoDialog
    
    {
    Q_OBJECT

    public:
      explicit PivotFilters(QWidget* parent,Selection* selection);
      QVector<QString> filterData();
      ~PivotFilters() override;
    private Q_SLOTS:
      void activateBoxes();
      void activateBoxes2();
      void fillValue();
      void fillValue2();
      void fillValue3();

    
    private:
      void selectFields(QComboBox* box);
      class Private;
      Private *const d;
    };
  }//Sheets
}//Calligra
#endif // PIVOTFILTERS_H
