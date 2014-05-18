#ifndef FRMCONTROL_H
#define FRMCONTROL_H

#include <QWidget>

namespace Ui {
class frmControl;
}

class frmControl : public QWidget
{
    Q_OBJECT

public:
    explicit frmControl(QWidget *parent = 0);
    ~frmControl();

private:
    Ui::frmControl *ui;
};

#endif // FRMCONTROL_H
