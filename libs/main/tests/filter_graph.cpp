/* This file is part of the KDE project
   Copyright (C) 2002 Werner Trobin <trobin@kde.org>

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

#include <QFile>
#include <QByteArray>
#include <QList>
#include <QPluginLoader>

#include "KoDocumentEntry.h"
#include "KoFilterEntry.h"
#include "KoFilterManager.h"

#include <MainDebug.h>

int main(int /*argc*/, char ** /*argv*/)
{
    QByteArray output = "digraph filters {\n";

    // The following code is shamelessly copied over from Calligra::Graph::buildGraph
    // It wasn't feasible to do some serious changes in the lib for that tiny bit
    // of duplicated code in a test file.

    QList<QString> vertices; // to keep track of already inserted values, not performance critical

    // Make sure that all available parts are added to the graph
    const QList<KoDocumentEntry> parts(KoDocumentEntry::query());
    QList<KoDocumentEntry>::ConstIterator partIt(parts.begin());
    QList<KoDocumentEntry>::ConstIterator partEnd(parts.end());

    while (partIt != partEnd) {
        //kDebug() << ( *partIt ).service()->desktopEntryName();
        QJsonObject metaData = (*partIt).metaData();
        QStringList nativeMimeTypes = metaData.value("X-KDE-ExtraNativeMimeTypes").toString().split(',');
        nativeMimeTypes += metaData.value("X-KDE-NativeMimeType").toString();
        QStringList::ConstIterator it = nativeMimeTypes.constBegin();
        QStringList::ConstIterator end = nativeMimeTypes.constEnd();
        for (; it != end; ++it) {
            QString key = *it;
            //kDebug() <<"" << key;
            if (!key.isEmpty()) {
                output += "    \"";
                output += key.toLatin1();
                output += "\" [shape=box, style=filled, fillcolor=lightblue];\n";
                if (! vertices.contains(key))
                    vertices.append(key);
            }
        }
        ++partIt;
    }

    const QList<KoFilterEntry::Ptr> filters(KoFilterEntry::query());   // no constraint here - we want *all* :)
    QList<KoFilterEntry::Ptr>::ConstIterator it = filters.begin();
    QList<KoFilterEntry::Ptr>::ConstIterator end = filters.end();

    for (; it != end; ++it) {
        qDebug() << "import" << (*it)->import << " export" << (*it)->export_;
        // First add the "starting points"
        QStringList::ConstIterator importIt = (*it)->import.constBegin();
        QStringList::ConstIterator importEnd = (*it)->import.constEnd();
        for (; importIt != importEnd; ++importIt) {
            // already there?
            if (! vertices.contains(*importIt)) {
                vertices.append(*importIt);
                output += "    \"";
                output += (*importIt).toLatin1();
                output += "\";\n";
            }
        }

        QStringList::ConstIterator exportIt = (*it)->export_.constBegin();
        QStringList::ConstIterator exportEnd = (*it)->export_.constEnd();

        for (; exportIt != exportEnd; ++exportIt) {
            // First make sure the export vertex is in place
            if (! vertices.contains(*exportIt)) {
                output += "    \"";
                output += (*exportIt).toLatin1();
                output += "\";\n";
                vertices.append(*exportIt);
            }
            // Then create the appropriate edges
            importIt = (*it)->import.constBegin();
            for (; importIt != importEnd; ++importIt) {
                output += "    \"";
                output += (*importIt).toLatin1();
                output += "\" -> \"";
                output += (*exportIt).toLatin1();
                if (KoFilterManager::filterAvailable(*it))
                    output += "\";\n";
                else
                    output += "\" [style=dotted];\n";
            }
        }
    }

    output += "}\n";

    QFile f("graph.dot");
    if (f.open(QIODevice::WriteOnly))
        f.write(output);
    f.close();
    return 0;
}
