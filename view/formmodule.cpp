#include "formmodule.h"
#include "ui_formmodule.h"

#include <QDebug>
#include <QTime>

#include <QtGui>

formModule::formModule(QWidget *parent, QString address, QSerialPort *SerialPort) :
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

    Main = new MainWindow();
    Serial = new serial();
    Setting = new setting();

    connect(Serial_Com, SIGNAL(readyRead()), this, SLOT(readData()));

    this->setInterface(address);

    this->ui->pbEditModule->setHidden(true);

    QMovie *movie = new QMovie(":/new/prefix1/image/circle-loading.gif");
    this->ui->Busy->setMovie(movie);
    movie->start();
    this->ui->Busy->hide();

    this->ui->request->hide();

    this->ui->pbGet->setText("Sync");
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
    this->ui->tabel_input->setColumnCount(5);
//    this->ui->tabel_input->setColumnWidth(0, 50);
    this->ui->tabel_input->setColumnWidth(1, 100);
    this->ui->tabel_input->setColumnWidth(2, 150);
//    this->ui->tabel_input->setColumnWidth(3, 100);
//    this->ui->tabel_input->setColumnWidth(4, 100);
    this->ui->tabel_input->setRowCount(rowInput);

    this->ui->tabel_output->verticalHeader()->setHidden(true);
    this->ui->tabel_output->setColumnCount(4);
    //    this->ui->tabel_output->setColumnWidth(0, 50);
        this->ui->tabel_output->setColumnWidth(1, 100);
        this->ui->tabel_output->setColumnWidth(2, 100);
    //    this->ui->tabel_output->setColumnWidth(3, 100);
    this->ui->tabel_output->setRowCount(rowOutput);

    for (int i = 0; i < rowInput; i++){
        name_input[i] = new QLineEdit(this);

        type_input[i] = new QComboBox(this);
        if (i < 6) {
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
//        state_input[i] = new QComboBox(this);
//        state_input[i]->addItem("NOT ACTIVE",0);
//        state_input[i]->addItem("ACTIVE",1);

        calib_m[i] = new QLineEdit(this);
        calib_m[i]->setAlignment(Qt::AlignRight);

        calib_x[i] = new QLineEdit(this);
        calib_x[i]->setAlignment(Qt::AlignRight);
    }

    QString str;
    str.append(tModule.input_a1_name).append(";");
    str.append(tModule.input_a1).append(";");
    str.append(tModule.input_a2_name).append(";");
    str.append(tModule.input_a2).append(";");
    str.append(tModule.input_a3_name).append(";");
    str.append(tModule.input_a3).append(";");
    str.append(tModule.input_a4_name).append(";");
    str.append(tModule.input_a4).append(";");
    str.append(tModule.input_a5_name).append(";");
    str.append(tModule.input_a5).append(";");
    str.append(tModule.input_a6_name).append(";");
    str.append(tModule.input_a6).append(";");

    str.append(tModule.input_d1_name).append(";");
    str.append(tModule.input_d1).append(";");
    str.append(tModule.input_d2_name).append(";");
    str.append(tModule.input_d2).append(";");
    str.append(tModule.input_d3_name).append(";");
    str.append(tModule.input_d3).append(";");
    str.append(tModule.input_d4_name).append(";");
    str.append(tModule.input_d4).append(";");
    str.append(tModule.input_d5_name).append(";");
    str.append(tModule.input_d5).append(";");
    str.append(tModule.input_d6_name).append(";");
    str.append(tModule.input_d6).append(";");
    str.append(tModule.input_d7_name).append(";");
    str.append(tModule.input_d7).append(";");
    str.append(tModule.input_d8_name).append(";");
    str.append(tModule.input_d8).append(";");

    QStringList list = str.split(';');

    for(int i = 0; i < rowInput; i++){
        if (i < 6) {
            type_IO = " - Analog";
        } else {
            type_IO = " - Digital";
        }

        type_IO.prepend(QString::number(i+1));

        name_input[i]->setText(list[i*6]);
        int indx;
        if (list[(i*6)+3].toInt() == 250) {indx = 0;}
        if (list[(i*6)+3].toInt() == 230) {indx = 1;}
        if (list[(i*6)+3].toInt() == 1) {indx = 0;}
        if (list[(i*6)+3].toInt() == 2) {indx = 1;}
        if (list[(i*6)+3].toInt() == 6) {indx = 2;}
        if (list[(i*6)+3].toInt() == 7) {indx = 3;}
        if (list[(i*6)+3].toInt() == 9) {indx = 4;}
        type_input[i]->setCurrentIndex(indx);
//        state_input[i]->setCurrentIndex(list[(i*6)+3].toInt());
        calib_m[i]->setText(list[(i*6)+4]);
        calib_x[i]->setText(list[(i*6)+5]);

        this->ui->tabel_input->setItem(i,0, new QTableWidgetItem(type_IO));
        this->ui->tabel_input->setCellWidget(i,1, name_input[i]);
        this->ui->tabel_input->setCellWidget(i,2, type_input[i]);
//        this->ui->tabel_input->setCellWidget(i,3, state_input[i]);
        this->ui->tabel_input->setCellWidget(i,3, calib_m[i]);
        this->ui->tabel_input->setCellWidget(i,4, calib_x[i]);
    }

    for (int i = 0; i < rowOutput; i++){
        name_output[i] = new QLineEdit(this);

        state_output[i] = new QComboBox(this);
        state_output[i]->addItem("NOT ACTIVE");
        state_output[i]->addItem("ACTIVE");

        control[i] = new QComboBox(this);
        control[i]->addItem("LOGIC");
        control[i]->addItem("SCHEDULER");
    }

    str = "";
    str.append(tModule.output_r1_name).append(";");
    str.append(tModule.output_r1).append(";");
    str.append(tModule.output_r2_name).append(";");
    str.append(tModule.output_r2).append(";");
    str.append(tModule.output_r3_name).append(";");
    str.append(tModule.output_r3).append(";");
    str.append(tModule.output_r4_name).append(";");
    str.append(tModule.output_r4).append(";");

    list = str.split(';');

    for(int i = 0; i < rowOutput; i++){
        name_output[i]->setText(list[i*5]);
        state_output[i]->setCurrentIndex(list[(i*5)+3].toInt());
        control[i]->setCurrentIndex(list[(i*5)+4].toInt());

        type_IO = " - Relay";
        type_IO.prepend(QString::number(i+1));
        this->ui->tabel_output->setItem(i,0, new QTableWidgetItem(type_IO));
        this->ui->tabel_output->setCellWidget(i,1, name_output[i]);
        this->ui->tabel_output->setCellWidget(i,2, state_output[i]);
        this->ui->tabel_output->setCellWidget(i,3, control[i]);
    }

    this->ui->tabel_input->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tabel_output->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

void formModule::on_pbSet_clicked()
{
    struct t_module tModule;
    QString data[16];
    QString Message;
    QString Request;
    int indx;
    int jeda = 1000;
    int diff = 0;
    int reset = 0;

    if (Serial_Com->isOpen()) {
        if (NoSeri == GetNoSeri) {
            this->ui->pbGet->setEnabled(false);
            this->ui->pbSet->setEnabled(false);
            this->ui->Busy->show();
            this->ui->request->show();
            this->ui->request->setText(Request);
            for (int i = 0; i < ui->tabel_input->rowCount(); i++)
            {
                Request.sprintf("set_kanal %d %.3f %.3f\r\n", i+1, calib_m[i]->text().toFloat(), calib_x[i]->text().toFloat());
                Serial->write_data(Serial_Com, Request);
                this->ui->request->setText(Request);
                this->delay(jeda);

                if (i<6) {
                    if (type_input[i]->currentIndex() == 0) {indx = 250;}
                    if (type_input[i]->currentIndex() == 1) {indx = 230;}

                    Request.sprintf("set_kanal %d status %d\r\n", i+1, indx);
                    Serial->write_data(Serial_Com, Request);
                    this->ui->request->setText(Request);
                    this->delay(jeda);
                } else {
                    if (type_input[i]->currentIndex() == 0) {indx = 1;}
                    if (type_input[i]->currentIndex() == 1) {indx = 2;}
                    if (type_input[i]->currentIndex() == 2) {indx = 6;}
                    if (type_input[i]->currentIndex() == 3) {indx = 7;}
                    if (type_input[i]->currentIndex() == 4) {indx = 9;}
                    if (indx == 9) {reset = 1;}
                    Request.sprintf("set_kanal %d status %d\r\n", i+1, indx);
                    Serial->write_data(Serial_Com, Request);
                    this->ui->request->setText(Request);
                    this->delay(jeda);
                }
            }
            for (int i = 0; i < ui->tabel_output->rowCount(); i++)
            {
                Request.sprintf("set_relay %d %d\r\n", i+1, state_output[i]->currentIndex());
                Serial->write_data(Serial_Com, Request);
                this->ui->request->setText(Request);
                this->delay(jeda);
            }

            if (!ui->device_1->text().isEmpty()) {
                Request = "set_cfg_sim 1 nama " + ui->device_1->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 1 nama -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->opt_1->text().isEmpty()) {
                Request = "set_cfg_sim 1 operator " + ui->opt_1->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 1 operator -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->number_1->text().isEmpty()) {
                Request = "set_cfg_sim 1 nomor " + ui->number_1->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 1 nomor -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->status_1->text().isEmpty()) {
                if (ui->status_1->text() == "ACTIVE") {
                    Request = "set_cfg_sim 1 status 1\r\n";
                } else {
                    Request = "set_cfg_sim 1 status 0\r\n";
                }
            } else {
                Request = "set_cfg_sim 1 status 0\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->apn_1->text().isEmpty()) {
                Request = "set_cfg_sim 1 apn " + ui->apn_1->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 1 apn -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->user_1->text().isEmpty()) {
                Request = "set_cfg_sim 1 user " + ui->user_1->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 1 user -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->passwd_1->text().isEmpty()) {
                Request = "set_cfg_sim 1 pass " + ui->passwd_1->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 1 pass -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->com_1->text().isEmpty()) {
                Request = "set_cfg_sim 1 mode " + ui->com_1->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 1 mode -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);

            if (!ui->device_2->text().isEmpty()) {
                Request = "set_cfg_sim 2 nama " + ui->device_2->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 2 nama -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->opt_2->text().isEmpty()) {
                Request = "set_cfg_sim 2 operator " + ui->opt_2->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 2 operator -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->number_2->text().isEmpty()) {
                Request = "set_cfg_sim 2 nomor " + ui->number_2->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 2 nomor -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->status_2->text().isEmpty()) {
                if (ui->status_2->text() == "ACTIVE") {
                    Request = "set_cfg_sim 2 status 1\r\n";
                } else {
                    Request = "set_cfg_sim 2 status 0\r\n";
                }
            } else {
                Request = "set_cfg_sim 2 status 0\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->apn_2->text().isEmpty()) {
                Request = "set_cfg_sim 2 apn " + ui->apn_2->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 2 apn -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->user_1->text().isEmpty()) {
                Request = "set_cfg_sim 2 user " + ui->user_2->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 2 user -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->passwd_2->text().isEmpty()) {
                Request = "set_cfg_sim 2 pass " + ui->passwd_2->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 2 pass -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);
            if (!ui->com_1->text().isEmpty()) {
                Request = "set_cfg_sim 2 mode " + ui->com_1->text() + "\r\n";
            } else {
                Request = "set_cfg_sim 2 mode -\r\n";
            }
            Serial->write_data(Serial_Com, Request);
            this->ui->request->setText(Request);
            this->delay(jeda);

            Message = "On-Board";
        } else {
            Message = "On-Local";
            if (!GetNoSeri.isEmpty()) {
                diff = 1;
            } else {
                diff = 2;
            }
        }
    } else {
        Message = "On-Local";
    }

    for (int i = 0; i < ui->tabel_input->rowCount(); i++)
    {
//        tModule.d_port[i].status_input = state_input[i]->currentIndex();
        tModule.d_port[i].calib_m = calib_m[i]->text().toFloat();
        tModule.d_port[i].calib_x = calib_x[i]->text().toFloat();

        if (i < 6) {
            if (type_input[i]->currentIndex() == 0) {indx = 250;}
            if (type_input[i]->currentIndex() == 1) {indx = 230;}
            tModule.d_port[i].type_input = indx;

            data[i].sprintf("A;%d;%d;%.3f;%.3f", i+1
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

            data[i].sprintf("D;%d;%d;%.3f;%.3f", i-6+1
                            , indx
                            , tModule.d_port[i].calib_m
                            , tModule.d_port[i].calib_x);
        }
    }

    strcpy(tModule.input_a1,data[0].toLatin1());
    strcpy(tModule.input_a1_name,name_input[0]->text().toLatin1());
    strcpy(tModule.input_a2,data[1].toLatin1());
    strcpy(tModule.input_a2_name,name_input[1]->text().toLatin1());
    strcpy(tModule.input_a3,data[2].toLatin1());
    strcpy(tModule.input_a3_name,name_input[2]->text().toLatin1());
    strcpy(tModule.input_a4,data[3].toLatin1());
    strcpy(tModule.input_a4_name,name_input[3]->text().toLatin1());
    strcpy(tModule.input_a5,data[4].toLatin1());
    strcpy(tModule.input_a5_name,name_input[4]->text().toLatin1());
    strcpy(tModule.input_a6,data[5].toLatin1());
    strcpy(tModule.input_a6_name,name_input[5]->text().toLatin1());

    strcpy(tModule.input_d1,data[6].toLatin1());
    strcpy(tModule.input_d1_name,name_input[6]->text().toLatin1());
    strcpy(tModule.input_d2,data[7].toLatin1());
    strcpy(tModule.input_d2_name,name_input[7]->text().toLatin1());
    strcpy(tModule.input_d3,data[8].toLatin1());
    strcpy(tModule.input_d3_name,name_input[8]->text().toLatin1());
    strcpy(tModule.input_d4,data[9].toLatin1());
    strcpy(tModule.input_d4_name,name_input[9]->text().toLatin1());
    strcpy(tModule.input_d5,data[10].toLatin1());
    strcpy(tModule.input_d5_name,name_input[10]->text().toLatin1());
    strcpy(tModule.input_d6,data[11].toLatin1());
    strcpy(tModule.input_d6_name,name_input[11]->text().toLatin1());
    strcpy(tModule.input_d7,data[12].toLatin1());
    strcpy(tModule.input_d7_name,name_input[12]->text().toLatin1());
    strcpy(tModule.input_d8,data[13].toLatin1());
    strcpy(tModule.input_d8_name,name_input[13]->text().toLatin1());

    for (int i = 0; i < ui->tabel_output->rowCount(); i++)
    {
        tModule.d_port[i].status_output = state_output[i]->currentIndex();
        tModule.d_port[i].control = control[i]->currentIndex();

        data[i].sprintf("R;%d;%d;%d", i+1
                     , tModule.d_port[i].status_output
                     , tModule.d_port[i].control) ;
    }

    strcpy(tModule.output_r1,data[0].toLatin1());
    strcpy(tModule.output_r1_name,name_output[0]->text().toLatin1());
    strcpy(tModule.output_r2,data[1].toLatin1());
    strcpy(tModule.output_r2_name,name_output[1]->text().toLatin1());
    strcpy(tModule.output_r3,data[2].toLatin1());
    strcpy(tModule.output_r3_name,name_output[2]->text().toLatin1());
    strcpy(tModule.output_r4,data[3].toLatin1());
    strcpy(tModule.output_r4_name,name_output[3]->text().toLatin1());

    module mod;
    mod.update_setting(&tModule, Address_Module);

    if (reset == 1) {
        Request = "reset\r\n";
        Serial->write_data(Serial_Com, Request);
        this->ui->request->setText(Request);
        this->delay(jeda*4);
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
        Message.append("\n\n Syncronize first for Setting to Board ..");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    }
    this->ui->pbGet->setEnabled(true);
    this->ui->pbSet->setEnabled(true);
    this->ui->Busy->hide();
    Request = "";
    this->ui->request->setText(Request);
    this->ui->request->hide();
}

void formModule::on_tabWidget_tabBarClicked(int index)
{
    if (index == 2) {
        this->ui->pbEditModule->setHidden(false);
    } else {
        this->ui->pbEditModule->setHidden(true);
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
}

void formModule::on_pbGet_clicked()
{
//        Serial->write_data(Serial_Com, "Test\r\n");
        this->ui->pbGet->setEnabled(false);
        this->ui->pbSet->setEnabled(false);
        if (!Serial_Com->isOpen())
        {
//            Main->on_actionConnect_triggered();
            QMessageBox::warning(this, "Serial Comunication !!", "Protocol is not open ..", 0, 0);
            this->ui->pbGet->setEnabled(true);
            this->ui->pbSet->setEnabled(true);
        } else
        {
            if (GetNoSeri.isEmpty() || GetNamaBoard.isEmpty()) {
                Serial->write_data(Serial_Com, "hmi_cek_env\r\n");
//                Serial->write_data(Serial_Com, "hmi_sync\r\n");
//                Serial->write_data(Serial_Com, "hmi_cek_cfg_sim\r\n");
            } else {
                Serial->write_data(Serial_Com, "hmi_sync\r\n");
                Serial->write_data(Serial_Com, "hmi_cek_cfg_sim\r\n");
            }
        }
}

void formModule::readData()
{
    str_data.append(Serial_Com->readAll());
    if (GetNoSeri.isEmpty()) {
        if (str_data.indexOf("<ENV") > 0 && str_data.indexOf("ENV>") > 0) {
            str_data = str_data.mid(str_data.indexOf("<ENV"), str_data.indexOf("ENV>"));
            val_data = str_data
                        .remove(" ")
                        .remove("<ENV")
                        .remove("<ENVani$")
                        .remove("ENV>")
                        .remove("Rinjani$")
                        .remove("hmi_cek_env")
                        .remove("\r").remove("\n").split(";");
            GetNamaBoard = val_data[0];
            GetNoSeri = val_data[1];
//            qDebug() << str_data;
            val_data.clear();
            str_data.clear();
            if (NoSeri == GetNoSeri) {
                QMessageBox::information(this, "Syncronize Success !!!", "Serial Number Syncronized !!!", 0, 0);
                this->ui->pbGet->setEnabled(true);
                this->ui->pbSet->setEnabled(true);
                this->ui->pbGet->setText("Get Setting");
            } else {
                QMessageBox::warning(this, "Syncronize Error !!!", "Different Serial Number !!!", 0, 0);
                GetNamaBoard = "";
                GetNoSeri = "";
                this->ui->pbGet->setEnabled(true);
                this->ui->pbSet->setEnabled(true);
                this->ui->pbGet->setText("Sync");
            }
        }
    } else {
        if (NoSeri == GetNoSeri) {
            if (str_data.indexOf("<I/O") > 0 && str_data.indexOf("I/O>") > 0) {
                str_data = str_data.mid(str_data.indexOf("<I/O"), str_data.indexOf("I/O>"));
                val_data = str_data
                            .remove(" ")
                            .remove("<I/O")
                            .remove("<I/Oani$")
                            .remove("I/O>")
                            .remove("Rinjani$")
                            .remove("hmi_sync")
                            .remove("\r").remove("\n").remove("(X)").split("*");
                this->Sync_IO();
//                qDebug() << str_data;
                str_data.clear();
                this->ui->pbGet->setEnabled(true);
                this->ui->pbSet->setEnabled(true);
            } else if (str_data.indexOf("<SIM") > 0 && str_data.indexOf("SIM>") > 0) {
                str_data = str_data.mid(str_data.indexOf("<SIM"), str_data.indexOf("SIM>"));
                val_data = str_data
                            .remove(" ")
                            .remove("<SIM")
                            .remove("<SIMani$")
                            .remove("SIM>")
                            .remove("Rinjani$")
                            .remove("hmi_cek_cfg_sim")
                            .remove("\r").remove("\n").remove("(X)").split("*");
                this->Sync_SIM();
//                qDebug() << str_data;
                QMessageBox::information(this, "Success!!", "Setting Syncronized ..", 0, 0);
                str_data.clear();
                this->ui->pbGet->setEnabled(true);
                this->ui->pbSet->setEnabled(true);
            }
        } else {
            QMessageBox::warning(this, "Syncronize Error !!", "Different Serial Number !!!", 0, 0);
            val_data.clear();
            str_data.clear();
            this->ui->pbGet->setEnabled(true);
            this->ui->pbSet->setEnabled(true);
        }
    }
}

void formModule::Sync_IO()
{
    struct t_module tModule;
    QString data[16];
    QString temp;
    for (int i = 0; i < ui->tabel_input->rowCount(); i++)
    {
        if (i<6) {
            temp = val_data[i];
            if (temp.mid(2,1) == QString::number(i+1)) {
                data[i] = val_data[i];
            }
        } else {
            temp = val_data[i];
            if (temp.mid(2,1) == QString::number(i-6+1)) {
                data[i] = val_data[i];
            }
        }
    }

    temp = data[0];
    if (temp.mid(0,2) == "A;") {
        strcpy(tModule.input_a1,data[0].toLatin1());
        strcpy(tModule.input_a1_name,name_input[0]->text().toLatin1());
    } else {
        data[0] = "A;1;250;0.000;0.000";
        strcpy(tModule.input_a1,data[0].toLatin1());
        strcpy(tModule.input_a1_name,name_input[0]->text().toLatin1());
    } temp = data[1];
    if (temp.mid(0,2) == "A;") {
        strcpy(tModule.input_a2,data[1].toLatin1());
        strcpy(tModule.input_a2_name,name_input[1]->text().toLatin1());
    } else {
        data[1] = "A;2;250;0.000;0.000";
        strcpy(tModule.input_a2,data[1].toLatin1());
        strcpy(tModule.input_a2_name,name_input[1]->text().toLatin1());
    } temp = data[2];
    if (temp.mid(0,2) == "A;") {
        strcpy(tModule.input_a3,data[2].toLatin1());
        strcpy(tModule.input_a3_name,name_input[2]->text().toLatin1());
    } else {
        data[2] = "A;3;250;0.000;0.000";
        strcpy(tModule.input_a3,data[2].toLatin1());
        strcpy(tModule.input_a3_name,name_input[2]->text().toLatin1());
    } temp = data[3];
    if (temp.mid(0,2) == "A;") {
        strcpy(tModule.input_a4,data[3].toLatin1());
        strcpy(tModule.input_a4_name,name_input[3]->text().toLatin1());
    } else {
        data[3] = "A;4;250;0.000;0.000";
        strcpy(tModule.input_a4,data[3].toLatin1());
        strcpy(tModule.input_a4_name,name_input[3]->text().toLatin1());
    } temp = data[4];
    if (temp.mid(0,2) == "A;") {
        strcpy(tModule.input_a5,data[4].toLatin1());
        strcpy(tModule.input_a5_name,name_input[4]->text().toLatin1());
    } else {
        data[4] = "A;5;250;0.000;0.000";
        strcpy(tModule.input_a5,data[4].toLatin1());
        strcpy(tModule.input_a5_name,name_input[4]->text().toLatin1());
    } temp = data[5];
    if (temp.mid(0,2) == "A;") {
        strcpy(tModule.input_a6,data[5].toLatin1());
        strcpy(tModule.input_a6_name,name_input[5]->text().toLatin1());
    } else {
        data[5] = "A;6;250;0.000;0.000";
        strcpy(tModule.input_a6,data[5].toLatin1());
        strcpy(tModule.input_a6_name,name_input[5]->text().toLatin1());
    }


    temp = data[6];
    if (temp.mid(0,2) == "D;") {
        strcpy(tModule.input_d1,data[6].toLatin1());
        strcpy(tModule.input_d1_name,name_input[6]->text().toLatin1());
    } else {
        data[6] = "D;1;1;0.000;0.000";
        strcpy(tModule.input_d1,data[6].toLatin1());
        strcpy(tModule.input_d1_name,name_input[6]->text().toLatin1());
    } temp = data[7];
    if (temp.mid(0,2) == "D;") {
        strcpy(tModule.input_d2,data[7].toLatin1());
        strcpy(tModule.input_d2_name,name_input[7]->text().toLatin1());
    } else {
        data[7] = "D;2;1;0.000;0.000";
        strcpy(tModule.input_d1,data[7].toLatin1());
        strcpy(tModule.input_d1_name,name_input[7]->text().toLatin1());
    } temp = data[8];
    if (temp.mid(0,2) == "D;") {
        strcpy(tModule.input_d3,data[8].toLatin1());
        strcpy(tModule.input_d3_name,name_input[8]->text().toLatin1());
    } else {
        data[8] = "D;3;1;0.000;0.000";
        strcpy(tModule.input_d1,data[8].toLatin1());
        strcpy(tModule.input_d1_name,name_input[8]->text().toLatin1());
    } temp = data[9];
    if (temp.mid(0,2) == "D;") {
        strcpy(tModule.input_d4,data[9].toLatin1());
        strcpy(tModule.input_d4_name,name_input[9]->text().toLatin1());
    } else {
        data[9] = "D;4;1;0.000;0.000";
        strcpy(tModule.input_d1,data[9].toLatin1());
        strcpy(tModule.input_d1_name,name_input[9]->text().toLatin1());
    } temp = data[10];
    if (temp.mid(0,2) == "D;") {
        strcpy(tModule.input_d5,data[10].toLatin1());
        strcpy(tModule.input_d5_name,name_input[10]->text().toLatin1());
    } else {
        data[10] = "D;5;1;0.000;0.000";
        strcpy(tModule.input_d1,data[10].toLatin1());
        strcpy(tModule.input_d1_name,name_input[10]->text().toLatin1());
    } temp = data[11];
    if (temp.mid(0,2) == "D;") {
        strcpy(tModule.input_d6,data[11].toLatin1());
        strcpy(tModule.input_d6_name,name_input[11]->text().toLatin1());
    } else {
        data[11] = "D;6;1;0.000;0.000";
        strcpy(tModule.input_d1,data[11].toLatin1());
        strcpy(tModule.input_d1_name,name_input[11]->text().toLatin1());
    } temp = data[12];
    if (temp.mid(0,2) == "D;") {
        strcpy(tModule.input_d7,data[12].toLatin1());
        strcpy(tModule.input_d7_name,name_input[12]->text().toLatin1());
    } else {
        data[12] = "D;7;1;0.000;0.000";
        strcpy(tModule.input_d1,data[12].toLatin1());
        strcpy(tModule.input_d1_name,name_input[12]->text().toLatin1());
    } temp = data[13];
    if (temp.mid(0,2) == "D;") {
        strcpy(tModule.input_d8,data[13].toLatin1());
        strcpy(tModule.input_d8_name,name_input[13]->text().toLatin1());
    } else {
        data[13] = "D;8;1;0.000;0.000";
        strcpy(tModule.input_d1,data[13].toLatin1());
        strcpy(tModule.input_d1_name,name_input[13]->text().toLatin1());
    }

    for (int i = 0; i < ui->tabel_output->rowCount(); i++)
    {
        temp = val_data[i+14];
        if (temp.mid(2,1) == QString::number(i+1)) {
            data[i] = val_data[i+14];
        }
    }

    temp = data[0];
    if (temp.mid(0,2) == "R;") {
        strcpy(tModule.output_r1,data[0].toLatin1());
        strcpy(tModule.output_r1_name,name_output[0]->text().toLatin1());
    } else {
        data[0] = "R;1;0;0";
        strcpy(tModule.input_d1,data[0].toLatin1());
        strcpy(tModule.input_d1_name,name_input[0]->text().toLatin1());
    } temp = data[1];
    if (temp.mid(0,2) == "R;") {
        strcpy(tModule.output_r2,data[1].toLatin1());
        strcpy(tModule.output_r2_name,name_output[1]->text().toLatin1());
    } else {
        data[1] = "R;1;0;0";
        strcpy(tModule.input_d1,data[1].toLatin1());
        strcpy(tModule.input_d1_name,name_input[1]->text().toLatin1());
    } temp = data[2];
    if (temp.mid(0,2) == "R;") {
        strcpy(tModule.output_r3,data[2].toLatin1());
        strcpy(tModule.output_r3_name,name_output[2]->text().toLatin1());
    } else {
        data[2] = "R;1;0;0";
        strcpy(tModule.input_d1,data[2].toLatin1());
        strcpy(tModule.input_d1_name,name_input[2]->text().toLatin1());
    } temp = data[3];
    if (temp.mid(0,2) == "R;") {
        strcpy(tModule.output_r4,data[3].toLatin1());
        strcpy(tModule.output_r4_name,name_output[3]->text().toLatin1());
    } else {
        data[3] = "R;1;0;0";
        strcpy(tModule.input_d1,data[3].toLatin1());
        strcpy(tModule.input_d1_name,name_input[3]->text().toLatin1());
    }

    module mod;
    mod.update_setting(&tModule, Address_Module);
    this->setInterface(Address_Module);
}

void formModule::Sync_SIM()
{
    struct t_module tModule;
    QString data[16];
    QStringList temp;
    for (int i = 0; i < 2; i++)
    {
        data[i] = val_data[i];
    }

    temp = data[0].split(";");
    if (temp[1] != "-") {
        data[0] = temp[1];
        strcpy(tModule.device_name_gsm_1, data[0].toLatin1());
    } else {
        data[0] = "";
        strcpy(tModule.device_name_gsm_1, data[0].toLatin1());
    }
    if (temp[2] != "-") {
        data[0] = temp[2];
        strcpy(tModule.name_gsm_1, data[0].toLatin1());
        if (data[0] == "TELKOMSEL") {
            tModule.flag_gsm_1 = 0;
        } else if (data[0] == "INDOSAT") {
            tModule.flag_gsm_1 = 1;
        } else if (data[0] == "XL") {
            tModule.flag_gsm_1 = 2;
        } else if (data[0] == "3") {
            tModule.flag_gsm_1 = 3;
        }
    } else {
        data[0] = "";
        strcpy(tModule.name_gsm_1, data[0].toLatin1());
        tModule.flag_gsm_1 = 0;
    }
    if (temp[3] != "-") {
        data[0] = temp[3];
        strcpy(tModule.number_gsm_1, data[0].toLatin1());
    } else {
        data[0] = "";
        strcpy(tModule.number_gsm_1, data[0].toLatin1());
    }
    if (temp[4] != "-") {
        data[0] = temp[4];
        tModule.flag_status_active_gsm_1 = data[0].toInt();
        if (tModule.flag_status_active_gsm_1 == 0) {
            data[0] = "NOT ACTIVE";
            strcpy(tModule.status_gsm_1, data[0].toLatin1());
        } else if (tModule.flag_status_active_gsm_1 == 1) {
            data[0] = "ACTIVE";
            strcpy(tModule.status_gsm_1, data[0].toLatin1());
        }
    } else {
        data[0] = "0";
        tModule.flag_status_active_gsm_1 = data[0].toInt();
        data[0] = "NOT ACTIVE";
        strcpy(tModule.status_gsm_1, data[0].toLatin1());
    }
    if (temp[5] != "-") {
        data[0] = temp[5];
        strcpy(tModule.apn_gsm_1, data[0].toLatin1());
    } else {
        data[0] = temp[5];
        strcpy(tModule.apn_gsm_1, data[0].toLatin1());
    }
    if (temp[6] != "-") {
        data[0] = temp[6];
        strcpy(tModule.user_gsm_1, data[0].toLatin1());
    } else {
        data[0] = "";
        strcpy(tModule.user_gsm_1, data[0].toLatin1());
    }
    if (temp[7] != "-") {
        data[0] = temp[7];
        strcpy(tModule.passwd_gsm_1, data[0].toLatin1());
    } else {
        data[0] = "";
        strcpy(tModule.passwd_gsm_1, data[0].toLatin1());
    }
    if (temp[8] != "-") {
        data[0] = temp[8];
        strcpy(tModule.com_gsm_1, data[0].toLatin1());
        if (data[0] == "GSM") {
            tModule.flag_com_gsm_1 = 0;
        } else if (data[0] == "GPRS") {
            tModule.flag_com_gsm_1 = 1;
        }
    } else {
        data[0] = "";
        strcpy(tModule.com_gsm_1, data[0].toLatin1());
        tModule.flag_com_gsm_1 = 0;
    }

    temp = data[1].split(";");
    if (temp[1] != "-") {
        data[1] = temp[1];
        strcpy(tModule.device_name_gsm_2, data[1].toLatin1());
    } else {
        data[1] = "";
        strcpy(tModule.device_name_gsm_2, data[1].toLatin1());
    }
    if (temp[2] != "-") {
        data[1] = temp[2];
        strcpy(tModule.name_gsm_2, data[1].toLatin1());
        if (data[1] == "TELKOMSEL") {
            tModule.flag_gsm_2 = 0;
        } else if (data[1] == "INDOSAT") {
            tModule.flag_gsm_2 = 1;
        } else if (data[1] == "XL") {
            tModule.flag_gsm_2 = 2;
        } else if (data[1] == "3") {
            tModule.flag_gsm_2 = 3;
        }
    } else {
        data[1] = "";
        strcpy(tModule.name_gsm_2, data[1].toLatin1());
        tModule.flag_gsm_2 = 0;
    }
    if (temp[3] != "-") {
        data[1] = temp[3];
        strcpy(tModule.number_gsm_2, data[1].toLatin1());
    } else {
        data[1] = "";
        strcpy(tModule.number_gsm_2, data[1].toLatin1());
    }
    if (temp[4] != "-") {
        data[1] = temp[4];
        tModule.flag_status_active_gsm_2 = data[1].toInt();
        if (tModule.flag_status_active_gsm_2 == 0) {
            data[1] = "NOT ACTIVE";
            strcpy(tModule.status_gsm_2, data[1].toLatin1());
        } else if (tModule.flag_status_active_gsm_2 == 1) {
            data[1] = "ACTIVE";
            strcpy(tModule.status_gsm_2, data[1].toLatin1());
        }
    } else {
        data[1] = "0";
        tModule.flag_status_active_gsm_2 = data[1].toInt();
        data[1] = "NOT ACTIVE";
        strcpy(tModule.status_gsm_2, data[1].toLatin1());
    }
    if (temp[5] != "-") {
        data[1] = temp[5];
        strcpy(tModule.apn_gsm_2, data[1].toLatin1());
    } else {
        data[1] = "";
        strcpy(tModule.apn_gsm_2, data[1].toLatin1());
    }
    if (temp[6] != "-") {
        data[1] = temp[6];
        strcpy(tModule.user_gsm_2, data[1].toLatin1());
    } else {
        data[1] = "";
        strcpy(tModule.user_gsm_2, data[1].toLatin1());
    }
    if (temp[7] != "-") {
        data[1] = temp[7];
        strcpy(tModule.passwd_gsm_2, data[1].toLatin1());
    } else {
        data[1] = "";
        strcpy(tModule.passwd_gsm_2, data[1].toLatin1());
    }
    if (temp[8] != "-") {
        data[1] = temp[8];
        strcpy(tModule.com_gsm_2, data[1].toLatin1());
        if (data[1] == "GSM") {
            tModule.flag_com_gsm_2 = 0;
        } else if (data[1] == "GPRS") {
            tModule.flag_com_gsm_2 = 1;
        }
    } else {
        data[1] = "";
        strcpy(tModule.com_gsm_2, data[1].toLatin1());
        tModule.flag_com_gsm_2 = 0;
    }

    module mod;
    mod.update_communication(&tModule, Address_Module);
    this->setInterface(Address_Module);
}

void formModule::on_pbEditModule_clicked()
{
    faddModule = new form_addModule(this, false, Address_Module);
    faddModule->setWindowTitle("Edit Module");
    faddModule->setModal(true);

    faddModule->exec();

    if (faddModule->accept == 0) return;

    Address_Module = faddModule->currentFile;
    this->setInterface(Address_Module);
    this->setWindowTitle(
                Address_Module.mid(Address_Module.indexOf("m_")+2,
                                   Address_Module.indexOf(".ini")).remove(".ini"));

    struct t_module tModule;
    QString Request;
    mod.read_module(&tModule, Address_Module.prepend("m_").append(".ini"));
    Request.sprintf("set_env nama %s\r\n", tModule.module_name);
    Serial->write_data(Serial_Com, Request);
    this->delay(1000);
    Request.sprintf("set_env SN %s\r\n", tModule.serial_number);
    Serial->write_data(Serial_Com, Request);
    this->delay(1000);
}

void formModule::delay(int v_ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(v_ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
