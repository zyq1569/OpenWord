# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = calligrastagetoolanimation
DESTDIR = ../../../../../calligra/bin/Debug
QT += core xml network gui widgets printsupport concurrent dbus
CONFIG += debug
DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligrastage\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" calligrastagetoolanimation_EXPORTS
INCLUDEPATH += ../../../../../../calligra/stage/part/tools/animationtool \
    ../../../../../../../src/calligra-v3.2.1/stage/part/tools/animationtool \
    ../../../../../../calligra/stage/part/tools/animationtool/calligrastagetoolanimation_autogen/include_Debug \
    ../../../../../../../src/calligra-v3.2.1/interfaces \
    ../../../../../../calligra \
    ../../../../../../../src/calligra-v3.2.1 \
    ../../../../../../../src/calligra-v3.2.1/winquirks \
    ../../../../../../../src/calligra-v3.2.1/libs/version \
    ../../../../../../calligra/libs/version \
    ../../../../../../../src/calligra-v3.2.1/libs/text \
    ../../../../../../calligra/libs/text \
    ../../../../../../../src/calligra-v3.2.1/libs/text/changetracker \
    ../../../../../../../src/calligra-v3.2.1/libs/text/styles \
    ../../../../../../../src/calligra-v3.2.1/libs/text/opendocument \
    ../../../../../../../src/calligra-v3.2.1/libs/flake \
    ../../../../../../../src/calligra-v3.2.1/libs/odf \
    ../../../../../../../src/calligra-v3.2.1/libs/store \
    ../../../../../../calligra/libs/odf \
    ../../../../../../calligra/libs/store \
    ../../../../../../../src/calligra-v3.2.1/libs/plugin \
    ../../../../../../../src/calligra-v3.2.1/libs/pigment \
    ../../../../../../calligra/libs/pigment \
    ../../../../../../../src/calligra-v3.2.1/libs/pigment/compositeops \
    ../../../../../../../src/calligra-v3.2.1/libs/pigment/resources \
    ../../../../../../../src/calligra-v3.2.1/libs/kundo2 \
    ../../../../../../calligra/libs/kundo2 \
    ../../../../../../../src/calligra-v3.2.1/libs/widgetutils \
    ../../../../../../../src/calligra-v3.2.1/libs/flake/commands \
    ../../../../../../../src/calligra-v3.2.1/libs/flake/tools \
    ../../../../../../../src/calligra-v3.2.1/libs/flake/svg \
    ../../../../../../calligra/libs/flake \
    ../../../../../../calligra/libs/widgetutils \
    ../../../../../../../src/calligra-v3.2.1/libs/widgets \
    ../../../../../../calligra/libs/widgets \
    ../../../../../../../src/calligra-v3.2.1/libs/textlayout \
    ../../../../../../calligra/libs/textlayout \
    ../../../../../../../src/calligra-v3.2.1/libs/main \
    ../../../../../../calligra/libs/main \
    ../../../../../../../src/calligra-v3.2.1/libs/main/config \
    ../../../../../../../src/calligra-v3.2.1/libs/pageapp \
    ../../../../../../../src/calligra-v3.2.1/libs/pageapp/commands \
    ../../../../../../calligra/libs/pageapp \
    ../../../../../../../src/calligra-v3.2.1/stage/part \
    ../../../../../../calligra/stage/part \
    ../../../../../../../src/calligra-v3.2.1/stage/part \
    $(QTDIR)/./mkspecs/win32-msvc \
    ../../../../../../../../include/KF5/KIOCore \
    ../../../../../../../../include/KF5 \
    ../../../../../../../../include/KF5/KCoreAddons \
    ../../../../../../../../include/KF5/KService \
    ../../../../../../../../include/KF5/KConfigCore \
    ../../../../../../../../include/KF5/KXmlGui \
    ../../../../../../../../include/KF5/KConfigWidgets \
    ../../../../../../../../include/KF5/KCodecs \
    ../../../../../../../../include/KF5/KWidgetsAddons \
    ../../../../../../../../include/KF5/KConfigGui \
    ../../../../../../../../include/KF5/KAuth \
    ../../../../../../../../include/KF5/KTextWidgets \
    ../../../../../../../../include/KF5/SonnetUi \
    ../../../../../../../../include/KF5/KIOWidgets \
    ../../../../../../../../include/KF5/KIOGui \
    ../../../../../../../../include/KF5/KWindowSystem \
    ../../../../../../../../include/KF5/KJobWidgets \
    ../../../../../../../../include/KF5/KCompletion \
    ../../../../../../../../include/KF5/KIconThemes
LIBS += -L"." \
    -l../../../../lib/Debug/calligrastageprivate \
    -l../../../../lib/Debug/kopageapp \
    -l../../../../lib/Debug/komain \
    -l../../../../lib/Debug/kowidgets \
    -lD://lib/KF5KIOWidgets \
    -lD://lib/KF5KIOGui \
    -lD://lib/KF5JobWidgets \
    -lD://lib/KF5Completion \
    -l../../../../lib/Debug/kotextlayout \
    -l../../../../lib/Debug/kotext \
    -l../../../../lib/Debug/flake \
    -l../../../../lib/Debug/pigmentcms \
    -l../../../../lib/Debug/kowidgetutils \
    -l../../../../lib/Debug/koodf \
    -l../../../../lib/Debug/koversion \
    -l../../../../lib/Debug/kostore \
    -lD://lib/KF5KIOCore \
    -lD://lib/KF5Service \
    -lD://lib/KF5Crash \
    -lD://lib/KF5DBusAddons \
    -l../../../../lib/Debug/kundo2 \
    -lD://lib/KF5XmlGui \
    -lD://lib/KF5IconThemes \
    -lD://lib/KF5TextWidgets \
    -lKF5::I18n \
    -lD://lib/KF5ConfigWidgets \
    -lD://lib/KF5WidgetsAddons \
    -lD://lib/KF5ConfigGui \
    -lD://lib/KF5Codecs \
    -lD://lib/KF5Auth \
    -lD://lib/KF5AuthCore \
    -lD://lib/KF5SonnetUi \
    -lD://lib/KF5WindowSystem \
    -lD://lib/KF5CoreAddons \
    -lD://lib/KF5ConfigCore \
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
include(calligrastagetoolanimation.pri)
