#ifndef STARTPACKET_H
#define STARTPACKET_H

#include "serial.h"

#include <QObject>

class StartPacket : public Serial::IPacket
{
public:
    StartPacket(char job, char trans, QByteArray begin = QByteArray(18, ' '), QByteArray end = QByteArray(18, ' '));

    QByteArray getData() const;
    char handleData(const QByteArray&);

private:
    char job_;
    char trans_;
    QByteArray d_begin;
    QByteArray d_end;
};

#endif // STARTPACKET_H
