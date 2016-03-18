#include "module.h"

module::module()
{

}

void module::write_module(struct t_module *tmodule){

    QStringList temp1; QString temp2; int index;
    QString pth;
    pth.sprintf("data/module/m_%s.dbe",tmodule->module_name);
    QSettings sett(pth, QSettings::IniFormat);

    sett.beginGroup( "MODULE" );
    sett.setValue("ACTIVE", tmodule->flag_active);
    sett.setValue("MODULE_NAME", tmodule->module_name);
    sett.setValue("SN", tmodule->serial_number);
    sett.setValue("FLAG_DUAL_GSM", tmodule->flag_dual_gsm);
    sett.setValue("IP_ADDRESS", tmodule->ip_address);
    sett.setValue("SERVER_ADDRESS", tmodule->server_address);
    sett.setValue("FILE_ADDRESS", tmodule->file_address);
    sett.setValue("FLAG_WEBCLIENT", tmodule->flag_webclient);
    sett.setValue("WEBCLIENT", tmodule->status_webclient);
    sett.endGroup();

    sett.beginGroup( "INPUT" );
    for (int i = 0; i < tmodule->Input.length(); i++) {
        temp2 = tmodule->Input.at(i);
        temp1 = temp2.split(';');
        temp2 = "KANAL_" + temp1.at(1);
        sett.setValue(temp2, tmodule->Input.at(i));
    }
    for (int i = 0; i < tmodule->InputName.length(); i++) {
        temp2 = tmodule->Input.at(i);
        temp1 = temp2.split(';');
        temp2 = "KANAL_NAME_" + temp1.at(1);
        sett.setValue(temp2, tmodule->InputName.at(i));
    }
    sett.endGroup();

    sett.beginGroup( "OUTPUT" );
    sett.setValue("OUTPUT_R1", tmodule->output_r1);
    sett.setValue("OUTPUT_R1_NAME", tmodule->output_r1_name);
    sett.setValue("OUTPUT_R2", tmodule->output_r2);
    sett.setValue("OUTPUT_R2_NAME", tmodule->output_r2_name);
    sett.endGroup();

    sett.beginGroup( "GSM_1" );
    sett.setValue("FLAG_GSM_1", tmodule->flag_gsm_1);
    sett.setValue("GSM_NAME_1", tmodule->name_gsm_1);
    sett.setValue("DEVICE_NAME_1", tmodule->device_name_gsm_1);
    sett.setValue("FLAG_STATUS_GSM_1", tmodule->flag_status_active_gsm_1);
    sett.setValue("STATUS_GSM_1", tmodule->status_gsm_1);
    sett.setValue("FLAG_COM_GSM_1", tmodule->flag_com_gsm_1);
    sett.setValue("COM_GSM_1", tmodule->com_gsm_1);
    sett.setValue("NUMBER_GSM_1", tmodule->number_gsm_1);
    sett.setValue("APN_GSM_1", tmodule->apn_gsm_1);
    sett.setValue("USER_GSM_1", tmodule->user_gsm_1);
    sett.setValue("PASSWD_GSM_1", tmodule->passwd_gsm_1);
    sett.endGroup();

    sett.beginGroup( "GSM_2" );
    if (tmodule->flag_dual_gsm == 1) {
        sett.setValue("FLAG_GSM_2", tmodule->flag_gsm_2);
        sett.setValue("GSM_NAME_2", tmodule->name_gsm_2);
        sett.setValue("DEVICE_NAME_2", tmodule->device_name_gsm_2);
        sett.setValue("FLAG_STATUS_GSM_2", tmodule->flag_status_active_gsm_2);
        sett.setValue("STATUS_GSM_2", tmodule->status_gsm_2);
        sett.setValue("FLAG_COM_GSM_2", tmodule->flag_com_gsm_2);
        sett.setValue("COM_GSM_2", tmodule->com_gsm_2);
        sett.setValue("NUMBER_GSM_2", tmodule->number_gsm_2);
        sett.setValue("APN_GSM_2", tmodule->apn_gsm_2);
        sett.setValue("USER_GSM_2", tmodule->user_gsm_2);
        sett.setValue("PASSWD_GSM_2", tmodule->passwd_gsm_2);
    } else {
        sett.setValue("FLAG_GSM_2", "");
        sett.setValue("GSM_NAME_2", "");
        sett.setValue("DEVICE_NAME_2", "");
        sett.setValue("FLAG_STATUS_GSM_2", "");
        sett.setValue("STATUS_GSM_2", "");
        sett.setValue("FLAG_COM_GSM_2", "");
        sett.setValue("COM_GSM_2", "");
        sett.setValue("NUMBER_GSM_2", "");
        sett.setValue("APN_GSM_2", "");
        sett.setValue("USER_GSM_2", "");
        sett.setValue("PASSWD_GSM_2", "");
    }
    sett.endGroup();

    sett.beginGroup( "SOURCES" );
    index = tmodule->sumber.length();
    for (int i = 0; i < index-1; i++) {
        temp2.sprintf("SUMBER_%d", i);
        sett.setValue(temp2, tmodule->sumber.at(i));
    }
    sett.endGroup();

    sett.beginGroup( "DATA" );
    index = tmodule->data.length();
    for (int i = 0; i < index-1; i++) {
        temp2.sprintf("DATA_%d", i);
        sett.setValue(temp2, tmodule->data.at(i));
    }
    sett.endGroup();
}

