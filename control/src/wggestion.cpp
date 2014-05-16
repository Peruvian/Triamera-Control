#include "../include/wggestion.h"
#include "ui_wggestion.h"

wgGestion::wgGestion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wgGestion)
{
    ui->setupUi(this);
    ui->grdDatos->setRowCount(5);

    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText("Hola");
    ui->grdDatos->setItem(1,1,item);
}

wgGestion::~wgGestion()
{
    delete ui;
}
