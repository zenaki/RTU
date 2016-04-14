#ifndef CRYP_H
#define CRYP_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QAction>
#include <QTextStream>

#define ENCRYP "BOCU-1" //"UTF-8" //
#define DECRYP "UTF-8"

class cryp
{
public:
    cryp();

    void encryp(QString address);
    void decryp(QString address);
};

#endif // CRYP_H
