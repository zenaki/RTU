#include "formmodule.h"
#include "ui_formmodule.h"

#include <QDebug>
#include "mainwindow.h"

formModule::formModule(QWidget *parent, struct t_module *tmodule, QString address) :
    QDialog(parent),
    ui(new Ui::formModule)
{
    ui->setupUi(this);

    this->setInterface(address);

    this->ui->tabWidget->setCurrentIndex(0);
}

formModule::~formModule()
{
    delete ui;
}

void formModule::setInterface(QString address){    
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    int rowInput = 14;
    int rowOutput = 4;
    QString type_IO;

    this->ui->tabel_input->verticalHeader()->setHidden(true);
    this->ui->tabel_input->setColumnCount(6);
    this->ui->tabel_input->setRowCount(rowInput);

    this->ui->tabel_output->verticalHeader()->setHidden(true);
    this->ui->tabel_output->setColumnCount(5);
    this->ui->tabel_output->setRowCount(rowOutput);

    for (int i = 0; i < rowInput; i++){
        type[i] = new QLabel(this);
        name_input[i] = new QLineEdit(this);

        type_input[i] = new QComboBox(this);
        type_input[i]->addItem("RPM");
        type_input[i]->addItem("ON / OFF");
        type_input[i]->addItem("Push Button");
        type_input[i]->addItem("Flow - X");
        type_input[i]->addItem("RPM - RH");
        type_input[i]->addItem("Running Hours");
        type_input[i]->addItem("ON / OFF - RH");
        type_input[i]->addItem("Analog Monita");
        type_input[i]->addItem("Analog Running Hours");

        state_input[i] = new QComboBox(this);
        state_input[i]->addItem("NOT ACTIVE");
        state_input[i]->addItem("ACTIVE");

        calib_m[i] = new QLineEdit(this);
        calib_x[i] = new QLineEdit(this);
    }

    QString str;
    str.append(tModule.input_a1);
    str.append(";");
    str.append(tModule.input_a2);
    str.append(";");
    str.append(tModule.input_a3);
    str.append(";");
    str.append(tModule.input_a4);
    str.append(";");
    str.append(tModule.input_a5);
    str.append(";");
    str.append(tModule.input_a6);
    str.append(";");

    str.append(tModule.input_d1);
    str.append(";");
    str.append(tModule.input_d2);
    str.append(";");
    str.append(tModule.input_d3);
    str.append(";");
    str.append(tModule.input_d4);
    str.append(";");
    str.append(tModule.input_d5);
    str.append(";");
    str.append(tModule.input_d6);
    str.append(";");
    str.append(tModule.input_d7);
    str.append(";");
    str.append(tModule.input_d8);
    str.append(";");

    QStringList list = str.split(';');

    for(int i = 0; i < rowInput; i++){
        if (i < 6) {
            type_IO = " - Analog";
        } else {
            type_IO = " - Digital";
        }
        type_IO.prepend(QString::number(i+1));

        name_input[i]->setText(list[i*5]);
        type_input[i]->setCurrentIndex(list[(i*5)+1].toInt());
        state_input[i]->setCurrentIndex(list[(i*5)+2].toInt());
        calib_m[i]->setText(list[(i*5)+3]);
        calib_x[i]->setText(list[(i*5)+4]);

        this->ui->tabel_input->setItem(i,0, new QTableWidgetItem(type_IO));
        this->ui->tabel_input->setCellWidget(i,1, name_input[i]);
        this->ui->tabel_input->setCellWidget(i,2, type_input[i]);
        this->ui->tabel_input->setCellWidget(i,3, state_input[i]);
        this->ui->tabel_input->setCellWidget(i,4, calib_m[i]);
        this->ui->tabel_input->setCellWidget(i,5, calib_x[i]);
    }

    for (int i = 0; i < rowOutput; i++){
        name_output[i] = new QLineEdit(this);
        type_output[i] = new QLineEdit(this);

        state_output[i] = new QComboBox(this);
        state_output[i]->addItem("NOT ACTIVE");
        state_output[i]->addItem("ACTIVE");

        control[i] = new QComboBox(this);
        control[i]->addItem("LOGIC");
        control[i]->addItem("SCHEDULER");
    }

    str = "";
    str.append(tModule.output_r1);
    str.append(";");
    str.append(tModule.output_r2);
    str.append(";");
    str.append(tModule.output_r3);
    str.append(";");
    str.append(tModule.output_r4);
    str.append(";");

    list = str.split(';');

    for(int i = 0; i < rowOutput; i++){
        name_output[i]->setText(list[i*4]);
        type_output[i]->setText(list[(i*4)+1]);
        state_output[i]->setCurrentIndex(list[(i*4)+2].toInt());
        control[i]->setCurrentIndex(list[(i*4)+3].toInt());

        type_IO = " - Relay";
        type_IO.prepend(QString::number(i+1));
        this->ui->tabel_output->setItem(i,0, new QTableWidgetItem(type_IO));
        this->ui->tabel_output->setCellWidget(i,1, name_output[i]);
        this->ui->tabel_output->setCellWidget(i,2, type_output[i]);
        this->ui->tabel_output->setCellWidget(i,3, state_output[i]);
        this->ui->tabel_output->setCellWidget(i,4, control[i]);
    }

    this->ui->tabel_input->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tabel_output->setEditTriggers(QAbstractItemView::NoEditTriggers);

    modules.sprintf("%s", tModule.module_name);
    this->ui->module_name->setText(modules);
    modules.sprintf("%s", tModule.serial_number);
    this->ui->serial_number->setText(modules);

    this->ui->module_name->setEnabled(false);
    this->ui->serial_number->setEnabled(false);

    this->ui->pbEdit_Module->setHidden(false);
    this->ui->pbSave_Module->setHidden(true);
    this->ui->pbCancel_Module->setHidden(true);

    this->ui->opt_1->setCurrentIndex(tModule.flag_gsm_1);
    this->ui->opt_2->setCurrentIndex(tModule.flag_gsm_2);
    modules.sprintf("%s", tModule.device_name_gsm_1);
    this->ui->device_1->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_2);
    this->ui->device_2->setText(modules);
    this->ui->status_1->setCurrentIndex(tModule.flag_status_active_gsm_1);
    this->ui->status_2->setCurrentIndex(tModule.flag_status_active_gsm_2);
    this->ui->com_1->setCurrentIndex(tModule.flag_com_gsm_1);
    this->ui->com_2->setCurrentIndex(tModule.flag_com_gsm_2);
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

    this->ui->opt_1->setEnabled(false);
    this->ui->device_1->setEnabled(false);
    this->ui->status_1->setEnabled(false);
    this->ui->com_1->setEnabled(false);
    this->ui->number_1->setEnabled(false);
    this->ui->user_1->setEnabled(false);
    this->ui->apn_1->setEnabled(false);

    this->ui->opt_2->setEnabled(false);
    this->ui->device_2->setEnabled(false);
    this->ui->status_2->setEnabled(false);
    this->ui->com_2->setEnabled(false);
    this->ui->number_2->setEnabled(false);
    this->ui->user_2->setEnabled(false);
    this->ui->apn_2->setEnabled(false);

    this->ui->pbEdit->setHidden(false);
    this->ui->pbSave->setHidden(true);
    this->ui->pbCancel->setHidden(true);
}

