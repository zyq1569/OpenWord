# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = calligra_textediting_thesaurus
DESTDIR = ../../bin/libs/
QT += core xml network gui widgets printsupport concurrent dbus

DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra_textediting_thesaurus\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" calligra_textediting_thesaurus_EXPORTS
INCLUDEPATH += ../../../../../calligra/plugins/textediting/thesaurus \
    ../../../../../../src/calligra-v3.2.1/plugins/textediting/thesaurus \
    ../../../../../calligra/plugins/textediting/thesaurus/calligra_textediting_thesaurus_autogen/include_Debug \
    ../../../../../../src/calligra-v3.2.1/interfaces \
    ../../../../../calligra \
    ../../../../../../src/calligra-v3.2.1 \
    ../../../../../../src/calligra-v3.2.1/winquirks \
    ../../../../../../src/calligra-v3.2.1/libs/version \
    ../../../../../calligra/libs/version \
    ../../../../../../src/calligra-v3.2.1/libs/text \
    ../../../../../calligra/libs/text \
    ../../../../../../src/calligra-v3.2.1/libs/text/changetracker \
    ../../../../../../src/calligra-v3.2.1/libs/text/styles \
    ../../../../../../src/calligra-v3.2.1/libs/text/opendocument \
    ../../../../../../src/calligra-v3.2.1/libs/flake \
    ../../../../../../src/calligra-v3.2.1/libs/odf \
    ../../../../../../src/calligra-v3.2.1/libs/store \
    ../../../../../calligra/libs/odf \
    ../../../../../calligra/libs/store \
    ../../../../../../src/calligra-v3.2.1/libs/plugin \
    ../../../../../../src/calligra-v3.2.1/libs/pigment \
    ../../../../../calligra/libs/pigment \
    ../../../../../../src/calligra-v3.2.1/libs/pigment/compositeops \
    ../../../../../../src/calligra-v3.2.1/libs/pigment/resources \
    ../../../../../../src/calligra-v3.2.1/libs/kundo2 \
    ../../../../../calligra/libs/kundo2 \
    ../../../../../../src/calligra-v3.2.1/libs/widgetutils \
    ../../../../../../src/calligra-v3.2.1/libs/flake/commands \
    ../../../../../../src/calligra-v3.2.1/libs/flake/tools \
    ../../../../../../src/calligra-v3.2.1/libs/flake/svg \
    ../../../../../calligra/libs/flake \
    ../../../../../calligra/libs/widgetutils \
    ../../../../../../src/calligra-v3.2.1/libs/widgets \
    ../../../../../calligra/libs/widgets \
    $(QTDIR)/./mkspecs/win32-msvc \
    ../../../../../../../include/KF5/KIOCore \
    ../../../../../../../include/KF5 \
    ../../../../../../../include/KF5/KCoreAddons \
    ../../../../../../../include/KF5/KService \
    ../../../../../../../include/KF5/KConfigCore \
    ../../../../../../../include/KF5/KXmlGui \
    ../../../../../../../include/KF5/KConfigWidgets \
    ../../../../../../../include/KF5/KCodecs \
    ../../../../../../../include/KF5/KWidgetsAddons \
    ../../../../../../../include/KF5/KConfigGui \
    ../../../../../../../include/KF5/KAuth \
    ../../../../../../../include/KF5/KTextWidgets \
    ../../../../../../../include/KF5/SonnetUi \
    ../../../../../../../include/KF5/KIOWidgets \
    ../../../../../../../include/KF5/KIOGui \
    ../../../../../../../include/KF5/KWindowSystem \
    ../../../../../../../include/KF5/KJobWidgets \
    ../../../../../../../include/KF5/KCompletion
LIBS += -L"." \
    -l../../../lib/Debug/kowidgets \
    -l../../../lib/Debug/kotext \
    -l../../../lib/Debug/flake \
    -l../../../lib/Debug/koodf \
    -l../../../lib/Debug/kostore \
    -l../../../lib/Debug/kundo2 \
    -lD://lib/KF5XmlGui \
    -lD://lib/KF5TextWidgets \
    -lD://lib/KF5SonnetUi \
    -l../../../lib/Debug/pigmentcms \
    -l../../../lib/Debug/kowidgetutils \
    -lD://lib/KF5KIOWidgets \
    -lD://lib/KF5KIOGui \
    -lD://lib/KF5KIOCore \
    -lD://lib/KF5Crash \
    -lD://lib/KF5JobWidgets \
    -lD://lib/KF5Service \
    -lKF5::I18n \
    -lD://lib/KF5DBusAddons \
    -lD://lib/KF5Completion \
    -lD://lib/KF5WindowSystem \
    -lD://lib/KF5IconThemes \
    -lD://lib/KF5ConfigWidgets \
    -lD://lib/KF5WidgetsAddons \
    -lD://lib/KF5ConfigGui \
    -lD://lib/KF5Codecs \
    -lD://lib/KF5Auth \
    -lD://lib/KF5AuthCore \
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
include(calligra_textediting_thesaurus.pri)
