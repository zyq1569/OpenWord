/* This file is part of the KDE project
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

#ifndef FINDDIRECTION_P_H
#define FINDDIRECTION_P_H

class KoCanvasResourceManager;
class KoFindPrivate;
class QTextCursor;
class QTextDocument;

class FindDirection
{
public:
    explicit FindDirection(KoCanvasResourceManager *provider);
    virtual ~FindDirection();

    virtual bool positionReached(const QTextCursor &currentPos, const QTextCursor &endPos) = 0;

    virtual void positionCursor(QTextCursor &currentPos) = 0;

    virtual void select(const QTextCursor &cursor) = 0;

    virtual void nextDocument(QTextDocument *document, KoFindPrivate *findPrivate) = 0;

protected:
    KoCanvasResourceManager *m_provider;
};

class FindForward : public FindDirection
{
public:
    explicit FindForward(KoCanvasResourceManager *provider);
    ~FindForward() override;

    bool positionReached(const QTextCursor &currentPos, const QTextCursor &endPos) override;

    void positionCursor(QTextCursor &currentPos) override;

    void select(const QTextCursor &cursor) override;

    void nextDocument(QTextDocument *document, KoFindPrivate *findPrivate) override;
};

class FindBackward : public FindDirection
{
public:
    explicit FindBackward(KoCanvasResourceManager *provider);
    ~FindBackward() override;

    bool positionReached(const QTextCursor &currentPos, const QTextCursor &endPos) override;

    void positionCursor(QTextCursor &currentPos) override;

    void select(const QTextCursor &cursor) override;

    void nextDocument(QTextDocument *document, KoFindPrivate *findPrivate) override;
};

#endif // FINDDIRECTION_P_H
