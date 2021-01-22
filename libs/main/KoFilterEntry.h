/* This file is part of the KDE project
   Copyright (C) 1998, 1999 Torben Weis <weis@kde.org>
   Copyright     2007       David Faure <faure@kde.org>

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

#ifndef __ko_filter_entry_h__
#define __ko_filter_entry_h__

#include <QExplicitlySharedDataPointer>
#include <QList>
#include <QStringList>
#include "komain_export.h"

class QObject;
class QPluginLoader;
class KoFilter;
class KoFilterChain;
/**
 *  Represents an available filter.
 */
class KOMAIN_TEST_EXPORT KoFilterEntry : public QSharedData
{

public:
    typedef QExplicitlySharedDataPointer<KoFilterEntry> Ptr;

    //KoFilterEntry() : weight( 0 ) { m_service = 0; } // for QList
    /**
     * @param loader pluginloader for the filter, KoFilterEntry takes ownership
     */
    explicit KoFilterEntry(QPluginLoader *loader);
    ~KoFilterEntry();

    KoFilter* createFilter(KoFilterChain* chain, QObject* parent = 0);

    /**
     *  The imported mimetype(s).
     */
    QStringList import;

    /**
     *  The exported mimetype(s).
     */
    QStringList export_;

    /**
     *  The "weight" of this filter path. Has to be > 0 to be valid.
     */
    unsigned int weight;

    /**
     *  Do we have to check during runtime?
     */
    QString available;

    /**
     *  @return TRUE if the filter can import the requested mimetype.
     */
    bool imports(const QString& _mimetype) const {
        return (import.contains(_mimetype));
    }

    /**
     *  @return TRUE if the filter can export the requested mimetype.
     */
    bool exports(const QString& _m) const {
        return (export_.contains(_m));
    }

    QString fileName() const;

    /**
     *  This function will query KDED to find all available filters.
     */
    static QList<KoFilterEntry::Ptr> query();


private:
    QPluginLoader * const m_loader;
};

#endif
