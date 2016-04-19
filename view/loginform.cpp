#include "loginform.h"
#include "ui_loginform.h"

loginForm::loginForm(QWidget *parent, QString mode) :
    QDialog(parent),
    ui(new Ui::loginForm)
{
    ui->setupUi(this);

    formMode = mode;
    if (formMode == "CREATE") {
        ui->label_4->setHidden(true);
        ui->loginButton->setText("Create User");
    } else if (formMode == "EDIT") {
        ui->editUser->setText(this->readUser());
        ui->editPass->setText(this->readPass());
        ui->label_4->setHidden(true);
        ui->loginButton->setText("Edit User");
    } else {
        ui->label_4->setHidden(false);
        loginForm::setWindowTitle("Sarasvati - Log In");
        ui->loginButton->setText("Login");
    }

    ui->editPass->setEchoMode(QLineEdit::Password);
}

loginForm::~loginForm()
{
    delete ui;
}

int loginForm::loginSuccess(){
    QString user = ui->editUser->text();
    QString pass = ui->editPass->text();

    QFile usr(PATH_USER_ACCESS);
    if (usr.exists()) {
        if (user == this->readUser() && pass == this->readPass()) return 1;
        else return 0;
    } else {
        if((user == "admin" && pass == "sarasvati2015")) return 1;
        else if (user == "" && pass == "") return 1;
        else return 0;
    }
}

void loginForm::writeUserAccess(QString user, QString pass)
{
    QSettings sett(PATH_USER_ACCESS, QSettings::IniFormat);
    sett.setValue("USER", user.toUtf8());
    sett.setValue("PASSWORD", pass.toUtf8());
}

QString loginForm::readUser()
{
    cryp code; code.decryp(PATH_USER_ACCESS);
    QSettings sett(PATH_USER_ACCESS, QSettings::IniFormat);
    QString user = sett.value("USER").toString();
    code.encryp(PATH_USER_ACCESS);
    return user;
}

QString loginForm::readPass()
{
    cryp code; code.decryp(PATH_USER_ACCESS);
    QSettings sett(PATH_USER_ACCESS, QSettings::IniFormat);
    QString pass = sett.value("PASSWORD").toString();
    code.encryp(PATH_USER_ACCESS);
    return pass;
}

void loginForm::on_loginButton_clicked()
{
    if (formMode == "CREATE" || formMode == "EDIT") {
        this->writeUserAccess(ui->editUser->text(), ui->editPass->text());
        cryp code; code.encryp(PATH_USER_ACCESS);
        this->hide();
    } else {
        if(loginSuccess()){
            MainWindow *mWindow;
            mWindow = new MainWindow(this);
            mWindow->showMaximized();

            this->hide();
        } else {
            QMessageBox::warning(this, "Warning!!", "Username & Password Not Match!", 0, 0);
            return;
        }
    }
}