void formModule::on_pbSet_clicked()
{
    struct t_module tModule;
    QString data[16];
    for (int i = 0; i < ui->tabel_input->rowCount(); i++)
    {
        strcpy(tModule.d_port[i].nama_input, name_input[i]->text().toLatin1());
        tModule.d_port[i].type_input = type_input[i]->currentIndex();
        tModule.d_port[i].status_input = state_input[i]->currentIndex();
        tModule.d_port[i].calib_m = calib_m[i]->text().toFloat();
        tModule.d_port[i].calib_x = calib_x[i]->text().toFloat();

        data[i].sprintf("%s;%d;%d;%.2f;%.2f"
                     , tModule.d_port[i].nama_input
                     , tModule.d_port[i].type_input
                     , tModule.d_port[i].status_input
                     , tModule.d_port[i].calib_m
                     , tModule.d_port[i].calib_x) ;
    }
    strcpy(tModule.input_a1,data[0].toLatin1());
    strcpy(tModule.input_a2,data[1].toLatin1());
    strcpy(tModule.input_a3,data[2].toLatin1());
    strcpy(tModule.input_a4,data[3].toLatin1());
    strcpy(tModule.input_a5,data[4].toLatin1());
    strcpy(tModule.input_a6,data[5].toLatin1());

    strcpy(tModule.input_d1,data[6].toLatin1());
    strcpy(tModule.input_d2,data[7].toLatin1());
    strcpy(tModule.input_d3,data[8].toLatin1());
    strcpy(tModule.input_d4,data[9].toLatin1());
    strcpy(tModule.input_d5,data[10].toLatin1());
    strcpy(tModule.input_d6,data[11].toLatin1());
    strcpy(tModule.input_d7,data[12].toLatin1());
    strcpy(tModule.input_d8,data[13].toLatin1());

    for (int i = 0; i < ui->tabel_output->rowCount(); i++)
    {
        strcpy(tModule.d_port[i].nama_output, name_output[i]->text().toLatin1());
        strcpy(tModule.d_port[i].type_output, type_output[i]->text().toLatin1());
        tModule.d_port[i].status_output = state_output[i]->currentIndex();
        tModule.d_port[i].control = control[i]->currentIndex();

        data[i].sprintf("%s;%s;%d;%d"
                     , tModule.d_port[i].nama_output
                     , tModule.d_port[i].type_output
                     , tModule.d_port[i].status_output
                     , tModule.d_port[i].control) ;
    }
    strcpy(tModule.output_r1,data[0].toLatin1());
    strcpy(tModule.output_r2,data[1].toLatin1());
    strcpy(tModule.output_r3,data[2].toLatin1());
    strcpy(tModule.output_r4,data[3].toLatin1());

    module mod;
    mod.update_setting(&tModule, Address_Module);

    QMessageBox::information(this, "Success!!", "Setting Saved", 0, 0);
}

