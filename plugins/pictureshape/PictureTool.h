/* This file is part of the KDE project
   Copyright 2007 Montel Laurent <montel@kde.org>
   Copyright 2011 Silvio Heinrich <plassy@web.de>

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
   Boston, MA 02110-1301, USA.
*/

#ifndef PICTURE_TOOL
#define PICTURE_TOOL

#include <KoToolBase.h>
#include <kjob.h>

class PictureShape;
struct PictureToolUI;

///add
#include <KoInteractionTool.h>
#include <KoFlake.h>
class KoSelection;
#include <QPolygonF>
class PictureTool : public KoInteractionTool/*KoToolBase*/
{
    Q_OBJECT
public:
    explicit PictureTool(KoCanvasBase* canvas);

    /// reimplemented from KoToolBase
    void paint(QPainter&, const KoViewConverter&) override;// {}
    /// reimplemented from KoToolBase
    void mousePressEvent(KoPointerEvent*) override;
    /// reimplemented from superclass
    void mouseDoubleClickEvent(KoPointerEvent *event) override;
    /// reimplemented from KoToolBase
    void mouseMoveEvent(KoPointerEvent*) override;// {}
    /// reimplemented from KoToolBase
    void mouseReleaseEvent(KoPointerEvent*) override;// {}

    /// reimplemented from KoToolBase
    void activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes) override;
    /// reimplemented from KoToolBase
    void deactivate() override;

    //add
    KoSelection * koSelection();
    void updateCursor();

protected:
    /// reimplemented from KoToolBase
    QWidget *createOptionWidget() override;

//add openword 20220424
    KoInteractionStrategy *createStrategy(KoPointerEvent *event) override;
    void repaintDecorations() override;
    QRectF handlesSize();

private Q_SLOTS:
    void colorModeChanged(int cmbBoxIndex);
    void changeUrlPressed();
    void cropRegionChanged(const QRectF& rect, bool undoPrev);
    void cropEditFieldsChanged();
    void aspectCheckBoxChanged(bool checked);
    void contourCheckBoxChanged(bool checked);
    void fillButtonPressed();
    void updateControlElements();
    void setImageData(KJob *job);

private:
    PictureShape *m_pictureshape;
    PictureToolUI *m_pictureToolUI;
/// add openword 20220424
    KoFlake::SelectionHandle m_lastHandle;
    KoFlake::Position m_hotPosition;
    bool m_mouseWasInsideHandles;
};


///-----------------------------------------SelectionPicture copy [class SelectionDecorator]----------------------------------------------\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
#include <KoViewConverter.h>
#include <KoFlake.h>
#include <QPainter>

class KoSelection;

/**
 * The SelectionPicture is used to paint extra user-interface items on top of a selection.
 */
class SelectionPicture
{
public:
    /**
     * Constructor.
     * @param arrows the direction that needs highlighting. (currently unused)
     * @param rotationHandles if true; the rotation handles will be drawn
     * @param shearHandles if true; the shearhandles will be drawn
     */
    SelectionPicture(KoFlake::SelectionHandle arrows, bool rotationHandles, bool shearHandles);
    ~SelectionPicture() {}

    /**
     * paint the decorations.
     * @param painter the painter to paint to.
     * @param converter to convert between internal and view coordinates.
     */
    void paint(QPainter &painter, const KoViewConverter &converter);

    /**
     * set the selection that is to be painted.
     * @param selection the current selection.
     */
    void setSelection(KoSelection *selection);

    /**
     * set the radius of the selection handles
     * @param radius the new handle radius
     */
    void setHandleRadius( int radius );

    /// Sets the hot position to highlight
    static void setHotPosition( KoFlake::Position hotPosition );

    /// Returns the hot position
    static KoFlake::Position hotPosition();

private:
    bool m_rotationHandles, m_shearHandles;
    KoFlake::SelectionHandle m_arrows;
    static KoFlake::Position m_hotPosition;
    KoSelection *m_selection;
    int m_handleRadius;
    int m_lineWidth;
};
#endif
