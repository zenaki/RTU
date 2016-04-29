#include "view/progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
}

ProgressDialog::~ProgressDialog()
{
    cancel = true;
    delete ui;
}

void ProgressDialog::Processing(QSerialPort *SerialPort, QString address, QString mode, QString index)
{
    struct t_module tModule; struct t_serial_settings tSerial;
    mod->read_module(&tModule, address);
    Serial_Com = SerialPort;
    timeout = false; flagERR = 2; strERR = "";
    cancel = false; finish = false;
    progressVal = 0;
    ui->progressBar->reset();
    if (index.isEmpty()) ui->Description->clear();
    QStringList list_mode = mode.split(';');
    QStringList list_index = index.split(';');
/** ---------------------------------------------------------- **/
    for (int i = 0; i < list_mode.length(); i++) {
        if (list_mode.at(i) == MODE_GET_ENV) {
            Request_ENV(false);
        } if (list_mode.at(i) == MODE_GET_SIM) {
            Request_SIM(false);
        } if (list_mode.at(i) == MODE_GET_I0) {
            Request_IO(false);
        } if (list_mode.at(i) == MODE_GET_SRC) {
            Request_Sumber(false);
        } if (list_mode.at(i) == MODE_GET_DAT) {
            Request_Data(false);
        } if (list_mode.at(i) == MODE_SET_ENV) {
            Set_ENV(false, &tModule);
        } if (list_mode.at(i) == MODE_SET_SIM) {
            Set_SIM(false, &tModule);
        } if (list_mode.at(i) == MODE_SET_KNL) {
            if (index.isEmpty()) {Set_Input(false, &tModule);}
            else {Set_Input(false, &tModule, list_index.at(i));}
        } if (list_mode.at(i) == MODE_SET_RLY) {
            if (index.isEmpty()) {Set_Output(false, &tModule);}
            else {Set_Output(false, &tModule, list_index.at(i));}
        } if (list_mode.at(i) == MODE_SET_SRC) {
            if (index.isEmpty()) {Set_Sumber(false, &tModule);}
            else {Set_Sumber(false, &tModule, list_index.at(i));}
        } if (list_mode.at(i) == MODE_SET_DAT) {
            if (index.isEmpty()) {Set_Data(false, &tModule);}
            else {Set_Data(false, &tModule, list_index.at(i));}
        }
    }
/** ---------------------------------------------------------- **/
    ui->progressBar->setRange(0,progressVal);
    progressVal = 0;
    for (int i = 0; i < list_mode.length(); i++) {
        if (list_mode.at(i) == MODE_GET_ENV) {
            Request_ENV(true);
            Serial->read_parsing(&tSerial);
            list1 = tSerial.str_data_env.split(";");
            Get_ENV(&tModule, list1);
        } if (list_mode.at(i) == MODE_GET_SIM) {
            Request_SIM(true);
            Serial->read_parsing(&tSerial);
            list1 = tSerial.str_data_sim.split("*");
            Get_SIM(&tModule, list1);
        } if (list_mode.at(i) == MODE_GET_I0) {
            Request_IO(true);
            Serial->read_parsing(&tSerial);
            list1 = tSerial.str_data_io.split("*");
            Get_Input(&tModule, list1);
            Get_Output(&tModule, list1);
        } if (list_mode.at(i) == MODE_GET_SRC) {
            Request_Sumber(true);
            Serial->read_parsing(&tSerial);
            list1 = tSerial.str_data_src.split("*");
            Get_Sumber(&tModule, list1);
        } if (list_mode.at(i) == MODE_GET_DAT) {
            Request_Data(true);
            Serial->read_parsing(&tSerial);
            list1 = tSerial.str_data_dat.split("*");
            Get_Data(&tModule, list1);
        } if (list_mode.at(i) == MODE_SET_ENV) {
            Set_ENV(true, &tModule);
        } if (list_mode.at(i) == MODE_SET_SIM) {
            Set_SIM(true, &tModule);
        } if (list_mode.at(i) == MODE_SET_KNL) {
            if (index.isEmpty()) {
                Set_Input(true, &tModule);
            } else {
                Set_Input(true, &tModule, list_index.at(i));
            }
        } if (list_mode.at(i) == MODE_SET_RLY) {
            if (index.isEmpty()) {
                Set_Output(true, &tModule);
            } else {
                Set_Output(true, &tModule, list_index.at(i));
            }
        } if (list_mode.at(i) == MODE_SET_SRC) {
            if (index.isEmpty()) {
                Set_Sumber(true, &tModule);
            } else {
                Set_Sumber(true, &tModule, list_index.at(i));
            }
        } if (list_mode.at(i) == MODE_SET_DAT) {
            if (index.isEmpty()) {
                Set_Data(true, &tModule);
            } else {
                Set_Data(true, &tModule, list_index.at(i));
            }
        }
        if (cancel) break;
    }
/** ---------------------------------------------------------- **/
    strcpy(tModule.module_name, address.mid(14,address.length()-18).toLatin1().data());
    mod->write_module(&tModule);
    cryp code; code.encryp(address);
    finish = true;
}

