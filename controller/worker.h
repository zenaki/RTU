#ifndef WORKER_H
#define WORKER_H

#include "util/utama.h"

#include <model/interface_manipulator/mtreeview.h>
#include <model/module.h>
#include <view/formmodule.h>
#include <ui_formmodule.h>

class worker
{
public:
    worker();
    module mod;
    mTreeview mTree;

    QString newModule(QStandardItemModel *tree, QTreeView *treeView, QString title);
    QString loadModule(QStandardItemModel *tree, QTreeView *treeView, QString address);
    QString checkModule(QString address);
    QString check_statusModule(QString address);

    void showModule(QWidget *parent, QMdiArea *mdiArea, QString module);

    bool checkIfmodule(QString name);
    bool state_of_module(int num, QString newModule, QString *existModule);
};

#endif // WORKER_H
