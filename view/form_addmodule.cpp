#include "form_addmodule.h"
#include "ui_form_addmodule.h"

form_addModule::form_addModule(QWidget *parent, bool create, QString address, int index) :
    QDialog(parent),
    ui(new Ui::form_addModule)
{
    ui->setupUi(this);

    this->ui->edit_module_name->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));
    this->ui->edit_sn->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));
    this->ui->edit_server_address->setInputMask("999.999.999.999");
    this->ui->edit_file_address->setValidator(new QRegExpValidator(QRegExp("^\\S{1,20}$"),this));

    this->ui->edit_devicename_1->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));
    this->ui->edit_devicename_2->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));
    this->ui->edit_number_1->setValidator(new QRegExpValidator(QRegExp("^\\d{1,15}$"),this));
    this->ui->edit_number_2->setValidator(new QRegExpValidator(QRegExp("^\\d{1,15}$"),this));
    this->ui->edit_apn_1->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));
    this->ui->edit_apn_2->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));
    this->ui->edit_user_1->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));
    this->ui->edit_user_2->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));
    this->ui->edit_passwd_1->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));
    this->ui->edit_passwd_2->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));

    edit = !create;
    accept = 0;

    if (edit) {
        struct t_module tModule;
        mod.read_module(&tModule, address);
        currentFile = address;
        QString modules;

        this->on_ck_flag_active_gsm_2_clicked(tModule.flag_dual_gsm);
        this->on_cb_com_1_currentIndexChanged(tModule.flag_com_gsm_1);
        this->on_cb_com_2_currentIndexChanged(tModule.flag_com_gsm_2);

//        this->ui->edit_module_name->setEnabled(false);
        modules.sprintf("%s", tModule.module_name);
        this->ui->edit_module_name->setText(modules);
        currentName = modules;
        modules.sprintf("%s", tModule.serial_number);
        this->ui->edit_sn->setText(modules);
        if (tModule.flag_dual_gsm == 1) {
            this->ui->ck_flag_active_gsm_2->setChecked(true);
        }
        modules.sprintf("%s", tModule.ip_address);
        this->ui->edit_ip_address->setText(modules);
        modules.sprintf("%s", tModule.server_address);
        this->ui->edit_server_address->setText(modules);
        modules.sprintf("%s", tModule.file_address);
        this->ui->edit_file_address->setText(modules);
        this->ui->cb_webclient->setCurrentIndex(tModule.flag_webclient);
        this->ui->spin_interval->setValue(tModule.interval);

        this->ui->cb_operator_1->setCurrentIndex(tModule.flag_gsm_1);
        modules.sprintf("%s", tModule.device_name_gsm_1);
        this->ui->edit_devicename_1->setText(modules);
        this->ui->cb_status_1->setCurrentIndex(tModule.flag_status_active_gsm_1);
        this->ui->cb_com_1->setCurrentIndex(tModule.flag_com_gsm_1);
        modules.sprintf("%s", tModule.number_gsm_1);
        this->ui->edit_number_1->setText(modules);
        modules.sprintf("%s", tModule.apn_gsm_1);
        this->ui->edit_apn_1->setText(modules);
        modules.sprintf("%s", tModule.user_gsm_1);
        this->ui->edit_user_1->setText(modules);
        modules.sprintf("%s", tModule.passwd_gsm_1);
        this->ui->edit_passwd_1->setText(modules);

        this->ui->cb_operator_2->setCurrentIndex(tModule.flag_gsm_2);
        modules.sprintf("%s", tModule.device_name_gsm_2);
        this->ui->edit_devicename_2->setText(modules);
        this->ui->cb_status_2->setCurrentIndex(tModule.flag_status_active_gsm_2);
        this->ui->cb_com_2->setCurrentIndex(tModule.flag_com_gsm_2);
        modules.sprintf("%s", tModule.number_gsm_2);
        this->ui->edit_number_2->setText(modules);
        modules.sprintf("%s", tModule.apn_gsm_2);
        this->ui->edit_apn_2->setText(modules);
        modules.sprintf("%s", tModule.user_gsm_2);
        this->ui->edit_user_2->setText(modules);
        modules.sprintf("%s", tModule.passwd_gsm_2);
        this->ui->edit_passwd_2->setText(modules);

        if (index == 1) {
//            this->ui->edit_module_name->setEnabled(true);
//            this->ui->edit_sn->setEnabled(true);
//            this->ui->ck_flag_active_gsm_2->setHidden(true);

//            this->setFixedWidth(640);
//            this->setFixedHeight(445);
//            this->ui->gbCom->setGeometry(20,70,601,311);
//            this->ui->buttonBox->setGeometry(14,405,601,27);
//            this->ui->gbCom->setHidden(false);
//            this->ui->gbEnv->setHidden(true);

            this->ui->edit_module_name->setEnabled(true);
            this->ui->edit_sn->setEnabled(true);
            this->ui->ck_flag_active_gsm_2->setHidden(false);

            this->setFixedWidth(640);
            this->setFixedHeight(654);

            this->ui->gbCom->setHidden(false);
            this->ui->gbEnv->setHidden(false);
        } else if (index == 2) {
            this->ui->edit_module_name->setEnabled(false);
            this->ui->edit_sn->setEnabled(false);
            this->ui->ck_flag_active_gsm_2->setHidden(false);

            this->setFixedWidth(640);
            this->setFixedHeight(445);
            this->ui->gbCom->setGeometry(20,70,601,311);
            this->ui->buttonBox->setGeometry(14,405,601,27);
            this->ui->gbCom->setHidden(false);
            this->ui->gbEnv->setHidden(true);
        } else if (index == 3) {
            this->ui->edit_module_name->setEnabled(true);
            this->ui->edit_sn->setEnabled(true);
            this->ui->ck_flag_active_gsm_2->setHidden(true);
            this->ui->gbCom->setHidden(true);

            this->ui->gbEnv->setGeometry(20,70,341,211);
            this->ui->buttonBox->setGeometry(14,285,341,27);
            this->setFixedWidth(380);
            this->setFixedHeight(330);

            this->ui->gbEnv->setHidden(false);
        }
    } else {
        this->ui->edit_module_name->setEnabled(true);
        this->ui->edit_sn->setEnabled(true);
        this->ui->ck_flag_active_gsm_2->setHidden(false);

        this->setFixedWidth(640);
        this->setFixedHeight(654);

        this->ui->gbCom->setHidden(false);
        this->ui->gbEnv->setHidden(false);
    }
    this->enabledButton();
    connect(ui->edit_module_name,SIGNAL(textChanged(const QString &)),this,SLOT(enabledButton()));
    connect(ui->edit_sn,SIGNAL(textChanged(const QString &)),this,SLOT(enabledButton()));

    connect(ui->edit_devicename_1,SIGNAL(textChanged(const QString &)),this,SLOT(enabledButton()));
    connect(ui->edit_number_1,SIGNAL(textChanged(const QString &)),this,SLOT(enabledButton()));

    connect(ui->edit_devicename_2,SIGNAL(textChanged(const QString &)),this,SLOT(enabledButton()));
    connect(ui->edit_number_2,SIGNAL(textChanged(const QString &)),this,SLOT(enabledButton()));
}

