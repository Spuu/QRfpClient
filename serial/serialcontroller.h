#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QWidget>
#include <QSerialPort>
#include "serial.h"

class SerialController : public QWidget
{
    Q_OBJECT

public:
    explicit SerialController(QSerialPort *port, QWidget *parent = 0, int timeout = 2000);

protected:
    int timeout_;
    QSerialPort *port_;

signals:
    void dataReceived(const QByteArray &data);
    void dataSent(const QByteArray &data);
    void error(const QString &err);

public slots:
    Serial::RESULT read();
    Serial::RESULT write(QByteArray data);
};

#endif // SERIALCONTROLLER_H
