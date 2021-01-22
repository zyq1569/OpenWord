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

#include "enhancedpath/EnhancedPathShapeFactory.h"
#include "enhancedpath/EnhancedPathShape.h"

#include <KoShapeStroke.h>
#include <KoProperties.h>
#include <KoXmlNS.h>
#include <KoXmlReader.h>
#include <KoColorBackground.h>
#include <KoShapeLoadingContext.h>

#include <KoIcon.h>

#include <klocalizedstring.h>

#include <QString>

#include <math.h>

EnhancedPathShapeFactory::EnhancedPathShapeFactory()
    : KoShapeFactoryBase(EnhancedPathShapeId, i18n("An enhanced path shape"))
{
    setToolTip(i18n("An enhanced path"));
    setIconName(koIconName("enhancedpath"));
    setXmlElementNames(KoXmlNS::draw, QStringList("custom-shape"));
    setLoadingPriority(1);

    addCross();
    addArrow();
    addSmiley();
    addCircularArrow();
    addGearhead();
}

KoShape *EnhancedPathShapeFactory::createDefaultShape(KoDocumentResourceManager *) const
{
    EnhancedPathShape *shape = new EnhancedPathShape(QRect(0, 0, 100, 100));
    shape->setStroke(new KoShapeStroke(1.0));
    shape->setShapeId(KoPathShapeId);

    shape->addModifiers("35");

    shape->addFormula("Right", "width - $0");
    shape->addFormula("Bottom", "height - $0");
    shape->addFormula("Half", "min(0.5 * height, 0.5 * width)");

    shape->addCommand("M $0 0");
    shape->addCommand("L ?Right 0 ?Right $0 width $0 width ?Bottom ?Right ?Bottom");
    shape->addCommand("L ?Right height $0 height $0 ?Bottom 0 ?Bottom 0 $0 $0 $0");
    shape->addCommand("Z");

    ComplexType handle;
    handle["draw:handle-position"] = "$0 0";
    handle["draw:handle-range-x-minimum"] = '0';
    handle["draw:handle-range-x-maximum"] = "?Half";
    shape->addHandle(handle);
    shape->setSize(QSize(100, 100));

    return shape;
}

KoShape *EnhancedPathShapeFactory::createShape(const KoProperties *params, KoDocumentResourceManager *) const
{
    QVariant viewboxData;
    const QRect viewBox = (params->property(QLatin1String("viewBox"), viewboxData)) ?
        viewboxData.toRect() :
        QRect(0, 0, 100, 100);

    EnhancedPathShape *shape = new EnhancedPathShape(viewBox);

    shape->setShapeId(KoPathShapeId);
    shape->setStroke(new KoShapeStroke(1.0));
    shape->addModifiers(params->stringProperty("modifiers"));

    ListType handles = params->property("handles").toList();
    foreach (const QVariant &v, handles)
        shape->addHandle(v.toMap());

    ComplexType formulae = params->property("formulae").toMap();
    ComplexType::const_iterator formula = formulae.constBegin();
    ComplexType::const_iterator lastFormula = formulae.constEnd();
    for (; formula != lastFormula; ++formula)
        shape->addFormula(formula.key(), formula.value().toString());

    QStringList commands = params->property("commands").toStringList();
    foreach (const QString &cmd, commands)
        shape->addCommand(cmd);

    QVariant color;
    if (params->property("background", color))
        shape->setBackground(QSharedPointer<KoColorBackground>(new KoColorBackground(color.value<QColor>())));
    QSizeF size = shape->size();
    if (size.width() > size.height())
        shape->setSize(QSizeF(100, 100 * size.height() / size.width()));
    else
        shape->setSize(QSizeF(100 * size.width() / size.height(), 100));

    return shape;
}

KoProperties* EnhancedPathShapeFactory::dataToProperties(
    const QString &modifiers, const QStringList &commands,
    const ListType &handles, const ComplexType & formulae) const
{
    KoProperties *props = new KoProperties();
    props->setProperty("modifiers", modifiers);
    props->setProperty("commands", commands);
    props->setProperty("handles", handles);
    props->setProperty("formulae", formulae);
    props->setProperty("background", QVariant::fromValue<QColor>(QColor(Qt::red)));

    return props;
}

