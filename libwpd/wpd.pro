

TEMPLATE     = lib
TARGET       = wpd
DESTDIR      = ../bin
CONFIG      += staticlib
#DEFINES     += _WINDOWS CMAKE_INTDIR=\"RelWithDebInfo\"
INCLUDEPATH += ../ \
               ./src/lib


#LIBS        += -L"."
#DEPENDPATH  += .
#MOC_DIR     += ./GeneratedFiles/$(ConfigurationName)
#OBJECTS_DIR += relwithdebinfo
#UI_DIR      += ./GeneratedFiles
#RCC_DIR     += ./GeneratedFiles

include(wpd.pri)
