#ifndef WORKER_H
#define WORKER_H

#include <QSerialPort>

#include "util/utama.h"

#include <model/interface_manipulator/mtreeview.h>
#include <model/module.h>
#include <view/mainwindow.h>
#include <view/formmodule.h>
#include <ui_formmodule.h>
#include "model/communication/serial.h"

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QTime>

#include <model/interface_manipulator/qlightboxwidget.h>

#include <QString>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QGridLayout>

//#include "JlCompress.h"

class MainWindow;
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

    void showModule(QWidget *parent, QMdiArea *mdiArea, QString module, QSerialPort *SerialPort);

    bool checkIfmodule(QString name);
    bool state_of_module(int num, QString newModule, QString *existModule);

    bool Request_ENV(QSerialPort *Serial_Com, bool timeout = false);

    void write_FinishRead(bool FinishRead, int cekErr, QString strErr);
    bool read_FinishRead();
    int read_flagERR();
    QString read_strERR();

    void delay(int ms);
    void serial_write(QSerialPort * Serial_Com, QString data, int d_c);
    bool waiting_set(bool timeout = false);

    void writeLogFile(QString log, int flagERR, QString strERR, bool timeout);

    void CompressDir(QString ZipFile, QString Directory);
    void DecompressDir(QString ZipFile, QString Directory);
    void CompressFiles(QString ZipFile, QStringList Files);
    void DecompressFiles(QString ZipFile, QStringList Files, QString Directory);
    QStringList ListContents(QString ZipFile);

//private slots:
//    void CancelSetting();
//signals:
//    void TimeOut();
};

#endif // WORKER_H
