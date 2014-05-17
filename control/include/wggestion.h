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
    void checkString(QString &temp, QChar character = 0);

    void on_btnCargar_clicked();

private:
    Ui::wgGestion *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;
    QStringList Header;
    QSqlDatabase *db;

};

#endif // WGGESTION_H
