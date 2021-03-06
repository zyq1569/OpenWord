#include "logging.h"
//INITIALIZE_EASYLOGGINGPP

#include <KWAboutData.h>
#include <KWDocument.h>

#include <KoApplication.h>
#include <Calligra2Migration.h>

#include <QLoggingCategory>
#include <QMessageBox>
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
    //    QLoggingCategory::setFilterRules("calligra.*.debug=true\n"
    //                                     "calligra.*.warning=true");

    QLoggingCategory::setFilterRules("calligra.*.debug=true\n calligra.*.warning=true");
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