form_addModule::~form_addModule()
{
    accept = 0;
    delete ui;
}

void form_addModule::on_buttonBox_accepted()
{
    if (!active_button) {
        QMessageBox::critical(this, tr("Form Critical!"), tr("Please complete this form !!", 0,0));
    }
    struct t_module tModule;
    QString newFiles;
    mod.read_module(&tModule, currentFile);
    strcpy(tModule.module_name, this->ui->edit_module_name->text().toLatin1());
    newFiles.sprintf("m_%s.dbe", tModule.module_name);

    tModule.flag_active = 1;
    strcpy(tModule.module_name, this->ui->edit_module_name->text().toLatin1());
    strcpy(tModule.serial_number, this->ui->edit_sn->text().toLatin1());

    strcpy(tModule.ip_address, this->ui->edit_ip_address->text().toLatin1());
    strcpy(tModule.server_address, this->ui->edit_server_address->text().toLatin1());
    strcpy(tModule.file_address, this->ui->edit_file_address->text().toLatin1());
    tModule.flag_webclient = this->ui->cb_webclient->currentIndex();
    strcpy(tModule.status_webclient, this->ui->cb_webclient->currentText().toLatin1());
    tModule.interval = this->ui->spin_interval->value();

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
    if (tModule.flag_com_gsm_1 == 0)
    {
        strcpy(tModule.user_gsm_1, "-");
        strcpy(tModule.apn_gsm_1, "-");
        strcpy(tModule.passwd_gsm_1, "-");
    } else if (tModule.flag_com_gsm_1 == 1)
    {
        strcpy(tModule.user_gsm_1, this->ui->edit_user_1->text().toLatin1());
        strcpy(tModule.apn_gsm_1, this->ui->edit_apn_1->text().toLatin1());
        strcpy(tModule.passwd_gsm_1, this->ui->edit_passwd_1->text().toLatin1());
    }

    /** GSM_2 **/
    if (tModule.flag_dual_gsm == 1) {
        tModule.flag_gsm_2 = this->ui->cb_operator_2->currentIndex();
        strcpy(tModule.name_gsm_2, this->ui->cb_operator_2->currentText().toLatin1());

        strcpy(tModule.device_name_gsm_2, this->ui->edit_devicename_2->text().toLatin1());

        tModule.flag_status_active_gsm_2 = this->ui->cb_status_2->currentIndex();
        strcpy(tModule.status_gsm_2, this->ui->cb_status_2->currentText().toLatin1());

        tModule.flag_com_gsm_2 = this->ui->cb_com_2->currentIndex();
        strcpy(tModule.com_gsm_2, this->ui->cb_com_2->currentText().toLatin1());

        strcpy(tModule.number_gsm_2, this->ui->edit_number_2->text().toLatin1());
        if (tModule.flag_com_gsm_2 == 0) {
            strcpy(tModule.user_gsm_2, "-");
            strcpy(tModule.apn_gsm_2, "-");
            strcpy(tModule.passwd_gsm_2, "-");
        } else if (tModule.flag_com_gsm_2 == 1) {
            strcpy(tModule.user_gsm_2, this->ui->edit_user_2->text().toLatin1());
            strcpy(tModule.apn_gsm_2, this->ui->edit_apn_2->text().toLatin1());
            strcpy(tModule.passwd_gsm_2, this->ui->edit_passwd_2->text().toLatin1());
        }
    } else {
        tModule.flag_gsm_2 = 0;
        strcpy(tModule.name_gsm_2,"-");
        strcpy(tModule.device_name_gsm_2,"-");
        tModule.flag_status_active_gsm_2 = 0;
        strcpy(tModule.status_gsm_2,"NOT ACTIVE");
        tModule.flag_com_gsm_2 = 0;
        strcpy(tModule.com_gsm_2,"GSM");
        strcpy(tModule.number_gsm_2,"-");
        strcpy(tModule.user_gsm_2, "-");
        strcpy(tModule.apn_gsm_2, "-");
        strcpy(tModule.passwd_gsm_2, "-");
    }

    /** ----------------------------- WRITE ---------------------------- **/
    bool cek = false;
    QDir path("data/module");
    QStringList files = path.entryList(QDir::Files);

    newFiles.sprintf("m_%s.dbe", tModule.module_name);

    if (newFiles.indexOf(" ") > 0) {
        accept = 0;
        QMessageBox::information(this, tr("Form Information"), tr("Should not use spaces ..", 0,0));
        return;
    }

    /* cek apakah nama module sudah dipakai atau belum */
    for(int i = 0; i < files.count(); i++){
        if(newFiles == QString(files.at(i))) {
            cek = true;
            break;
        } else {
            cek = false;
        }
    }
    if (newFiles == currentName.prepend("m_").append(".dbe")) cek = false;

    if (cek) {
        accept = 0;
        QMessageBox::information(this, tr("Form Information"), tr("Module name already in use ..", 0,0));
        return;
    } else {
        if (edit) {
            QFile CurrFile(currentFile);
            CurrFile.remove();
            QString CurrNameFile = CurrFile.fileName();
            CurrFile.rename(CurrNameFile, newFiles);
//            CurrFile.close();

            mod.write_module(&tModule);
            QString pth; pth.sprintf("data/module/m_%s.dbe",tModule.module_name);
            cryp code; code.encryp(pth);

//            mod.update_module(&tModule, newFiles.prepend("data/module/"));
//            mod.update_communication(&tModule, newFiles.prepend("data/module/"));
            accept = 1;
            currentFile = newFiles.prepend("data/module/");
            close();
        } else {
            /** INPUT **/
            QString temp;
            int j = 0;
            for (int i = 1; i < tModule.jml_input_digital + tModule.jml_input_analog; i++) {
                if (i < 7 && i > 10) {
                    temp.sprintf("A;%d;0;0.000;0.000", i);
                    tModule.Input[j] = temp;
                    tModule.InputName[j] = "";
                    j++;
                }
            }

            /** OUTPUT **/
            for (int i = 1; i < tModule.jml_output; i++) {
                temp.sprintf("R;%d;0;0.000;0.000", i);
                tModule.Output[i-1] = temp;
                tModule.OutputName[i-1] = "";
            }

            mod.write_module(&tModule);
            QString pth; pth.sprintf("data/module/m_%s.dbe",tModule.module_name);
            cryp code; code.encryp(pth);

            accept = 1;

            close();
        }
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
    ui->label_17->setEnabled(checked);
    ui->label_18->setEnabled(checked);
    ui->label_20->setEnabled(checked);

    ui->cb_operator_2->setEnabled(checked);
    ui->edit_devicename_2->setEnabled(checked);
    ui->cb_status_2->setEnabled(checked);
    ui->cb_com_2->setEnabled(checked);
    ui->cb_com_2->setCurrentIndex(0);
    ui->edit_number_2->setEnabled(checked);
}

void form_addModule::on_cb_com_1_currentIndexChanged(int index)
{
    if (index == 0) {
        this->ui->edit_user_1->setEnabled(false);
        this->ui->edit_apn_1->setEnabled(false);
        this->ui->edit_passwd_1->setEnabled(false);
    } else if (index == 1) {
        this->ui->edit_user_1->setEnabled(true);
        this->ui->edit_apn_1->setEnabled(true);
        this->ui->edit_passwd_1->setEnabled(true);
    }
}

void form_addModule::on_cb_com_2_currentIndexChanged(int index)
{
    if (index == 0) {
        this->ui->edit_user_2->setEnabled(false);
        this->ui->edit_apn_2->setEnabled(false);
        this->ui->edit_passwd_2->setEnabled(false);
    } else if (index == 1) {
        this->ui->edit_user_2->setEnabled(true);
        this->ui->edit_apn_2->setEnabled(true);
        this->ui->edit_passwd_2->setEnabled(true);
    }
}

void form_addModule::enabledButton()
{
    if (!ui->edit_module_name->text().isEmpty() ||
            !ui->edit_sn->text().isEmpty() ||
            !ui->edit_devicename_1->text().isEmpty() ||
            !ui->edit_number_1->text().isEmpty()) {
        if (ui->ck_flag_active_gsm_2->isChecked()) {
            if (!ui->edit_devicename_2->text().isEmpty() ||
                    !ui->edit_number_2->text().isEmpty()) {
                active_button = true;
            } else {
                active_button = false;
            }
        } else {
            active_button = true;
        }
    } else {
        active_button = false;
    }
}
