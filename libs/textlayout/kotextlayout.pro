# ----------------------------------------------------
# 
# ------------------------------------------------------

TEMPLATE     =  lib
TARGET       =  kotextlayout
DESTDIR      =  ../../bin/libs/
QT          +=  core xml network gui widgets printsupport concurrent dbus

#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" kotextlayout_EXPORTS

DEFINES     +=  kotextlayout_EXPORTS
INCLUDEPATH +=  ../text \
                 ../../interfaces \
                 ../../ \
                 ../../winquirks \
                 ../../version \
                 ../text/changetracker \
                 ../text/styles \
                 ../text/opendocument \
                 ../flake \
                 ../odf \
                 ../store \
                 ../odf \
                 ../store \
                 ../kundo2 \
                 ../widgetutils \
                 ../flake/commands \
                 ../flake/tools \
                 ../flake/svg \
                 ../flake \
                 ../widgetutils \
                 ../plugin \
                 ../pigment \
                 ../pigment/compositeops \
                 ../pigment/resources



include(../../calligra.pri)
include(kotextlayout.pri)


LIBS      +=     -L$${DESTDIR} \
                 -lkotext \
                 -lflake \
                 -lpigmentcms \
                 -lkoplugin \
                 -lkowidgetutils \
                 -lkoodf \
                 -lkostore \
                 -lkundo2

