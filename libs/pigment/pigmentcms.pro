
#build_pass:message($$PWD) # 当前pri文件所在目录
#build_pass:message($$OUT_PWD) # 生成makefile所在目录
#build_pass:message($$_PRO_FILE_) # 包含当前pri的pro所在路径
#build_pass:message($$_PRO_FILE_PWD_) # 包含当前pri的pro所在目录

TEMPLATE = lib
TARGET   = pigmentcms
CONFIG  += debug_and_release  c++11
DESTDIR  = ../../bin/libs/
QT      += core xml gui

#DEFINES += _WINDOWS WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0600 WINVER=0x0600 _WIN32_IE=0x0600 _UNICODE _USE_MATH_DEFINES _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0 QT_USE_QSTRINGBUILDER QT_STRICT_ITERATORS QT_NO_SIGNALS_SLOTS_KEYWORDS QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_TO_ASCII NOMINMAX BOOST_ALL_NO_LIB TRANSLATION_DOMAIN=\"calligra\" QT_XML_LIB CMAKE_INTDIR=\"Debug\"

DEFINES     +=   pigmentcms_EXPORTS
INCLUDEPATH  +=  ../pigment \
                 ../../interfaces \
                 ../../ \
                 ../../winquirks \
                 ../version \
                 ../plugin \
                 ../pigment/compositeops \
                 ../pigment/resources \
                 ../plugin

#LIBS         +=  -L../.././bin/bin/libs/
#                 -llibkoplugin
#LIBS         +=  -L$${IDE_BUILD_TREE} \
#                 -llibkoplugin

#build_pass:message($$IDE_BUILD_TREE)
include(../../calligra.pri)
#build_pass:message(------show start: ALL_LIBS_DIR---------)
#build_pass:message($$ALL_LIBS_DIR)
#build_pass:message(------show end: ALL_LIBS_DIR---------)
LIBS         +=  -L$${ALL_LIBS_DIR}\
                 -lkoplugin
include(pigmentcms.pri)
