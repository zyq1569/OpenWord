/* This file is part of the KDE libraries

   Copyright (C) 1999 Daniel M. Duley <mosfet@kde.org>
                 2006 Tobias Koenig <tokoe@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef KODUALCOLORBUTTON_H
#define KODUALCOLORBUTTON_H

#include "kowidgets_export.h"

#include <QWidget>

class KoColor;
class KoColorDisplayRendererInterface;

/**
 * @short A widget for selecting two related colors.
 *
 * KoDualColorButton allows the user to select two cascaded colors (usually a
 * foreground and background color). Other features include drag and drop
 * from other KDE color widgets, a reset to black and white control, and a
 * swap colors control.
 *
 * When the user clicks on the foreground or background rectangle the
 * rectangle is first sunken and the selectionChanged() signal is emitted.
 * Further clicks will present a color dialog and emit either the foregroundColorChanged()
 * or backgroundColorChanged() if a new color is selected.
 *
 * Note: With drag and drop when dropping a color the current selected color
 * will be set, while when dragging a color it will use whatever color
 * rectangle the mouse was pressed inside.
 *
 * @author Daniel M. Duley <mosfet@kde.org>
 */
class KOWIDGETS_EXPORT KoDualColorButton : public QWidget
{
    Q_OBJECT
    Q_ENUMS( Selection )
    Q_PROPERTY( KoColor foregroundColor READ foregroundColor WRITE setForegroundColor )
    Q_PROPERTY( KoColor backgroundColor READ backgroundColor WRITE setBackgroundColor )
    Q_PROPERTY( bool popDialog READ popDialog WRITE setPopDialog )


  public:
    enum Selection {
      Foreground,
      Background
    };

    /**
     * Constructs a new KoDualColorButton with the supplied foreground and
     * background colors.
     *
     * @param parent The parent widget of the KoDualColorButton.
     * @param dialogParent The parent widget of the color selection dialog.
     */
    KoDualColorButton(const KoColor &foregroundColor, const KoColor &backgroundColor,
                      QWidget *parent = nullptr, QWidget* dialogParent = nullptr );

    KoDualColorButton(const KoColor &foregroundColor, const KoColor &backgroundColor,
                      const KoColorDisplayRendererInterface *displayRenderer,
                      QWidget *parent = nullptr, QWidget* dialogParent = nullptr);

    /**
     * Destroys the KoDualColorButton.
     */
    ~KoDualColorButton() override;

    /**
     * Returns the current foreground color.
     */
    KoColor foregroundColor() const;

    /**
     * Returns the current background color.
     */
    KoColor backgroundColor() const;

    /**
     * Returns if a dialog with a color chooser will be popped up when clicking
     * If false then you could/should connect to the pleasePopDialog signal
     * and pop your own dialog. Just set the current color afterwards.
     */
    bool popDialog() const;

    /**
     * Returns the minimum size needed to display the widget and all its
     * controls.
     */
    QSize sizeHint() const override;

  public Q_SLOTS:
    /**
     * Sets the foreground color.
     */
    void setForegroundColor( const KoColor &color );

    /**
     * Sets the background color.
     */
    void setBackgroundColor( const KoColor &color );

    /**
     * Sets if a dialog with a color chooser should be popped up when clicking
     * If you set this to false then you could connect to the pleasePopDialog signal
     * and pop your own dialog. Just set the current color afterwards.
     */
    void setPopDialog( bool popDialog );

  Q_SIGNALS:
    /**
     * Emitted when the foreground color is changed.
     */
    void foregroundColorChanged( const KoColor &color );

    /**
     * Emitted when the background color is changed.
     */
    void backgroundColorChanged( const KoColor &color );

    /**
     * Emitted when the user clicks one of the two color patches.
     * You should/could pop you own color chooser dialog in response.
     * Also see the popDialog attribute.
     */
    void pleasePopDialog( const KoColor &color );

  protected:
    /**
     * Sets the supplied rectangles to the proper size and position for the
     * current widget size. You can reimplement this to change the layout
     * of the widget. Restrictions are that the swap control will always
     * be at the top right, the reset control will always be at the bottom
     * left, and you must leave at least a 14x14 space in those corners.
     */
    virtual void metrics( QRect &foregroundRect, QRect &backgroundRect );

    void paintEvent( QPaintEvent *event ) override;
    void mousePressEvent( QMouseEvent *event ) override;
    void mouseMoveEvent( QMouseEvent *event ) override;
    void mouseReleaseEvent( QMouseEvent *event ) override;
    void dragEnterEvent( QDragEnterEvent *event ) override;
    void dropEvent( QDropEvent *event ) override;
    void changeEvent(QEvent *event) override;

  private:
    class Private;
    Private *const d;
};

#include "KoColor.h"
#include <QPainter>
#include "dcolorreset.xpm"
class Q_DECL_HIDDEN KoDualColorButton::Private
{
  public:
    Private(const KoColor &fgColor, const KoColor &bgColor,
            QWidget *_dialogParent,
            const KoColorDisplayRendererInterface *_displayRenderer)
        : dialogParent(_dialogParent)
        , dragFlag( false )
        , miniCtlFlag( false )
        , foregroundColor(fgColor)
        , backgroundColor(bgColor)

        , displayRenderer(_displayRenderer)
    {
        updateArrows();
        resetPixmap = QPixmap( (const char **)dcolorreset_xpm );

        popDialog = true;
    }

    void updateArrows() {
        arrowBitmap = QPixmap(12,12);
        arrowBitmap.fill(Qt::transparent);

        QPainter p(&arrowBitmap);
        p.setPen(QPen(dialogParent->palette().foreground().color(), 0));

        // arrow pointing left
        p.drawLine(0, 3, 7, 3);
        p.drawLine(1, 2, 1, 4);
        p.drawLine(2, 1, 2, 5);
        p.drawLine(3, 0, 3, 6);

        // arrow pointing down
        p.drawLine(8, 4, 8, 11);
        p.drawLine(5, 8, 11, 8);
        p.drawLine(6, 9, 10, 9);
        p.drawLine(7, 10, 9, 10);
    }

    QWidget* dialogParent;

    QPixmap arrowBitmap;
    QPixmap resetPixmap;
    bool dragFlag, miniCtlFlag;
    KoColor foregroundColor;
    KoColor backgroundColor;
    QPoint dragPosition;
    Selection tmpSelection;
    bool popDialog;
    const KoColorDisplayRendererInterface *displayRenderer;

    void init(KoDualColorButton *q);
};

#endif

