
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


#DEPENDPATH += .
#MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
#OBJECTS_DIR += debug
#UI_DIR += ./GeneratedFiles
#RCC_DIR += ./GeneratedFiles
#include(calligrasheets.pri)
