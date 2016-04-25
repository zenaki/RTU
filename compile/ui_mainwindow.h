/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionLoad;
    QAction *actionConnect;
    QAction *actionRead_Config;
    QAction *actionWrite_Config;
    QAction *actionSave;
    QAction *actionMenu;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSetting;
    QMenu *menuModule;
    QMenu *menuUser_Access;
    QMenu *menuHelp;
    QMenu *menuActive_Window;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1250, 800);
        MainWindow->setMinimumSize(QSize(1100, 500));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionRead_Config = new QAction(MainWindow);
        actionRead_Config->setObjectName(QStringLiteral("actionRead_Config"));
        actionWrite_Config = new QAction(MainWindow);
        actionWrite_Config->setObjectName(QStringLiteral("actionWrite_Config"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionMenu = new QAction(MainWindow);
        actionMenu->setObjectName(QStringLiteral("actionMenu"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setMinimumSize(QSize(250, 450));

        gridLayout->addWidget(treeView, 0, 0, 1, 1);

        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setMinimumSize(QSize(700, 450));

        gridLayout->addWidget(mdiArea, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1250, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QStringLiteral("menuSetting"));
        menuModule = new QMenu(menuBar);
        menuModule->setObjectName(QStringLiteral("menuModule"));
        menuUser_Access = new QMenu(menuBar);
        menuUser_Access->setObjectName(QStringLiteral("menuUser_Access"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuActive_Window = new QMenu(menuBar);
        menuActive_Window->setObjectName(QStringLiteral("menuActive_Window"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSetting->menuAction());
        menuBar->addAction(menuModule->menuAction());
        menuBar->addAction(menuUser_Access->menuAction());
        menuBar->addAction(menuActive_Window->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionLoad);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionRead_Config);
        mainToolBar->addAction(actionWrite_Config);
        mainToolBar->addAction(actionMenu);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        actionRead_Config->setText(QApplication::translate("MainWindow", "Read Config", 0));
        actionWrite_Config->setText(QApplication::translate("MainWindow", "Write Config", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionMenu->setText(QApplication::translate("MainWindow", "Menu", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuSetting->setTitle(QApplication::translate("MainWindow", "Setting", 0));
        menuModule->setTitle(QApplication::translate("MainWindow", "Module", 0));
        menuUser_Access->setTitle(QApplication::translate("MainWindow", "User Access", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuActive_Window->setTitle(QApplication::translate("MainWindow", "Active Window", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
