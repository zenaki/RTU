#include "debugdialog.h"
#include "ui_debugdialog.h"

DebugDialog::DebugDialog(QWidget *parent, QString command1, QString command2, int delay_ms) :
    QDialog(parent),
    ui(new Ui::DebugDialog)
{
    ui->setupUi(this);

    delay_write = delay_ms;
    start_command = command1;
    stop_command = command2;

    SerialPort = new QSerialPort(this);
    connect(SerialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(SerialPort, SIGNAL(error(QSerialPort::SerialPortError)), this,SLOT(handleError(QSerialPort::SerialPortError)));
    this->connect_serial();

    if (SerialPort->isOpen()) {
        QString tmp;
        start_command.remove("\r\n");
        for (int i = 0; i < start_command.length(); i++) {
            tmp = QChar(start_command.at(i));
            SerialPort->write(tmp.toUtf8().data());
            delay(delay_write);
        }
        SerialPort->write("\r\n");
    } else {
        QMessageBox::critical(this, tr("Critical Error"), "Please check your connection ..!!!");
        this->close();
    }
}

DebugDialog::~DebugDialog()
{
    if (SerialPort->isOpen()) {
        QString tmp;
        stop_command.remove("\r\n");
        for (int i = 0; i < stop_command.length(); i++) {
            tmp = QChar(stop_command.at(i));
            SerialPort->write(tmp.toUtf8().data());
            delay(delay_write);
        }
        SerialPort->write("\r\n");
        SerialPort->close();
    }
    delete ui;
}

void DebugDialog::readData()
{
    this->ui->pte_debug->appendPlainText(SerialPort->readAll());
}

void DebugDialog::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), "Please check your connection ..!!!");
        this->close();
    }
}

void DebugDialog::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void DebugDialog::connect_serial() {
    struct t_serial_settings tSerial;
    serial Serial;
    setting Setting;

    Setting.read_setting(&tSerial);
    if (!SerialPort->isOpen()) Serial.open_serial(SerialPort, &tSerial);
    SerialPort->open(QIODevice::ReadWrite);
}

void DebugDialog::close_window() {
    if (SerialPort->isOpen()) {
        QString tmp;
        stop_command.remove("\r\n");
        for (int i = 0; i < stop_command.length(); i++) {
            tmp = QChar(stop_command.at(i));
            SerialPort->write(tmp.toUtf8().data());
            delay(delay_write);
        }
        SerialPort->write("\r\n");
        SerialPort->close();
    }
    this->close();
}
