#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingsdialog.h"

#include <QMessageBox>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QWidget>

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

    bottom_message = new QLabel(this);
    this->ui->statusBar->addPermanentWidget(bottom_message,1);
    bottom_message->setStyleSheet("QLabel { color : black; }");
    bottom_message->setText("Not Connected");
//    this->ui->statusBar->setStyleSheet("QLabel { color : black; }");
//    this->ui->statusBar->showMessage("Not Connected");

//    serial = new QSerialPort(this);
//    SettingsDialogForm = new SettingsDialog(this);

//    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));

    SerialPort = new  QSerialPort(this);
    Serial = new serial();
    connect(SerialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(SerialPort, SIGNAL(error(QSerialPort::SerialPortError)), this,SLOT(handleError(QSerialPort::SerialPortError)));

    this->ui->actionConnect->setEnabled(true);
    this->ui->actionDisconnect->setEnabled(false);
    this->ui->actionConfig->setEnabled(true);

    busy = new QLightBoxWidget(this);

    SigMapPlugin = new QSignalMapper(this);
    this->readPlugin();

    QFile usr(PATH_USER_ACCESS);
    if (usr.exists()) {
        this->ui->actionCreate_User->setEnabled(false);
        this->ui->actionEdit_User->setEnabled(true);
    } else {
        this->ui->actionCreate_User->setEnabled(true);
        this->ui->actionEdit_User->setEnabled(false);
    }

    progress_dialog = new ProgressDialog(this);
    progress_dialog->setModal(true);
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
    if (SerialPort->isOpen()) {
        bool timeout = false;
        timeout = work->Request_ENV(this, busy, SerialPort, timeout);
        if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}

        struct t_module tModule;
        bool cek = false;
        QString command;
        QString newFiles;
        QDir path("data/module");
        QStringList files = path.entryList(QDir::Files);

        newFiles = GetNamaBoard;
        newFiles.prepend("m_").append(".dbe");

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
                QString Address = "data/module/" + newFiles;
                mod->read_module(&tModule, Address);
                strcpy(tModule.serial_number, GetNoSeri.toLatin1());

//                timeout = work->Request_ENV(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_ENV(&tModule, val_data);
//                timeout = work->Request_SIM(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_SIM(&tModule, val_data);
//                timeout = work->Request_Data(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_Data(&tModule, val_data);
//                timeout = work->Request_IO(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_Input(&tModule, val_data);
//                work->Get_Output(&tModule, val_data);
//                timeout = work->Request_Sumber(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_Sumber(&tModule, val_data);

                progress_dialog->show();
                progress_dialog->setWindowTitle("Get from board ..");
                progress_dialog->Processing(SerialPort, Address, "0000;0001;0005;0002;0004");
                progress_dialog->close();

//                mod->write_module(&tModule);
//                cryp code; code.encryp(Address);
            } else {
                GetNamaBoard.append("_new");
                QString newModule = "m_" + GetNamaBoard + ".dbe";
                strcpy(tModule.module_name, GetNamaBoard.toUtf8().data());
                strcpy(tModule.serial_number, GetNoSeri.toLatin1());
                QString Address = "data/module/" + newModule;

                tModule.InputName.clear();
                tModule.OutputName.clear();

//                timeout = work->Request_ENV(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_ENV(&tModule, val_data);
//                timeout = work->Request_SIM(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_SIM(&tModule, val_data);
//                timeout = work->Request_Data(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_Data(&tModule, val_data);
//                timeout = work->Request_IO(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_Input(&tModule, val_data);
//                work->Get_Output(&tModule, val_data);
//                timeout = work->Request_Sumber(this, busy, SerialPort, timeout);
//                if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//                work->Get_Sumber(&tModule, val_data);

                tModule.jml_alarm = 0;

                progress_dialog->show();
                progress_dialog->setWindowTitle("Get from board ..");
                progress_dialog->Processing(SerialPort, Address, "0000;0001;0005;0002;0004");
                progress_dialog->close();

//                mod->write_module(&tModule);
//                cryp code; code.encryp(Address);

                faddModule = new form_addModule(this, false, Address, 1);
                faddModule->setWindowTitle("New Module");
                faddModule->setModal(true);

                faddModule->exec();

                if (faddModule->accept == 0) {
                    QFile CurrFile(Address);
                    CurrFile.remove();
                    return;
                }

                Address = faddModule->currentFile;
                mod->read_module(&tModule, Address);

                bool fail = false;
//                timeout = work->Set_ENV(this, busy, SerialPort, &tModule, timeout);
//                if (timeout) {fail = true;}
//                timeout = work->Set_SIM(this, busy, SerialPort, &tModule, timeout);
//                if (timeout) {fail = true;}

                progress_dialog->show();
                progress_dialog->setWindowTitle("Set to board ..");
                progress_dialog->Processing(SerialPort, Address, "0100;0101");
                progress_dialog->close();

                this->GetNamaBoard.sprintf("%s", tModule.module_name);
                this->Refresh_Tree();

                if (fail) {
                    this->on_actionDisconnect_triggered();
                    QMessageBox::information(this,
                                             "Serial Communication",
                                             "Please check your serial communication port ..", 0, 0);
                    return;
                }
            }
        } else {
            QString Address = "data/module/" + newFiles;
            tModule.InputName.clear();
            tModule.OutputName.clear();

//            timeout = work->Request_ENV(this, busy, SerialPort, timeout);
//            if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//            work->Get_ENV(&tModule, val_data);
//            timeout = work->Request_SIM(this, busy, SerialPort, timeout);
//            if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//            work->Get_SIM(&tModule, val_data);
//            timeout = work->Request_Data(this, busy, SerialPort, timeout);
//            if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//            work->Get_Data(&tModule, val_data);
//            timeout = work->Request_IO(this, busy, SerialPort, timeout);
//            if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//            work->Get_Input(&tModule, val_data);
//            work->Get_Output(&tModule, val_data);
//            timeout = work->Request_Sumber(this, busy, SerialPort, timeout);
//            if (timeout) {this->on_actionDisconnect_triggered(); QMessageBox::information(this, "Serial Communication", "Please check your serial communication port ..", 0, 0); return;}
//            work->Get_Sumber(&tModule, val_data);
            tModule.jml_alarm = 0;

            progress_dialog->show();
            progress_dialog->setWindowTitle("Get from board ..");
            progress_dialog->Processing(SerialPort, Address, "0000;0001;0005;0002;0004");
            progress_dialog->close();

            strcpy(tModule.module_name, GetNamaBoard.toUtf8().data());
            strcpy(tModule.serial_number, GetNoSeri.toLatin1());

//            mod->write_module(&tModule);
//            QString pth; pth.sprintf("data/module/m_%s.dbe", tModule.module_name);
//            cryp code; code.encryp(pth);

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
        this->GetNamaBoard = title;
    }
    QString Message = this->GetNamaBoard;
    Message.prepend("Module with name : \n").append("\nwas created ..");
    QMessageBox::information(this, "New Module", Message, 0, 0);
}

