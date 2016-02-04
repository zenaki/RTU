#include "module.h"

module::module()
{

}

void module::write_module(struct t_module *tmodule){
    QString pth;

    pth.sprintf("data/module/m_%s.ini",tmodule->module_name);
    QSettings sett(pth, QSettings::IniFormat);

    sett.beginGroup( "MODULE" );
    sett.setValue("ACTIVE", tmodule->flag_active);
    sett.setValue("MODULE_NAME", tmodule->module_name);
    sett.setValue("SN", tmodule->serial_number);
    sett.setValue("FLAG_DUAL_GSM", tmodule->flag_dual_gsm);
    sett.endGroup();

    sett.beginGroup( "INPUT" );
    sett.setValue("INPUT_A1", tmodule->input_a1);
    sett.setValue("INPUT_A2", tmodule->input_a2);
    sett.setValue("INPUT_A3", tmodule->input_a3);
    sett.setValue("INPUT_A4", tmodule->input_a4);
    sett.setValue("INPUT_A5", tmodule->input_a5);
    sett.setValue("INPUT_A6", tmodule->input_a6);

    sett.setValue("INPUT_D1", tmodule->input_d1);
    sett.setValue("INPUT_D2", tmodule->input_d2);
    sett.setValue("INPUT_D3", tmodule->input_d3);
    sett.setValue("INPUT_D4", tmodule->input_d4);
    sett.setValue("INPUT_D5", tmodule->input_d5);
    sett.setValue("INPUT_D6", tmodule->input_d6);
    sett.setValue("INPUT_D7", tmodule->input_d7);
    sett.setValue("INPUT_D8", tmodule->input_d8);
    sett.endGroup();

    sett.beginGroup( "OUTPUT" );
    sett.setValue("OUTPUT_R1", tmodule->output_r1);
    sett.setValue("OUTPUT_R2", tmodule->output_r2);
    sett.setValue("OUTPUT_R3", tmodule->output_r3);
    sett.setValue("OUTPUT_R4", tmodule->output_r4);
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
    sett.endGroup();
}

void module::update_module(struct t_module *tmodule, QString addressModule){
    QString pth = addressModule;
    QSettings sett(pth, QSettings::IniFormat);

    sett.beginGroup( "MODULE" );
    sett.setValue("ACTIVE", tmodule->flag_active);
    sett.setValue("MODULE_NAME", tmodule->module_name);
    sett.setValue("SN", tmodule->serial_number);
    sett.setValue("FLAG_DUAL_GSM", tmodule->flag_dual_gsm);
    sett.endGroup();

    sett.beginGroup( "INPUT" );
    sett.setValue("INPUT_A1", tmodule->input_a1);
    sett.setValue("INPUT_A2", tmodule->input_a2);
    sett.setValue("INPUT_A3", tmodule->input_a3);
    sett.setValue("INPUT_A4", tmodule->input_a4);
    sett.setValue("INPUT_A5", tmodule->input_a5);
    sett.setValue("INPUT_A6", tmodule->input_a6);

    sett.setValue("INPUT_D1", tmodule->input_d1);
    sett.setValue("INPUT_D2", tmodule->input_d2);
    sett.setValue("INPUT_D3", tmodule->input_d3);
    sett.setValue("INPUT_D4", tmodule->input_d4);
    sett.setValue("INPUT_D5", tmodule->input_d5);
    sett.setValue("INPUT_D6", tmodule->input_d6);
    sett.setValue("INPUT_D7", tmodule->input_d7);
    sett.setValue("INPUT_D8", tmodule->input_d8);
    sett.endGroup();

    sett.beginGroup( "OUTPUT" );
    sett.setValue("OUTPUT_R1", tmodule->output_r1);
    sett.setValue("OUTPUT_R2", tmodule->output_r2);
    sett.setValue("OUTPUT_R3", tmodule->output_r3);
    sett.setValue("OUTPUT_R4", tmodule->output_r4);
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
    sett.endGroup();
}

