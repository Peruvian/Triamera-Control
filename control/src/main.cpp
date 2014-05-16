#include "wggestion.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wgGestion w;
    w.show();

    return a.exec();
}
