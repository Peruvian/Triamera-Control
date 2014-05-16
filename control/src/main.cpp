#include <QApplication>
#include "../include/wggestion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wgGestion w;
    w.show();

    return a.exec();
}
