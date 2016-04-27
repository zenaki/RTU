#include "worker.h"

worker::worker()
{
//    cancelSetting = false;
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
    cryp code; code.encryp(address);

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

void worker::showModule(QWidget *parent, QMdiArea *mdiArea, QString module, QSerialPort *SerialPort){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.dbe", module.toUtf8().data());
    mod.read_module(&tModule, address);


    formModule *fModule;

    fModule = new formModule(parent, address, SerialPort);
    fModule->setModal(true);
    fModule->setWindowTitle(tModule.module_name);
//    fModule->setFixedWidth(800);
//    fModule->setFixedHeight(600);
    fModule->setMaximumSize(mdiArea->maximumSize());

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

bool worker::Request_ENV(QSerialPort *Serial_Com, bool timeout)
{
//    QString Request = "hmi_cek_env\r\n";
    QString Request = "0000\r\n";
    QString Desc = "Request Environment ..";
    serial_write(Serial_Com, Request, WAIT_WRITE);
//    Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
//    Serial_Com->waitForBytesWritten(WAIT_WRITE);
    if (!timeout) {timeout = this->waiting_set(timeout);}
    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
    if (timeout) {return timeout;}

    return timeout;
}

//bool worker::Request_IO(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
//{
////    QString Request = "hmi_sync\r\n";
//    QString Request = "0002\r\n";
//    QString Desc = "Request I/O ..";
//    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
////    Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
////    Serial_Com->waitForBytesWritten(WAIT_WRITE);
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, "Request I/O ..", timeout);}
//    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//    if (timeout) {return timeout;}

//    return timeout;
//}

//bool worker::Request_SIM(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
//{
////    QString Request = "hmi_cek_cfg_sim\r\n";
//    QString Request = "0001\r\n";
//    QString Desc = "Request SIM ..";
//    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
////    Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
////    Serial_Com->waitForBytesWritten(WAIT_WRITE);
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, "Request SIM ..", timeout);}
//    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//    if (timeout) {return timeout;}

//    return timeout;
//}

//bool worker::Request_Signal(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
//{
//    QString Request = "hmi_cek_signal\r\n";
//    QString Desc = "Request Signal ..";
//    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
////    Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
////    Serial_Com->waitForBytesWritten(WAIT_WRITE);
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, "Request Signal ..", timeout);}
//    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//    if (timeout) {return timeout;}

//    return timeout;
//}

//bool worker::Request_Sumber(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
//{
////    QString Request = "hmi_cek_sumber\r\n";
//    QString Request = "0004\r\n";
//    QString Desc = "Request Sources ..";
//    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
////    Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
////    Serial_Com->waitForBytesWritten(WAIT_WRITE);
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, "Request Sources ..", timeout);}
//    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//    if (timeout) {return timeout;}

//    return timeout;
//}

//bool worker::Request_Data(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
//{
////    QString Request = "hmi_cek_data\r\n";
//    QString Request = "0005\r\n";
//    QString Desc = "Request Data ..";
//    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
////    Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
////    Serial_Com->waitForBytesWritten(WAIT_WRITE);
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, "Request Data ..", timeout);}
//    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//    if (timeout) {return timeout;}

//    return timeout;
//}

//void worker::Get_ENV(struct t_module *tModule, QStringList data)
//{
//    QString temp;

//    temp = data.at(0);
//    strcpy(tModule->module_name, temp.toUtf8().data());
//    temp = data.at(1);
//    strcpy(tModule->serial_number, temp.toUtf8().data());
//    temp = data.at(2);
//    strcpy(tModule->ip_address, temp.toUtf8().data());
//    temp = data.at(3);
//    strcpy(tModule->server_address, temp.toUtf8().data());
//    temp = data.at(4);
//    strcpy(tModule->file_address, temp.toUtf8().data());
//    temp = data.at(5);
//    tModule->flag_webclient = temp.toInt();
//    if (temp == "0") {
//        temp = "ACTIVE";
//        strcpy(tModule->status_webclient, temp.toUtf8().data());
//    } else if (temp == "1") {
//        temp = "NOT ACTIVE";
//        strcpy(tModule->status_webclient, temp.toUtf8().data());
//    }
//    temp = data.at(7);
//    tModule->interval = temp.toInt();
//}