void ProgressDialog::Request_ENV(bool stat)
{
    if (stat) {
        Request = "0000\r\n";
        Desc = "Request Environment ..";
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}
}

void ProgressDialog::Request_SIM(bool stat)
{
    if (stat) {
        Request = "0001\r\n";
        Desc = "Request SIM Configuration ..";
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}
}

void ProgressDialog::Request_IO(bool stat)
{
    if (stat) {
        Request = "0002\r\n";
        Desc = "Request I/O ..";
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}
}

void ProgressDialog::Request_Signal(bool stat)
{
    if (stat) {
        Request = "0003\r\n";
        Desc = "Request Signal ..";
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}
}

void ProgressDialog::Request_Sumber(bool stat)
{
    if (stat) {
        Request = "0004\r\n";
        Desc = "Request Sources ..";
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}
}

void ProgressDialog::Request_Data(bool stat)
{
    if (stat) {
        Request = "0005\r\n";
        Desc = "Request Data ..";
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}
}

void ProgressDialog::Get_ENV(struct t_module *tModule, QStringList data)
{
    temp = data.at(0);
    strcpy(tModule->module_name, temp.toUtf8().data());
    temp = data.at(1);
    strcpy(tModule->serial_number, temp.toUtf8().data());
    temp = data.at(2);
    strcpy(tModule->ip_address, temp.toUtf8().data());
    temp = data.at(3);
    strcpy(tModule->server_address, temp.toUtf8().data());
    temp = data.at(4);
    strcpy(tModule->file_address, temp.toUtf8().data());
    temp = data.at(5);
    tModule->flag_webclient = temp.toInt();
    if (temp == "0") {
        temp = "ACTIVE";
        strcpy(tModule->status_webclient, temp.toUtf8().data());
    } else if (temp == "1") {
        temp = "NOT ACTIVE";
        strcpy(tModule->status_webclient, temp.toUtf8().data());
    }
    temp = data.at(7);
    tModule->interval = temp.toInt();
}

