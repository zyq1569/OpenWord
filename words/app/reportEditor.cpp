#include "logging.h"

#include <KWAboutData.h>
#include <KWDocument.h>

#include <KoApplication.h>
#include <Calligra2Migration.h>

#include <QLoggingCategory>
#include <QMessageBox>

Q_DECL_EXPORT int main(int argc, char **argv)
{
    QLoggingCategory::setFilterRules("calligra.*.debug=true\n calligra.*.warning=true");
    KoApplication app(WORDS_MIME_TYPE, QStringLiteral("HEditor"), newWordsAboutData, argc, argv);
    INFO_LOG("----HEditor start to run!-----");//must after:KoApplication
    // Migrate data from kde4 to kf5 locations
    Calligra2Migration m("HealthEditor", "HEditor");
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
