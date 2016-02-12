#ifndef SERIAL_H
#define SERIAL_H

#include "util/utama.h"
#include "view/settingsdialog.h"

#include <QMessageBox>
#include <QDebug>
#include <QtSerialPort/QSerialPort>

class SettingsDialog;

class serial
{
public:
    serial();

    QSerialPort *SerialPort;
    bool serial_set;
    bool serial_connect;
    QString str_data;
    QStringList val_data;

    SettingsDialog *settings_dialog;

    void open_serial(QWidget *parent, struct t_serial_settings *tSerial, bool serial_set, bool serial_connect);
    void close_serial(bool serial_connect);
    void write_data(const QByteArray &data);

public slots:
    void read_data(QString str_data, QStringList val_data);
    void handleError(QSerialPort::SerialPortError error);
};

#endif // SERIAL_H
