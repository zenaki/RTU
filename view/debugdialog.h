#ifndef DEBUGDIALOG_H
#define DEBUGDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QTime>

#include "model/communication/serial.h"
#include "model/setting.h"

namespace Ui {
class DebugDialog;
}

class DebugDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief DebugDialog
     * @param parent
     * @param command1
     * @param command2
     * @param delay
     */
    explicit DebugDialog(QWidget *parent = 0, QString command1 = 0, QString command2 = 0, int delay = 0);
    ~DebugDialog();

    /**
     * @brief close_window
     */
    void close_window();
private:
    /**
     * @brief ui
     */
    Ui::DebugDialog *ui;

    /**
     * @brief SerialPort
     */
    QSerialPort *SerialPort;
    /**
     * @brief delay
     * @param ms
     */
    void delay(int ms);
    /**
     * @brief connect_serial
     */
    void connect_serial();

    /**
     * @brief delay_write
     */
    int delay_write;
    /**
     * @brief start_command
     */
    QString start_command;
    /**
     * @brief stop_command
     */
    QString stop_command;
private slots:
    /**
     * @brief readData
     */
    void readData();
    /**
     * @brief handleError
     * @param error
     */
    void handleError(QSerialPort::SerialPortError error);
};

#endif // DEBUGDIALOG_H
