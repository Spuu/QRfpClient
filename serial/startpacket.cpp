#include "startpacket.h"

StartPacket::StartPacket(char job, char trans, QByteArray begin, QByteArray end) :
    job_(job),
    trans_(trans),
    d_begin(begin),
    d_end(end)
{
    while(d_begin.size() < 18) d_begin.insert(0, ' ');
    while(d_end.size() < 18) d_end.insert(0, ' ');
}

QByteArray StartPacket::getData() const
{
    QByteArray data;
    data += Serial::STX;
    data += 'S';
    data += job_;
    data += trans_;
    data += d_begin;
    data += d_end;
    data += Serial::ETX;

    data += Serial::CalcCrc(data);

    return data;
}

char StartPacket::handleData(const QByteArray&)
{
    return Serial::ACK;
}
