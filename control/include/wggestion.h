#ifndef WGGESTION_H
#define WGGESTION_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStandardItemModel>

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

private:
    Ui::wgGestion *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;
};

#endif // WGGESTION_H
