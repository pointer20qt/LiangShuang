#include "formregister.h"
#include "ui_formregister.h"
#include <QMessageBox>
#include <QSqlQuery>

Formregister::Formregister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formregister)
{
    ui->setupUi(this);

    QFile qssFileName(":/qss/style.qss");
    qssFileName.open(QIODevice::ReadOnly);
    this->setStyleSheet(qssFileName.readAll());
    this->setWindowIcon(QIcon(":/editer_image/yellowDuck.ico"));
    this->setWindowTitle("欢 迎 注 册");
}

Formregister::~Formregister()
{
    delete ui;
}

void Formregister::on_pushButton_yes_clicked()//判断注册是否合法，如果合法则插入数据库
{
    QString sno = ui->lineEdit_sno->text();
    QString sname = ui->lineEdit_sname->text();
    QString classname = ui->lineEdit_class->text();
    QString pwd = ui->lineEdit_pwd->text();
    QString pwd2 = ui->lineEdit_pwd2->text();

    if(pwd != pwd2){
        QMessageBox::warning(this,"warn","二次密码不一致");
    }else{
        if(sno.size() == 0||sname.size() == 0||classname.size() == 0||pwd.size() == 0){
            QMessageBox::warning(this,"warn","输入不能为空");
        }else{
            QSqlQuery q;
            q.exec(QString("insert into QtStudent values('%1','%2','%3','%4')").arg(sno).arg(sname).arg(classname).arg(pwd));
            QMessageBox::warning(this,"Successful","注册成功");
            this->close();
        }

    }
}


void Formregister::on_pushButton_no_clicked()//关闭界面
{
    this->close();
}
