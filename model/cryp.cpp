#include "cryp.h"

cryp::cryp()
{

}

void cryp::encryp(QString address)
{
    QString fileName = address;
    if (!fileName.isEmpty()) {
        QFile file_in(fileName);
        if (!file_in.open(QFile::ReadOnly)) {return;}
        QByteArray data = file_in.readAll();
        QFile file_out(fileName);
        if (!file_out.open(QFile::WriteOnly | QFile::Text)) {return;}
        QTextStream out(&file_out);
        out.setCodec("BOCU-1"); //out.setCodec("UTF-8"); //
        out << data;
    }
}

void cryp::decryp(QString address)
{
    QString fileName = address;
    if (!fileName.isEmpty()) {
        QFile file_in(fileName);
        if (!file_in.open(QFile::ReadOnly)) {return;}
        QByteArray data = file_in.readAll();

        QTextStream in(&data);
        in.setAutoDetectUnicode(false);
        in.setCodec("BOCU-1"); //in.setCodec("UTF-8"); //
        QString textFile = in.readAll();

        QFile file_out(fileName);
        if (!file_out.open(QFile::WriteOnly | QFile::Text)) {return;}
        QTextStream out(&file_out);
        out.setCodec("UTF-8");
        out << textFile;
    }
}

