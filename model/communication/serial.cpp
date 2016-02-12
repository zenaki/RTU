#include "serial.h"

serial::serial()
{
//    serialFunct = new serial(this);

}

void serial::open_serial(QWidget *parent, struct t_serial_settings *tSerial, bool serial_set, bool serial_connect)
{
    settings_dialog = SettingsDialog(parent, tSerial);
    settings_dialog->setWindowTitle("Serial Communication Setting");
    settings_dialog->setModal(true);
    settings_dialog->exec();

    if (!serial_set) return;

    SerialPort->setPortName(tSerial->name);
    SerialPort->setBaudRate(tSerial->baudRate);
    SerialPort->setDataBits(tSerial->dataBits);
    SerialPort->setParity(tSerial->parity);
    SerialPort->setStopBits(tSerial->stopBits);
    SerialPort->setFlowControl(tSerial->flowControl);
    if (SerialPort->open(QIODevice::ReadWrite)) {
//        this->ui->bottom_message->setStyleSheet("QLabel { color : blue; }");
//        StatusMessage = QString("Connected to ") +
//                        SettingsDialogForm->currentSettings.name +
//                        QString(", BR = ") +
//                        SettingsDialogForm->currentSettings.stringBaudRate +
//                        QString(", DB = ") +
//                        SettingsDialogForm->currentSettings.stringDataBits +
//                        QString(", PR = ") +
//                        SettingsDialogForm->currentSettings.stringParity +
//                        QString(", SB = ") +
//                        SettingsDialogForm->currentSettings.stringStopBits +
//                        QString(", FC = ") +
//                        SettingsDialogForm->currentSettings.stringFlowControl;
//        this->ui->bottom_message->setText(StatusMessage);
        serial_connect = true;
    } else {
//        QMessageBox::critical(this, tr("Error"), serial->errorString());
//        this->ui->bottom_message->setStyleSheet("QLabel { color : red; }");
//        this->ui->bottom_message->setText("Connecting Fail");
//        if (SerialPort->isOpen())
//            SerialPort->close();
        serial_connect = false;
    }
//    if (!serial_connect)
//    {
//        this->close_serial();
//    } else
//    {
//        serial.writeData("\r\n");
//        serial.writeData("cek_env\r\n");
//        serial.writeData("set_env nama ganti_nama\r\n");
//        serial.writeData("cek_env\r\n");
////        serial.close_serial(tSerial, serial_set, serial_connect);
//    }

}

void serial::close_serial(bool serial_connect)
{
    if (SerialPort->isOpen())
        SerialPort->close();
    if (serial_connect)
    {
        serial_connect = false;
//        this->ui->bottom_message->setStyleSheet("QLabel { color : black; }");
//        this->ui->bottom_message->setText("Disconnect");
    }
}

void serial::write_data(const QByteArray &data)
{
    SerialPort->write(data);
}

void serial::read_data(QString str_data, QStringList val_data)
{
    str_data.append(SerialPort->readAll());
    if (str_data.indexOf("(x)") > 0)
    {
        str_data.remove("\r").remove("\n").remove("(x)");
        val_data.append(str_data.split(";"));
        qDebug() << str_data;
        str_data.clear();
    }
    val_data.clear();
}

//void serial::handleError(QSerialPort::SerialPortError error)
//{
//    if (error == QSerialPort::ResourceError) {
//        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
//        serial.close_serial();
//    }
//}
