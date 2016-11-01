#include "serialport.h"

SerialPort::SerialPort(const SerialPortParams &params)
{
    this->setPortName(params.getPortName());
    this->setBaudRate(params.getBaudRate());
    this->setDataBits(params.getDataBits());
    this->setParity(params.getParity());
    this->setFlowControl(params.getFlowControl());
    this->setStopBits(params.getStopBits());
}
