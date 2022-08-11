
TEMPLATE     = lib
TARGET       = kowidgets
DESTDIR      = ../../bin/libs/
QT          += core xml network gui widgets printsupport concurrent dbus


DEFINES     +=  kowidgets_EXPORTS
INCLUDEPATH +=   ../../ \
                ../../interfaces \
                ../../winquirks \
                ../../version \
                ../libodf2 \
                ../libodf2/chart \
                ../../interfaces \
                ../../winquirks \
                ../../version \
                ../../filters/libmso \
                ../text \
                ../text/changetracker \
                ../text/styles \
                ../text/opendocument \
                ../flake \
                ../odf \
                ../store \
                ../plugin \
                ../pigment \
                ../pigment \
                ../pigment/compositeops \
                ../pigment/resources \
                ../kundo2 \
                ../kundo2 \
                ../widgetutils \
                ../flake/commands \
                ../flake/tools \
                ../flake/svg \
                ../flake \
                ../widgetutils


#    -lD://lib/KF5KIOWidgets \
#    -lD://lib/KF5WidgetsAddons \
#    -lD://lib/KF5Codecs \
#    -lD://lib/KF5Completion \
#    -lD://lib/KF5XmlGui \
#    -lD://lib/KF5TextWidgets \
#    -lD://lib/KF5SonnetUi \
#    -lD://lib/KF5IconThemes \
#    -lD://lib/KF5KIOGui \
#    -lD://lib/KF5KIOCore \
#    -lD://lib/KF5Crash \
#    -lD://lib/KF5JobWidgets \
#    -lD://lib/KF5Service \
#    -lKF5::I18n \
#    -lD://lib/KF5DBusAddons \
#    -lD://lib/KF5WindowSystem \
#    -lD://lib/KF5ConfigWidgets \
#    -lD://lib/KF5GuiAddons \
#    -lD://lib/KF5ConfigGui \
#    -lD://lib/KF5ConfigCore \
#    -lD://lib/KF5Auth \
#    -lD://lib/KF5AuthCore \
#    -lD://lib/KF5CoreAddons \
#    -lkernel32 \
#    -luser32 \
#    -lgdi32 \
#    -lwinspool \
#    -lshell32 \
#    -lole32 \
#    -loleaut32 \
#    -luuid \
#    -lcomdlg32 \
#    -ladvapi32

#DEPENDPATH += .
#MOC_DIR += ./tmp/moc
#OBJECTS_DIR += ./tmp/obj
#UI_DIR += ./tmp/ui
#RCC_DIR += ./tmp/rcc
include(../../calligra.pri)
include(kowidgets.pri)


msvc{

LIBS     +=      -L$${DESTDIR} \
                 -lflake \
                 -lpigmentcms \
                 -lkowidgetutils \
                 -lodf \
                 -lkostore \
                 -lkundo2 \
                 -lkotext
}else
{

LIBS     +=      -L$${DESTDIR} \
                 -lflake \
                 -lpigmentcms \
                 -lkowidgetutils \
                 -lkoodf \
                 -lkostore \
                 -lkundo2 \
                 -lkotext
}