void formModule::on_pbEdit_clicked()
{
    this->ui->tabWidget->setCurrentIndex(2);

    this->ui->opt_1->setEnabled(true);
    this->ui->device_1->setEnabled(true);
    this->ui->status_1->setEnabled(true);
    this->ui->com_1->setEnabled(true);
    this->ui->number_1->setEnabled(true);
    if (ui->com_1->currentIndex() == 0) {
        this->ui->user_1->setEnabled(false);
        this->ui->apn_1->setEnabled(false);
    } else if (ui->com_1->currentIndex() == 1) {
        this->ui->user_1->setEnabled(true);
        this->ui->apn_1->setEnabled(true);
    }

    this->ui->opt_2->setEnabled(true);
    this->ui->device_2->setEnabled(true);
    this->ui->status_2->setEnabled(true);
    this->ui->com_2->setEnabled(true);
    this->ui->number_2->setEnabled(true);
    if (ui->com_2->currentIndex() == 0) {
        this->ui->user_2->setEnabled(false);
        this->ui->apn_2->setEnabled(false);
    } else if (ui->com_2->currentIndex() == 1) {
        this->ui->user_2->setEnabled(true);
        this->ui->apn_2->setEnabled(true);
    }

    this->ui->pbEdit->setHidden(true);
    this->ui->pbSave->setHidden(false);
    this->ui->pbCancel->setHidden(false);
}

