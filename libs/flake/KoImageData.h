/* This file is part of the KDE project
 * Copyright (C) 2007, 2009 Thomas Zander <zander@kde.org>
 * Copyright (C) 2007 Jan Hambrecht <jaham@gmx.net>
 * Copyright (C) 2008 Thorsten Zachmann <zachmann@kde.org>
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
#ifndef KOIMAGEDATA_H
#define KOIMAGEDATA_H

#include "flake_export.h"
#include "logging.h"
#include <QSize>
#include <QMetaType>
#include <QTimer>
#include <QDir>
#include <QUrl>
#include <QImage>
#include <QPixmap>
#include <KoShapeUserData.h>

class QIODevice;
class QPixmap;
class QImage;
class QSizeF;
class QUrl;
class KoImageCollection;
class KoImageDataPrivate;
class KoStore;

/**
 * This class is meant to represent the image data so it can be shared between image shapes.
 *
 * This class inherits from KoShapeUserData which means you can set it on any KoShape using
 * KoShape::setUserData() and get it using KoShape::userData().  The pictureshape plugin
 * uses this class to show its image data.
 *
 * Plugins should not make a copy of the pixmap data, but use the pixmap() method, which
 * handles caching.
 */
class FLAKE_EXPORT KoImageData : public KoShapeUserData
{
    Q_OBJECT
public:
    /// Various error codes representing what has gone wrong
    enum ErrorCode
    {
        Success,
        OpenFailed,
        StorageFailed, ///< This is set if the image data has to be stored on disk in a temporary file, but we failed to do so
        LoadFailed
    };

    /// default constructor, creates an invalid imageData object
    KoImageData();

    ~KoImageData() override;
    KoImageData(const KoImageData &imageData);
    KoImageData &operator=(const KoImageData &other);
    inline bool operator!=(const KoImageData &other) const
    {
        return !operator==(other);
    }
    bool operator==(const KoImageData &other) const;

    void setImage(const QString &location, KoStore *store, KoImageCollection *collection = 0);

    /**
     * Renders a pixmap the first time you request it is called and returns it.
     * @returns the cached pixmap
     * @see isValid(), hasCachedPixmap()
     */
    QPixmap pixmap(const QSize &targetSize = QSize());

    /**
     * Return the internal store of the image.
     * @see isValid(), hasCachedImage()
     */
    QImage image() const;

    /**
     * The size of the image in points
     */
    QSizeF imageSize();

    /**
     * Save the image data to the param device.
     * The full file is saved.
     * @param device the device that is used to get the data from.
     * @return returns true if load was successful.
     */
    bool saveData(QIODevice &device);

    /**
     * Get a unique key of the image data
     */
    qint64 key() const;

    /// @return the original image file's extension, e.g. "png" or "gif"
    QString suffix() const;

    ErrorCode errorCode() const;

    /// returns if this is a valid imageData with actual image data present on it.
    bool isValid() const;

    /// \internal
    KoImageDataPrivate *priv()
    {
        return d;
    }

private:
    friend class KoImageCollection;
    friend class TestImageCollection;


    explicit KoImageData(KoImageDataPrivate *priv);

    /// returns true only if pixmap() would return immediately with a cached pixmap
    bool hasCachedPixmap() const;

    /// returns true only if image() would return immediately with a cached image
    bool hasCachedImage() const;

    void setImage(const QImage &image, KoImageCollection *collection = 0);
    void setImage(const QByteArray &imageData, KoImageCollection *collection = 0);


private:
    KoImageDataPrivate *d;
    Q_PRIVATE_SLOT(d, void cleanupImageCache())
};

Q_DECLARE_METATYPE(KoImageData*)


class KoImageCollection;
class QTemporaryFile;

class KoImageDataPrivate
{
public:
    explicit KoImageDataPrivate(KoImageData *q);
    virtual ~KoImageDataPrivate();

    /**
     * Save the image data to the param device.
     * The full file is saved.
     * @param device the device that is used to get the data from.
     * @return returns true if load was successful.
     */
    bool saveData(QIODevice &device);

    /// store the suffix based on the full filename.
    void setSuffix(const QString &fileName);

    /// take the data from \a device and store it in the temporaryFile
    void copyToTemporary(QIODevice &device);

    /// clean the image cache.
    void cleanupImageCache();

    void clear();

    static qint64 generateKey(const QByteArray &bytes);

    enum DataStoreState
    {
        StateEmpty,     ///< No image data, either as url or as QImage
        StateNotLoaded, ///< Image data is set as Url
        StateImageLoaded,///< Image data is loaded from Url, so both are present.
        StateImageOnly  ///< Image data is stored in a QImage. There is no external storage.
    };

    KoImageCollection *collection;
    KoImageData::ErrorCode errorCode;
    QSizeF imageSize;
    qint64 key;
    QString suffix; // the suffix of the picture e.g. png  TODO use a QByteArray ?
    QTimer cleanCacheTimer;

    QAtomicInt refCount;

    // Image data store.
    DataStoreState dataStoreState;
    QUrl imageLocation;
    QImage image;
    /// screen optimized cached version.
    QPixmap pixmap;

    QTemporaryFile *temporaryFile;
};


#endif
