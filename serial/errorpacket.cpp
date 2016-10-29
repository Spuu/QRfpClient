#include "errorpacket.h"

ErrorPacket::ErrorPacket(const QByteArray &msg) : data_(msg)
{
    handleData(msg);
}

char ErrorPacket::handleData(const QByteArray&)
{


}
