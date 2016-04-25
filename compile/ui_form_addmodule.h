/********************************************************************************
** Form generated from reading UI file 'form_addmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ADDMODULE_H
#define UI_FORM_ADDMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_form_addModule
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QComboBox *cb_operator_2;
    QLabel *label_7;
    QLineEdit *edit_devicename_2;
    QLabel *label_8;
    QComboBox *cb_status_2;
    QLabel *label_9;
    QComboBox *cb_com_2;
    QLabel *label_10;
    QLineEdit *edit_number_2;
    QLabel *label_11;
    QLabel *label_12;
    QCheckBox *ck_flag_active_gsm_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cb_operator_1;
    QLabel *label_2;
    QLineEdit *edit_devicename_1;
    QLabel *label_3;
    QComboBox *cb_status_1;
    QLabel *label_4;
    QComboBox *cb_com_1;
    QLabel *label_5;
    QLineEdit *edit_number_1;
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *label_14;
    QLineEdit *edit_module_name;
    QGridLayout *gridLayout_3;
    QLabel *label_13;
    QLineEdit *edit_sn;

    void setupUi(QDialog *form_addModule)
    {
        if (form_addModule->objectName().isEmpty())
            form_addModule->setObjectName(QStringLiteral("form_addModule"));
        form_addModule->resize(634, 353);
        layoutWidget = new QWidget(form_addModule);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(350, 130, 265, 161));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setEnabled(false);
        label_6->setMinimumSize(QSize(111, 17));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        cb_operator_2 = new QComboBox(layoutWidget);
        cb_operator_2->setObjectName(QStringLiteral("cb_operator_2"));
        cb_operator_2->setEnabled(false);
        cb_operator_2->setMinimumSize(QSize(141, 27));

        gridLayout_2->addWidget(cb_operator_2, 0, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setEnabled(false);
        label_7->setMinimumSize(QSize(111, 17));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        edit_devicename_2 = new QLineEdit(layoutWidget);
        edit_devicename_2->setObjectName(QStringLiteral("edit_devicename_2"));
        edit_devicename_2->setEnabled(false);
        edit_devicename_2->setMinimumSize(QSize(141, 27));

        gridLayout_2->addWidget(edit_devicename_2, 1, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setEnabled(false);
        label_8->setMinimumSize(QSize(111, 17));

        gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

        cb_status_2 = new QComboBox(layoutWidget);
        cb_status_2->setObjectName(QStringLiteral("cb_status_2"));
        cb_status_2->setEnabled(false);
        cb_status_2->setMinimumSize(QSize(141, 27));

        gridLayout_2->addWidget(cb_status_2, 2, 1, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setEnabled(false);
        label_9->setMinimumSize(QSize(111, 17));

        gridLayout_2->addWidget(label_9, 3, 0, 1, 1);

        cb_com_2 = new QComboBox(layoutWidget);
        cb_com_2->setObjectName(QStringLiteral("cb_com_2"));
        cb_com_2->setEnabled(false);
        cb_com_2->setMinimumSize(QSize(141, 27));

        gridLayout_2->addWidget(cb_com_2, 3, 1, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setEnabled(false);
        label_10->setMinimumSize(QSize(111, 17));

        gridLayout_2->addWidget(label_10, 4, 0, 1, 1);

        edit_number_2 = new QLineEdit(layoutWidget);
        edit_number_2->setObjectName(QStringLiteral("edit_number_2"));
        edit_number_2->setEnabled(false);
        edit_number_2->setMinimumSize(QSize(141, 27));

        gridLayout_2->addWidget(edit_number_2, 4, 1, 1, 1);

        label_11 = new QLabel(form_addModule);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 96, 91, 31));
        label_12 = new QLabel(form_addModule);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setEnabled(true);
        label_12->setGeometry(QRect(350, 98, 91, 31));
        ck_flag_active_gsm_2 = new QCheckBox(form_addModule);
        ck_flag_active_gsm_2->setObjectName(QStringLiteral("ck_flag_active_gsm_2"));
        ck_flag_active_gsm_2->setGeometry(QRect(347, 56, 121, 22));
        ck_flag_active_gsm_2->setMinimumSize(QSize(121, 22));
        layoutWidget1 = new QWidget(form_addModule);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(18, 130, 265, 161));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(111, 17));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cb_operator_1 = new QComboBox(layoutWidget1);
        cb_operator_1->setObjectName(QStringLiteral("cb_operator_1"));
        cb_operator_1->setMinimumSize(QSize(141, 27));

        gridLayout->addWidget(cb_operator_1, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(111, 17));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        edit_devicename_1 = new QLineEdit(layoutWidget1);
        edit_devicename_1->setObjectName(QStringLiteral("edit_devicename_1"));
        edit_devicename_1->setMinimumSize(QSize(141, 27));

        gridLayout->addWidget(edit_devicename_1, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(111, 17));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        cb_status_1 = new QComboBox(layoutWidget1);
        cb_status_1->setObjectName(QStringLiteral("cb_status_1"));
        cb_status_1->setMinimumSize(QSize(141, 27));

        gridLayout->addWidget(cb_status_1, 2, 1, 1, 1);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(111, 17));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        cb_com_1 = new QComboBox(layoutWidget1);
        cb_com_1->setObjectName(QStringLiteral("cb_com_1"));
        cb_com_1->setMinimumSize(QSize(141, 27));

        gridLayout->addWidget(cb_com_1, 3, 1, 1, 1);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(111, 17));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        edit_number_1 = new QLineEdit(layoutWidget1);
        edit_number_1->setObjectName(QStringLiteral("edit_number_1"));
        edit_number_1->setMinimumSize(QSize(141, 27));

        gridLayout->addWidget(edit_number_1, 4, 1, 1, 1);

        buttonBox = new QDialogButtonBox(form_addModule);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(14, 314, 601, 27));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget2 = new QWidget(form_addModule);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(19, 16, 267, 66));
        gridLayout_5 = new QGridLayout(layoutWidget2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_14 = new QLabel(layoutWidget2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMinimumSize(QSize(111, 17));

        gridLayout_4->addWidget(label_14, 0, 0, 1, 1);

        edit_module_name = new QLineEdit(layoutWidget2);
        edit_module_name->setObjectName(QStringLiteral("edit_module_name"));
        edit_module_name->setMinimumSize(QSize(146, 27));

        gridLayout_4->addWidget(edit_module_name, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_13 = new QLabel(layoutWidget2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(111, 17));

        gridLayout_3->addWidget(label_13, 0, 0, 1, 1);

        edit_sn = new QLineEdit(layoutWidget2);
        edit_sn->setObjectName(QStringLiteral("edit_sn"));
        edit_sn->setMinimumSize(QSize(146, 27));

        gridLayout_3->addWidget(edit_sn, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 1, 0, 1, 1);


        retranslateUi(form_addModule);

        QMetaObject::connectSlotsByName(form_addModule);
    } // setupUi

    void retranslateUi(QDialog *form_addModule)
    {
        form_addModule->setWindowTitle(QApplication::translate("form_addModule", "Dialog", 0));
        label_6->setText(QApplication::translate("form_addModule", "Operator", 0));
        cb_operator_2->clear();
        cb_operator_2->insertItems(0, QStringList()
         << QApplication::translate("form_addModule", "TELKOMSEL", 0)
         << QApplication::translate("form_addModule", "INDOSAT", 0)
         << QApplication::translate("form_addModule", "XL", 0)
        );
        label_7->setText(QApplication::translate("form_addModule", "Device name", 0));
        label_8->setText(QApplication::translate("form_addModule", "Status", 0));
        cb_status_2->clear();
        cb_status_2->insertItems(0, QStringList()
         << QApplication::translate("form_addModule", "NOT ACTIVE", 0)
         << QApplication::translate("form_addModule", "ACTIVE", 0)
        );
        label_9->setText(QApplication::translate("form_addModule", "Communication", 0));
        cb_com_2->clear();
        cb_com_2->insertItems(0, QStringList()
         << QApplication::translate("form_addModule", "SMS", 0)
         << QApplication::translate("form_addModule", "GPRS", 0)
        );
        label_10->setText(QApplication::translate("form_addModule", "Number", 0));
        label_11->setText(QApplication::translate("form_addModule", "<html><head/><body><p><span style=\" font-size:20pt; color:#0f0c67;\">GSM 1</span></p></body></html>", 0));
        label_12->setText(QApplication::translate("form_addModule", "<html><head/><body><p><span style=\" font-size:20pt; color:#0f0c67;\">GSM 2</span></p></body></html>", 0));
        ck_flag_active_gsm_2->setText(QApplication::translate("form_addModule", "Active GSM 2", 0));
        label->setText(QApplication::translate("form_addModule", "Operator", 0));
        cb_operator_1->clear();
        cb_operator_1->insertItems(0, QStringList()
         << QApplication::translate("form_addModule", "TELKOMSEL", 0)
         << QApplication::translate("form_addModule", "INDOSAT", 0)
         << QApplication::translate("form_addModule", "XL", 0)
        );
        label_2->setText(QApplication::translate("form_addModule", "Device name", 0));
        label_3->setText(QApplication::translate("form_addModule", "Status", 0));
        cb_status_1->clear();
        cb_status_1->insertItems(0, QStringList()
         << QApplication::translate("form_addModule", "NOT ACTIVE", 0)
         << QApplication::translate("form_addModule", "ACTIVE", 0)
        );
        label_4->setText(QApplication::translate("form_addModule", "Communication", 0));
        cb_com_1->clear();
        cb_com_1->insertItems(0, QStringList()
         << QApplication::translate("form_addModule", "SMS", 0)
         << QApplication::translate("form_addModule", "GPRS", 0)
        );
        label_5->setText(QApplication::translate("form_addModule", "Number", 0));
        label_14->setText(QApplication::translate("form_addModule", "Module Name", 0));
        label_13->setText(QApplication::translate("form_addModule", "Serial Number", 0));
    } // retranslateUi

};

namespace Ui {
    class form_addModule: public Ui_form_addModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ADDMODULE_H
