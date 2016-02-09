#ifndef FORMMODULE_H
#define FORMMODULE_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QStandardItem>
#include <QTableWidgetItem>
#include <QDialog>
#include <QtSerialPort/QSerialPort>

#include "model/module.h"
#include "view/settingsdialog.h"
#include "ui_settingsdialog.h"

namespace Ui {
class formModule;
}

class SettingsDialog;

class formModule : public QDialog
{
    Q_OBJECT

public:
    Ui::formModule *ui;
    QString Address_Module;

    explicit formModule(QWidget *parent = 0, struct t_module *tModule = 0, QString address = 0);
    ~formModule();

private slots:
    void on_pbSet_clicked();
    void on_pbEdit_clicked();
    void on_pbSave_clicked();
    void on_pbCancel_clicked();

    void on_com_1_currentIndexChanged(int index);
    void on_com_2_currentIndexChanged(int index);

    void on_tabWidget_tabBarClicked(int index);

    void on_pbEdit_Module_clicked();
    void on_pbSave_Module_clicked();
    void on_pbCancel_Module_clicked();

    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

private:
    module mod;
    QLabel *type[16];

    /** Input Tab **/
    QLineEdit *name_input[16];
    QComboBox *type_input[16];
    QComboBox *state_input[16];
    QLineEdit *calib_m[16];
    QLineEdit *calib_x[16];

    QLineEdit *name_output[16];
    QLineEdit *type_output[16];
    QComboBox *state_output[16];
    QComboBox *control[16];


    /** Function **/
    void setInterface(QString address);

    /** Serial Communication **/
    struct Connection_Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    void initActionsConnections();
    QString StatusMessage;
    SettingsDialog *Com_Setting;
    QSerialPort *serial;
    Connection_Settings p;
};

#endif // FORMMODULE_H