void module::update_setting(struct t_module *tmodule, QString addressModule){
    QString pth = addressModule;
    QSettings sett(pth, QSettings::IniFormat);
    QString temp;

    sett.beginGroup( "INPUT" );
    for (int i = 0; i < tmodule->Input.length()-1; i++) {
        temp.sprintf("KANAL_%d", i);
        sett.setValue(temp, tmodule->Input.at(i));
    }
    for (int i = 0; i < tmodule->InputName.length()-1; i++) {
        temp.sprintf("KANAL_NAME_%d", i);
        sett.setValue(temp, tmodule->InputName.at(i));
    }
    sett.endGroup();

    sett.beginGroup( "OUTPUT" );
    sett.setValue("OUTPUT_R1", tmodule->output_r1);
    sett.setValue("OUTPUT_R1_NAME", tmodule->output_r1_name);
    sett.setValue("OUTPUT_R2", tmodule->output_r2);
    sett.setValue("OUTPUT_R2_NAME", tmodule->output_r2_name);
    sett.endGroup();
}

void module::update_communication(struct t_module *tmodule, QString addressModule){
    QString pth = addressModule;
    QSettings sett(pth, QSettings::IniFormat);

    sett.beginGroup( "GSM_1" );
    sett.setValue("FLAG_GSM_1", tmodule->flag_gsm_1);
    sett.setValue("GSM_NAME_1", tmodule->name_gsm_1);
    sett.setValue("DEVICE_NAME_1", tmodule->device_name_gsm_1);
    sett.setValue("FLAG_STATUS_GSM_1", tmodule->flag_status_active_gsm_1);
    sett.setValue("STATUS_GSM_1", tmodule->status_gsm_1);
    sett.setValue("FLAG_COM_GSM_1", tmodule->flag_com_gsm_1);
    sett.setValue("COM_GSM_1", tmodule->com_gsm_1);
    sett.setValue("NUMBER_GSM_1", tmodule->number_gsm_1);
    sett.setValue("APN_GSM_1", tmodule->apn_gsm_1);
    sett.setValue("USER_GSM_1", tmodule->user_gsm_1);
    sett.setValue("PASSWD_GSM_1", tmodule->passwd_gsm_1);
    sett.endGroup();

    sett.beginGroup( "GSM_2" );
    if (tmodule->flag_dual_gsm == 1) {
        sett.setValue("FLAG_GSM_2", tmodule->flag_gsm_2);
        sett.setValue("GSM_NAME_2", tmodule->name_gsm_2);
        sett.setValue("DEVICE_NAME_2", tmodule->device_name_gsm_2);
        sett.setValue("FLAG_STATUS_GSM_2", tmodule->flag_status_active_gsm_2);
        sett.setValue("STATUS_GSM_2", tmodule->status_gsm_2);
        sett.setValue("FLAG_COM_GSM_2", tmodule->flag_com_gsm_2);
        sett.setValue("COM_GSM_2", tmodule->com_gsm_2);
        sett.setValue("NUMBER_GSM_2", tmodule->number_gsm_2);
        sett.setValue("APN_GSM_2", tmodule->apn_gsm_2);
        sett.setValue("USER_GSM_2", tmodule->user_gsm_2);
        sett.setValue("PASSWD_GSM_2", tmodule->passwd_gsm_2);
    } else {
        sett.setValue("FLAG_GSM_2", "");
        sett.setValue("GSM_NAME_2", "");
        sett.setValue("DEVICE_NAME_2", "");
        sett.setValue("FLAG_STATUS_GSM_2", "");
        sett.setValue("STATUS_GSM_2", "");
        sett.setValue("FLAG_COM_GSM_2", "");
        sett.setValue("COM_GSM_2", "");
        sett.setValue("NUMBER_GSM_2", "");
        sett.setValue("APN_GSM_2", "");
        sett.setValue("USER_GSM_2", "");
        sett.setValue("PASSWD_GSM_2", "");
    }
    sett.endGroup();
}

