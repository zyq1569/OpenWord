/*
 * This file is part of the KDE project
 * Copyright (C) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef QMLGLOBALENGINE_H
#define QMLGLOBALENGINE_H


class QQmlEngine;
class QmlGlobalEngine
{
public:
    QQmlEngine* engine() const;
    void setEngine(QQmlEngine* engine);

    static QmlGlobalEngine* instance();

private:
    QmlGlobalEngine();
    ~QmlGlobalEngine();

    QQmlEngine* m_engine;

    static QmlGlobalEngine* sm_instance;
};

#endif // QMLGLOBALENGINE_H
