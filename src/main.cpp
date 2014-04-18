
#include <QApplication>
#include <QMainWindow>
#include <QDebug>

int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    QMainWindow mainWin;
    qDebug()<<"Hola";
    //mainWin.show();

    //return app.exec();
    return 0;
}
