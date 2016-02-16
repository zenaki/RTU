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

    int rowInput = 13;
    int rowOutput = 4;
    QString type_IO;

    this->ui->tabel_input->verticalHeader()->setHidden(true);
    this->ui->tabel_input->setColumnCount(6);
//    this->ui->tabel_input->setColumnWidth(0, 50);
    this->ui->tabel_input->setColumnWidth(1, 100);
    this->ui->tabel_input->setColumnWidth(2, 150);
    this->ui->tabel_input->setColumnWidth(3, 100);
//    this->ui->tabel_input->setColumnWidth(4, 100);
//    this->ui->tabel_input->setColumnWidth(5, 100);
    this->ui->tabel_input->setRowCount(rowInput);

    this->ui->tabel_output->verticalHeader()->setHidden(true);
    this->ui->tabel_output->setColumnCount(5);
    //    this->ui->tabel_output->setColumnWidth(0, 50);
        this->ui->tabel_output->setColumnWidth(1, 100);
        this->ui->tabel_output->setColumnWidth(2, 100);
        this->ui->tabel_output->setColumnWidth(3, 100);
    //    this->ui->tabel_output->setColumnWidth(4, 100);
    this->ui->tabel_output->setRowCount(rowOutput);

    for (int i = 0; i < rowInput; i++){
        name_input[i] = new QLineEdit(this);

        type_input[i] = new QComboBox(this);
        type_input[i]->addItem("RPM",1);
        type_input[i]->addItem("ON / OFF",2);
        type_input[i]->addItem("Push Button",3);
        type_input[i]->addItem("Flow - X",6);
        type_input[i]->addItem("RPM - RH",7);
        type_input[i]->addItem("Running Hours",8);
        type_input[i]->addItem("ON / OFF - RH",9);
        type_input[i]->addItem("Analog Monita",250);
        type_input[i]->addItem("Analog Running Hours",999);

        state_input[i] = new QComboBox(this);
        state_input[i]->addItem("NOT ACTIVE",0);
        state_input[i]->addItem("ACTIVE",1);

        calib_m[i] = new QLineEdit(this);
        calib_m[i]->setAlignment(Qt::AlignRight);

        calib_x[i] = new QLineEdit(this);
        calib_x[i]->setAlignment(Qt::AlignRight);
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

        name_input[i]->setText(list[(i*7)+2]);
        type_input[i]->setCurrentIndex(list[(i*7)+3].toInt());
        state_input[i]->setCurrentIndex(list[(i*7)+4].toInt());
        calib_m[i]->setText(list[(i*7)+5]);
        calib_x[i]->setText(list[(i*7)+6]);

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
        name_output[i]->setText(list[(i*6)+2]);
        type_output[i]->setText(list[(i*6)+3]);
        state_output[i]->setCurrentIndex(list[(i*6)+4].toInt());
        control[i]->setCurrentIndex(list[(i*6)+5].toInt());

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
    data[0].prepend("A;1;");
    strcpy(tModule.input_a1,data[0].toLatin1());
    data[1].prepend("A;2;");
    strcpy(tModule.input_a2,data[1].toLatin1());
    data[2].prepend("A;3;");
    strcpy(tModule.input_a3,data[2].toLatin1());
    data[3].prepend("A;4;");
    strcpy(tModule.input_a4,data[3].toLatin1());
    data[4].prepend("A;5;");
    strcpy(tModule.input_a5,data[4].toLatin1());
    data[5].prepend("A;6;");
    strcpy(tModule.input_a6,data[5].toLatin1());

    data[6].prepend("D;1;");
    strcpy(tModule.input_d1,data[6].toLatin1());
    data[7].prepend("D;2;");
    strcpy(tModule.input_d2,data[7].toLatin1());
    data[8].prepend("D;3;");
    strcpy(tModule.input_d3,data[8].toLatin1());
    data[9].prepend("D;4;");
    strcpy(tModule.input_d4,data[9].toLatin1());
    data[10].prepend("D;5");
    strcpy(tModule.input_d5,data[10].toLatin1());
    data[11].prepend("D;6;");
    strcpy(tModule.input_d6,data[11].toLatin1());
    data[12].prepend("D;7;");
    strcpy(tModule.input_d7,data[12].toLatin1());
    data[13].prepend("D;8;");
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
    data[0].prepend("R;1;");
    strcpy(tModule.output_r1,data[0].toLatin1());
    data[1].prepend("R;2;");
    strcpy(tModule.output_r2,data[1].toLatin1());
    data[2].prepend("R;3;");
    strcpy(tModule.output_r3,data[2].toLatin1());
    data[3].prepend("R;4;");
    strcpy(tModule.output_r4,data[3].toLatin1());

    module mod;
    mod.update_setting(&tModule, Address_Module);

    QMessageBox::information(this, "Success!!", "Setting Saved", 0, 0);
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
            Main->on_actionConnect_triggered();
        } else
        {
            Serial->write_data(Serial_Com, "\r\n");
            Serial->write_data(Serial_Com, "cek_env\r\n");
            Serial->write_data(Serial_Com, "set_env TEST_SELASA_16_PEBRUARI_2016\r\n");
            Serial->write_data(Serial_Com, "cek_env\r\n");
        }
}

void formModule::readData()
{
    str_data.append(Serial_Com->readAll());
    if (str_data.indexOf(NoSeri) > 0)
    {
        val_data = str_data.remove("\r").remove("\n").remove("(" + NoSeri + ")").split("*");
        this->Syncronization();
        qDebug() << str_data;
        str_data.clear();
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
        data[i] = val_data[i+15];
    }
    strcpy(tModule.output_r1,data[0].toLatin1());
    strcpy(tModule.output_r2,data[1].toLatin1());
    strcpy(tModule.output_r3,data[2].toLatin1());
    strcpy(tModule.output_r4,data[3].toLatin1());

    module mod;
    mod.update_setting(&tModule, Address_Module);
    this->setInterface(Address_Module);

    QMessageBox::information(this, "Success!!", "Syncronized ..", 0, 0);
}

void formModule::on_pushButton_clicked()
{
    faddModule = new form_addModule(this, false);
    faddModule->setWindowTitle("Edit Module");
    faddModule->setModal(true);

    faddModule->exec();

    if (faddModule->accept == 0) return;

    QString title;
    title.sprintf("%s", faddModule->ui->edit_module_name->text().toUtf8().data());

    module_name = work->editModule(Main->modelTree, Main->ui->treeView, title);
//    module_count++;
}