void module::update_module(struct t_module *tmodule, QString addressModule){
    QString pth = addressModule;
    QSettings sett(pth, QSettings::IniFormat);

    sett.beginGroup( "MODULE" );
//    sett.setValue("ACTIVE", tmodule->flag_active);
    sett.setValue("MODULE_NAME", tmodule->module_name);
    sett.setValue("SN", tmodule->serial_number);
//    sett.setValue("FLAG_DUAL_GSM", tmodule->flag_dual_gsm);
    sett.setValue("IP_ADDRESS", tmodule->ip_address);
    sett.setValue("SERVER_ADDRESS", tmodule->server_address);
    sett.setValue("FILE_ADDRESS", tmodule->file_address);
    sett.setValue("FLAG_WEBCLIENT", tmodule->flag_webclient);
    sett.setValue("WEBCLIENT", tmodule->status_webclient);
    sett.endGroup();
}

void module::read_module(struct t_module *tmodule, QString addressModule){
    QString pth = addressModule;
    QString temp;
    QSettings sett(pth, QSettings::IniFormat);

    tmodule->flag_active = sett.value("MODULE/ACTIVE").toInt();
    strcpy(tmodule->module_name, sett.value("MODULE/MODULE_NAME").toString().toLatin1());
    strcpy(tmodule->serial_number, sett.value("MODULE/SN").toString().toLatin1());
    strcpy(tmodule->ip_address, sett.value("MODULE/IP_ADDRESS").toString().toLatin1());
    strcpy(tmodule->server_address, sett.value("MODULE/SERVER_ADDRESS").toString().toLatin1());
    strcpy(tmodule->file_address, sett.value("MODULE/FILE_ADDRESS").toString().toLatin1());
    tmodule->flag_webclient = sett.value("MODULE/FLAG_WEBCLIENT").toInt();
    strcpy(tmodule->status_webclient, sett.value("MODULE/WEBCLIENT").toString().toLatin1());

    tmodule->flag_dual_gsm = sett.value("MODULE/FLAG_DUAL_GSM").toInt();

    int j = 0;
    for (int i = 1; i <= 16; i++) {
        if (i < 7 || i > 10) {
            temp.sprintf("INPUT/KANAL_%d", i);
            tmodule->Input.insert(j,sett.value(temp).toString());
            temp.sprintf("INPUT/KANAL_NAME_%d", i);
            tmodule->InputName.insert(j,sett.value(temp).toString());
            j++;
        }
    }

    strcpy(tmodule->output_r1, sett.value("OUTPUT/OUTPUT_R1").toString().toLatin1());
    strcpy(tmodule->output_r1_name, sett.value("OUTPUT/OUTPUT_R1_NAME").toString().toLatin1());
    strcpy(tmodule->output_r2, sett.value("OUTPUT/OUTPUT_R2").toString().toLatin1());
    strcpy(tmodule->output_r2_name, sett.value("OUTPUT/OUTPUT_R2_NAME").toString().toLatin1());

    tmodule->flag_gsm_1 = sett.value("GSM_1/FLAG_GSM_1").toInt();
    strcpy(tmodule->name_gsm_1, sett.value("GSM_1/GSM_NAME_1").toString().toLatin1());
    strcpy(tmodule->device_name_gsm_1, sett.value("GSM_1/DEVICE_NAME_1").toString().toLatin1());
    tmodule->flag_status_active_gsm_1 = sett.value("GSM_1/FLAG_STATUS_GSM_1").toInt();
    strcpy(tmodule->status_gsm_1, sett.value("GSM_1/STATUS_GSM_1").toString().toLatin1());
    tmodule->flag_com_gsm_1 = sett.value("GSM_1/FLAG_COM_GSM_1").toInt();
    strcpy(tmodule->com_gsm_1, sett.value("GSM_1/COM_GSM_1").toString().toLatin1());
    strcpy(tmodule->number_gsm_1, sett.value("GSM_1/NUMBER_GSM_1").toString().toLatin1());
    strcpy(tmodule->apn_gsm_1, sett.value("GSM_1/APN_GSM_1").toString().toLatin1());
    strcpy(tmodule->user_gsm_1, sett.value("GSM_1/USER_GSM_1").toString().toLatin1());
    strcpy(tmodule->passwd_gsm_1, sett.value("GSM_1/PASSWD_GSM_1").toString().toLatin1());

    tmodule->flag_gsm_2 = sett.value("GSM_2/FLAG_GSM_2").toInt();
    strcpy(tmodule->name_gsm_2, sett.value("GSM_2/GSM_NAME_2").toString().toLatin1());
    strcpy(tmodule->device_name_gsm_2, sett.value("GSM_2/DEVICE_NAME_2").toString().toLatin1());
    tmodule->flag_status_active_gsm_2 = sett.value("GSM_2/FLAG_STATUS_GSM_2").toInt();
    strcpy(tmodule->status_gsm_2, sett.value("GSM_2/STATUS_GSM_2").toString().toLatin1());
    tmodule->flag_com_gsm_2 = sett.value("GSM_2/FLAG_COM_GSM_2").toInt();
    strcpy(tmodule->com_gsm_2, sett.value("GSM_2/COM_GSM_2").toString().toLatin1());
    strcpy(tmodule->number_gsm_2, sett.value("GSM_2/NUMBER_GSM_2").toString().toLatin1());
    strcpy(tmodule->apn_gsm_2, sett.value("GSM_2/APN_GSM_2").toString().toLatin1());
    strcpy(tmodule->user_gsm_2, sett.value("GSM_2/USER_GSM_2").toString().toLatin1());
    strcpy(tmodule->passwd_gsm_2, sett.value("GSM_2/PASSWD_GSM_2").toString().toLatin1());

    for (int i = 0; i < 6; i++) {
        temp.sprintf("SOURCES/SUMBER_%d", i);
        tmodule->sumber.insert(i,sett.value(temp).toString());
    }

    for (int i = 0; i < 12; i++) {
        temp.sprintf("DATA/DATA_%d", i);
        tmodule->data.insert(i,sett.value(temp).toString());
    }
}

