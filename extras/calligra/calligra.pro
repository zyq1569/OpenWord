
TEMPLATE = app
TARGET = calligra
DESTDIR = ../../bin/libs/
QT += core xml network gui widgets printsupport concurrent dbus

#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\"
INCLUDEPATH +=  ../../ \
                ../../interfaces \
                ../../winquirks \
                ../../version \
                ../../winquirks \
                ../../libs/version \
                ../../libs/text \
                ../../libs/text/changetracker \
                ../../text/styles \
                ../../text/opendocument  \
                ../../libs/text \
                ../../libs/plugin \
                ../../libs/pigment \
                ../../libs/pigment/compositeops \
                ../../libs/pigment/resources \
                ../../libs/kundo2 \
                ../../libs/widgetutils \
                ../../libs/flake/commands \
                ../../libs/flake/tools \
                ../../libs/flake/svg \
                ../../libs/widgets \
                ../../libs/textlayout \
                ../../libs/textlayout \
                ../../libs/main \
                ../../libs/main/config \
                ../../libs/odf \
                ../../libs/store \
                ../../libs/plugin \
                ../../libs/flake \
                ../../libs/odf \
                ../../libs/store \
                ../../libs/pigment \
                ../../libs/kundo2 \
                ../../libs/flake \
                ../../libs/widgetutils \
                ../../libs/widgets \
                ../../libs/main

LIBS += -L$${DESTDIR} \
        -lkomain \
        -lkowidgets \
        -lkotextlayout \
        -lkotext \
        -lflake \
        -lpigmentcms \
        -lkowidgetutils \
        -lkoodf \
        -lkostore \
        -lkundo2 \
        -lkoversion

#    -lD://lib/KF5Service \
#    -lD://lib/KF5KIOWidgets \
#    -lD://lib/KF5WidgetsAddons \
#    -lD://lib/KF5KIOGui \
#    -lD://lib/KF5JobWidgets \
#    -lD://lib/KF5Completion \
#    -lD://lib/KF5KIOCore \
#    -lD://lib/KF5Crash \
#    -lD://lib/KF5XmlGui \
#    -lD://lib/KF5WindowSystem \
#    -lD://lib/KF5TextWidgets \
#    -lKF5::I18n \
#    -lD://lib/KF5SonnetUi \
#    -lD://lib/KF5DBusAddons \
#    -lD://lib/KF5IconThemes \
#    -lD://lib/KF5ConfigWidgets \
#    -lD://lib/KF5ConfigGui \
#    -lD://lib/KF5Codecs \
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
include(calligra.pri)
