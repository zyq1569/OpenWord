#include <klocalizedstring.h> --->i18n
#K_PLUGIN_FACTORY_WITH_JSON
#HEADERS +=
#DESTDIR = ../../../../bin/libs/
#DESTDIR = ../../bin/libs/




win32 {

msvc: DEFINES      += MSVC

}

contains(DEFINES, MSVC) {

# Use Precompiled headers (PCH)
CONFIG             += precompile_header

DEFINES            += UNICODE

ALL_LIBS_DIR        = $$PWD/bin/bin/libs
SDK_INSTALL_PREFIX  = D:/Dev/CraftRoot-D/include
SDK_LIB_PREFIX      = D:/Dev/CraftRoot-D/lib

SDK_INSTALL_PREFIX  = D:/CraftRoot/include
SDK_LIB_PREFIX      = D:/CraftRoot/lib

SDK_INSTALL_PREFIX  = D:/Dev/KDE_SDK/MSC/RelWithDebInfo/include
SDK_LIB_PREFIX      = D:/Dev/KDE_SDK/MSC/RelWithDebInfo/lib

DESTDIR             = $$PWD/MS_bin/bin

DLLDESTDIR          = $$PWD/MS_bin/bin

TARGET_FILE         = $$PWD/MS_bin/temp/TARGET
TARGET_IMPLIB       = $$PWD/MS_bin/temp/TARGET
TARGET_PDB          = $$PWD/MS_bin/temp/TARGET

LOGLIB              = $$PWD/ms_bin/bin

DEFINES            +=  WIN32_LEAN_AND_MEAN  _WINSOCKAPI_

QMAKE_CFLAGS       += /utf-8
QMAKE_CXXFLAGS     += /utf-8

LIBS               +=  -L$${SDK_LIB_PREFIX} \
                       -lzlib

}else {

ALL_LIBS_DIR        = $$PWD/bin/bin
SDK_INSTALL_PREFIX  = D:/Dev/KDE_SDK/include
SDK_LIB_PREFIX      = D:/Dev/KDE_SDK/libs

DESTDIR             = $$PWD/bin/bin
DLLDESTDIR          = $$PWD/bin/bin

LOGLIB              =  $$PWD/bin/bin

LIBS               +=  -L$${SDK_LIB_PREFIX} \
                        -lz

}

//QMAKE_CXXFLAGS     +=  -Wno-unused-parameter

CONFIG             += debug_and_release  c++11

DEFINES            +=  KWIDGETSADDONS_DEPRECATED_WARNINGS_SINCE KCOMPLETION_NO_DEPRECATED  KI18N_DEPRECATED KI18N_NO_DEPRECATED
DEFINES            +=  KIOCORE_NO_DEPRECATED KIOWIDGETS_NO_DEPRECATED KCONFIGCORE_NO_DEPRECATED KCOREADDONS_NO_DEPRECATED
DEFINES            +=  KCONFIGWIDGETS_ENABLE_DEPRECATED_SINCE KCONFIGWIDGETS_NO_DEPRECATED
DEFINES            +=  KXMLGUI_NO_DEPRECATED KICONTHEMES_NO_DEPRECATED KCONFIGGUI_NO_DEPRECATED
DEFINES            +=  _USE_MATH_DEFINES

#-----selef defined----------
DEFINES            += KIOWIDGETS_calligra calligra_def
#-----selef defined----------

INCLUDEPATH        +=  $$SDK_INSTALL_PREFIX \
                       $$SDK_INSTALL_PREFIX/KF5 \
                       $$SDK_INSTALL_PREFIX/KF5/KrossUi \
                       $$SDK_INSTALL_PREFIX/KF5/KrossCore \
                       $$SDK_INSTALL_PREFIX/KF5/KAuth \
                       $$SDK_INSTALL_PREFIX/KF5/KArchive \
                       $$SDK_INSTALL_PREFIX/KF5/KActivities \
                       $$SDK_INSTALL_PREFIX/KF5/KIOCore \
                       $$SDK_INSTALL_PREFIX/KF5/ki18n \
                       $$SDK_INSTALL_PREFIX/KF5/kdecore \
                       $$SDK_INSTALL_PREFIX/KF5/KDBusAddons \
                       $$SDK_INSTALL_PREFIX/KF5/KGuiAddons \
                       $$SDK_INSTALL_PREFIX/KF5/KService \
                       $$SDK_INSTALL_PREFIX/KF5/KXmlGui \
                       $$SDK_INSTALL_PREFIX/KF5/KConfigWidgets \
                       $$SDK_INSTALL_PREFIX/KF5/KCodecs \
                       $$SDK_INSTALL_PREFIX/KF5/KConfigGui \
                       $$SDK_INSTALL_PREFIX/KF5/KConfigCore \
                       $$SDK_INSTALL_PREFIX/KF5/KCoreAddons \
                       $$SDK_INSTALL_PREFIX/KF5/KCompletion \
                       $$SDK_INSTALL_PREFIX/KF5/KTextWidgets \
                       $$SDK_INSTALL_PREFIX/KF5/KIOWidgets \
                       $$SDK_INSTALL_PREFIX/KF5/KIOGui \
                       $$SDK_INSTALL_PREFIX/KF5/KItemViews \
                       $$SDK_INSTALL_PREFIX/KF5/KIOFileWidgets \
                       $$SDK_INSTALL_PREFIX/KF5/KIconThemes \
                       $$SDK_INSTALL_PREFIX/KF5/KWindowSystem \
                       $$SDK_INSTALL_PREFIX/KF5/KWidgetsAddons \
                       $$SDK_INSTALL_PREFIX/KF5/KJobWidgets \
                       $$SDK_INSTALL_PREFIX/KF5/KNotifications \
                       $$SDK_INSTALL_PREFIX/KF5/KBookmarks \
                       $$SDK_INSTALL_PREFIX/KF5/SonnetUi \
                       $$SDK_INSTALL_PREFIX/KF5/SonnetCore \
                       $$SDK_INSTALL_PREFIX/KF5/Solid \
                       $$SDK_INSTALL_PREFIX/phonon4qt5 \
                       $$SDK_INSTALL_PREFIX/KChart \
                       $$SDK_INSTALL_PREFIX/libwpd-0.9 \
                       $$SDK_INSTALL_PREFIX/libwpg-0.2