//void worker::Get_Input(struct t_module *tModule, QStringList data)
//{
//    QString temp;
//    tModule->Input.clear();
//    int index = 0;
//    for (int i = 0; i < data.length(); i++) {
//        temp = data.at(i);
//        if (temp.mid(0,1) == "D" || temp.mid(0,1) == "A") {
//            tModule->Input.insert(index, data.at(i));
//            index++;
//        }
//    }
//    tModule->jml_input_digital = 0;
//    tModule->jml_input_analog = 0;
//    for (int i = 0; i < tModule->Input.length(); i++) {
//        temp = tModule->Input.at(i);
//        if (temp.mid(0,1) == "D") {
//            tModule->jml_input_digital++;
//        } else if (temp.mid(0,1) == "A") {
//            tModule->jml_input_analog++;
//        }
//    }
//    QStringList list; QStringList list2;
//    tModule->InputName.clear();
//    for (int i = 0; i < tModule->Input.length(); i++) {
//        temp = tModule->Input.at(i);
//        list = temp.split(';');
//        for (int j = 0; j < tModule->data.length(); j++) {
//            temp = tModule->data.at(j);
//            list2 = temp.split(';');
//            if (list.at(1) == list2.at(0)) {
//                tModule->InputName.insert(i, list2.at(2));
//                break;
//            }
//        }
//    }
//}

//void worker::Get_Output(struct t_module *tModule, QStringList data)
//{
//    QString temp;
//    tModule->Output.clear();
//    int index = 0;
//    for (int i = 0; i < data.length(); i++) {
//        temp = data.at(i);
//        if (temp.mid(0,1) == "R") {
//            tModule->Output.insert(index, data.at(i));
//            index++;
//        }
//    }
//    tModule->jml_output = tModule->Output.length();
//    tModule->OutputName.clear();
//    for (int i = 0; i < tModule->Output.length(); i++) {
//        tModule->OutputName.insert(i, "");
//    }
//}

//void worker::Get_SIM(struct t_module *tModule, QStringList data)
//{
//    QString temp;

//    QString str_sim_1 = data.at(0);
//    QString str_sim_2 = data.at(1);

//    QStringList list_sim_1 = str_sim_1.split(";");
//    QStringList list_sim_2 = str_sim_2.split(";");

//    /** MODUlE **/
//    tModule->flag_active = 1;
//    if (list_sim_2.at(3) != "-") {tModule->flag_dual_gsm = 1;}
//    else {tModule->flag_dual_gsm = 0;}

//    /** GSM_1 **/
//    temp = list_sim_1.at(1);
//    if (temp == "-") {
//        strcpy(tModule->device_name_gsm_1, "");
//    } else {
//        strcpy(tModule->device_name_gsm_1, temp.toUtf8().data());
//    }
//    temp = list_sim_1.at(2);
//    if (temp == "-") {
//        strcpy(tModule->name_gsm_1, "");
//        tModule->flag_gsm_1 = 0;
//    } else {
//        strcpy(tModule->name_gsm_1, temp.toUtf8().data());
//        if (temp == "TELKOMSEL") {
//            tModule->flag_gsm_1 = 0;
//        } else if (temp == "INDOSAT") {
//            tModule->flag_gsm_1 = 1;
//        } else if (temp == "XL") {
//            tModule->flag_gsm_1 = 2;
//        } else if (temp == "3") {
//            tModule->flag_gsm_1 = 3;
//        }
//    }
//    temp = list_sim_1.at(3);
//    if (temp == "-") {
//        strcpy(tModule->number_gsm_1, "");
//    } else {
//        strcpy(tModule->number_gsm_1, temp.toUtf8().data());
//    }
//    temp = list_sim_1.at(4);
//    if (temp == "0") {
//        tModule->flag_status_active_gsm_1 = temp.toInt();
//        temp = "NOT ACTIVE";
//        strcpy(tModule->status_gsm_1, temp.toUtf8().data());
//    } else if (temp == "1") {
//        tModule->flag_status_active_gsm_1 = temp.toInt();
//        temp = "ACTIVE";
//        strcpy(tModule->status_gsm_1, temp.toUtf8().data());
//    }
//    temp = list_sim_1.at(8);
//    if (temp == "GSM") {
////        temp = "SMS";
//        strcpy(tModule->com_gsm_1, temp.toUtf8().data());
//        tModule->flag_com_gsm_1 = 0;
//    } else if (temp == "GPRS") {
//        strcpy(tModule->com_gsm_1, temp.toUtf8().data());
//        tModule->flag_com_gsm_1 = 1;
//    } else {
//        strcpy(tModule->com_gsm_1, "");
//        tModule->flag_com_gsm_1 = 0;
//    }
//    if (tModule->flag_com_gsm_1 == 0) {
//        temp = "";
//        strcpy(tModule->apn_gsm_1, temp.toUtf8().data());
//        strcpy(tModule->user_gsm_1, temp.toUtf8().data());
//        strcpy(tModule->passwd_gsm_1, temp.toUtf8().data());
//    } else if (tModule->flag_com_gsm_1 == 1) {
//        temp = list_sim_1.at(5);
//        if (temp == "-") {
//            strcpy(tModule->apn_gsm_1, "");
//        } else {
//            strcpy(tModule->apn_gsm_1, temp.toUtf8().data());
//        }
//        temp = list_sim_1.at(6);
//        if (temp == "-") {
//            strcpy(tModule->user_gsm_1, "");
//        } else {
//            strcpy(tModule->user_gsm_1, temp.toUtf8().data());
//        }
//        temp = list_sim_1.at(7);
//        if (temp == "-") {
//            strcpy(tModule->passwd_gsm_1, "");
//        } else {
//            strcpy(tModule->passwd_gsm_1, temp.toUtf8().data());
//        }
//    }

