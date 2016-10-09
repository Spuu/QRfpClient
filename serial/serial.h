#ifndef SERIAL_H
#define SERIAL_H

namespace Serial {

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
}

#endif // SERIAL_H
