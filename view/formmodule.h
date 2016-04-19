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
    wait_process    *wait;
private slots:
    void on_pbSetAll_clicked();
    void on_pbGetAll_clicked();
    void on_pbEdit_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pbSet_clicked();
    void on_pbGet_clicked();

    void on_pbSetChk_clicked();

    void writeLogFile();

    void reg_kanal_changed();
    void on_pbAddRow_clicked();
    void del_src_clicked(int index);
    void length_src_changed();
    void tReg_src_changed();
    void del_alrm_clicked(int index);
    void input_alrm_changed(int index);

    void on_pbDeleteRows_clicked();

    void on_pbRefresh_clicked();    
private:
    worker          *work;
    form_addModule  *faddModule;
    QString         module_name;

    QString         Address_Module;
    QString         NoSeri;
    module          mod;
    QSerialPort     *Serial_Com;
//    QLabel          *type[16];

    MainWindow      *Main;
    serial          *Serial;
    setting         *Setting;

    /** Function **/
    void setInterface(QString address);
    void setInterface_Input(QString address);
    void setInterface_Output(QString address);
    void setInterface_Communication(QString address);
    void setInterface_Environtment(QString address);
    void setInterface_Sumber(QString address);
    void setInterface_Alarm(QString address);
    void setInterface_Data_Settings(QString address);
    void setInterface_Data_Monitoring(QString address);
    void EnableButton(bool enab);

    /** Input Tab **/
    QCheckBox       *check_input[16];
    QLineEdit       *name_input[16];
    QComboBox       *type_input[16];
    QComboBox       *state_input[16];
    QLineEdit       *calib_m[16];
    QLineEdit       *calib_x[16];
    QComboBox       *reg_input[60];
    QSignalMapper   *SigMapReg_input;

    /** Output Tab **/
    QCheckBox       *check_output[16];
    QLineEdit       *name_output[16];
    QLineEdit       *type_output[16];
    QComboBox       *state_output[16];
    QComboBox       *control[16];

    /** Sources Tab **/
    QCheckBox       *check_source[16];
    QPushButton     *delete_source[16];
    QSignalMapper   *SigMapDel_Source;
    QLineEdit       *name_source[16];
    QLineEdit       *ip_source[16];
    QLineEdit       *port_source[16];
    QComboBox       *state_source[16];
    QComboBox       *type_source[16];
    QLineEdit       *id_source[16];
    QLineEdit       *sensor_reg_source[16];
    QComboBox       *OffsetBase_source[16];
    QComboBox       *command_source[16];
    QComboBox       *length_source[16];
    QSignalMapper   *SigMap_length_source;
    QComboBox       *target_reg_source[16];
    QSignalMapper   *SigMap_tReg_source;

    bool checkFormula(QString data);

    /** Alarm Threshold Tab **/
    QCheckBox       *check_alarm[16];
    QPushButton     *delete_alarm[16];
    QSignalMapper   *SigMapDel_alarm;
    QLineEdit       *name_alarm[16];
    QComboBox       *state_alarm[16];
    QComboBox       *input_alarm[16];
    QSignalMapper   *SigMapInput_alarm;
    QComboBox       *output_alarm[16];
    QLineEdit       *range_l[16];
    QLineEdit       *batas_ll[16];
    QLineEdit       *batas_l[16];
    QLineEdit       *batas_h[16];
    QLineEdit       *batas_hh[16];
    QLineEdit       *range_h[16];

    /** Data Settings **/
    QCheckBox       *check_data_s[60];
    QLineEdit       *id_data_s[60];
    QLineEdit       *name_data_s[60];
    QLineEdit       *value_data_s[60];
    QLineEdit       *unit_data_s[60];
    QLineEdit       *range_l_data_s[60];
    QLineEdit       *border_ll_data_s[60];
    QLineEdit       *border_l_data_s[60];
    QLineEdit       *border_h_data_s[60];
    QLineEdit       *border_hh_data_s[60];
    QLineEdit       *range_h_data_s[60];
    QComboBox       *state_data_s[60];

    /** Data Monitoring **/
    QLabel          *reg_data[60];
    QLabel          *name_data[60];
    QLabel          *value_data[60];
    QLabel          *unit_data[60];

    void data_monitoring();
};

#endif // FORMMODULE_H
