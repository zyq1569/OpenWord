

#TEMPLATE = app
#TARGET = TestBlockLayout
#DESTDIR = ../../../bin/Debug
#QT += core xml network gui widgets printsupport concurrent dbus
#CONFIG += qtestlib debug console
#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII COMPILING_TESTS NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB QT_TESTLIB_LIB QT_TESTCASE_BUILDDIR=\"D:/Dev/build/calligra-vc2013\" CMAKE_INTDIR=\"Debug\"
#INCLUDEPATH += ../ \
#    ../../ \
#    ../../../widgetutils \

#LIBS += -L"." \
#    -l../../../lib/Debug/kotextlayout \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libQt5Test.a \
#    -l../../../lib/Debug/kotext \
#    -l../../../lib/Debug/flake \
#    -l../../../lib/Debug/pigmentcms \
#    -l../../../lib/Debug/kowidgetutils \
#    -l../../../lib/Debug/koodf \
#    -l../../../lib/Debug/kostore \
#    -l../../../lib/Debug/kundo2 \

# ----------------------------------------------------
#
# ------------------------------------------------------

TEMPLATE     =  app
TARGET       =  TestBlockLayout
DESTDIR      =  ../../../bin/
QT          +=  core xml network gui widgets printsupport concurrent dbus
QT          +=  testlib
win32 {

msvc: DEFINES +=  BOOST_ALL_NO_LIB  KCOREADDONS_LIB    NOMINMAX  QT_CONCURRENT_LIB  QT_CORE_LIB  QT_DBUS_LIB   QT_GUI_LIB  QT_NETWORK_LIB  QT_NO_CAST_TO_ASCII  QT_NO_DEBUG  QT_NO_SIGNALS_SLOTS_KEYWORDS  QT_NO_URL_CAST_FROM_STRING  QT_PRINTSUPPORT_LIB  QT_STRICT_ITERATORS  QT_USE_QSTRINGBUILDER  QT_WIDGETS_LIB  QT_XML_LIB   UNICODE  WIN32_LEAN_AND_MEAN  WINVER=0x0600  _CRT_NONSTDC_NO_DEPRECATE  _CRT_SECURE_NO_DEPRECATE  _CRT_SECURE_NO_WARNINGS  _SCL_SECURE_NO_WARNINGS  _UNICODE  _USE_MATH_DEFINES  _WIN32_IE=0x0600  _WIN32_WINNT=0x0600

}

DEFINES     +=  kotextlayout_EXPORTS
INCLUDEPATH +=  ../ \
                 ../../../interfaces \
                 ../../../ \
                 ../../../winquirks \
                 ../../../version \
                 ../../text/changetracker \
                 ../../text/styles \
                 ../../text \
                 ../../text/opendocument \
                 ../../flake \
                 ../../odf \
                 ../../store \
                 ../../odf \
                 ../../store \
                 ../../kundo2 \
                 ../../widgetutils \
                 ../../flake/commands \
                 ../../flake/tools \
                 ../../flake/svg \
                 ../../flake \
                 ../../widgetutils \
                 ../../plugin \
                 ../../pigment \
                 ../../pigment/compositeops \
                 ../../pigment/resources



include(../../../calligra.pri)
include(TestBlockLayout.pri)


LIBS      +=     -L$${DESTDIR} \
                 -lkotextlayout \
                 -lkotext \
                 -lflake \
                 -lpigmentcms \
                 -lkoplugin \
                 -lkowidgetutils \
                 -lkoodf \
                 -lkostore \
                 -lkundo2


