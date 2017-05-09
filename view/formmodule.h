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

#include "controller/worker.h"

#include "view/form_addmodule.h"
#include "ui_form_addmodule.h"
#include "view/mainwindow.h"
#include "ui_mainwindow.h"
//#include <model/interface_manipulator/qlightboxwidget.h>
#include "view/progressdialog.h"

namespace Ui {
    class formModule;
}

class worker;
class MainWindow;
class serial;
class setting;
//class QLightBoxWidget;
class wait_process;
class ProgressDialog;
class DebugDialog;

/**
 * @brief The formModule class
 */
class formModule : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ui
     */
    Ui::formModule *ui;

    /**
     * @brief formModule
     * @param parent
     * @param address
     * @param SerialPort
     */
    explicit formModule(QWidget *parent = 0, QString address = 0, QSerialPort *SerialPort = 0);
    ~formModule();

//    QLightBoxWidget *busyForm;
    /**
     * @brief wait
     */
    wait_process    *wait;
    /**
     * @brief eventFilter
     */
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    /**
     * @brief on_pbSetAll_clicked
     */
    void on_pbSetAll_clicked();
    /**
     * @brief on_pbGetAll_clicked
     */
    void on_pbGetAll_clicked();
    /**
     * @brief on_pbEdit_clicked
     */
    void on_pbEdit_clicked();

    /**
     * @brief on_tabWidget_tabBarClicked
     * @param index
     */
    void on_tabWidget_tabBarClicked(int index);

    /**
     * @brief on_pbSet_clicked
     */
    void on_pbSet_clicked();
    /**
     * @brief on_pbGet_clicked
     */
    void on_pbGet_clicked();

    /**
     * @brief on_pbSetChk_clicked
     */
    void on_pbSetChk_clicked();

    /**
     * @brief writeLogFile
     */
    void writeLogFile();

    /**
     * @brief reg_kanal_changed
     */
    void reg_kanal_changed();
    /**
     * @brief on_pbAddRow_clicked
     */
    void on_pbAddRow_clicked();
    /**
     * @brief del_src_clicked
     * @param index
     */
    void del_src_clicked(int index);
    /**
     * @brief length_src_changed
     */
    void length_src_changed();
    /**
     * @brief tReg_src_changed
     */
    void tReg_src_changed();
    /**
     * @brief del_frm_clicked
     * @param index
     */
    void del_frm_clicked(int index);
    /**
     * @brief del_alrm_clicked
     * @param index
     */
    void del_alrm_clicked(int index);
    /**
     * @brief input_alrm_changed
     * @param index
     */
    void input_alrm_changed(int index);

    /**
     * @brief on_pbDeleteRows_clicked
     */
    void on_pbDeleteRows_clicked();

    /**
     * @brief on_pbRefresh_clicked
     */
    void on_pbRefresh_clicked();

//    /**
//     * @brief state_kanal_change
//     * @param index
//     */
//    void state_kanal_change(int index);
//    /**
//     * @brief state_data_change
//     * @param index
//     */
//    void state_data_change(int index);

private:
    /**
     * @brief work
     */
    worker          *work;
    /**
     * @brief faddModule
     */
    form_addModule  *faddModule;
    /**
     * @brief module_name
     */
    QString         module_name;

    /**
     * @brief Address_Module
     */
    QString         Address_Module;
    /**
     * @brief NoSeri
     */
    QString         NoSeri;
    /**
     * @brief mod
     */
    module          mod;
    /**
     * @brief Serial_Com
     */
    QSerialPort     *Serial_Com;
    /**
     * @brief progress_dialog
     */
    ProgressDialog  *progress_dialog;