void EnhancedPathShapeFactory::addCross()
{
    QString modifiers("35");

    QStringList commands;
    commands.append("M $0 0");
    commands.append("L ?Right 0 ?Right $0 width $0 width ?Bottom ?Right ?Bottom");
    commands.append("L ?Right height $0 height $0 ?Bottom 0 ?Bottom 0 $0 $0 $0");
    commands.append("Z");

    ListType handles;
    ComplexType handle;
    handle["draw:handle-position"] = "$0 0";
    handle["draw:handle-range-x-minimum"] = '0';
    handle["draw:handle-range-x-maximum"] = "?Half";
    handles.append(QVariant(handle));

    ComplexType formulae;
    formulae["Right"] = "width - $0";
    formulae["Bottom"] = "height - $0";
    formulae["Half"] = "min(0.5 * height, 0.5 * width)";

    KoShapeTemplate t;
    t.id = KoPathShapeId;
    t.templateId = "cross";
    t.name = i18n("Cross");
    t.family = "funny";
    t.toolTip = i18n("A cross");
    t.iconName = koIconName("cross-shape");
    t.properties = dataToProperties(modifiers, commands, handles, formulae);

    addTemplate(t);
}

void EnhancedPathShapeFactory::addArrow()
{
    { // arrow right
        QString modifiers("60 35");

        QStringList commands;
        commands.append("M $0 $1");
        commands.append("L $0 0 width ?HalfHeight $0 height $0 ?LowerCorner 0 ?LowerCorner 0 $1");
        commands.append("Z");

        ListType handles;
        ComplexType handle;
        handle["draw:handle-position"] = "$0 $1";
        handle["draw:handle-range-x-minimum"] = '0';
        handle["draw:handle-range-x-maximum"] = "width";
        handle["draw:handle-range-y-minimum"] = '0';
        handle["draw:handle-range-y-maximum"] = "?HalfHeight";
        handles.append(QVariant(handle));

        ComplexType formulae;
        formulae["HalfHeight"] = "0.5 * height";
        formulae["LowerCorner"] = "height - $1";

        KoShapeTemplate t;
        t.id = KoPathShapeId;
        t.templateId = "arrow_right";
        t.name = i18n("Arrow");
        t.family = "arrow";
        t.toolTip = i18n("An arrow");
        t.iconName = koIconName("draw-arrow-forward");
        t.properties = dataToProperties(modifiers, commands, handles, formulae);

        addTemplate(t);
    }

    { // arrow left
        QString modifiers("40 35");

        QStringList commands;
        commands.append("M $0 $1");
        commands.append("L $0 0 0 ?HalfHeight $0 height $0 ?LowerCorner width ?LowerCorner width $1");
        commands.append("Z");

        ListType handles;
        ComplexType handle;
        handle["draw:handle-position"] = "$0 $1";
        handle["draw:handle-range-x-minimum"] = '0';
        handle["draw:handle-range-x-maximum"] = "width";
        handle["draw:handle-range-y-minimum"] = '0';
        handle["draw:handle-range-y-maximum"] = "?HalfHeight";
        handles.append(QVariant(handle));

        ComplexType formulae;
        formulae["HalfHeight"] = "0.5 * height";
        formulae["LowerCorner"] = "height - $1";

        KoShapeTemplate t;
        t.id = KoPathShapeId;
        t.templateId = "arrow_left";
        t.name = i18n("Arrow");
        t.family = "arrow";
        t.toolTip = i18n("An arrow");
        t.iconName = koIconName("draw-arrow-back");
        t.properties = dataToProperties(modifiers, commands, handles, formulae);

        addTemplate(t);
    }

    { // arrow top
        QString modifiers("35 40");

        QStringList commands;
        commands.append("M $0 $1");
        commands.append("L 0 $1 ?HalfWidth 0 width $1 ?RightCorner $1 ?RightCorner height $0 height");
        commands.append("Z");

        ListType handles;
        ComplexType handle;
        handle["draw:handle-position"] = "$0 $1";
        handle["draw:handle-range-x-minimum"] = '0';
        handle["draw:handle-range-x-maximum"] = "?HalfWidth";
        handle["draw:handle-range-y-minimum"] = '0';
        handle["draw:handle-range-y-maximum"] = "height";
        handles.append(QVariant(handle));

        ComplexType formulae;
        formulae["HalfWidth"] = "0.5 * width";
        formulae["RightCorner"] = "width - $0";

        KoShapeTemplate t;
        t.id = KoPathShapeId;
        t.templateId = "arrow_top";
        t.name = i18n("Arrow");
        t.family = "arrow";
        t.toolTip = i18n("An arrow");
        t.iconName = koIconName("draw-arrow-up");
        t.properties = dataToProperties(modifiers, commands, handles, formulae);

        addTemplate(t);
    }

    { // arrow bottom
        QString modifiers("35 60");

        QStringList commands;
        commands.append("M $0 $1");
        commands.append("L 0 $1 ?HalfWidth height width $1 ?RightCorner $1 ?RightCorner 0 $0 0");
        commands.append("Z");

        ListType handles;
        ComplexType handle;
        handle["draw:handle-position"] = "$0 $1";
        handle["draw:handle-range-x-minimum"] = '0';
        handle["draw:handle-range-x-maximum"] = "?HalfWidth";
        handle["draw:handle-range-y-minimum"] = '0';
        handle["draw:handle-range-y-maximum"] = "height";
        handles.append(QVariant(handle));

        ComplexType formulae;
        formulae["HalfWidth"] = "0.5 * width";
        formulae["RightCorner"] = "width - $0";

        KoShapeTemplate t;
        t.id = KoPathShapeId;
        t.templateId = "arrow_bottom";
        t.name = i18n("Arrow");
        t.family = "arrow";
        t.toolTip = i18n("An arrow");
        t.iconName = koIconName("draw-arrow-down");
        t.properties = dataToProperties(modifiers, commands, handles, formulae);

        addTemplate(t);
    }
}

