# ----------------------------------------------------
# 
# ------------------------------------------------------

TEMPLATE = lib
TARGET = kowidgetutils
DESTDIR = ../../bin/libs/
QT += core xml gui widgets

#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_WIDGETS_LIB QT_XML_LIB CMAKE_INTDIR=\"Debug\" kowidgetutils_EXPORTS
INCLUDEPATH +=  ../../ \
        ../../interfaces \
    ../../winquirks \
    ../../libs/version

#LIBS += -L"." \
#    -lKF5::I18n \
#    -lD://lib/KF5ConfigCore \
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
include(../../calligra.pri)
include(kowidgetutils.pri)
