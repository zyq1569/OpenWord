
TEMPLATE     = lib
TARGET       = calligra_textediting_spellcheck
LIBDIR       = ../../../bin/libs/
DESTDIR      = ../../../bin/libs/
QT          += core xml network gui widgets printsupport concurrent dbus

DEFINES     += calligra_textediting_spellcheck_EXPORTS

INCLUDEPATH +=  ../../../interfaces \
                ../../../ \
                ../../../winquirks \
                ../../../libs/version \
                ../../../libs/text \
                ../../../libs/text/changetracker \
                ../../../libs/text/styles \
                ../../../libs/text/opendocument \
                ../../../libs/flake \
                ../../../libs/odf \
                ../../../libs/store \
                ../../../libs/odf \
                ../../../libs/store \
                ../../../libs/plugin \
                ../../../libs/pigment/compositeops \
                ../../../libs/pigment/resources \
                ../../../libs/kundo2 \
                ../../../libs/widgetutils \
                ../../../libs/flake/commands \
                ../../../libs/flake/tools \
                ../../../libs/flake/svg \
                ../../../libs/flake \
                ../../../libs/widgetutils \
                ../../../libs/textlayout \
                ../../../libs/widgets

msvc{
LIBS       +=   -L$${LIBDIR} \
                -lkotextlayout \
                -lkotext \
                -lflake \
                -lodf \
                -lkostore \
                -lkundo2 \
                -lpigmentcms \
                -lkowidgetutils
}else
{
LIBS       +=   -L$${LIBDIR} \
                -lkotextlayout \
                -lkotext \
                -lflake \
                -lkoodf \
                -lkostore \
                -lkundo2 \
                -lpigmentcms \
                -lkowidgetutils
}



#DEFINES     += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra_textediting_spellcheck\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" calligra_textediting_spellcheck_EXPORTS
#INCLUDEPATH += ../../../../../calligra/plugins/textediting/spellcheck \
#    ../../../../../../plugins/textediting/spellcheck \
#    ../../../../../calligra/plugins/textediting/spellcheck/calligra_textediting_spellcheck_autogen/include_Debug \
#    ../../../../../../interfaces \
#    ../../../../../calligra \
#    ../../../../../../src/calligra-v3.2.1 \
#    ../../../../../../winquirks \
#    ../../../../../../libs/version \
#    ../../../../../calligra/libs/version \
#    ../../../../../../libs/text \
#    ../../../../../calligra/libs/text \
#    ../../../../../../libs/text/changetracker \
#    ../../../../../../libs/text/styles \
#    ../../../../../../libs/text/opendocument \
#    ../../../../../../libs/flake \
#    ../../../../../../libs/odf \
#    ../../../../../../libs/store \
#    ../../../../../calligra/libs/odf \
#    ../../../../../calligra/libs/store \
#    ../../../../../../libs/plugin \
#    ../../../../../../libs/pigment \
#    ../../../../../calligra/libs/pigment \
#    ../../../../../../libs/pigment/compositeops \
#    ../../../../../../libs/pigment/resources \
#    ../../../../../../libs/kundo2 \
#    ../../../../../calligra/libs/kundo2 \
#    ../../../../../../libs/widgetutils \
#    ../../../../../../libs/flake/commands \
#    ../../../../../../libs/flake/tools \
#    ../../../../../../libs/flake/svg \
#    ../../../../../calligra/libs/flake \
#    ../../../../../../libs/textlayout \
#    ../../../../../calligra/libs/textlayout \
#    ../../../../../calligra/libs/widgetutils \
#    $(QTDIR)/./mkspecs/win32-msvc \
#    ../../../../../../../include/KF5/KIOCore \
#    ../../../../../../../include/KF5 \
#    ../../../../../../../include/KF5/KCoreAddons \
#    ../../../../../../../include/KF5/KService \
#    ../../../../../../../include/KF5/KConfigCore \
#    ../../../../../../../include/KF5/KXmlGui \
#    ../../../../../../../include/KF5/KConfigWidgets \
#    ../../../../../../../include/KF5/KCodecs \
#    ../../../../../../../include/KF5/KWidgetsAddons \
#    ../../../../../../../include/KF5/KConfigGui \
#    ../../../../../../../include/KF5/KAuth \
#    ../../../../../../../include/KF5/KTextWidgets \
#    ../../../../../../../include/KF5/SonnetUi \
#    ../../../../../../../include/KF5/SonnetCore
#LIBS += -L"." \
#    -l../../../lib/Debug/kotextlayout \
#    -l../../../lib/Debug/kotext \
#    -l../../../lib/Debug/flake \
#    -l../../../lib/Debug/pigmentcms \
#    -l../../../lib/Debug/kowidgetutils \
#    -l../../../lib/Debug/koodf \
#    -l../../../lib/Debug/kostore \
#    -lD://lib/KF5KIOCore \
#    -lD://lib/KF5Service \
#    -lD://lib/KF5Crash \
#    -lD://lib/KF5DBusAddons \
#    -l../../../lib/Debug/kundo2 \
#    -lD://lib/KF5XmlGui \
#    -lD://lib/KF5TextWidgets \
#    -lD://lib/KF5SonnetUi \
#    -lD://lib/KF5SonnetCore \
#    -lKF5::I18n \
#    -lD://lib/KF5ConfigWidgets \
#    -lD://lib/KF5Codecs \
#    -lD://lib/KF5WidgetsAddons \
#    -lD://lib/KF5ConfigGui \
#    -lD://lib/KF5Auth \
#    -lD://lib/KF5AuthCore \
#    -lD://lib/KF5ConfigCore \
#    -lD://lib/KF5CoreAddons \
#    -lkernel32 \
#    -luser32 \
#    -lgdi32 \
#    -lwinspool \
#    -lshell32 \
#    -lole32 \
#    -loleaut32 \
#    -luuid \
#    -lcomdlg32 \
#    -ladvapi32 \
#    -l$(NOINHERIT)
#DEPENDPATH += .
#MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
#OBJECTS_DIR += debug
#UI_DIR += ./GeneratedFiles
#RCC_DIR += ./GeneratedFiles
include(calligra_textediting_spellcheck.pri)
include(../../../calligra.pri)


DLLDESTDIR     =  $$DLLDESTDIR/calligra/textediting
