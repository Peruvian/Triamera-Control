#include "../include/wggestion.h"
#include "ui_wggestion.h"

wgGestion::wgGestion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wgGestion)
{
    ui->setupUi(this);
}

wgGestion::~wgGestion()
{
    delete ui;
}
