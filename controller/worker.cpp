#include "worker.h"

worker::worker()
{

}

QString worker::newModule(QStandardItemModel *tree, QTreeView *treeView, QString title){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.ini", title.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    modules.sprintf("%s", tModule.module_name);
//    modules.sprintf("m_%s.ini", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::editModule(QStandardItemModel *tree, QTreeView *treeView, QString title){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.ini", title.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    modules.sprintf("%s", tModule.module_name);
//    modules.sprintf("m_%s.ini", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::loadModule(QStandardItemModel *tree, QTreeView *treeView, QString address, QString NewName){
    struct t_module tModule;

    mod.read_module(&tModule, address);

    tModule.flag_active = 1;

    if (!NewName.isEmpty()) {
        strcpy(tModule.module_name, NewName.toLatin1());
    }
    mod.write_module(&tModule);

    QString modules;
    modules.sprintf("%s", tModule.module_name);
//    modules.sprintf("m_%s.ini", tModule.module_name);
    mTree.appendItem(tree, treeView, modules);

    return modules;
}

QString worker::checkModule(QString address){
    struct t_module tModule;

    mod.read_module(&tModule, address);

    QString modules;
    modules.sprintf("m_%s.ini", tModule.module_name);
    return modules;
}

QString worker::check_statusModule(QString address){
    struct t_module tModule;

    address.sprintf("data/module/%s", address.toUtf8().data());

    mod.read_module(&tModule, address);

    QString modules;
    if(tModule.flag_active){
        modules.sprintf("m_%s.ini", tModule.module_name);
        return modules;
    }
    return "none";
}

void worker::showModule(QWidget *parent, QMdiArea *mdiArea, QString module, QSerialPort *SerialPort){
    struct t_module tModule;
    QString address;

    address.sprintf("data/module/m_%s.ini", module.toUtf8().data());
    mod.read_module(&tModule, address);


    formModule *fModule;

    fModule = new formModule(parent, address, SerialPort);
    fModule->setModal(true);
    fModule->setWindowTitle(tModule.module_name);
//    fModule->setMaximumWidth(700);

    mdiArea->addSubWindow(fModule, 0);

    fModule->exec();

}

bool worker::checkIfmodule(QString name){
    /** ----------------------------- WRITE ---------------------------- **/
    bool cek = false;
    QDir path("data/module");
    QStringList files = path.entryList(QDir::Files);

    QString currFiles;
    currFiles.sprintf("m_%s.ini", name.toUtf8().data());

    for(int i = 0; i < files.count(); i++){
        if(currFiles == QString(files.at(i))) cek = true;
    }

//    std::string sub = name.toStdString();
//    ext = QString::fromStdString(sub.substr(index_max-3, index_max));

//    if(ext == ".ini") return true;
//    else return false;

    return cek;
}

bool worker::state_of_module(int num, QString newModule, QString *existModule){
    bool cek;
    int  ceknt = num+1;
//    QString currModule;
    existModule->prepend("m_").append(".ini");

    for(int n = 0; n < ceknt; n++){
//        currModule = existModule->at(n);
//        currModule.prepend("m_").append(".ini");
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
