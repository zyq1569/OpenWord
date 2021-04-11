# ----------------------------------------------------
#
# ------------------------------------------------------

TEMPLATE      = lib
TARGET        = calligra_docker_stencils
LIBDIR        =  ../../bin/libs/
DESTDIR       = ../../bin/libs/calligra/dockers
QT           += core xml network gui widgets printsupport concurrent dbus

DEFINES      += calligra_docker_stencils_EXPORTS

INCLUDEPATH +=  ../ \
                ../../plugins/stencilsdocker \
                ../../interfaces \
                ../../ \
                ../../winquirks \
                ../../libs/version \
                ../../libs/text \
                ../../libs/text \
                ../../libs/text/changetracker \
                ../../libs/text/styles \
                ../../libs/text/opendocument \
                ../../libs/flake \
                ../../libs/odf \
                ../../libs/store \
                ../../libs/odf \
                ../../libs/store \
                ../../libs/plugin \
                ../../libs/pigment \
                ../../libs/pigment \
                ../../libs/pigment/compositeops \
                ../../libs/pigment/resources \
                ../../libs/kundo2 \
                ../../libs/kundo2 \
                ../../libs/widgetutils \
                ../../libs/flake/commands \
                ../../libs/flake/tools \
                ../../libs/flake/svg \
                ../../libs/flake \
                ../../libs/widgetutils \
                ../../libs/widgets \
                ../../libs/widgets \
                ../../libs/textlayout \
                ../../libs/textlayout \
                ../../libs/main \
                ../../libs/main \
                ../../libs/main/config

LIBS       +=   -L$${LIBDIR} \
                -lkomain \
                -lkowidgets \
                -lkotextlayout \
                -lkotext \
                -lflake \
                -lpigmentcms \
                -lkowidgetutils \
                -lkoodf \
                -lkostore

include(../../calligra.pri)
include(calligra_docker_stencils.pri)


DLLDESTDIR          = $$DLLDESTDIR/calligra/dockers
