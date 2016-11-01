#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QWidget>
#include <QSerialPort>
#include <memory>
#include "serial.h"

class ISerialCtrl
{
public:
    virtual void dataReceived(const QByteArray &data) = 0;
    virtual void dataSent(const QByteArray &data) = 0;
    virtual void error(const QString &err) = 0;
};

class SerialController
{
public:
    explicit SerialController(ISerialCtrl *ctrl, int timeout = 2000);
    virtual ~SerialController() {}

    void setPort(QSerialPort *port);

protected:
    Serial::RESULT read();
    Serial::RESULT write(QByteArray data);

    int timeout_;

private:
    ISerialCtrl *ctrl_;
    QSerialPort *port_;
};

#endif // SERIALCONTROLLER_H
