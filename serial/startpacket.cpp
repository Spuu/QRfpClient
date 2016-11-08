#include "startpacket.h"
#include <QDebug>


StartPacket::StartPacket(std::string job, char trans, QByteArray begin, QByteArray end) :
    job_(job),
    trans_(trans),
    d_begin(std::move(begin)),
    d_end(std::move(end))
{
    while(d_begin.size() < 18) d_begin.insert(0, ' ');
    while(d_end.size() < 18) d_end.insert(0, ' ');
}

QByteArray StartPacket::getData() const
{
    QByteArray data;
    data += 'S';
    data += job_.c_str();
    data += trans_;
    data += d_begin;
    data += d_end;
    data += Serial::ETX;
    data += Serial::CalcCrc(data);

    // STX does not count to CRC
    data.prepend(Serial::STX);

    return data;
}
