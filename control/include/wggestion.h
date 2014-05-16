#ifndef WGGESTION_H
#define WGGESTION_H

#include <QWidget>

namespace Ui {
class wgGestion;
}

class wgGestion : public QWidget
{
    Q_OBJECT

public:
    explicit wgGestion(QWidget *parent = 0);
    ~wgGestion();

private:
    Ui::wgGestion *ui;
};

#endif // WGGESTION_H