//    QLabel          *type[16];

    /**
     * @brief Main
     */
    MainWindow      *Main;
    /**
     * @brief Serial
     */
    serial          *Serial;
    /**
     * @brief Setting
     */
    setting         *Setting;

    /**
     * @brief Message
     */
    QString Message;
    /**
     * @brief Request
     */
    QString Request;
    /**
     * @brief indx
     */
    int indx;
    /**
     * @brief diff
     */
    int diff;
    /**
     * @brief reset
     */
    int reset;
    /**
     * @brief timeout
     */
    bool timeout;
    /**
     * @brief type
     */
    QString type;
    /**
     * @brief tmp
     */
    QString tmp;
    /**
     * @brief tmp2
     */
    QString tmp2;
    /**
     * @brief str
     */
    QString str;
    /**
     * @brief str2
     */
    QString str2;
    /**
     * @brief list
     */
    QStringList list;
    /**
     * @brief list2
     */
    QStringList list2;
    /**
     * @brief fail
     */
    bool fail;
    /**
     * @brief cancel
     */
    bool cancel;

    /**
     * @brief setInterface
     * @param address
     */
    void setInterface(QString address);
    /**
     * @brief setInterface_Input
     * @param address
     */
    void setInterface_Input(QString address);
    /**
     * @brief setInterface_Output
     * @param address
     */
    void setInterface_Output(QString address);
    /**
     * @brief setInterface_Communication
     * @param address
     */
    void setInterface_Communication(QString address);
    /**
     * @brief setInterface_Environment
     * @param address
     */
    void setInterface_Environment(QString address);
    /**
     * @brief setInterface_Sumber
     * @param address
     */
    void setInterface_Sumber(QString address);
    /**
     * @brief setInterface_Formula
     * @param address
     */
    void setInterface_Formula(QString address);
    /**
     * @brief setInterface_Alarm
     * @param address
     */
    void setInterface_Alarm(QString address);
    /**
     * @brief setInterface_Data_Settings
     * @param address
     */
    void setInterface_Data_Settings(QString address);
    /**
     * @brief setInterface_Data_Monitoring
     * @param address
     */
    void setInterface_Data_Monitoring(QString address);
    /**
     * @brief setInterface_System_Monitoring
     * @param address
     */
    void setInterface_System_Monitoring(QString address);
    /**
     * @brief EnableButton
     * @param enab
     */
    void EnableButton(bool enab);

    //** Input Tab **//
    /**
     * @brief check_input
     */
    QCheckBox       *check_input[PIN_ANALOG + PIN_DIGITAL];
    /**
     * @brief name_input
     */
    QLineEdit       *name_input[PIN_ANALOG + PIN_DIGITAL];
    /**
     * @brief type_input
     */
    QComboBox       *type_input[PIN_ANALOG + PIN_DIGITAL];
    /**
     * @brief state_input
     */
    QComboBox       *state_input[PIN_ANALOG + PIN_DIGITAL];
    /**
     * @brief calib_m
     */
    QDoubleSpinBox  *calib_m[PIN_ANALOG + PIN_DIGITAL];
    /**
     * @brief calib_x
     */
    QDoubleSpinBox  *calib_x[PIN_ANALOG + PIN_DIGITAL];
    /**
     * @brief reg_input
     */
    QComboBox       *reg_input[PIN_ANALOG + PIN_DIGITAL];
    /**
     * @brief SigMapReg_input
     */
    QSignalMapper   *SigMapReg_input;
    /**
     * @brief SigMapState_input
     */
    QSignalMapper   *SigMapState_input;

    //** Output Tab **//
    /**
     * @brief check_output
     */
    QCheckBox       *check_output[PIN_OUTPUT];
    /**
     * @brief name_output
     */
    QLineEdit       *name_output[PIN_OUTPUT];
    /**
     * @brief type_output
     */
    QLineEdit       *type_output[PIN_OUTPUT];
    /**
     * @brief state_output
     */
    QComboBox       *state_output[PIN_OUTPUT];
    /**
     * @brief control
     */
    QComboBox       *control[PIN_OUTPUT];
    /**
     * @brief reg_output
     */
    QSpinBox        *reg_output[PIN_OUTPUT];

    //** Sources Tab **//
    /**
     * @brief check_source
     */
    QCheckBox       *check_source[JML_SOURCE];
    /**
     * @brief delete_source
     */
    QPushButton     *delete_source[JML_SOURCE];
    /**
     * @brief SigMapDel_Source
     */
    QSignalMapper   *SigMapDel_Source;
    /**
     * @brief name_source
     */
    QLineEdit       *name_source[JML_SOURCE];
    /**
     * @brief ip_source
     */
    QLineEdit       *ip_source[JML_SOURCE];
    /**
     * @brief port_source
     */
    QSpinBox        *port_source[JML_SOURCE];
    /**
     * @brief state_source
     */
    QComboBox       *state_source[JML_SOURCE];
    /**
     * @brief type_source
     */
    QComboBox       *type_source[JML_SOURCE];
    /**
     * @brief id_source
     */
    QSpinBox        *id_source[JML_SOURCE];
    /**
     * @brief sensor_reg_source
     */
    QSpinBox        *sensor_reg_source[JML_SOURCE];
