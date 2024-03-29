#include "logging.h"
//INITIALIZE_EASYLOGGINGPP

#include <KWAboutData.h>
#include <KWDocument.h>

#include <KoApplication.h>
#include <Calligra2Migration.h>

#include <QLoggingCategory>
#include <QMessageBox>
//#include <QTextCodec>
///???if (KRun::isExecutableFile(_url, type))
/*extern "C"*/ Q_DECL_EXPORT int main(int argc, char **argv)
{
    /**
     * Disable debug output by default, only log warnings.
     * Debug logs can be controlled by the environment variable QT_LOGGING_RULES.
     *
     * For example, to get full debug output, run the following:
     * QT_LOGGING_RULES="calligra.*=true" calligrawords
     *
     * See: http://doc.qt.io/qt-5/qloggingcategory.html
     */
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    //    QLoggingCategory::setFilterRules("calligra.*.debug=true\n"
    //                                     "calligra.*.warning=true");

//    QString appname = argv[0];
//    appname = appname.right(appname.lastIndexOf('\\')-2).replace(".exe","");
//    QString appname =  QCoreApplication::applicationFilePath();
    QLoggingCategory::setFilterRules("calligra.*.debug=true\n calligra.*.warning=true");
    //to do:
    //1.考虑调整界面布局
    //2.KDE 的界面库是否考虑弱化
    KoApplication app(WORDS_MIME_TYPE, QStringLiteral("calligrawords"), newWordsAboutData, argc, argv);
    INFO_LOG("----Word start to run!-----");//must after:KoApplication
    // Migrate data from kde4 to kf5 locations
    Calligra2Migration m("calligrawords", "words");
    QStringList qlist = QStringList() << QStringLiteral("wordsrc");
    m.setConfigFiles(qlist);
    qlist.clear();
    qlist = QStringList() << QStringLiteral("words.rc") << QStringLiteral("words_readonly.rc");
    m.setUiFiles(QStringList() << QStringLiteral("words.rc") << QStringLiteral("words_readonly.rc"));
    m.migrate();
    if (!app.start())
    {
        return 1;
    }

    return app.exec();
}
