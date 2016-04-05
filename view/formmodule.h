#ifndef FORMMODULE_H
#define FORMMODULE_H

#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QSignalMapper>
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
    void on_pbSetAll_clicked();
    void on_pbGetAll_clicked();
    void on_pbEdit_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pbSet_clicked();
    void on_pbGet_clicked();

    void writeLogFile();

    void on_pbAddRow_clicked();
    void set_kanal_clicked(int index);
    void del_src_clicked(int index);
    void del_alrm_clicked(int index);

    void on_pbDeleteRows_clicked();

    void on_pbRefresh_clicked();

private:
    worker *work;
    form_addModule *faddModule;
    QString module_name;\

    QString Address_Module;
    QString NoSeri;
    module mod;
    QSerialPort *Serial_Com;
    QLabel *type[16];

    MainWindow *Main;
    serial *Serial;
    setting *Setting;

    /** Function **/
    void setInterface(QString address);
    void setInterface_Input(QString address);
    void setInterface_Output(QString address);
    void setInterface_Communication(QString address);
    void setInterface_Environtment(QString address);
    void setInterface_Sumber(QString address);
    void setInterface_Alarm(QString address);
    void setInterface_Data(QString address);
    void EnableButton(bool enab);

    /** Input Tab **/
    QPushButton *set_input[16];
    QSignalMapper *SigMapSet_input;
    QLineEdit *name_input[16];
    QComboBox *type_input[16];
    QComboBox *state_input[16];
    QLineEdit *calib_m[16];
    QLineEdit *calib_x[16];
    QComboBox *reg_input[16];

    /** Output Tab **/
    QLineEdit *name_output[16];
    QLineEdit *type_output[16];
    QComboBox *state_output[16];
    QComboBox *control[16];

    /** Sources Tab **/
    QCheckBox *check_source[16];
    QPushButton *delete_source[16];
    QSignalMapper *SigMapDel_Source;
    QLineEdit *name_source[16];
    QLineEdit *ip_source[16];
    QLineEdit *port_source[16];
    QComboBox *state_source[16];
    QComboBox *type_source[16];
    QLineEdit *id_source[16];
    QLineEdit *sensor_reg_source[16];
    QComboBox *OffsetBase_source[16];
    QComboBox *command_source[16];
    QLineEdit *length_source[16];
    QLineEdit *target_reg_source[16];

    bool checkFormula(QString data);

    /** Alarm Threshold Tab **/
    QCheckBox *check_alarm[16];
    QPushButton *delete_alarm[16];
    QSignalMapper *SigMapDel_Alarm;
    QLineEdit *name_alarm[16];
    QComboBox *state_alarm[16];
    QLineEdit *input_reg_alarm[16];
    QLineEdit *output_reg_alarm[16];
    QLineEdit *range_l[16];
    QLineEdit *batas_ll[16];
    QLineEdit *batas_l[16];
    QLineEdit *batas_h[16];
    QLineEdit *batas_hh[16];
    QLineEdit *range_h[16];

    /** Data Monitoring **/
    QLabel *reg_data[20];
    QLabel *name_data[20];
    QLabel *value_data[20];
    QLabel *unit_data[20];

    void data_monitoring();
};

#endif // FORMMODULE_H
