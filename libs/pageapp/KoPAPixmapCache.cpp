/* This file is part of the KDE project
   Copyright (C) 2009 Thorsten Zachmann <zachmann@kde.org>

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

#include "KoPAPixmapCache.h"

#include <QPixmapCache>
#include <QGlobalStatic>

class KoPAPixmapCache::Singleton
{
public:
    KoPAPixmapCache q;
};

Q_GLOBAL_STATIC( KoPAPixmapCache::Singleton, singleton )

KoPAPixmapCache * KoPAPixmapCache::instance()
{
    return &( singleton->q );
}

KoPAPixmapCache::KoPAPixmapCache()
{
}

KoPAPixmapCache::~KoPAPixmapCache()
{
}

int KoPAPixmapCache::cacheLimit()
{
    return QPixmapCache::cacheLimit();
}

void KoPAPixmapCache::clear( bool all )
{
    if ( all ) {
        QPixmapCache::clear();
    }
    else {
        QMap<QString, QVector<QSize> >::ConstIterator it( m_keySize.constBegin() );

        for ( ; it != m_keySize.constEnd(); ++it ) {
            foreach( const QSize& size, it.value() ) {
                QString k = generateKey( it.key(), size );
                QPixmapCache::remove( k );
            }
        }
        m_keySize.clear();
    }
}

bool KoPAPixmapCache::find( const QString & key, const QSize & size, QPixmap & pm )
{
    QString k = generateKey( key, size );
    return QPixmapCache::find( k, pm );
}

bool KoPAPixmapCache::insert( const QString & key, const QPixmap & pm, const QSize &size )
{
    QString k = generateKey( key, size.isValid() ? size: pm.size() );
    m_keySize[key].append( size.isValid() ? size: pm.size() );
    return QPixmapCache::insert( k, pm );
}

void KoPAPixmapCache::remove( const QString & key )
{
    QMap<QString, QVector<QSize> >::iterator it( m_keySize.find( key ) );

    if ( it != m_keySize.end() ) {
        foreach( const QSize& size, it.value() ) {
            QString k = generateKey( key, size );
            QPixmapCache::remove( k );
        }
        m_keySize.erase( it );
    }
}

void KoPAPixmapCache::setCacheLimit( int n )
{
    QPixmapCache::setCacheLimit( n );
}

QString KoPAPixmapCache::generateKey( const QString &key, const QSize & size )
{
    return QString( "%1-%2-%3" ).arg( key ).arg( size.width() ).arg( size.height() );
}
