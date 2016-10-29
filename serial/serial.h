#ifndef SERIAL_H
#define SERIAL_H

#include <QByteArray>

namespace Serial {

    enum DIRECTION {
        DEVICE,
        HOST,
    };

    enum RESULT {
        SUCCESS,
        FAIL
    };

    enum PACKET {
        ENQ = 0x05,
        ACK = 0x06,
        NAK = 0x15,
        STX = 0x02,
        ETX = 0x03,
        ETB = 0x17,
        EOT = 0x04,
        WACK = 0x09,
        RVI = 0x40
    };

    class IPacketHandler {
    public:
        virtual char handleData(const QByteArray&) = 0;
    };

    class IPacket
    {
    public:
        virtual QByteArray getData() const = 0;
        virtual void setResult(RESULT result);

    private:
        RESULT result_ = FAIL;
    };

    QByteArray CalcCrc(const QByteArray& ba);
    QByteArray CalcCrc(const char *str,int len);
    QByteArray createSerialPacket(PACKET p);
}

#endif // SERIAL_H
