
TEMPLATE       = lib
TARGET         = basicflakes
DESTDIR        = ../../bin/libs/
msvc: DESTDIR  = ../../MS_bin/libs/
QT            += core xml network gui widgets printsupport concurrent dbus
#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" basicflakes_EXPORTS

#win32 {

#msvc: DEFINES +=  BOOST_ALL_NO_LIB  KCOREADDONS_LIB    NOMINMAX  QT_CONCURRENT_LIB  QT_CORE_LIB  QT_DBUS_LIB   QT_GUI_LIB  QT_NETWORK_LIB  QT_NO_CAST_TO_ASCII  QT_NO_DEBUG  QT_NO_SIGNALS_SLOTS_KEYWORDS  QT_NO_URL_CAST_FROM_STRING  QT_PRINTSUPPORT_LIB  QT_STRICT_ITERATORS  QT_USE_QSTRINGBUILDER  QT_WIDGETS_LIB  QT_XML_LIB   UNICODE  WIN32_LEAN_AND_MEAN  WINVER=0x0600  _CRT_NONSTDC_NO_DEPRECATE  _CRT_SECURE_NO_DEPRECATE  _CRT_SECURE_NO_WARNINGS  _SCL_SECURE_NO_WARNINGS  _UNICODE  _USE_MATH_DEFINES  _WIN32_IE=0x0600  _WIN32_WINNT=0x0600  kotext_EXPORTS
#use error!!!!!
#}

DEFINES       += basicflakes_EXPORTS
INCLUDEPATH   += ../ \
                 ../../interfaces \
                 ../../../ \
                 ../../winquirks \
                 ../../libs/version \
                 ../../libs/widgets \
                 ../../libs/plugin \
                 ../../libs/pigment \
                 ../../libs/pigment/compositeops \
                 ../../libs/pigment/resources \
                 ../../libs/flake \
                 ../../libs/odf \
                 ../../libs/store \
                 ../../libs/odf \
                 ../../libs/store \
                 ../../libs/kundo2 \
                 ../../libs/widgetutils \
                 ../../libs/flake/commands \
                 ../../libs/flake/tools \
                 ../../libs/flake/svg \
                 ../../libs/flake \
                 ../../libs/widgets \
                 ../../libs/text \
                 ../../libs/widgetutils


#LIBS       +=   -L$${DESTDIR} \
#                -lkowidgets \
#                -lkotext \
#                -lflake \
#                -lpigmentcms \
#                -lkoodf \
#                -lkostore \
#                -lkundo2 \
#                -lkowidgetutils


include(../../calligra.pri)
include(basicflakes.pri)


msvc{
LIBS         +=  -L$${ALL_LIBS_DIR}\
                -lkowidgets \
                -lkotext \
                -lflake \
                -lpigmentcms \
                -lodf \
                -lkostore \
                -lkundo2 \
                -lkowidgetutils
}else
{
LIBS         +=  -L$${ALL_LIBS_DIR}\
                -lkowidgets \
                -lkotext \
                -lflake \
                -lpigmentcms \
                -lkoodf \
                -lkostore \
                -lkundo2 \
                -lkowidgetutils
}


#for build error!!
#add: #include "../../../../libs/basicflakes/tools/KoCreatePathTool_p.h" in " :moc_KoCreatePathTool.cpp "

