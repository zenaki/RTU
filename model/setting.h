#ifndef SETTING_H
#define SETTING_H

#include "model/cryp.h"
class cryp;

#include "util/utama.h"

#include "view/settingsdialog.h"
#include "ui_settingsdialog.h"

class SettingsDialog;

/**
 * @brief The setting class
 */
class setting
{
public:
    /**
     * @brief setting
     */
    setting();

    /**
     * @brief write_setting
     * @param s_d
     * @param tSerial
     */
    void write_setting(SettingsDialog *s_d, struct t_serial_settings *tSerial);
    /**
     * @brief read_setting
     * @param tSerial
     */
    void read_setting(struct t_serial_settings *tSerial);
    /**
     * @brief checkSetting
     * @return
     */
    bool checkSetting();
};

#endif // SETTING_H
