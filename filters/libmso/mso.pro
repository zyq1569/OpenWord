# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = mso
DESTDIR = ../../../calligra/lib/Debug
QT += core xml network gui widgets printsupport concurrent dbus
CONFIG += staticlib release
DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligrafilters\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\"
INCLUDEPATH += ../../../../calligra/filters/libmso \
    ../../../../../src/calligra-v3.2.1/filters/libmso \
    ../../../../calligra/filters/libmso/mso_autogen/include_Debug \
    ../../../../../src/calligra-v3.2.1/interfaces \
    ../../../../calligra \
    ../../../../../src/calligra-v3.2.1 \
    ../../../../../src/calligra-v3.2.1/winquirks \
    ../../../../../src/calligra-v3.2.1/libs/version \
    ../../../../calligra/libs/version \
    ../../../../../src/calligra-v3.2.1/libs/odf \
    ../../../../../src/calligra-v3.2.1/libs/store \
    ../../../../calligra/libs/odf \
    ../../../../calligra/libs/store \
    ../../../../../inst/zlib123dll/include \
    $(QTDIR)/./mkspecs/win32-msvc \
    ../../../../../../include/KF5/KIOCore \
    ../../../../../../include/KF5 \
    ../../../../../../include/KF5/KCoreAddons \
    ../../../../../../include/KF5/KService \
    ../../../../../../include/KF5/KConfigCore
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(mso.pri)
