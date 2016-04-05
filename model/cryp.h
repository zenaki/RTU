#ifndef CRYP_H
#define CRYP_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QAction>
#include <QTextStream>

class cryp
{
public:
    cryp();

    void encryp(QString address);
    void decryp(QString address);
};

#endif // CRYP_H
