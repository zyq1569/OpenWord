/*
 * Copyright (C) 2007 Cyrille Berger <cberger@cberger.net>
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

#include "KoColorConversionCache.h"

#include <QHash>
#include <QList>
#include <QMutex>
#include <QThreadStorage>

#include <KoColorSpace.h>

struct KoColorConversionCacheKey
{

    KoColorConversionCacheKey(const KoColorSpace* _src,
                              const KoColorSpace* _dst,
                              KoColorConversionTransformation::Intent _renderingIntent,
                              KoColorConversionTransformation::ConversionFlags _conversionFlags)
        : src(_src)
        , dst(_dst)
        , renderingIntent(_renderingIntent)
        , conversionFlags(_conversionFlags)
    {
    }

    bool operator==(const KoColorConversionCacheKey& rhs) const
    {
        return (*src == *(rhs.src)) && (*dst == *(rhs.dst))
               && (renderingIntent == rhs.renderingIntent)
               && (conversionFlags == rhs.conversionFlags);
    }

    const KoColorSpace* src;
    const KoColorSpace* dst;
    KoColorConversionTransformation::Intent renderingIntent;
    KoColorConversionTransformation::ConversionFlags conversionFlags;
};

uint qHash(const KoColorConversionCacheKey& key)
{
    return qHash(key.src) + qHash(key.dst) + qHash(key.renderingIntent) + qHash(key.conversionFlags);
}

struct KoColorConversionCache::CachedTransformation
{

    CachedTransformation(KoColorConversionTransformation* _transfo)
        : transfo(_transfo), use(0)
    {}

    ~CachedTransformation()
    {
        delete transfo;
    }

    bool available()
    {
        return use == 0;
    }

    KoColorConversionTransformation* transfo;
    int use;
};

typedef QPair<KoColorConversionCacheKey, KoCachedColorConversionTransformation> FastPathCacheItem;

struct KoColorConversionCache::Private
{
    QMultiHash< KoColorConversionCacheKey, CachedTransformation*> cache;
    QMutex cacheMutex;

    QThreadStorage<FastPathCacheItem*> fastStorage;
};


KoColorConversionCache::KoColorConversionCache() : d(new Private)
{
}

KoColorConversionCache::~KoColorConversionCache()
{
    foreach(CachedTransformation* transfo, d->cache)
    {
        delete transfo;
    }
    delete d;
}

KoCachedColorConversionTransformation KoColorConversionCache::cachedConverter(const KoColorSpace* src,
        const KoColorSpace* dst,
        KoColorConversionTransformation::Intent _renderingIntent,
        KoColorConversionTransformation::ConversionFlags _conversionFlags)
{
    KoColorConversionCacheKey key(src, dst, _renderingIntent, _conversionFlags);

    FastPathCacheItem *cacheItem =
        d->fastStorage.localData();

    if (cacheItem)
    {
        if (cacheItem->first == key)
        {
            return cacheItem->second;
        }
    }

    cacheItem = 0;

    QMutexLocker lock(&d->cacheMutex);
    QList< CachedTransformation* > cachedTransfos = d->cache.values(key);
    if (cachedTransfos.size() != 0)
    {
        foreach(CachedTransformation* ct, cachedTransfos)
        {
            if (ct->available())
            {
                ct->transfo->setSrcColorSpace(src);
                ct->transfo->setDstColorSpace(dst);

                cacheItem = new FastPathCacheItem(key, KoCachedColorConversionTransformation(this, ct));
                break;
            }
        }
    }
    if (!cacheItem)
    {
        KoColorConversionTransformation* transfo = src->createColorConverter(dst, _renderingIntent, _conversionFlags);
        CachedTransformation* ct = new CachedTransformation(transfo);
        d->cache.insert(key, ct);
        cacheItem = new FastPathCacheItem(key, KoCachedColorConversionTransformation(this, ct));
    }

    d->fastStorage.setLocalData(cacheItem);
    return cacheItem->second;
}

void KoColorConversionCache::colorSpaceIsDestroyed(const KoColorSpace* cs)
{
    d->fastStorage.setLocalData(0);

    QMutexLocker lock(&d->cacheMutex);
    QMultiHash< KoColorConversionCacheKey, CachedTransformation*>::iterator endIt = d->cache.end();
    for (QMultiHash< KoColorConversionCacheKey, CachedTransformation*>::iterator it = d->cache.begin(); it != endIt;)
    {
        if (it.key().src == cs || it.key().dst == cs)
        {
            Q_ASSERT(it.value()->available()); // That's terribely evil, if that assert fails, that means that someone is using a color transformation with a color space which is currently being deleted
            delete it.value();
            it = d->cache.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

//--------- KoCachedColorConversionTransformation ----------//

struct KoCachedColorConversionTransformation::Private
{
    KoColorConversionCache* cache;
    KoColorConversionCache::CachedTransformation* transfo;
};


KoCachedColorConversionTransformation::KoCachedColorConversionTransformation(KoColorConversionCache* cache, KoColorConversionCache::CachedTransformation* transfo) : d(new Private)
{
    Q_ASSERT(transfo->available());
    d->cache = cache;
    d->transfo = transfo;
    d->transfo->use++;
}

KoCachedColorConversionTransformation::KoCachedColorConversionTransformation(const KoCachedColorConversionTransformation& rhs) : d(new Private(*rhs.d))
{
    d->transfo->use++;
}

KoCachedColorConversionTransformation::~KoCachedColorConversionTransformation()
{
    d->transfo->use--;
    Q_ASSERT(d->transfo->use >= 0);
    delete d;
}

const KoColorConversionTransformation* KoCachedColorConversionTransformation::transformation() const
{
    return d->transfo->transfo;
}

