#include "worker.h"

worker::worker()
{
//    cancelSetting = false;
}

QString worker::newModule(QStandardItemModel *tree, QTreeView *treeView, QString title){
    struct t_module tModule;
    QString address;

    address.sprintf(".RTUdata/module/m_%s.dbe", title.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    if (!tModule.module_name.isEmpty() && !tModule.serial_number.isEmpty()) {
        //    modules.sprintf("%s [%s]", tModule.module_name, tModule.serial_number);
            modules = tModule.module_name + " [" + tModule.serial_number + "]";
        //    modules.sprintf("m_%s.dbe", tModule.module_name);
            mTree.appendItem(tree, treeView, modules);

            return modules;
    }
    return "Error";
}

QString worker::editModule(QStandardItemModel *tree, QTreeView *treeView, QString title){
    struct t_module tModule;
    QString address;

    address.sprintf(".RTUdata/module/m_%s.dbe", title.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
//    modules.sprintf("%s", tModule.module_name);
    modules = tModule.module_name;
//    modules.sprintf("m_%s.dbe", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::loadModule(QStandardItemModel *tree, QTreeView *treeView, QString address, QString NewName){
    struct t_module tModule;

    mod.read_module(&tModule, address);

    tModule.flag_active = 1;

    if (!NewName.isEmpty()) {
//        strcpy(tModule.module_name, NewName.toLatin1());
        tModule.module_name = NewName;
    }

    QString modules;
//    modules.sprintf("%s [%s]", tModule.module_name, tModule.serial_number);
    modules = tModule.module_name + " [" + tModule.serial_number + "]";
//    modules.sprintf("m_%s.dbe", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::checkModule(QString address){
    struct t_module tModule;

    mod.read_module(&tModule, address);

    QString modules;
//    modules.sprintf("m_%s.dbe", tModule.module_name);
    modules = "m_" + tModule.module_name + ".dbe";
    return modules;
}

QString worker::check_statusModule(QString address){
    struct t_module tModule;

    address.sprintf(".RTUdata/module/%s", address.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    if(tModule.flag_active){
//        modules.sprintf("m_%s.dbe", tModule.module_name);
        modules = "m_" + tModule.module_name + ".dbe";
        return modules;
    }
    return "none";
}

void worker::showModule(QWidget *parent, QMdiArea *mdiArea, QString module, QSerialPort *SerialPort){
    struct t_module tModule;
    QString address;

    address.sprintf(".RTUdata/module/m_%s.dbe", module.toUtf8().data());
    mod.read_module(&tModule, address);


    formModule *fModule;

    fModule = new formModule(parent, address, SerialPort);
    fModule->setModal(true);
    fModule->setWindowTitle(tModule.module_name);
//    fModule->setFixedWidth(800);
//    fModule->setFixedHeight(600);
    fModule->setMaximumSize(mdiArea->maximumSize());

    mdiArea->addSubWindow(fModule, 0);
    fModule->exec();

}

bool worker::checkIfmodule(QString name){
    bool cek = false;
    QDir path(".RTUdata/module");
    QStringList files = path.entryList(QDir::Files);

    QString currFiles;
    currFiles.sprintf("m_%s.dbe", name.toUtf8().data());

    for(int i = 0; i < files.count(); i++){
        if(currFiles == QString(files.at(i))) cek = true;
    }

//    std::string sub = name.toStdString();
//    ext = QString::fromStdString(sub.substr(index_max-3, index_max));

//    if(ext == ".dbe") return true;
//    else return false;

    return cek;
}

bool worker::state_of_module(int num, QString newModule, QString *existModule){
    bool cek;
    int  ceknt = num+1;
//    QString currModule;
    existModule->prepend("m_").append(".dbe");

    for(int n = 0; n < ceknt; n++){
//        currModule = existModule->at(n);
//        currModule.prepend("m_").append(".dbe");
        if(newModule != existModule[n]){
            cek = true;
        }
        else{
            cek = false;
            return cek;
        }
    }

    return cek;
}

bool worker::Request_ENV(QSerialPort *Serial_Com, bool timeout)
{
//    QString Request = "hmi_cek_env\r\n";
    QString Request = MODE_GET_ENV;
    QString Desc = "Request Environment ..";
    serial_write(Serial_Com, Request, WAIT_WRITE);
//    Serial_Com->write(Request.toUtf8().data(), qstrlen(Request.toUtf8().data()));
//    Serial_Com->waitForBytesWritten(WAIT_WRITE);
    if (!timeout) {timeout = this->waiting_set(timeout);}
    this->writeLogFile(Request, this->read_flagERR(), this->read_strERR(), timeout);
    if (timeout) {return timeout;}

    return timeout;
}

void worker::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void worker::serial_write(QSerialPort *Serial_Com, QString data, int d_c)
{
    QString temp;
    data.remove("\r\n");
    for (int i = 0; i < data.length(); i++) {
        temp = QChar(data.at(i));
        Serial_Com->write(temp.toUtf8().data());
        delay(d_c);
    }
    Serial_Com->write("\n");
}

bool worker::waiting_set(bool timeout)
{
    QTime dieTime = QTime::currentTime().addMSecs(TIMEOUT);
    while (!this->read_FinishRead()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        if (this->read_flagERR() == 1 && !timeout) {
            timeout = false;
            break;
        }
        if (QTime::currentTime() >= dieTime && !timeout) {
            timeout = true;
            break;
        }
    }
    return timeout;
}

void worker::write_FinishRead(bool FinishRead, int cekErr, QString strErr)
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    QSettings sett(pth, QSettings::IniFormat);

    sett.setValue("FINISH_READ", FinishRead);
    sett.setValue("ERROR_FLAG", cekErr);
    sett.setValue("ERROR_STRING", strErr);
}

bool worker::read_FinishRead()
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    bool FinishRead = sett.value("FINISH_READ").toBool();

    code.encryp(pth);
    return FinishRead;
}

int worker::read_flagERR()
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    int flagERR = sett.value("ERROR_FLAG").toInt();

    code.encryp(pth);
    return flagERR;
}

