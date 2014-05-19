#include <QApplication>
#include "../include/wggestion.h"
#include "../include/frmcontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmControl wcontrol;
    wcontrol.show();
    //wgGestion w;
    //w.show();


    return a.exec();
}
