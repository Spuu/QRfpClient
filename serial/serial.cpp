#include "serial.h"

namespace Serial {

void IPacket::setResult(RESULT result) { result_ = result; }

QByteArray CalcCrc(const QByteArray& ba)
{
    return CalcCrc(ba.data(), ba.size());
}

QByteArray CalcCrc(const char *str,int len)
{
    short crc=0;
    for(int i=0;i<len;i++)
        crc ^= (short)((unsigned char)str[i]) << (i%9);

    return QByteArray::number(crc, 16).toUpper().rightJustified(4, '0');
}

QByteArray createSerialPacket(PACKET p)
{
    QByteArray data;
    data.append(p);
    return data;
}

}
