#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "util/utama.h"
#include "model/communication/serial.h"

#include <QDialog>
#include <QtSerialPort/QSerialPort>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

namespace Ui {
class SettingsDialog;
}

class QIntValidator;
class serial;

QT_END_NAMESPACE

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0, struct t_serial_settings *tSerial = 0);
    ~SettingsDialog();
    serial *Serial;
//    t_serial_settings currentSettings;
private slots:
    void showPortInfo(int idx);
    void apply();

    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings(struct t_serial_settings *tSerial);

private:
    Ui::SettingsDialog *ui;
//    Settings currentSettings;
    QIntValidator *intValidator;
};

#endif // SETTINGSDIALOG_H
