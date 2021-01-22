/* This file is part of the KDE project
 * Copyright (C) 2011 Boudewijn Rempt <boud@valdyas.org>
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
#include "TestKoElementReference.h"

#include <KoElementReference.h>

#include <QTest>
#include <QLoggingCategory>

void TestKoElementReference::initTestCase()
{
    QLoggingCategory::setFilterRules("*.debug=false\n"
        "calligra.lib.store=true");
}

void TestKoElementReference::testElementReference()
{
    KoElementReference ref1;
    KoElementReference ref2;

    QVERIFY(ref1 != ref2);

    KoElementReference ref3(ref1);
    QVERIFY(ref1 == ref3);

    {
        KoElementReference ref4;
        ref3 = ref4;

        QVERIFY(ref3 == ref4);
    }

    QVERIFY(ref3 != ref1);
}

QTEST_MAIN(TestKoElementReference)
