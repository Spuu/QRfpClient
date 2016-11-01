#include "serialportparams.h"

SerialPortParams::SerialPortParams()
{

}

SerialPortParams::SerialPortParams(const QSerialPort &port) :
    portName_(port.portName()),
    baudRate_((QSerialPort::BaudRate)port.baudRate()),
    dataBits_(port.dataBits()),
    parity_(port.parity()),
    flowControl_(port.flowControl()),
    stopBits_(port.stopBits())
{
}

//SerialPortParams::SerialPortParams(const SerialPortParams &rhs)
//{

//}

QString SerialPortParams::getPortName() const
{
    return portName_;
}

QSerialPort::BaudRate SerialPortParams::getBaudRate() const
{
    return baudRate_;
}

QSerialPort::DataBits SerialPortParams::getDataBits() const
{
    return dataBits_;
}

QSerialPort::Parity SerialPortParams::getParity() const
{
    return parity_;
}

QSerialPort::FlowControl SerialPortParams::getFlowControl() const
{
    return flowControl_;
}

QSerialPort::StopBits SerialPortParams::getStopBits() const
{
    return stopBits_;
}



