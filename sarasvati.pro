#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T10:08:34
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sarasvati
TEMPLATE = app

OBJECTS_DIR += compile
UI_DIR += compile
MOC_DIR += compile

SOURCES += \
    main.cpp\
    view/mainwindow.cpp \
    view/formmodule.cpp \
    util/debug.cpp \
    model/interface_manipulator/mtreeview.cpp \
    view/loginform.cpp \
    model/module.cpp \
    model/config.cpp \
    model/communication/serial.cpp \
    model/communication/gsm.cpp \
    model/communication/gprs.cpp \
    model/setting.cpp \
    view/form_addmodule.cpp \
    controller/worker.cpp \
    view/settingsdialog.cpp \
    model/interface_manipulator/qlightboxwidget.cpp \

HEADERS += \
    util/debug.h \
    util/utama.h \
    view/mainwindow.h \
    view/formmodule.h \
    model/interface_manipulator/mtreeview.h \
    view/loginform.h \
    model/module.h \
    model/config.h \
    model/communication/serial.h \
    model/communication/gsm.h \
    model/communication/gprs.h \
    model/setting.h \
    view/form_addmodule.h \
    controller/worker.h \
    view/settingsdialog.h \
    model/interface_manipulator/qlightboxwidget.h \

FORMS += \
    view/mainwindow.ui \
    view/formmodule.ui \
    view/loginform.ui \
    view/form_addmodule.ui \
    view/settingsdialog.ui

RESOURCES += \
    image.qrc
