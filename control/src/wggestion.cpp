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

    modelBajas = new QStandardItemModel(this);
    HeaderBajas.clear();
    HeaderBajas << "DNI" << "Fecha Baja" << "BAJA";
    modelBajas->setHorizontalHeaderLabels(HeaderBajas);
    ui->grdVBajas->setModel(modelBajas);

    model = new QStandardItemModel(this);
    Header.clear();
    Header << "DNI" << "Nombres" << "Apellido Paterno" << "Apellido Materno" << "Fecha Nacimiento" << "Fecha Ingreso" << "Formacion" << "Registrado";
    model->setHorizontalHeaderLabels(Header);
    ui->grdVData->setModel(model);
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    db->setHostName("PECIXAP001");
    db->setDatabaseName("Triamera-Control");
    db->setUserName("postgres");
    db->setPassword("triamera");
    db->setPort(5432);


    if (!db->open())
    {
       QMessageBox::critical(0,"Error en Base de Datos","No se pudo establecer conexion con la base de datos", QMessageBox::Ok);
       QMessageBox msgBox;
        msgBox.setText(db->lastError().text());
        msgBox.exec();

        ui->tabWidget->setEnabled(false);
    }
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
    Header.clear();
    Header << "DNI" << "Nombres" << "Apellido Paterno" << "Apellido Materno" << "Fecha Nacimiento" << "Fecha Ingreso" << "Formacion" << "Registrado";
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
                checkString(*model, temp, character);
            } else if (character == '\n') {
                checkString(*model,temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(*model, temp);
            } else {
                temp.append(character);
            }
        }
    }
    model->removeRow(0,QModelIndex());
    //QModelIndex index = model->index(0,7);
    //model->setItem(0,8,QStandardItem("Hola"));
//    QStandardItem *itemV = new QStandardItem("V");
//    model->setItem(3,7,itemV);

}

void wgGestion::checkString(QStandardItemModel &modelBase, QString &temp, QChar character)
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
            //modelBase->appendRow(standardItemList);
            modelBase.appendRow(standardItemList);
            standardItemList.clear();
        }
        temp.clear();
    } else {
        temp.append(character);
    }

}

void wgGestion::on_btnCargar_clicked()
{
    QSqlQuery query;
//    query.exec("SELECT * FROM personal_datos;");
//    while (query.next()) {
//        QString name = query.value(0).toString();
//        QString salary = query.value(1).toString();
//        qDebug() << name << salary;
//    }
    for (int mRow = 0; mRow < model->rowCount(); ++mRow)
    {
        QStandardItem *m_dni= model->item(mRow,0);
        QStandardItem *m_nom= model->item(mRow,1);
        QStandardItem *m_app= model->item(mRow,2);
        QStandardItem *m_apm= model->item(mRow,3);
        QStandardItem *m_fna= model->item(mRow,4);
        QStandardItem *m_fin= model->item(mRow,5);
        QStandardItem *m_for= model->item(mRow,6);
        //QStandardItem *m_item = new QStandardItem;
        //m_item = model->item(mRows,0);
        db->transaction();
        query.exec("SELECT personal_add('"+m_dni->text().trimmed()+
                      "','"+m_nom->text().trimmed()+
                      "','"+m_app->text().trimmed()+
                      "','"+m_apm->text().trimmed()+
                      "','"+m_fna->text().trimmed()+
                      "','"+m_fin->text().trimmed()+
                      "',"+m_for->text().trimmed()+");");

//        query.bindValue(":dni",m_dni->text());
//        query.bindValue(":nom",m_nom->text());
//        query.bindValue(":app",m_app->text());
//        query.bindValue(":apm",m_apm->text());
//        query.bindValue(":fna",m_fna->text());
//        query.bindValue(":fin",m_fin->text());
//        query.bindValue(":for",m_for->text());

        db->commit();
        query.last();

//        qDebug()<<query.lastQuery();
//        qDebug()<<query.lastError();
//        qDebug()<<query.value(0).toString();
        if (query.value(0).toBool())
        {
            QStandardItem *itemV = new QStandardItem("REGISTRADO");
            model->setItem(mRow ,7,itemV);
        }else{
            QStandardItem *itemV = new QStandardItem("DUPLICADO");
            model->setItem(mRow ,7,itemV);

        }
        //qDebug()<<query.value(0).toString();


    }

}

void wgGestion::on_btnAbrirBajas_clicked()
{
    modelBajas->clear();
    HeaderBajas.clear();
    HeaderBajas << "DNI" << "Fecha Baja" << "BAJA";
    modelBajas->setHorizontalHeaderLabels(HeaderBajas);

    QString fileName = QFileDialog::getOpenFileName (this, "Open CSV file",
                                                     QDir::currentPath(), "CSV (*.csv)");
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
                checkString(*modelBajas, temp, character);
            } else if (character == '\n') {
                checkString(*modelBajas, temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(*modelBajas, temp);
            } else {
                temp.append(character);
            }
        }
    }
    modelBajas->removeRow(0,QModelIndex());
}

void wgGestion::on_btnApplicarBajas_clicked()
{
    QSqlQuery queryBaja;

    for (int mRow = 0; mRow < modelBajas->rowCount(); ++mRow)
    {
        QStandardItem *m_dniBaja= modelBajas->item(mRow,0);
        QStandardItem *m_fecBaja= modelBajas->item(mRow,1);
        db->transaction();
        queryBaja.exec("SELECT personal_baja('"+m_dniBaja->text().trimmed()+"','"+m_fecBaja->text().trimmed()+"');");
        db->commit();
        queryBaja.last();
        if(queryBaja.value(0).toBool())
        {
            QStandardItem *itemB = new QStandardItem("APLICADA");
            modelBajas->setItem(mRow ,2,itemB);
        }else{
            QStandardItem *itemB = new QStandardItem("NO APLICADA");
            modelBajas->setItem(mRow ,2,itemB);
        }

    }
}
