# ----------------------------------------------------
#
# ------------------------------------------------------

TEMPLATE = lib
TARGET   = chartshapecore
DESTDIR  = ../../bin/libs/
QT      += core xml network gui widgets printsupport concurrent dbus
CONFIG  += staticlib debug_and_release
#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra_shape_chart\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\"
INCLUDEPATH +=  ../../plugins/chartshape \
                ../../interfaces \
                ../../calligra \
                ../../ \
                ../../winquirks \
                ../../libs/version \
                ../../plugins/chartshape/dialogs \
                ../../plugins/chartshape/widgets \
                ../../libs/text \
                ../../libs/text/changetracker \
                ../../libs/text/styles \
                ../../libs/text/opendocument \
                ../../libs/flake \
                ../../libs/odf \
                ../../libs/store \
                ../../libs/odf \
                ../../libs/store \
                ../../libs/plugin \
                ../../libs/pigment \
                ../../libs/pigment/compositeops \
                ../../libs/pigment/resources \
                ../../libs/kundo2 \
                ../../libs/widgetutils \
                ../../libs/flake/commands \
                ../../libs/flake/tools \
                ../../libs/flake/svg \
                ../../libs/flake \
                ../../libs/widgetutils \
                ../../libs/widgets \
                ../../libs/textlayout \
                ../../libs/main \
                ../../libs/main/config
# \
#    $(QTDIR)/./mkspecs/win32-msvc \
#    ../../../../../../include/KF5/KIOCore \
#    ../../../../../../include/KF5 \
#    ../../../../../../include/KF5/KCoreAddons \
#    ../../../../../../include/KF5/KService \
#    ../../../../../../include/KF5/KConfigCore \
#    ../../../../../../include/KF5/KXmlGui \
#    ../../../../../../include/KF5/KConfigWidgets \
#    ../../../../../../include/KF5/KCodecs \
#    ../../../../../../include/KF5/KWidgetsAddons \
#    ../../../../../../include/KF5/KConfigGui \
#    ../../../../../../include/KF5/KAuth \
#    ../../../../../../include/KF5/KTextWidgets \
#    ../../../../../../include/KF5/SonnetUi \
#    ../../../../../../include/KF5/KIOWidgets \
#    ../../../../../../include/KF5/KIOGui \
#    ../../../../../../include/KF5/KWindowSystem \
#    ../../../../../../include/KF5/KJobWidgets \
#    ../../../../../../include/KF5/KCompletion

#LIBS += -L"."
#DEPENDPATH += .
#MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
#OBJECTS_DIR += debug
#UI_DIR += D:/KDE/build/calligra/plugins/chartshape
#RCC_DIR += ./GeneratedFiles

include(../../calligra.pri)
include(chartshapecore.pri)
