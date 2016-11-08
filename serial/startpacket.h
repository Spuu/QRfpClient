#ifndef STARTPACKET_H
#define STARTPACKET_H

#include "serial.h"
#include <iostream>

#include <QObject>

class StartPacket : public Serial::IPacket
{
public:
    StartPacket(std::string job, char trans, QByteArray begin = "", QByteArray end = "");
    StartPacket(const StartPacket &rhs) = default;
    StartPacket(StartPacket &&rhs) = default;
    StartPacket& operator=(const StartPacket &rhs) = default;
    StartPacket& operator=(StartPacket &&rhs) = default;
    virtual ~StartPacket() {}

    QByteArray getData() const;

private:
    std::string job_;
    char trans_;
    QByteArray d_begin;
    QByteArray d_end;
};

#endif // STARTPACKET_H
