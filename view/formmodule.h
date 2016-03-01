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
#include <view/mainwindow.h>
#include <ui_mainwindow.h>
#include <model/interface_manipulator/qlightboxwidget.h>
#include <view/wait_process.h>

namespace Ui {
class formModule;
}

class worker;
class MainWindow;
class serial;
class setting;
class QLightBoxWidget;
class wait_process;

class formModule : public QDialog
{
    Q_OBJECT

public:
    Ui::formModule *ui;

    explicit formModule(QWidget *parent = 0, QString address = 0, QSerialPort *SerialPort = 0, QLightBoxWidget *LightBox = 0);
    ~formModule();

    QLightBoxWidget *busyForm;
    wait_process *wait;
private slots:
    void on_pbSet_clicked();
    void on_pbGet_clicked();
    void on_pbEditModule_clicked();

    void on_tabWidget_tabBarClicked(int index);

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

    MainWindow *Main;
    serial *Serial;
    setting *Setting;
};

#endif // FORMMODULE_H
