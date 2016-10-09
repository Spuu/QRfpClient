#include "serialcontroller.h"

SerialController::SerialController(QSerialPort *port, QWidget *parent, int timeout) :
    QWidget(parent),
    port_(port),
    timeout_(timeout)
{

}

Serial::RESULT SerialController::read()
{
    if (!port_->isOpen()) {
        emit error(QObject::tr("Failed to open port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    }

    QByteArray readData = port_->readAll();
    while (port_->waitForReadyRead(timeout_))
        readData.append(port_->readAll());

    if (port_->error() == QSerialPort::ReadError) {
        emit error(QObject::tr("Failed to read from port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    } else if (port_->error() == QSerialPort::TimeoutError && readData.isEmpty()) {
        emit error(QObject::tr("No data was currently available for reading from port %1").arg(port_->portName()));
        return Serial::FAIL;
    }

    emit dataReceived(readData);
    return Serial::SUCCESS;
}

Serial::RESULT SerialController::write(QByteArray data)
{
    if (!port_->isOpen()) {
        emit error(QObject::tr("Failed to open port %1, error: %2").arg(port_->portName()).arg(port_->error()));
        return Serial::FAIL;
    }

    qint64 bytesWritten = port_->write(data);

    if (bytesWritten == -1) {
        emit error(QObject::tr("Failed to write the data to port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    } else if (bytesWritten != data.size()) {
        emit error(QObject::tr("Failed to write all the data to port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    } else if (!port_->waitForBytesWritten(timeout_)) {
        emit error(QObject::tr("Operation timed out or an error occurred for port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    }

    //port_->flush();
    emit dataSent(data);
    return Serial::SUCCESS;
}
