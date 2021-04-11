# ----------------------------------------------------
# 
# ------------------------------------------------------

TEMPLATE = lib
TARGET   = kundo2
DESTDIR  =  ../../bin/libs/
QT      += core xml gui widgets dbus


DEFINES     += kundo2_EXPORTS
INCLUDEPATH +=  ../../ \
                ../../interfaces \
                ../widgetutils

include(../../calligra.pri)
include(kundo2.pri)
