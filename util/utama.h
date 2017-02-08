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
#define PIN_DIGITAL          6
#define PIN_ANALOG           6
#define PIN_OUTPUT           2

#define DELAY_MS             50
#define TIMEOUT              5000 //ms
#define STR_TIMEOUT          "Time Out !! \r\nPlease try again .."

#define PATH_SERIAL_SETTING  ".RTUdata/config/serial_setting.cfg"
#define PATH_SERIAL_PARSING  ".RTUdata/config/serial_parsing.cfg"
#define PATH_PLUGIN_CONFIG   ".RTUdata/plugin/plugin.cfg"
#define PATH_USER_ACCESS     ".RTUdata/config/usr.cfg"
#define PATH_LOG             ".RTUdata/log.txt"

#define WAIT_WRITE           10 //ms

#define MODE_GET_ENV         "0000"
#define MODE_GET_SIM         "0001"
#define MODE_GET_I0          "0002"
#define MODE_GET_SRC         "0004"
#define MODE_GET_DAT         "0005"

#define MODE_SET_ENV         "0100"
#define MODE_SET_SIM         "0101"
#define MODE_SET_KNL         "0102"
#define MODE_SET_RLY         "0103"
#define MODE_SET_SRC         "0104"
#define MODE_SET_DAT         "0105"

#define DEFAULT_USERNAME     "admin"
#define DEFAULT_PASSWORD     "Sarasvati2015"

//** STRUCT **//
/**
 * @brief The data_port struct
 */
struct data_port {
    /**
     * @brief nama_input
     */
    char nama_input[64];
    /**
     * @brief type_input
     */
    int type_input;
    /**
     * @brief status_input
     */
    int status_input;
    /**
     * @brief calib_m
     */
    float calib_m;
    /**
     * @brief calib_x
     */
    float calib_x;

    /**
     * @brief nama_output
     */
    char nama_output[64];
    /**
     * @brief type_output
     */
    char type_output[32];
    /**
     * @brief status_output
     */
    int status_output;
    /**
     * @brief control
     */
    int control;
    /**
     * @brief reg_output
     */
    int reg_output;
};
/**
 * @brief The t_module struct
 */
struct t_module {
    /**
     * @brief flag_active
     */
    int  flag_active;
    /**
     * @brief module_name
     */
    char module_name[32];
    /**
     * @brief serial_number
     */
    char serial_number[32];

    /**
     * @brief ip_address
     */
    char ip_address[32];
    /**
     * @brief server_address
     */
    char server_address[32];
    /**
     * @brief file_address
     */
    char file_address[32];
    /**
     * @brief flag_webclient
     */
    int  flag_webclient;
    /**
     * @brief status_webclient
     */
    char status_webclient[32];
    /**
     * @brief interval_relay
     */
    int  interval_relay;
    /**
     * @brief interval_data
     */
    int  interval_data;
    /**
     * @brief flag_mode_http
     */
    int  flag_mode_http;
    /**
     * @brief mode_http
     */
    char mode_http[32];
    /**
     * @brief port
     */
    int  port;
    /**
     * @brief utc
     */
    int  utc;

    /**
     * @brief flag_dual_gsm
     */
    int  flag_dual_gsm;
    /**
     * @brief last_signal
     */
    int  last_signal;

    /**
     * @brief flag_gsm_1
     */
    int  flag_gsm_1;
    /**
     * @brief name_gsm_1
     */
    char name_gsm_1[32];
    /**
     * @brief device_name_gsm_1
     */
    char device_name_gsm_1[64];
    /**
     * @brief flag_status_active_gsm_1
     */
    int  flag_status_active_gsm_1;
    /**
     * @brief status_gsm_1
     */
    char status_gsm_1[32];
    /**
     * @brief flag_com_gsm_1
     */
    int  flag_com_gsm_1;
    /**
     * @brief com_gsm_1
     */
    char com_gsm_1[32];
    /**
     * @brief number_gsm_1
     */
    char number_gsm_1[16];
    /**
     * @brief user_gsm_1
     */
    char user_gsm_1[16];
    /**
     * @brief passwd_gsm_1
     */
    char passwd_gsm_1[16];
    /**
     * @brief apn_gsm_1
     */
    char apn_gsm_1[16];

    /**
     * @brief flag_gsm_2
     */
    int  flag_gsm_2;
    /**
     * @brief name_gsm_2
     */
    char name_gsm_2[32];
    /**
     * @brief device_name_gsm_2
     */
    char device_name_gsm_2[64];
    /**
     * @brief flag_status_active_gsm_2
     */
    int  flag_status_active_gsm_2;
    /**
     * @brief status_gsm_2
     */
    char status_gsm_2[32];
    /**
     * @brief flag_com_gsm_2
     */
    int  flag_com_gsm_2;
    /**
     * @brief com_gsm_2
     */
    char com_gsm_2[32];
    /**
     * @brief number_gsm_2
     */
    char number_gsm_2[16];
    /**
     * @brief user_gsm_2
     */
    char user_gsm_2[16];
    /**
     * @brief passwd_gsm_2
     */
    char passwd_gsm_2[16];
    /**
     * @brief apn_gsm_2
     */
    char apn_gsm_2[16];

    /**
     * @brief d_port
     */
    struct data_port d_port[16];

    /**
     * @brief Input
     */
    QStringList Input;
    /**
     * @brief InputName
     */
    QStringList InputName;
    /**
     * @brief jml_input_digital
     */
    int  jml_input_digital;
    /**
     * @brief jml_input_analog
     */
    int  jml_input_analog;
    /**
     * @brief Output
     */
    QStringList Output;
    /**
     * @brief OutputName
     */
    QStringList OutputName;
    /**
     * @brief jml_output
     */
    int  jml_output;

    /**
     * @brief sumber
     */
    QStringList sumber;
    /**
     * @brief jml_sumber
     */
    int  jml_sumber;
    /**
     * @brief alarm
     */
    QStringList alarm;
    /**
     * @brief jml_alarm
     */
    int  jml_alarm;
    /**
     * @brief data
     */
    QStringList data;
    /**
     * @brief jml_data
     */
    int  jml_data;
};
/**
 * @brief The t_serial_settings struct
 */
struct t_serial_settings {
    /**
     * @brief name
     */
    QString name;
    /**
     * @brief baudRate
     */
    qint32 baudRate;
    /**
     * @brief stringBaudRate
     */
    QString stringBaudRate;
    /**
     * @brief dataBits
     */
    QSerialPort::DataBits dataBits;
    /**
     * @brief stringDataBits
     */
    QString stringDataBits;
    /**
     * @brief parity
     */
    QSerialPort::Parity parity;
    /**
     * @brief stringParity
     */
    QString stringParity;
    /**
     * @brief stopBits
     */
    QSerialPort::StopBits stopBits;
    /**
     * @brief stringStopBits
     */
    QString stringStopBits;
    /**
     * @brief flowControl
     */
    QSerialPort::FlowControl flowControl;
    /**
     * @brief stringFlowControl
     */
    QString stringFlowControl;

    /**
     * @brief str_data_env
     */
    QString str_data_env;
    /**
     * @brief str_data_io
     */
    QString str_data_io;
    /**
     * @brief str_data_sim
     */
    QString str_data_sim;
    /**
     * @brief str_data_src
     */
    QString str_data_src;
    /**
     * @brief str_data_dat
     */
    QString str_data_dat;
};

#include "model/debug.h"

#endif // UTAMA

