#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include "util/utama.h"
#include "model/communication/serial.h"
#include "view/mainwindow.h"

namespace Ui {
class loginForm;
}

class loginForm : public QDialog
{
    Q_OBJECT

public:
    explicit loginForm(QWidget *parent = 0, QString mode = 0);
    ~loginForm();

    int loginSuccess();
    QString editUser;

private slots:
    void on_loginButton_clicked();
    void writeUserAccess();
    QString readUserAccess_User();
    QString readUserAccess_Pass();

private:
    Ui::loginForm *ui;
};

#endif // LOGINFORM_H
