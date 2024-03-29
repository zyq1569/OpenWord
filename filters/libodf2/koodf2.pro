# ----------------------------------------------------
# 
# ------------------------------------------------------

TEMPLATE     =  lib
TARGET       =  koodf2
DESTDIR      =  ../../bin/libs/
QT          +=  core xml network gui widgets printsupport concurrent dbus
#DEFINES    +=  _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligrafilters\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" koodf2_EXPORTS


DEFINES     +=  koodf2_EXPORTS
INCLUDEPATH +=   ../../ \
                 ../../libs/odf \
                 ../../interfaces \
                 ../../winquirks \
                 ../../version \
                 ../../libs/store \
                 ../libodf2 \
                 ../libodf2/chart \
                 ../../interfaces \
                 ../../winquirks \
                 ../../version \
                 ../../filters/libmso


#DEPENDPATH += .
#MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
#OBJECTS_DIR += debug
#UI_DIR += ./GeneratedFiles
#RCC_DIR += ./GeneratedFiles
include(../../calligra.pri)
include(koodf2.pri)

msvc{
TARGET       =  odf2
LIBS        +=   -L$${DESTDIR} \
                 -lmso \
                 -lodf \
                 -lkostore
}else
{
LIBS        +=   -L$${DESTDIR} \
                 -lmso \
                 -lkoodf \
                 -lkostore
}

