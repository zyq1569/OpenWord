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
    ///app.start() 考虑在这个地方增加参数启动线程和共享内存
    /// bool KoApplication::start() 是否增加函数传递参数，还是其函数里面KAboutData aboutData = KAboutData::applicationData(); 获取参数
    if (!app.start())
    {
        return 1;
    }

    return app.exec();
}
