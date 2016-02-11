#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingsdialog.h"

#include <QMessageBox>
#include <QDebug>
#include <QtSerialPort/QSerialPort>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setWindowTitle("Sarasvati - MONITA RTU Configuration");
    ui->treeView->header()->setHidden(true);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    init_signalSlots();

    module_count = 0;

    modelTree = new QStandardItemModel();
    mTree.add_firstItem(modelTree, ui->treeView, "Module");

    /** check current module active **/
    QDir path("data/module");
    QStringList files = path.entryList(QDir::Files);

    QString moduleName;
    QString filePath;
    for(int i = 0; i < files.count(); i++){
        moduleName = work->check_statusModule(QString(files.at(i)));

        if(moduleName != "none"){
            filePath.sprintf("data/module/%s", moduleName.toUtf8().data());

            module_name[module_count] = work->loadModule(modelTree, this->ui->treeView, filePath);
            module_count++;
        }
    }

    mTree.add_firstItem(modelTree, ui->treeView, "Text");
    //mTree.add_firstItem(modelTree, ui->treeView, "Configuration");

    this->ui->bottom_message->setStyleSheet("QLabel { color : black; }");
    this->ui->bottom_message->setText("Not Connected");

    serial = new QSerialPort(this);
    SettingsDialogForm = new SettingsDialog(this);

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

MainWindow::~MainWindow()
{
    if (serial->isOpen())
        serial->close();
    delete ui;
}

void MainWindow::init_signalSlots(){
    num_window = 0;
    windowMapper = new QSignalMapper(this);

    QObject::connect(ui->menuActive_Window, SIGNAL(aboutToShow()), this, SLOT(update_activeWindow()));
    QObject::connect(windowMapper, SIGNAL(mapped(QWidget*)), this, SLOT(setActiveSubWindow(QWidget*)));
}

