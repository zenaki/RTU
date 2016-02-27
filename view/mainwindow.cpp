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
    this->Refresh_Tree();

    this->ui->bottom_message->setStyleSheet("QLabel { color : black; }");
    this->ui->bottom_message->setText("Not Connected");

//    serial = new QSerialPort(this);
//    SettingsDialogForm = new SettingsDialog(this);

//    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));

    SerialPort = new  QSerialPort(this);
    Serial = new serial();
    connect(SerialPort, SIGNAL(readyRead()), this, SLOT(readData()));

    this->ui->actionConnect->setEnabled(true);
    this->ui->actionDisconnect->setEnabled(false);
    this->ui->actionConfig->setEnabled(true);
}

MainWindow::~MainWindow()
{
//    if (serial->isOpen())
//        serial->close();
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
    int jeda = 1000;

    if (SerialPort->isOpen()) {
        Serial->write_data(SerialPort, "hmi_cek_env\r\n");
        work->delay(jeda);

        struct t_module tModule;
        bool cek = false;
        QString command;
        QString newFiles;
        QDir path("data/module");
        QStringList files = path.entryList(QDir::Files);

        newFiles = GetNamaBoard;
        newFiles.prepend("m_").append(".ini");

        /* cek apakah nama module sudah dipakai atau belum */
        for(int i = 0; i < files.count(); i++){
            if(newFiles == QString(files.at(i))) {
                cek = true;
                break;
            } else {
                cek = false;
            }
        }

        if (cek) {
            command.sprintf("Module : %s\nis Exist !!\n\n", GetNamaBoard.toUtf8().data());
            command.append("Replace it ??");
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Attention !!", command,
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                Serial->write_data(SerialPort, "hmi_sync\r\n");
                work->delay(jeda);
                Serial->write_data(SerialPort, "hmi_cek_cfg_sim\r\n");
                work->delay(jeda);

                QString address = "data/module/" + newFiles;
                mod->read_module(&tModule, address);
                strcpy(tModule.serial_number, GetNoSeri.toLatin1());

                work->Get_IO(&tModule, val_data_io);
                work->Get_SIM(&tModule, val_data_sim);

                mod->write_module(&tModule);
            } else {
                Serial->write_data(SerialPort, "hmi_sync\r\n");
                work->delay(jeda);
                Serial->write_data(SerialPort, "hmi_cek_cfg_sim\r\n");
                work->delay(jeda);

                work->Get_IO(&tModule, val_data_io);
                work->Get_SIM(&tModule, val_data_sim);

                /** INPUT **/
                strcpy(tModule.input_a1_name, "");
                strcpy(tModule.input_a2_name, "");
                strcpy(tModule.input_a3_name, "");
                strcpy(tModule.input_a4_name, "");
                strcpy(tModule.input_a5_name, "");
                strcpy(tModule.input_a6_name, "");

                strcpy(tModule.input_d1_name, "");
                strcpy(tModule.input_d2_name, "");
                strcpy(tModule.input_d3_name, "");
                strcpy(tModule.input_d4_name, "");
                strcpy(tModule.input_d5_name, "");
                strcpy(tModule.input_d6_name, "");
                strcpy(tModule.input_d7_name, "");

                /** OUTPUT **/
                strcpy(tModule.output_r1_name, "");
                strcpy(tModule.output_r2_name, "");

                GetNamaBoard.append("_new");
                QString newModule = "m_" + GetNamaBoard + ".ini";
                strcpy(tModule.module_name, GetNamaBoard.toUtf8().data());
                strcpy(tModule.serial_number, GetNoSeri.toLatin1());
                QString Address = "data/module/" + newModule;
                mod->write_module(&tModule);

                faddModule = new form_addModule(this, false, Address);
                faddModule->setWindowTitle("Edit Module");
                faddModule->setModal(true);

                faddModule->exec();

                if (faddModule->accept == 0) {
                    QFile CurrFile(Address);
                    CurrFile.remove();
                    return;
                }

                Address = faddModule->currentFile;
                mod->read_module(&tModule, Address);

                work->Set_ENV(SerialPort, &tModule);
                work->Set_SIM(SerialPort, &tModule);

                this->Refresh_Tree();
            }
        } else {
            Serial->write_data(SerialPort, "hmi_sync\r\n");
            work->delay(jeda);
            Serial->write_data(SerialPort, "hmi_cek_cfg_sim\r\n");
            work->delay(jeda);

            strcpy(tModule.module_name, GetNamaBoard.toUtf8().data());
            strcpy(tModule.serial_number, GetNoSeri.toLatin1());

            work->Get_IO(&tModule, val_data_io);
            work->Get_SIM(&tModule, val_data_sim);

            /** INPUT **/
            strcpy(tModule.input_a1_name, "");
            strcpy(tModule.input_a2_name, "");
            strcpy(tModule.input_a3_name, "");
            strcpy(tModule.input_a4_name, "");
            strcpy(tModule.input_a5_name, "");
            strcpy(tModule.input_a6_name, "");

            strcpy(tModule.input_d1_name, "");
            strcpy(tModule.input_d2_name, "");
            strcpy(tModule.input_d3_name, "");
            strcpy(tModule.input_d4_name, "");
            strcpy(tModule.input_d5_name, "");
            strcpy(tModule.input_d6_name, "");
            strcpy(tModule.input_d7_name, "");

            /** OUTPUT **/
            strcpy(tModule.output_r1_name, "");
            strcpy(tModule.output_r2_name, "");

            mod->write_module(&tModule);

            QString title;
            title.sprintf("%s", tModule.module_name);

            module_name[module_count] = work->newModule(modelTree, this->ui->treeView, title);
            module_count++;
        }
    } else {
        faddModule = new form_addModule(this, true);
        faddModule->setWindowTitle("New Module");
        faddModule->setModal(true);

        faddModule->exec();

        if (faddModule->accept == 0) return;

        QString title;
        title.sprintf("%s", faddModule->ui->edit_module_name->text().toUtf8().data());

        module_name[module_count] = work->newModule(modelTree, this->ui->treeView, title);
        module_count++;
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString Message;
    if (!module_name_sv.isEmpty()) {
        struct t_module tModule;
        mod->read_module(&tModule, module_address_sv);
        QString newAddress = QFileDialog::getSaveFileName(this, tr("Save As Module"), module_address_sv, tr("(*.ini)"));
        mod->save_as_module(&tModule, newAddress);
        Message = "Module with name : " + module_name_sv + " was saved on \n\n";
        Message.append(newAddress);
        QMessageBox::information(this, "Saving Successfully ..", Message, 0, 0);
    } else {
        QMessageBox::information(this, "Cannot Saving ..", "Please Select Module Name Before Save Module ..", 0, 0);
    }
}

