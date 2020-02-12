#ifndef FORMREGISTER_H
#define FORMREGISTER_H

#include <QWidget>
#include "login.h"

namespace Ui {
class Formregister;
}

class Formregister : public QWidget
{
    Q_OBJECT

public:
    explicit Formregister(QWidget *parent = 0);
    ~Formregister();

private slots:
    void on_pushButton_yes_clicked();

    void on_pushButton_no_clicked();

private:
    Ui::Formregister *ui;
};

#endif // FORMREGISTER_H
