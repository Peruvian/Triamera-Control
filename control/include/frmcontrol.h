#ifndef FRMCONTROL_H
#define FRMCONTROL_H

#include <QWidget>
#include <QDebug>
#include <QDate>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QMessageBox>

namespace Ui {
class frmControl;
}

class frmControl : public QWidget
{
    Q_OBJECT

public:
    explicit frmControl(QWidget *parent = 0);
    ~frmControl();

private slots:
    void on_txtDNI_returnPressed();

private:
    Ui::frmControl *ui;

    QSqlDatabase *db;
};

#endif // FRMCONTROL_H
