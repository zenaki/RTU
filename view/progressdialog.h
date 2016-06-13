#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>

#include "util/utama.h"
#include "model/module.h"
#include "model/communication/serial.h"

#include <view/mainwindow.h>
#include <view/formmodule.h>
#include "model/communication/serial.h"

#include <QObject>
#include <QTime>
#include <model/interface_manipulator/qlightboxwidget.h>

#include <QString>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QGridLayout>

namespace Ui {
class ProgressDialog;
}
class serial;
class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = 0);
    ~ProgressDialog();

    void Processing(QSerialPort *SerialPort = 0, QString address = 0, QString mode = 0, QString index = 0);
    int progressVal;
    serial *Serial;
    QSerialPort *Serial_Com;

    void Request_ENV(bool stat);
    void Request_SIM(bool stat);
    void Request_IO(bool stat);
    void Request_Signal(bool stat);
    void Request_Sumber(bool stat);
    void Request_Data(bool stat);

    void Get_ENV(struct t_module *tModule, QStringList data);
    void Get_SIM(struct t_module *tModule, QStringList data);
    void Get_Input(struct t_module *tModule, QStringList data);
    void Get_Output(struct t_module *tModule, QStringList data);
//    void Get_Signal(struct t_module *tModule, QStringList data);
    void Get_Sumber(struct t_module *tModule, QStringList data);
    void Get_Data(struct t_module *tModule, QStringList data);

    module *mod;
    QString Request;
    QString Desc;
    QString str;
    QString temp;
    QString temp2;
    QString pth;
    QStringList list1;
    QStringList list2;
    QStringList list3;

    bool    timeout;
    int     flagERR;
    QString strERR;

    bool    cancel;
    bool    finish;

    void Set_ENV(bool stat, struct t_module *tModule);
    void Set_SIM(bool stat, struct t_module *tModule);
    void Set_Input(bool stat, struct t_module *tModule, QString index = 0);
    void Set_Output(bool stat, struct t_module *tModule, QString index = 0);
    void Set_Sumber(bool stat, struct t_module *tModule, QString index = 0);
    void Set_Data(bool stat, struct t_module *tModule, QString index = 0);
    void Reset_Board(bool stat);

    void write_FinishRead(bool FinishRead, int cekErr, QString strErr);
    bool read_FinishRead(); int read_flagERR(); QString read_strERR();

    void delay(int ms);
    void serial_write(QString desc, QString data, int delay_char);
    void waiting_set();

    void writeLogFile(QString log, int flagERR, QString strERR, bool timeout);

private slots:
    void on_pbDetail_clicked();

    void on_pbCancel_clicked();

private:
    Ui::ProgressDialog *ui;
};

#endif // PROGRESSDIALOG_H
