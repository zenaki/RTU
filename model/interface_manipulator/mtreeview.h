#ifndef MTREEVIEW_H
#define MTREEVIEW_H

#include "util/utama.h"

class mTreeview
{
public:
    mTreeview();

    void add_firstItem(QStandardItemModel *tree, QTreeView *treeView, QString name);
    void appendItem(QStandardItemModel *tree, QTreeView *treeView, QString name);
};

#endif // MTREEVIEW_H
