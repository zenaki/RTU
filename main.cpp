#include "view/loginform.h"
#include "view/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /////////////////////////////////////////////////////////////////////////////////////////////////
    /** FOR DEPLOY **/
//    QApplication::setLibraryPaths(QStringList("/usr/lib/x86_64-linux-gnu"));
//    QString Path_Plugins = QLibraryInfo::location(QLibraryInfo::PrefixPath);
//    qDebug() << "Path_Plugins = " + Path_Plugins;
//    QString qt_conf_path =  QCoreApplication::applicationDirPath() + QDir::separator() + "qt.conf";
    /////////////////////////////////////////////////////////////////////////////////////////////////
    loginForm l;
    //Comment Baru
    l.show();

    return a.exec();
}
