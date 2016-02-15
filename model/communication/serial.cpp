#include "serial.h"

serial::serial()
{
//    serialFunct = new serial(this);
//    connect(SerialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));

}

void serial::open_serial(QSerialPort *SerialPort, struct t_serial_settings *tSerial)
{
    SerialPort->setPortName(tSerial->name);
    SerialPort->setBaudRate(tSerial->baudRate);
    SerialPort->setDataBits(tSerial->dataBits);
    SerialPort->setParity(tSerial->parity);
    SerialPort->setStopBits(tSerial->stopBits);
    SerialPort->setFlowControl(tSerial->flowControl);
}

void serial::close_serial()
{
//    if (SerialPort->isOpen())
//        SerialPort->close();
//    if (serial_connect)
//    {
//        serial_connect = 0;
//        this->ui->bottom_message->setStyleSheet("QLabel { color : black; }");
//        this->ui->bottom_message->setText("Disconnect");
//    }
}

void serial::write_data(QSerialPort *port, QString data)
{
    port->write(data.toUtf8().data());
    //SerialPort->write(data);
}

void serial::read_data(QString str_data, QStringList val_data)
{
//    str_data.append(SerialPort->readAll());
//    if (str_data.indexOf("(x)") > 0)
//    {
//        str_data.remove("\r").remove("\n").remove("(x)");
//        val_data.append(str_data.split(";"));
//        qDebug() << str_data;
//        str_data.clear();
//    }
//    val_data.clear();
}

//void serial::handleError(QSerialPort::SerialPortError error)
//{
//    if (error == QSerialPort::ResourceError) {
//        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
//        serial.close_serial();
//    }
//}
