#ifndef SETTING_H
#define SETTING_H

#include "model/cryp.h"
class cryp;

#include "util/utama.h"

#include "view/settingsdialog.h"
#include "ui_settingsdialog.h"

class SettingsDialog;

class setting
{
public:
    setting();

    void write_setting(SettingsDialog *s_d, struct t_serial_settings *tSerial);
    void read_setting(struct t_serial_settings *tSerial);
    bool checkSetting();
};

#endif // SETTING_H
