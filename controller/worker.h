#ifndef WORKER_H
#define WORKER_H

#include <QSerialPort>

#include "util/utama.h"

#include <model/interface_manipulator/mtreeview.h>
#include <model/module.h>
#include <view/mainwindow.h>
#include <view/formmodule.h>
#include <ui_formmodule.h>
#include "model/communication/serial.h"

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QTime>

#include <model/interface_manipulator/qlightboxwidget.h>

#include <QString>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QGridLayout>

//#include "JlCompress.h"

class MainWindow;
class formModule;
class serial;
class QLightBoxWidget;
/**
 * @brief Class worker
 */
class worker /*: public QObject*/
{
//    Q_OBJECT
public:
    /**
     * @brief worker
     */
    worker();
    /**
     * @brief mod
     */
    module mod;
    /**
     * @brief mTree
     */
    mTreeview mTree;
    /**
     * @brief Serial
     */
    serial *Serial;

    /**
     * @brief newModule
     * @param tree
     * @param treeView
     * @param title
     * @return
     */
    QString newModule(QStandardItemModel *tree, QTreeView *treeView, QString title);
    /**
     * @brief editModule
     * @param tree
     * @param treeView
     * @param title
     * @return
     */
    QString editModule(QStandardItemModel *tree, QTreeView *treeView, QString title);
    /**
     * @brief loadModule
     * @param tree
     * @param treeView
     * @param address
     * @param NewName
     * @return
     */
    QString loadModule(QStandardItemModel *tree, QTreeView *treeView, QString address, QString NewName);
    /**
     * @brief checkModule
     * @param address
     * @return
     */
    QString checkModule(QString address);
    /**
     * @brief check_statusModule
     * @param address
     * @return
     */
    QString check_statusModule(QString address);

    /**
     * @brief showModule
     * @param parent
     * @param mdiArea
     * @param module
     * @param SerialPort
     */
    void showModule(QWidget *parent, QMdiArea *mdiArea, QString module, QSerialPort *SerialPort);

    /**
     * @brief checkIfmodule
     * @param name
     * @return
     */
    bool checkIfmodule(QString name);
    /**
     * @brief state_of_module
     * @param num
     * @param newModule
     * @param existModule
     * @return
     */
    bool state_of_module(int num, QString newModule, QString *existModule);

    /**
     * @brief Request_ENV
     * @param Serial_Com
     * @param timeout
     * @return
     */
    bool Request_ENV(QSerialPort *Serial_Com, bool timeout = false);

    /**
     * @brief write_FinishRead
     * @param FinishRead
     * @param cekErr
     * @param strErr
     */
    void write_FinishRead(bool FinishRead, int cekErr, QString strErr);
    /**
     * @brief read_FinishRead
     * @return
     */
    bool read_FinishRead();
    /**
     * @brief read_flagERR
     * @return
     */
    int read_flagERR();
    /**
     * @brief read_strERR
     * @return
     */
    QString read_strERR();

    void delay(int ms);
    /**
     * @brief serial_write
     * @param Serial_Com
     * @param data
     * @param d_c
     */
    void serial_write(QSerialPort * Serial_Com, QString data, int d_c);
    /**
     * @brief waiting_set
     * @param timeout
     * @return
     */
    bool waiting_set(bool timeout = false);

    /**
     * @brief writeLogFile
     * @param log
     * @param flagERR
     * @param strERR
     * @param timeout
     */
    void writeLogFile(QString log, int flagERR, QString strERR, bool timeout);

    /**
     * @brief CompressDir
     * @param ZipFile
     * @param Directory
     */
    void CompressDir(QString ZipFile, QString Directory);
    /**
     * @brief DecompressDir
     * @param ZipFile
     * @param Directory
     */
    void DecompressDir(QString ZipFile, QString Directory);
    /**
     * @brief CompressFiles
     * @param ZipFile
     * @param Files
     */
    void CompressFiles(QString ZipFile, QStringList Files);
    /**
     * @brief DecompressFiles
     * @param ZipFile
     * @param Files
     * @param Directory
     */
    void DecompressFiles(QString ZipFile, QStringList Files, QString Directory);
    /**
     * @brief ListContents
     * @param ZipFile
     * @return
     */
    QStringList ListContents(QString ZipFile);

//private slots:
//    void CancelSetting();
//signals:
//    void TimeOut();
};

#endif // WORKER_H
