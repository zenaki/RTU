#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "util/utama.h"
#include "model/communication/serial.h"
#include "model/setting.h"
#include "view/mainwindow.h"

#include <QDialog>
#include <QtSerialPort/QSerialPort>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

namespace Ui {
    class SettingsDialog;
}

class QIntValidator;

QT_END_NAMESPACE

class MainWindow;
class serial;
class setting;

/**
 * @brief The SettingsDialog class
 */
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief SettingsDialog
     * @param parent
     */
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    /**
     * @brief ui
     */
    Ui::SettingsDialog *ui;

    /**
     * @brief Serial
     */
    serial *Serial;
    /**
     * @brief Setting
     */
    setting *Setting;
    /**
     * @brief Main
     */
    MainWindow *Main;
//    t_serial_settings currentSettings;

    /**
     * @brief updateSettings
     * @param tSerial
     */
    void updateSettings(struct t_serial_settings *tSerial);
private slots:
    /**
     * @brief showPortInfo
     * @param idx
     */
    void showPortInfo(int idx);
    /**
     * @brief apply
     */
    void apply();

    /**
     * @brief checkCustomBaudRatePolicy
     * @param idx
     */
    void checkCustomBaudRatePolicy(int idx);
    /**
     * @brief checkCustomDevicePathPolicy
     * @param idx
     */
    void checkCustomDevicePathPolicy(int idx);

private:
    /**
     * @brief fillPortsParameters
     */
    void fillPortsParameters();
    /**
     * @brief fillPortsInfo
     */
    void fillPortsInfo();

    /**
     * @brief fillSettings
     */
    void fillSettings();

private:
//    Settings currentSettings;
    /**
     * @brief intValidator
     */
    QIntValidator *intValidator;
};

#endif // SETTINGSDIALOG_H