INCLUDEPATH      +=  $$PWD/log


LIBS             +=  -L$${SDK_LIB_PREFIX} \
                     -lws2_32 \
                     -lnetapi32 \
                     -lkernel32 \
                     -luser32 \
                     -lgdi32 \
                     -lwinspool \
                     -lshell32 \
                     -lole32 \
                     -loleaut32 \
                     -luuid \
                     -lcomdlg32 \
                     -ladvapi32 \
                     -liconv \
                     -lKF5I18n \
                     -lKF5WidgetsAddons \
                     -lKF5KIOCore \
                     -lKF5Service \
                     -lKF5Crash \
                     -lKF5DBusAddons \
                     -lKF5XmlGui \
                     -lKF5KIOFileWidgets \
                     -lKF5IconThemes \
                     -lKF5ConfigWidgets \
                     -lKF5Codecs \
                     -lKF5ConfigGui \
                     -lKF5ConfigCore \
                     -lKF5Auth \
                     -lKF5AuthCore \
                     -lKF5Activities \
                     -lKF5Archive \
                     -lKF5AuthCore \
                     -lKF5CoreAddons \
                     -lKF5JobWidgets \
                     -lKF5Parts \
                     -lKF5SonnetUi \
                     -lKF5SonnetCore \
                     -lKF5Crash \
                     -lKF5Solid \
                     -lKF5Completion \
                     -lKF5GuiAddons \
                     -lKF5TextWidgets \
                     -lKF5WindowSystem \
                     -lKF5ItemViews \
                     -lKF5KIOWidgets \
                     -lKF5KrossCore \
                     -lKF5KrossUi \
                     -lKF5Notifications \
                     -lzstd


LIBS              +=   -L$${LOGLIB}  \
                       -leasylog


# EasyLogging++ is set to be thread safe, to not have a default log file, and to not handle crashes
#DEFINES         += ELPP_THREAD_SAFE ELPP_NO_DEFAULT_LOG_FILE ELPP_DISABLE_DEFAULT_CRASH_HANDLING


#build_pass:message($$PWD) # 当前pri文件所在目录
#build_pass:message($$OUT_PWD) # 生成makefile所在目录
#build_pass:message($$_PRO_FILE_) # 包含当前pri的pro所在路径
#build_pass:message($$_PRO_FILE_PWD_) # 包含当前pri的pro所在目录


#define K_PLUGIN_FACTORY_WITH_JSON(name, jsonFile, pluginRegistrations)
#class name : public KPluginFactory
#{
#    Q_OBJECT
#    Q_INTERFACES(KPluginFactory)
#    Q_PLUGIN_METADATA(IID KPluginFactory_iid FILE jsonFile)
#public:
#    explicit name();
#    ~name();
#};

#name::name()
#{
#    pluginRegistrations
#}
#name::~name()
#{}

#build_pass:message($$PWD) # 当前pri文件所在目录
#build_pass:message($$OUT_PWD) # 生成makefile所在目录
#build_pass:message($$_PRO_FILE_) # 包含当前pri的pro所在路径
#build_pass:message($$_PRO_FILE_PWD_) # 包含当前pri的pro所在目录
#https://www.cnblogs.com/codeForFamily/p/qt-creator-ide-source-learn-3-2.html#replace-functions


#OFString HashValue(int F, int S, OFString str)
#{
#    int len = str.length();
#    int value = 0;
#    for (unsigned int i = 0; i < len; i++)
#    {
#        value = value * F + str[i] + i;
#    }
#    value %= S;

#    return longToString(value);
#}
