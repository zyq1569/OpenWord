# ----------------------------------------------------
# 
# ------------------------------------------------------

#SDK_INSTALL_PREFIX = D:/CraftRoot/include

TEMPLATE    = lib
TARGET      = kotext
DESTDIR     = ../../bin/libs/
QT         += core xml network gui widgets printsupport concurrent dbus
##CONFIG += debug
##DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" kotext_EXPORTS
#DEFINES += KWIDGETSADDONS_DEPRECATED_WARNINGS_SINCE KCOMPLETION_NO_DEPRECATED  KI18N_DEPRECATED KI18N_NO_DEPRECATED
##DEFINES += KCOMPLETION_EXPORT KXMLGUI_EXPORT KCONFIGWIDGETS_EXPORT KIOCORE_EXPORT
#DEFINES += KIOCORE_NO_DEPRECATED KIOWIDGETS_NO_DEPRECATED KCONFIGCORE_NO_DEPRECATED KCOREADDONS_NO_DEPRECATED
#DEFINES += KCONFIGWIDGETS_ENABLE_DEPRECATED_SINCE KCONFIGWIDGETS_NO_DEPRECATED
#DEFINES += KXMLGUI_NO_DEPRECATED KICONTHEMES_NO_DEPRECATED KCONFIGGUI_NO_DEPRECATED
#DEFINES += kotext_EXPORTS _USE_MATH_DEFINES  TRANSLATION_DOMAIN = "calligra"
#DEFINES += KWINDOWSYSTEM_NO_DEPRECATED KTEXTWIDGETS_NO_DEPRECATED
#DEFINES += KIOWIDGETS_calligra calligra
DEFINES     += WIN32_LEAN_AND_MEAN kotext_EXPORTS
win32 {

#DEFINES +=  BOOST_ALL_NO_LIB  KCOREADDONS_LIB  KF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x053000  NOMINMAX  QT_CONCURRENT_LIB  QT_CORE_LIB  QT_DBUS_LIB  QT_DISABLE_DEPRECATED_BEFORE=0x050600  QT_GUI_LIB  QT_NETWORK_LIB  QT_NO_CAST_TO_ASCII  QT_NO_DEBUG  QT_NO_SIGNALS_SLOTS_KEYWORDS  QT_NO_URL_CAST_FROM_STRING  QT_PRINTSUPPORT_LIB  QT_STRICT_ITERATORS  QT_USE_QSTRINGBUILDER  QT_WIDGETS_LIB  QT_XML_LIB  TRANSLATION_DOMAIN=\"calligra\"  UNICODE  WIN32_LEAN_AND_MEAN  WINVER=0x0600  _CRT_NONSTDC_NO_DEPRECATE  _CRT_SECURE_NO_DEPRECATE  _CRT_SECURE_NO_WARNINGS  _SCL_SECURE_NO_WARNINGS  _UNICODE  _USE_MATH_DEFINES  _WIN32_IE=0x0600  _WIN32_WINNT=0x0600  kotext_EXPORTS
msvc: DEFINES +=  BOOST_ALL_NO_LIB  KCOREADDONS_LIB    NOMINMAX  QT_CONCURRENT_LIB  QT_CORE_LIB  QT_DBUS_LIB   QT_GUI_LIB  QT_NETWORK_LIB  QT_NO_CAST_TO_ASCII  QT_NO_DEBUG  QT_NO_SIGNALS_SLOTS_KEYWORDS  QT_NO_URL_CAST_FROM_STRING  QT_PRINTSUPPORT_LIB  QT_STRICT_ITERATORS  QT_USE_QSTRINGBUILDER  QT_WIDGETS_LIB  QT_XML_LIB   UNICODE  WIN32_LEAN_AND_MEAN  WINVER=0x0600  _CRT_NONSTDC_NO_DEPRECATE  _CRT_SECURE_NO_DEPRECATE  _CRT_SECURE_NO_WARNINGS  _SCL_SECURE_NO_WARNINGS  _UNICODE  _USE_MATH_DEFINES  _WIN32_IE=0x0600  _WIN32_WINNT=0x0600  kotext_EXPORTS

}
# libwriteodf  no find  ---> writeodf/writeodftext.h writeodfoffice.h writeodfdc.h
INCLUDEPATH +=   ../text \
                 ../../interfaces \
                 ../../ \
                 ../../winquirks \
                 ../../version \
                 ../text/changetracker \
                 ../text/styles \
                 ../text/opendocument \
                 ../flake \
                 ../odf \
                 ../store \
                 ../odf \
                 ../store \
                 ../plugin \
                 ../pigment \
                 ../pigment/compositeops \
                 ../pigment/resources \
                 ../kundo2 \
                 ../widgetutils \
                 ../flake/commands \
                 ../flake/tools \
                 ../flake/svg \
                 ../flake \
                 ../widgetutils \
                 ../plugin


include(../../calligra.pri)
include(kotext.pri)


LIBS       +=  -L$${DESTDIR} \
                   -lflake \
                   -lpigmentcms \
                   -lkoplugin \
                   -lkowidgetutils \
                   -lkoodf \
                   -lkostore \
                   -lkundo2
