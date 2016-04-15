#include "serial.h"

serial::serial()
{
//    connect(&m_timer, SIGNAL(timeout()), SLOT(handleTimeout()));
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

void serial::write_data(QSerialPort *port, QByteArray data)
{
//    port->write(data.toUtf8().data());

    m_writeData = data;
    qint64 bytesWritten = port->write(data);

    if (bytesWritten == -1) {
//        m_standardOutput << QObject::tr("Failed to write the data to port %1, error: %2").arg(port->portName()).arg(port->errorString()) << endl;
//        QCoreApplication::exit(1);
        return;
    } else if (bytesWritten != m_writeData.size()) {
//        m_standardOutput << QObject::tr("Failed to write all the data to port %1, error: %2").arg(port->portName()).arg(port->errorString()) << endl;
//        QCoreApplication::exit(1);
        return;
    }

    m_timer.start(10);
}

//void serial::handleBytesWritten(qint64 bytes)
//{
//    m_bytesWritten += bytes;
//    if (m_bytesWritten == m_writeData.size()) {
//        m_bytesWritten = 0;
////        m_standardOutput << QObject::tr("Data successfully sent to port %1").arg(m_serialPort->portName()) << endl;
////        QCoreApplication::quit();
//        return;
//    }
//}

//void serial::handleTimeout()
//{
////    m_standardOutput << QObject::tr("Operation timed out for port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
////    QCoreApplication::exit(1);
//    return;
//}

//void serial::handleError(QSerialPort::SerialPortError serialPortError)
//{
//    if (serialPortError == QSerialPort::WriteError) {
////        m_standardOutput << QObject::tr("An I/O error occurred while writing the data to port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
////        QCoreApplication::exit(1);
//        return;
//    }
//}

void serial::write_parsing_env(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    QSettings sett(pth, QSettings::IniFormat);
//    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_ENV", tSerial->str_data_env);
}

void serial::write_parsing_io(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    QSettings sett(pth, QSettings::IniFormat);
//    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_IO", tSerial->str_data_io);
}

void serial::write_parsing_sim(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    QSettings sett(pth, QSettings::IniFormat);
//    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_SIM", tSerial->str_data_sim);
}

void serial::write_parsing_src(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    QSettings sett(pth, QSettings::IniFormat);
//    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_SRC", tSerial->str_data_src);
}

void serial::write_parsing_dat(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    QSettings sett(pth, QSettings::IniFormat);
//    sett.setIniCodec(CODEC);

    sett.setValue("STR_DATA_DAT", tSerial->str_data_dat);
}

void serial::read_parsing(struct t_serial_settings *tSerial)
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);
//    sett.setIniCodec(CODEC);
    QByteArray decode;

    tSerial->str_data_env = sett.value("STR_DATA_ENV").toString();
    tSerial->str_data_io = sett.value("STR_DATA_IO").toString();
    tSerial->str_data_sim = sett.value("STR_DATA_SIM").toString();
    tSerial->str_data_src = sett.value("STR_DATA_SRC").toString();
    tSerial->str_data_dat = sett.value("STR_DATA_DAT").toString();

    code.encryp(pth);
}
