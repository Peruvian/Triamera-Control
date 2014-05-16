#include "../include/wggestion.h"
#include "ui_wggestion.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>

wgGestion::wgGestion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wgGestion)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    Header << "DNI" << "Nombres" << "Apellido Paterno" << "Apellido Materno" << "Fecha Nacimiento" << "Fecha Ingreso" << "Formacion" << "V";
    model->setHorizontalHeaderLabels(Header);
    ui->grdVData->setModel(model);

}

wgGestion::~wgGestion()
{
    delete ui;
}

void wgGestion::on_btnAbrir_clicked()
{
    model->clear();
    QString fileName = QFileDialog::getOpenFileName (this, "Open CSV file",
                                                     QDir::currentPath(), "CSV (*.csv)");
    Header << "DNI" << "Nombres" << "Apellido Paterno" << "Apellido Materno" << "Fecha Nacimiento" << "Fecha Ingreso" << "Formacion" << "V";
    model->setHorizontalHeaderLabels(Header);

    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        textStream.setCodec("LATIN-1");
        while (!textStream.atEnd()) {
            textStream >> character;
            if (character == ';') {
                checkString(temp, character);
            } else if (character == '\n') {
                checkString(temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(temp);
            } else {
                temp.append(character);
            }
        }
    }
    model->removeRow(0,QModelIndex());
    //QModelIndex index = model->index(0,7);
    //model->setItem(0,8,QStandardItem("Hola"));
    QStandardItem *itemV = new QStandardItem("V");
    model->setItem(3,7,itemV);

}

void wgGestion::checkString(QString &temp, QChar character)
{
    if(temp.count("\"")%2 == 0) {
        //if (temp.size() == 0 && character != ',') //problem with line endings
        //    return;
        if (temp.startsWith( QChar('\"')) && temp.endsWith( QChar('\"') ) ) {
             temp.remove( QRegExp("^\"") );
             temp.remove( QRegExp("\"$") );
        }
        //FIXME: will possibly fail if there are 4 or more reapeating double quotes
        temp.replace("\"\"", "\"");
        QStandardItem *item = new QStandardItem(temp);
        standardItemList.append(item);
        if (character != QChar(';')) {
            model->appendRow(standardItemList);
            standardItemList.clear();
        }
        temp.clear();
    } else {
        temp.append(character);
    }

}
