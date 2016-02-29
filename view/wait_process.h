#ifndef WAIT_PROCESS_H
#define WAIT_PROCESS_H

#include <model/interface_manipulator/qlightboxwidget.h>

#include <QString>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QGridLayout>

class wait_process
{
public:
    wait_process();

    QLightBoxWidget *lightBox;

    QLabel *lbTitle;
    QLabel *lbProgress;
    QMovie *progressMovie;
    QLabel *lbDescription;
    QPushButton *lbClose;

    QGridLayout *lbLayout;

    void waiting_show(QWidget *parent, QString title, QString desc);
    void waiting_close();
};

#endif // WAIT_PROCESS_H
