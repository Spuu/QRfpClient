#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include "serialportparams.h"

class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    SerialPort(const SerialPortParams &);
    virtual ~SerialPort() {}
};

#endif // SERIALPORT_H
