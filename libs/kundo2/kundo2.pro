# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = kundo2
DESTDIR = ../../../calligra/bin/Debug
QT += core xml gui widgets dbus
CONFIG += debug
DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_DBUS_LIB CMAKE_INTDIR=\"Debug\" kundo2_EXPORTS
INCLUDEPATH += ../../../../calligra/libs/kundo2 \
    ../../../../../src/calligra-v3.2.1/libs/kundo2 \
    ../../../../calligra/libs/kundo2/kundo2_autogen/include_Debug \
    ../../../../../src/calligra-v3.2.1/interfaces \
    ../../../../calligra \
    ../../../../../src/calligra-v3.2.1 \
    ../../../../../src/calligra-v3.2.1/winquirks \
    ../../../../../src/calligra-v3.2.1/libs/version \
    ../../../../calligra/libs/version \
    ../../../../../../include/KF5/KXmlGui \
    ../../../../../../include/KF5 \
    $(QTDIR)/./mkspecs/win32-msvc \
    ../../../../../../include/KF5/KConfigCore \
    ../../../../../../include/KF5/KConfigWidgets \
    ../../../../../../include/KF5/KCodecs \
    ../../../../../../include/KF5/KWidgetsAddons \
    ../../../../../../include/KF5/KConfigGui \
    ../../../../../../include/KF5/KAuth \
    ../../../../../../include/KF5/KCoreAddons
LIBS += -L"." \
    -lKF5::I18n \
    -lD://lib/KF5XmlGui \
    -lD://lib/KF5ConfigWidgets \
    -lD://lib/KF5Codecs \
    -lD://lib/KF5WidgetsAddons \
    -lD://lib/KF5ConfigGui \
    -lD://lib/KF5ConfigCore \
    -lD://lib/KF5Auth \
    -lD://lib/KF5AuthCore \
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
include(kundo2.pri)
