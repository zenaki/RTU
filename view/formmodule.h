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

#include <controller/worker.h>

#include <view/form_addmodule.h>
#include <ui_form_addmodule.h>
#include <ui_mainwindow.h>

namespace Ui {
class formModule;
}

class worker;
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
    void on_pbGet_clicked();

    void on_tabWidget_tabBarClicked(int index);
    void readData();

    void on_pushButton_clicked();

private:
    worker *work;
    form_addModule *faddModule;
    QString module_name;\

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
