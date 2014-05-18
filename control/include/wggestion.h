#ifndef WGGESTION_H
#define WGGESTION_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStandardItemModel>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QMessageBox>
#include <QApplication>
namespace Ui {
class wgGestion;
}

class wgGestion : public QWidget
{
    Q_OBJECT

public:
    explicit wgGestion(QWidget *parent = 0);
    ~wgGestion();

private slots:
    void on_btnAbrir_clicked();
    void checkString(QStandardItemModel &modelBase,QString &temp, QChar character = 0);

    void on_btnCargar_clicked();


    void on_btnAbrirBajas_clicked();

    void on_btnApplicarBajas_clicked();

private:
    Ui::wgGestion *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QStandardItemModel *modelBajas;
    QList<QStandardItem*> standardItemList;
    QStringList Header;
    QStringList HeaderBajas;
    QSqlDatabase *db;

};

#endif // WGGESTION_H
