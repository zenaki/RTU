#include "worker.h"

worker::worker()
{

}

QString worker::newModule(QStandardItemModel *tree, QTreeView *treeView, QString title){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.dbe", title.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    modules.sprintf("%s", tModule.module_name);
//    modules.sprintf("m_%s.dbe", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::editModule(QStandardItemModel *tree, QTreeView *treeView, QString title){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.dbe", title.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    modules.sprintf("%s", tModule.module_name);
//    modules.sprintf("m_%s.dbe", tModule.module_name);
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
//    modules.sprintf("m_%s.dbe", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::checkModule(QString address){
    struct t_module tModule;

    mod.read_module(&tModule, address);

    QString modules;
    modules.sprintf("m_%s.dbe", tModule.module_name);
    return modules;
}

QString worker::check_statusModule(QString address){
    struct t_module tModule;

    address.sprintf("data/module/%s", address.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    if(tModule.flag_active){
        modules.sprintf("m_%s.dbe", tModule.module_name);
        return modules;
    }
    return "none";
}

void worker::showModule(QWidget *parent, QMdiArea *mdiArea, QString module, QSerialPort *SerialPort, QLightBoxWidget *LightBox){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.dbe", module.toUtf8().data());
    mod.read_module(&tModule, address);


    formModule *fModule;

    fModule = new formModule(parent, address, SerialPort, LightBox);
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
    currFiles.sprintf("m_%s.dbe", name.toUtf8().data());

    for(int i = 0; i < files.count(); i++){
        if(currFiles == QString(files.at(i))) cek = true;
    }

//    std::string sub = name.toStdString();
//    ext = QString::fromStdString(sub.substr(index_max-3, index_max));

//    if(ext == ".dbe") return true;
//    else return false;

    return cek;
}

bool worker::state_of_module(int num, QString newModule, QString *existModule){
    bool cek;
    int  ceknt = num+1;
//    QString currModule;
    existModule->prepend("m_").append(".dbe");

    for(int n = 0; n < ceknt; n++){
//        currModule = existModule->at(n);
//        currModule.prepend("m_").append(".dbe");
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

bool worker::Request_ENV(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
{
    QString Request = "hmi_cek_env\r\n";
    Serial_Com->write(Request.toUtf8().data());
//    this->delay(parent, lBox, Request, jeda);
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    return timeout;
}

bool worker::Request_IO(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
{
    QString Request = "hmi_sync\r\n";
    Serial_Com->write(Request.toUtf8().data());
//    this->delay(parent, lBox, Request, jeda);
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    return timeout;
}

bool worker::Request_SIM(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
{
    QString Request = "hmi_cek_cfg_sim\r\n";
    Serial_Com->write(Request.toUtf8().data());
//    this->delay(parent, lBox, Request, jeda);
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    return timeout;
}

bool worker::Request_SIG(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
{
    QString Request = "hmi_cek_signal\r\n";
    Serial_Com->write(Request.toUtf8().data());
//    this->delay(parent, lBox, Request, jeda);
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    return timeout;
}

void worker::Get_ENV(struct t_module *tModule, QStringList data)
{
    QString temp;

    temp = data.at(0);
    strcpy(tModule->module_name, temp.toUtf8().data());
    temp = data.at(1);
    strcpy(tModule->serial_number, temp.toUtf8().data());
//    temp = data.at(2);
//    strcpy(tModule->ip_address, temp.toUtf8().data());
//    temp = data.at(3);
//    strcpy(tModule->gateway_address, temp.toUtf8().data());
//    temp = data.at(4);
//    strcpy(tModule->server_address, temp.toUtf8().data());
//    temp = data.at(5);
//    strcpy(tModule->file_address, temp.toUtf8().data());
//    temp = data.at(6);
//    tModule->flag_webclient = temp.toInt();
}

void worker::Get_Input(struct t_module *tModule, QStringList data)
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
    strcpy(tModule->input_a1, temp.toUtf8().data());
    temp = data.at(7);
    strcpy(tModule->input_a2, temp.toUtf8().data());
    temp = data.at(8);
    strcpy(tModule->input_a3, temp.toUtf8().data());
    temp = data.at(9);
    strcpy(tModule->input_a4, temp.toUtf8().data());
    temp = data.at(10);
    strcpy(tModule->input_a5, temp.toUtf8().data());
    temp = data.at(11);
    strcpy(tModule->input_a6, temp.toUtf8().data());
}

void worker::Get_Output(struct t_module *tModule, QStringList data)
{
    QString temp;

    temp = data.at(12);
    strcpy(tModule->output_r1, temp.toUtf8().data());
    temp = data.at(13);
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

bool worker::Set_ENV(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout)
{
//    int jeda = 1000;
    QString Request;

    Request.sprintf("set_env nama %s\r\n", tModule->module_name);
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request.sprintf("set_env SN %s\r\n", tModule->serial_number);
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

//    Request.sprintf("set_env ipaddr %s\r\n", tModule->ip_address);
//    Serial_Com->write(Request.toUtf8().data());
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
//    if (timeout) {return timeout;}

//    Request.sprintf("set_env gateway %s\r\n", tModule->gateway_address);
//    Serial_Com->write(Request.toUtf8().data());
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
//    if (timeout) {return timeout;}

//    Request.sprintf("set_env server %s\r\n", tModule->server_address);
//    Serial_Com->write(Request.toUtf8().data());
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
//    if (timeout) {return timeout;}

//    Request.sprintf("set_env file %s\r\n", tModule->file_address);
//    Serial_Com->write(Request.toUtf8().data());
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
//    if (timeout) {return timeout;}
    return timeout;
}

bool worker::Set_Input(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout)
{
    QString Request;
    QString temp;
    QStringList val;

    /** SET INPUT DIGITAL **/
    temp.sprintf("%s", tModule->input_d1);
    val = temp.split(";");

    Request = "set_kanal 1 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 1 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_d2);
    val = temp.split(";");

    Request = "set_kanal 2 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 2 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_d3);
    val = temp.split(";");

    Request = "set_kanal 3 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 3 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_d4);
    val = temp.split(";");

    Request = "set_kanal 4 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 4 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_d5);
    val = temp.split(";");

    Request = "set_kanal 5 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 5 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_d6);
    val = temp.split(";");

    Request = "set_kanal 6 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 6 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}


    /** SET INPUT ANALOG **/
    temp.sprintf("%s", tModule->input_a1);
    val = temp.split(";");

    Request = "set_kanal 7 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 7 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_a2);
    val = temp.split(";");

    Request = "set_kanal 8 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 8 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_a3);
    val = temp.split(";");

    Request = "set_kanal 9 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 9 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_a4);
    val = temp.split(";");

    Request = "set_kanal 10 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 10 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_a5);
    val = temp.split(";");

    Request = "set_kanal 11 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 11 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->input_a6);
    val = temp.split(";");

    Request = "set_kanal 12 status " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    Request = "set_kanal 12 " + val.at(3) + " " + val.at(4) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    return timeout;
}

bool worker::Set_Output(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout)
{
    QString Request;
    QString temp;
    QStringList val;

    /** SET OUTPUT RELAY **/
    temp.sprintf("%s", tModule->output_r1);
    val = temp.split(";");
    Request = "set_relay 1 " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}
//    Request = "set_relay 1 " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
//    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
//    this->delay(jeda);

    temp.sprintf("%s", tModule->output_r2);
    val = temp.split(";");
    Request = "set_relay 2 " + val.at(2) + "\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}
//    Request = "set_relay 1 " + val.at(2) + "\r\n";
//    Serial->write_data(Serial_Com, Request);
//    Serial_Com->write(Request.toUtf8().data());
//    FormModule->ui->request->setText(Request);
//    this->delay(jeda);

    return timeout;
}

bool worker::Set_SIM(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout)
{
//    int jeda = 1000;
    QString Request;
    QString temp;

    /** SET SIM 1 **/
    temp.sprintf("%s", tModule->device_name_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 nama -\r\n";
    } else {
        Request = "set_cfg_sim 1 nama " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->name_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 operator -\r\n";
    } else {
        Request = "set_cfg_sim 1 operator " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->number_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 nomor -\r\n";
    } else {
        Request = "set_cfg_sim 1 nomor " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%d", tModule->flag_status_active_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 status 0\r\n";
    } else {
        Request = "set_cfg_sim 1 status " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->apn_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 apn -\r\n";
    } else {
        Request = "set_cfg_sim 1 apn " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->user_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 user -\r\n";
    } else {
        Request = "set_cfg_sim 1 user " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->passwd_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 pass -\r\n";
    } else {
        Request = "set_cfg_sim 1 pass " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->com_gsm_1);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 1 mode -\r\n";
    } else {
        Request = "set_cfg_sim 1 mode " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}


    /** SET SIM 2 **/
    temp.sprintf("%s", tModule->device_name_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 nama -\r\n";
    } else {
        Request = "set_cfg_sim 2 nama " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->name_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 operator -\r\n";
    } else {
        Request = "set_cfg_sim 2 operator " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->number_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 nomor -\r\n";
    } else {
        Request = "set_cfg_sim 2 nomor " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%d", tModule->flag_status_active_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 status 0\r\n";
    } else {
        Request = "set_cfg_sim 2 status " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->apn_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 apn -\r\n";
    } else {
        Request = "set_cfg_sim 2 apn " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->user_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 user -\r\n";
    } else {
        Request = "set_cfg_sim 2 user " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->passwd_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 pass -\r\n";
    } else {
        Request = "set_cfg_sim 2 pass " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    temp.sprintf("%s", tModule->com_gsm_2);
    if (temp.isEmpty()) {
        Request = "set_cfg_sim 2 mode -\r\n";
    } else {
        Request = "set_cfg_sim 2 mode " + temp + "\r\n";
    }
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    return timeout;
}

bool worker::Reset_Board(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
{
    QString Request;
    QString temp;

    Request = "reset\r\n";
    Serial_Com->write(Request.toUtf8().data());
    if (!timeout) {timeout = this->waiting_set(parent, lBox, Request, timeout);}
    if (timeout) {return timeout;}

    return timeout;
}

void worker::delay(QWidget *parent, QLightBoxWidget *lBox, QString desc, int ms)
{
    /** Set Light Box for Busy **/
    QLightBoxWidget* lightBox = new QLightBoxWidget(parent, true);
    lightBox = lBox;
    lightBox->repaint();

    QLabel* lbTitle = new QLabel("MONITA RTU");
    lbTitle->setStyleSheet("font-size: 28px; font-weight: bold; color: white");
    QLabel* lbProgress = new QLabel;
    QMovie* progressMovie = new QMovie(":/new/prefix1/image/loader.gif");
    lbProgress->setMovie(progressMovie);
    progressMovie->start();
    desc = "Processing ...";
    desc.prepend("wait a second\n");
    QLabel* lbDescription = new QLabel(desc.toUtf8().data());
    lbDescription->setStyleSheet("color: white");

    QGridLayout* lbLayout = new QGridLayout;
    lbLayout->setRowStretch(0, 1);
    lbLayout->setColumnStretch(0, 1);
    lbLayout->addWidget(lbTitle, 1, 1);
    lbLayout->addWidget(lbProgress, 1, 2, Qt::AlignRight);
    lbLayout->setColumnStretch(3, 1);
    lbLayout->addWidget(lbDescription, 2, 1, 1, 2);
    lbLayout->setRowStretch(4, 1);

    lightBox->setLayout(lbLayout);
    lightBox->show();

    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    lightBox->close();
}

bool worker::waiting_set(QWidget *parent, QLightBoxWidget *lBox, QString desc, bool timeout)
{
    /** Set Light Box for Busy **/
    QLightBoxWidget* lightBox = new QLightBoxWidget(parent, true);
    lightBox = lBox;
    lightBox->repaint();

    QLabel* lbTitle = new QLabel("MONITA RTU");
    lbTitle->setStyleSheet("font-size: 28px; font-weight: bold; color: white");
    QLabel* lbProgress = new QLabel;
    QMovie* progressMovie = new QMovie(":/new/prefix1/image/loader.gif");
    lbProgress->setMovie(progressMovie);
    progressMovie->start();
    desc = "Processing ...";
    desc.prepend("wait a second\n");
    QLabel* lbDescription = new QLabel(desc.toUtf8().data());
    lbDescription->setStyleSheet("color: white");

    QGridLayout* lbLayout = new QGridLayout;
    lbLayout->setRowStretch(0, 1);
    lbLayout->setColumnStretch(0, 1);
    lbLayout->addWidget(lbTitle, 1, 1);
    lbLayout->addWidget(lbProgress, 1, 2, Qt::AlignRight);
    lbLayout->setColumnStretch(3, 1);
    lbLayout->addWidget(lbDescription, 2, 1, 1, 2);
    lbLayout->setRowStretch(4, 1);

    lightBox->setLayout(lbLayout);
    lightBox->show();

    QTime dieTime = QTime::currentTime().addMSecs(5000);
    while (!this->read_FinishRead()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        if (QTime::currentTime() >= dieTime && !timeout) {
            timeout = true;
//            emit TimeOut();
            break;
        }
    }

//    Serial->write_FinishRead(false);

//    QTime dieTime = QTime::currentTime().addMSecs(1000);
//    while (QTime::currentTime() < dieTime) {
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    }

    lightBox->close();
    this->write_FinishRead(false);
    return timeout;
}

void worker::write_FinishRead(bool FinishRead)
{
    QString pth;
    pth = "data/config/serial_parsing.ini";
    QSettings sett(pth, QSettings::IniFormat);

    sett.setValue("FINISH_READ", FinishRead);
}

bool worker::read_FinishRead()
{
    QString pth;
    pth = "data/config/serial_parsing.ini";
    QSettings sett(pth, QSettings::IniFormat);

    bool FinishRead = sett.value("FINISH_READ").toBool();
    return FinishRead;
}