//    /**
//     * @brief OffsetBase_source
//     */
//    QComboBox       *OffsetBase_source[JML_SOURCE];
    /**
     * @brief command_source
     */
    QComboBox       *command_source[JML_SOURCE];
    /**
     * @brief length_source
     */
    QComboBox       *length_source[JML_SOURCE];
    /**
     * @brief SigMap_length_source
     */
    QSignalMapper   *SigMap_length_source;
    /**
     * @brief target_reg_source
     */
    QComboBox       *target_reg_source[JML_SOURCE];
    /**
     * @brief SigMap_tReg_source
     */
    QSignalMapper   *SigMap_tReg_source;
    /**
     * @brief target_reg_source
     */
    QComboBox       *swap_source[JML_SOURCE];
    /**
     * @brief target_reg_source
     */
    QComboBox       *data_type_source[JML_SOURCE];
    /**
     * @brief target_reg_source
     */
    QComboBox       *data_bits_source[JML_SOURCE];
    /**
     * @brief checkFormula
     * @param data
     * @return
     */
    bool checkFormula(QString data);

    //** Formula Tab **//
    /**
     * @brief check_formula
     */
    QCheckBox       *check_formula[JML_FORMULA];
    /**
     * @brief delete_formula
     */
    QPushButton     *delete_formula[JML_FORMULA];
    /**
     * @brief SigMapDel_Formula
     */
    QSignalMapper   *SigMapDel_Formula;
    /**
     * @brief name_formula
     */
    QLineEdit       *name_formula[JML_FORMULA];
    /**
     * @brief type_formula
     */
    QComboBox       *type_formula[JML_FORMULA];
    /**
     * @brief hx_formula
     */
    QComboBox       *hx_formula[JML_FORMULA];
    /**
     * @brief pa_formula
     */
    QLineEdit       *pa_formula[JML_FORMULA];
    /**
     * @brief b_formula
     */
    QLineEdit       *b_formula[JML_FORMULA];
    /**
     * @brief q_formula
     */
    QComboBox       *q_formula[JML_FORMULA];
    /**
     * @brief v_formula
     */
    QComboBox       *v_formula[JML_FORMULA];
    /**
     * @brief m_formula
     */
    QDoubleSpinBox  *m_formula[JML_FORMULA];
    /**
     * @brief c_formula
     */
    QDoubleSpinBox  *c_formula[JML_FORMULA];
    /**
     * @brief status_formula
     */
    QComboBox       *state_formula[JML_FORMULA];
    /**
     * @brief checkParameter
     * @param data
     * @return
     */
    bool checkParameter(QString data);


    //** Alarm Threshold Tab **//
    /**
     * @brief check_alarm
     */
    QCheckBox       *check_alarm[16];
    /**
     * @brief delete_alarm
     */
    QPushButton     *delete_alarm[16];
    /**
     * @brief SigMapDel_alarm
     */
    QSignalMapper   *SigMapDel_alarm;
    /**
     * @brief name_alarm
     */
    QLineEdit       *name_alarm[16];
    /**
     * @brief state_alarm
     */
    QComboBox       *state_alarm[16];
    /**
     * @brief input_alarm
     */
    QComboBox       *input_alarm[16];
    /**
     * @brief SigMapInput_alarm
     */
    QSignalMapper   *SigMapInput_alarm;
    /**
     * @brief output_alarm
     */
    QComboBox       *output_alarm[16];
    /**
     * @brief range_l
     */
    QLineEdit       *range_l[16];
    /**
     * @brief batas_ll
     */
    QLineEdit       *batas_ll[16];
    /**
     * @brief batas_l
     */
    QLineEdit       *batas_l[16];
    /**
     * @brief batas_h
     */
    QLineEdit       *batas_h[16];
    /**
     * @brief batas_hh
     */
    QLineEdit       *batas_hh[16];
    /**
     * @brief range_h
     */
    QLineEdit       *range_h[16];

    //** Data Settings **//
    /**
     * @brief check_data_s
     */
    QCheckBox       *check_data_s[JML_DATA];
    /**
     * @brief id_data_s
     */
    QSpinBox        *id_data_s[JML_DATA];
    /**
     * @brief name_data_s
     */
    QLineEdit       *name_data_s[JML_DATA];

//    QDoubleSpinBox  *value_data_s[JML_DATA];
    /**
     * @brief unit_data_s
     */
    QLineEdit       *unit_data_s[JML_DATA];
    /**
     * @brief range_l_data_s
     */
    QDoubleSpinBox  *range_l_data_s[JML_DATA];
    /**
     * @brief border_ll_data_s
     */
    QDoubleSpinBox  *border_ll_data_s[JML_DATA];
    /**
     * @brief border_l_data_s
     */
    QDoubleSpinBox  *border_l_data_s[JML_DATA];
    /**
     * @brief border_h_data_s
     */
    QDoubleSpinBox  *border_h_data_s[JML_DATA];
    /**
     * @brief border_hh_data_s
     */
    QDoubleSpinBox  *border_hh_data_s[JML_DATA];
    /**
     * @brief range_h_data_s
     */
    QDoubleSpinBox  *range_h_data_s[JML_DATA];
    /**
     * @brief state_data_s
     */
    QComboBox       *state_data_s[JML_DATA];
    /**
     * @brief sdCard_data
     */
    QCheckBox       *sdCard_data_s[JML_DATA];
    /**
     * @brief SigMapState_data_s
     */
    QSignalMapper   *SigMapState_data_s;

    //** Data Monitoring **//
    /**
     * @brief reg_data
     */
    QLabel          *reg_data[JML_DATA];
    /**
     * @brief name_data
     */
    QLabel          *name_data[JML_DATA];
    /**
     * @brief value_data
     */
    QLabel          *value_data[JML_DATA];
    /**
     * @brief unit_data
     */
    QLabel          *unit_data[JML_DATA];

    /**
     * @brief data_monitoring
     */
    void data_monitoring();
    /**
     * @brief system_monitoring
     */
    void system_monitoring();
};

#endif // FORMMODULE_H