void MainWindow::on_actionLoad_triggered()
{
    struct t_module tModule;
    bool cek;
    QString currName;
    QString newName;
    int cpy_num = 0;
    QString file;
    QString command;

    QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Load Module"), tr("data/module/"), tr("(*.ini)"));

    if (fileName.isEmpty()) return;

    for(int i = 0; i < fileName.count(); i++){
        mod->read_module(&tModule, fileName.at(i));
        file.sprintf("m_%s.ini", tModule.module_name);
//        file = work->checkModule(QString(fileName.at(i)).toUtf8().data());
        cek = false;
        for (int j = 0; j < module_count; j++) {
            currName = module_name[j];
            if (currName.prepend("m_").append(".ini") == file) {
                cek = true;
                break;
            } else {
                cek = false;
            }
        }
        if(!cek) {
            QApplication::processEvents();
            module_name[module_count] = work->loadModule(modelTree, this->ui->treeView, QString(fileName.at(i)).toUtf8().data(), "");
            module_count++;
//            this->Refresh_Tree();
        }
        else {
            command.sprintf("Module : %s\nis Exist !!\n\n", file.toUtf8().data());
            command.append("Replace it ??");
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Attention !!", command,
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                mod->read_module(&tModule, fileName[i]);
                mod->write_module(&tModule);
                return;
            } else {
                mod->read_module(&tModule, fileName[i]);
                cek = false;
                while (1) {
                    cpy_num++;
                    newName.sprintf("%s_%d", tModule.module_name, cpy_num);
                    for (int l = 0; l < module_count; l++) {
                        currName = module_name[l];
                        if (currName == newName) {
                            cek = true;
                            break;
                        } else {
                            cek = false;
                        }
                    }
                    if (!cek)
                        break;
                }
                if(!cek) {
                    QApplication::processEvents();
                    module_name[module_count] = work->loadModule(modelTree, this->ui->treeView, QString(fileName.at(i)).toUtf8().data(), newName);
                    module_count++;
                    break;
                }
            }
        }
    }
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString name = index.data(Qt::DisplayRole).toString();


    if(work->checkIfmodule(name)) {
        module_name_sv = name;
        module_name_sv.prepend("m_").append(".ini");
        module_address_sv = "data/module/" + module_name_sv;
    } else {
        module_name_sv = "";
        module_address_sv = "";
        return;
    }
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString name = index.data(Qt::DisplayRole).toString();


    if(work->checkIfmodule(name))
        work->showModule(this, this->ui->mdiArea, name, SerialPort);
    else
        return;
}

