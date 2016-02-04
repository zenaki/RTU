/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginForm
{
public:
    QPushButton *loginButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *editUser;
    QLabel *label_2;
    QLineEdit *editPass;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *loginmage;

    void setupUi(QDialog *loginForm)
    {
        if (loginForm->objectName().isEmpty())
            loginForm->setObjectName(QStringLiteral("loginForm"));
        loginForm->resize(459, 260);
        loginForm->setMinimumSize(QSize(459, 260));
        loginForm->setMaximumSize(QSize(459, 260));
        loginButton = new QPushButton(loginForm);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(334, 190, 99, 27));
        layoutWidget = new QWidget(loginForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(164, 123, 271, 62));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(81, 17));
        label->setMaximumSize(QSize(81, 17));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        editUser = new QLineEdit(layoutWidget);
        editUser->setObjectName(QStringLiteral("editUser"));
        editUser->setMinimumSize(QSize(181, 27));
        editUser->setMaximumSize(QSize(181, 27));

        gridLayout->addWidget(editUser, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(81, 17));
        label_2->setMaximumSize(QSize(81, 17));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        editPass = new QLineEdit(layoutWidget);
        editPass->setObjectName(QStringLiteral("editPass"));
        editPass->setMinimumSize(QSize(181, 27));
        editPass->setMaximumSize(QSize(181, 27));

        gridLayout->addWidget(editPass, 1, 1, 1, 1);

        label_4 = new QLabel(loginForm);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(156, 10, 291, 31));
        label_5 = new QLabel(loginForm);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(150, 40, 301, 31));
        loginmage = new QLabel(loginForm);
        loginmage->setObjectName(QStringLiteral("loginmage"));
        loginmage->setGeometry(QRect(4, 4, 141, 251));
        loginmage->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/image/sarasvati_login_2.png")));
        loginmage->setScaledContents(true);

        retranslateUi(loginForm);

        QMetaObject::connectSlotsByName(loginForm);
    } // setupUi

    void retranslateUi(QDialog *loginForm)
    {
        loginForm->setWindowTitle(QApplication::translate("loginForm", "Dialog", 0));
        loginButton->setText(QApplication::translate("loginForm", "Login", 0));
        label->setText(QApplication::translate("loginForm", "Username", 0));
        label_2->setText(QApplication::translate("loginForm", "Password", 0));
        label_4->setText(QApplication::translate("loginForm", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">Welcome To SARASVATI</span></p></body></html>", 0));
        label_5->setText(QApplication::translate("loginForm", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Monita RTU - Module Configurator</span></p></body></html>", 0));
        loginmage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class loginForm: public Ui_loginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
