#include "widget.h"
#include "ui_widget.h"
#include "person.h"

Widget::Widget(QWidget *parent, QString sname) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFile qssFileName(":/qss/style.qss");
    qssFileName.open(QIODevice::ReadOnly);
    this->setStyleSheet(qssFileName.readAll());
    this->setWindowIcon(QIcon(":/editer_image/yellowDuck.ico"));
    this->setWindowTitle("签 到 记 录");

    this->sname=sname;

    opensql();

    datatotable("select * from QtStudent");
    
    displayClass();

    displaySno();

   connect(ui->tableWidget,QTableWidget::cellDoubleClicked,[=](int r,int c){//双击所在行显示person界面
        Person* p = new Person();
        p->init(ui->tableWidget->item(r,0)->text(),ui->tableWidget->item(r,1)->text());
        p->show();
    });



}


void Widget::datatotable(QString sql){//将数据显示到表格
    QSqlQuery q;
    q.exec(QString("select sno from QtStudent where sname = '%1'").arg(this->sname));
    q.next();
    QString curSno = q.value(0).toString();;

    if(q.exec(sql))
    {
        ui->tableWidget->setRowCount(q.size());
        int i = 0;
        while(q.next())
        {
            QCheckBox *c = new QCheckBox("未签到");//控件是否签到
            QString sno = q.value(0).toString();

            QSqlQuery q3;
            q3.exec(QString("select Signtime from QtSign "
                            "where sno = %1 and date(signtime) = curdate() "
                            "order by signtime desc").arg(sno));
            q3.next();


            if(sno != curSno)
            {
                c->setDisabled(true);
            }


            if(q3.size())
            {
                c->setText("已签到");
                c->setDisabled(true);
                c->setChecked(true);
                ui->tableWidget->setItem(i,4,new QTableWidgetItem(q3.value(0).toString()));
            }

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(sno));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(q.value(1).toString()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(q.value(2).toString()));
            ui->tableWidget->setCellWidget(i,3,c);

            connect(c,QCheckBox::clicked,[=](){
                    //修改控件状态
                    c->setText("已签到");
                    c->setDisabled(true);
                    //签到时间
                    ui->tableWidget->setItem(i,4,new QTableWidgetItem(QDateTime::currentDateTime().toString()));
                    //插入数据库
                    QSqlQuery q1;
                    q1.exec(QString("insert into QtSign values(%1,now())").arg(sno));
            });
            i++;
        }
    }

}

void Widget::displayClass(){//选择班级并显示
    QSqlQuery sqlclass;//数据库中所有班级
    sqlclass.exec("select distinct class from QtStudent");
    ui->comboBox->addItem("全部班级");
    while(sqlclass.next())
    {
        ui->comboBox->addItem(sqlclass.value(0).toString());
    }
    connect(ui->comboBox,QComboBox::currentTextChanged,[=](QString sqlclass){//选择班级并将选择的班级显示
        if(sqlclass == "全部班级")
        {
            datatotable("select * from QtStudent");
        }
        else
        {
            datatotable(QString("select * from Qtstudent where class = '%1'").arg(sqlclass));
        }
    });
}

void Widget::displaySno(){//输入学号并示
    connect(ui->pushButton,QPushButton::clicked,[=](){
        if(ui->lineEdit->text().isEmpty()){
            QMessageBox::warning(this,"warn","输入为空");
        }
        else{
           datatotable(QString("select * from Qtstudent where sno like '%1'").arg(ui->lineEdit->text()));
        }
    });


}

void Widget::opensql(){//打开数据库
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

Widget::~Widget()
{
    delete ui;
}