void formModule::on_pbSave_clicked()
{
    struct t_module tModule;

    tModule.flag_gsm_1 = this->ui->opt_1->currentIndex();
    strcpy(tModule.name_gsm_1,ui->opt_1->currentText().toLatin1());
    tModule.flag_gsm_2 = this->ui->opt_2->currentIndex();
    strcpy(tModule.name_gsm_2,ui->opt_2->currentText().toLatin1());

    strcpy(tModule.device_name_gsm_1,ui->device_1->text().toLatin1());
    strcpy(tModule.device_name_gsm_2,ui->device_2->text().toLatin1());

    tModule.flag_status_active_gsm_1 = this->ui->status_1->currentIndex();
    strcpy(tModule.status_gsm_1,ui->status_1->currentText().toLatin1());
    tModule.flag_status_active_gsm_2 = this->ui->status_2->currentIndex();
    strcpy(tModule.status_gsm_2,ui->status_2->currentText().toLatin1());

    tModule.flag_com_gsm_1 = this->ui->com_1->currentIndex();
    strcpy(tModule.com_gsm_1,ui->com_1->currentText().toLatin1());
    tModule.flag_com_gsm_2 = this->ui->com_2->currentIndex();
    strcpy(tModule.com_gsm_2,ui->com_2->currentText().toLatin1());

    strcpy(tModule.number_gsm_1,ui->number_1->text().toLatin1());
    strcpy(tModule.number_gsm_2,ui->number_2->text().toLatin1());

    if (tModule.flag_com_gsm_1 == 0)
    {
        strcpy(tModule.user_gsm_1, "");
        strcpy(tModule.apn_gsm_1, "");
    } else if (tModule.flag_com_gsm_1 == 1)
    {
        strcpy(tModule.user_gsm_1, this->ui->user_1->text().toLatin1());
        strcpy(tModule.apn_gsm_1, this->ui->apn_1->text().toLatin1());
    }

    if (tModule.flag_com_gsm_2 == 0)
    {
        strcpy(tModule.user_gsm_2, "");
        strcpy(tModule.apn_gsm_2, "");
    } else if (tModule.flag_com_gsm_2 == 1)
    {
        strcpy(tModule.user_gsm_2, this->ui->user_2->text().toLatin1());
        strcpy(tModule.apn_gsm_2, this->ui->apn_2->text().toLatin1());
    }

    module mod;
    mod.update_communication(&tModule, Address_Module);
    QString modules;

    this->ui->opt_1->setCurrentIndex(tModule.flag_gsm_1);
    this->ui->opt_2->setCurrentIndex(tModule.flag_gsm_2);
    modules.sprintf("%s", tModule.device_name_gsm_1);
    this->ui->device_1->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_2);
    this->ui->device_2->setText(modules);
    this->ui->status_1->setCurrentIndex(tModule.flag_status_active_gsm_1);
    this->ui->status_2->setCurrentIndex(tModule.flag_status_active_gsm_2);
    this->ui->com_1->setCurrentIndex(tModule.flag_com_gsm_1);
    this->ui->com_2->setCurrentIndex(tModule.flag_com_gsm_2);
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

    this->ui->opt_1->setEnabled(false);
    this->ui->device_1->setEnabled(false);
    this->ui->status_1->setEnabled(false);
    this->ui->com_1->setEnabled(false);
    this->ui->number_1->setEnabled(false);
    this->ui->user_1->setEnabled(false);
    this->ui->apn_1->setEnabled(false);

    this->ui->opt_2->setEnabled(false);
    this->ui->device_2->setEnabled(false);
    this->ui->status_2->setEnabled(false);
    this->ui->com_2->setEnabled(false);
    this->ui->number_2->setEnabled(false);
    this->ui->user_2->setEnabled(false);
    this->ui->apn_2->setEnabled(false);

    this->ui->pbEdit->setHidden(false);
    this->ui->pbSave->setHidden(true);
    this->ui->pbCancel->setHidden(true);
}

void formModule::on_pbCancel_clicked()
{  
    struct t_module tModule;
    module mod;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    this->ui->opt_1->setCurrentIndex(tModule.flag_gsm_1);
    this->ui->opt_2->setCurrentIndex(tModule.flag_gsm_2);
    modules.sprintf("%s", tModule.device_name_gsm_1);
    this->ui->device_1->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_2);
    this->ui->device_2->setText(modules);
    this->ui->status_1->setCurrentIndex(tModule.flag_status_active_gsm_1);
    this->ui->status_2->setCurrentIndex(tModule.flag_status_active_gsm_2);
    this->ui->com_1->setCurrentIndex(tModule.flag_com_gsm_1);
    this->ui->com_2->setCurrentIndex(tModule.flag_com_gsm_2);
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

    this->ui->opt_1->setEnabled(false);
    this->ui->device_1->setEnabled(false);
    this->ui->status_1->setEnabled(false);
    this->ui->com_1->setEnabled(false);
    this->ui->number_1->setEnabled(false);
    this->ui->user_1->setEnabled(false);
    this->ui->apn_1->setEnabled(false);

    this->ui->opt_2->setEnabled(false);
    this->ui->device_2->setEnabled(false);
    this->ui->status_2->setEnabled(false);
    this->ui->com_2->setEnabled(false);
    this->ui->number_2->setEnabled(false);
    this->ui->user_2->setEnabled(false);
    this->ui->apn_2->setEnabled(false);

    this->ui->pbEdit->setHidden(false);
    this->ui->pbSave->setHidden(true);
    this->ui->pbCancel->setHidden(true);
}

void formModule::on_com_1_currentIndexChanged(int index)
{
    if (index == 0) {
        this->ui->user_1->setEnabled(false);
        this->ui->apn_1->setEnabled(false);
    } else if (index == 1) {
        this->ui->user_1->setEnabled(true);
        this->ui->apn_1->setEnabled(true);
    }
}

void formModule::on_com_2_currentIndexChanged(int index)
{
    if (index == 0) {
        this->ui->user_2->setEnabled(false);
        this->ui->apn_2->setEnabled(false);
    } else if (index == 1) {
        this->ui->user_2->setEnabled(true);
        this->ui->apn_2->setEnabled(true);
    }
}