void MainWindow::update_activeWindow(){
    ui->menuActive_Window->clear();

    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();

    for (int i = 0; i < windows.size(); i++){
        QWidget *sublist = qobject_cast<QWidget *>(windows.at(i)->widget());

        QString text;
        text = tr("%1 / %2").arg(i+1).arg(sublist->windowTitle());

        QAction *action  = ui->menuActive_Window->addAction(text);
        QObject::connect(action, SIGNAL(triggered(bool)), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window) return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::on_actionNew_triggered()
{
    faddModule = new form_addModule(this);
    faddModule->setWindowTitle("New Module");
    faddModule->setModal(true);

    faddModule->exec();

    if (faddModule->accept == 0) return;

    QString title;
    title.sprintf("%s", faddModule->ui->edit_module_name->text().toUtf8().data());

    module_name[module_count] = work->newModule(modelTree, this->ui->treeView, title);
    module_count++;

}

void MainWindow::on_actionLoad_triggered()
{
    QString file;
    QString command;

    QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Load Module"), tr("data/module/"), tr("(*.ini)"));

    if (fileName.isEmpty()) return;

    for(int i = 0; i < fileName.count(); i++){
        file = work->checkModule(QString(fileName.at(i)).toUtf8().data());

        if(work->state_of_module(module_count, file, module_name)){
            QApplication::processEvents();
            module_name[module_count] = work->loadModule(modelTree, this->ui->treeView, QString(fileName.at(i)).toUtf8().data());
            module_count++;
        }
        else{
            command.sprintf("Module :\n\n%s\n\nSudah terdaftar didalam list!", file.toUtf8().data());
            QMessageBox::warning(this, tr("Warning!"), command, 0,0);
        }
    }
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString name = index.data(Qt::DisplayRole).toString();


    if(work->checkIfmodule(name))
        work->showModule(this, this->ui->mdiArea, name);
    else
        return;
}

void MainWindow::openSerialPort()
{
    if (SettingsDialogForm->currentSettings.serial_set != 1)
    {
        SettingsDialogForm->setWindowTitle("Serial Communication Setting");
        SettingsDialogForm->setModal(true);
        SettingsDialogForm->exec();

//        struct t_serial_settings Com_Setting;
        if (SettingsDialogForm->currentSettings.serial_set == 0) return;

        serial->setPortName(SettingsDialogForm->currentSettings.name);
        serial->setBaudRate(SettingsDialogForm->currentSettings.baudRate);
        serial->setDataBits(SettingsDialogForm->currentSettings.dataBits);
        serial->setParity(SettingsDialogForm->currentSettings.parity);
        serial->setStopBits(SettingsDialogForm->currentSettings.stopBits);
        serial->setFlowControl(SettingsDialogForm->currentSettings.flowControl);
        if (serial->open(QIODevice::ReadWrite)) {
            this->ui->bottom_message->setStyleSheet("QLabel { color : blue; }");
            StatusMessage = QString("Connected to ") +
                            SettingsDialogForm->currentSettings.name +
                            QString(", BR = ") +
                            SettingsDialogForm->currentSettings.stringBaudRate +
                            QString(", DB = ") +
                            SettingsDialogForm->currentSettings.stringDataBits +
                            QString(", PR = ") +
                            SettingsDialogForm->currentSettings.stringParity +
                            QString(", SB = ") +
                            SettingsDialogForm->currentSettings.stringStopBits +
                            QString(", FC = ") +
                            SettingsDialogForm->currentSettings.stringFlowControl;
            this->ui->bottom_message->setText(StatusMessage);
            SettingsDialogForm->currentSettings.serial_connect = 1;
        } else {
            QMessageBox::critical(this, tr("Error"), serial->errorString());
            this->ui->bottom_message->setStyleSheet("QLabel { color : red; }");
            this->ui->bottom_message->setText("Connecting Fail");
            if (serial->isOpen())
                serial->close();
            SettingsDialogForm->currentSettings.serial_connect = 0;
        }
    } else
    {
        serial->setPortName(SettingsDialogForm->currentSettings.name);
        serial->setBaudRate(SettingsDialogForm->currentSettings.baudRate);
        serial->setDataBits(SettingsDialogForm->currentSettings.dataBits);
        serial->setParity(SettingsDialogForm->currentSettings.parity);
        serial->setStopBits(SettingsDialogForm->currentSettings.stopBits);
        serial->setFlowControl(SettingsDialogForm->currentSettings.flowControl);
        if (serial->open(QIODevice::ReadWrite)) {
            this->ui->bottom_message->setStyleSheet("QLabel { color : blue; }");
            StatusMessage = QString("Connected to ") +
                            SettingsDialogForm->currentSettings.name +
                            QString(", BR = ") +
                            SettingsDialogForm->currentSettings.stringBaudRate +
                            QString(", DB = ") +
                            SettingsDialogForm->currentSettings.stringDataBits +
                            QString(", PR = ") +
                            SettingsDialogForm->currentSettings.stringParity +
                            QString(", SB = ") +
                            SettingsDialogForm->currentSettings.stringStopBits +
                            QString(", FC = ") +
                            SettingsDialogForm->currentSettings.stringFlowControl;
            this->ui->bottom_message->setText(StatusMessage);
            SettingsDialogForm->currentSettings.serial_connect = 1;
        } else {
            QMessageBox::critical(this, tr("Error"), serial->errorString());
            this->ui->bottom_message->setStyleSheet("QLabel { color : red; }");
            this->ui->bottom_message->setText("Connecting Fail");
            if (serial->isOpen())
                serial->close();
            SettingsDialogForm->currentSettings.serial_connect = 0;
        }
    }
    if (SettingsDialogForm->currentSettings.serial_connect == 0)
    {
        this->openSerialPort();
    }/* else
    {
        this->writeData("\r\n");
        this->writeData("cek_env\r\n");
        this->writeData("set_env nama ganti_nama\r\n");
        this->writeData("cek_env\r\n");
//        this->closeSerialPort();
    }*/
}
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    if (SettingsDialogForm->currentSettings.serial_connect == 0)
    {
        this->ui->bottom_message->setStyleSheet("QLabel { color : black; }");
        this->ui->bottom_message->setText("Disconnect");
    }
}

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

void MainWindow::readData()
{
    SettingsDialogForm->currentSettings.str_data.append(serial->readAll());
    if (SettingsDialogForm->currentSettings.str_data.indexOf("(x)") > 0)
    {
        SettingsDialogForm->currentSettings.str_data.remove("\r").remove("\n").remove("(x)");
        SettingsDialogForm->currentSettings.val_data.append(SettingsDialogForm->currentSettings.str_data.split(";"));
        qDebug() << SettingsDialogForm->currentSettings.str_data;
        SettingsDialogForm->currentSettings.str_data.clear();
    }
    SettingsDialogForm->currentSettings.val_data.clear();
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::on_actionConnect_triggered()
{
    this->openSerialPort();
}
