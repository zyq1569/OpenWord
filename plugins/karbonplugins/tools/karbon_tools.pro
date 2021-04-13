# ----------------------------------------------------
#
# ------------------------------------------------------

TEMPLATE     =  lib
TARGET       =  karbon_tools
LIBDIR       =   ../../../bin/libs/
DESTDIR      =  ../../../bin/libs/calligra/tools
QT          +=  core xml network gui widgets printsupport concurrent dbus

#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"KarbonTools\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" karbon_tools_EXPORTS

win32 {

#DEFINES +=  BOOST_ALL_NO_LIB  KCOREADDONS_LIB  KF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x053000  NOMINMAX  QT_CONCURRENT_LIB  QT_CORE_LIB  QT_DBUS_LIB  QT_DISABLE_DEPRECATED_BEFORE=0x050600  QT_GUI_LIB  QT_NETWORK_LIB  QT_NO_CAST_TO_ASCII  QT_NO_DEBUG  QT_NO_SIGNALS_SLOTS_KEYWORDS  QT_NO_URL_CAST_FROM_STRING  QT_PRINTSUPPORT_LIB  QT_STRICT_ITERATORS  QT_USE_QSTRINGBUILDER  QT_WIDGETS_LIB  QT_XML_LIB  TRANSLATION_DOMAIN=\"calligra\"  UNICODE  WIN32_LEAN_AND_MEAN  WINVER=0x0600  _CRT_NONSTDC_NO_DEPRECATE  _CRT_SECURE_NO_DEPRECATE  _CRT_SECURE_NO_WARNINGS  _SCL_SECURE_NO_WARNINGS  _UNICODE  _USE_MATH_DEFINES  _WIN32_IE=0x0600  _WIN32_WINNT=0x0600  kotext_EXPORTS
msvc: DEFINES +=  BOOST_ALL_NO_LIB  KCOREADDONS_LIB    NOMINMAX  QT_CONCURRENT_LIB  QT_CORE_LIB  QT_DBUS_LIB   QT_GUI_LIB  QT_NETWORK_LIB  QT_NO_CAST_TO_ASCII  QT_NO_DEBUG  QT_NO_SIGNALS_SLOTS_KEYWORDS  QT_NO_URL_CAST_FROM_STRING  QT_PRINTSUPPORT_LIB  QT_STRICT_ITERATORS  QT_USE_QSTRINGBUILDER  QT_WIDGETS_LIB  QT_XML_LIB   UNICODE  WIN32_LEAN_AND_MEAN  WINVER=0x0600  _CRT_NONSTDC_NO_DEPRECATE  _CRT_SECURE_NO_DEPRECATE  _CRT_SECURE_NO_WARNINGS  _SCL_SECURE_NO_WARNINGS  _UNICODE  _USE_MATH_DEFINES  _WIN32_IE=0x0600  _WIN32_WINNT=0x0600  kotext_EXPORTS

}

DEFINES     +=  karbon_tools_EXPORTS
INCLUDEPATH +=  ../../../plugins/karbonplugins/tools \
                ../../../ \
                ../../../interfaces \
                ../../../calligra \
                ../../../winquirks \
                ../../../libs/version \
                ../../../libs/flake \
                ../../../libs/odf \
                ../../../libs/store \
                ../../../libs/odf \
                ../../../libs/store \
                ../../../libs/plugin \
                ../../../libs/pigment \
                ../../../libs/pigment/compositeops \
                ../../../libs/pigment/resources \
                ../../../libs/kundo2 \
                ../../../libs/widgetutils \
                ../../../libs/flake/commands \
                ../../../libs/flake/tools \
                ../../../libs/flake/svg \
                ../../../libs/flake \
                ../../../plugins/karbonplugins/tools/filterEffectTool \
                ../../../libs/widgets \
                ../../../libs/text \
                ../../../libs/widgetutils



include(../../../calligra.pri)
include(karbon_tools.pri)


LIBS       +=    -L$${LIBDIR} \
                 -lkowidgets \
                 -lkotext \
                 -lflake \
                 -lkoodf \
                 -lkostore \
                 -lkundo2 \
                 -lpigmentcms \
                 -lkowidgetutils


DLLDESTDIR          = $$DLLDESTDIR/calligra/tools