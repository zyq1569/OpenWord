
TEMPLATE         = app
TARGET           = calligrasheets
DESTDIR          = ../../bin/libs/
QT              += core xml network gui widgets printsupport concurrent dbus
#DEFINES        += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligrawords\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\"

# EasyLogging++ is set to be thread safe, to not have a default log file, and to not handle crashes
#DEFINES        +=  ELPP_THREAD_SAFE ELPP_NO_DEFAULT_LOG_FILE ELPP_DISABLE_DEFAULT_CRASH_HANDLING
INCLUDEPATH     +=  ../  \
                    ../sheets \
                    ../sheets/part \
                    ../interfaces \
                    ../winquirks \
                    ../version \
                    ../libs/version \
                    ../libs/kundo2 \
                    ../libs/text \
                    ../libs/text/changetracker \
                    ../libs/text/styles \
                    ../libs/text/opendocument \
                    ../libs/flake \
                    ../libs/odf \
                    ../libs/store \
                    ../libs/store \
                    ../libs/plugin \
                    ../libs/pigment \
                    ../libs/pigment/compositeops \
                    ../libs/pigment/resources \
                    ../libs/kundo2 \
                    ../libs/widgetutils \
                    ../libs/flake/commands \
                    ../libs/flake/tools \
                    ../libs/flake/svg \
                    ../libs/flake \
                    ../libs/widgetutils \
                    ../libs/widgets \
                    ../libs/textlayout \
                    ../libs/main \
                    ../libs/main/config


#LIBS          +=    -L$${DESTDIR}  \
#                    -leasylog

include(../calligra.pri)
include(calligrasheets.pri)


LIBS          +=    -L$${DESTDIR} \
                    -lpigmentcms \
                    -lkowidgetutils \
                    -lkoodf \
                    -lkundo2 \
                    -lkoplugin \
                    -lkostore \
                    -lkomain \
                    -lkowidgets \
                    -lkotextlayout \
                    -lkotext \
                    -lflake \
                    -lpigmentcms \
                    -lkoversion



#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII COMPILING_TESTS NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligrasheets\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB KGUIADDONS_LIB CMAKE_INTDIR=\"Debug\"
#INCLUDEPATH += ../ \
#    ../../../../src/calligra-v3.2.1/sheets \
#    ../calligrasheets_autogen/include_Debug \
#    ../../../../src/calligra-v3.2.1/interfaces \
#    ../../ \
#    ../../../../src/calligra-v3.2.1 \
#    ../../../../src/calligra-v3.2.1/winquirks \
#    ../../../../src/calligra-v3.2.1/libs/version \
#    ../../libs/version \
#    ../../../../src/calligra-v3.2.1/libs/text \
#    ../../libs/text \
#    ../../../../src/calligra-v3.2.1/libs/text/changetracker \
#    ../../../../src/calligra-v3.2.1/libs/text/styles \
#    ../../../../src/calligra-v3.2.1/libs/text/opendocument \
#    ../../../../src/calligra-v3.2.1/libs/flake \
#    ../../../../src/calligra-v3.2.1/libs/odf \
#    ../../../../src/calligra-v3.2.1/libs/store \
#    ../../libs/odf \
#    ../../libs/store \
#    ../../../../src/calligra-v3.2.1/libs/plugin \
#    ../../../../src/calligra-v3.2.1/libs/pigment \
#    ../../libs/pigment \
#    ../../../../src/calligra-v3.2.1/libs/pigment/compositeops \
#    ../../../../src/calligra-v3.2.1/libs/pigment/resources \
#    ../../../../src/calligra-v3.2.1/libs/kundo2 \
#    ../../libs/kundo2 \
#    ../../../../src/calligra-v3.2.1/libs/widgetutils \
#    ../../../../src/calligra-v3.2.1/libs/flake/commands \
#    ../../../../src/calligra-v3.2.1/libs/flake/tools \
#    ../../../../src/calligra-v3.2.1/libs/flake/svg \
#    ../../libs/flake \
#    ../../libs/widgetutils \
#    ../../../../src/calligra-v3.2.1/libs/widgets \
#    ../../libs/widgets \
#    ../../../../src/calligra-v3.2.1/libs/textlayout \
#    ../../libs/textlayout \
#    ../../../../src/calligra-v3.2.1/libs/main \
#    ../../libs/main \
#    ../../../../src/calligra-v3.2.1/libs/main/config

