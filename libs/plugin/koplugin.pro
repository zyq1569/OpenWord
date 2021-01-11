# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = koplugin
DESTDIR = ../../../calligra/bin/Debug
QT += core
CONFIG += debug
DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" KCOREADDONS_LIB CMAKE_INTDIR=\"Debug\" koplugin_EXPORTS
INCLUDEPATH += ../../../../calligra/libs/plugin \
    ../../../../../src/calligra-v3.2.1/libs/plugin \
    ../../../../calligra/libs/plugin/koplugin_autogen/include_Debug \
    ../../../../../src/calligra-v3.2.1/interfaces \
    ../../../../calligra \
    ../../../../../src/calligra-v3.2.1 \
    ../../../../../src/calligra-v3.2.1/winquirks \
    ../../../../../src/calligra-v3.2.1/libs/version \
    ../../../../calligra/libs/version \
    $(QTDIR)/./mkspecs/win32-msvc \
    ../../../../../../include/KF5/KConfigCore \
    ../../../../../../include/KF5 \
    ../../../../../../include/KF5/KCoreAddons
LIBS += -L"." \
    -lD://lib/KF5ConfigCore \
    -lD://lib/KF5CoreAddons \
    -lkernel32 \
    -luser32 \
    -lgdi32 \
    -lwinspool \
    -lshell32 \
    -lole32 \
    -loleaut32 \
    -luuid \
    -lcomdlg32 \
    -ladvapi32 \
    -l$(NOINHERIT)
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(koplugin.pri)