void MainWindow::on_actionConnect_triggered()
{
    struct t_serial_settings tSerial;
    serial Serial;
    setting Setting;

    if (!Setting.checkSetting())
    {
        int exe;
        settings_dialog = new SettingsDialog(this);
        settings_dialog->setWindowTitle("Serial Communication Setting");
        settings_dialog->setModal(true);
        exe = settings_dialog->exec();
        if(exe == 0) return;

        if (!SerialPort->isOpen())
            Serial.open_serial(SerialPort, &tSerial);
    } else
    {
        Setting.read_setting(&tSerial);
        if (!SerialPort->isOpen())
            Serial.open_serial(SerialPort, &tSerial);
    }

    if (SerialPort->open(QIODevice::ReadWrite)) {
        Setting.read_setting(&tSerial);
        this->ui->bottom_message->setStyleSheet("QLabel { color : blue; }");
        StatusMessage = QString("Connected to ") + tSerial.name +
                        QString(", BR = ") + tSerial.stringBaudRate +
                        QString(", DB = ") + tSerial.stringDataBits +
                        QString(", PR = ") + tSerial.stringParity +
                        QString(", SB = ") + tSerial.stringStopBits +
                        QString(", FC = ") + tSerial.stringFlowControl;
        this->ui->bottom_message->setText(StatusMessage);
        this->ui->actionConnect->setEnabled(false);
        this->ui->actionDisconnect->setEnabled(true);
        this->ui->actionConfig->setEnabled(false);
    } else {
//        QMessageBox::critical(this, tr("Error"), SerialPort->errorString());
        this->ui->bottom_message->setStyleSheet("QLabel { color : red; }");
        this->ui->bottom_message->setText("Connecting Fail");
        if (SerialPort->isOpen())
            SerialPort->close();
        this->ui->actionConnect->setEnabled(true);
        this->ui->actionDisconnect->setEnabled(false);
        this->ui->actionConfig->setEnabled(true);
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
//    serial Serial;
//    Serial.close_serial(SerialPort);
    if (SerialPort->isOpen()) {
        SerialPort->close();
        this->ui->bottom_message->setStyleSheet("QLabel { color : black; }");
        StatusMessage.replace("Connected to ", "Disconnected from ");
//        StatusMessage = "Disconnect";
        this->ui->bottom_message->setText(StatusMessage);
    } else {
        this->ui->bottom_message->setStyleSheet("QLabel { color : black; }");
        StatusMessage = "Disconnect";
        this->ui->bottom_message->setText(StatusMessage);
    }

    this->ui->actionConnect->setEnabled(true);
    this->ui->actionDisconnect->setEnabled(false);
    this->ui->actionConfig->setEnabled(true);
}

void MainWindow::readData()
{
    struct t_serial_settings tSerial;
    str_data.append(SerialPort->readAll());
    if (GetNoSeri.isEmpty()) {
        if (str_data.indexOf("<ENV") > 0 && str_data.indexOf("ENV>") > 0) {
            int a = str_data.indexOf("<ENV");
            int b = str_data.indexOf("ENV>");
            str_data = str_data.mid(a+4, b-a);
            val_data = str_data
                        .remove(" ")
                        .remove("<ENV")
                        .remove("<ENVani$")
                        .remove("ENV>")
                        .remove("Rinjani$")
                        .remove("hmi_cek_env")
                        .remove("\r").remove("\n").split(";");
            GetNamaBoard = val_data[0];
            GetNoSeri = val_data[1];
            tSerial.str_data_env = str_data;
            Serial->write_parsing_env(&tSerial);
            val_data.clear();
            str_data.clear();
        }
    } else {
        if (str_data.indexOf("<I/O") > 0 && str_data.indexOf("I/O>") > 0) {
            int a = str_data.indexOf("<I/O");
            int b = str_data.indexOf("I/O>");
            str_data = str_data.mid(a+4, b-a);
            val_data_io = str_data
                          .remove(" ")
                          .remove("<I/O")
                          .remove("<I/Oani$")
                          .remove("I/O>")
                          .remove("Rinjani$")
                          .remove("hmi_sync")
                          .remove("\r").remove("\n").remove("(X)").split("*");
            tSerial.str_data_io = str_data;
            Serial->write_parsing_io(&tSerial);
            str_data.clear();
            val_data.clear();
        } else if (str_data.indexOf("<SIM") > 0 && str_data.indexOf("SIM>") > 0) {
            int a = str_data.indexOf("<SIM");
            int b = str_data.indexOf("SIM>");
            str_data = str_data.mid(a+4, b-a);
            val_data_sim = str_data
                           .remove(" ")
                           .remove("<SIM")
                           .remove("<SIMani$")
                           .remove("SIM>")
                           .remove("Rinjani$")
                           .remove("hmi_cek_cfg_sim")
                           .remove("\r").remove("\n").remove("(X)").split("*");
            tSerial.str_data_sim = str_data;
            Serial->write_parsing_sim(&tSerial);
            str_data.clear();
            val_data.clear();
        }
    }
}

void MainWindow::on_actionConfig_triggered()
{
    int exe;
    settings_dialog = new SettingsDialog(this);
    settings_dialog->setWindowTitle("Serial Communication Setting");
    settings_dialog->setModal(true);
    exe = settings_dialog->exec();
    if(exe == 0) return;
}

void MainWindow::Refresh_Tree()
{
    modelTree->clear();
    module_count = 0;
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

            module_name[module_count] = work->loadModule(modelTree, this->ui->treeView, filePath, "");
            module_count++;
        }
    }

    mTree.add_firstItem(modelTree, ui->treeView, "Text");
    //mTree.add_firstItem(modelTree, ui->treeView, "Configuration");
}

void MainWindow::on_actionRefresh_triggered()
{
    this->Refresh_Tree();
}
