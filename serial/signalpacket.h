#ifndef SIGNALPACKET_H
#define SIGNALPACKET_H

#include "serial.h"

class SignalPacket : public Serial::IPacket
{
public:
    SignalPacket(Serial::PACKET packet);

    virtual QByteArray getData() const;
    virtual char handleData(const QByteArray&);

private:
    Serial::PACKET packet_;
};

#endif // SIGNALPACKET_H
