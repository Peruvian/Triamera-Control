#ifndef TRI_LOGGER_H
#define TRI_LOGGER_H

#include <QStringList>
#include <QObject>
#include <QMap>
#include <QThread>
#include <QMutex>

namespace TRIMERA
{

    enum LogLevel {TraceLevel = 0, DebugLevel, InfoLevel, WarnLevel, ErrorLevel, FatalLevel };

    void TRI_Log_(const QString &module, LogLevel level, const QString &message);
    void TRI_Log_Trace(const QString &module, const QString &message);
    void TRI_Log_Debug(const QString &module, const QString &message);
    void TRI_Log_Info(const QString &module, const QString &message);
    void TRI_Log_Warning(const QString &module, const QString &message);
    void TRI_Log_Error(const QString &module, const QString &message);
    void TRI_Log_Fatal(const QString &module, const QString &message);

    class TRI_LoggerWriter : public QObject
    {
        Q_OBJECT

        public:
            explicit TRI_LoggerWriter (const QString &fileDestination, LogLevel level);
            LogLevel getLeveL() const {return m_level; }
            void write (const QString &module, const QString &message);

        private:
            QString m_fileDestination;
            LogLevel m_level;
    };

    class TRI_LoggerManager : public QThread
    {
        public:
            static QString levelToText(const LogLevel &level);
            static TRI_LoggerManager *getInstance();
            bool addDestination(const QString &fileDest, const QString &modules, LogLevel level);
            bool addDestination(const QString &fileDest, const QStringList &modules, LogLevel level);
            TRI_LoggerWriter * getLogWriter(const QString &module) { return moduleDest.value(module); }
            void closeLogger();
            QMutex mutex;

        private:
            static TRI_LoggerManager *INSTANCE;

            QMap<QString,TRI_LoggerWriter*> moduleDest;
            TRI_LoggerManager();
    };
}
#endif // TRI_LOGGER_H
