
TEMPLATE     = lib
TARGET       = calligra_filter_doc2odt
LIBDIR       =  ../../../bin/libs/
DESTDIR      = ../../../bin/libs/calligra/formatfilters
QT          += core xml network gui widgets printsupport concurrent dbus

DEFINES     += calligra_filter_doc2odt_EXPORTS

INCLUDEPATH += ../msword-odf \
               ../../../interfaces \
               ../../../ \
               ../../../winquirks \
               ../../../libs/version \
               ../../../libs/text \
               ../../../libs/text/changetracker \
               ../../../libs/text/styles \
               ../../../libs/text/opendocument \
               ../../../libs/flake \
               ../../../libs/odf \
               ../../../libs/store \
               ../../../libs/odf \
               ../../../libs/plugin \
               ../../../libs/pigment \
               ../../../libs/pigment/compositeops \
               ../../../libs/pigment/resources \
               ../../../libs/kundo2 \
               ../../../libs/widgetutils \
               ../../../libs/flake/commands \
               ../../../libs/flake/tools \
               ../../../libs/flake/svg \
               ../../../libs/flake \
               ../../../libs/widgetutils \
               ../../../libs/widgets \
               ../../../libs/textlayout \
               ../../../libs/main \
               ../../../libs/main/config \
               ../../../filters/libmso \
               ../../../filters/words/msword-odf/wv2/src

msvc{
LIBS         += -L$${LIBDIR} \
                -lkowv2 \
                -lmso \
                -lmain \
                -lkowidgets \
                -lkotextlayout \
                -lkotext \
                -lflake \
                -lodf \
                -lkostore \
                -lpigmentcms \
                -lkowidgetutils \
                -lkundo2 \
                -lkoversion
}else
{
LIBS         += -L$${LIBDIR} \
                -lkowv2 \
                -lmso \
                -lkomain \
                -lkowidgets \
                -lkotextlayout \
                -lkotext \
                -lflake \
                -lkoodf \
                -lkostore \
                -lpigmentcms \
                -lkowidgetutils \
                -lkundo2 \
                -lkoversion
}





include(../../../calligra.pri)
include(calligra_filter_doc2odt.pri)

#设置调试信息文件输出到dll文件同位置
DESTDIR             = $$DLLDESTDIR/calligra/formatfilters
DLLDESTDIR          = $$DLLDESTDIR/calligra/formatfilters
