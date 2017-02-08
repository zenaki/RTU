#ifndef MTREEVIEW_H
#define MTREEVIEW_H

#include "util/utama.h"

/**
 * @brief The mTreeview class
 */
class mTreeview
{
public:
    /**
     * @brief mTreeview
     */
    mTreeview();

    /**
     * @brief add_firstItem
     * @param tree
     * @param treeView
     * @param name
     */
    void add_firstItem(QStandardItemModel *tree, QTreeView *treeView, QString name);
    /**
     * @brief appendItem
     * @param tree
     * @param treeView
     * @param name
     */
    void appendItem(QStandardItemModel *tree, QTreeView *treeView, QString name);
};

#endif // MTREEVIEW_H
