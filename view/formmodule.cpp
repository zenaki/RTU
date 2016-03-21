#include "formmodule.h"
#include "ui_formmodule.h"

#include <QDebug>
#include <QtGui>

formModule::formModule(QWidget *parent, QString address, QSerialPort *SerialPort, QLightBoxWidget *LightBox) :
    QDialog(parent),
    ui(new Ui::formModule)
{
    ui->setupUi(this);
    this->ui->tabWidget->setCurrentIndex(0);

    Address_Module = address;
    struct t_module tModule;
    module mod;
    mod.read_module(&tModule, Address_Module);
    NoSeri.sprintf("%s", tModule.serial_number);

    Serial_Com = new QSerialPort(this);
    Serial_Com = SerialPort;

    Main = new MainWindow(this);
    Serial = new serial();
    Setting = new setting();

    busyForm = new QLightBoxWidget(this);
    busyForm = LightBox;

    this->setInterface(address);
    this->ui->pbEdit->setHidden(true);
    this->ui->pbAddRow->setHidden(true);
    this->ui->pbDeleteRows->setHidden(true);

    this->ui->pbSet->setText("Set Input Settings");
    this->ui->pbGet->setText("Get Input Settings");
}

formModule::~formModule()
{
    delete ui;
}

void formModule::setInterface(QString address)
{
    this->setInterface_Input(address);
    this->setInterface_Output(address);
    this->setInterface_Communication(address);
    this->setInterface_Environtment(address);
    this->setInterface_Sumber(address);
    this->setInterface_Alarm(address);
    this->setInterface_Data(address);
}

void formModule::setInterface_Input(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    int rowInputDigital = tModule.jml_input_digital;
    int rowInputAnalog = tModule.jml_input_analog;
    QString type;

    this->ui->tabel_input->verticalHeader()->setHidden(true);
    this->ui->tabel_input->setColumnCount(7);
//    this->ui->tabel_input->setColumnWidth(0, 50);
    this->ui->tabel_input->setColumnWidth(1, 100);
    this->ui->tabel_input->setColumnWidth(2, 150);
//    this->ui->tabel_input->setColumnWidth(3, 100);
//    this->ui->tabel_input->setColumnWidth(4, 100);
//    this->ui->tabel_input->setColumnWidth(5, 100);
    this->ui->tabel_input->setColumnWidth(6, 100);
    this->ui->tabel_input->setRowCount(rowInputDigital + rowInputAnalog);

    for (int i = 0; i < rowInputDigital + rowInputAnalog; i++){
        name_input[i] = new QLineEdit(this);

        type_input[i] = new QComboBox(this);
        if (i >= rowInputDigital) {
            type_input[i]->addItem("Analog Monita",250);
            type_input[i]->addItem("Analog Running Hours",230);
        } else
        {
            type_input[i]->addItem("RPM",1);
            type_input[i]->addItem("ON / OFF",2);
//            type_input[i]->addItem("Push Button",3);
            type_input[i]->addItem("Flow - X",6);
            type_input[i]->addItem("RPM - RH",7);
//            type_input[i]->addItem("Running Hours",8);
            type_input[i]->addItem("ON / OFF - RH",9);
        }

        calib_m[i] = new QLineEdit(this);
        calib_m[i]->setAlignment(Qt::AlignRight);

        calib_x[i] = new QLineEdit(this);
        calib_x[i]->setAlignment(Qt::AlignRight);

        reg_input[i] = new QLineEdit(this);
        reg_input[i]->setAlignment(Qt::AlignCenter);
        reg_input[i]->setEnabled(false);

        state_input[i] = new QComboBox(this);
        state_input[i]->addItem("NOT ACTIVE",0);
        state_input[i]->addItem("ACTIVE",1);
    }

    QString str;
    QString tmp;
    QStringList list;
    for (int i = 0; i < tModule.Input.length(); i++) {
        str.append(tModule.InputName.at(i)).append(";").append(tModule.Input.at(i)).append(";");
        tmp = tModule.data.at(i); list = tmp.split(';');
        str.append(list.at(1)).append(";").append(list.at(11)).append(";");
    }

    list = str.split(';');

    for(int i = 0; i < rowInputDigital + rowInputAnalog; i++){
        if (i >= rowInputDigital) {
            type = " - Analog";
        } else {
            type = " - Digital";
        }

        type.prepend(QString::number(i+1));

        name_input[i]->setText(list[i*8]);
        int indx;
        if (list[(i*8)+3].toInt() == 250) {indx = 0;}
        if (list[(i*8)+3].toInt() == 230) {indx = 1;}
        if (list[(i*8)+3].toInt() == 1) {indx = 0;}
        if (list[(i*8)+3].toInt() == 2) {indx = 1;}
        if (list[(i*8)+3].toInt() == 6) {indx = 2;}
        if (list[(i*8)+3].toInt() == 7) {indx = 3;}
        if (list[(i*8)+3].toInt() == 9) {indx = 4;}
        type_input[i]->setCurrentIndex(indx);
        calib_m[i]->setText(list[(i*8)+4]);
        calib_x[i]->setText(list[(i*8)+5]);
        reg_input[i]->setText(list[(i*8)+6]);
        state_input[i]->setCurrentIndex(list[(i*8)+7].toInt());

        this->ui->tabel_input->setItem(i,0, new QTableWidgetItem(type));
        this->ui->tabel_input->setCellWidget(i,1, name_input[i]);
        this->ui->tabel_input->setCellWidget(i,2, type_input[i]);
        this->ui->tabel_input->setCellWidget(i,3, calib_m[i]);
        this->ui->tabel_input->setCellWidget(i,4, calib_x[i]);
        this->ui->tabel_input->setCellWidget(i,5, reg_input[i]);
        this->ui->tabel_input->setCellWidget(i,6, state_input[i]);
    }

    this->ui->tabel_input->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void formModule::setInterface_Output(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    int rowOutput = tModule.jml_output;
    QString type;

    this->ui->tabel_output->verticalHeader()->setHidden(true);
    this->ui->tabel_output->setColumnCount(4);
    //    this->ui->tabel_output->setColumnWidth(0, 50);
        this->ui->tabel_output->setColumnWidth(1, 100);
        this->ui->tabel_output->setColumnWidth(2, 100);
    //    this->ui->tabel_output->setColumnWidth(3, 100);
    this->ui->tabel_output->setRowCount(rowOutput);

    for (int i = 0; i < rowOutput; i++){
        name_output[i] = new QLineEdit(this);

        state_output[i] = new QComboBox(this);
        state_output[i]->addItem("NOT ACTIVE");
        state_output[i]->addItem("ACTIVE");

        control[i] = new QComboBox(this);
        control[i]->addItem("LOGIC");
        control[i]->addItem("LATCH");
        control[i]->addItem("SCHEDULER");
    }

    QString str;
    QString tmp;
    QStringList list;
    for (int i = 0; i < tModule.Output.length(); i++) {
        str.append(tModule.OutputName.at(i)).append(";")
                .append(tModule.Output.at(i)).append(";");
    }
    list = str.split(';');

    for(int i = 0; i < rowOutput; i++){
        name_output[i]->setText(list[i*5]);
        state_output[i]->setCurrentIndex(list[(i*5)+3].toInt());
        control[i]->setCurrentIndex(list[(i*5)+4].toInt());

        type = " - Relay";
        type.prepend(QString::number(i+1));
        this->ui->tabel_output->setItem(i,0, new QTableWidgetItem(type));
        this->ui->tabel_output->setCellWidget(i,1, name_output[i]);
        this->ui->tabel_output->setCellWidget(i,2, state_output[i]);
        this->ui->tabel_output->setCellWidget(i,3, control[i]);
    }

    this->ui->tabel_output->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void formModule::setInterface_Communication(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    modules.sprintf("%s", tModule.name_gsm_1);
    this->ui->opt_1->setText(modules);
    modules.sprintf("%s", tModule.name_gsm_2);
    this->ui->opt_2->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_1);
    this->ui->device_1->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_2);
    this->ui->device_2->setText(modules);
    modules.sprintf("%s", tModule.status_gsm_1);
    this->ui->status_1->setText(modules);
    modules.sprintf("%s", tModule.status_gsm_2);
    this->ui->status_2->setText(modules);
    modules.sprintf("%s", tModule.com_gsm_1);
    this->ui->com_1->setText(modules);
    modules.sprintf("%s", tModule.com_gsm_2);
    this->ui->com_2->setText(modules);
    modules.sprintf("%s", tModule.number_gsm_1);
    this->ui->number_1->setText(modules);
    modules.sprintf("%s", tModule.number_gsm_2);
    this->ui->number_2->setText(modules);

    modules.sprintf("%s", tModule.user_gsm_1);
    this->ui->user_1->setText(modules);
    modules.sprintf("%s", tModule.apn_gsm_1);
    this->ui->apn_1->setText(modules);
    modules.sprintf("%s", tModule.passwd_gsm_1);
    this->ui->passwd_1->setText(modules);

    modules.sprintf("%s", tModule.user_gsm_2);
    this->ui->user_2->setText(modules);
    modules.sprintf("%s", tModule.apn_gsm_2);
    this->ui->apn_2->setText(modules);
    modules.sprintf("%s", tModule.passwd_gsm_2);
    this->ui->passwd_2->setText(modules);
}

