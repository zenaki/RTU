#include "setting.h"

setting::setting()
{

}

void setting::write_setting(SettingsDialog *s_d, struct t_serial_settings *tSerial){
    tSerial->name = s_d->ui->serialPortInfoListBox->currentText();

    if (s_d->ui->baudRateBox->currentIndex() == 4) {
        tSerial->baudRate = s_d->ui->baudRateBox->currentText().toInt();
    } else {
        tSerial->baudRate = static_cast<QSerialPort::BaudRate>(
                    s_d->ui->baudRateBox->itemData(s_d->ui->baudRateBox->currentIndex()).toInt());
    }
    tSerial->stringBaudRate = QString::number(tSerial->baudRate);

    tSerial->dataBits = static_cast<QSerialPort::DataBits>(
                s_d->ui->dataBitsBox->itemData(s_d->ui->dataBitsBox->currentIndex()).toInt());
    tSerial->stringDataBits = s_d->ui->dataBitsBox->currentText();

    tSerial->parity = static_cast<QSerialPort::Parity>(
                s_d->ui->parityBox->itemData(s_d->ui->parityBox->currentIndex()).toInt());
    tSerial->stringParity = s_d->ui->parityBox->currentText();

    tSerial->stopBits = static_cast<QSerialPort::StopBits>(
                s_d->ui->stopBitsBox->itemData(s_d->ui->stopBitsBox->currentIndex()).toInt());
    tSerial->stringStopBits = s_d->ui->stopBitsBox->currentText();

    tSerial->flowControl = static_cast<QSerialPort::FlowControl>(
                s_d->ui->flowControlBox->itemData(s_d->ui->flowControlBox->currentIndex()).toInt());
    tSerial->stringFlowControl = s_d->ui->flowControlBox->currentText();

    QString pth;
    pth = PATH_SERIAL_SETTING;
    cryp code; code.decryp(PATH_SERIAL_SETTING);
    QSettings sett(pth, QSettings::IniFormat);

    sett.beginGroup( "SERIAL_CONFIGURATION" );
    sett.setValue("NAME", tSerial->name);
    sett.setValue("BAUDRATE", tSerial->baudRate);
    sett.setValue("STR_BAUDRATE", tSerial->stringBaudRate);
    sett.setValue("DATA_BITS", tSerial->dataBits);
    sett.setValue("STR_DATA_BITS", tSerial->stringDataBits);
    sett.setValue("PARITY", tSerial->parity);
    sett.setValue("STR_PARITY", tSerial->stringParity);
    sett.setValue("STOP_BITS", tSerial->stopBits);
    sett.setValue("STR_STOP_BITS", tSerial->stringStopBits);
    sett.setValue("FLOW_CONTROL", tSerial->flowControl);
    sett.setValue("STR_FLOW_CONTROL", tSerial->stringFlowControl);
    sett.endGroup();

    code.encryp(PATH_SERIAL_SETTING);
}

void setting::read_setting(t_serial_settings *tSerial)
{
    QString pth;
    pth = PATH_SERIAL_SETTING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);
    QString val;

    tSerial->name = sett.value("SERIAL_CONFIGURATION/NAME").toString().toUtf8();
    tSerial->baudRate = sett.value("SERIAL_CONFIGURATION/BAUDRATE", 0).toInt();
    tSerial->stringBaudRate = sett.value("SERIAL_CONFIGURATION/STR_BAUDRATE", "").toString().toUtf8();

    val = sett.value("SERIAL_CONFIGURATION/DATA_BITS").toString();
    if (val == "8") { tSerial->dataBits = static_cast<QSerialPort::DataBits>(QSerialPort::Data8); }
    else if (val == "7") { tSerial->dataBits = static_cast<QSerialPort::DataBits>(QSerialPort::Data7); }
    else if (val == "6") { tSerial->dataBits = static_cast<QSerialPort::DataBits>(QSerialPort::Data6); }
    else if (val == "5") { tSerial->dataBits = static_cast<QSerialPort::DataBits>(QSerialPort::Data5); }
    tSerial->stringDataBits = sett.value("SERIAL_CONFIGURATION/STR_DATA_BITS").toString();

    val = sett.value("SERIAL_CONFIGURATION/PARITY").toString();
    if (val == "0") { tSerial->parity = static_cast<QSerialPort::Parity>(QSerialPort::NoParity); }
    else if (val == "2") { tSerial->parity = static_cast<QSerialPort::Parity>(QSerialPort::EvenParity); }
    else if (val == "3") { tSerial->parity = static_cast<QSerialPort::Parity>(QSerialPort::OddParity); }
    else if (val == "5") { tSerial->parity = static_cast<QSerialPort::Parity>(QSerialPort::MarkParity); }
    else if (val == "4") { tSerial->parity = static_cast<QSerialPort::Parity>(QSerialPort::SpaceParity); }
    tSerial->stringParity = sett.value("SERIAL_CONFIGURATION/STR_PARITY").toString();

    val = sett.value("SERIAL_CONFIGURATION/STOP_BITS").toString();
    if (val == "1") { tSerial->stopBits = static_cast<QSerialPort::StopBits>(QSerialPort::OneStop); }
    else { tSerial->stopBits = static_cast<QSerialPort::StopBits>(QSerialPort::TwoStop); }
    tSerial->stringStopBits = sett.value("SERIAL_CONFIGURATION/STR_STOP_BITS").toString();

    val = sett.value("SERIAL_CONFIGURATION/FLOW_CONTROL").toString();
    if (val == "0") { tSerial->flowControl = static_cast<QSerialPort::FlowControl>(QSerialPort::NoFlowControl); }
    else if (val == "1") { tSerial->flowControl = static_cast<QSerialPort::FlowControl>(QSerialPort::HardwareControl); }
    else if (val == "2") { tSerial->flowControl = static_cast<QSerialPort::FlowControl>(QSerialPort::SoftwareControl); }
    tSerial->stringFlowControl = sett.value("SERIAL_CONFIGURATION/STR_FLOW_CONTROL").toString();
    sett.endGroup();

    code.encryp(pth);
}

bool setting::checkSetting(){
    bool cek = false;
    QDir path("data/config");
    QStringList files = path.entryList(QDir::Files);

    QString currFiles = "serial_setting.cfg";

    for(int i = 0; i < files.count(); i++){
        if(currFiles == QString(files.at(i))) cek = true;
    }

    return cek;
}