//    /** GSM_2 **/
//    if (tModule->flag_dual_gsm == 0) {
//        strcpy(tModule->device_name_gsm_2, "");
//        strcpy(tModule->name_gsm_2, "");
//        tModule->flag_gsm_2 = 0;
//        strcpy(tModule->number_gsm_2, "");
//        tModule->flag_status_active_gsm_2 = 0;
//        strcpy(tModule->status_gsm_2, "");
//        strcpy(tModule->com_gsm_2, "");
//        tModule->flag_com_gsm_2 = 0;
//        strcpy(tModule->apn_gsm_2, "");
//        strcpy(tModule->user_gsm_2, "");
//        strcpy(tModule->passwd_gsm_2, "");
//    } else if (tModule->flag_dual_gsm == 1) {
//        temp = list_sim_2.at(1);
//        if (temp == "-") {
//            strcpy(tModule->device_name_gsm_2, "");
//        } else {
//            strcpy(tModule->device_name_gsm_2, temp.toUtf8().data());
//        }
//        temp = list_sim_2.at(2);
//        if (temp == "-") {
//            strcpy(tModule->name_gsm_2, "");
//            tModule->flag_gsm_2 = 0;
//        } else {
//            strcpy(tModule->name_gsm_2, temp.toUtf8().data());
//            if (temp == "TELKOMSEL") {
//                tModule->flag_gsm_2 = 0;
//            } else if (temp == "INDOSAT") {
//                tModule->flag_gsm_2 = 1;
//            } else if (temp == "XL") {
//                tModule->flag_gsm_2 = 2;
//            } else if (temp == "3") {
//                tModule->flag_gsm_2 = 3;
//            }
//        }
//        temp = list_sim_2.at(3);
//        if (temp == "-") {
//            strcpy(tModule->number_gsm_2, "");
//        } else {
//            strcpy(tModule->number_gsm_2, temp.toUtf8().data());
//        }
//        temp = list_sim_2.at(4);
//        if (temp == "0") {
//            tModule->flag_status_active_gsm_2 = temp.toInt();
//            temp = "NOT ACTIVE";
//            strcpy(tModule->status_gsm_2, temp.toUtf8().data());
//        } else if (temp == "1") {
//            tModule->flag_status_active_gsm_2 = temp.toInt();
//            temp = "ACTIVE";
//            strcpy(tModule->status_gsm_2, temp.toUtf8().data());
//        }
//        temp = list_sim_2.at(8);
//        if (temp == "GSM") {
////            temp = "SMS";
//            strcpy(tModule->com_gsm_2, temp.toUtf8().data());
//            tModule->flag_com_gsm_2 = 0;
//        } else if (temp == "GPRS") {
//            strcpy(tModule->com_gsm_2, temp.toUtf8().data());
//            tModule->flag_com_gsm_2 = 1;
//        } else {
//            strcpy(tModule->com_gsm_2, "");
//            tModule->flag_com_gsm_2 = 0;
//        }
//        if (tModule->flag_com_gsm_2 == 0) {
//            temp = "";
//            strcpy(tModule->apn_gsm_2, temp.toUtf8().data());
//            strcpy(tModule->user_gsm_2, temp.toUtf8().data());
//            strcpy(tModule->passwd_gsm_2, temp.toUtf8().data());
//        } else if (tModule->flag_com_gsm_2 == 1) {
//            temp = list_sim_2.at(5);
//            if (temp == "-") {
//                strcpy(tModule->apn_gsm_2, "");
//            } else {
//                strcpy(tModule->apn_gsm_2, temp.toUtf8().data());
//            }
//            temp = list_sim_2.at(6);
//            if (temp == "-") {
//                strcpy(tModule->user_gsm_2, "");
//            } else {
//                strcpy(tModule->user_gsm_2, temp.toUtf8().data());
//            }
//            temp = list_sim_2.at(7);
//            if (temp == "-") {
//                strcpy(tModule->passwd_gsm_2, "");
//            } else {
//                strcpy(tModule->passwd_gsm_2, temp.toUtf8().data());
//            }
//        }
//    }
//}

