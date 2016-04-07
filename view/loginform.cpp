#include "loginform.h"
#include "ui_loginform.h"

loginForm::loginForm(QWidget *parent, QString mode) :
    QDialog(parent),
    ui(new Ui::loginForm)
{
    ui->setupUi(this);

    if (mode == "CREATE") {
        loginForm::setWindowTitle("Sarasvati - Create User Access");
        ui->loginButton->setText("SAVE");
        ui->label_4->setHidden(true);
    } else if (mode == "EDIT") {
        loginForm::setWindowTitle("Sarasvati - Edit User Access");
        ui->loginButton->setText("SAVE");
        ui->editUser->setText(this->readUserAccess_User());
        ui->editPass->setText(this->readUserAccess_Pass());
        ui->label_4->setHidden(true);
    } else {
        loginForm::setWindowTitle("Sarasvati - Log In");
        ui->loginButton->setText("LOGIN");
        ui->label_4->setHidden(false);
    }

    ui->editPass->setEchoMode(QLineEdit::Password);
    editUser = mode;
}

loginForm::~loginForm()
{
    delete ui;
}

int loginForm::loginSuccess(){
    QString user = ui->editUser->text();
    QString pass = ui->editPass->text();

    QFile usr(PATH_USER_ACCESS);
    if (!usr.exists()) {
        if((user == "admin" && pass == "sarasvati2015")) return 1;
        else if (user == "" && pass == "") return 1;
        else return 0;
    } else {
        QString userDB = this->readUserAccess_User();
        QString passDB = this->readUserAccess_Pass();

        if((user == userDB && pass == passDB)) return 1;
        else return 0;
    }
}

void loginForm::on_loginButton_clicked()
{
    if (!editUser.isEmpty()) {
        this->writeUserAccess();
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

void loginForm::writeUserAccess()
{
    QSettings sett(PATH_USER_ACCESS, QSettings::IniFormat);
    sett.setValue("USERNAME", ui->editUser->text());
    sett.setValue("PASSWORD", ui->editPass->text());
}

QString loginForm::readUserAccess_User()
{
    cryp code;
    code.decryp(PATH_USER_ACCESS);
    QSettings sett(PATH_USER_ACCESS, QSettings::IniFormat);

    QString userDB = sett.value("USERNAME").toString();

    code.encryp(PATH_USER_ACCESS);

    return userDB;
}

QString loginForm::readUserAccess_Pass()
{
    cryp code;
    code.decryp(PATH_USER_ACCESS);
    QSettings sett(PATH_USER_ACCESS, QSettings::IniFormat);

    QString passDB = sett.value("PASSWORD").toString();

    code.encryp(PATH_USER_ACCESS);

    return passDB;
}
