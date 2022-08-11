
#include "logging.h"

#include <QDir>
#include <QApplication>

INITIALIZE_EASYLOGGINGPP

namespace LOG
{

const char* getPID(const el::LogMessage*)
{
    //static QString pid = QString::number(getpid());
    static QString pid = QString::number(qApp->applicationPid());
    static std::string stdpid = pid.toStdString();
    return  stdpid.c_str();
}

void setLogDefault(QString appName)
{
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    el::Helpers::installCustomFormatSpecifier(el::CustomFormatSpecifier("%pid", getPID));
    // Values are always std::string
    //defaultConf.set(el::Level::Info, el::ConfigurationType::Format, "%datetime{%Y-%M-%d %H:%m:%s} %level %msg");
    defaultConf.set(el::Level::Warning, el::ConfigurationType::Format, "%datetime{%y/%M/%d %H:%m:%s:%g} %pid %thread %levshort %msg");
    //defaultConf.set(el::ConfigurationType::MaxLogFileSize, "2097152"); // 2MB
    el::Configuration confMaxLogFileSizeInfo(el::Level::Info, el::ConfigurationType::MaxLogFileSize, "2097152");
    //default logger uses default configurations
    el::Loggers::reconfigureLogger("default", defaultConf);
    //LOG(INFO) << "Log using default file";
    //To set GLOBAL configurations you may use
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime{%y/%M/%d %H:%m:%s:%g} %pid %thread %levshort %msg");
    defaultConf.setGlobally(el::ConfigurationType::Filename, getLogFilePath(appName).toStdString());
    el::Loggers::reconfigureLogger("default", defaultConf);

#ifndef MSVC
    INFO_LOG("setLogDefault()---INFO!");
#endif
}

void beginLogging(QString appName)
{
    if (appName.length() < 1)
    {
        appName = qAppName();
        if (appName.length() < 1)
        {
            appName = qApp->applicationFilePath();
            if (appName.length() > 1)
            {
                appName = appName.right(appName.length() - appName.lastIndexOf("/"));
                appName = appName.left(appName.length() - 4);
            }
        }
        if (appName.length() < 1)
        {
            appName = "Calligra";
        }
    }
    //QDir logDir = udg::UserLogsPath;
    QString logDir = QDir::currentPath()+"/log";
    QDir qlogDir =  logDir;// udg::UserCurrentAppPath;//use current work path
    if (!qlogDir.exists())
    {
        qlogDir.mkpath(logDir);
    }
    setLogDefault(appName);

}

void InitLog()
{
    static int init = 0 ;
    if ( init > 0 )
    {
        return;
    }
    init++;
    beginLogging("");
}

QString getLogFilePath(QString appName)
{
    if (appName.length()>1)
    {
        return QDir::toNativeSeparators(QDir::currentPath()+"/log/"+appName+".log");
    }
    return QDir::toNativeSeparators(QDir::currentPath()+"/log/calligrawords.log");
}

void debugLog(const QString &msg, const QString &file, int line, const QString &function)
{
    InitLog();
    LOG(DEBUG) << qPrintable(QString("%1 [ %2:%3 %4 ]").arg(msg).arg(file).arg(line).arg(function));
}

void infoLog(const QString &msg, const QString&, int, const QString&)
{
    InitLog();
    LOG(INFO) << qUtf8Printable(msg);
}

void warnLog(const QString &msg, const QString &file, int line, const QString &function)
{
    InitLog();
    LOG(WARNING) << qUtf8Printable(QString("%1 [ %2:%3 %4 ]").arg(msg).arg(file).arg(line).arg(function));
}

void errorLog(const QString &msg, const QString &file, int line, const QString &function)
{
    InitLog();
    LOG(ERROR) << qUtf8Printable(QString("%1 [ %2:%3 %4 ]").arg(msg).arg(file).arg(line).arg(function));
}

void fatalLog(const QString &msg, const QString &file, int line, const QString &function)
{
    InitLog();
    LOG(FATAL) << qUtf8Printable(QString("%1 [ %2:%3 %4 ]").arg(msg).arg(file).arg(line).arg(function));
}

void verboseLog(int vLevel, const QString &msg, const QString&, int, const QString&)
{
    InitLog();
    VLOG(vLevel) << qUtf8Printable(msg);
}

void traceLog(const QString &msg, const QString&, int, const QString&)
{
    InitLog();
    LOG(TRACE) << qUtf8Printable(msg);
}

}
