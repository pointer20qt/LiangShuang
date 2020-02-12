#include "widget.h"
#include <QApplication>
#include "login.h"
#include "ui_login.h"
#include "formregister.h"
#include "ui_formregister.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Formregister register_in;
    //register_in.show();

    Login log_in;
    log_in.show();


    //Widget w;
    //w.show();

    return a.exec();
}
