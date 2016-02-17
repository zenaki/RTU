#include "formmodule.h"
#include "ui_formmodule.h"

#include <QDebug>

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
            type_input[i]->addItem("Analog Running Hours",999);
        } else
        {
            type_input[i]->addItem("RPM",1);
            type_input[i]->addItem("ON / OFF",2);
            type_input[i]->addItem("Push Button",3);
            type_input[i]->addItem("Flow - X",6);
            type_input[i]->addItem("RPM - RH",7);
            type_input[i]->addItem("Running Hours",8);
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
        if (list[(i*6)+3].toInt() == 999) {indx = 1;}
        if (list[(i*6)+3].toInt() == 1) {indx = 0;}
        if (list[(i*6)+3].toInt() == 2) {indx = 1;}
        if (list[(i*6)+3].toInt() == 3) {indx = 2;}
        if (list[(i*6)+3].toInt() == 6) {indx = 3;}
        if (list[(i*6)+3].toInt() == 7) {indx = 4;}
        if (list[(i*6)+3].toInt() == 8) {indx = 5;}
        if (list[(i*6)+3].toInt() == 9) {indx = 6;}
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
    modules.sprintf("%s", tModule.user_gsm_2);
    this->ui->user_2->setText(modules);
    modules.sprintf("%s", tModule.apn_gsm_1);
    this->ui->apn_1->setText(modules);
    modules.sprintf("%s", tModule.apn_gsm_2);
    this->ui->apn_2->setText(modules);
}

void formModule::on_pbSet_clicked()
{
    struct t_module tModule;
    QString data[16];
    QString Message;
    QString Request;

    if (Serial_Com->isOpen()) {
        if (!GetNoSeri.isEmpty()) {
            if (NoSeri == GetNoSeri) {
                for (int i = 0; i < ui->tabel_input->rowCount(); i++)
                {
                    if (i<6) {
                        Request.sprintf("set_kanal %d %.3f %.3f", i+1, calib_m[i]->text().toFloat(), calib_x[i]->text().toFloat());
                        Serial->write_data(Serial_Com, Request);
                    } else {
                        Request.sprintf("set_kanal %d %.3f %.3f", i-6+1, calib_m[i]->text().toFloat(), calib_x[i]->text().toFloat());
                        Serial->write_data(Serial_Com, Request);
                    }
                    Message = "On-Board";
                }
            } else {
                Message = "On-Local";
            }
        } else {
            Message = "On-Local";
        }
    } else {
        Message = "On-Local";
    }

    int indx;

    for (int i = 0; i < ui->tabel_input->rowCount(); i++)
    {
//        tModule.d_port[i].status_input = state_input[i]->currentIndex();
        tModule.d_port[i].calib_m = calib_m[i]->text().toFloat();
        tModule.d_port[i].calib_x = calib_x[i]->text().toFloat();

        if (i < 6) {
            if (type_input[i]->currentIndex() == 0) {indx = 250;}
            if (type_input[i]->currentIndex() == 1) {indx = 999;}
            tModule.d_port[i].type_input = indx;

            data[i].sprintf("A;%d;%d;%.3f;%.3f", i+1
                            , indx
                            , tModule.d_port[i].calib_m
                            , tModule.d_port[i].calib_x);
        } else {
            if (type_input[i]->currentIndex() == 0) {indx = 1;}
            if (type_input[i]->currentIndex() == 1) {indx = 2;}
            if (type_input[i]->currentIndex() == 2) {indx = 3;}
            if (type_input[i]->currentIndex() == 3) {indx = 6;}
            if (type_input[i]->currentIndex() == 4) {indx = 7;}
            if (type_input[i]->currentIndex() == 5) {indx = 8;}
            if (type_input[i]->currentIndex() == 6) {indx = 9;}
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

    Message.prepend("Setting ").append(" Saved");
    QMessageBox::information(this, "Success!!", Message, 0, 0);
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
    //    Serial->write_data(Serial_Com, "Test\r\n");
        if (!Serial_Com->isOpen())
        {
//            Main->on_actionConnect_triggered();
            QMessageBox::warning(this, "Serial Comunication !!", "Protocol is not open ..", 0, 0);
        } else
        {
            if (GetNoSeri.isEmpty() || GetNamaBoard.isEmpty()) {
                Serial->write_data(Serial_Com, "hmi_cek_env\r\n");
                Serial->write_data(Serial_Com, "hmi_sync\r\n");
            } else {
                Serial->write_data(Serial_Com, "hmi_sync\r\n");
            }
        }
}

void formModule::readData()
{
    str_data.append(Serial_Com->readAll());
    if (GetNoSeri.isEmpty() || GetNamaBoard.isEmpty()) {
        if (str_data.indexOf("\r\n") > 0) {
            val_data = str_data.remove("Rinjani$ ").remove("hmi_cek_env").remove("\r").remove("\n").split(";");
            GetNamaBoard = val_data[0];
            GetNoSeri = val_data[1];
//            qDebug() << str_data;
            val_data.clear();
            str_data.clear();
        }
    } else {
        if (str_data.indexOf("(X)") > 0)
        {
            val_data = str_data.remove("Rinjani$ ").remove("hmi_sync").remove("\r").remove("\n").remove("(X)").split("*");
            this->Syncronization();
//            qDebug() << str_data;
            str_data.clear();
        }
    }
}

void formModule::Syncronization()
{
    struct t_module tModule;
    QString data[16];
    for (int i = 0; i < ui->tabel_input->rowCount(); i++)
    {
        data[i] = val_data[i];
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
        data[i] = val_data[i+14];
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
    this->setInterface(Address_Module);

    QMessageBox::information(this, "Success!!", "Setting Syncronized ..", 0, 0);
}

void formModule::on_pbEditModule_clicked()
{
    faddModule = new form_addModule(this, false, Address_Module);
    faddModule->setWindowTitle("Edit Module");
    faddModule->setModal(true);

    faddModule->exec();

    if (faddModule->accept == 0) return;

    QString title;
    title.sprintf("%s", faddModule->ui->edit_module_name->text().toUtf8().data());

    module_name = work->editModule(Main->modelTree, Main->ui->treeView, title);
//    module_count++;
}
