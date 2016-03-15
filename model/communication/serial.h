#ifndef SERIAL_H
#define SERIAL_H

#include "util/utama.h"
#include "view/settingsdialog.h"

#include <QMessageBox>
#include <QObject>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SettingsDialog;

class serial
{
public:
    serial();

//    int serial_set;
//    int serial_connect;
//    QString str_data;
//    QStringList val_data;

    void open_serial(QSerialPort *SerialPort, struct t_serial_settings *tSerial);
    void close_serial(QSerialPort *SerialPort);
    void write_data(QSerialPort *port, QString data);

    void write_parsing_env(struct t_serial_settings *tSerial);
    void write_parsing_io(struct t_serial_settings *tSerial);
    void write_parsing_sim(struct t_serial_settings *tSerial);

    void read_parsing(struct t_serial_settings *tSerial);

public slots:
    void read_data(QString str_data, QStringList val_data);
    void handleError(QSerialPort::SerialPortError error);

};

#endif // SERIAL_H