void EnhancedPathShapeFactory::addSmiley()
{
    QString modifiers("17520");

    QStringList commands;
    commands.append("U 10800 10800 10800 10800 0 23592960");
    commands.append("Z");
    commands.append("N");
    commands.append("U 7305 7515 1165 1165 0 23592960");
    commands.append("Z");
    commands.append("N");
    commands.append("U 14295 7515 1165 1165 0 23592960");
    commands.append("Z");
    commands.append("N");
    commands.append("M 4870 ?f1");
    commands.append("C 8680 ?f2 12920 ?f2 16730 ?f1");
    commands.append("Z");
    commands.append("F");
    commands.append("N");

    ComplexType formulae;
    formulae["f0"] = "$0 -15510";
    formulae["f1"] = "17520-?f0";
    formulae["f2"] = "15510+?f0";

    ListType handles;
    ComplexType handle;
    handle["draw:handle-position"] = "10800 $0";
    handle["draw:handle-range-y-minimum"] = "15510";
    handle["draw:handle-range-y-maximum"] = "17520";
    handles.append(QVariant(handle));

    KoShapeTemplate t;
    t.id = KoPathShapeId;
    t.templateId = "smiley";
    t.name = i18n("Smiley");
    t.family = "funny";
    t.toolTip = i18n("Smiley");
    t.iconName = koIconName("smiley-shape");
    KoProperties* properties = dataToProperties(modifiers, commands, handles, formulae);
    properties->setProperty(QLatin1String("viewBox"), QRect(0, 0, 21600, 21600));
    t.properties = properties;

    addTemplate(t);
}

void EnhancedPathShapeFactory::addCircularArrow()
{
    QString modifiers("180 0 5500");

    QStringList commands;
    commands.append("B ?f3 ?f3 ?f20 ?f20 ?f19 ?f18 ?f17 ?f16");
    commands.append("W 0 0 21600 21600 ?f9 ?f8 ?f11 ?f10");
    commands.append("L ?f24 ?f23 ?f36 ?f35 ?f29 ?f28");
    commands.append("Z");
    commands.append("N");

    ComplexType formulae;

    formulae["f0"] = "$0";
    formulae["f1"] = "$1";
    formulae["f2"] = "$2";
    formulae["f3"] = "10800+$2";
    formulae["f4"] = "10800*sin($0 *(pi/180))";
    formulae["f5"] = "10800*cos($0 *(pi/180))";
    formulae["f6"] = "10800*sin($1 *(pi/180))";
    formulae["f7"] = "10800*cos($1 *(pi/180))";
    formulae["f8"] = "?f4 +10800";
    formulae["f9"] = "?f5 +10800";
    formulae["f10"] = "?f6 +10800";
    formulae["f11"] = "?f7 +10800";
    formulae["f12"] = "?f3 *sin($0 *(pi/180))";
    formulae["f13"] = "?f3 *cos($0 *(pi/180))";
    formulae["f14"] = "?f3 *sin($1 *(pi/180))";
    formulae["f15"] = "?f3 *cos($1 *(pi/180))";
    formulae["f16"] = "?f12 +10800";
    formulae["f17"] = "?f13 +10800";
    formulae["f18"] = "?f14 +10800";
    formulae["f19"] = "?f15 +10800";
    formulae["f20"] = "21600-?f3";
    formulae["f21"] = "13500*sin($1 *(pi/180))";
    formulae["f22"] = "13500*cos($1 *(pi/180))";
    formulae["f23"] = "?f21 +10800";
    formulae["f24"] = "?f22 +10800";
    formulae["f25"] = "$2 -2700";
    formulae["f26"] = "?f25 *sin($1 *(pi/180))";
    formulae["f27"] = "?f25 *cos($1 *(pi/180))";
    formulae["f28"] = "?f26 +10800";
    formulae["f29"] = "?f27 +10800";
    formulae["f30"] = "($1+45)*pi/180";
    formulae["f31"] = "sqrt(((?f29-?f24)*(?f29-?f24))+((?f28-?f23)*(?f28-?f23)))";
    formulae["f32"] = "sqrt(2)/2*?f31";
    formulae["f33"] = "?f32*sin(?f30)";
    formulae["f34"] = "?f32*cos(?f30)";
    formulae["f35"] = "?f28+?f33";
    formulae["f36"] = "?f29+?f34";

    ListType handles;
    ComplexType handle;
    handle["draw:handle-position"] = "$0 10800";
    handle["draw:handle-polar"] = "10800 10800";
    handle["draw:handle-radius-range-minimum"] = "10800";
    handle["draw:handle-radius-range-maximum"] = "10800";
    handles.append(QVariant(handle));

    handle.clear();
    handle["draw:handle-position"] = "$1 $2";
    handle["draw:handle-polar"] = "10800 10800";
    handle["draw:handle-radius-range-minimum"] = '0';
    handle["draw:handle-radius-range-maximum"] = "10800";
    handles.append(QVariant(handle));

    KoShapeTemplate t;
    t.id = KoPathShapeId;
    t.templateId = "circulararrow";
    t.name = i18n("Circular Arrow");
    t.family = "arrow";
    t.toolTip = i18n("A circular-arrow");
    t.iconName = koIconName("circular-arrow-shape");
    KoProperties* properties = dataToProperties(modifiers, commands, handles, formulae);
    properties->setProperty(QLatin1String("viewBox"), QRect(0, 0, 21600, 21600));
    t.properties = properties;
    addTemplate(t);
}

