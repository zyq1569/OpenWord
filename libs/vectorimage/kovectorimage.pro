# ----------------------------------------------------
# 
# ------------------------------------------------------

TEMPLATE = lib
TARGET = kovectorimage
DESTDIR = ../../bin/libs/
QT += core gui widgets printsupport

#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_PRINTSUPPORT_LIB QT_WIDGETS_LIB CMAKE_INTDIR=\"Debug\" kovectorimage_EXPORTS
INCLUDEPATH += ../../libs/vectorimage \
                ../../libs/vectorimage \
                ../../libs/vectorimage/kovectorimage_autogen/include_Debug \
                ../../interfaces \
                ../../calligra \
                ../../src \
                ../../winquirks \
                ../../libs/version \
                ../../libs/version \
                ../../libs/vectorimage/libemf \
                ../../libs/vectorimage/libsvm \
                ../../libs/vectorimage/libwmf



#LIBS += -L$${DESTDIR} \
#        -lkernel32 \
#        -luser32 \
#        -lgdi32 \
#        -lwinspool \
#        -lshell32 \
#        -lole32 \
#        -loleaut32 \
#        -luuid \
#        -lcomdlg32 \
#        -ladvapi32

#kovectorimage_EXPORTS
include(../../calligra.pri)

include(kovectorimage.pri)
