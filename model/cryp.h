#ifndef CRYP_H
#define CRYP_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QAction>
#include <QTextStream>

#define ENCRYP "UTF-8" //"BOCU-1" //
#define DECRYP "UTF-8"

class cryp
{
public:
    cryp();

    void encryp(QString address);
    void decryp(QString address);
};

#endif // CRYP_H
