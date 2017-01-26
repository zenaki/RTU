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

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    Ui::SettingsDialog *ui;

    serial *Serial;
    setting *Setting;
    MainWindow *Main;
//    t_serial_settings currentSettings;
private slots:
    void showPortInfo(int idx);
    void apply();

    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();

    void fillSettings();
    void updateSettings(struct t_serial_settings *tSerial);

private:
//    Settings currentSettings;
    QIntValidator *intValidator;
};

#endif // SETTINGSDIALOG_H
