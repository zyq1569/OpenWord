

TEMPLATE     = lib
TARGET       = calligra_tool_defaults
LIBDIR       =  ../../bin/
DESTDIR      = ../../bin/libs/calligra/tools
QT          += core xml network gui widgets printsupport concurrent dbus

#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra-defaulttools\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" calligra_tool_defaults_EXPORTS

DEFINES     +=  calligra_tool_defaults_EXPORTS

INCLUDEPATH +=  ../../plugins/defaultTools \
                ../../interfaces \
                ../../ \
                ../../winquirks \
                ../../libs/version \
                ../../libs/text \
                ../../libs/text/changetracker \
                ../../libs/text/styles \
                ../../libs/text/opendocument \
                ../../libs/flake \
                ../../libs/odf \
                ../../libs/store \
                ../../libs/odf \
                ../../libs/store \
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
                ../../libs/textlayout \
                ../../libs/widgets \
                ../../libs/widgetutils \
                ../../libs/widgets



LIBS        +=    -L$${LIBDIR} \
                  -lkowidgets \
                  -lkotext \
                  -lflake \
                  -lpigmentcms \
                  -lkowidgetutils \
                  -lkoodf \
                  -lkostore \
                  -lkundo2

include(../../calligra.pri)
include(calligra_tool_defaults.pri)


DLLDESTDIR          = $$DLLDESTDIR/calligra/tools/
