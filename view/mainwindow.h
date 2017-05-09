#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QProcess>
#include <QtWidgets>

#include "util/utama.h"
#include "model/interface_manipulator/mtreeview.h"
#include "controller/worker.h"
#include "model/communication/serial.h"

#include "view/form_addmodule.h"
#include <ui_form_addmodule.h>

#include "view/settingsdialog.h"
#include "view/mainwindow.h"
#include "model/module.h"
//#include <model/interface_manipulator/qlightboxwidget.h>
#include "view/progressdialog.h"
#include "view/debugdialog.h"

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

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief ui
     */
    Ui::MainWindow *ui;

    /**
     * @brief MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // main variable //
    /**
     * @brief modelTree
     */
    QStandardItemModel *modelTree;

    /**
     * @brief Refresh_Tree
     */
    void Refresh_Tree();

    /**
     * @brief ActiveWidget
     */
    QWidget ActiveWidget[];
    /**
     * @brief ActiveAddress
     */
    QString ActiveAddress[];

    /**
     * @brief GetNamaBoard
     */
    QString GetNamaBoard;
    /**
     * @brief GetNoSeri
     */
    QString GetNoSeri;

    /**
     * @brief str_data
     */
    QString str_data;
    /**
     * @brief val_data
     */
    QStringList val_data;

//    QLightBoxWidget *busy;

    /**
     * @brief FinishRead
     */
    bool FinishRead;
    /**
     * @brief standBy
     */
    bool standBy;
    /**
     * @brief checkRinjaniPassword
     */
    void checkRinjaniPassword();

    /**
     * @brief bottom_message
     */
    QLabel *bottom_message;

public slots:
    /**
     * @brief on_actionConnect_triggered
     */
    void on_actionConnect_triggered();
    /**
     * @brief on_actionDisconnect_triggered
     */
    void on_actionDisconnect_triggered();

    /**
     * @brief readData
     */
    void readData();
    /**
     * @brief handleError
     * @param error
     */
    void handleError(QSerialPort::SerialPortError error);

private slots:
    /**
     * @brief on_actionNew_triggered
     */
    void on_actionNew_triggered();
    /**
     * @brief update_activeWindow
     */
    void update_activeWindow();
    /**
     * @brief setActiveSubWindow
     * @param window
     */
    void setActiveSubWindow(QWidget *window);

    /**
     * @brief on_actionSave_triggered
     */
    void on_actionSave_triggered();
    /**
     * @brief on_actionLoad_triggered
     */
    void on_actionLoad_triggered();
    /**
     * @brief on_actionDelete_triggered
     */
    void on_actionDelete_triggered();

    /**
     * @brief on_treeView_clicked
     * @param index
     */
    void on_treeView_clicked(const QModelIndex &index);
    /**
     * @brief on_treeView_doubleClicked
     * @param index
     */
    void on_treeView_doubleClicked(const QModelIndex &index);

    /**
     * @brief on_actionRefresh_triggered
     */
    void on_actionRefresh_triggered();
    /**
     * @brief on_actionConfig_triggered
     */
    void on_actionConfig_triggered();

    /**
     * @brief on_actionCreate_User_triggered
     */
    void on_actionCreate_User_triggered();

    /**
     * @brief on_actionEdit_User_triggered
     */
    void on_actionEdit_User_triggered();

    /**
     * @brief on_actionExit_triggered
     */
    void on_actionExit_triggered();

    void on_actionDebug_Modem_triggered();

private:
    //** Other Class **//
    /**
     * @brief NoSeri
     */
    QString NoSeri;
    /**
     * @brief SerialPort
     */
    QSerialPort *SerialPort;
    /**
     * @brief Serial
     */
    serial *Serial;

    /**
     * @brief StatusMessage
     */
    QString StatusMessage;

    /**
     * @brief mTree
     */
    mTreeview mTree;
    /**
     * @brief faddModule
     */
    form_addModule *faddModule;
    /**
     * @brief settings_dialog
     */
    SettingsDialog *settings_dialog;
    /**
     * @brief work
     */
    worker *work;
    /**
     * @brief progress_dialog
     */
    ProgressDialog *progress_dialog;
    /**
     * @brief debug_dialog
     */
    DebugDialog    *debug_dialog;

    /**
     * @brief num_window
     */
    int num_window;
    /**
     * @brief windowMapper
     */
    QSignalMapper *windowMapper;

    /**
     * @brief module_name
     */
    QString module_name[MAX_MODULE];
//    QStringList module_name;
    /**
     * @brief module_count
     */
    int module_count;

    /**
     * @brief init_signalSlots
     */
    void init_signalSlots();
    /**
     * @brief mod
     */
    module *mod;

    /**
     * @brief module_address_sv
     */
    QString module_address_sv; //for save
    /**
     * @brief module_name_sv
     */
    QString module_name_sv; //for save

    /**
     * @brief LoginForm
     */
    loginForm *LoginForm;
};

#endif // MAINWINDOW_H