void module::save_as_module(struct t_module *tmodule, QString address){
    QString pth = address;
    QSettings sett(pth, QSettings::IniFormat);
    QString temp;

    sett.beginGroup( "MODULE" );
    sett.setValue("ACTIVE", tmodule->flag_active);
    sett.setValue("MODULE_NAME", tmodule->module_name);
    sett.setValue("SN", tmodule->serial_number);
    sett.setValue("FLAG_DUAL_GSM", tmodule->flag_dual_gsm);
    sett.setValue("IP_ADDRESS", tmodule->ip_address);
    sett.setValue("SERVER_ADDRESS", tmodule->server_address);
    sett.setValue("FILE_ADDRESS", tmodule->file_address);
    sett.setValue("FLAG_WEBCLIENT", tmodule->flag_webclient);
    sett.setValue("WEBCLIENT", tmodule->status_webclient);
    sett.endGroup();

    sett.beginGroup( "INPUT" );
    for (int i = 0; i < tmodule->Input.length()-1; i++) {
        temp.sprintf("KANAL_%d", i);
        sett.setValue(temp, tmodule->Input.at(i));
    }
    for (int i = 0; i < tmodule->InputName.length()-1; i++) {
        temp.sprintf("KANAL_NAME_%d", i);
        sett.setValue(temp, tmodule->InputName.at(i));
    }
    sett.endGroup();

    sett.beginGroup( "OUTPUT" );
    sett.setValue("OUTPUT_R1", tmodule->output_r1);
    sett.setValue("OUTPUT_R1_NAME", tmodule->output_r1_name);
    sett.setValue("OUTPUT_R2", tmodule->output_r2);
    sett.setValue("OUTPUT_R2_NAME", tmodule->output_r2_name);
    sett.endGroup();

    sett.beginGroup( "GSM_1" );
    sett.setValue("FLAG_GSM_1", tmodule->flag_gsm_1);
    sett.setValue("GSM_NAME_1", tmodule->name_gsm_1);
    sett.setValue("DEVICE_NAME_1", tmodule->device_name_gsm_1);
    sett.setValue("FLAG_STATUS_GSM_1", tmodule->flag_status_active_gsm_1);
    sett.setValue("STATUS_GSM_1", tmodule->status_gsm_1);
    sett.setValue("FLAG_COM_GSM_1", tmodule->flag_com_gsm_1);
    sett.setValue("COM_GSM_1", tmodule->com_gsm_1);
    sett.setValue("NUMBER_GSM_1", tmodule->number_gsm_1);
    sett.setValue("APN_GSM_1", tmodule->apn_gsm_1);
    sett.setValue("USER_GSM_1", tmodule->user_gsm_1);
    sett.setValue("PASSWD_GSM_1", tmodule->passwd_gsm_1);
    sett.endGroup();

    sett.beginGroup( "GSM_2" );
    sett.setValue("FLAG_GSM_2", tmodule->flag_gsm_2);
    sett.setValue("GSM_NAME_2", tmodule->name_gsm_2);
    sett.setValue("DEVICE_NAME_2", tmodule->device_name_gsm_2);
    sett.setValue("FLAG_STATUS_GSM_2", tmodule->flag_status_active_gsm_2);
    sett.setValue("STATUS_GSM_2", tmodule->status_gsm_2);
    sett.setValue("FLAG_COM_GSM_2", tmodule->flag_com_gsm_2);
    sett.setValue("COM_GSM_2", tmodule->com_gsm_2);
    sett.setValue("NUMBER_GSM_2", tmodule->number_gsm_2);
    sett.setValue("APN_GSM_2", tmodule->apn_gsm_2);
    sett.setValue("USER_GSM_2", tmodule->user_gsm_2);
    sett.setValue("PASSWD_GSM_2", tmodule->passwd_gsm_2);
    sett.endGroup();
}
