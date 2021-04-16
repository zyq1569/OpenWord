
include(../rootdir.pri)
#build_pass:message(@---$$ROOTDIR----)
#build_pass:message($$ROOTDIR)
#build_pass:message($$ROOTDIR/bin/libs/)
#build_pass:message(---$$ROOTDIR-----@)
TEMPLATE                = lib
TARGET                  = easylog
DESTDIR                 = $$ROOTDIR/bin/bin/
DLLDESTDIR              = $$ROOTDIR/bin/bin/
QT                     += widgets

DEFINES                += easylog_EXPORTS
win32 {

#msvc:DEFINES+= BOOST_ALL_NO_LIB KCOREADDONS_LIB KF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x053000 NOMINMAX QT_CONCURRENT_LIB QT_CORE_LIB QT_DBUS_LIB QT_DISABLE_DEPRECATED_BEFORE=0x050600 QT_GUI_LIB QT_NETWORK_LIB QT_NO_CAST_TO_ASCII QT_NO_DEBUG QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_PRINTSUPPORT_LIB QT_STRICT_ITERATORS QT_USE_QSTRINGBUILDER QT_WIDGETS_LIB QT_XML_LIB  UNICODE WIN32_LEAN_AND_MEAN WINVER=0x0600 _CRT_NONSTDC_NO_DEPRECATE _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS _UNICODE _USE_MATH_DEFINES _WIN32_IE=0x0600 _WIN32_WINNT=0x0600

msvc {

QT                     -= core gui
DESTDIR                 = ../bin/libs/
DLLDESTDIR              = ../bin/

#TARGET_FILE            = ../bin/
#TARGET_IMPLIB          = ../bin/lib/
#TARGET_PDB             = ../bin/pdb/

     }
}
CONFIG   += debug_and_release c++11
#CONFIG  += staticlib

DEFINES  += ELPP_THREAD_SAFE ELPP_NO_DEFAULT_LOG_FILE ELPP_DISABLE_DEFAULT_CRASH_HANDLING

include(easylog.pri)
