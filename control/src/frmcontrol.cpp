#include "../include/frmcontrol.h"
#include "ui_frmcontrol.h"

frmControl::frmControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmControl)
{
    ui->setupUi(this);
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    db->setHostName("PECIXAP001");
    db->setDatabaseName("Triamera-Control");
    db->setUserName("postgres");
    db->setPassword("triamera");
    db->setPort(5432);

    if (!db->open())
    {
       QMessageBox::critical(0,"Error en Base de Datos","No se pudo establecer conexion con la base de datos", QMessageBox::Ok);
        ui->txtDNI->setEnabled(false);
    }
    ui->lblNombres->setText(" ");
    ui->lblApPaterno->setText(" ");
    ui->lblApMaterno->setText(" ");
    ui->lblFecha->setText(" ");
    ui->lblEstado->setText(" ");


}

frmControl::~frmControl()
{
    delete ui;
}

void frmControl::on_txtDNI_returnPressed()
{
    QSqlQuery query;
    QString m_dni =  ui->txtDNI->text().trimmed();
    query.exec("SELECT * FROM personal_datos WHERE dni::bigint = "+m_dni+"::bigint;");
    //query.last();
    if (query.size() > 0)
    {
        query.first();
        ui->lblNombres->setText(query.value(1).toString().trimmed());
        ui->lblApPaterno->setText(query.value(2).toString().trimmed());
        ui->lblApMaterno->setText(query.value(3).toString().trimmed());
        QDate m_fecha = query.value(5).toDate();
        ui->lblFecha->setText(m_fecha.toString("dd/MM/yyyy"));

        if (query.value(6).isNull())
        {
            if (query.value(7).toBool())
            {
                QDate m_fecha = query.value(6).toDate();
                ui->lblFecha->setText(m_fecha.toString("dd/MM/yyyy"));

                ui->lblEstado->setStyleSheet("font: 87 24pt ""Arial Black""; color: rgb(255, 175, 46);");
                ui->lblFecha->setStyleSheet("font: 87 24pt ""Arial Black""; color: rgb(255, 175, 46);");
                ui->lblEstado->setText("CAPACITACION");
            } else {
                QDate m_fecha = query.value(6).toDate();
                ui->lblFecha->setText(m_fecha.toString("dd/MM/yyyy"));

                ui->lblEstado->setStyleSheet("font: 87 24pt ""Arial Black""; color: rgb(85, 170, 0);");
                ui->lblFecha->setStyleSheet("font: 87 24pt ""Arial Black""; color: rgb(85, 170, 0);");
                ui->lblEstado->setText("TRABAJADOR");
            }

        } else {
            QDate m_fecha = query.value(6).toDate();
            ui->lblFecha->setText(m_fecha.toString("dd/MM/yyyy"));

            ui->lblEstado->setStyleSheet("font: 87 24pt ""Arial Black""; color: rgb(199, 0, 3);");
            ui->lblFecha->setStyleSheet("font: 87 24pt ""Arial Black""; color: rgb(199, 0, 3);");
            ui->lblEstado->setText("EX TRABAJADOR");
        }


    } else {
        ui->lblNombres->setText(" ");
        ui->lblApPaterno->setText(" ");
        ui->lblApMaterno->setText(" ");
        ui->lblFecha->setText(" ");
        ui->lblEstado->setStyleSheet("font: 87 24pt ""Arial Black""; color: rgb(199, 0, 3);");
        ui->lblEstado->setText("NO REGISTRADO");
    }
}
