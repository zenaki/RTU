#ifndef WORKER_H
#define WORKER_H

#include <QSerialPort>

#include "util/utama.h"

#include <model/interface_manipulator/mtreeview.h>
#include <model/module.h>
#include <view/formmodule.h>
#include <ui_formmodule.h>
#include "model/communication/serial.h"

//#include <QObject>
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
class QLightBoxWidget;

class worker /*: public QObject*/
{
//    Q_OBJECT
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

    void showModule(QWidget *parent, QMdiArea *mdiArea, QString module, QSerialPort *SerialPort, QLightBoxWidget *LightBox);

    bool checkIfmodule(QString name);
    bool state_of_module(int num, QString newModule, QString *existModule);

    bool Request_ENV(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout = false);
    bool Request_IO(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout = false);
    bool Request_SIM(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout = false);
    bool Request_Signal(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout = false);
    bool Request_Sumber(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout = false);
    bool Request_Data(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout = false);

    void Get_ENV(struct t_module *tModule, QStringList data);
    void Get_Input(struct t_module *tModule, QStringList data);
    void Get_Output(struct t_module *tModule, QStringList data);
    void Get_SIM(struct t_module *tModule, QStringList data);
    void Get_Signal(struct t_module *tModule, QStringList data);
    void Get_Sumber(struct t_module *tModule, QStringList data);
    void Get_Data(struct t_module *tModule, QStringList data);

//    QLightBoxWidget *lightBox;
//    QLabel *lbTitle;
//    QLabel *lbProgress;
//    QMovie *progressMovie;
//    QLabel *lbDescription;
//    QGridLayout *lbLayout;

//    QString Request;

    bool Set_ENV(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout = false);
    bool Set_Input(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout = false);
    bool Set_Output(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout = false);
    bool Set_SIM(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout = false);
    bool Set_Sumber(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout = false);
    bool Set_Data(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout = false);
    bool Reset_Board(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout = false);

    void write_FinishRead(bool FinishRead);
    bool read_FinishRead();

    void delay(int ms);
    bool waiting_set(QWidget *parent, QLightBoxWidget *lBox, QString desc, bool timeout = false);

    void writeLogFile(QString log);

//signals:
//    void TimeOut();
};

#endif // WORKER_H
