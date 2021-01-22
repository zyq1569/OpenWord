/* This file is part of the KDE project
 * Copyright (C) 2007, 2009 Thomas Zander <zander@kde.org>
 * Copyright (C) 2008 Thorsten Zachmann <zachmann@kde.org>
 * Copyright (C) 2009 C. Boemann <cbo@boemann.dk>
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
#include "VideoCollection.h"

#include "VideoData.h"
#include "VideoDebug.h"

#include "KoShapeSavingContext.h"
#include <KoStoreDevice.h>
#include <QCryptographicHash>
#include <KoXmlWriter.h>

#include <QMap>
#include <QUrl>
#include <QMimeDatabase>
#include <QMimeType>


class VideoCollection::Private
{
public:
    ~Private()
    {
   }

    QMap<qint64, VideoData*> videos;
    // an extra map to find all dataObjects based on the key of a store.
    QMap<QByteArray, VideoData*> storeVideos;
};

VideoCollection::VideoCollection(QObject *parent)
    : QObject(parent)
    , saveCounter(0)
    , d(new Private())
{
}

VideoCollection::~VideoCollection()
{
    foreach(VideoData *id, d->videos) {
        id->setCollection(0);
    }
    delete d;
}

bool VideoCollection::completeLoading(KoStore *store)
{
    Q_UNUSED( store );
    d->storeVideos.clear();
    return true;
}

bool VideoCollection::completeSaving(KoStore *store, KoXmlWriter *manifestWriter, KoShapeSavingContext *context)
{
    Q_UNUSED(context);
    QMap<qint64, VideoData *>::ConstIterator dataIt(d->videos.constBegin());

    while (dataIt != d->videos.constEnd()) {
        if (!dataIt.value()->saveName().isEmpty()) {
            VideoData *videoData = dataIt.value();
            if (store->open(videoData->saveName())) {
                KoStoreDevice device(store);
                bool ok = videoData->saveData(device);
                store->close();
                // TODO error handling
                if (ok) {
                    QMimeDatabase db;
                    const QString mimetype(db.mimeTypeForFile(videoData->saveName(), QMimeDatabase::MatchExtension).name());
                    manifestWriter->addManifestEntry(videoData->saveName(), mimetype);
                } else {
                    warnVideo << "saving video failed";
                }
            } else {
                warnVideo << "saving video failed: open store failed";
            }
            dataIt.value()->setSaveName(QString());
        }
        ++dataIt;
    }
    saveCounter=0;
    return true;
}

VideoData *VideoCollection::createExternalVideoData(const QUrl &url, bool saveInternal)
{
    Q_ASSERT(!url.isEmpty() && url.isValid());

    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(url.toEncoded().append(saveInternal ? "true" : "false"));
    qint64 key = VideoData::generateKey(md5.result());

    if (d->videos.contains(key)) {
        return new VideoData(*(d->videos.value(key)));
    }

    VideoData *data = new VideoData();
    data->setExternalVideo(url, saveInternal);
    data->setCollection(this);
    Q_ASSERT(data->key() == key);
    d->videos.insert(key, data);
    return data;
}

VideoData *VideoCollection::createVideoData(const QString &href, KoStore *store)
{
    // the tricky thing with a 'store' is that we need to read the data now
    // as the store will no longer be readable after the loading completed.
    // The solution we use is to read the data, store it in a QTemporaryFile
    // and read and parse it on demand when the video data is actually needed.
    // This leads to having two keys, one for the store and one for the
    // actual video data. We need the latter so if someone else gets the same
    // video data they can find this data and share (warm fuzzy feeling here)
    QByteArray storeKey = (QString::number((qint64) store) + href).toLatin1();
    if (d->storeVideos.contains(storeKey))
        return new VideoData(*(d->storeVideos.value(storeKey)));

    VideoData *data = new VideoData();
    data->setVideo(href, store);
    data->setCollection(this);

    d->storeVideos.insert(storeKey, data);
    return data;
}

int VideoCollection::size() const
{
    return d->videos.count();
}

int VideoCollection::count() const
{
    return d->videos.count();
}

void VideoCollection::removeOnKey(qint64 videoDataKey)
{
    d->videos.remove(videoDataKey);
}
