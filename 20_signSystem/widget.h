#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QCheckBox>
#include <QTableWidget>
#include <QDateTime>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTextCharFormat>
#include <QFile>
#include "formregister.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0,QString sname = NULL);
    ~Widget();
    void datatotable(QString sql);
    void displayClass();
    void displaySno();
    void opensql();
    QString sname;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
