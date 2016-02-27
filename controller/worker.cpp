#include "worker.h"

worker::worker()
{

}

QString worker::newModule(QStandardItemModel *tree, QTreeView *treeView, QString title){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.ini", title.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    modules.sprintf("%s", tModule.module_name);
//    modules.sprintf("m_%s.ini", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::editModule(QStandardItemModel *tree, QTreeView *treeView, QString title){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.ini", title.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    modules.sprintf("%s", tModule.module_name);
//    modules.sprintf("m_%s.ini", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::loadModule(QStandardItemModel *tree, QTreeView *treeView, QString address, QString NewName){
    struct t_module tModule;

    mod.read_module(&tModule, address);

    tModule.flag_active = 1;

    if (!NewName.isEmpty()) {
        strcpy(tModule.module_name, NewName.toLatin1());
    }
    mod.write_module(&tModule);

    QString modules;
    modules.sprintf("%s", tModule.module_name);
//    modules.sprintf("m_%s.ini", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::checkModule(QString address){
    struct t_module tModule;

    mod.read_module(&tModule, address);

    QString modules;
    modules.sprintf("m_%s.ini", tModule.module_name);
    return modules;
}

QString worker::check_statusModule(QString address){
    struct t_module tModule;

    address.sprintf("data/module/%s", address.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    if(tModule.flag_active){
        modules.sprintf("m_%s.ini", tModule.module_name);
        return modules;
    }
    return "none";
}

void worker::showModule(QWidget *parent, QMdiArea *mdiArea, QString module, QSerialPort *SerialPort){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.ini", module.toUtf8().data());
    mod.read_module(&tModule, address);


    formModule *fModule;

    fModule = new formModule(parent, address, SerialPort);
    fModule->setModal(true);
    fModule->setWindowTitle(tModule.module_name);
//    fModule->setMaximumWidth(700);

    mdiArea->addSubWindow(fModule, 0);

    fModule->exec();

}

bool worker::checkIfmodule(QString name){
    /** ----------------------------- WRITE ---------------------------- **/
    bool cek = false;
    QDir path("data/module");
    QStringList files = path.entryList(QDir::Files);

    QString currFiles;
    currFiles.sprintf("m_%s.ini", name.toUtf8().data());

    for(int i = 0; i < files.count(); i++){
        if(currFiles == QString(files.at(i))) cek = true;
    }

//    std::string sub = name.toStdString();
//    ext = QString::fromStdString(sub.substr(index_max-3, index_max));

//    if(ext == ".ini") return true;
//    else return false;

    return cek;
}

bool worker::state_of_module(int num, QString newModule, QString *existModule){
    bool cek;
    int  ceknt = num+1;
//    QString currModule;
    existModule->prepend("m_").append(".ini");

    for(int n = 0; n < ceknt; n++){
//        currModule = existModule->at(n);
//        currModule.prepend("m_").append(".ini");
        if(newModule != existModule[n]){
            cek = true;
        }
        else{
            cek = false;
            return cek;
        }
    }

    return cek;
}

void worker::Get_ENV(struct t_module *tModule, QStringList data)
{
    QString temp;

    temp = data.at(0);
    strcpy(tModule->module_name, temp.toUtf8().data());
    temp = data.at(1);
    strcpy(tModule->serial_number, temp.toUtf8().data());
}

void worker::Get_IO(struct t_module *tModule, QStringList data)
{
    QString temp;

    temp = data.at(0);
    strcpy(tModule->input_d1, temp.toUtf8().data());
    temp = data.at(1);
    strcpy(tModule->input_d2, temp.toUtf8().data());
    temp = data.at(2);
    strcpy(tModule->input_d3, temp.toUtf8().data());
    temp = data.at(3);
    strcpy(tModule->input_d4, temp.toUtf8().data());
    temp = data.at(4);
    strcpy(tModule->input_d5, temp.toUtf8().data());
    temp = data.at(5);
    strcpy(tModule->input_d6, temp.toUtf8().data());
    temp = data.at(6);
    strcpy(tModule->input_d7, temp.toUtf8().data());

    temp = data.at(7);
    strcpy(tModule->input_a1, temp.toUtf8().data());
    temp = data.at(8);
    strcpy(tModule->input_a2, temp.toUtf8().data());
    temp = data.at(9);
    strcpy(tModule->input_a3, temp.toUtf8().data());
    temp = data.at(10);
    strcpy(tModule->input_a4, temp.toUtf8().data());
    temp = data.at(11);
    strcpy(tModule->input_a5, temp.toUtf8().data());
    temp = data.at(12);
    strcpy(tModule->input_a6, temp.toUtf8().data());

    temp = data.at(13);
    strcpy(tModule->output_r1, temp.toUtf8().data());
    temp = data.at(14);
    strcpy(tModule->output_r2, temp.toUtf8().data());
}

void worker::Get_SIM(struct t_module *tModule, QStringList data)
{
    QString temp;

    QString str_sim_1 = data.at(0);
    QString str_sim_2 = data.at(1);

    QStringList list_sim_1 = str_sim_1.split(";");
    QStringList list_sim_2 = str_sim_2.split(";");

    /** MODUlE **/
    tModule->flag_active = 1;
    if (list_sim_2.at(3) != "-") {tModule->flag_dual_gsm = 1;}
    else {tModule->flag_dual_gsm = 0;}

    /** GSM_1 **/
    temp = list_sim_1.at(1);
    if (temp == "-") {
        strcpy(tModule->device_name_gsm_1, "");
    } else {
        strcpy(tModule->device_name_gsm_1, temp.toUtf8().data());
    }
    temp = list_sim_1.at(2);
    if (temp == "-") {
        strcpy(tModule->name_gsm_1, "");
        tModule->flag_gsm_1 = 0;
    } else {
        strcpy(tModule->name_gsm_1, temp.toUtf8().data());
        if (temp == "TELKOMSEL") {
            tModule->flag_gsm_1 = 0;
        } else if (temp == "INDOSAT") {
            tModule->flag_gsm_1 = 1;
        } else if (temp == "XL") {
            tModule->flag_gsm_1 = 2;
        } else if (temp == "3") {
            tModule->flag_gsm_1 = 3;
        }
    }
    temp = list_sim_1.at(3);
    if (temp == "-") {
        strcpy(tModule->number_gsm_1, "");
    } else {
        strcpy(tModule->number_gsm_1, temp.toUtf8().data());
    }
    temp = list_sim_1.at(4);
    if (temp == "0") {
        tModule->flag_status_active_gsm_1 = temp.toInt();
        temp = "NOT ACTIVE";
        strcpy(tModule->status_gsm_1, temp.toUtf8().data());
    } else if (temp == "1") {
        tModule->flag_status_active_gsm_1 = temp.toInt();
        temp = "ACTIVE";
        strcpy(tModule->status_gsm_1, temp.toUtf8().data());
    }
    temp = list_sim_1.at(8);
    if (temp == "GSM") {
        temp = "SMS";
        strcpy(tModule->com_gsm_1, temp.toUtf8().data());
        tModule->flag_com_gsm_1 = 0;
    } else if (temp == "GPRS") {
        strcpy(tModule->com_gsm_1, temp.toUtf8().data());
        tModule->flag_com_gsm_1 = 1;
    } else {
        strcpy(tModule->com_gsm_1, "");
        tModule->flag_com_gsm_1 = 0;
    }
    if (tModule->flag_com_gsm_1 == 0) {
        temp = "";
        strcpy(tModule->apn_gsm_1, temp.toUtf8().data());
        strcpy(tModule->user_gsm_1, temp.toUtf8().data());
        strcpy(tModule->passwd_gsm_1, temp.toUtf8().data());
    } else if (tModule->flag_com_gsm_1 == 1) {
        temp = list_sim_1.at(5);
        if (temp == "-") {
            strcpy(tModule->apn_gsm_1, "");
        } else {
            strcpy(tModule->apn_gsm_1, temp.toUtf8().data());
        }
        temp = list_sim_1.at(6);
        if (temp == "-") {
            strcpy(tModule->user_gsm_1, "");
        } else {
            strcpy(tModule->user_gsm_1, temp.toUtf8().data());
        }
        temp = list_sim_1.at(7);
        if (temp == "-") {
            strcpy(tModule->passwd_gsm_1, "");
        } else {
            strcpy(tModule->passwd_gsm_1, temp.toUtf8().data());
        }
    }

    /** GSM_2 **/
    if (tModule->flag_dual_gsm == 0) {
        strcpy(tModule->device_name_gsm_2, "");
        strcpy(tModule->name_gsm_2, "");
        tModule->flag_gsm_2 = 0;
        strcpy(tModule->number_gsm_2, "");
        tModule->flag_status_active_gsm_2 = 0;
        strcpy(tModule->status_gsm_2, "");
        strcpy(tModule->com_gsm_2, "");
        tModule->flag_com_gsm_2 = 0;
        strcpy(tModule->apn_gsm_2, "");
        strcpy(tModule->user_gsm_2, "");
        strcpy(tModule->passwd_gsm_2, "");
    } else if (tModule->flag_dual_gsm == 1) {
        temp = list_sim_2.at(1);
        if (temp == "-") {
            strcpy(tModule->device_name_gsm_2, "");
        } else {
            strcpy(tModule->device_name_gsm_2, temp.toUtf8().data());
        }
        temp = list_sim_2.at(2);
        if (temp == "-") {
            strcpy(tModule->name_gsm_2, "");
            tModule->flag_gsm_2 = 0;
        } else {
            strcpy(tModule->name_gsm_2, temp.toUtf8().data());
            if (temp == "TELKOMSEL") {
                tModule->flag_gsm_2 = 0;
            } else if (temp == "INDOSAT") {
                tModule->flag_gsm_2 = 1;
            } else if (temp == "XL") {
                tModule->flag_gsm_2 = 2;
            } else if (temp == "3") {
                tModule->flag_gsm_2 = 3;
            }
        }
        temp = list_sim_2.at(3);
        if (temp == "-") {
            strcpy(tModule->number_gsm_2, "");
        } else {
            strcpy(tModule->number_gsm_2, temp.toUtf8().data());
        }
        temp = list_sim_2.at(4);
        if (temp == "0") {
            tModule->flag_status_active_gsm_2 = temp.toInt();
            temp = "NOT ACTIVE";
            strcpy(tModule->status_gsm_2, temp.toUtf8().data());
        } else if (temp == "1") {
            tModule->flag_status_active_gsm_2 = temp.toInt();
            temp = "ACTIVE";
            strcpy(tModule->status_gsm_2, temp.toUtf8().data());
        }
        temp = list_sim_2.at(8);
        if (temp == "GSM") {
            temp = "SMS";
            strcpy(tModule->com_gsm_2, temp.toUtf8().data());
            tModule->flag_com_gsm_2 = 0;
        } else if (temp == "GPRS") {
            strcpy(tModule->com_gsm_2, temp.toUtf8().data());
            tModule->flag_com_gsm_2 = 1;
        } else {
            strcpy(tModule->com_gsm_2, "");
            tModule->flag_com_gsm_2 = 0;
        }
        if (tModule->flag_com_gsm_2 == 0) {
            temp = "";
            strcpy(tModule->apn_gsm_2, temp.toUtf8().data());
            strcpy(tModule->user_gsm_2, temp.toUtf8().data());
            strcpy(tModule->passwd_gsm_2, temp.toUtf8().data());
        } else if (tModule->flag_com_gsm_2 == 1) {
            temp = list_sim_2.at(5);
            if (temp == "-") {
                strcpy(tModule->apn_gsm_2, "");
            } else {
                strcpy(tModule->apn_gsm_2, temp.toUtf8().data());
            }
            temp = list_sim_2.at(6);
            if (temp == "-") {
                strcpy(tModule->user_gsm_2, "");
            } else {
                strcpy(tModule->user_gsm_2, temp.toUtf8().data());
            }
            temp = list_sim_2.at(7);
            if (temp == "-") {
                strcpy(tModule->passwd_gsm_2, "");
            } else {
                strcpy(tModule->passwd_gsm_2, temp.toUtf8().data());
            }
        }
    }
}

void worker::Set_ENV(QSerialPort *Serial_Com, struct t_module *tModule)
{
    QString Request;
    int jeda = 1000;

    Request.sprintf("set_env nama %s\r\n", tModule->module_name);
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
    this->delay(jeda);
    Request.sprintf("set_env SN %s\r\n", tModule->serial_number);
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
    this->delay(jeda);
}

void worker::Set_IO(QSerialPort *Serial_Com, struct t_module *tModule)
{
    int jeda = 1000;
    QString Request;
    QString temp;
    QStringList val;

    /** SET I/O DIGITAL **/
    temp.sprintf("%s", tModule->input_d1);
    val = temp.split(";");
    Request = "set_kanal 1 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 1 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_d2);
    val = temp.split(";");
    Request = "set_kanal 2 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 2 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_d3);
    val = temp.split(";");
    Request = "set_kanal 3 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 3 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_d4);
    val = temp.split(";");
    Request = "set_kanal 4 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 4 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_d5);
    val = temp.split(";");
    Request = "set_kanal 5 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 5 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_d6);
    val = temp.split(";");
    Request = "set_kanal 6 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 6 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_d7);
    val = temp.split(";");
    Request = "set_kanal 7 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 7 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);


    /** SET I/O ANALOG **/
    temp.sprintf("%s", tModule->input_a1);
    val = temp.split(";");
    Request = "set_kanal 8 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 8 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_a2);
    val = temp.split(";");
    Request = "set_kanal 9 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 9 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_a3);
    val = temp.split(";");
    Request = "set_kanal 10 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 10 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_a4);
    val = temp.split(";");
    Request = "set_kanal 11 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 11 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_a5);
    val = temp.split(";");
    Request = "set_kanal 12 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 12 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);

    temp.sprintf("%s", tModule->input_a6);
    val = temp.split(";");
    Request = "set_kanal 13 status " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    Request = "set_kanal 13 " + val.at(3) + " " + val.at(4) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);


    /** SET I/O RELAY **/
    temp.sprintf("%s", tModule->output_r1);
    val = temp.split(";");
    Request = "set_relay 1 " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
//    Request = "set_relay 1 " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
//    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
//    this->delay(jeda);

    temp.sprintf("%s", tModule->output_r2);
    val = temp.split(";");
    Request = "set_relay 2 " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
//    Request = "set_relay 1 " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
//    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
//    this->delay(jeda);
}

