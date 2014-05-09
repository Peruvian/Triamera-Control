
#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <../include/core/huffman.h>
#include <../extlibs/QLogger/QLogger.h>

using namespace QLogger;
int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    QMainWindow mainWin;
    HUFFMAN *compres = new HUFFMAN();
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination(QString("file.log"), QStringList("ModuleName"), InfoLevel);

    //To print a log message
    QLog_Trace("ModuleName", "Message: HOLA");

    compres->Procesar("c:/Projectos/comprimir.txt");
    qDebug()<<"Hola";
    //mainWin.show();

    //return app.exec();
    return 0;
}
