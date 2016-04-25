#include "view/loginform.h"
#include "view/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginForm l;

    l.show();

    return a.exec();
}