////void worker::Get_Signal(t_module *tModule, QStringList data)
////{

////}

//void worker::Get_Sumber(t_module *tModule, QStringList data)
//{
//    tModule->sumber.clear();
//    tModule->jml_sumber = 0;
//    for (int i = 0; i < data.length(); i++) {
//        if (data.at(i) != "") {
//            tModule->sumber.insert(tModule->jml_sumber, data.at(i));
//            tModule->jml_sumber++;
//        }
//    }
//}

//void worker::Get_Data(t_module *tModule, QStringList data)
//{
//    tModule->data.clear();
//    tModule->jml_data = 0;
//    for (int i = 0; i < data.length(); i++) {
//        if (data.at(i) != "") {
//            tModule->data.insert(tModule->jml_data, data.at(i));
//            tModule->jml_data++;
//        }
//    }
//}

//bool worker::Set_ENV(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout)
//{
//    QString Request; QString Desc;

//    Request.sprintf("0100 %s %s %s %s %d %d\r\n"
//                    , tModule->module_name
//                    , tModule->serial_number
//                    , tModule->server_address
//                    , tModule->file_address
//                    , tModule->flag_webclient
//                    , tModule->interval);
//    Desc.sprintf("Set Environtment \"%s \" ..", tModule->module_name);
//    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//    if (timeout) {return timeout;}

//    return timeout;
//}

//bool worker::Set_Input(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout, QString index)
//{
//    QString Request; QString Desc;
//    QString temp;
//    QStringList val;

//    /** SET INPUT DIGITAL **/
//    if (index.isEmpty()) {
//        for (int i = 0; i < tModule->Input.length(); i++) {
//            temp = tModule->Input.at(i);
//            val = temp.split(';');

//            Request = "0102 " + val.at(1) + " " + val.at(2) + " " + val.at(3) + " " + val.at(4) + "\r\n";
//            Desc = "Set Input Channel " + val.at(1) + " ..";
//            serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//            if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//            this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//            if (timeout) {return timeout;}
//        }
//    } else {
//        temp = tModule->Input.at(index.toInt());
//        val = temp.split(';');

//        Request = "0102 " + val.at(1) + " " + val.at(2) + " " + val.at(3) + " " + val.at(4) + "\r\n";
//        Desc = "Set Input Channel " + val.at(1) + " ..";
//        serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//        if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//        this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//        if (timeout) {return timeout;}
//    }

//    return timeout;
//}

//bool worker::Set_Output(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout, QString index)
//{
//    QString Request; QString Desc;
//    QString temp;
//    QStringList val;

//    if (index.isEmpty()) {
//        /** SET OUTPUT RELAY **/
//        for (int i = 0; i < tModule->Output.length(); i++) {
//            temp = tModule->Output.at(i);
//            val = temp.split(';');
////            Request = "set_relay " + val.at(1) + " " + val.at(2) + "\r\n";
//            Request = "0103 " + val.at(1) + " " + val.at(2) + " " + val.at(4) + "\r\n";
//            Desc = "Set Output Channel " + val.at(1) + " ..";
//            serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
////            Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
////            Serial_Com->waitForBytesWritten(WAIT_WRITE);
//            if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//            this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//            if (timeout) {return timeout;}
//        }
//    } else {
//        temp = tModule->Output.at(index.toInt());
//        val = temp.split(';');
////        Request = "set_relay " + val.at(1) + " " + val.at(2) + "\r\n";
//        Request = "0103 " + val.at(1) + " " + val.at(2) + " " + val.at(4) + "\r\n";
//        Desc = "Set Output Channel " + val.at(1) + " ..";
//        serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
////            Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
////            Serial_Com->waitForBytesWritten(WAIT_WRITE);
//        if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//        this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//        if (timeout) {return timeout;}
//    }

