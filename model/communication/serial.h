#ifndef SERIAL_H
#define SERIAL_H

#include "util/utama.h"
#include "view/settingsdialog.h"

#include <QMessageBox>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SettingsDialog;

/**
 * @brief The serial class
 */
class serial
{
public:
    /**
     * @brief serial
     */
    serial();

//    int serial_set;
//    int serial_connect;
//    QString str_data;
//    QStringList val_data;

    /**
     * @brief open_serial
     * @param SerialPort
     * @param tSerial
     */
    void open_serial(QSerialPort *SerialPort, struct t_serial_settings *tSerial);
    /**
     * @brief close_serial
     * @param SerialPort
     */
    void close_serial(QSerialPort *SerialPort);
    /**
     * @brief write_data
     * @param port
     * @param data
     */
    void write_data(QSerialPort *port, QByteArray data);

    /**
     * @brief write_parsing_env
     * @param tSerial
     */
    void write_parsing_env(struct t_serial_settings *tSerial);
    /**
     * @brief write_parsing_io
     * @param tSerial
     */
    void write_parsing_io(struct t_serial_settings *tSerial);
    /**
     * @brief write_parsing_sim
     * @param tSerial
     */
    void write_parsing_sim(struct t_serial_settings *tSerial);
    /**
     * @brief write_parsing_src
     * @param tSerial
     */
    void write_parsing_src(struct t_serial_settings *tSerial);
    /**
     * @brief write_parsing_frm
     * @param tSerial
     */
    void write_parsing_frm(struct t_serial_settings *tSerial);
    /**
     * @brief write_parsing_dat
     * @param tSerial
     */
    void write_parsing_dat(struct t_serial_settings *tSerial);
    /**
     * @brief write_parsing_sys
     * @param tSerial
     */
    void write_parsing_sys(struct t_serial_settings *tSerial);

    /**
     * @brief read_parsing
     * @param tSerial
     */
    void read_parsing(struct t_serial_settings *tSerial);

public slots:
    /**
     * @brief read_data
     * @param str_data
     * @param val_data
     */
    void read_data(QString str_data, QStringList val_data);
//    void handleError(QSerialPort::SerialPortError error);

//private slots:
//    void handleBytesWritten(qint64 bytes);
//    void handleTimeout();
//    void handleError(QSerialPort::SerialPortError error);

private:
    /**
     * @brief m_writeData
     */
    QByteArray      m_writeData;
    /**
     * @brief m_standardOutput
     */
    QTextStream     m_standardOutput;
    /**
     * @brief m_bytesWritten
     */
    qint64          m_bytesWritten;
    /**
     * @brief m_timer
     */
    QTimer          m_timer;

};

#endif // SERIAL_H
