
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

//    manager->addDestination("file.log", QStringList("ModuleName"), TraceLevel);
//    //To print a log message
//    QLog_Trace("ModuleName", "Message: HOLA");


    TRI_LoggerManager *LogMan = TRI_LoggerManager::getInstance();
    LogMan->addDestination("file.log", QStringList("ModuleName"), TraceLevel);

    //compres->Procesar("c:/Projectos/comprimir.txt");
    qDebug()<<"Hola";
    //mainWin.show();

    //return app.exec();
    return 0;
}
