#-------------------------------------------------
#
# Project created by "PT. Daun Biru Engineering" - 2015-10-05T10:08:34
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sarasvati
TEMPLATE = app

OBJECTS_DIR += compile
UI_DIR += compile
MOC_DIR += compile

#########################################################################
#Set Variables QuaZip and ZLib
QUAZIPCODEDIR = "../quazip-0.5.1/quazip"
ZLIBCODEDIR = "../Libs"

#Include the compiled code
unix {
    LIBS += -L$${ZLIBCODEDIR} -lz
}

win32 {
    LIBS += -L$${ZLIBCODEDIR} -lzdll
}

#Include files
INCLUDEPATH += $${QUAZIPCODEDIR}
HEADERS += $${QUAZIPCODEDIR}/*.h \
    view/progressdialog.h
SOURCES += $${QUAZIPCODEDIR}/*.cpp \
    view/progressdialog.cpp
SOURCES += $${QUAZIPCODEDIR}/*.c
#########################################################################

SOURCES += \
    main.cpp\
    view/mainwindow.cpp \
    view/formmodule.cpp \
    util/debug.cpp \
    model/interface_manipulator/mtreeview.cpp \
    view/loginform.cpp \
    model/module.cpp \
    model/cryp.cpp \
    model/communication/serial.cpp \
    model/communication/gsm.cpp \
    model/communication/gprs.cpp \
    model/setting.cpp \
    view/form_addmodule.cpp \
    controller/worker.cpp \
    view/settingsdialog.cpp \
    model/interface_manipulator/qlightboxwidget.cpp

HEADERS += \
    util/debug.h \
    util/utama.h \
    view/mainwindow.h \
    view/formmodule.h \
    model/interface_manipulator/mtreeview.h \
    view/loginform.h \
    model/module.h \
    model/cryp.h \
    model/communication/serial.h \
    model/communication/gsm.h \
    model/communication/gprs.h \
    model/setting.h \
    view/form_addmodule.h \
    controller/worker.h \
    view/settingsdialog.h \
    model/interface_manipulator/qlightboxwidget.h

FORMS += \
    view/mainwindow.ui \
    view/formmodule.ui \
    view/loginform.ui \
    view/form_addmodule.ui \
    view/settingsdialog.ui \
    view/progressdialog.ui

RESOURCES += \
    image.qrc