void formModule::setInterface_Environtment(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    modules.sprintf("%s", tModule.module_name);
    this->ui->module_name->setText(modules);
    modules.sprintf("%s", tModule.serial_number);
    this->ui->serial_number->setText(modules);

    modules.sprintf("%s", tModule.ip_address);
    this->ui->ip_address->setText(modules);
    modules.sprintf("%s", tModule.server_address);
    this->ui->server_address->setText(modules);
    modules.sprintf("%s", tModule.file_address);
    this->ui->file_address->setText(modules);
    modules.sprintf("%s", tModule.status_webclient);
    this->ui->web_client->setText(modules);
}

void formModule::setInterface_Sumber(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    int rowSource = tModule.jml_sumber;
    QString type;
    cb_header_source = new MyHeader(Qt::Horizontal, this->ui->tabel_sources);
    this->ui->tabel_sources->setHorizontalHeader(cb_header_source);

    this->ui->tabel_sources->verticalHeader()->setHidden(true);
    this->ui->tabel_sources->setColumnCount(14);
    this->ui->tabel_sources->setColumnWidth(0, 25);
//    this->ui->tabel_sources->setHorizontalHeaderItem(0, cb_header_source);
    this->ui->tabel_sources->setColumnWidth(1, 25);
//    this->ui->tabel_sources->setColumnWidth(2, 75);
    this->ui->tabel_sources->setColumnWidth(3, 100);
    this->ui->tabel_sources->setColumnWidth(4, 100);
//    this->ui->tabel_sources->setColumnWidth(5, 75);
    this->ui->tabel_sources->setColumnWidth(6, 100);
//    this->ui->tabel_sources->setColumnWidth(7, 75);
    this->ui->tabel_sources->setColumnWidth(8, 50);
    this->ui->tabel_sources->setColumnWidth(9, 85);
    this->ui->tabel_sources->setColumnWidth(10, 85);
    this->ui->tabel_sources->setColumnWidth(11, 150);
//    this->ui->tabel_sources->setColumnWidth(12, 75);
    this->ui->tabel_sources->setColumnWidth(13, 85);
    this->ui->tabel_sources->setRowCount(rowSource);

    SigMapDel_Source = new QSignalMapper(this);
    for (int i = 0; i < rowSource; i++){
        check_source[i] = new QCheckBox(this);
        delete_source[i] = new QPushButton("Del", this);
        SigMapDel_Source->setMapping(delete_source[i], i);
        connect(delete_source[i],SIGNAL(clicked()),SigMapDel_Source,SLOT(map()));

        name_source[i] = new QLineEdit(this);

        ip_source[i] = new QLineEdit(this);
        ip_source[i]->setAlignment(Qt::AlignCenter);

        port_source[i] = new QLineEdit(this);
        port_source[i]->setAlignment(Qt::AlignCenter);

        state_source[i] = new QComboBox(this);
        state_source[i]->addItem("NOT ACTIVE",0);
        state_source[i]->addItem("ACTIVE",1);

        type_source[i] = new QComboBox(this);
        type_source[i]->addItem("Native",1);
        type_source[i]->addItem("PM810",2);
        type_source[i]->addItem("Santer",3);
        type_source[i]->addItem("GWR",4);
        type_source[i]->addItem("PM5560",5);

        id_source[i] = new QLineEdit(this);
        id_source[i]->setAlignment(Qt::AlignCenter);

        sensor_reg_source[i] = new QLineEdit(this);
        sensor_reg_source[i]->setAlignment(Qt::AlignCenter);

        OffsetBase_source[i] = new QComboBox(this);
        OffsetBase_source[i]->addItem("0",0);
        OffsetBase_source[i]->addItem("1",1);

        command_source[i] = new QComboBox(this);
        command_source[i]->addItem("Read Holding Register",0);
        command_source[i]->addItem("Write Holding Register",1);

        length_source[i] = new QLineEdit(this);
        length_source[i]->setAlignment(Qt::AlignCenter);

        target_reg_source[i] = new QLineEdit(this);
        target_reg_source[i]->setAlignment(Qt::AlignCenter);
    }
    connect(SigMapDel_Source,SIGNAL(mapped(int)),this,SLOT(del_src_clicked(int)));

    QString str;
    QString tmp;
    QStringList list;

    for (int i = 0; i < rowSource; i++){
        type = "Source - ";
        type.append(QString::number(i+1));

        if (i <= tModule.sumber.length()) {
            if (this->checkFormula(tModule.sumber.at(i))) {
                str = tModule.sumber.at(i);
                list = str.split(';');
                name_source[i]->setText(list[1]);
                ip_source[i]->setText(list[2]);
                port_source[i]->setText(list[3]);
                state_source[i]->setCurrentIndex(list[4].toInt());
                type_source[i]->setCurrentIndex(list[5].toInt());
                id_source[i]->setText(list[6]);
                sensor_reg_source[i]->setText(list[7]);
                OffsetBase_source[i]->setCurrentIndex(list[8].toInt());
                command_source[i]->setCurrentIndex(list[9].toInt());
                length_source[i]->setText(list[10]);
                target_reg_source[i]->setText(list[11]);
            } else {
                str = tModule.sumber.at(i);
                list = str.split(';');
                name_source[i]->setText(list[1]);
                ip_source[i]->setText(list[2]);
                port_source[i]->setText(list[3]);
                state_source[i]->setCurrentIndex(list[4].toInt());
            }
        }

        this->ui->tabel_sources->setCellWidget(i,0, check_source[i]);
        this->ui->tabel_sources->setCellWidget(i,1, delete_source[i]);
        this->ui->tabel_sources->setItem(i,2, new QTableWidgetItem(type));
        this->ui->tabel_sources->setCellWidget(i,3, name_source[i]);
        this->ui->tabel_sources->setCellWidget(i,4, ip_source[i]);
        this->ui->tabel_sources->setCellWidget(i,5, port_source[i]);
        this->ui->tabel_sources->setCellWidget(i,6, state_source[i]);
        this->ui->tabel_sources->setCellWidget(i,7, type_source[i]);
        this->ui->tabel_sources->setCellWidget(i,8, id_source[i]);
        this->ui->tabel_sources->setCellWidget(i,9, sensor_reg_source[i]);
        this->ui->tabel_sources->setCellWidget(i,10, OffsetBase_source[i]);
        this->ui->tabel_sources->setCellWidget(i,11, command_source[i]);
        this->ui->tabel_sources->setCellWidget(i,12, length_source[i]);
        this->ui->tabel_sources->setCellWidget(i,13, target_reg_source[i]);
    }

    this->ui->tabel_sources->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void formModule::setInterface_Alarm(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    int rowAlarm = tModule.jml_alarm;
    QString type;

    this->ui->tabel_alarm->verticalHeader()->setHidden(true);
    this->ui->tabel_alarm->setColumnCount(13);
    this->ui->tabel_alarm->setColumnWidth(0, 25);
    this->ui->tabel_alarm->setColumnWidth(1, 25);
//    this->ui->tabel_alarm->setColumnWidth(2, 75);
    this->ui->tabel_alarm->setColumnWidth(3, 100);
//    this->ui->tabel_alarm->setColumnWidth(4, 75);
//    this->ui->tabel_alarm->setColumnWidth(5, 75);
    this->ui->tabel_alarm->setColumnWidth(6, 100);
//    this->ui->tabel_alarm->setColumnWidth(7, 50);
//    this->ui->tabel_alarm->setColumnWidth(8, 75);
//    this->ui->tabel_alarm->setColumnWidth(9, 75);
//    this->ui->tabel_alarm->setColumnWidth(10, 75);
//    this->ui->tabel_alarm->setColumnWidth(11, 75);
//    this->ui->tabel_alarm->setColumnWidth(12, 75);
    this->ui->tabel_alarm->setRowCount(rowAlarm);

    SigMapDel_Alarm = new QSignalMapper(this);
    for (int i = 0; i < rowAlarm; i++){
        check_alarm[i] = new QCheckBox(this);
        delete_alarm[i] = new QPushButton("Del", this);
        SigMapDel_Alarm->setMapping(delete_alarm[i], i);
        connect(delete_alarm[i],SIGNAL(clicked()),SigMapDel_Alarm,SLOT(map()));

        name_alarm[i] = new QLineEdit(this);

        state_alarm[i] = new QComboBox(this);
        state_alarm[i]->addItem("NOT ACTIVE",0);
        state_alarm[i]->addItem("ACTIVE",1);

        input_reg_alarm[i] = new QLineEdit(this);
        input_reg_alarm[i]->setAlignment(Qt::AlignCenter);

        output_reg_alarm[i] = new QLineEdit(this);
        output_reg_alarm[i]->setAlignment(Qt::AlignCenter);

        range_l[i] = new QLineEdit(this);
        range_l[i]->setAlignment(Qt::AlignCenter);

        batas_ll[i] = new QLineEdit(this);
        batas_ll[i]->setAlignment(Qt::AlignCenter);

        batas_l[i] = new QLineEdit(this);
        batas_l[i]->setAlignment(Qt::AlignCenter);

        batas_h[i] = new QLineEdit(this);
        batas_h[i]->setAlignment(Qt::AlignCenter);

        batas_hh[i] = new QLineEdit(this);
        batas_hh[i]->setAlignment(Qt::AlignCenter);

        range_h[i] = new QLineEdit(this);
        range_h[i]->setAlignment(Qt::AlignCenter);
    }
    connect(SigMapDel_Alarm,SIGNAL(mapped(int)),this,SLOT(del_alrm_clicked(int)));

    QString str;
    QString tmp;
    QStringList list;

    for (int i = 0; i < rowAlarm; i++){
        type = "Alarm - ";
        type.append(QString::number(i+1));

        if (i <= tModule.alarm.length()) {
            str = tModule.alarm.at(i);
            list = str.split(';');
            name_alarm[i]->setText(list[1]);
            input_reg_alarm[i]->setText(list[2]);
            output_reg_alarm[i]->setText(list[3]);
            state_alarm[i]->setCurrentIndex(list[4].toInt());
            range_l[i]->setText(list[5]);
            batas_ll[i]->setText(list[6]);
            batas_l[i]->setText(list[7]);
            batas_h[i]->setText(list[8]);
            batas_hh[i]->setText(list[9]);
            range_h[i]->setText(list[10]);
        }

        this->ui->tabel_alarm->setCellWidget(i,0, check_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,1, delete_alarm[i]);
        this->ui->tabel_alarm->setItem(i,2, new QTableWidgetItem(type));
        this->ui->tabel_alarm->setCellWidget(i,3, name_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,4, input_reg_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,5, output_reg_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,6, state_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,7, range_l[i]);
        this->ui->tabel_alarm->setCellWidget(i,8, batas_ll[i]);
        this->ui->tabel_alarm->setCellWidget(i,9, batas_l[i]);
        this->ui->tabel_alarm->setCellWidget(i,10, batas_h[i]);
        this->ui->tabel_alarm->setCellWidget(i,11, batas_hh[i]);
        this->ui->tabel_alarm->setCellWidget(i,12, range_h[i]);
    }

    this->ui->tabel_alarm->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void formModule::setInterface_Data(QString address)
{

}

bool formModule::checkFormula(QString data)
{
    QStringList list = data.split(';');
    if (list.length() > 6) {
        return true;
    } else {
        return false;
    }
}

void formModule::on_pbSetAll_clicked()
{
    struct t_module tModule;
    QString data[12];
    QString Message;
    QString Request;
    int indx;
    int diff = 0;
    int reset = 0;
    bool timeout = false;
    QStringList list;

    module mod;
    mod.read_module(&tModule, Address_Module);

    /** ON MODULE FILE **/
    for (int i = 0; i < ui->tabel_input->rowCount(); i++)
    {
//        tModule.d_port[i].status_input = state_input[i]->currentIndex();
        tModule.d_port[i].calib_m = calib_m[i]->text().toFloat();
        tModule.d_port[i].calib_x = calib_x[i]->text().toFloat();

        if (i >= 6) {
            if (type_input[i]->currentIndex() == 0) {indx = 250;}
            if (type_input[i]->currentIndex() == 1) {indx = 230;}
            tModule.d_port[i].type_input = indx;

            data[i].sprintf("A;%d;%d;%.3f;%.3f", i-6+11
                            , indx
                            , tModule.d_port[i].calib_m
                            , tModule.d_port[i].calib_x);
        } else {
            if (type_input[i]->currentIndex() == 0) {indx = 1;}
            if (type_input[i]->currentIndex() == 1) {indx = 2;}
            if (type_input[i]->currentIndex() == 2) {indx = 6;}
            if (type_input[i]->currentIndex() == 3) {indx = 7;}
            if (type_input[i]->currentIndex() == 4) {indx = 9;}
            tModule.d_port[i].type_input = indx;

            data[i].sprintf("D;%d;%d;%.3f;%.3f", i+1
                            , indx
                            , tModule.d_port[i].calib_m
                            , tModule.d_port[i].calib_x);
        }
        tModule.Input[i] = data[i];
        tModule.InputName[i] = name_input[i]->text();

        data[i] = tModule.data.at(i);
        list = data[i].split(';');
        list[2] = name_input[i]->text();
        data[i].clear();
        data[i] = list[0];
        for (int j = 1; j < 12; j++) {
            data[i].append(";").append(list[j]);
        }
        tModule.data[i] = data[i];
    }

    for (int i = 0; i < ui->tabel_output->rowCount(); i++)
    {
        tModule.d_port[i].status_output = state_output[i]->currentIndex();
        tModule.d_port[i].control = control[i]->currentIndex();

        data[i].sprintf("R;%d;%d;%d", i+1
                     , tModule.d_port[i].status_output
                     , tModule.d_port[i].control) ;

        tModule.Output[i] = data[i];
        tModule.OutputName[i] = name_output[i]->text();
    }

    for (int i = 0; i < ui->tabel_sources->rowCount(); i++) {
        data[i] = QString::number(i+1) + ";" +
                  name_source[i]->text() + ";" +
                  ip_source[i]->text() + ";" +
                  port_source[i]->text() + ";" +
                  QString::number(state_source[i]->currentIndex()) + ";" +
                  QString::number(type_source[i]->currentIndex()) + ";" +
                  id_source[i]->text() + ";" +
                  sensor_reg_source[i]->text() + ";" +
                  QString::number(OffsetBase_source[i]->currentIndex()) + ";" +
                  QString::number(command_source[i]->currentIndex()) + ";" +
                  length_source[i]->text() + ";" +
                  target_reg_source[i]->text();

        tModule.sumber[i] = data[i];
    }

    mod.write_module(&tModule);

    /** ON BOARD **/
    if (Serial_Com->isOpen()) {
        this->EnableButton(false);

        struct t_serial_settings tSerial;
        QStringList val_data;

        timeout = work->Request_ENV(this, busyForm, Serial_Com, timeout);
        if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;}

        Serial->read_parsing(&tSerial);
        val_data = tSerial.str_data_env.split(";");
        if (NoSeri == val_data.at(1)) {
            this->writeLogFile();
            timeout = work->Set_Input(this, busyForm, Serial_Com, &tModule, timeout);
            if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
            timeout = work->Set_Output(this, busyForm, Serial_Com, &tModule, timeout);
            if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
            timeout = work->Set_SIM(this, busyForm, Serial_Com, &tModule, timeout);
            if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
            timeout = work->Set_Sumber(this, busyForm, Serial_Com, &tModule, timeout);
            if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
//            timeout = work->Set_Data(this, busyForm, Serial_Com, &tModule, timeout);
//            if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
//            work->Reset_Board(busyForm, "Reset Board ...", Serial_Com);

            Message = "On-Board";

        } else {
            Message = "On-Local";
            if (val_data.at(1) != "") {
                diff = 1;
            } else {
                diff = 2;
            }
        }
    } else {
        Message = "On-Local";
    }

    if (reset == 1) {
//        Request = "reset\r\n";
//        Serial->write_data(Serial_Com, Request);
//        work->delay(jeda*5);
    }

    if (diff == 0) {
        Message.prepend("Setting ").append(" Saved");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    } else if (diff == 1) {
        Message.prepend("Setting ").append(" Saved");
        Message.append("\n\n Different Serial Number !!!");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    } else if (diff == 2) {
        Message.prepend("Setting ").append(" Saved");
        Message.append("\nBoard is not have Serial Number ..");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    }
    this->EnableButton(true);
}

void formModule::on_pbSet_clicked()
{
    struct t_module tModule;
    QString data[12];
    QString Message;
    QString Request;
    int indx;
    int diff = 0;
    int reset = 0;
    bool timeout = false;
    QStringList list;

    module mod;
    mod.read_module(&tModule, Address_Module);

    /** ON MODULE FILE **/
    if (this->ui->tabWidget->currentIndex() == 0) {
        /** SET INPUT **/
        for (int i = 0; i < ui->tabel_input->rowCount(); i++)
        {
            tModule.d_port[i].calib_m = calib_m[i]->text().toFloat();
            tModule.d_port[i].calib_x = calib_x[i]->text().toFloat();

            if (i >= 6) {
                if (type_input[i]->currentIndex() == 0) {indx = 250;}
                if (type_input[i]->currentIndex() == 1) {indx = 230;}
                tModule.d_port[i].type_input = indx;

                data[i].sprintf("A;%d;%d;%.3f;%.3f", i-6+1
                                , indx
                                , tModule.d_port[i].calib_m
                                , tModule.d_port[i].calib_x);
            } else {
                if (type_input[i]->currentIndex() == 0) {indx = 1;}
                if (type_input[i]->currentIndex() == 1) {indx = 2;}
                if (type_input[i]->currentIndex() == 2) {indx = 6;}
                if (type_input[i]->currentIndex() == 3) {indx = 7;}
                if (type_input[i]->currentIndex() == 4) {indx = 9;}
                tModule.d_port[i].type_input = indx;

                data[i].sprintf("D;%d;%d;%.3f;%.3f", i+1
                                , indx
                                , tModule.d_port[i].calib_m
                                , tModule.d_port[i].calib_x);
            }
            tModule.Input[i] = data[i];
            tModule.InputName[i] = name_input[i]->text();

            data[i] = tModule.data.at(i);
            list = data[i].split(';');
            list[2] = name_input[i]->text();
            data[i].clear();
            data[i] = list[0];
            for (int j = 1; j < 12; j++) {
                data[i].append(";").append(list[j]);
            }
            tModule.data[i] = data[i];
        }
    } else if (this->ui->tabWidget->currentIndex() == 1) {
        /** SET OUTPUT **/
        for (int i = 0; i < ui->tabel_output->rowCount(); i++)
        {
            tModule.d_port[i].status_output = state_output[i]->currentIndex();
            tModule.d_port[i].control = control[i]->currentIndex();

            data[i].sprintf("R;%d;%d;%d", i+1
                         , tModule.d_port[i].status_output
                         , tModule.d_port[i].control);

            tModule.Output[i] = data[i];
            tModule.OutputName[i] = name_output[i]->text();
        }
    } else if (this->ui->tabWidget->currentIndex() == 4) {
        /** SET SUMBER **/
        for (int i = 0; i < ui->tabel_sources->rowCount(); i++) {
            data[i] = QString::number(i+1) + ";" +
                      name_source[i]->text() + ";" +
                      ip_source[i]->text() + ";" +
                      port_source[i]->text() + ";" +
                      QString::number(state_source[i]->currentIndex()) + ";" +
                      QString::number(type_source[i]->currentIndex()) + ";" +
                      id_source[i]->text() + ";" +
                      sensor_reg_source[i]->text() + ";" +
                      QString::number(OffsetBase_source[i]->currentIndex()) + ";" +
                      QString::number(command_source[i]->currentIndex()) + ";" +
                      length_source[i]->text() + ";" +
                      target_reg_source[i]->text();

            tModule.sumber[i] = data[i];
        }
    } else if (this->ui->tabWidget->currentIndex() == 5) {
        /** SET ALARM **/
        for (int i = 0; i < ui->tabel_alarm->rowCount(); i++) {

        }
    }

    mod.write_module(&tModule);

    /** ON BOARD **/
    if (Serial_Com->isOpen()) {
        this->EnableButton(false);

        struct t_serial_settings tSerial;
        QStringList val_data;

        timeout = work->Request_ENV(this, busyForm, Serial_Com, timeout);
        if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};

        Serial->read_parsing(&tSerial);
        val_data = tSerial.str_data_env.split(";");
        if (NoSeri == val_data.at(1)) {
            this->writeLogFile();
            if (this->ui->tabWidget->currentIndex() == 0) {
                timeout = work->Set_Input(this, busyForm, Serial_Com, &tModule, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
//                timeout = work->Set_Data(this, busyForm, Serial_Com, &tModule, timeout);
//                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
            } else if (this->ui->tabWidget->currentIndex() == 1) {
                timeout = work->Set_Output(this, busyForm, Serial_Com, &tModule, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
            } else if (this->ui->tabWidget->currentIndex() == 2) {
                timeout = work->Set_SIM(this, busyForm, Serial_Com, &tModule, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
            } else if (this->ui->tabWidget->currentIndex() == 3) {
                timeout = work->Set_ENV(this, busyForm, Serial_Com, &tModule, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
            } else if (this->ui->tabWidget->currentIndex() == 4) {
                timeout = work->Set_Sumber(this, busyForm, Serial_Com, &tModule, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
            } else if (this->ui->tabWidget->currentIndex() == 5) {
//                timeout = work->Set_Data(this, busyForm, Serial_Com, &tModule, timeout);
//                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
            }
//            work->Reset_Board(busyForm, "Reset Board ...", Serial_Com);

            Message = "On-Board";

        } else {
            Message = "On-Local";
            if (val_data.at(1) != "") {
                diff = 1;
            } else {
                diff = 2;
            }
        }
    } else {
        Message = "On-Local";
    }

    if (reset == 1) {
//        Request = "reset\r\n";
//        Serial->write_data(Serial_Com, Request);
//        work->delay(jeda*5);
    }

    if (diff == 0) {
        if (this->ui->tabWidget->currentIndex() == 0) {
            Message.prepend("Input Channel ");
        } else if (this->ui->tabWidget->currentIndex() == 1) {
            Message.prepend("Output Channel ");
        } else if (this->ui->tabWidget->currentIndex() == 2) {
            Message.prepend("SIM Configuration ");
        } else if (this->ui->tabWidget->currentIndex() == 3) {
            Message.prepend("Environtment ");
        } else if (this->ui->tabWidget->currentIndex() == 4) {
            Message.prepend("Sources ");
        } else if (this->ui->tabWidget->currentIndex() == 5) {
            Message.prepend("Alarm ");
        }
        Message.prepend("Setting ").append(" Saved");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    } else if (diff == 1) {
        Message.prepend("Setting ").append(" Saved");
        Message.append("\n\n Different Serial Number !!!");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    } else if (diff == 2) {
        Message.prepend("Setting ").append(" Saved");
        Message.append("\nBoard is not have Serial Number ..");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    }
    this->EnableButton(true);
}

void formModule::on_tabWidget_tabBarClicked(int index)
{
    if (index == 2 || index == 3) {
        this->ui->pbSet->setHidden(true);
        this->ui->pbGet->setHidden(true);
        this->ui->pbEdit->setHidden(false);
        this->ui->pbAddRow->setHidden(true);
        this->ui->pbDeleteRows->setHidden(true);
    } else {
        this->ui->pbSet->setHidden(false);
        this->ui->pbGet->setHidden(false);
        this->ui->pbEdit->setHidden(true);
        if (index == 4 || index == 5) {
            this->ui->pbAddRow->setHidden(false);
            this->ui->pbDeleteRows->setHidden(false);
        } else {
            this->ui->pbAddRow->setHidden(true);
            this->ui->pbDeleteRows->setHidden(true);
        }
    }

    this->ui->tabWidget->setCurrentIndex(index);

    struct t_module tModule;
    module mod;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    modules.sprintf("%s", tModule.module_name);
    this->ui->module_name->setText(modules);
    modules.sprintf("%s", tModule.serial_number);
    this->ui->serial_number->setText(modules);

    modules.sprintf("%s", tModule.name_gsm_1);
    this->ui->opt_1->setText(modules);
    modules.sprintf("%s", tModule.name_gsm_2);
    this->ui->opt_2->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_1);
    this->ui->device_1->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_2);
    this->ui->device_2->setText(modules);
    modules.sprintf("%s", tModule.status_gsm_1);
    this->ui->status_1->setText(modules);
    modules.sprintf("%s", tModule.status_gsm_2);
    this->ui->status_2->setText(modules);
    modules.sprintf("%s", tModule.com_gsm_1);
    this->ui->com_1->setText(modules);
    modules.sprintf("%s", tModule.com_gsm_2);
    this->ui->com_2->setText(modules);
    modules.sprintf("%s", tModule.number_gsm_1);
    this->ui->number_1->setText(modules);
    modules.sprintf("%s", tModule.number_gsm_2);
    this->ui->number_2->setText(modules);
    modules.sprintf("%s", tModule.user_gsm_1);
    this->ui->user_1->setText(modules);
    modules.sprintf("%s", tModule.user_gsm_2);
    this->ui->user_2->setText(modules);
    modules.sprintf("%s", tModule.apn_gsm_1);
    this->ui->apn_1->setText(modules);
    modules.sprintf("%s", tModule.apn_gsm_2);
    this->ui->apn_2->setText(modules);

    if (index == 0) {
        this->ui->pbSet->setText("Set Input Settings");
        this->ui->pbGet->setText("Get Input Settings");
    } else if (index == 1) {
        this->ui->pbSet->setText("Set Output Settings");
        this->ui->pbGet->setText("Get Output Settings");
    } else if (index == 2) {
        this->ui->pbEdit->setText("Edit Communication");
    } else if (index == 3) {
        this->ui->pbEdit->setText("Edit Environtment");
    } else if (index == 4) {
        this->ui->pbSet->setText("Set Sources Settings");
        this->ui->pbGet->setText("Get Sources Settings");
    } else if (index == 5) {
        this->ui->pbSet->setText("Set Alarm Settings");
        this->ui->pbGet->setText("Get Alarm Settings");
    } else if (index == 6) {
        this->ui->pbSet->setText("Set Data Settings");
        this->ui->pbGet->setText("Get Data Settings");
    }
}

void formModule::on_pbGetAll_clicked()
{
        struct t_module tModule;
        struct t_serial_settings tSerial;
        QStringList val_data;
        bool timeout = false;

        this->EnableButton(false);
        if (!Serial_Com->isOpen())
        {
            QMessageBox::warning(this, "Serial Comunication", "Protocol is not open ..!!", 0, 0);
            this->EnableButton(true);
        } else {
            timeout = work->Request_ENV(this, busyForm, Serial_Com, timeout);
            if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};

            Serial->read_parsing(&tSerial);
            val_data = tSerial.str_data_env.split(";");
            if (NoSeri == val_data.at(1)) {
                this->writeLogFile();
                module mod;
                mod.read_module(&tModule, Address_Module);

                timeout = work->Request_Data(this, busyForm, Serial_Com, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
                val_data = tSerial.str_data_dat.split("*");
                work->Get_Data(&tModule, val_data);

                timeout = work->Request_IO(this, busyForm, Serial_Com, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
                Serial->read_parsing(&tSerial);
                val_data = tSerial.str_data_io.split("*");
                work->Get_Input(&tModule, val_data);
                work->Get_Output(&tModule, val_data);

                timeout = work->Request_SIM(this, busyForm, Serial_Com, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
                val_data = tSerial.str_data_sim.split("*");
                work->Get_SIM(&tModule, val_data);

                timeout = work->Request_Sumber(this, busyForm, Serial_Com, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
                val_data = tSerial.str_data_src.split("*");
                work->Get_Sumber(&tModule, val_data);

                mod.write_module(&tModule);
                this->setInterface(Address_Module);

                QMessageBox::information(this, "Syncronization Board", "All Setting is Syncronized ..", 0, 0);
                this->EnableButton(true);
            } else {
                QMessageBox::warning(this, "Serial Comunication", "Serial Number is not syncronize ..!!", 0, 0);
                this->EnableButton(true);
            }
        }
}

void formModule::on_pbGet_clicked()
{
    struct t_module tModule;
    struct t_serial_settings tSerial;
    QStringList val_data;
    QString Message;
    bool timeout = false;

    this->EnableButton(false);
    if (!Serial_Com->isOpen())
    {
        QMessageBox::warning(this, "Serial Comunication", "Protocol is not open ..!!", 0, 0);
        this->EnableButton(true);
    } else {
        timeout = work->Request_ENV(this, busyForm, Serial_Com, timeout);
        if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};

        Serial->read_parsing(&tSerial);
        val_data = tSerial.str_data_env.split(";");
        if (NoSeri == val_data.at(1)) {
            this->writeLogFile();
            module mod;
            mod.read_module(&tModule, Address_Module);

            if (this->ui->tabWidget->currentIndex() <= 1) {
                timeout = work->Request_IO(this, busyForm, Serial_Com, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};

                Serial->read_parsing(&tSerial);
                val_data = tSerial.str_data_io.split("*");
                if (this->ui->tabWidget->currentIndex() == 0) {
                    work->Get_Input(&tModule, val_data);

                    timeout = work->Request_Data(this, busyForm, Serial_Com, timeout);
                    if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
                    work->Get_Data(&tModule, val_data);

                    Message = "Input Channel ";
                } else if (this->ui->tabWidget->currentIndex() == 1) {
                    work->Get_Output(&tModule, val_data);
                    Message = "Output Channel ";
                }
            } else if (this->ui->tabWidget->currentIndex() == 2) {
                timeout = work->Request_SIM(this, busyForm, Serial_Com, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};

                val_data = tSerial.str_data_sim.split("*");
                work->Get_SIM(&tModule, val_data);
                Message = "SIM Configuration ";
            } else if (this->ui->tabWidget->currentIndex() == 3) {
                timeout = work->Request_ENV(this, busyForm, Serial_Com, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};

                val_data = tSerial.str_data_sim.split("*");
                work->Get_ENV(&tModule, val_data);
                Message = "Environtment ";
            } else if (this->ui->tabWidget->currentIndex() == 4) {
                timeout = work->Request_Sumber(this, busyForm, Serial_Com, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};

                val_data = tSerial.str_data_src.split("*");
                work->Get_Sumber(&tModule, val_data);
                Message = "Sources ";
            } else if (this->ui->tabWidget->currentIndex() == 5) {
                timeout = work->Request_Data(this, busyForm, Serial_Com, timeout);
                if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};

                val_data = tSerial.str_data_dat.split("*");
                work->Get_Data(&tModule, val_data);
                Message = "Alarm ";
            }

            mod.write_module(&tModule);
            this->setInterface(Address_Module);

            Message.append(" Setting is Syncronized ..");
            QMessageBox::information(this, "Syncronization Board", Message, 0, 0);
            this->EnableButton(true);
        } else {
            QMessageBox::warning(this, "Serial Comunication", "Serial Number is not syncronize ..!!", 0, 0);
            this->EnableButton(true);
        }
    }
}

void formModule::on_pbEdit_clicked()
{
    bool timeout = false;
    if (this->ui->tabWidget->currentIndex() == 2) {
        faddModule = new form_addModule(this, false, Address_Module, this->ui->tabWidget->currentIndex());
        faddModule->setWindowTitle("Edit Communications");
        faddModule->setModal(true);
    } else if (this->ui->tabWidget->currentIndex() == 3) {
        faddModule = new form_addModule(this, false, Address_Module, this->ui->tabWidget->currentIndex());
        faddModule->setWindowTitle("Edit Environtments");
        faddModule->setModal(true);
    }
    faddModule->exec();

    if (faddModule->accept == 0) return;

    Address_Module = faddModule->currentFile;
    this->setInterface(Address_Module);
    this->setWindowTitle(
                Address_Module.mid(Address_Module.indexOf("m_")+2,
                                   Address_Module.indexOf(".dbe")).remove(".dbe"));
    struct t_module tModule;

    mod.read_module(&tModule, Address_Module);
    if (Serial_Com->isOpen()) {
        this->writeLogFile();
        this->EnableButton(false);

        timeout = work->Set_ENV(this, busyForm, Serial_Com, &tModule, timeout);
        if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};
        timeout = work->Set_SIM(this, busyForm, Serial_Com, &tModule, timeout);
        if (timeout) {QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); this->EnableButton(true); return;};

        QMessageBox::information(this, "Syncronization Board !!", "Setting Environtment and SIM Configuration Saved ..", 0, 0);

        this->EnableButton(true);
    }

    NoSeri = tModule.serial_number;
}

void formModule::EnableButton(bool enab)
{
    this->ui->pbGetAll->setEnabled(enab);
    this->ui->pbSetAll->setEnabled(enab);
    this->ui->pbGet->setEnabled(enab);
    this->ui->pbSet->setEnabled(enab);
    this->ui->pbEdit->setEnabled(enab);
}

void formModule::writeLogFile() {
    /* Try and open a file for output */
    QString outputFilename = "log.txt";
    QFile outputFile(outputFilename);
    outputFile.open(QIODevice::Append | QIODevice::Text);

    /* Check it opened OK */
    if(!outputFile.isOpen()){
        qDebug() << "- Error, unable to open" << outputFilename << "for output";
    } else {

        /* Point a QTextStream object at the file */
        QTextStream outStream(&outputFile);

        /* Write the line to the file */
        outStream << "-------------------------------------------------------\r\n";

        /* Close the file */
        outputFile.close();
    }
}

void formModule::on_pbAddRow_clicked()
{
    struct t_module tModule;
    module mod;
    Address_Module = "data/module/m_" + this->windowTitle() + ".dbe";
    QString tmp;
    mod.read_module(&tModule, Address_Module);
    if (this->ui->tabWidget->currentIndex() == 4) {
        if (tModule.jml_sumber < 6) {
            tModule.jml_sumber++;
            tmp = QString::number(tModule.jml_sumber) + ";;;0;0;-";
            tModule.sumber.insert(tModule.jml_sumber-1, tmp);
            mod.write_module(&tModule);
            this->setInterface_Sumber(Address_Module);
        } else {
            QMessageBox::information(this, "Sources Configuration", "Max 6 Rows ..", 0, 0);
        }
    } else if (this->ui->tabWidget->currentIndex() == 5) {
        tModule.jml_alarm++;
        tmp = QString::number(tModule.jml_alarm) + ";;;;0;0;0;0;0;0;0";
        tModule.alarm.insert(tModule.jml_alarm-1, tmp);
        mod.write_module(&tModule);
        this->setInterface_Alarm(Address_Module);
    }
}

void formModule::del_src_clicked(int index)
{
    struct t_module tModule; module mod;
    Address_Module = "data/module/m_" + this->windowTitle() + ".dbe";
    QString tmp; QStringList list1; QStringList list2;
    mod.read_module(&tModule, Address_Module);
    list1 = tModule.sumber;
    list1[index] = "";
    tModule.sumber.clear(); tModule.jml_sumber = 0;
    for (int i = 0; i < list1.length(); i++) {
        if (list1.at(i) != "") {
            tmp = list1.at(i);
            list2 = tmp.split(';');
            tmp = QString::number(tModule.jml_sumber+1) + ";" +
                    list2.at(1) + ";" +
                    list2.at(2) + ";" +
                    list2.at(3) + ";" +
                    list2.at(4) + ";" +
                    list2.at(5);
            tModule.sumber.insert(tModule.jml_sumber,tmp);
            tModule.jml_sumber++;
        }
    }
    mod.write_module(&tModule);
    this->setInterface_Sumber(Address_Module);
}

void formModule::del_alrm_clicked(int index)
{
    struct t_module tModule; module mod;
    Address_Module = "data/module/m_" + this->windowTitle() + ".dbe";
    QString tmp; QStringList list1; QStringList list2;
    mod.read_module(&tModule, Address_Module);
    list1 = tModule.alarm;
    list1[index] = "";
    tModule.alarm.clear(); tModule.jml_alarm = 0;
    for (int i = 0; i < list1.length(); i++) {
        if (list1.at(i) != "") {
            tmp = list1.at(i);
            list2 = tmp.split(';');
            tmp = QString::number(tModule.jml_alarm+1) + ";" +
                    list2.at(1) + ";" +
                    list2.at(2) + ";" +
                    list2.at(3) + ";" +
                    list2.at(4) + ";" +
                    list2.at(5) + ";" +
                    list2.at(6) + ";" +
                    list2.at(7) + ";" +
                    list2.at(8) + ";" +
                    list2.at(9) + ";" +
                    list2.at(10);
            tModule.alarm.insert(tModule.jml_alarm,tmp);
            tModule.jml_alarm++;
        }
    }
    mod.write_module(&tModule);
    this->setInterface_Alarm(Address_Module);
}

void formModule::on_pbDeleteRows_clicked()
{
    struct t_module tModule; module mod;
    Address_Module = "data/module/m_" + this->windowTitle() + ".dbe";
    QString tmp; QStringList list1; QStringList list2;
    mod.read_module(&tModule, Address_Module);
    if (this->ui->tabWidget->currentIndex() == 4) {
        list1 = tModule.sumber;
        for (int i = 0; i < tModule.jml_sumber; i++) {
            if (check_source[i]->isChecked()) {
                list1[i] = "";
            }
        }
        tModule.sumber.clear(); tModule.jml_sumber = 0;
        for (int i = 0; i < list1.length(); i++) {
            if (list1.at(i) != "") {
              tmp = list1.at(i);
                list2 = tmp.split(';');
                tmp = QString::number(tModule.jml_sumber+1) + ";" +
                        list2.at(1) + ";" +
                        list2.at(2) + ";" +
                        list2.at(3) + ";" +
                        list2.at(4) + ";" +
                        list2.at(5);
                tModule.sumber.insert(tModule.jml_sumber,tmp);
                tModule.jml_sumber++;
            }
        }
        mod.write_module(&tModule);
        this->setInterface_Sumber(Address_Module);
    } else if (this->ui->tabWidget->currentIndex() == 5) {
        list1 = tModule.alarm;
        for (int i = 0; i < tModule.jml_alarm; i++) {
            if (check_alarm[i]->isChecked()) {
                list1[i] = "";
            }
        }
        tModule.alarm.clear(); tModule.jml_alarm = 0;
        for (int i = 0; i < list1.length(); i++) {
            if (list1.at(i) != "") {
                tmp = list1.at(i);
                list2 = tmp.split(';');
                tmp = QString::number(tModule.jml_alarm+1) + ";" +
                        list2.at(1) + ";" +
                        list2.at(2) + ";" +
                        list2.at(3) + ";" +
                        list2.at(4) + ";" +
                        list2.at(5) + ";" +
                        list2.at(6) + ";" +
                        list2.at(7) + ";" +
                        list2.at(8) + ";" +
                        list2.at(9) + ";" +
                        list2.at(10);
                tModule.alarm.insert(tModule.jml_alarm,tmp);
                tModule.jml_alarm++;
            }
        }
        mod.write_module(&tModule);
        this->setInterface_Alarm(Address_Module);
    }
}