void worker::Set_SIM(QSerialPort *Serial_Com, struct t_module *tModule)
{
    int jeda = 1000;
    QString Request;
    QString temp;

    /** SET SIM 1 **/
    temp.sprintf("%s", tModule->device_name_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 nama -\r\n";
    } else {
        Request = "set_cfg_sim 1 nama " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->name_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 operator -\r\n";
    } else {
        Request = "set_cfg_sim 1 operator " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->number_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 nomor -\r\n";
    } else {
        Request = "set_cfg_sim 1 nomor " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%d", tModule->flag_status_active_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 status 0\r\n";
    } else {
        Request = "set_cfg_sim 1 status " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->apn_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 apn -\r\n";
    } else {
        Request = "set+cfg_sim 1 apn " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->user_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 user -\r\n";
    } else {
        Request = "set_cfg_sim 1 user " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->passwd_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 pass -\r\n";
    } else {
        Request = "set_cfg_sim 1 pass " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->com_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 mode -\r\n";
    } else {
        Request = "set_cfg_sim 1 mode " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);


    /** SET SIM 2 **/
    temp.sprintf("%s", tModule->device_name_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 nama -\r\n";
    } else {
        Request = "set_cfg_sim 2 nama " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->name_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 operator -\r\n";
    } else {
        Request = "set_cfg_sim 2 operator " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->number_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 nomor -\r\n";
    } else {
        Request = "set_cfg_sim 2 nomor " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%d", tModule->flag_status_active_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 status 0\r\n";
    } else {
        Request = "set_cfg_sim 2 status " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->apn_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 apn -\r\n";
    } else {
        Request = "set+cfg_sim 2 apn " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->user_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 user -\r\n";
    } else {
        Request = "set_cfg_sim 2 user " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->passwd_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 pass -\r\n";
    } else {
        Request = "set_cfg_sim 2 pass " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
    temp.sprintf("%s", tModule->com_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 mode -\r\n";
    } else {
        Request = "set_cfg_sim 2 mode " + temp + "\r\n";
    }
//    Serial->write_data(Serial_Com, Request);
    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
    this->delay(jeda);
}

void worker::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
