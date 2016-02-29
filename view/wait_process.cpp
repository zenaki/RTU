#include "wait_process.h"

wait_process::wait_process()
{

}

void wait_process::waiting_show(QWidget *parent, QString title, QString desc)
{
    /** Set Light Box for Busy **/
    //QLightBoxWidget* lightBox = new QLightBoxWidget(parent);
    lightBox = new QLightBoxWidget(parent);

//    QLabel* lbTitle = new QLabel(title);
    lbTitle = new QLabel(title);
    lbTitle->setStyleSheet("font-size: 28px; font-weight: bold; color: white");
//    QLabel* lbProgress = new QLabel;
    lbProgress = new QLabel;
//    QMovie* progressMovie = new QMovie(":/new/prefix1/image/loader.gif");
    progressMovie = new QMovie(":/new/prefix1/image/loader.gif");
    lbProgress->setMovie(progressMovie);
    progressMovie->start();
    desc.prepend("wait a second\n");
//    QLabel* lbDescription = new QLabel(desc.toUtf8().data());
    lbDescription = new QLabel(desc.toUtf8().data());
    lbDescription->setStyleSheet("color: white");
//    QPushButton* lbClose = new QPushButton("Close");
//    lbClose = new QPushButton("Close");

//    QGridLayout* lbLayout = new QGridLayout;
    lbLayout = new QGridLayout;
    lbLayout->setRowStretch(0, 1);
    lbLayout->setColumnStretch(0, 1);
    lbLayout->addWidget(lbTitle, 1, 1);
    lbLayout->addWidget(lbProgress, 1, 2, Qt::AlignRight);
    lbLayout->setColumnStretch(3, 1);
    lbLayout->addWidget(lbDescription, 2, 1, 1, 2);
//    lbLayout->addWidget(lbClose, 3, 2);
    lbLayout->setRowStretch(4, 1);

//    connect(showLB, SIGNAL(clicked()), lightBox, SLOT(show()));
//    connect(lbClose, SIGNAL(clicked()), lightBox, SLOT(close()));
    lightBox->setLayout(lbLayout);
//    lightBox->show();
//    lightBox->close();
}

void wait_process::waiting_close()
{
    lightBox->close();
}
