#ifndef ERRORPACKET_H
#define ERRORPACKET_H

#include "serial.h"

class ErrorPacket : public Serial::IPacketHandler
{
public:
    ErrorPacket(const QByteArray &msg);
    char handleData(const QByteArray&);

private:
    QByteArray data_;
};

#endif // ERRORPACKET_H
