#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include "util/utama.h"
#include "model/communication/serial.h"
#include "view/mainwindow.h"

namespace Ui {
    class loginForm;
}

/**
 * @brief The loginForm class
 */
class loginForm : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief loginForm
     * @param parent
     * @param mode
     */
    explicit loginForm(QWidget *parent = 0, QString mode = 0);
    ~loginForm();

    /**
     * @brief loginSuccess
     * @return
     */
    int loginSuccess();

    /**
     * @brief formMode
     */
    QString formMode;
    /**
     * @brief writeUserAccess
     * @param user
     * @param pass
     */
    void writeUserAccess(QString user, QString pass);
    /**
     * @brief readUser
     * @return
     */
    QString readUser();
    /**
     * @brief readPass
     * @return
     */
    QString readPass();

private slots:
    /**
     * @brief on_loginButton_clicked
     */
    void on_loginButton_clicked();

private:
    /**
     * @brief ui
     */
    Ui::loginForm *ui;
};

#endif // LOGINFORM_H
