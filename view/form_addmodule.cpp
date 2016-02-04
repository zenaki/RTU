#include "form_addmodule.h"
#include "ui_form_addmodule.h"

form_addModule::form_addModule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_addModule)
{
    ui->setupUi(this);

    accept = 0;
}

form_addModule::~form_addModule()
{
    accept = 0;
    delete ui;
}

void form_addModule::on_buttonBox_accepted()
{
    struct t_module tModule;

    tModule.flag_active = 1;
    strcpy(tModule.module_name, this->ui->edit_module_name->text().toLatin1());
    strcpy(tModule.serial_number, this->ui->edit_sn->text().toLatin1());

    if(this->ui->ck_flag_active_gsm_2->isChecked()) tModule.flag_dual_gsm = 1;
    else tModule.flag_dual_gsm = 0;

    /** GSM_1 **/
    tModule.flag_gsm_1 = this->ui->cb_operator_1->currentIndex();
    strcpy(tModule.name_gsm_1, this->ui->cb_operator_1->currentText().toLatin1());

    strcpy(tModule.device_name_gsm_1, this->ui->edit_devicename_1->text().toLatin1());

    tModule.flag_status_active_gsm_1 = this->ui->cb_status_1->currentIndex();
    strcpy(tModule.status_gsm_1, this->ui->cb_status_1->currentText().toLatin1());

    tModule.flag_com_gsm_1 = this->ui->cb_com_1->currentIndex();
    strcpy(tModule.com_gsm_1, this->ui->cb_com_1->currentText().toLatin1());

    strcpy(tModule.number_gsm_1, this->ui->edit_number_1->text().toLatin1());

    /** GSM_2 **/
    tModule.flag_gsm_2 = this->ui->cb_operator_2->currentIndex();
    strcpy(tModule.name_gsm_2, this->ui->cb_operator_2->currentText().toLatin1());

    strcpy(tModule.device_name_gsm_2, this->ui->edit_devicename_2->text().toLatin1());

    tModule.flag_status_active_gsm_2 = this->ui->cb_status_2->currentIndex();
    strcpy(tModule.status_gsm_2, this->ui->cb_status_2->currentText().toLatin1());

    tModule.flag_com_gsm_2 = this->ui->cb_com_2->currentIndex();
    strcpy(tModule.com_gsm_2, this->ui->cb_com_2->currentText().toLatin1());

    strcpy(tModule.number_gsm_2, this->ui->edit_number_2->text().toLatin1());

    strcpy(tModule.input_a1, "");
    strcpy(tModule.input_a2, "");
    strcpy(tModule.input_a3, "");
    strcpy(tModule.input_a4, "");
    strcpy(tModule.input_a5, "");
    strcpy(tModule.input_a6, "");

    strcpy(tModule.input_d1, "");
    strcpy(tModule.input_d2, "");
    strcpy(tModule.input_d3, "");
    strcpy(tModule.input_d4, "");
    strcpy(tModule.input_d5, "");
    strcpy(tModule.input_d6, "");
    strcpy(tModule.input_d7, "");
    strcpy(tModule.input_d8, "");

    strcpy(tModule.output_r1, "");
    strcpy(tModule.output_r2, "");
    strcpy(tModule.output_r3, "");
    strcpy(tModule.output_r4, "");

    /** ----------------------------- WRITE ---------------------------- **/
    bool cek = false;
    QDir path("data/module");
    QStringList files = path.entryList(QDir::Files);

    QString newFiles;
    newFiles.sprintf("m_%s.ini", tModule.module_name);

    /* cek apakah nama module sudah dipakai atau belum */
    for(int i = 0; i < files.count(); i++){
        if(newFiles == QString(files.at(i))) cek = true;
    }

    if (cek) {
        accept = 0;
        QMessageBox::warning(this, tr("Warning!"), tr("Nama Module sudah terpakai!", 0,0));
        return;
    }
    else {
        mod.write_module(&tModule);
        accept = 1;

        close();
    }
}

void form_addModule::on_buttonBox_rejected()
{
    accept = 0;
    close();
}

void form_addModule::on_ck_flag_active_gsm_2_clicked(bool checked)
{
    if(checked) flag_gsm_2_active = 1;
    else flag_gsm_2_active = 0;

    ui->label_6->setEnabled(checked);
    ui->label_7->setEnabled(checked);
    ui->label_8->setEnabled(checked);
    ui->label_9->setEnabled(checked);
    ui->label_10->setEnabled(checked);

    ui->cb_operator_2->setEnabled(checked);
    ui->edit_devicename_2->setEnabled(checked);
    ui->cb_status_2->setEnabled(checked);
    ui->cb_com_2->setEnabled(checked);
    ui->edit_number_2->setEnabled(checked);
}
