#include "signalpacket.h"

SignalPacket::SignalPacket(Serial::PACKET packet) :
    packet_(packet)
{

}

QByteArray SignalPacket::getData() const
{
    return Serial::createSerialPacket(packet_);
}
