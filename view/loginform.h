#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include "util/utama.h"
#include "view/mainwindow.h"

namespace Ui {
class loginForm;
}

class loginForm : public QDialog
{
    Q_OBJECT

public:
    explicit loginForm(QWidget *parent = 0);
    ~loginForm();

    int loginSuccess();

private slots:
    void on_loginButton_clicked();

private:
    Ui::loginForm *ui;
};

#endif // LOGINFORM_H