void ProgressDialog::Get_SIM(struct t_module *tModule, QStringList data)
{
    str = data.at(0);
    list1 = str.split(";");
    str = data.at(1);
    list2 = str.split(";");

    /** MODUlE **/
    tModule->flag_active = 1;
    if (list2.at(3) != "-") {tModule->flag_dual_gsm = 1;}
    else {tModule->flag_dual_gsm = 0;}

    /** GSM_1 **/
    temp = list1.at(1);
    if (temp == "-") {strcpy(tModule->device_name_gsm_1, "");}
    else {strcpy(tModule->device_name_gsm_1, temp.toUtf8().data());}

    temp = list1.at(2);
    if (temp == "-") {
        strcpy(tModule->name_gsm_1, "");
        tModule->flag_gsm_1 = 0;
    } else {
        strcpy(tModule->name_gsm_1, temp.toUtf8().data());
        if (temp == "TELKOMSEL") {tModule->flag_gsm_1 = 0;}
        else if (temp == "INDOSAT") {tModule->flag_gsm_1 = 1;}
        else if (temp == "XL") {tModule->flag_gsm_1 = 2;
        } else if (temp == "3") {
            tModule->flag_gsm_1 = 3;
        }
    }
    temp = list1.at(3);
    if (temp == "-") {
        strcpy(tModule->number_gsm_1, "");
    } else {
        strcpy(tModule->number_gsm_1, temp.toUtf8().data());
    }
    temp = list1.at(4);
    if (temp == "0") {
        tModule->flag_status_active_gsm_1 = temp.toInt();
        temp = "NOT ACTIVE";
        strcpy(tModule->status_gsm_1, temp.toUtf8().data());
    } else if (temp == "1") {
        tModule->flag_status_active_gsm_1 = temp.toInt();
        temp = "ACTIVE";
        strcpy(tModule->status_gsm_1, temp.toUtf8().data());
    }
    temp = list1.at(8);
    if (temp == "GSM") {
//        temp = "SMS";
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
        temp = list1.at(5);
        if (temp == "-") {
            strcpy(tModule->apn_gsm_1, "");
        } else {
            strcpy(tModule->apn_gsm_1, temp.toUtf8().data());
        }
        temp = list1.at(6);
        if (temp == "-") {
            strcpy(tModule->user_gsm_1, "");
        } else {
            strcpy(tModule->user_gsm_1, temp.toUtf8().data());
        }
        temp = list1.at(7);
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
        temp = list2.at(1);
        if (temp == "-") {
            strcpy(tModule->device_name_gsm_2, "");
        } else {
            strcpy(tModule->device_name_gsm_2, temp.toUtf8().data());
        }
        temp = list2.at(2);
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
        temp = list2.at(3);
        if (temp == "-") {
            strcpy(tModule->number_gsm_2, "");
        } else {
            strcpy(tModule->number_gsm_2, temp.toUtf8().data());
        }
        temp = list2.at(4);
        if (temp == "0") {
            tModule->flag_status_active_gsm_2 = temp.toInt();
            temp = "NOT ACTIVE";
            strcpy(tModule->status_gsm_2, temp.toUtf8().data());
        } else if (temp == "1") {
            tModule->flag_status_active_gsm_2 = temp.toInt();
            temp = "ACTIVE";
            strcpy(tModule->status_gsm_2, temp.toUtf8().data());
        }
        temp = list2.at(8);
        if (temp == "GSM") {
//            temp = "SMS";
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
            temp = list2.at(5);
            if (temp == "-") {
                strcpy(tModule->apn_gsm_2, "");
            } else {
                strcpy(tModule->apn_gsm_2, temp.toUtf8().data());
            }
            temp = list2.at(6);
            if (temp == "-") {
                strcpy(tModule->user_gsm_2, "");
            } else {
                strcpy(tModule->user_gsm_2, temp.toUtf8().data());
            }
            temp = list2.at(7);
            if (temp == "-") {
                strcpy(tModule->passwd_gsm_2, "");
            } else {
                strcpy(tModule->passwd_gsm_2, temp.toUtf8().data());
            }
        }
    }
}

void ProgressDialog::Get_Input(struct t_module *tModule, QStringList data)
{
    tModule->Input.clear();
    int index = 0;
    for (int i = 0; i < data.length(); i++) {
        temp = data.at(i);
        if (temp.mid(0,1) == "D" || temp.mid(0,1) == "A") {
            tModule->Input.insert(index, data.at(i));
            index++;
        }
    }
    tModule->jml_input_digital = 0;
    tModule->jml_input_analog = 0;
    for (int i = 0; i < tModule->Input.length(); i++) {
        temp = tModule->Input.at(i);
        if (temp.mid(0,1) == "D") {
            tModule->jml_input_digital++;
        } else if (temp.mid(0,1) == "A") {
            tModule->jml_input_analog++;
        }
    }
    QStringList list; QStringList list2;
    tModule->InputName.clear();
    for (int i = 0; i < tModule->Input.length(); i++) {
        temp = tModule->Input.at(i);
        list = temp.split(';');
        for (int j = 0; j < tModule->data.length(); j++) {
            temp = tModule->data.at(j);
            list2 = temp.split(';');
            if (list.at(1) == list2.at(0)) {
                tModule->InputName.insert(i, list2.at(2));
                break;
            }
        }
    }
}

void ProgressDialog::Get_Output(struct t_module *tModule, QStringList data)
{
    tModule->Output.clear();
    int index = 0;
    for (int i = 0; i < data.length(); i++) {
        temp = data.at(i);
        if (temp.mid(0,1) == "R") {
            tModule->Output.insert(index, data.at(i));
            index++;
        }
    }
    tModule->jml_output = tModule->Output.length();
    tModule->OutputName.clear();
    for (int i = 0; i < tModule->Output.length(); i++) {
        tModule->OutputName.insert(i, "");
    }
}

