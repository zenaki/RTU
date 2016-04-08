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
    pth = "data/config/serial_parsing";
    QSettings sett(pth, QSettings::IniFormat);
    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_ENV", tSerial->str_data_env);
}

void serial::write_parsing_io(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = "data/config/serial_parsing";
    QSettings sett(pth, QSettings::IniFormat);
    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_IO", tSerial->str_data_io);
}

void serial::write_parsing_sim(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = "data/config/serial_parsing";
    QSettings sett(pth, QSettings::IniFormat);
    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_SIM", tSerial->str_data_sim);
}

void serial::write_parsing_src(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = "data/config/serial_parsing";
    QSettings sett(pth, QSettings::IniFormat);
    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_SRC", tSerial->str_data_src);
}

void serial::write_parsing_dat(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = "data/config/serial_parsing";
    QSettings sett(pth, QSettings::IniFormat);
    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_DAT", tSerial->str_data_dat);
}

void serial::read_parsing(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = "data/config/serial_parsing";
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);
    sett.setIniCodec(CODEC);
    QByteArray decode;

    tSerial->str_data_env = sett.value("STR_DATA_ENV").toString();
    tSerial->str_data_io = sett.value("STR_DATA_IO").toString();
    tSerial->str_data_sim = sett.value("STR_DATA_SIM").toString();
    tSerial->str_data_src = sett.value("STR_DATA_SRC").toString();
    tSerial->str_data_dat = sett.value("STR_DATA_DAT").toString();

    code.encryp(pth);
}