QString worker::read_strERR()
{
    QString pth;
    pth = PATH_SERIAL_PARSING;
    cryp code; code.decryp(pth);
    QSettings sett(pth, QSettings::IniFormat);

    QString strERR = sett.value("ERROR_STRING").toString();

    code.encryp(pth);
    return strERR;
}

void worker::writeLogFile(QString log, int flagERR, QString strERR, bool timeout)
{
    /* Try and open a file for output */
    QString outputFilename = PATH_LOG;
    QFile outputFile(outputFilename);
    outputFile.open(QIODevice::Append | QIODevice::Text);

    /* Check it opened OK */
    if(!outputFile.isOpen()){
        qDebug() << "- Error, unable to open" << outputFilename << "for output";
    } else {
        log.remove("\r").remove("\n");
        if (log.length() < 100) {
            for (int i = log.length(); i < 100; i++) {
                log.append(" ");
            }
        }
        log.append("|");

        QString Flag;
        if      (flagERR == 1) {Flag = "ERROR|";}
        else if (flagERR == 0) {Flag = "OK   |";}
        else                   {Flag = "     |";}

        QString TimeOut;
        if      (timeout) {TimeOut = "TIMEOUT|";}
        else              {TimeOut = "       |";}

        /* Point a QTextStream object at the file */
        QTextStream outStream(&outputFile);

        /* Write the line to the file */
        outStream << QTime::currentTime().toString("hh:mm:ss.zzz") << " | " << log << Flag << TimeOut << strERR<< "\r\n";

        /* Close the file */
        outputFile.close();
    }
    this->write_FinishRead(false,2,"");
    cryp code; code.encryp(PATH_SERIAL_PARSING);
}

