
#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <../include/core/huffman.h>

int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    QMainWindow mainWin;
    HUFFMAN *compres = new HUFFMAN();
    compres->Procesar("c:/Projectos/comprimir.txt");
    qDebug()<<"Hola";
    //mainWin.show();

    //return app.exec();
    return 0;
}