//    return timeout;
//}

//bool worker::Set_SIM(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, struct t_module *tModule, bool timeout)
//{
////    int jeda = 1000;
//    QString Request; QString Desc;
//    QString temp;

//    /** SET SIM 1 **/
//    Request.sprintf("0101 1 %s %s %s %d %s %s %s %s"
//                    , tModule->device_name_gsm_1
//                    , tModule->name_gsm_1
//                    , tModule->number_gsm_1
//                    , tModule->flag_status_active_gsm_1
//                    , tModule->apn_gsm_1
//                    , tModule->user_gsm_1
//                    , tModule->passwd_gsm_1
//                    , tModule->com_gsm_1);
//    Desc.sprintf("Set SIM 1 Configuration (\"%s\") ..", tModule->device_name_gsm_1);
//    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//    if (timeout) {return timeout;}

//    /** SET SIM 2 **/
//    Request.sprintf("0101 2 %s %s %s %d %s %s %s %s"
//                    , tModule->device_name_gsm_2
//                    , tModule->name_gsm_2
//                    , tModule->number_gsm_2
//                    , tModule->flag_status_active_gsm_2
//                    , tModule->apn_gsm_2
//                    , tModule->user_gsm_2
//                    , tModule->passwd_gsm_2
//                    , tModule->com_gsm_2);
//    Desc.sprintf("Set SIM 2 Configuration (\"%s\") ..", tModule->device_name_gsm_2);
//    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//    if (timeout) {return timeout;}

//    return timeout;
//}

//bool worker::Set_Sumber(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, t_module *tModule, bool timeout, QString index)
//{
//    QString Request; QString Desc;
//    QString temp; QString str;
//    QStringList val; QStringList list;

//    if (index.isEmpty()) {
//        for (int i = 0; i < tModule->sumber.length(); i++) {
//            temp = tModule->sumber.at(i);
//            val = temp.split(";");

//            Request = "0104 " + val.at(0) + " " + val.at(1) + " " +
//                      val.at(2) + " " + val.at(3) + " " + val.at(4) + " " +
//                      val.at(5) + ";" + val.at(6) + ";" + val.at(7) + ";" +
//                      val.at(8) + ";" + val.at(9) + ";" +
//                      val.at(10) + ";" + val.at(11) + "\r\n";
//            Desc = "Set Sources " + val.at(0) + " : \"" + val.at(1) + "\" ..";
//            serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//            if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//            this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//            if (timeout) {return timeout;}

//            if (val.at(5) != "0" && val.at(11) != "") {
//                temp = val.at(11);
//                for (int k = 0; k < tModule->data.length(); k++) {
//                    str = tModule->data.at(k);
//                    list = str.split(';');
//                    if (temp == list.at(1)) {
//                        str = list.at(0);
//                        break;
//                    }
//                }
//                temp = val.at(10);
//                for (int j = 0; j < temp.toInt()/2; j++) {
//                    Request = "set_data " + QString::number(str.toInt()+j) +
//                              " status " + val.at(4);
//                    if (val.at(4) == "1") {
//                        Desc = "Set Data " + QString::number(str.toInt()+j) + " with status : ACTIVE ..";
//                    } else {
//                        Desc = "Set Data " + QString::number(str.toInt()+j) + " with status : NOT ACTIVE ..";
//                    }
//                    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//                    if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//                    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//                    if (timeout) {return timeout;}
//                }
//            }
//        }
//    } else {
//        temp = tModule->sumber.at(index.toInt());
//        val = temp.split(";");

//        Request = "0104 " + val.at(0) + " " + val.at(1) + " " +
//                  val.at(2) + " " + val.at(3) + " " + val.at(4) + " " +
//                  val.at(5) + ";" + val.at(6) + ";" + val.at(7) + ";" +
//                  val.at(8) + ";" + val.at(9) + ";" +
//                  val.at(10) + ";" + val.at(11) + "r\n";
//        Desc = "Set Sources " + val.at(0) + " : \"" + val.at(1) + "\" ..";
//        serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//        if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//        this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//        if (timeout) {return timeout;}