#LIBS += -L"." \
#    -l../lib/Debug/kdeinit5_calligrasheets \
#    -l../lib/Debug/komain \
#    -l../lib/Debug/kowidgets \
#    -l../lib/Debug/kotextlayout \
#    -l../lib/Debug/kotext \
#    -l../lib/Debug/flake \
#    -l../lib/Debug/pigmentcms \
#    -l../lib/Debug/kowidgetutils \
#    -l../lib/Debug/koodf \
#    -l../lib/Debug/kostore \
#    -l../lib/Debug/kundo2 \
#    -l../lib/Debug/koversion \
#    -lD://lib/KF5KDELibs4Support \
#    -lD:/CraftRoot/lib/libKF5KIOFileWidgets.dll.a \
#    -lD:/CraftRoot/lib/libKF5Bookmarks.dll.a \
#    -lD:/CraftRoot/lib/libKF5Solid.dll.a \
#    -lD:/CraftRoot/lib/libKF5Notifications.dll.a \
#    -lD:/CraftRoot/lib/libKF5UnitConversion.dll.a \
#    -lD:/CraftRoot/lib/libKF5Parts.dll.a \
#    -lD:/CraftRoot/lib/libKF5TextWidgets.dll.a \
#    -lD:/CraftRoot/lib/libKF5SonnetUi.dll.a \
#    -lD:/CraftRoot/lib/libKF5KIOWidgets.dll.a \
#    -lD:/CraftRoot/lib/libKF5Completion.dll.a \
#    -lD:/CraftRoot/lib/libKF5KIOGui.dll.a \
#    -lD:/CraftRoot/lib/libKF5KIOCore.dll.a \
#    -lD:/CraftRoot/lib/libKF5Crash.dll.a \
#    -lD:/CraftRoot/lib/libKF5Service.dll.a \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libQt5Concurrent.a \
#    -lD:/CraftRoot/lib/libKF5WindowSystem.dll.a \
#    -lD:/CraftRoot/lib/libKF5JobWidgets.dll.a \
#    -lD:/CraftRoot/lib/libKF5XmlGui.dll.a \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libQt5PrintSupport.a \
#    -lD:/CraftRoot/lib/libKF5IconThemes.dll.a \
#    -lD:/CraftRoot/lib/libKF5ConfigWidgets.dll.a \
#    -lD:/CraftRoot/lib/libKF5WidgetsAddons.dll.a \
#    -lD:/CraftRoot/lib/libKF5Codecs.dll.a \
#    -lD:/CraftRoot/lib/libKF5ConfigGui.dll.a \
#    -lD:/CraftRoot/lib/libKF5ConfigCore.dll.a \
#    -lD:/CraftRoot/lib/libKF5Auth.dll.a \
#    -lD:/CraftRoot/lib/libKF5AuthCore.dll.a \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libQt5DBus.a \
#    -lD:/CraftRoot/lib/libKF5CoreAddons.dll.a \
#    -lD:/CraftRoot/lib/libKF5I18n.dll.a \
#    -lD:/CraftRoot/lib/libKF5GuiAddons.dll.a \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libQt5Network.a \
#    -lD:/CraftRoot/lib/libKF5ItemViews.dll.a \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libQt5Xml.a \
#    -lD:/CraftRoot/lib/libkdewin.dll.a \
#    -luuid \
#    -lole32 \
#    -luser32 \
#    -lnetapi32 \
#    -luserenv \
#    -lD:/CraftRoot/lib/libkdewin-qt-static.a \
#    -ladvapi32 \
#    -lshell32 \
#    -lws2_32 \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libQt5Widgets.a \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libQt5Gui.a \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libQt5Core.a \
#    -lC:/Qt/Qt5.14.1/5.14.1/mingw73_64/lib/libqtmain.a \
#    -lkernel32 \
#    -lgdi32 \
#    -lwinspool \
#    -loleaut32 \
#    -lcomdlg32 \
#    -l$(NOINHERIT)
#DEPENDPATH += .
#MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
#OBJECTS_DIR += debug
#UI_DIR += ./GeneratedFiles
#RCC_DIR += ./GeneratedFiles
#include(calligrasheets.pri)
