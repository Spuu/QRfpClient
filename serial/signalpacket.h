#ifndef SIGNALPACKET_H
#define SIGNALPACKET_H

#include <iostream>
#include "serial.h"

class SignalPacket : public Serial::IPacket
{
public:
    SignalPacket(Serial::PACKET packet = Serial::ACK);
    virtual ~SignalPacket() {}

    virtual QByteArray getData() const;

private:
    Serial::PACKET packet_;
};

#endif // SIGNALPACKET_H
