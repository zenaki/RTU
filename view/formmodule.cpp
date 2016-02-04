#include "formmodule.h"
#include "ui_formmodule.h"

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
        type_input[i] = new QLineEdit(this);
        calib_m[i] = new QLineEdit(this);
        calib_x[i] = new QLineEdit(this);

        state_input[i] = new QComboBox(this);
        state_input[i]->addItem("NOT ACTIVE");
        state_input[i]->addItem("ACTIVE");
    }

    QString str_input_a1 = tModule.input_a1;
    QStringList list_input_a1 = str_input_a1.split(';');

    for(int i = 0; i < rowInput; i++){
        if (i < 6) {
            type_IO = " - Analog";
        } else {
            type_IO = " - Digital";
        }
        type_IO.prepend(QString::number(i+1));


//        name_input[i]->setText(list_input_a[i]][0]);
//        type_input[i]->setText(list_input_a[i]][1]);
//        state_input[i]->setCurrentIndex(list_input_a[i]][2].toInt());
//        calib_mi1]->setText(list_input_a[i]][3]);
//        calib_x[i]->setText(list_input_a[i]][4]);

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
        state_output[i]->addItem("ACTIVE");
        state_output[i]->addItem("NOT ACTIVE");

        control[i] = new QComboBox(this);
        control[i]->addItem("LOGIC");
        control[i]->addItem("SCHEDULER");
    }

    for(int i = 0; i < rowOutput; i++){
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
        strcpy(tModule.d_port[i].type_input, type_input[i]->text().toLatin1());
        tModule.d_port[i].status_input = state_input[i]->currentIndex();
        tModule.d_port[i].calib_m = calib_m[i]->text().toFloat();
        tModule.d_port[i].calib_x = calib_x[i]->text().toFloat();

        data[i].sprintf("%s;%s;%d;%.2f;%.2f"
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
}

void formModule::on_pbEdit_clicked()
{
    this->ui->opt_1->setEnabled(true);
    this->ui->device_1->setEnabled(true);
    this->ui->status_1->setEnabled(true);
    this->ui->com_1->setEnabled(true);
    this->ui->number_1->setEnabled(true);

    this->ui->opt_2->setEnabled(true);
    this->ui->device_2->setEnabled(true);
    this->ui->status_2->setEnabled(true);
    this->ui->com_2->setEnabled(true);
    this->ui->number_2->setEnabled(true);

    this->ui->pbEdit->setHidden(true);
    this->ui->pbSave->setHidden(false);
    this->ui->pbCancel->setHidden(false);
}

void formModule::on_pbSave_clicked()
{
    this->ui->opt_1->setEnabled(false);
    this->ui->device_1->setEnabled(false);
    this->ui->status_1->setEnabled(false);
    this->ui->com_1->setEnabled(false);
    this->ui->number_1->setEnabled(false);

    this->ui->opt_2->setEnabled(false);
    this->ui->device_2->setEnabled(false);
    this->ui->status_2->setEnabled(false);
    this->ui->com_2->setEnabled(false);
    this->ui->number_2->setEnabled(false);

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

    this->ui->opt_1->setEnabled(false);
    this->ui->device_1->setEnabled(false);
    this->ui->status_1->setEnabled(false);
    this->ui->com_1->setEnabled(false);
    this->ui->number_1->setEnabled(false);

    this->ui->opt_2->setEnabled(false);
    this->ui->device_2->setEnabled(false);
    this->ui->status_2->setEnabled(false);
    this->ui->com_2->setEnabled(false);
    this->ui->number_2->setEnabled(false);

    this->ui->pbEdit->setHidden(false);
    this->ui->pbSave->setHidden(true);
    this->ui->pbCancel->setHidden(true);
}
