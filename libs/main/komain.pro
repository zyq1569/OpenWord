
TEMPLATE = lib
TARGET   = komain
DESTDIR  = ../../bin/libs/
#DEFINES += CALLIGRA_RC=1
QT      += core xml network gui widgets printsupport concurrent dbus


INCLUDEPATH += ../../ \
                ../../interfaces \
                ../widgets \
                ../../winquirks \
                ../version \
                ../text \
                ../text/changetracker \
                ../text/styles \
                ../text/opendocument \
                ../flake \
                ../odf \
                ../store \
                ../plugin \
                ../pigment/compositeops \
                ../pigment/resources \
                ../kundo2 \
                ../widgetutils \
                ../flake/commands \
                ../flake/tools \
                ../flake/svg \
                ../flake \
                ../widgetutils \
                ../textlayout \
                config \
                ../plugin

LIBS         += -L$${DESTDIR} \
                -lkowidgets \
                -lkotextlayout \
                -lkotext \
                -lflake \
                -lpigmentcms \
                -lkoplugin \
                -lkowidgetutils \
                -lkoodf \
                -lkoversion \
                -lkostore \
                -lkundo2

LIBS       +=   -L$${DESTDIR} \
                -leasylog

include(../../calligra.pri)
include(komain.pri)