//        if (val.at(5) != "0" && val.at(11) != "") {
//            temp = val.at(11);
//            for (int k = 0; k < tModule->data.length(); k++) {
//                str = tModule->data.at(k);
//                list = str.split(';');
//                if (temp == list.at(1)) {
//                    str = list.at(0);
//                    break;
//                }
//            }
//            temp = val.at(10);
//            for (int j = 0; j < temp.toInt()/2; j++) {
//                Request = "set_data " + QString::number(str.toInt()+j) +
//                          " status " + val.at(4);
//                if (val.at(4) == "1") {
//                    Desc = "Set Data " + QString::number(str.toInt()+j) + " with status : ACTIVE ..";
//                } else {
//                    Desc = "Set Data " + QString::number(str.toInt()+j) + " with status : NOT ACTIVE ..";
//                }
//                serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//                if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//                this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//                if (timeout) {return timeout;}
//            }
//        }
//    }

//    return timeout;
//}

//bool worker::Set_Data(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, t_module *tModule, bool timeout, QString index)
//{
//    QString Request; QString Desc;
//    QString temp;
//    QStringList val;

//    if (index.isEmpty()) {
//        for (int i = 0; i < tModule->data.length(); i++) {
//            temp = tModule->data.at(i);
//            val = temp.split(";");

//            Request = "0105 " + val.at(0) + " " + val.at(1) + " " +
//                      val.at(2) + " " + val.at(4) + " " + val.at(5) + " " +
//                      val.at(6) + " " + val.at(7) + " " + val.at(8) + " " +
//                      val.at(9) + " " + val.at(10) + " " + val.at(11) + "\r\n";
//            Desc = "Set Data " + val.at(0) + " ..";
//            serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//            if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//            this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//            if (timeout) {return timeout;}
//        }
//    } else {
//        temp = tModule->data.at(index.toInt());
//        val = temp.split(";");

//        Request = "0105 " + val.at(0) + " " + val.at(1) + " " +
//                  val.at(2) + " " + val.at(4) + " " + val.at(5) + " " +
//                  val.at(6) + " " + val.at(7) + " " + val.at(8) + " " +
//                  val.at(9) + " " + val.at(10) + " " + val.at(11) + "\r\n";
//        Desc = "Set Data " + val.at(0)  + " ..";
//        serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
//        if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//        this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//        if (timeout) {return timeout;}
//    }

//    return timeout;
//}

//bool worker::Reset_Board(QWidget *parent, QLightBoxWidget *lBox, QSerialPort *Serial_Com, bool timeout)
//{
//    QString Request; QString Desc;
//    QString temp;

//    Request = "reset\r\n";
//    Desc = "Reset Board ..";
//    serial_write(parent, Serial_Com, lBox, Desc, Request, WAIT_WRITE);
////    Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
////    Serial_Com->waitForBytesWritten(WAIT_WRITE);
//    if (!timeout) {timeout = this->waiting_set(parent, lBox, Desc, timeout);}
//    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
//    if (timeout) {return timeout;}

//    return timeout;
//}

void worker::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void worker::serial_write(QSerialPort *Serial_Com, QString data, int d_c)
{
//    /** Set Light Box for Busy **/
//    QLightBoxWidget *lightBox = new QLightBoxWidget(parent);
//     lightBox = lBox;

//    QLabel *lbTitle = new QLabel("MONITA RTU");
//    lbTitle->setStyleSheet("font-size: 28px; font-weight: bold; color: white");
//    QLabel *lbProgress = new QLabel;
//    QMovie *progressMovie = new QMovie(":/new/prefix1/image/loader.gif");
//    lbProgress->setMovie(progressMovie);
//    progressMovie->start();
//    QLabel *lbDescription = new QLabel();
//    lbDescription->setStyleSheet("color: white");
////    QPushButton *btnCancel = new QPushButton("Cancel Setting");
//    QGridLayout *lbLayout = new QGridLayout;

//    desc = "Processing ...";
//    desc.prepend("wait a minute\n");
//    lbDescription->setText(desc);

//    lbLayout->setRowStretch(0, 1);
//    lbLayout->setColumnStretch(0, 1);
//    lbLayout->addWidget(lbTitle, 1, 1);
//    lbLayout->addWidget(lbProgress, 1, 2, Qt::AlignRight);
//    lbLayout->setColumnStretch(3, 1);
//    lbLayout->addWidget(lbDescription, 2, 1, 1, 2);
////    lbLayout->addWidget(btnCancel, 3, 2);
//    lbLayout->setRowStretch(4, 1);

//    lightBox->setLayout(lbLayout);
//    lightBox->show();
////*********************************************************************************************************//

    QString temp;
    data.remove("\r\n");
    for (int i = 0; i < data.length(); i++) {
        temp = QChar(data.at(i));
        Serial_Com->write(temp.toUtf8().data());
        delay(d_c);
    }
    Serial_Com->write("\r\n");

////*********************************************************************************************************//
//    lightBox->close();
}

