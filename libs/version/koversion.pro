# ----------------------------------------------------
# 
# ------------------------------------------------------

TEMPLATE     = lib
TARGET       = koversion
DESTDIR      = ../../bin/libs/
QT          += core
#DEFINES     += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" CMAKE_INTDIR=\"Debug\" koversion_EXPORTS

DEFINES     += koversion_EXPORTS
INCLUDEPATH +=   ../../ \
                ../../libs/odf \
                ../../interfaces \
                ../../winquirks \
                ../../version \
                ../../libs/store \
                ../libodf2 \
                ../libodf2/chart \
                ../../interfaces \
                ../../winquirks \
                ../../version \
                ../../filters/libmso

include(../../calligra.pri)
include(koversion.pri)
