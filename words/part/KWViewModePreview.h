/* This file is part of the KDE project
 * Copyright (C) 2001 David Faure <faure@kde.org>
 * Copyright (C) 2006 Thomas Zander <zander@kde.org>
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

#ifndef KWVIEWMODEPREVIEW_H
#define KWVIEWMODEPREVIEW_H

#include "KWViewMode.h"
#include "words_export.h"

#include <QString>

/**
 * A mode for previewing the overall document
 * Pages are organized in a grid (mostly useful with low zoom levels)
 */
class WORDS_EXPORT KWViewModePreview : public KWViewMode
{
    Q_OBJECT
public:
    /// constructor
    explicit KWViewModePreview();
    ~KWViewModePreview() override
    {

    }

    QPointF documentToView(const QPointF &point, KoViewConverter *viewConverter) const override;
    QPointF viewToDocument(const QPointF &point, KoViewConverter *viewConverter) const override;
    QSizeF contentsSize() const override;

    /**
     * The preview can show several pages in a row for easy overview.
     * You can set the preferred pages per row here.
     * @param num the new number of pages per row
     */
    void setPagesPerRow(int num)
    {
        m_pagesPerRow = num;
    }
    /**
     * @return the number of pages we are showing per row
     */
    int pagesPerRow() const
    {
        return m_pagesPerRow;
    }

    /// return a string identification of this viewMode
    static const QString viewMode()
    {
        return "ModePreview";
    }
    /// return a string identification of this viewMode
    const QString type() const override
    {
        return KWViewModePreview::viewMode();
    }
    QVector<ViewMap> mapExposedRects(const QRectF &viewRect, KoViewConverter *viewConverter) const override;

    /// set the gap between the pages
    void setGap(int gap);

protected:
    void updatePageCache() override;

private:
    int m_pagesPerRow;
};

#endif
