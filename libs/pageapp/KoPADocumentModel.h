/* This file is part of the KDE project
 * Copyright (C) 2007 Jan Hambrecht <jaham@gmx.net>
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

#ifndef KOPADOCUMENTMODEL_H
#define KOPADOCUMENTMODEL_H

#include <KoDocumentSectionModel.h>

class KoPADocument;
class KoShape;
class KoShapeContainer;
class KoPAPageBase;

#include "kopageapp_export.h"

/**
 * Model class for the document structure widget (dsw). The dsw can
 * show the structure of a document as a three, as thumbnails or as
 * a list.
 *
 * XXX: implement beginInsertRows, endInsertRows, beginRemoveRows
 *      and endRemoveRows to make the widget react to page insertions
 *      and deletions.
 */
class KOPAGEAPP_EXPORT KoPADocumentModel : public KoDocumentSectionModel
{
    Q_OBJECT
public:
    /// Constructs a new document section model using the specified documents data
    explicit KoPADocumentModel( QObject* parent, KoPADocument *document = 0 );

    /// Set the document used in the model
    void setDocument(KoPADocument* document);
    /// Set the mode to show, master page or normal page
    void setMasterMode(bool master);

    // from QAbstractItemModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent( const QModelIndex &child ) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QMimeData * mimeData( const QModelIndexList & indexes ) const override;
    bool dropMimeData( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent ) override;
    Qt::DropActions supportedDragActions() const override;

public Q_SLOTS:
    /// Triggers an update of the complete model
    void update();

Q_SIGNALS:
    void requestPageSelection(int start, int count);

private:
    /// Returns properties of the given shape
    PropertyList properties( KoShape* shape ) const;
    /// Sets the properties on the given shape
    void setProperties( KoShape* shape, const PropertyList &properties );
    /// Creates a thumbnail image with the specified size from the given shape
    QImage createThumbnail( KoShape* shape, const QSize &thumbSize ) const;
    /// Returns the child shape with the given index from the parent shape
    KoShape * childFromIndex( KoShapeContainer *parent, int row ) const;
    /// Returns the zero based index of a child shape within its parent shape
    int indexFromChild( KoShapeContainer *parent, KoShape *child ) const;
    /// Returns the parent model index from the given child shape
    QModelIndex parentIndexFromShape( const KoShape * child );
    /// Creates a context menu when dropping pages to choose between copy or move action.
    bool doDrop(QList<KoPAPageBase *> pages, KoPAPageBase *pageAfter, Qt::DropAction action);

    KoPADocument *m_document; ///< the undelying data structure
    bool m_master;
    mutable QList<KoShape*> m_childs;
    mutable KoShapeContainer *m_lastContainer;
};

#endif // KODOCUMENTMODEL_H
