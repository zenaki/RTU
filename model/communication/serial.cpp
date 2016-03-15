#include "serial.h"

serial::serial()
{

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

void serial::close_serial(QSerialPort *SerialPort)
{
    if (SerialPort->isOpen())
        SerialPort->close();
}

void serial::write_data(QSerialPort *port, QString data)
{
    port->write(data.toUtf8().data());
}

void serial::write_parsing_env(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = "data/config/serial_parsing.ini";
    QSettings sett(pth, QSettings::IniFormat);

    sett.setValue("STR_DATA_ENV", tSerial->str_data_env);
}

void serial::write_parsing_io(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = "data/config/serial_parsing.ini";
    QSettings sett(pth, QSettings::IniFormat);

    sett.setValue("STR_DATA_IO", tSerial->str_data_io);
}

void serial::write_parsing_sim(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = "data/config/serial_parsing.ini";
    QSettings sett(pth, QSettings::IniFormat);

    sett.setValue("STR_DATA_SIM", tSerial->str_data_sim);
}

void serial::read_parsing(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = "data/config/serial_parsing.ini";
    QSettings sett(pth, QSettings::IniFormat);

    tSerial->str_data_env = sett.value("STR_DATA_ENV").toString();
    tSerial->str_data_io = sett.value("STR_DATA_IO").toString();
    tSerial->str_data_sim = sett.value("STR_DATA_SIM").toString();
}
