/********************************************************************************
** Form generated from reading UI file 'formmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMODULE_H
#define UI_FORMMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formModule
{
public:
    QGridLayout *gridLayout_10;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTableWidget *tabel_input;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QTableWidget *tabel_output;
    QWidget *tab_3;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_7;
    QLabel *label;
    QGridLayout *gridLayout_6;
    QLabel *label_2;
    QLabel *label_7;
    QLabel *opt_1;
    QLabel *label_3;
    QLabel *label_8;
    QLabel *device_1;
    QLabel *label_4;
    QLabel *label_9;
    QLabel *statu_1;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *com_1;
    QLabel *label_6;
    QLabel *label_11;
    QLabel *number_1;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_8;
    QLabel *label_12;
    QGridLayout *gridLayout_9;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *opt_2;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *device_2;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *statu_2;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *com_2;
    QLabel *label_22;
    QLabel *number_2;
    QLabel *label_21;
    QWidget *tab_4;
    QWidget *tab_5;
    QGridLayout *gridLayout_4;
    QTableWidget *tabel_logic;
    QWidget *tab_6;
    QWidget *tab_7;
    QGridLayout *gridLayout_5;
    QTableWidget *tabel_properties;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *formModule)
    {
        if (formModule->objectName().isEmpty())
            formModule->setObjectName(QStringLiteral("formModule"));
        formModule->resize(800, 500);
        formModule->setMinimumSize(QSize(800, 500));
        gridLayout_10 = new QGridLayout(formModule);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        tabWidget = new QTabWidget(formModule);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabel_input = new QTableWidget(tab);
        if (tabel_input->columnCount() < 6)
            tabel_input->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tabel_input->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tabel_input->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tabel_input->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tabel_input->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tabel_input->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tabel_input->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tabel_input->setObjectName(QStringLiteral("tabel_input"));

        gridLayout_2->addWidget(tabel_input, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tabel_output = new QTableWidget(tab_2);
        if (tabel_output->columnCount() < 5)
            tabel_output->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tabel_output->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tabel_output->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tabel_output->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tabel_output->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tabel_output->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        tabel_output->setObjectName(QStringLiteral("tabel_output"));

        gridLayout_3->addWidget(tabel_output, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        layoutWidget_2 = new QWidget(tab_3);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(42, 51, 301, 171));
        gridLayout_7 = new QGridLayout(layoutWidget_2);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_7->addWidget(label, 0, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(-1, 10, -1, -1);
        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(130, 17));

        gridLayout_6->addWidget(label_2, 0, 0, 1, 1);

        label_7 = new QLabel(layoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(16, 17));

        gridLayout_6->addWidget(label_7, 0, 1, 1, 1);

        opt_1 = new QLabel(layoutWidget_2);
        opt_1->setObjectName(QStringLiteral("opt_1"));
        opt_1->setMinimumSize(QSize(151, 17));

        gridLayout_6->addWidget(opt_1, 0, 2, 1, 1);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(130, 17));

        gridLayout_6->addWidget(label_3, 1, 0, 1, 1);

        label_8 = new QLabel(layoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(16, 17));

        gridLayout_6->addWidget(label_8, 1, 1, 1, 1);

        device_1 = new QLabel(layoutWidget_2);
        device_1->setObjectName(QStringLiteral("device_1"));
        device_1->setMinimumSize(QSize(151, 17));

        gridLayout_6->addWidget(device_1, 1, 2, 1, 1);

        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(130, 17));

        gridLayout_6->addWidget(label_4, 2, 0, 1, 1);

        label_9 = new QLabel(layoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMaximumSize(QSize(16, 17));

        gridLayout_6->addWidget(label_9, 2, 1, 1, 1);

        statu_1 = new QLabel(layoutWidget_2);
        statu_1->setObjectName(QStringLiteral("statu_1"));
        statu_1->setMinimumSize(QSize(151, 17));

        gridLayout_6->addWidget(statu_1, 2, 2, 1, 1);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(130, 17));

        gridLayout_6->addWidget(label_5, 3, 0, 1, 1);

        label_10 = new QLabel(layoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMaximumSize(QSize(16, 17));

        gridLayout_6->addWidget(label_10, 3, 1, 1, 1);

        com_1 = new QLabel(layoutWidget_2);
        com_1->setObjectName(QStringLiteral("com_1"));
        com_1->setMinimumSize(QSize(151, 17));

        gridLayout_6->addWidget(com_1, 3, 2, 1, 1);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(130, 17));

        gridLayout_6->addWidget(label_6, 4, 0, 1, 1);

        label_11 = new QLabel(layoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMaximumSize(QSize(16, 17));

        gridLayout_6->addWidget(label_11, 4, 1, 1, 1);

        number_1 = new QLabel(layoutWidget_2);
        number_1->setObjectName(QStringLiteral("number_1"));
        number_1->setMinimumSize(QSize(151, 17));

        gridLayout_6->addWidget(number_1, 4, 2, 1, 1);


        gridLayout_7->addLayout(gridLayout_6, 1, 0, 1, 1);

        layoutWidget = new QWidget(tab_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(440, 51, 301, 171));
        gridLayout_8 = new QGridLayout(layoutWidget);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_8->addWidget(label_12, 0, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_9->setContentsMargins(-1, 10, -1, -1);
        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(130, 17));

        gridLayout_9->addWidget(label_13, 0, 0, 1, 1);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMaximumSize(QSize(16, 17));

        gridLayout_9->addWidget(label_14, 0, 1, 1, 1);

        opt_2 = new QLabel(layoutWidget);
        opt_2->setObjectName(QStringLiteral("opt_2"));
        opt_2->setMinimumSize(QSize(151, 17));

        gridLayout_9->addWidget(opt_2, 0, 2, 1, 1);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMinimumSize(QSize(130, 17));

        gridLayout_9->addWidget(label_15, 1, 0, 1, 1);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMaximumSize(QSize(16, 17));

        gridLayout_9->addWidget(label_16, 1, 1, 1, 1);

        device_2 = new QLabel(layoutWidget);
        device_2->setObjectName(QStringLiteral("device_2"));
        device_2->setMinimumSize(QSize(151, 17));

        gridLayout_9->addWidget(device_2, 1, 2, 1, 1);

        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setMinimumSize(QSize(130, 17));

        gridLayout_9->addWidget(label_17, 2, 0, 1, 1);

        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setMaximumSize(QSize(16, 17));

        gridLayout_9->addWidget(label_18, 2, 1, 1, 1);

        statu_2 = new QLabel(layoutWidget);
        statu_2->setObjectName(QStringLiteral("statu_2"));
        statu_2->setMinimumSize(QSize(151, 17));

        gridLayout_9->addWidget(statu_2, 2, 2, 1, 1);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setMinimumSize(QSize(130, 17));

        gridLayout_9->addWidget(label_19, 3, 0, 1, 1);

        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setMaximumSize(QSize(16, 17));

        gridLayout_9->addWidget(label_20, 3, 1, 1, 1);

        com_2 = new QLabel(layoutWidget);
        com_2->setObjectName(QStringLiteral("com_2"));
        com_2->setMinimumSize(QSize(151, 17));

        gridLayout_9->addWidget(com_2, 3, 2, 1, 1);

        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setMaximumSize(QSize(16, 17));

        gridLayout_9->addWidget(label_22, 4, 1, 1, 1);

        number_2 = new QLabel(layoutWidget);
        number_2->setObjectName(QStringLiteral("number_2"));
        number_2->setMinimumSize(QSize(151, 17));

        gridLayout_9->addWidget(number_2, 4, 2, 1, 1);

        label_21 = new QLabel(layoutWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setMinimumSize(QSize(130, 17));

        gridLayout_9->addWidget(label_21, 4, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_9, 1, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        gridLayout_4 = new QGridLayout(tab_5);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tabel_logic = new QTableWidget(tab_5);
        tabel_logic->setObjectName(QStringLiteral("tabel_logic"));

        gridLayout_4->addWidget(tabel_logic, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        gridLayout_5 = new QGridLayout(tab_7);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        tabel_properties = new QTableWidget(tab_7);
        tabel_properties->setObjectName(QStringLiteral("tabel_properties"));

        gridLayout_5->addWidget(tabel_properties, 0, 0, 1, 1);

        tabWidget->addTab(tab_7, QString());

        gridLayout_10->addWidget(tabWidget, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        pushButton = new QPushButton(formModule);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout, 1, 0, 1, 1);


        retranslateUi(formModule);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(formModule);
    } // setupUi

    void retranslateUi(QDialog *formModule)
    {
        formModule->setWindowTitle(QApplication::translate("formModule", "Dialog", 0));
        QTableWidgetItem *___qtablewidgetitem = tabel_input->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("formModule", "No.", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tabel_input->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("formModule", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tabel_input->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("formModule", "Type", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tabel_input->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("formModule", "Status", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tabel_input->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("formModule", "Calibration M", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tabel_input->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("formModule", "Calibration X", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("formModule", "Input", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tabel_output->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("formModule", "No.", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tabel_output->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("formModule", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tabel_output->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("formModule", "Type", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tabel_output->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("formModule", "Status", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tabel_output->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QApplication::translate("formModule", "Control", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("formModule", "Output", 0));
        label->setText(QApplication::translate("formModule", "<html><head/><body><p><span style=\" font-size:18pt;\">GSM 1</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("formModule", "Operator", 0));
        label_7->setText(QApplication::translate("formModule", ":", 0));
        opt_1->setText(QApplication::translate("formModule", "...", 0));
        label_3->setText(QApplication::translate("formModule", "Device Name", 0));
        label_8->setText(QApplication::translate("formModule", ":", 0));
        device_1->setText(QApplication::translate("formModule", "...", 0));
        label_4->setText(QApplication::translate("formModule", "Status", 0));
        label_9->setText(QApplication::translate("formModule", ":", 0));
        statu_1->setText(QApplication::translate("formModule", "...", 0));
        label_5->setText(QApplication::translate("formModule", "Communication", 0));
        label_10->setText(QApplication::translate("formModule", ":", 0));
        com_1->setText(QApplication::translate("formModule", "...", 0));
        label_6->setText(QApplication::translate("formModule", "Number", 0));
        label_11->setText(QApplication::translate("formModule", ":", 0));
        number_1->setText(QApplication::translate("formModule", "...", 0));
        label_12->setText(QApplication::translate("formModule", "<html><head/><body><p><span style=\" font-size:18pt;\">GSM 2</span></p></body></html>", 0));
        label_13->setText(QApplication::translate("formModule", "Operator", 0));
        label_14->setText(QApplication::translate("formModule", ":", 0));
        opt_2->setText(QApplication::translate("formModule", "...", 0));
        label_15->setText(QApplication::translate("formModule", "Device Name", 0));
        label_16->setText(QApplication::translate("formModule", ":", 0));
        device_2->setText(QApplication::translate("formModule", "...", 0));
        label_17->setText(QApplication::translate("formModule", "Status", 0));
        label_18->setText(QApplication::translate("formModule", ":", 0));
        statu_2->setText(QApplication::translate("formModule", "...", 0));
        label_19->setText(QApplication::translate("formModule", "Communication", 0));
        label_20->setText(QApplication::translate("formModule", ":", 0));
        com_2->setText(QApplication::translate("formModule", "...", 0));
        label_22->setText(QApplication::translate("formModule", ":", 0));
        number_2->setText(QApplication::translate("formModule", "...", 0));
        label_21->setText(QApplication::translate("formModule", "Number", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("formModule", "Communication", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("formModule", "Scheduler", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("formModule", "Logic Configuration", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("formModule", "Data Recording", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("formModule", "Properties", 0));
        pushButton->setText(QApplication::translate("formModule", "SET", 0));
    } // retranslateUi

};

namespace Ui {
    class formModule: public Ui_formModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMODULE_H
