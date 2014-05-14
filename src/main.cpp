
#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <../include/core/huffman.h>
//#include <../extlibs/QLogger/QLogger.h>
#include <../include/core/TRI_Logger.h>

//using namespace QLogger;
using namespace TRI_Logger;

int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    QMainWindow mainWin;
//    HUFFMAN *compres = new HUFFMAN();
//    QLoggerManager *manager = QLoggerManager::getInstance();

    TRI_LoggerManager *LogMan = TRI_LoggerManager::getInstance();
//    LogMan->addDestination("file.log", QStringList("Modulo-01"), DebugLevel);
    LogMan->addDestination("file.log", QStringList("Modulo-01"), TraceLevel);
//    LogMan->addDestination("file.log", QStringList("Modulo-01"), InfoLevel);
//    LogMan->addDestination("file.log", QStringList("Modulo-01"), WarnLevel);
//    LogMan->addDestination("file.log", QStringList("Modulo-01"), ErrorLevel);
//    LogMan->addDestination("file.log", QStringList("Modulo-01"), FatalLevel);

//    TRI_Log_Debug("Module-01","Debug 01");
    TRI_Log_Trace("Module-01","Debug 02");
//    TRI_Log_Info("Module-01","Debug 03");
//    TRI_Log_Warning("Module-01","Debug 04");
//    TRI_Log_Error("Module-01","Debug 05");
//    TRI_Log_Fatal("Module-01","Debug 06");

    LogMan->closeLogger();

    //compres->Procesar("c:/Projectos/comprimir.txt");
    qDebug()<<"Hola";
    //mainWin.show();

    //return app.exec();
    return 0;
}
