#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include "../include/core/TRI_Logger.h"
#include <QDebug>

namespace TRIMERA
{
    void TRI_Log_(const QString &module, LogLevel level, const QString &message)
    {
        TRI_LoggerManager *manager = TRI_LoggerManager::getInstance();
        QMutexLocker(&manager->mutex);
        TRI_LoggerWriter *logWriter = manager->getLogWriter(module);
        if (logWriter and logWriter->getLeveL() <= level)
            logWriter->write(module, message);
    }

    void TRI_Log_Trace(const QString &module, const QString &message)
    {
        TRI_Log_(module, TraceLevel, message);
    }

    void TRI_Log_Debug(const QString &module, const QString &message)
    {
        TRI_Log_(module, DebugLevel, message);
    }

    void TRI_Log_Info(const QString &module, const QString &message)
    {
        TRI_Log_(module, InfoLevel, message);
    }

    void TRI_Log_Warning(const QString &module, const QString &message)
    {
        TRI_Log_(module, WarnLevel, message);
    }

    void TRI_Log_Error(const QString &module, const QString &message)
    {
        TRI_Log_(module, ErrorLevel, message);
    }

    void TRI_Log_Fatal(const QString &module, const QString &message)
    {
        TRI_Log_(module, FatalLevel, message);
    }
    //TRI_LoggerManager
    TRI_LoggerManager * TRI_LoggerManager::INSTANCE = NULL;

    TRI_LoggerManager::TRI_LoggerManager() : QThread(), mutex(QMutex::Recursive)
    {
        start();
    }

    QString TRI_LoggerManager::levelToText(const LogLevel &level)
    {
        switch (level)
        {
            case TraceLevel: return "Trace";
            case DebugLevel: return "Debug";
            case InfoLevel: return "Info";
            case WarnLevel: return "Warning";
            case ErrorLevel: return "Error";
            case FatalLevel: return "Fatal";
            default: return QString();
        }
    }

    TRI_LoggerManager * TRI_LoggerManager::getInstance()
    {
        if (!INSTANCE)
            INSTANCE = new TRI_LoggerManager();

        return INSTANCE;
    }

    bool TRI_LoggerManager::addDestination(const QString &fileDest, const QString &module, LogLevel level)
    {
        TRI_LoggerWriter *log;

        if (!moduleDest.contains(module))
        {
            log = new TRI_LoggerWriter(fileDest,level);
            moduleDest.insert(module, log);
            return false;
        }
        return false;
    }

    bool TRI_LoggerManager::addDestination(const QString &fileDest, const QStringList &modules, LogLevel level)
    {
        qDebug()<<"addDestination";
        TRI_LoggerWriter *log;
        foreach (QString module, modules)
        {
            if (!moduleDest.contains(module))
            {
                log = new TRI_LoggerWriter(fileDest,level);
                moduleDest.insert(module, log);
                return true;
            }
        }
        return false;
    }

    void TRI_LoggerManager::closeLogger()
    {
        exit(0);
        deleteLater();
    }

    //TRI_LoggerWriter
    TRI_LoggerWriter::TRI_LoggerWriter(const QString &fileDestination, LogLevel level)
    {
        m_fileDestination = fileDestination;
        m_level = level;
    }

    void TRI_LoggerWriter::write(const QString &module, const QString &message)
    {
        QString _fileName = m_fileDestination;
        int MAX_SIZE = 1024*1024;

        QDir dir(QDir::currentPath());
        if (!dir.exists("logs"))
            dir.mkdir("logs");

        dir.cd("logs");
        QFile file(_fileName);
        QString toRemove = _fileName.section('.',-1);
        QString fileNameAux = _fileName.left(_fileName.size() - toRemove.size()-1);
        bool renamed = false;
        QString newName = fileNameAux + "_%1__%2.log";

        if (file.size() >= MAX_SIZE)
        {
            QDateTime currentTime = QDateTime::currentDateTime();
            newName = newName.arg(currentTime.date().toString("dd_MM_yyyy")).arg(currentTime.time().toString("hh_MM_SS"));
            renamed = file.rename(_fileName,newName);
        }

        file.setFileName(dir.path()+"/"+_fileName);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
        {
            QTextStream out(&file);
            QString dtFormat = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss.zzz");

            if (renamed)
                out << QString("%1 - Log Anterior %2\n").arg(dtFormat).arg(newName);

            QString logLevel = TRI_LoggerManager::levelToText(m_level);
            QString text = QString("[%1] [%2] {%3} %4\n").arg(dtFormat).arg(logLevel).arg(module).arg(message);
            out << text;
            file.close();
        }
    }
 }
