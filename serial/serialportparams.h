#ifndef SERIALPORTPARAMS_H
#define SERIALPORTPARAMS_H

#include <QString>
#include <QtSerialPort>

/**
 * Keeps QSerialPort connection parameters
 */
class SerialPortParams
{
public:
    SerialPortParams();
    SerialPortParams(const QSerialPort &);
    SerialPortParams(const SerialPortParams &) = default;
    virtual ~SerialPortParams() {}

    QString getPortName() const;
    QSerialPort::BaudRate getBaudRate() const;
    QSerialPort::DataBits getDataBits() const;
    QSerialPort::Parity getParity() const;
    QSerialPort::FlowControl getFlowControl() const;
    QSerialPort::StopBits getStopBits() const;

private:
    QString portName_;
    QSerialPort::BaudRate baudRate_;
    QSerialPort::DataBits dataBits_;
    QSerialPort::Parity parity_;
    QSerialPort::FlowControl flowControl_;
    QSerialPort::StopBits stopBits_;
};

#endif // SERIALPORTPARAMS_H
