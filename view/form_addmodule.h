#ifndef FORM_ADDMODULE_H
#define FORM_ADDMODULE_H

#include <QDialog>

#include "model/module.h"

namespace Ui {
class form_addModule;
}

class form_addModule : public QDialog
{
    Q_OBJECT

public:
    Ui::form_addModule *ui;

    explicit form_addModule(QWidget *parent = 0);
    ~form_addModule();

    int accept;
    int flag_gsm_2_active;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_ck_flag_active_gsm_2_clicked(bool checked);

    void on_cb_com_1_currentIndexChanged(int index);

    void on_cb_com_2_currentIndexChanged(int index);

private:
    module mod;

};

#endif // FORM_ADDMODULE_H