bool worker::waiting_set(bool timeout)
{
//    /** Set Light Box for Busy **/
//    QLightBoxWidget *lightBox = new QLightBoxWidget(parent);
//     lightBox = lBox;

//    QLabel *lbTitle = new QLabel("MONITA RTU");
//    lbTitle->setStyleSheet("font-size: 28px; font-weight: bold; color: white");
//    QLabel *lbProgress = new QLabel;
//    QMovie *progressMovie = new QMovie(":/new/prefix1/image/loader.gif");
//    lbProgress->setMovie(progressMovie);
//    progressMovie->start();
//    QLabel *lbDescription = new QLabel();
//    lbDescription->setStyleSheet("color: white");
////    QPushButton *btnCancel = new QPushButton("Cancel Setting");
//    QGridLayout *lbLayout = new QGridLayout;
//    desc = "Processing ...";
//    desc.prepend("wait a minute\n");
//    lbDescription->setText(desc);

//    lbLayout->setRowStretch(0, 1);
//    lbLayout->setColumnStretch(0, 1);
//    lbLayout->addWidget(lbTitle, 1, 1);
//    lbLayout->addWidget(lbProgress, 1, 2, Qt::AlignRight);
//    lbLayout->setColumnStretch(3, 1);
//    lbLayout->addWidget(lbDescription, 2, 1, 1, 2);
////    lbLayout->addWidget(btnCancel, 3, 2);
//    lbLayout->setRowStretch(4, 1);

//    lightBox->setLayout(lbLayout);
//    lightBox->show();
////*********************************************************************************************************//

    QTime dieTime = QTime::currentTime().addMSecs(TIMEOUT);
    while (!this->read_FinishRead()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        if (this->read_flagERR() == 1 && !timeout) {
            timeout = false;
            break;
        }
        if (QTime::currentTime() >= dieTime && !timeout) {
            timeout = true;
            break;
        }
    }

////*********************************************************************************************************//
//    lightBox->close();

    return timeout;
}

//void worker::CancelSetting()
//{
//    cancelSetting = true;
//}

void worker::write_FinishRead(bool FinishRead, int cekErr, QString strErr)
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    QSettings sett(pth, QSettings::IniFormat);

    sett.setValue("FINISH_READ", FinishRead);
    sett.setValue("ERROR_FLAG", cekErr);
    sett.setValue("ERROR_STRING", strErr);
}

bool worker::read_FinishRead()
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    bool FinishRead = sett.value("FINISH_READ").toBool();

    code.encryp(pth);
    return FinishRead;
}

int worker::read_flagERR()
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    int flagERR = sett.value("ERROR_FLAG").toInt();

    code.encryp(pth);
    return flagERR;
}

QString worker::read_strERR()
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    QString strERR = sett.value("ERROR_STRING").toString();

    code.encryp(pth);
    return strERR;
}

