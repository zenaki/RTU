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

/**
 * @brief The form_addModule class
 */
class form_addModule : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ui
     */
    Ui::form_addModule *ui;

    /**
     * @brief form_addModule
     * @param parent
     * @param create
     * @param address
     * @param index
     */
    explicit form_addModule(QWidget *parent = 0, bool create = true, QString address = 0, int index = 0);
    ~form_addModule();

    /**
     * @brief edit
     */
    bool edit;
    /**
     * @brief accept
     */
    int accept;
    /**
     * @brief flag_gsm_2_active
     */
    int flag_gsm_2_active;
    /**
     * @brief currentFile
     */
    QString currentFile;
    /**
     * @brief currentName
     */
    QString currentName;

private slots:
    /**
     * @brief on_buttonBox_accepted
     */
    void on_buttonBox_accepted();
    /**
     * @brief on_buttonBox_rejected
     */
    void on_buttonBox_rejected();

    /**
     * @brief on_ck_flag_active_gsm_2_clicked
     * @param checked
     */
    void on_ck_flag_active_gsm_2_clicked(bool checked);

    /**
     * @brief on_cb_com_1_currentIndexChanged
     * @param index
     */
    void on_cb_com_1_currentIndexChanged(QString index);

    /**
     * @brief on_cb_com_2_currentIndexChanged
     * @param index
     */
    void on_cb_com_2_currentIndexChanged(QString index);

    /**
     * @brief enabledButton
     */
    void enabledButton();

    /**
     * @brief on_spin_interval_relay_d_valueChanged
     * @param arg1
     */
    void on_spin_interval_relay_d_valueChanged(int arg1);

    /**
     * @brief on_spin_interval_relay_h_valueChanged
     * @param arg1
     */
    void on_spin_interval_relay_h_valueChanged(int arg1);

    /**
     * @brief on_spin_interval_relay_m_valueChanged
     * @param arg1
     */
    void on_spin_interval_relay_m_valueChanged(int arg1);

    /**
     * @brief on_spin_interval_data_d_valueChanged
     * @param arg1
     */
    void on_spin_interval_data_d_valueChanged(int arg1);

    /**
     * @brief on_spin_interval_data_h_valueChanged
     * @param arg1
     */
    void on_spin_interval_data_h_valueChanged(int arg1);

    /**
     * @brief on_spin_interval_data_m_valueChanged
     * @param arg1
     */
    void on_spin_interval_data_m_valueChanged(int arg1);

private:
    /**
     * @brief active_button
     */
    bool active_button;
    /**
     * @brief mod
     */
    module mod;
};

#endif // FORM_ADDMODULE_H