void formModule::on_tabWidget_tabBarClicked(int index)
{
    this->ui->tabWidget->setCurrentIndex(index);

    struct t_module tModule;
    module mod;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    modules.sprintf("%s", tModule.module_name);
    this->ui->module_name->setText(modules);
    modules.sprintf("%s", tModule.serial_number);
    this->ui->serial_number->setText(modules);

    this->ui->module_name->setEnabled(false);
    this->ui->serial_number->setEnabled(false);

    this->ui->pbEdit_Module->setHidden(false);
    this->ui->pbSave_Module->setHidden(true);
    this->ui->pbCancel_Module->setHidden(true);

    this->ui->opt_1->setCurrentIndex(tModule.flag_gsm_1);
    this->ui->opt_2->setCurrentIndex(tModule.flag_gsm_2);
    modules.sprintf("%s", tModule.device_name_gsm_1);
    this->ui->device_1->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_2);
    this->ui->device_2->setText(modules);
    this->ui->status_1->setCurrentIndex(tModule.flag_status_active_gsm_1);
    this->ui->status_2->setCurrentIndex(tModule.flag_status_active_gsm_2);
    this->ui->com_1->setCurrentIndex(tModule.flag_com_gsm_1);
    this->ui->com_2->setCurrentIndex(tModule.flag_com_gsm_2);
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

    this->ui->opt_1->setEnabled(false);
    this->ui->device_1->setEnabled(false);
    this->ui->status_1->setEnabled(false);
    this->ui->com_1->setEnabled(false);
    this->ui->number_1->setEnabled(false);
    this->ui->user_1->setEnabled(false);
    this->ui->apn_1->setEnabled(false);

    this->ui->opt_2->setEnabled(false);
    this->ui->device_2->setEnabled(false);
    this->ui->status_2->setEnabled(false);
    this->ui->com_2->setEnabled(false);
    this->ui->number_2->setEnabled(false);
    this->ui->user_2->setEnabled(false);
    this->ui->apn_2->setEnabled(false);

    this->ui->pbEdit->setHidden(false);
    this->ui->pbSave->setHidden(true);
    this->ui->pbCancel->setHidden(true);
}

void formModule::on_pbEdit_Module_clicked()
{
    this->ui->module_name->setEnabled(true);
    this->ui->serial_number->setEnabled(true);

    this->ui->pbEdit_Module->setHidden(true);
    this->ui->pbSave_Module->setHidden(false);
    this->ui->pbCancel_Module->setHidden(false);

}

void formModule::on_pbSave_Module_clicked()
{
    struct t_module tModule;

    strcpy(tModule.module_name,ui->module_name->text().toLatin1());
    strcpy(tModule.serial_number,ui->serial_number->text().toLatin1());

    module mod;
    mod.update_module(&tModule, Address_Module);
    QString modules;

    modules.sprintf("%s", tModule.module_name);
    this->ui->module_name->setText(modules);
    modules.sprintf("%s", tModule.serial_number);
    this->ui->serial_number->setText(modules);

    this->ui->module_name->setEnabled(false);
    this->ui->serial_number->setEnabled(false);

    this->ui->pbEdit_Module->setHidden(false);
    this->ui->pbSave_Module->setHidden(true);
    this->ui->pbCancel_Module->setHidden(true);
}

void formModule::on_pbCancel_Module_clicked()
{
    struct t_module tModule;
    module mod;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    modules.sprintf("%s", tModule.module_name);
    this->ui->module_name->setText(modules);
    modules.sprintf("%s", tModule.serial_number);
    this->ui->serial_number->setText(modules);

    this->ui->module_name->setEnabled(false);
    this->ui->serial_number->setEnabled(false);

    this->ui->pbEdit_Module->setHidden(false);
    this->ui->pbSave_Module->setHidden(true);
    this->ui->pbCancel_Module->setHidden(true);
}

void formModule::on_pbSync_clicked()
{
    Serial_Connection = new MainWindow;
    Serial_Connection->openSerialPort();
    QString string_data;

    Serial_Connection->writeData("/r/n");
    Serial_Connection->readData();
//    string_data.sprintf("%s", Serial_Connection->readData());
//    qDebug() << Serial_Connection->readData();
    Serial_Connection->writeData("cek_env/r/n");
    Serial_Connection->readData();
//    qDebug() << Serial_Connection->readData();
    Serial_Connection->writeData("set_env nama nama_dari_hmi/r/n");
    Serial_Connection->readData();
//    qDebug() << Serial_Connection->readData();
    Serial_Connection->writeData("cek_env/r/n");
    Serial_Connection->readData();
//    qDebug() << Serial_Connection->readData();

    Serial_Connection->closeSerialPort();
}
