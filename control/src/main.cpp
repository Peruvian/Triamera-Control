#include <QApplication>
#include "../include/wggestion.h"
#include "../include/frmcontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wgGestion w;
    frmControl wcontrol;
    //w.show();
    wcontrol.show();

    return a.exec();
}
