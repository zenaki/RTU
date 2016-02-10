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

    Com_Setting = new SettingsDialog(this);
    Com_Setting->setWindowTitle("Serial Communication Setting");
    Com_Setting->setModal(true);
    Com_Setting->accept = 0;
    serial = new QSerialPort(this);
//    Com_Setting = new SettingsDialog;

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
//    MainWindow::Connection_Settings p = Connection_Settings;
//    Com_Setting = new SettingsDialog(this);
//    Com_Setting->setWindowTitle("Serial Communication Setting");
//    Com_Setting->setModal(true);
    if (Com_Setting->accept == 0)
    {
        Com_Setting->exec();

        if (Com_Setting->accept == 0) return;

        serial->setPortName(Com_Setting->currentSettings.name);
        serial->setBaudRate(Com_Setting->currentSettings.baudRate);
        serial->setDataBits(Com_Setting->currentSettings.dataBits);
        serial->setParity(Com_Setting->currentSettings.parity);
        serial->setStopBits(Com_Setting->currentSettings.stopBits);
        serial->setFlowControl(Com_Setting->currentSettings.flowControl);
        if (serial->open(QIODevice::ReadWrite)) {
            this->ui->bottom_message->setStyleSheet("QLabel { color : blue; }");
            StatusMessage = QString("Connected to ") +
                            Com_Setting->currentSettings.name +
                            QString(", BR = ") +
                            Com_Setting->currentSettings.stringBaudRate +
                            QString(", DB = ") +
                            Com_Setting->currentSettings.stringDataBits +
                            QString(", PR = ") +
                            Com_Setting->currentSettings.stringParity +
                            QString(", SB = ") +
                            Com_Setting->currentSettings.stringStopBits +
                            QString(", FC = ") +
                            Com_Setting->currentSettings.stringFlowControl;
            this->ui->bottom_message->setText(StatusMessage);
            Com_Setting->accept = 1;
        } else {
            QMessageBox::critical(this, tr("Error"), serial->errorString());
            this->ui->bottom_message->setStyleSheet("QLabel { color : red; }");
            this->ui->bottom_message->setText("Connecting Fail");
            Com_Setting->accept = 0;
        }
    } else
    {
        serial->setPortName(Com_Setting->currentSettings.name);
        serial->setBaudRate(Com_Setting->currentSettings.baudRate);
        serial->setDataBits(Com_Setting->currentSettings.dataBits);
        serial->setParity(Com_Setting->currentSettings.parity);
        serial->setStopBits(Com_Setting->currentSettings.stopBits);
        serial->setFlowControl(Com_Setting->currentSettings.flowControl);
        if (serial->open(QIODevice::ReadWrite)) {
            this->ui->bottom_message->setStyleSheet("QLabel { color : blue; }");
            StatusMessage = QString("Connected to ") +
                            Com_Setting->currentSettings.name +
                            QString(", BR = ") +
                            Com_Setting->currentSettings.stringBaudRate +
                            QString(", DB = ") +
                            Com_Setting->currentSettings.stringDataBits +
                            QString(", PR = ") +
                            Com_Setting->currentSettings.stringParity +
                            QString(", SB = ") +
                            Com_Setting->currentSettings.stringStopBits +
                            QString(", FC = ") +
                            Com_Setting->currentSettings.stringFlowControl;
            this->ui->bottom_message->setText(StatusMessage);
            Com_Setting->accept = 1;
        } else {
            QMessageBox::critical(this, tr("Error"), serial->errorString());
            this->ui->bottom_message->setStyleSheet("QLabel { color : red; }");
            this->ui->bottom_message->setText("Connecting Fail");
            Com_Setting->accept = 0;
        }
    }
    if (Com_Setting->accept == 0)
    {
        this->openSerialPort();
    } else
    {
        this->writeData("\r\n");
        this->writeData("cek_env\r\n");
        this->writeData("set_env nama Berhasil_Ganti_Nama_Board\r\n");
        this->writeData("cek_env\r\n");
//        this->closeSerialPort();
    }
}
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    if (Com_Setting->accept == 0)
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
    string_data.append(serial->readAll());
    if (string_data.indexOf("\r") > 0 || string_data.indexOf("\n") > 0)
    {
        QStringList val = string_data.remove("\r").remove("\n").split(";");
//        qDebug() << string_data.remove("\r").remove("\n");
        qDebug() << string_data;
        string_data.clear();
    }
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
