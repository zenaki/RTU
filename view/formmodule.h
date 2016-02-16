#ifndef FORMMODULE_H
#define FORMMODULE_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QStandardItem>
#include <QTableWidgetItem>

#include "view/mainwindow.h"
#include "model/module.h"
#include "model/setting.h"
#include "model/communication/serial.h"

namespace Ui {
class formModule;
}

class MainWindow;
class serial;
class setting;

class formModule : public QDialog
{
    Q_OBJECT

public:
    Ui::formModule *ui;

    explicit formModule(QWidget *parent = 0, QString address = 0, QSerialPort *SerialPort = 0);
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

    void on_pbSync_clicked();
    void readData();

private:
    QString Address_Module;
    QString NoSeri;
    module mod;
    QSerialPort *Serial_Com;
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
    void Syncronization();

    MainWindow *Main;
    serial *Serial;
    setting *Setting;
    QString str_data;
    QStringList val_data;
};

#endif // FORMMODULE_H
