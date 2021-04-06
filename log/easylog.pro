
QT       +=  widgets
TEMPLATE  = lib
TARGET    = easylog
DESTDIR   = ../bin/libs/

CONFIG   += debug_and_release c++11
#CONFIG  += staticlib

DEFINES  += ELPP_THREAD_SAFE ELPP_NO_DEFAULT_LOG_FILE ELPP_DISABLE_DEFAULT_CRASH_HANDLING

include(easylog.pri)
