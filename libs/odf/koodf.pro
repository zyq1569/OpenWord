# ----------------------------------------------------
# 
# ------------------------------------------------------

TEMPLATE           = lib
TARGET             = koodf
DESTDIR            = ../../bin/libs/
QT                += core xml network gui widgets printsupport concurrent dbus

#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\" koodf_EXPORTS
DEFINES           += koodf_EXPORTS
win32 {

#msvc:DEFINES+= BOOST_ALL_NO_LIB KCOREADDONS_LIB KF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x053000 NOMINMAX QT_CONCURRENT_LIB QT_CORE_LIB QT_DBUS_LIB QT_DISABLE_DEPRECATED_BEFORE=0x050600 QT_GUI_LIB QT_NETWORK_LIB QT_NO_CAST_TO_ASCII QT_NO_DEBUG QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_PRINTSUPPORT_LIB QT_STRICT_ITERATORS QT_USE_QSTRINGBUILDER QT_WIDGETS_LIB QT_XML_LIB  UNICODE WIN32_LEAN_AND_MEAN WINVER=0x0600 _CRT_NONSTDC_NO_DEPRECATE _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS _UNICODE _USE_MATH_DEFINES _WIN32_IE=0x0600 _WIN32_WINNT=0x0600

msvc {

DESTDIR            = ../../bin/

QMAKE_CFLAGS      += /utf-8
QMAKE_CXXFLAGS    += /utf-8

#OBJEC//T_DIR = libs\odf\CMakeFiles\koodf.dir/
#TARGET_COMPILE_PDB = libs\odf\CMakeFiles\koodf.dir\
#TARGET_FILE        = bin\koodf.dll
#TARGET_IMPLIB      = lib\koodf.lib
#TARGET_PDB         = bin\koodf.pdb

#MOC_DIR += ./tmp/moc
#OBJECTS_DIR += ./tmp/obj
#UI_DIR += ./tmp/ui
#RCC_DIR += ./tmp/rcc


    }

}


INCLUDEPATH        +=   ../../ \
                        ../odf \
                        ../../interfaces \
                        ../../winquirks \
                        ../version \
                        ../store

LIBS               +=   -L$${DESTDIR} \
                        -lkoversion \
                        -lkostore


include(../../calligra.pri)

include(koodf.pri)


