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

/**
 * @brief The ProgressDialog class
 */
class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ProgressDialog
     * @param parent
     */
    explicit ProgressDialog(QWidget *parent = 0);
    ~ProgressDialog();

    /**
     * @brief Processing
     * @param SerialPort
     * @param address
     * @param mode
     * @param index
     */
    void Processing(QSerialPort *SerialPort = 0, QString address = 0, QString mode = 0, QString index = 0);
    /**
     * @brief progressVal
     */
    int progressVal;
    /**
     * @brief Serial
     */
    serial *Serial;
    /**
     * @brief Serial_Com
     */
    QSerialPort *Serial_Com;

    /**
     * @brief Request_ENV
     * @param stat
     */
    void Request_ENV(bool stat);
    /**
     * @brief Request_SIM
     * @param stat
     */
    void Request_SIM(bool stat);
    /**
     * @brief Request_IO
     * @param stat
     */
    void Request_IO(bool stat);
    /**
     * @brief Request_Signal
     * @param stat
     */
    void Request_Signal(bool stat);
    /**
     * @brief Request_Sumber
     * @param stat
     */
    void Request_Sumber(bool stat);
    /**
     * @brief Request_Data
     * @param stat
     */
    void Request_Data(bool stat);

    /**
     * @brief Get_ENV
     * @param tModule
     * @param data
     */
    void Get_ENV(struct t_module *tModule, QStringList data);
    /**
     * @brief Get_SIM
     * @param tModule
     * @param data
     */
    void Get_SIM(struct t_module *tModule, QStringList data);
    /**
     * @brief Get_Input
     * @param tModule
     * @param data
     */
    void Get_Input(struct t_module *tModule, QStringList data);
    /**
     * @brief Get_Output
     * @param tModule
     * @param data
     */
    void Get_Output(struct t_module *tModule, QStringList data);
//    void Get_Signal(struct t_module *tModule, QStringList data);
    /**
     * @brief Get_Sumber
     * @param tModule
     * @param data
     */
    void Get_Sumber(struct t_module *tModule, QStringList data);
    /**
     * @brief Get_Data
     * @param tModule
     * @param data
     */
    void Get_Data(struct t_module *tModule, QStringList data);

    /**
     * @brief mod
     */
    module *mod;
    /**
     * @brief Request
     */
    QString Request;
    /**
     * @brief Desc
     */
    QString Desc;
    /**
     * @brief str
     */
    QString str;
    /**
     * @brief temp
     */
    QString temp;
    /**
     * @brief temp2
     */
    QString temp2;
    /**
     * @brief pth
     */
    QString pth;
    /**
     * @brief list1
     */
    QStringList list1;
    /**
     * @brief list2
     */
    QStringList list2;
    /**
     * @brief list3
     */
    QStringList list3;

    /**
     * @brief timeout
     */
    bool    timeout;
    /**
     * @brief flagERR
     */
    int     flagERR;
    /**
     * @brief strERR
     */
    QString strERR;

    /**
     * @brief cancel
     */
    bool    cancel;
    /**
     * @brief finish
     */
    bool    finish;
    /**
     * @brief cnt_try
     */
    int     cnt_try;

    /**
     * @brief Set_ENV
     * @param stat
     * @param tModule
     */
    void Set_ENV(bool stat, struct t_module *tModule);
    /**
     * @brief Set_SIM
     * @param stat
     * @param tModule
     */
    void Set_SIM(bool stat, struct t_module *tModule);
    /**
     * @brief Set_Input
     * @param stat
     * @param tModule
     * @param index
     */
    void Set_Input(bool stat, struct t_module *tModule, QString index = 0);
    /**
     * @brief Set_Output
     * @param stat
     * @param tModule
     * @param index
     */
    void Set_Output(bool stat, struct t_module *tModule, QString index = 0);
    /**
     * @brief Set_Sumber
     * @param stat
     * @param tModule
     * @param index
     */
    void Set_Sumber(bool stat, struct t_module *tModule, QString index = 0);
    /**
     * @brief Set_Data
     * @param stat
     * @param tModule
     * @param index
     */
    void Set_Data(bool stat, struct t_module *tModule, QString index = 0);
    /**
     * @brief Reset_Board
     * @param stat
     */
    void Reset_Board(bool stat);

    /**
     * @brief write_FinishRead
     * @param FinishRead
     * @param cekErr
     * @param strErr
     */
    void write_FinishRead(bool FinishRead, int cekErr, QString strErr);
    /**
     * @brief read_FinishRead
     * @return
     */
    bool read_FinishRead(); int read_flagERR(); QString read_strERR();


    /**
     * @brief delay
     * @param ms
     */
    void delay(int ms);
    /**
     * @brief serial_write
     * @param desc
     * @param data
     * @param delay_char
     */
    void serial_write(QString desc, QString data, int delay_char);
    /**
     * @brief waiting_set
     */
    void waiting_set();

    /**
     * @brief writeLogFile
     * @param log
     * @param flagERR
     * @param strERR
     * @param timeout
     */
    void writeLogFile(QString log, int flagERR, QString strERR, bool timeout);

private slots:
    /**
     * @brief on_pbDetail_clicked
     */
    void on_pbDetail_clicked();

    /**
     * @brief on_pbCancel_clicked
     */
    void on_pbCancel_clicked();

private:
    /**
     * @brief ui
     */
    Ui::ProgressDialog *ui;
};

#endif // PROGRESSDIALOG_H
