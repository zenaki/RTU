#ifndef FORM_ADDMODULE_H
#define FORM_ADDMODULE_H

#include <QDialog>
#include <QRect>
#include "model/module.h"

#include "model/cryp.h"
class cryp;

namespace Ui {
class form_addModule;
}

class worker;

class form_addModule : public QDialog
{
    Q_OBJECT

public:
    Ui::form_addModule *ui;

    explicit form_addModule(QWidget *parent = 0, bool create = true, QString address = 0, int index = 0);
    ~form_addModule();

    bool edit;
    int accept;
    int flag_gsm_2_active;
    QString currentFile;
    QString currentName;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_ck_flag_active_gsm_2_clicked(bool checked);

    void on_cb_com_1_currentIndexChanged(int index);

    void on_cb_com_2_currentIndexChanged(int index);

    void enabledButton();

    void on_spin_interval_relay_d_valueChanged(int arg1);

    void on_spin_interval_relay_h_valueChanged(int arg1);

    void on_spin_interval_relay_m_valueChanged(int arg1);

    void on_spin_interval_data_d_valueChanged(int arg1);

    void on_spin_interval_data_h_valueChanged(int arg1);

    void on_spin_interval_data_m_valueChanged(int arg1);

private:
    bool active_button;
    module mod;
};

#endif // FORM_ADDMODULE_H
