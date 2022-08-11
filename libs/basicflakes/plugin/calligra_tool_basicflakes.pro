
TEMPLATE    = lib
LIBDIR      =  ../../../bin/libs/
TARGET      = calligra_tool_basicflakes
DESTDIR     = ../../../bin/libs/calligra/tools
QT         += core xml network gui widgets printsupport concurrent dbus

#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" calligra_tool_basicflakes_EXPORTS

DEFINES     += calligra_tool_basicflakes_EXPORTS

INCLUDEPATH +=  ../../../libs/basicflakes/plugin \
                ../../../interfaces \
                ../../../ \
                ../../../winquirks \
                ../../../libs/version \
                ../../../libs/flake \
                ../../../libs/odf \
                ../../../libs/store \
                ../../../libs/odf \
                ../../../libs/store \
                ../../../libs/plugin \
                ../../../libs/pigment \
                ../../../libs/pigment/compositeops \
                ../../../libs/pigment/resources \
                ../../../libs/kundo2 \
                ../../../libs/widgetutils \
                ../../../libs/flake/commands \
                ../../../libs/flake/tools \
                ../../../libs/flake/svg \
                ../../../libs/flake \
                ../../../libs/text \
                ../../../libs/text/changetracker \
                ../../../libs/text/styles \
                ../../../libs/text/opendocument \
                ../../../libs/widgetutils \
                ../../../libs/widgets \
                ../../../libs/basicflakes/tools \
                ../../../libs/basicflakes
msvc{
LIBS      +=   -L$${LIBDIR} \
               -lbasicflakes \
               -lkowidgets \
               -lkotext \
               -lflake \
               -lpigmentcms \
               -lkowidgetutils \
               -lodf \
               -lkostore \
               -lkundo2
}else
{
LIBS      +=   -L$${LIBDIR} \
               -lbasicflakes \
               -lkowidgets \
               -lkotext \
               -lflake \
               -lpigmentcms \
               -lkowidgetutils \
               -lkoodf \
               -lkostore \
               -lkundo2
}


#\
#        -lkernel32 \
#        -luser32 \
#        -lgdi32 \
#        -lwinspool \
#        -lshell32 \
#        -lole32 \
#        -loleaut32 \
#        -luuid \
#        -lcomdlg32 \
#        -ladvapi32

include(../../../calligra.pri)
include(calligra_tool_basicflakes.pri)


DLLDESTDIR          =  $$DLLDESTDIR/calligra/tools
