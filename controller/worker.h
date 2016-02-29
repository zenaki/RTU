#ifndef WORKER_H
#define WORKER_H

#include <QSerialPort>

#include "util/utama.h"

#include <model/interface_manipulator/mtreeview.h>
#include <model/module.h>
#include <view/formmodule.h>
#include <ui_formmodule.h>
#include "model/communication/serial.h"

#include <QtSerialPort/QSerialPort>
#include <QTime>

#include <model/interface_manipulator/qlightboxwidget.h>

#include <QString>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QGridLayout>

class formModule;
class serial;

class worker
{
public:
    worker();
    module mod;
    mTreeview mTree;
    serial *Serial;

    QString newModule(QStandardItemModel *tree, QTreeView *treeView, QString title);
    QString editModule(QStandardItemModel *tree, QTreeView *treeView, QString title);
    QString loadModule(QStandardItemModel *tree, QTreeView *treeView, QString address, QString NewName);
    QString checkModule(QString address);
    QString check_statusModule(QString address);

    void showModule(QWidget *parent, QMdiArea *mdiArea, QString module, QSerialPort *SerialPort);

    bool checkIfmodule(QString name);
    bool state_of_module(int num, QString newModule, QString *existModule);

    void Get_ENV(struct t_module *tModule, QStringList data);
    void Get_IO(struct t_module *tModule, QStringList data);
    void Get_SIM(struct t_module *tModule, QStringList data);
    void Get_SIG(struct t_module *tModule, QStringList data);

//    QString Request;

    void Set_ENV(QWidget *parent, QString desc, QSerialPort *Serial_Com, struct t_module *tModule);
    void Set_IO(QWidget *parent, QString desc, QSerialPort *Serial_Com, struct t_module *tModule);
    void Set_SIM(QWidget *parent, QString desc, QSerialPort *Serial_Com, struct t_module *tModule);

    void delay(int ms);
};

#endif // WORKER_H
