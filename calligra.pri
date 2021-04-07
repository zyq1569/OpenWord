#include <klocalizedstring.h> --->i18n
#K_PLUGIN_FACTORY_WITH_JSON
#HEADERS +=
#DESTDIR = ../../../../bin/libs/
#DESTDIR = ../../bin/libs/



win32 {
msvc: DEFINES += MSVC
}

contains(DEFINES, MSVC) {

ALL_LIBS_DIR        = $$PWD/bin/bin/libs
SDK_INSTALL_PREFIX  = D:/Dev/KDE_SDK/MSC/include
SDK_LIB_PREFIX      = D:/Dev/KDE_SDK/MSC/libs

DESTDIR             = ./bin/libs/

LOGLIB              =  $$PWD/bin/bin/libs


}else {

ALL_LIBS_DIR        = $$PWD/bin/bin/libs
SDK_INSTALL_PREFIX  = D:/Dev/KDE_SDK/include
SDK_LIB_PREFIX      = D:/Dev/KDE_SDK/libs

DESTDIR             = ./MS_bin/libs/

LOGLIB              =  $$PWD/MS_bin/libs

}
CONFIG             += debug_and_release  c++11

DEFINES     +=  KWIDGETSADDONS_DEPRECATED_WARNINGS_SINCE KCOMPLETION_NO_DEPRECATED  KI18N_DEPRECATED KI18N_NO_DEPRECATED
DEFINES     +=  KIOCORE_NO_DEPRECATED KIOWIDGETS_NO_DEPRECATED KCONFIGCORE_NO_DEPRECATED KCOREADDONS_NO_DEPRECATED
DEFINES     +=  KCONFIGWIDGETS_ENABLE_DEPRECATED_SINCE KCONFIGWIDGETS_NO_DEPRECATED
DEFINES     +=  KXMLGUI_NO_DEPRECATED KICONTHEMES_NO_DEPRECATED KCONFIGGUI_NO_DEPRECATED
DEFINES     +=  pigmentcms_EXPORTS koplugin_EXPORTS kowidgetutils_EXPORTS flake_EXPORTS  _USE_MATH_DEFINES
DEFINES     +=  koodf_EXPORTS koodf2_EXPORTS kostore_EXPORTS  kundo2_EXPORTS kokross_EXPORTS kowidgets_EXPORTS
DEFINES     +=  kotext_EXPORTS kotextlayout_EXPORTS RtfReader_EXPORTS koodfreader_EXPORTS basicflakes_EXPORTS
DEFINES     +=  calligra_docker_defaults_EXPORTS calligra_docker_stencils_EXPORTS calligra_filter_applixword2odt_EXPORTS
DEFINES     +=  wordsprivate_EXPORTS calligra_filter_dbase2kspread_EXPORTS calligra_filter_doc2odt_EXPORTS kowv2_EXPORTS
DEFINES     +=  calligra_filter_docx2odt_EXPORTS komsooxml_EXPORTS calligra_filter_eps2svgai_EXPORTS
DEFINES     +=  calligra_filter_karbon1x2karbon_EXPORTS karboncommon_EXPORTS karbonui_EXPORTS
DEFINES     +=  kopageapp_EXPORTS calligra_filter_karbon2wmf_EXPORTS kovectorimage_EXPORTS
DEFINES     +=  calligra_filter_odt2ascii_EXPORTS calligra_filter_odt2docx_EXPORTS calligra_filter_odt2wiki_EXPORTS
DEFINES     +=  calligra_filter_kpr2odp_EXPORTS calligra_filter_odt2epub2_EXPORTS calligra_filter_odt2mobi_EXPORTS
DEFINES     +=  calligrawordspart_EXPORTS calligra_filter_karbon2svg_EXPORTS
DEFINES     +=  calligra_shape_artistictext_EXPORTS calligra_shape_formula_EXPORTS
DEFINES     +=  koformula_EXPORTS calligra_shape_music_EXPORTS calligra_shape_paths_EXPORTS
DEFINES     +=  calligra_shape_picture_EXPORTS calligra_shape_plugin_EXPORTS calligra_shape_text_EXPORTS
DEFINES     +=  calligra_shape_vector_EXPORTS calligra_shape_video_EXPORTS calligraimagethumbnail_EXPORTS
DEFINES     +=  calligra_tool_basicflakes_EXPORTS calligra_tool_defaults_EXPORTS
DEFINES     +=  karbon_tools_EXPORTS karbonpart_EXPORTS calligra_shape_chart_EXPORTS
DEFINES     +=  calligrathumbnail_EXPORTS
DEFINES     +=  komain_EXPORTS

#-----selef defined----------
DEFINES     += KIOWIDGETS_calligra calligra_def
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
                $$SDK_INSTALL_PREFIX/KF5/Solid \
                $$SDK_INSTALL_PREFIX/phonon4qt5 \
                $$SDK_INSTALL_PREFIX/KChart \
                $$SDK_INSTALL_PREFIX/libwpd-0.9 \
                $$SDK_INSTALL_PREFIX/libwpg-0.2


INCLUDEPATH +=  $$PWD/log


LIBS        +=  -L$${SDK_LIB_PREFIX} \
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
                -llibiconv \
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
                -lKF5Notifications \
                -llibzstd \
                -llibz



LIBS      +=    -L$${LOGLIB}  \
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
