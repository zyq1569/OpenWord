/*
 *  Copyright (c) 2007 Cyrille Berger <cberger@cberger.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#ifndef TestColorConversionSystem_H
#define TestColorConversionSystem_H

#include <QObject>
#include <QList>
#include <QString>

struct ModelDepthProfile {
    ModelDepthProfile(const QString& _model, const QString& _depth, const QString& _profile)
            : model(_model), depth(_depth), profile(_profile) {
    }
    QString model;
    QString depth;
    QString profile;
};

class TestColorConversionSystem : public QObject
{
    Q_OBJECT
public:
    TestColorConversionSystem();
private Q_SLOTS:
    void testConnections_data();
    void testConnections();
    void testGoodConnections_data();
    void testGoodConnections();
    void testFailedConnections();
private:
    QList< ModelDepthProfile > listModels;
    int countFail;
};

#endif
