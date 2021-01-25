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

#ifndef KOFINDSTRATEGY_H
#define KOFINDSTRATEGY_H

#include "KoFindStrategyBase.h"
#include <kfinddialog.h>
class QWidget;

/**
 * Strategy used for implementing find
 */
class KoFindStrategy : public KoFindStrategyBase
{
public:
    explicit KoFindStrategy(QWidget *parent);
    ~KoFindStrategy() override;

    /// reimplemented
    KFindDialog *dialog() const override;

    /// reimplemented
    void reset() override;

    /// reimplemented
    void displayFinalDialog() override;

    /// reimplemented
    bool foundMatch(QTextCursor &cursor, FindDirection *findDirection) override;

private:
    KFindDialog *m_dialog;
    int m_matches;
};

class NonClosingFindDialog : public KFindDialog
{
Q_OBJECT
public:
    NonClosingFindDialog(QWidget *parent)
            : KFindDialog(parent) {}

    void accept() override {}
};
#endif /* KOFINDSTRATEGY_H */
