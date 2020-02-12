#include "login.h"
#include "ui_login.h"
#include <QSqlQuery>


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QFile qssFileName(":/qss/style.qss");
    qssFileName.open(QIODevice::ReadOnly);
    this->setStyleSheet(qssFileName.readAll());
    this->setWindowIcon(QIcon(":/editer_image/yellowDuck.ico"));
    this->setWindowTitle("请 您 登 陆");


    opensql();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()//注册
{
    Formregister *r = new Formregister();
    r->show();
}

void Login::on_pushButton_2_clicked()//登录
{
    QString sname = ui->lineEdit->text();
    QString pwd = ui->lineEdit_2->text();

    QSqlQuery q;
    q.exec(QString("select * from QtStudent where sname = '%1'").arg(sname));
    if(q.size()>0)
    {
        q.exec(QString("select * from QtStudent "
                       "where sname = '%1' and pwd = '%2'").arg(sname).arg(pwd));
        if(q.size()>0){
            Widget* w = new Widget(NULL,sname);
            w->sname = sname;
            w->show();
            this->close();
        }else{
            QMessageBox::warning(this,"warn","密码错误");
        }
    }else{
        QMessageBox::warning(this,"warn","用户不存在");
    }
}

void Login::opensql(){//打开数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("text1");
    db.setUserName("root");
    db.setPassword("123456");
    if (db.open())
    {
        qDebug()<<"打开数据库成功";
    }
    else
    {
        qDebug()<<"打开数据库成功";
    }
}
