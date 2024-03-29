# ----------------------------------------------------
# 
# ------------------------------------------------------

TEMPLATE      =    lib
TARGET        =    koodfreader
DESTDIR       =    ../../bin/libs/
QT           +=    core xml network gui widgets printsupport concurrent dbus

#DEFINES     += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligrafilters\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" koodfreader_EXPORTS

DEFINES      +=     koodfreader_EXPORTS
INCLUDEPATH  +=    ../libodfreader \
                   ../../interfaces \
                   ../../winquirks \
                   ../../libs/version \
                   ../../libs/odf \
                   ../../libs/store \
                   ../../filters/libodf2 \
                   ../../filters/libodf2/chart \
                   ../../libs/text \
                   ../../libs/text/changetracker \
                   ../../libs/text/styles \
                   ../../libs/text/opendocument \
                   ../../libs/flake \
                   ../../libs/plugin \
                   ../../libs/pigment \
                   ../../libs/pigment/compositeops \
                   ../../libs/pigment/resources \
                   ../../libs/kundo2 \
                   ../../libs/widgetutils \
                   ../../libs/flake/commands \
                   ../../libs/flake/tools \
                   ../../libs/flake/svg \
                   ../../libs/flake \
                   ../../libs/widgetutils \
                   ../../libs/widgets \
                   ../../libs/textlayout \
                   ../../libs/main \
                   ../../libs/main/config \
                   ../../filters/libodf2

msvc{
LIBS       +=   -L$${DESTDIR} \
                -lodf2 \
                -lodf \
                -lkostore
}else
{
LIBS       +=   -L$${DESTDIR} \
                -lkoodf2 \
                -lkoodf \
                -lkostore
}



include(../../calligra.pri)
include(koodfreader.pri)
