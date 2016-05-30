#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QProcess>
#include <QtWidgets>

#include <util/utama.h>
#include <model/interface_manipulator/mtreeview.h>
#include <controller/worker.h>
#include <model/communication/serial.h>

#include <view/form_addmodule.h>
#include <ui_form_addmodule.h>

#include <view/settingsdialog.h>
#include <view/mainwindow.h>
#include <model/module.h>
//#include <model/interface_manipulator/qlightboxwidget.h>
#include <view/progressdialog.h>

#include <view/loginform.h>
#include <ui_loginform.h>
class loginForm;

namespace Ui {
class MainWindow;
}

class worker;
class serial;
class module;
//class QLightBoxWidget;
class ProgressDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /** main variable **/
    QStandardItemModel *modelTree;

    void Refresh_Tree();

    QWidget ActiveWidget[];
    QString ActiveAddress[];

    QString GetNamaBoard;
    QString GetNoSeri;

    QString str_data;
    QStringList val_data;

//    QLightBoxWidget *busy;

    bool FinishRead;

    QLabel *bottom_message;

public slots:
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();

    void readData();
    void handleError(QSerialPort::SerialPortError error);

private slots:
    void on_actionNew_triggered();
    void update_activeWindow();
    void setActiveSubWindow(QWidget *window);

    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionDelete_triggered();

    void on_treeView_clicked(const QModelIndex &index);
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionRefresh_triggered();
    void on_actionConfig_triggered();

    void on_actionCreate_User_triggered();

    void on_actionEdit_User_triggered();

private:
    /** Other Class **/
    QString NoSeri;
    QSerialPort *SerialPort;
    serial *Serial;

    QString StatusMessage;

    mTreeview mTree;
    form_addModule *faddModule;
    SettingsDialog *settings_dialog;
    worker *work;
    ProgressDialog *progress_dialog;

    int num_window;
    QSignalMapper *windowMapper;

    QString module_name[MAX_MODULE];
//    QStringList module_name;
    int module_count;

    void init_signalSlots();
    module *mod;

    QString module_address_sv; //for save
    QString module_name_sv; //for save

    loginForm *LoginForm;
};

#endif // MAINWINDOW_H
