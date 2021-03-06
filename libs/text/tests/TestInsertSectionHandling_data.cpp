/* This file is part of the KDE project
 *
 * Copyright (c) 2014-2015 Denis Kuplyakov <dener.kup@gmail.com>
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

void TestKoTextEditor::testInsertSectionHandling_data()
{
    QTest::addColumn<int>("insertPosition");
    QTest::addColumn<int>("neededBlockCount");
    QTest::addColumn< QVector< QVector<QString> > >("needStartings");
    QTest::addColumn< QVector< QVector<QString> > >("needEndings");

    QTest::newRow("Test #0") << 0 << 12
        << (QVector< QVector<QString> >()
        << (QVector<QString>() << "0")
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>() << "1")
        << (QVector<QString>() << "2")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>()))
        << (QVector< QVector<QString> >()
        << (QVector<QString>())
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "2")
        << (QVector<QString>() << "1")
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>() << "0")
        << (QVector<QString>()));
    QTest::newRow("Test #1") << 39 << 12
        << (QVector< QVector<QString> >()
        << (QVector<QString>() << "0")
        << (QVector<QString>() << "1")
        << (QVector<QString>() << "2")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>()))
        << (QVector< QVector<QString> >()
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "2")
        << (QVector<QString>() << "1")
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>())
        << (QVector<QString>() << "New section 6" << "0")
        << (QVector<QString>()));
    QTest::newRow("Test #2") << 40 << 12
        << (QVector< QVector<QString> >()
        << (QVector<QString>() << "0")
        << (QVector<QString>() << "1")
        << (QVector<QString>() << "2")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "New section 6"))
        << (QVector< QVector<QString> >()
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "2")
        << (QVector<QString>() << "1")
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>() << "0")
        << (QVector<QString>())
        << (QVector<QString>() << "New section 6"));
    QTest::newRow("Test #3") << 5 << 12
        << (QVector< QVector<QString> >()
        << (QVector<QString>() << "0")
        << (QVector<QString>() << "1")
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>() << "2")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>()))
        << (QVector< QVector<QString> >()
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>())
        << (QVector<QString>() << "2")
        << (QVector<QString>() << "1")
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>() << "0")
        << (QVector<QString>()));
    QTest::newRow("Test #4") << 8 << 12
        << (QVector< QVector<QString> >()
        << (QVector<QString>() << "0")
        << (QVector<QString>() << "1")
        << (QVector<QString>() << "2")
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>()))
        << (QVector< QVector<QString> >()
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>() << "2")
        << (QVector<QString>() << "1")
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>() << "0")
        << (QVector<QString>()));
    QTest::newRow("Test #5") << 20 << 12
        << (QVector< QVector<QString> >()
        << (QVector<QString>() << "0")
        << (QVector<QString>() << "1")
        << (QVector<QString>() << "2")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>()))
        << (QVector< QVector<QString> >()
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "2")
        << (QVector<QString>() << "1")
        << (QVector<QString>())
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>() << "0")
        << (QVector<QString>()));
    QTest::newRow("Test #6") << 1 << 12
        << (QVector< QVector<QString> >()
        << (QVector<QString>() << "0")
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>() << "1")
        << (QVector<QString>() << "2")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>()))
        << (QVector< QVector<QString> >()
        << (QVector<QString>())
        << (QVector<QString>() << "New section 6")
        << (QVector<QString>())
        << (QVector<QString>())
        << (QVector<QString>() << "2")
        << (QVector<QString>() << "1")
        << (QVector<QString>())
        << (QVector<QString>() << "3")
        << (QVector<QString>())
        << (QVector<QString>() << "4")
        << (QVector<QString>() << "0")
        << (QVector<QString>()));
}
