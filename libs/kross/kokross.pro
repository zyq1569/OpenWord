
TEMPLATE     =   lib
TARGET       =   kokross
DESTDIR      =   ../../bin/libs/
QT          +=   core xml network gui script widgets printsupport concurrent dbus


DEFINES     +=  kokross_EXPORTS
INCLUDEPATH +=  ../ \
                 ../kross/core \
                 ../../ \
                 ../kundo2 \
                 ../widgets \
                 ../textlayout \
                 ../widgetutils \
                 ../main \
                 ../main/config \
                 ../text \
                 ../text/changetracker \
                 ../text/styles \
                 ../text/opendocument \
                 ../flake \
                 ../flake/commands \
                 ../flake/tools \
                 ../flake/svg \
                 ../plugin \
                 ../pigment \
                 ../pigment/compositeops \
                 ../pigment/resources \
                 ../odf \
                 ../../interfaces \
                 ../../winquirks \
                 ../version \
                 ../store


include(../../calligra.pri)
include(kokross.pri)

msvc{
LIBS       +=   -L$${DESTDIR} \
                -lkostore \
                -lkoversion \
                -lmain \
                -lkowidgets \
                -lkotextlayout \
                -lkotext \
                -lflake \
                -lpigmentcms \
                -lkowidgetutils \
                -lodf \
                -lkostore \
                -lkundo2 \
                -lkoversion
}else
{
LIBS       +=   -L$${DESTDIR} \
                -lkostore \
                -lkoversion \
                -lkomain \
                -lkowidgets \
                -lkotextlayout \
                -lkotext \
                -lflake \
                -lpigmentcms \
                -lkowidgetutils \
                -lkoodf \
                -lkostore \
                -lkundo2 \
                -lkoversion
}