void ProgressDialog::Get_Sumber(struct t_module *tModule, QStringList data)
{
    tModule->sumber.clear();
    tModule->jml_sumber = 0;
    for (int i = 0; i < data.length(); i++) {
        if (data.at(i) != "") {
            tModule->sumber.insert(tModule->jml_sumber, data.at(i));
            tModule->jml_sumber++;
        }
    }
}

void ProgressDialog::Get_Data(struct t_module *tModule, QStringList data)
{
    tModule->data.clear();
    tModule->jml_data = 0;
    for (int i = 0; i < data.length(); i++) {
        if (data.at(i) != "") {
            tModule->data.insert(tModule->jml_data, data.at(i));
            tModule->jml_data++;
        }
    }
}

void ProgressDialog::Set_ENV(bool stat, t_module *tModule)
{
    /** SET ENVIRONTMENT **/
    Request.sprintf("0100 %s %s %s %s %d %d\r\n"
                    , tModule->module_name
                    , tModule->serial_number
                    , tModule->server_address
                    , tModule->file_address
                    , tModule->flag_webclient
                    , tModule->interval);
    Desc.sprintf("Set Environtment \"%s \" ..", tModule->module_name);
    if (stat) {
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}
}

void ProgressDialog::Set_SIM(bool stat, t_module *tModule)
{
    /** SET SIM 1 **/
    Request.sprintf("0101 1 %s %s %s %d %s %s %s %s"
                    , tModule->device_name_gsm_1
                    , tModule->name_gsm_1
                    , tModule->number_gsm_1
                    , tModule->flag_status_active_gsm_1
                    , tModule->apn_gsm_1
                    , tModule->user_gsm_1
                    , tModule->passwd_gsm_1
                    , tModule->com_gsm_1);
    Desc.sprintf("Set SIM 1 Configuration (\"%s\") ..", tModule->device_name_gsm_1);
    if (stat) {
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}

    /** SET SIM 2 **/
    Request.sprintf("0101 2 %s %s %s %d %s %s %s %s"
                    , tModule->device_name_gsm_2
                    , tModule->name_gsm_2
                    , tModule->number_gsm_2
                    , tModule->flag_status_active_gsm_2
                    , tModule->apn_gsm_2
                    , tModule->user_gsm_2
                    , tModule->passwd_gsm_2
                    , tModule->com_gsm_2);
    Desc.sprintf("Set SIM 2 Configuration (\"%s\") ..", tModule->device_name_gsm_2);
    if (stat) {
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}
}

void ProgressDialog::Set_Input(bool stat, t_module *tModule, QString index)
{
    /** SET INPUT DIGITAL **/
    if (index.isEmpty()) {
        for (int i = 0; i < tModule->Input.length(); i++) {
            temp = tModule->Input.at(i);
            list1 = temp.split(';');

            Request = "0102 " + list1.at(1) + " " + list1.at(2) + " " + list1.at(3) + " " + list1.at(4) + "\r\n";
            Desc = "Set Input Channel " + list1.at(1) + " ..";
            if (stat) {
                serial_write(Desc, Request, WAIT_WRITE);
                ui->progressBar->setValue(progressVal++);
            } else {progressVal++;}
            if (cancel) break;
        }
    } else {
        temp = tModule->Input.at(index.toInt());
        list1 = temp.split(';');

        Request = "0102 " + list1.at(1) + " " + list1.at(2) + " " + list1.at(3) + " " + list1.at(4) + "\r\n";
        Desc = "Set Input Channel " + list1.at(1) + " ..";
        if (stat) {
            serial_write(Desc, Request, WAIT_WRITE);
            ui->progressBar->setValue(progressVal++);
        } else {progressVal++;}
    }
}

void ProgressDialog::Set_Output(bool stat, t_module *tModule, QString index)
{
    if (index.isEmpty()) {
        /** SET OUTPUT RELAY **/
        for (int i = 0; i < tModule->Output.length(); i++) {
            temp = tModule->Output.at(i);
            list1 = temp.split(';');
            Request = "0103 " + list1.at(1) + " " + list1.at(2) + " " + list1.at(4) + "\r\n";
            Desc = "Set Output Channel " + list1.at(1) + " ..";
            if (stat) {
                serial_write(Desc, Request, WAIT_WRITE);
                ui->progressBar->setValue(progressVal++);
            } else {progressVal++;}
            if (cancel) break;
        }
    } else {
        temp = tModule->Output.at(index.toInt());
        list1 = temp.split(';');
        Request = "0103 " + list1.at(1) + " " + list1.at(2) + " " + list1.at(4) + "\r\n";
        Desc = "Set Output Channel " + list1.at(1) + " ..";
        if (stat) {
            serial_write(Desc, Request, WAIT_WRITE);
            ui->progressBar->setValue(progressVal++);
        } else {progressVal++;}
    }
}

