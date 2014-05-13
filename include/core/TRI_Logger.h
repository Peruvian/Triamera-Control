#ifndef TRI_LOGGER_H
#define TRI_LOGGER_H

#include <QStringList>
#include <QObject>
#include <QMap>
#include <QThread>
#include <QMutex>

namespace TRI_Logger
{

    enum LogLevel {TraceLevel = 0, DebugLevel, InfoLevel, WarnLevel, ErrorLevel, FatalLevel };

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
            bool addDestination(const QString &fileDest, const QStringList &modules, LogLevel level);
            void closeLogger();
            QMutex mutex;

        private:
            static TRI_LoggerManager *INSTANCE;

            QMap<QString,TRI_LoggerWriter*> moduleDest;
            TRI_LoggerManager();

    };
}
#endif // TRI_LOGGER_H
