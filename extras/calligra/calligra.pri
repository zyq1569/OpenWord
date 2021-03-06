
#SDK_INSTALL_PREFIX = D:/CraftRoot/include
#SDK_LIB_PREFIX     = D:/CraftRoot/KDE_libs

SDK_INSTALL_PREFIX = D:/Dev/KDE_SDK/include
SDK_LIB_PREFIX     = D:/Dev/KDE_SDK/libs
CONFIG += debug_and_release  c++11

DEFINES += KWIDGETSADDONS_DEPRECATED_WARNINGS_SINCE KCOMPLETION_NO_DEPRECATED  KI18N_DEPRECATED KI18N_NO_DEPRECATED
DEFINES += KIOCORE_NO_DEPRECATED KIOWIDGETS_NO_DEPRECATED KCONFIGCORE_NO_DEPRECATED KCOREADDONS_NO_DEPRECATED
DEFINES += KCONFIGWIDGETS_ENABLE_DEPRECATED_SINCE KCONFIGWIDGETS_NO_DEPRECATED
DEFINES += KXMLGUI_NO_DEPRECATED KICONTHEMES_NO_DEPRECATED KCONFIGGUI_NO_DEPRECATED
DEFINES += pigmentcms_EXPORTS koplugin_EXPORTS kowidgetutils_EXPORTS flake_EXPORTS  _USE_MATH_DEFINES
DEFINES += koodf_EXPORTS koodf2_EXPORTS kostore_EXPORTS  kundo2_EXPORTS kokross_EXPORTS kowidgets_EXPORTS
DEFINES += kotext_EXPORTS kotextlayout_EXPORTS
DEFINES += komain_EXPORTS

#-----selef defined----------
DEFINES += KIOWIDGETS_calligra calligra_def
#-----selef defined----------

INCLUDEPATH +=  $$SDK_INSTALL_PREFIX \
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
                $$SDK_INSTALL_PREFIX/KF5/Solid

LIBS += -L$${SDK_LIB_PREFIX} \
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
        -lKF5Notifications

SOURCES   += main.cpp

RC_FILE   +=  calligra_rc.rc

#<PropertyGroup Label="Globals">
#<ProjectGuid>{84B9CC03-3DB2-39AB-B225-D018AFE22B7B}</ProjectGuid>
#<Keyword>Win32Proj</Keyword>
#<Platform>x64</Platform>
#<ProjectName>calligrawords</ProjectName>
#    <Keyword>Qt4VSv1.0</Keyword>
