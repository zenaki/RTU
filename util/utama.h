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
#include <QDebug>

#include <QSettings>
#include <QStringList>
#include <QChar>
#include "string.h"

#include <QtSerialPort/QSerialPort>

/** DEFINE LIB **/
#define  MAX_MODULE          256

#define Analog_Monita        250
#define Analog_Running_Hours 230
#define RPM                  1
#define ON_OFF               2
//#define PUSH_BUTTON          3
#define FLOW_X               6
#define RPM_RH               7
//#define RUNNING_HOURS        8
#define ON_OFF_RH            9

#define DATA_PERIOD          10

#define DELAY_MS             50
#define TIMEOUT              5000 //ms
#define STR_TIMEOUT          "Time Out !! \r\nPlease try again .."

#define CODEC                "UTF-8"
//#define DECODEC              "UTF-8"

#define PATH_SERIAL_SETTING  "data/config/serial_setting.cfg"
#define PATH_SERIAL_PARSING  "data/config/serial_parsing.cfg"
#define PATH_PLUGIN_CONFIG   "plugin/plugin.cfg"
#define PATH_USER_ACCESS     "data/config/usr.cfg"

#define WAIT_WRITE           1 //ms

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
    int  flag_active;
    char module_name[32];
    char serial_number[32];

    char ip_address[32];
    char server_address[32];
    char file_address[32];
    int  flag_webclient;
    char status_webclient[32];

    int  flag_dual_gsm;
    int  last_signal;

    int  flag_gsm_1;
    char name_gsm_1[32];
    char device_name_gsm_1[64];
    int  flag_status_active_gsm_1;
    char status_gsm_1[32];
    int  flag_com_gsm_1;
    char com_gsm_1[32];
    char number_gsm_1[16];
    char user_gsm_1[16];
    char passwd_gsm_1[16];
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
    char passwd_gsm_2[16];
    char apn_gsm_2[16];

    struct data_port d_port[16];

    QStringList Input;
    QStringList InputName;
    int  jml_input_digital;
    int  jml_input_analog;
    QStringList Output;
    QStringList OutputName;
    int  jml_output;

    QStringList sumber;
    int  jml_sumber;
    QStringList alarm;
    int  jml_alarm;
    QStringList data;
    int  jml_data;
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

    QString str_data_env;
    QString str_data_io;
    QString str_data_sim;
    QString str_data_src;
    QString str_data_dat;
};

struct t_plugin {
    QStringList PluginName;
    QStringList PluginExec;
    int jml_plugin;
};

#include "model/debug.h"

#endif // UTAMA

