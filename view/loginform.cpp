#include "loginform.h"
#include "ui_loginform.h"

loginForm::loginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginForm)
{
    ui->setupUi(this);

    loginForm::setWindowTitle("Sarasvati - Log In");

    ui->editPass->setEchoMode(QLineEdit::Password);
}

loginForm::~loginForm()
{
    delete ui;
}

int loginForm::loginSuccess(){
    QString user = ui->editUser->text();
    QString pass = ui->editPass->text();

    if((user == "admin" && pass == "sarasvati2015")) return 1;
    else if (user == "" && pass == "") return 1;
    else return 0;
}

void loginForm::on_loginButton_clicked()
{
    if(loginSuccess()){
        MainWindow *mWindow;
        mWindow = new MainWindow(this);

        struct t_serial_settings tSerialSetting;
        tSerialSetting.serial_set = 0;
        tSerialSetting.serial_connect = 0;

        mWindow->show();

        this->hide();
    }
    else{
        QMessageBox::warning(this, "Warning!!", "Username & Password Not Match!", 0, 0);
        return;
    }
}
