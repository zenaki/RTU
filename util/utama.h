#ifndef UTAMA
#define UTAMA


/** CLASS **/
#include "model/module.h"


/** INCLUDE LIB **/
#include <string>
#include <string.h>
#include <strings.h>

#include <QList>
#include <QWidget>
#include <QAction>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QSignalMapper>

#include <QTreeView>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>

#include <QMessageBox>
#include <QMessageLogger>

#include <QSettings>
#include <QStringList>

#include <QtSerialPort/QSerialPort>

/** DEFINE LIB **/
#define  MAX_MODULE    256



/** STRUCT **/

struct data_port{
    char nama_input[64];
    int type_input;
    int status_input;
    float calib_m;
    float calib_x;

    char nama_output[64];
    char type_output[32];
    int status_output;
    int control;
};

struct t_module{
    int flag_active;
    char module_name[32];
    char serial_number[32];

    int  flag_dual_gsm;

    int  flag_gsm_1;
    char name_gsm_1[32];
    char device_name_gsm_1[64];
    int  flag_status_active_gsm_1;
    char status_gsm_1[32];
    int  flag_com_gsm_1;
    char com_gsm_1[32];
    char number_gsm_1[16];
    char user_gsm_1[16];
    char apn_gsm_1[16];

    int  flag_gsm_2;
    char name_gsm_2[32];
    char device_name_gsm_2[64];
    int  flag_status_active_gsm_2;
    char status_gsm_2[32];
    int  flag_com_gsm_2;
    char com_gsm_2[32];
    char number_gsm_2[16];
    char user_gsm_2[16];
    char apn_gsm_2[16];

    struct data_port d_port[16];

    char input_a1[128];
    char input_a1_name[32];
    char input_a2[128];
    char input_a2_name[32];
    char input_a3[128];
    char input_a3_name[32];
    char input_a4[128];
    char input_a4_name[32];
    char input_a5[128];
    char input_a5_name[32];
    char input_a6[128];
    char input_a6_name[32];

    char input_d1[128];
    char input_d1_name[32];
    char input_d2[128];
    char input_d2_name[32];
    char input_d3[128];
    char input_d3_name[32];
    char input_d4[128];
    char input_d4_name[32];
    char input_d5[128];
    char input_d5_name[32];
    char input_d6[128];
    char input_d6_name[32];
    char input_d7[128];
    char input_d7_name[32];
    char input_d8[128];
    char input_d8_name[32];

    char output_r1[128];
    char output_r1_name[32];
    char output_r2[128];
    char output_r2_name[32];
    char output_r3[128];
    char output_r3_name[32];
    char output_r4[128];
    char output_r4_name[32];
};

struct t_serial_settings {
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
};

#include "model/debug.h"

#endif // UTAMA

