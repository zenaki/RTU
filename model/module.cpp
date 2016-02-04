#include "module.h"

module::module()
{

}

void module::write_module(struct t_module *tmodule){
    QString pth;

    pth.sprintf("data/module/m_%s.ini",tmodule->module_name);
    QSettings sett(pth, QSettings::IniFormat);

    sett.setValue("ACTIVE", tmodule->flag_active);
    sett.setValue("MODULE_NAME", tmodule->module_name);
    sett.setValue("SN", tmodule->serial_number);
    sett.setValue("FLAG_DUAL_GSM", tmodule->flag_dual_gsm);

    sett.setValue("FLAG_GSM_1", tmodule->flag_gsm_1);
    sett.setValue("GSM_NAME_1", tmodule->name_gsm_1);
    sett.setValue("DEVICE_NAME_1", tmodule->device_name_gsm_1);
    sett.setValue("FLAG_STATUS_GSM_1", tmodule->flag_status_active_gsm_1);
    sett.setValue("STATUS_GSM_1", tmodule->status_gsm_1);
    sett.setValue("FLAG_COM_GSM_1", tmodule->flag_com_gsm_1);
    sett.setValue("COM_GSM_1", tmodule->com_gsm_1);
    sett.setValue("NUMBER_GSM_1", tmodule->number_gsm_1);

    sett.setValue("FLAG_GSM_2", tmodule->flag_gsm_2);
    sett.setValue("GSM_NAME_2", tmodule->name_gsm_2);
    sett.setValue("DEVICE_NAME_2", tmodule->device_name_gsm_2);
    sett.setValue("FLAG_STATUS_GSM_2", tmodule->flag_status_active_gsm_2);
    sett.setValue("STATUS_GSM_2", tmodule->status_gsm_2);
    sett.setValue("FLAG_COM_GSM_2", tmodule->flag_com_gsm_2);
    sett.setValue("COM_GSM_2", tmodule->com_gsm_2);
    sett.setValue("NUMBER_GSM_2", tmodule->number_gsm_2);
}

void module::read_module(struct t_module *tmodule, QString addressModule){
    QString pth = addressModule;
    QSettings sett(pth, QSettings::IniFormat);

    tmodule->flag_active = sett.value("ACTIVE").toInt();
    strcpy(tmodule->module_name, sett.value("MODULE_NAME").toString().toLatin1());
    strcpy(tmodule->serial_number, sett.value("SN").toString().toLatin1());

    tmodule->flag_dual_gsm = sett.value("FLAG_DUAL_GSM").toInt();

    tmodule->flag_gsm_1 = sett.value("FLAG_GSM_1").toInt();
    strcpy(tmodule->name_gsm_1, sett.value("GSM_NAME_1").toString().toLatin1());
    strcpy(tmodule->device_name_gsm_1, sett.value("DEVICE_NAME_1").toString().toLatin1());
    tmodule->flag_status_active_gsm_1 = sett.value("FLAG_STATUS_GSM_1").toInt();
    strcpy(tmodule->status_gsm_1, sett.value("STATUS_GSM_1").toString().toLatin1());
    tmodule->flag_com_gsm_1 = sett.value("FLAG_COM_GSM_1").toInt();
    strcpy(tmodule->com_gsm_1, sett.value("COM_GSM_1").toString().toLatin1());
    strcpy(tmodule->number_gsm_1, sett.value("NUMBER_GSM_1").toString().toLatin1());

    tmodule->flag_gsm_2 = sett.value("FLAG_GSM_2").toInt();
    strcpy(tmodule->name_gsm_2, sett.value("GSM_NAME_2").toString().toLatin1());
    strcpy(tmodule->device_name_gsm_2, sett.value("DEVICE_NAME_2").toString().toLatin1());
    tmodule->flag_status_active_gsm_2 = sett.value("FLAG_STATUS_GSM_2").toInt();
    strcpy(tmodule->status_gsm_2, sett.value("STATUS_GSM_2").toString().toLatin1());
    tmodule->flag_com_gsm_2 = sett.value("FLAG_COM_GSM_2").toInt();
    strcpy(tmodule->com_gsm_2, sett.value("COM_GSM_2").toString().toLatin1());
    strcpy(tmodule->number_gsm_2, sett.value("NUMBER_GSM_2").toString().toLatin1());
}