void EnhancedPathShapeFactory::addGearhead()
{
    QStringList commands;
    commands.append("M 20 70");
    commands.append("L 20 100 30 100 30 50 30 70 40 70 40 40 0 40 0 70 10 70 10 50 10 100 20 100");
    commands.append("Z");
    commands.append("N");

    uint toothCount = 10;
    qreal toothAngle = 360.0 / qreal(toothCount);
    //kDebug() <<"toothAngle =" << toothAngle;
    qreal outerRadius = 0.5 * 25.0;
    qreal innerRadius = 0.5 * 17.0;
    QPointF center(20, 25);
    qreal radian = (270.0 - 0.35 * toothAngle) * M_PI / 180.0;
    commands.append(QString("M %1 %2").arg(center.x() + innerRadius*cos(radian)).arg(center.y() + innerRadius*sin(radian)));
    QString cmd("L");
    for (uint i = 0; i < toothCount; ++i) {
        radian += 0.15 * toothAngle * M_PI / 180.0;
        cmd += QString(" %1 %2").arg(center.x() + outerRadius*cos(radian)).arg(center.y() + outerRadius*sin(radian));
        radian += 0.35 * toothAngle * M_PI / 180.0;
        cmd += QString(" %1 %2").arg(center.x() + outerRadius*cos(radian)).arg(center.y() + outerRadius*sin(radian));
        radian += 0.15 * toothAngle * M_PI / 180.0;
        cmd += QString(" %1 %2").arg(center.x() + innerRadius*cos(radian)).arg(center.y() + innerRadius*sin(radian));
        radian += 0.35 * toothAngle * M_PI / 180.0;
        cmd += QString(" %1 %2").arg(center.x() + innerRadius*cos(radian)).arg(center.y() + innerRadius*sin(radian));
    }
    //kDebug() <<"gear command =" << cmd;
    commands.append(cmd);
    commands.append("Z");
    commands.append("N");

    KoShapeTemplate t;
    t.id = KoPathShapeId;
    t.templateId = "gearhead";
    t.name = i18n("Gearhead");
    t.family = "funny";
    t.toolTip = i18n("A gearhead");
    t.iconName = koIconName("gearhead-shape");
    KoProperties* properties = dataToProperties(QString(), commands, ListType(), ComplexType());
    properties->setProperty("background", QVariant::fromValue<QColor>(QColor(Qt::blue)));
    properties->setProperty(QLatin1String("viewBox"), QRect(0, 0, 40, 90));
    t.properties = properties;
    addTemplate(t);
}

bool EnhancedPathShapeFactory::supports(const KoXmlElement & e, KoShapeLoadingContext &context) const
{
    Q_UNUSED(context);
    qInfo()<<Q_FUNC_INFO<<e.localName();
    return (e.localName() == "custom-shape" && e.namespaceURI() == KoXmlNS::draw);
}
