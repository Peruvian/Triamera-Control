#include "../include/frmcontrol.h"
#include "ui_frmcontrol.h"

frmControl::frmControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmControl)
{
    ui->setupUi(this);
}

frmControl::~frmControl()
{
    delete ui;
}
