/*
   SPDX-FileCopyrightText: 2006, 2011 Boudewijn Rempt (boud@valdyas.org)
   SPDX-FileCopyrightText: 2007, 2009, 2010 Thomas Zander <zander@kde.org>
   SPDX-FileCopyrightText: 2008 Carlos Licea <carlos.licea@kdemail.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
 */
#ifndef KO_RESOURCEMANAGER_P_H
#define KO_RESOURCEMANAGER_P_H

#include <QList>
#include <QVariant>
#include <QSizeF>
#include <QHash>

#include <KoColor.h>
#include <KoUnit.h>

class KoShape;

class KoResourceManager
{
public:

    KoResourceManager() {}

    /**
     * Set a resource of any type.
     * @param key the integer key
     * @param value the new value for the key.
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    void setResource(int key, const QVariant &value);

    /**
     * Set a resource of type KoColor.
     * @param key the integer key
     * @param color the new value for the key.
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    void setResource(int key, const KoColor &color);

    /**
     * Set a resource of type KoShape*.
     * @param key the integer key
     * @param shape the new value for the key.
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    void setResource(int key, KoShape *shape);

    /**
     * Set a resource of type KoUnit
     * @param key the integer key
     * @param unit the new value for the key.
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    void setResource(int key, const KoUnit &unit);

    /**
     * Returns a qvariant containing the specified resource or a standard one if the
     * specified resource does not exist.
     * @param key the key
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    QVariant resource(int key) const;

    /**
     * Return the resource determined by param key as a boolean.
     * @param key the indentifying key for the resource
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    bool boolResource(int key) const;

    /**
     * Return the resource determined by param key as an integer.
     * @param key the indentifying key for the resource
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    int intResource(int key) const;

    /**
     * Return the resource determined by param key as a KoColor.
     * @param key the indentifying key for the resource
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    KoColor koColorResource(int key) const;

    /**
     * Return the resource determined by param key as a pointer to a KoShape.
     * @param key the indentifying key for the resource
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    KoShape *koShapeResource(int key) const;

    /**
     * Return the resource determined by param key as a QString .
     * @param key the indentifying key for the resource
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    QString stringResource(int key) const;

    /**
     * Return the resource determined by param key as a QSizeF.
     * @param key the indentifying key for the resource
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    QSizeF sizeResource(int key) const;

    /**
     * Return the resource determined by param key as a KoUnit.
     * @param key the indentifying key for the resource
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    KoUnit unitResource(int key) const;

    /**
     * Returns true if there is a resource set with the requested key.
     * @param key the indentifying key for the resource
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    bool hasResource(int key) const;

    /**
     * Remove the resource with @p key from the provider.
     * @param key the key that will be used to remove the resource
     * @see KoCanvasResourceManager::CanvasResource KoDocumentResourceManager::DocumentResource
     */
    void clearResource(int key);

private:
    KoResourceManager(const KoResourceManager&);
    KoResourceManager& operator=(const KoResourceManager&);

    QHash<int, QVariant> m_resources;
};

#endif