void module::read_module(struct t_module *tmodule, QString addressModule){
    QString pth = addressModule;
    QSettings sett(pth, QSettings::IniFormat);

    tmodule->flag_active = sett.value("MODULE/ACTIVE").toInt();
    strcpy(tmodule->module_name, sett.value("MODULE/MODULE_NAME").toString().toLatin1());
    strcpy(tmodule->serial_number, sett.value("MODULE/SN").toString().toLatin1());

    tmodule->flag_dual_gsm = sett.value("MODULE/FLAG_DUAL_GSM").toInt();

    strcpy(tmodule->input_a1, sett.value("INPUT/INPUT_A1").toString().toLatin1());
    strcpy(tmodule->input_a2, sett.value("INPUT/INPUT_A2").toString().toLatin1());
    strcpy(tmodule->input_a3, sett.value("INPUT/INPUT_A3").toString().toLatin1());
    strcpy(tmodule->input_a4, sett.value("INPUT/INPUT_A4").toString().toLatin1());
    strcpy(tmodule->input_a5, sett.value("INPUT/INPUT_A5").toString().toLatin1());
    strcpy(tmodule->input_a6, sett.value("INPUT/INPUT_A6").toString().toLatin1());

    strcpy(tmodule->input_d1, sett.value("INPUT/INPUT_D1").toString().toLatin1());
    strcpy(tmodule->input_d2, sett.value("INPUT/INPUT_D2").toString().toLatin1());
    strcpy(tmodule->input_d3, sett.value("INPUT/INPUT_D3").toString().toLatin1());
    strcpy(tmodule->input_d4, sett.value("INPUT/INPUT_D4").toString().toLatin1());
    strcpy(tmodule->input_d5, sett.value("INPUT/INPUT_D5").toString().toLatin1());
    strcpy(tmodule->input_d6, sett.value("INPUT/INPUT_D6").toString().toLatin1());
    strcpy(tmodule->input_d7, sett.value("INPUT/INPUT_D7").toString().toLatin1());
    strcpy(tmodule->input_d8, sett.value("INPUT/INPUT_D8").toString().toLatin1());

    strcpy(tmodule->output_r1, sett.value("INPUT/OUTPUT_R1").toString().toLatin1());
    strcpy(tmodule->output_r2, sett.value("INPUT/OUTPUT_R2").toString().toLatin1());
    strcpy(tmodule->output_r3, sett.value("INPUT/OUTPUT_R3").toString().toLatin1());
    strcpy(tmodule->ouctput_r4, sett.value("INPUT/OUTPUT_R4").toString().toLatin1());

    tmodule->flag_gsm_1 = sett.value("GSM_1/FLAG_GSM_1").toInt();
    strcpy(tmodule->name_gsm_1, sett.value("GSM_1/GSM_NAME_1").toString().toLatin1());
    strcpy(tmodule->device_name_gsm_1, sett.value("GSM_1/DEVICE_NAME_1").toString().toLatin1());
    tmodule->flag_status_active_gsm_1 = sett.value("GSM_1/FLAG_STATUS_GSM_1").toInt();
    strcpy(tmodule->status_gsm_1, sett.value("GSM_1/STATUS_GSM_1").toString().toLatin1());
    tmodule->flag_com_gsm_1 = sett.value("GSM_1/FLAG_COM_GSM_1").toInt();
    strcpy(tmodule->com_gsm_1, sett.value("GSM_1/COM_GSM_1").toString().toLatin1());
    strcpy(tmodule->number_gsm_1, sett.value("GSM_1/NUMBER_GSM_1").toString().toLatin1());

    tmodule->flag_gsm_2 = sett.value("GSM_2/FLAG_GSM_2").toInt();
    strcpy(tmodule->name_gsm_2, sett.value("GSM_2/GSM_NAME_2").toString().toLatin1());
    strcpy(tmodule->device_name_gsm_2, sett.value("GSM_2/DEVICE_NAME_2").toString().toLatin1());
    tmodule->flag_status_active_gsm_2 = sett.value("GSM_2/FLAG_STATUS_GSM_2").toInt();
    strcpy(tmodule->status_gsm_2, sett.value("GSM_2/STATUS_GSM_2").toString().toLatin1());
    tmodule->flag_com_gsm_2 = sett.value("GSM_2/FLAG_COM_GSM_2").toInt();
    strcpy(tmodule->com_gsm_2, sett.value("GSM_2/COM_GSM_2").toString().toLatin1());
    strcpy(tmodule->number_gsm_2, sett.value("GSM_2/NUMBER_GSM_2").toString().toLatin1());
}
