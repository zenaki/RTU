#include "mtreeview.h"

mTreeview::mTreeview()
{

}

void mTreeview::add_firstItem(QStandardItemModel *tree, QTreeView *treeView, QString name){
    QStandardItem *item;

    item = new QStandardItem(name);
    tree->appendRow(item);

    treeView->setModel(tree);
}

void mTreeview::appendItem(QStandardItemModel *tree, QTreeView *treeView, QString name){
    QStandardItem *sd;
    QStandardItem *item;

    item = new QStandardItem(name);

    sd = tree->itemFromIndex(treeView->indexAt(QPoint(0,0)));
    sd->appendRow(item);

    treeView->setModel(tree);
}

