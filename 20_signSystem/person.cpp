#include "person.h"
#include "ui_person.h"

Person::Person(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
    QFile qssFileName(":/qss/style.qss");
    qssFileName.open(QIODevice::ReadOnly);
    this->setStyleSheet(qssFileName.readAll());
    this->setWindowIcon(QIcon(":/editer_image/yellowDuck.ico"));
    this->setWindowTitle("个 人 界 面");
}


void Person::init(QString sno,QString sname) //标记选中同学已签到日期，显示签到次数
{
    ui->label->setText("学号: " + sno);
    ui->label_2->setText("姓名: " + sname);

    QSqlQuery q;
    qDebug()<<q.exec(QString("select Signtime from Qtsign "
                             "where sno = %1 and date_format(Signtime,'%Y-%m') = "
                             "date_format(curdate(),'%Y-%m')").arg(sno));
    ui->label_3->setText("签到次数： "+QString::number(q.size()));

    QTextCharFormat colorday;
    colorday.setForeground(Qt::green);
    colorday.setBackground(Qt::gray);

    while(q.next()){
        ui->calendarWidget->setDateTextFormat(q.value(0).toDate(),colorday);
    }
}

Person::~Person()
{
    delete ui;
}