void ProgressDialog::Set_Sumber(bool stat, t_module *tModule, QString index)
{
    if (index.isEmpty()) {
        for (int i = 0; i < tModule->sumber.length(); i++) {
            temp = tModule->sumber.at(i);
            list1 = temp.split(";");

            Request = "0104 " + list1.at(0) + " " + list1.at(1) + " " +
                      list1.at(2) + " " + list1.at(3) + " " + list1.at(4) + " " +
                      list1.at(5) + ";" + list1.at(6) + ";" + list1.at(7) + ";" +
                      list1.at(8) + ";" + list1.at(9) + ";" +
                      list1.at(10) + ";" + list1.at(11) + "\r\n";
            Desc = "Set Sources " + list1.at(0) + " : \"" + list1.at(1) + "\" ..";
            if (stat) {
                serial_write(Desc, Request, WAIT_WRITE);
                ui->progressBar->setValue(progressVal++);
            } else {progressVal++;}

            if (list1.at(5) != "0" && list1.at(11) != "") {
                temp = list1.at(11);
                for (int k = 0; k < tModule->data.length(); k++) {
                    str = tModule->data.at(k);
                    list2 = str.split(';');
                    if (temp == list2.at(1)) {
                        str = list2.at(0);
                        break;
                    }
                }
                temp = list1.at(10);
                for (int j = 0; j < temp.toInt()/2; j++) {
                    Request = "set_data " + QString::number(str.toInt()+j) +
                              " status " + list1.at(4);
                    if (list1.at(4) == "1") {
                        Desc = "Set Data " + QString::number(str.toInt()+j) + " with status : ACTIVE ..";
                    } else {
                        Desc = "Set Data " + QString::number(str.toInt()+j) + " with status : NOT ACTIVE ..";
                    }
                    if (stat) {
                        serial_write(Desc, Request, WAIT_WRITE);
                        ui->progressBar->setValue(progressVal++);
                    } else {progressVal++;}
                }
            }
            if (cancel) break;
        }
    } else {
        temp = tModule->sumber.at(index.toInt());
        list1 = temp.split(";");

        Request = "0104 " + list1.at(0) + " " + list1.at(1) + " " +
                  list1.at(2) + " " + list1.at(3) + " " + list1.at(4) + " " +
                  list1.at(5) + ";" + list1.at(6) + ";" + list1.at(7) + ";" +
                  list1.at(8) + ";" + list1.at(9) + ";" +
                  list1.at(10) + ";" + list1.at(11) + "r\n";
        Desc = "Set Sources " + list1.at(0) + " : \"" + list1.at(1) + "\" ..";
        if (stat) {
            serial_write(Desc, Request, WAIT_WRITE);
            ui->progressBar->setValue(progressVal++);
        } else {progressVal++;}

        if (list1.at(5) != "0" && list1.at(11) != "") {
            temp = list1.at(11);
            for (int k = 0; k < tModule->data.length(); k++) {
                str = tModule->data.at(k);
                list2 = str.split(';');
                if (temp == list2.at(1)) {
                    str = list2.at(0);
                    break;
                }
            }
            temp = list1.at(10);
            for (int j = 0; j < temp.toInt()/2; j++) {
                Request = "set_data " + QString::number(str.toInt()+j) +
                          " status " + list1.at(4);
                if (list1.at(4) == "1") {
                    Desc = "Set Data " + QString::number(str.toInt()+j) + " with status : ACTIVE ..";
                } else {
                    Desc = "Set Data " + QString::number(str.toInt()+j) + " with status : NOT ACTIVE ..";
                }
                if (stat) {
                    serial_write(Desc, Request, WAIT_WRITE);
                    ui->progressBar->setValue(progressVal++);
                } else {progressVal++;}
            }
        }
    }
}

