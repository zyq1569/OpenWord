
TEMPLATE         = app
TARGET           = HEditor
DESTDIR          = ../../bin/libs/
QT              += core xml network gui widgets printsupport concurrent dbus
#DEFINES        += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligrawords\" QT_XML_LIB QT_WIDGETS_LIB KCOREADDONS_LIB QT_NETWORK_LIB QT_CONCURRENT_LIB QT_DBUS_LIB QT_PRINTSUPPORT_LIB CMAKE_INTDIR=\"Debug\"

# EasyLogging++ is set to be thread safe, to not have a default log file, and to not handle crashes
#DEFINES        +=  ELPP_THREAD_SAFE ELPP_NO_DEFAULT_LOG_FILE ELPP_DISABLE_DEFAULT_CRASH_HANDLING
INCLUDEPATH     +=  ../../  \
                    ../  \
                    ../../interfaces \
                    ../../winquirks \
                    ../../version \
                    ../../libs/version \
                    ../../libs/kundo2 \
                    ../../libs/text \
                    ../../libs/text/changetracker \
                    ../../libs/text/styles \
                    ../../libs/text/opendocument \
                    ../../libs/flake \
                    ../../libs/odf \
                    ../../libs/store \
                    ../../libs/store \
                    ../../libs/plugin \
                    ../../libs/pigment \
                    ../../libs/pigment/compositeops \
                    ../../libs/pigment/resources \
                    ../../libs/kundo2 \
                    ../../libs/widgetutils \
                    ../../libs/flake/commands \
                    ../../libs/flake/tools \
                    ../../libs/flake/svg \
                    ../../libs/flake \
                    ../../libs/widgetutils \
                    ../../libs/widgets \
                    ../../libs/textlayout \
                    ../../libs/main \
#                    ../../libs/editorWindow \
                    ../../libs/main/config \
                    ../../words/part


#LIBS          +=    -L$${DESTDIR}  \
#                    -leasylog

include(../../calligra.pri)
include(reportEditor.pri)
#mingw
msvc{
LIBS          +=    -L$${DESTDIR} \
                    -lpigmentcms \
                    -lkowidgetutils \
                    -lodf \
                    -lkundo2 \
                    -lkoplugin \
                    -lkostore \
                    -lmain \
                    -lkowidgets \
                    -lkotextlayout \
                    -lkotext \
                    -lflake \
                    -lpigmentcms \
                    -lkoversion
}else
{
LIBS          +=    -L$${DESTDIR} \
                    -lpigmentcms \
                    -lkowidgetutils \
                    -lkoodf \
                    -lkundo2 \
                    -lkoplugin \
                    -lkostore \
                    -lkomain \
                    -lkowidgets \
                    -lkotextlayout \
                    -lkotext \
                    -lflake \
                    -lpigmentcms \
                    -lkoversion
}