void worker::writeLogFile(QString log, int flagERR, QString strERR, bool timeout)
{
    /* Try and open a file for output */
    QString outputFilename = "log.txt";
    QFile outputFile(outputFilename);
    outputFile.open(QIODevice::Append | QIODevice::Text);

    /* Check it opened OK */
    if(!outputFile.isOpen()){
        qDebug() << "- Error, unable to open" << outputFilename << "for output";
    } else {
        log.remove("\r").remove("\n");
        if (log.length() < 100) {
            for (int i = log.length(); i < 100; i++) {
                log.append(" ");
            }
        }
        log.append("|");

        QString Flag;
        if      (flagERR == 1) {Flag = "ERROR|";}
        else if (flagERR == 0) {Flag = "OK   |";}
        else                   {Flag = "     |";}

        QString TimeOut;
        if      (timeout) {TimeOut = "TIMEOUT|";}
        else              {TimeOut = "       |";}

        /* Point a QTextStream object at the file */
        QTextStream outStream(&outputFile);

        /* Write the line to the file */
        outStream << QTime::currentTime().toString("hh:mm:ss.zzz") << " | " << log << Flag << TimeOut << strERR<< "\r\n";

        /* Close the file */
        outputFile.close();
    }
    this->write_FinishRead(false,2,"");
    cryp code; code.encryp(PATH_SERIAL_PARSING);
}

void worker::CompressDir(QString ZipFile, QString Directory)
{
    if (JlCompress::compressDir(ZipFile, Directory)) {
        qDebug() << "Created: " << ZipFile;
    } else {
        qDebug() << "Could not create: " << ZipFile;
    }
}

void worker::DecompressDir(QString ZipFile, QString Directory)
{
    QStringList list = JlCompress::extractDir(ZipFile, Directory);
    foreach (QString item, list) {
        qDebug() << "Extracted: " << item;
    }
}

void worker::CompressFiles(QString ZipFile, QStringList Files)
{
    if (JlCompress::compressFiles(ZipFile, Files)) {
        qDebug() << "Created: " << ZipFile;
    } else {
        qDebug() << "Could not create: " << ZipFile;
    }
}

void worker::DecompressFiles(QString ZipFile, QStringList Files, QString Directory)
{
    QStringList list = JlCompress::extractFiles(ZipFile, Files, Directory);
    foreach (QString item, list) {
        qDebug() << "Extracted: " << item;
    }
}

QStringList worker::ListContents(QString ZipFile)
{
    QStringList list;
    QFile File(ZipFile);
    if (!File.exists()) {
        qDebug() << "Zip file not found";
    } else {

        list = JlCompress::getFileList(ZipFile);
//        foreach (QString item, list) {
//            qDebug() << item;
//        }
    }
    return list;
}

void worker::readPlugin(struct t_plugin *tPlugin)
{
    QString temp;
    QString pth = PATH_PLUGIN_CONFIG;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    sett.beginGroup("PLUGIN");
    tPlugin->jml_plugin = sett.value("JML_PLUGIN").toInt();
    tPlugin->PluginName.clear();
    for (int i = 0; i < tPlugin->jml_plugin; i++) {
        temp = "PLUGIN_" + QString::number(i+1) + "_NAME";
        temp = sett.value(temp).toString();
        tPlugin->PluginName.insert(i, temp);
        temp = "PLUGIN_" + QString::number(i+1) + "_EXEC";
        temp = sett.value(temp).toString();
        tPlugin->PluginExec.insert(i, temp);
    }
    sett.endGroup();

    code.encryp(pth);
}

QString worker::readPluginConfgName(QString address)
{
    QString temp;
    cryp code; code.decryp(address);
    QSettings sett(address, QSettings::IniFormat);

    sett.beginGroup("PLUGIN");
    temp = sett.value("PLUGIN_NAME").toString();
    sett.endGroup();

    code.encryp(address);
    return temp;
}

QString worker::readPluginConfgExec(QString address)
{
    QString temp;
    cryp code; code.decryp(address);
    QSettings sett(address, QSettings::IniFormat);

    sett.beginGroup("PLUGIN");
    temp = sett.value("PLUGIN_EXEC").toString();
    sett.endGroup();

    code.encryp(address);
    return temp;
}

void worker::writePlugin(struct t_plugin *tPlugin)
{
    QString temp;
    QString pth = PATH_PLUGIN_CONFIG;
    QSettings sett(pth, QSettings::IniFormat);

    sett.beginGroup("PLUGIN");
    sett.setValue("JML_PLUGIN", tPlugin->jml_plugin);
    for (int i = 0; i < tPlugin->jml_plugin; i++) {
        temp = "PLUGIN_" + QString::number(i+1) + "_NAME";
        sett.setValue(temp, tPlugin->PluginName.at(i));
        temp = "PLUGIN_" + QString::number(i+1) + "_EXEC";
        sett.setValue(temp, tPlugin->PluginExec.at(i));
    }
    sett.endGroup();
}