void ProgressDialog::Set_Data(bool stat, t_module *tModule, QString index)
{
    if (index.isEmpty()) {
        for (int i = 0; i < tModule->data.length(); i++) {
            temp = tModule->data.at(i);
            list1 = temp.split(";");

            Request = "0105 " + list1.at(0) + " " + list1.at(1) + " " +
                      list1.at(2) + " " + list1.at(4) + " " + list1.at(5) + " " +
                      list1.at(6) + " " + list1.at(7) + " " + list1.at(8) + " " +
                      list1.at(9) + " " + list1.at(10) + " " + list1.at(11) + "\r\n";
            Desc = "Set Data " + list1.at(0) + " ..";
            if (stat) {
                serial_write(Desc, Request, WAIT_WRITE);
                ui->progressBar->setValue(progressVal++);
            } else {progressVal++;}
            if (cancel) break;
        }
    } else {
        temp = tModule->data.at(index.toInt());
        list1 = temp.split(";");

        Request = "0105 " + list1.at(0) + " " + list1.at(1) + " " +
                  list1.at(2) + " " + list1.at(4) + " " + list1.at(5) + " " +
                  list1.at(6) + " " + list1.at(7) + " " + list1.at(8) + " " +
                  list1.at(9) + " " + list1.at(10) + " " + list1.at(11) + "\r\n";
        Desc = "Set Data " + list1.at(0)  + " ..";
        if (stat) {
            serial_write(Desc, Request, WAIT_WRITE);
            ui->progressBar->setValue(progressVal++);
        } else {progressVal++;}
    }
}

void ProgressDialog::Reset_Board(bool stat)
{
    Request = "reset\r\n";
    Desc = "Reset Board ..";
    if (stat) {
        serial_write(Desc, Request, WAIT_WRITE);
        ui->progressBar->setValue(progressVal++);
    } else {progressVal++;}
}

void ProgressDialog::write_FinishRead(bool FinishRead, int cekErr, QString strErr)
{
    pth = PATH_SERIAL_PARSING;
    QSettings sett(pth, QSettings::IniFormat);

    sett.setValue("FINISH_READ", FinishRead);
    sett.setValue("ERROR_FLAG", cekErr);
    sett.setValue("ERROR_STRING", strErr);
}

bool ProgressDialog::read_FinishRead()
{
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    bool FinishRead = sett.value("FINISH_READ").toBool();

    code.encryp(pth);
    return FinishRead;
}

int ProgressDialog::read_flagERR()
{
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    int flagERR = sett.value("ERROR_FLAG").toInt();

    code.encryp(pth);
    return flagERR;
}

QString ProgressDialog::read_strERR()
{
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    QString strERR = sett.value("ERROR_STRING").toString();

    code.encryp(pth);
    return strERR;
}

void ProgressDialog::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void ProgressDialog::serial_write(QString desc, QString data, int delay_char)
{
    ui->Description->append(desc);
    QString tmp;
    data.remove("\r\n");
    for (int i = 0; i < data.length(); i++) {
        tmp = QChar(data.at(i));
        Serial_Com->write(tmp.toUtf8().data());
        delay(delay_char);
    }
    Serial_Com->write("\r\n");
    waiting_set();
    flagERR = read_flagERR();
    strERR = read_strERR();
//    if (timeout) {QMessageBox::information(this, "Serial Communication", STR_TIMEOUT, 0, 0);}
//    if (flagERR == 1) {QMessageBox::information(this, "Serial Communication", "ERROR !!\r\n" + strERR, 0, 0);}
    if (timeout) {ui->Description->append("TIMEOUT\r\n");}
    else if (flagERR == 1) {ui->Description->append("ERROR !! : " + strERR + "\r\n");}
    else {ui->Description->append("OK\r\n");}
    writeLogFile(data,flagERR,strERR,timeout);
    timeout = false; flagERR = 2; strERR = "";

    this->write_FinishRead(timeout,flagERR,strERR);
    cryp code; code.encryp(PATH_SERIAL_PARSING);
}

void ProgressDialog::waiting_set()
{
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
}

void ProgressDialog::writeLogFile(QString log, int flagERR, QString strERR, bool timeout)
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
}

void ProgressDialog::on_pbDetail_clicked()
{
    if (ui->Description->isHidden()) {
        ui->Description->setHidden(false);
    } else {
        ui->Description->setHidden(true);
    }
}

void ProgressDialog::on_pbCancel_clicked()
{
    cancel = true;
}
