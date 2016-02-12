#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

#include <util/utama.h>
#include <model/interface_manipulator/mtreeview.h>
#include <controller/worker.h>
#include <model/communication/serial.h>

#include <view/form_addmodule.h>
#include <ui_form_addmodule.h>

namespace Ui {
class MainWindow;
}

class worker;
class serial;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    

private slots:
    void on_actionNew_triggered();
    void update_activeWindow();
    void setActiveSubWindow(QWidget *window);

    void on_actionLoad_triggered();
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionConnect_triggered();

private:
    /** Other Class **/
    mTreeview mTree;
    form_addModule *faddModule;
    worker *work;

    /** main variable **/
    QStandardItemModel *modelTree;

    int num_window;
    QSignalMapper *windowMapper;

    QString module_name[MAX_MODULE];\
    int module_count;

    void init_signalSlots();
};

#endif // MAINWINDOW_H