void MainWindow::on_actionSave_triggered()
{
    QString Message;
    if (!module_name_sv.isEmpty()) {
        struct t_module tModule;
        mod->read_module(&tModule, module_address_sv);
        QString newAddress = QFileDialog::getSaveFileName(this, tr("Save As Module"), module_address_sv, tr("(*.dbe)"));
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

    QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Load Module"), tr("data/module/"), tr("(*.dbe)"));

    if (fileName.isEmpty()) return;

    for(int i = 0; i < fileName.count(); i++){
        mod->read_module(&tModule, fileName.at(i));
        file.sprintf("m_%s.dbe", tModule.module_name);
//        file = work->checkModule(QString(fileName.at(i)).toUtf8().data());
        cek = false;
        for (int j = 0; j < module_count; j++) {
            currName = module_name[j];
            if (currName.prepend("m_").append(".dbe") == file) {
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
                QString pth; pth.sprintf("data/module/m_%s.dbe", tModule.module_name);
                cryp code; code.encryp(pth);
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

void MainWindow::on_actionDelete_triggered()
{
    QString Message;
    if (!module_name_sv.isEmpty()) {
        QFile d_m(module_address_sv);
        if (d_m.remove()) {
            Message = "Module with name : " + module_name_sv + " was deleted";
            QMessageBox::information(this, "Delete Successfully ..", Message, 0, 0);
        } else {
            Message = d_m.errorString();
            QMessageBox::information(this, "Delete Error ..", Message, 0, 0);
        }
        this->Refresh_Tree();
    } else {
        QMessageBox::information(this, "Cannot Deleting ..", "Please Select Module Name Before Delete Module ..", 0, 0);
    }
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString name = index.data(Qt::DisplayRole).toString();

    if(work->checkIfmodule(name)) {
        module_name_sv = name;
        module_name_sv.prepend("m_").append(".dbe");
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
    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    bool cek = false;
    for (int i = 0; i < windows.size(); i++){
        QWidget *sublist = qobject_cast<QWidget *>(windows.at(i)->widget());

        if (name == sublist->windowTitle()) {
            sublist->setFocus();
            cek = true;
        }
    }

    if (cek)
        return;

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

    if (!Setting.checkSetting()) {
        int exe;
        settings_dialog = new SettingsDialog(this);
        settings_dialog->setWindowTitle("Serial Communication Setting");
        settings_dialog->setModal(true);
        exe = settings_dialog->exec();
        if(exe == 0) return;

        Setting.read_setting(&tSerial);
        if (!SerialPort->isOpen())
            Serial.open_serial(SerialPort, &tSerial);
    } else {
        Setting.read_setting(&tSerial);
        if (!SerialPort->isOpen())
            Serial.open_serial(SerialPort, &tSerial);
    }

    if (SerialPort->open(QIODevice::ReadWrite)) {
        Setting.read_setting(&tSerial);
        bottom_message->setStyleSheet("QLabel { color : blue; }");
//        this->ui->statusBar->setStyleSheet("QLabel { color : blue; }");
        StatusMessage = QString("Connected to ") + tSerial.name +
                        QString(", BR = ") + tSerial.stringBaudRate +
                        QString(", DB = ") + tSerial.stringDataBits +
                        QString(", PR = ") + tSerial.stringParity +
                        QString(", SB = ") + tSerial.stringStopBits +
                        QString(", FC = ") + tSerial.stringFlowControl;
        bottom_message->setText(StatusMessage);
        this->ui->statusBar->showMessage(StatusMessage);
        this->ui->actionConnect->setEnabled(false);
        this->ui->actionDisconnect->setEnabled(true);
        this->ui->actionConfig->setEnabled(false);
    } else {
//        QMessageBox::critical(this, tr("Error"), SerialPort->errorString());
        bottom_message->setStyleSheet("QLabel { color : red; }");
        bottom_message->setText("Connecting Fail");
//        this->ui->statusBar->setStyleSheet("QLabel { color : red; }");
//        this->ui->statusBar->showMessage("Connecting Fail");
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
//        if (SerialPort->open(QIODevice::ReadWrite)) {
//            SerialPort->close();
//        } else if (SerialPort->open(QIODevice::ReadOnly)) {
//            SerialPort->close();
//        }
        SerialPort->close();
        bottom_message->setStyleSheet("QLabel { color : black; }");
//        this->ui->statusBar->setStyleSheet("QLabel { color : black; }");
        StatusMessage.replace("Connected to ", "Disconnected from ");
//        StatusMessage = "Disconnect";
        bottom_message->setText(StatusMessage);
//        this->ui->statusBar->showMessage(StatusMessage);
    } else {
        bottom_message->setStyleSheet("QLabel { color : black; }");
//        this->ui->statusBar->setStyleSheet("QLabel { color : black; }");
        StatusMessage = "Disconnect";
        bottom_message->setText(StatusMessage);
//        this->ui->statusBar->showMessage(StatusMessage);
    }

    this->ui->actionConnect->setEnabled(true);
    this->ui->actionDisconnect->setEnabled(false);
    this->ui->actionConfig->setEnabled(true);
}

void MainWindow::readData()
{
    QCoreApplication::processEvents();
    struct t_serial_settings tSerial;
    str_data.append(SerialPort->readAll());
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
                    .remove("0000")
                    .remove("hmi_cek_env")
                    .remove("\r").remove("\n").split(";");
        GetNamaBoard = val_data[0];
        GetNoSeri = val_data[1];
        tSerial.str_data_env = str_data;
        Serial->write_parsing_env(&tSerial);
        cryp code; code.encryp(PATH_SERIAL_PARSING);
        str_data.clear();
        FinishRead = true;
        work->write_FinishRead(FinishRead, 0, "");
        code.encryp(PATH_SERIAL_PARSING);
    } else if (str_data.indexOf("<I/O") > 0 && str_data.indexOf("I/O>") > 0) {
        int a = str_data.indexOf("<I/O");
        int b = str_data.indexOf("I/O>");
        str_data = str_data.mid(a+4, b-a);
        val_data = str_data
                    .remove(" ")
                    .remove("<I/O")
                    .remove("<I/Oani$")
                    .remove("I/O>")
                    .remove("Rinjani$")
                    .remove("0002")
                    .remove("hmi_sync")
                    .remove("\r").remove("\n").remove("(X)").split("*");
        tSerial.str_data_io = str_data;
        Serial->write_parsing_io(&tSerial);
        cryp code; code.encryp(PATH_SERIAL_PARSING);
        str_data.clear();
        FinishRead = true;
        work->write_FinishRead(FinishRead, 0, "");
        code.encryp(PATH_SERIAL_PARSING);
    } else if (str_data.indexOf("<SIM") > 0 && str_data.indexOf("SIM>") > 0) {
        int a = str_data.indexOf("<SIM");
        int b = str_data.indexOf("SIM>");
        str_data = str_data.mid(a+4, b-a);
        val_data = str_data
                    .remove(" ")
                    .remove("<SIM")
                    .remove("<SIMani$")
                    .remove("SIM>")
                    .remove("Rinjani$")
                    .remove("0001")
                    .remove("hmi_cek_cfg_sim")
                    .remove("\r").remove("\n").remove("(X)").split("*");
        tSerial.str_data_sim = str_data;
        Serial->write_parsing_sim(&tSerial);
        cryp code; code.encryp(PATH_SERIAL_PARSING);
        str_data.clear();
        FinishRead = true;
        work->write_FinishRead(FinishRead, 0, "");
        code.encryp(PATH_SERIAL_PARSING);
    } else if (str_data.indexOf("<SRC") > 0 && str_data.indexOf("SRC>") > 0) {
        int a = str_data.indexOf("<SRC");
        int b = str_data.indexOf("SRC>");
        str_data = str_data.mid(a+4, b-a);
        val_data = str_data
                    .remove(" ")
                    .remove("<SRC")
                    .remove("<SRCani$")
                    .remove("SRC>")
                    .remove("Rinjani$")
                    .remove("0004")
                    .remove("hmi_cek_sumber")
                    .remove("\r").remove("\n").remove("(X)").split("*");
        tSerial.str_data_src = str_data;
        Serial->write_parsing_src(&tSerial);
        cryp code; code.encryp(PATH_SERIAL_PARSING);
        str_data.clear();
        FinishRead = true;
        work->write_FinishRead(FinishRead, 0, "");
        code.encryp(PATH_SERIAL_PARSING);
    } else if (str_data.indexOf("<DAT") > 0 && str_data.indexOf("DAT>") > 0) {
        int a = str_data.indexOf("<DAT");
        int b = str_data.indexOf("DAT>");
        str_data = str_data.mid(a+4, b-a);
        val_data = str_data
                    .remove(" ")
                    .remove("<DAT")
                    .remove("<DATani$")
                    .remove("DAT>")
                    .remove("Rinjani$")
                    .remove("0005")
                    .remove("hmi_cek_data")
                    .remove("\r").remove("\n").remove("(X)").split("*");
        tSerial.str_data_dat = str_data;
        Serial->write_parsing_dat(&tSerial);
        cryp code; code.encryp(PATH_SERIAL_PARSING);
        str_data.clear();
        FinishRead = true;
        work->write_FinishRead(FinishRead, 0, "");
        code.encryp(PATH_SERIAL_PARSING);
    } else if (str_data.indexOf("<OK>") > 0) {
        FinishRead = true;
        work->write_FinishRead(FinishRead, 0, "");
        str_data.clear();
        cryp code; code.encryp(PATH_SERIAL_PARSING);
    } else if (str_data.indexOf("<OK:") > 0 && str_data.indexOf(":OK>") > 0) {
        int a = str_data.indexOf("<OK:");
        int b = str_data.indexOf(":OK>");
        str_data = str_data.mid(a+4, b-a-4);
        FinishRead = true;
        work->write_FinishRead(FinishRead, 0, str_data);
        str_data.clear();
        cryp code; code.encryp(PATH_SERIAL_PARSING);
    } else if (str_data.indexOf("<ERR>") > 0) {
        FinishRead = true;
        work->write_FinishRead(FinishRead, 1, "ERROR");
        cryp code; code.encryp(PATH_SERIAL_PARSING);
        str_data.clear();
    } else if (str_data.indexOf("<ERR:") > 0 && str_data.indexOf(":ERR>") > 0) {
        int a = str_data.indexOf("<ERR:");
        int b = str_data.indexOf(":ERR>");
        str_data = str_data.mid(a+5, b-a-5);
        FinishRead = true;
        work->write_FinishRead(FinishRead, 1, str_data);
        cryp code; code.encryp(PATH_SERIAL_PARSING);
        str_data.clear();
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

void MainWindow::on_actionAdd_Plugin_triggered()
{
    QStringList plugin = QFileDialog::getOpenFileNames(this, tr("Load Module"), tr("data/module/"), tr("(*.zip)"));
    if (plugin.isEmpty()) return;
    QStringList file; bool fail = false;
    QStringList PluginName; QStringList PluginExec;

    for (int i = 0; i < plugin.length(); i++) {
        file = work->ListContents(plugin.at(i));
        if (file.indexOf(QRegExp("^" + QRegExp::escape("plugin.cfg") + ".+")) == 0) {
            fail = true;
            break;
        }
    }
    if (fail) {QMessageBox::information(this, "Add Pluggin", "Please select plugin zip file correctly"); return;}
    QFile FileConfg("plugin.cfg");
    QFile PluginConfg(PATH_PLUGIN_CONFIG);
    struct t_plugin tPlugin;
    for (int i = 0; i < plugin.length(); i++) {
        work->DecompressFiles(plugin.at(i), QStringList() << "plugin.cfg", QDir::currentPath());
        PluginName.insert(i, work->readPluginConfgName("plugin.cfg"));
        PluginExec.insert(i, work->readPluginConfgExec("plugin.cfg"));

        if (PluginConfg.exists()) {
            work->readPlugin(&tPlugin);
            fail = false;
            for (int j = 0; j < tPlugin.jml_plugin; j++) {
                if (tPlugin.PluginName.at(i) == PluginName.at(i)) {
                    fail = true;
                    break;
                }
            }
            if (!fail) {
                tPlugin.PluginName.insert(tPlugin.jml_plugin, PluginName.at(i));
                tPlugin.PluginExec.insert(tPlugin.jml_plugin, PluginExec.at(i));

                work->DecompressDir(plugin.at(i), "plugin/" + tPlugin.PluginName.at(tPlugin.jml_plugin));
                Plugin[tPlugin.jml_plugin] = new QAction(tPlugin.PluginName.at(tPlugin.jml_plugin), this);
                this->ui->menuPlugin->addAction(Plugin[tPlugin.jml_plugin]);
                connect(Plugin[tPlugin.jml_plugin], SIGNAL(triggered()), SigMapPlugin, SLOT(map()));
                SigMapPlugin->setMapping(Plugin[tPlugin.jml_plugin], tPlugin.jml_plugin);

                tPlugin.jml_plugin++;
                work->writePlugin(&tPlugin);
                cryp code; code.encryp(PATH_PLUGIN_CONFIG);
            } else {
                QMessageBox::warning(this, "Plugin Warning", "The Plugin is added before ..");
            }
        } else {
            tPlugin.jml_plugin = 0;
            tPlugin.PluginName.insert(tPlugin.jml_plugin, PluginName.at(i));
            tPlugin.PluginExec.insert(tPlugin.jml_plugin, PluginExec.at(i));

            work->DecompressDir(plugin.at(i), "plugin/" + tPlugin.PluginName.at(tPlugin.jml_plugin));
            Plugin[tPlugin.jml_plugin] = new QAction(tPlugin.PluginName.at(tPlugin.jml_plugin), this);
            this->ui->menuPlugin->addAction(Plugin[tPlugin.jml_plugin]);
            connect(Plugin[tPlugin.jml_plugin], SIGNAL(triggered()), SigMapPlugin, SLOT(map()));
            SigMapPlugin->setMapping(Plugin[tPlugin.jml_plugin], tPlugin.jml_plugin);

            tPlugin.jml_plugin++;
            work->writePlugin(&tPlugin);
            cryp code; code.encryp(PATH_PLUGIN_CONFIG);
        }
        FileConfg.remove();
    }
    connect(SigMapPlugin, SIGNAL(mapped(int)), this, SLOT(openPlugin(int)));
}

void MainWindow::openPlugin(int index)
{
    struct t_plugin tPlugin;
    work->readPlugin(&tPlugin);

    QString program = QDir::currentPath() + "/plugin/" +
                      tPlugin.PluginName.at(index) + "/" +
                      tPlugin.PluginExec.at(index);
    QFile Plugin(program);
    if (Plugin.exists()) {
        QStringList arguments;
        QProcess *myProcess = new QProcess(qApp);
        myProcess->start(program, arguments);
    } else {
        QMessageBox::warning(this, "Plugin Warning", "Plugin not found !");
    }
}

void MainWindow::readPlugin()
{
    QFile PluginConfg(PATH_PLUGIN_CONFIG);
    if (PluginConfg.exists()) {
        struct t_plugin tPlugin;
        work->readPlugin(&tPlugin);
        for (int i = 0; i < tPlugin.jml_plugin; i++) {
            Plugin[i] = new QAction(tPlugin.PluginName.at(i), this);
            this->ui->menuPlugin->addAction(Plugin[i]);
            connect(Plugin[i], SIGNAL(triggered()), SigMapPlugin, SLOT(map()));
            SigMapPlugin->setMapping(Plugin[i], i);
        }
        connect(SigMapPlugin, SIGNAL(mapped(int)), this, SLOT(openPlugin(int)));
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
//        QMessageBox::critical(this, tr("Critical Error"), SerialPort->errorString());
        this->on_actionDisconnect_triggered();
        QMessageBox::critical(this, tr("Critical Error"), "Please check your connection ..!!!");
    }
}

void MainWindow::on_actionCreate_User_triggered()
{
    int exe;
    LoginForm = new loginForm(this, "CREATE");
    LoginForm->setWindowTitle("Create User Access");
    LoginForm->setModal(true);
    exe = LoginForm->exec();
    if(exe != 0) return;

    this->ui->actionCreate_User->setEnabled(false);
    this->ui->actionEdit_User->setEnabled(true);
}

void MainWindow::on_actionEdit_User_triggered()
{
    int exe;
    LoginForm = new loginForm(this, "EDIT");
    LoginForm->setWindowTitle("Edit User Access");
    LoginForm->setModal(true);
    exe = LoginForm->exec();
    if(exe == 0) return;
}
