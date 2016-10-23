#include "serialcontroller.h"

SerialController::SerialController(ISerialCtrl *ctrl, int timeout) :
    ctrl_(ctrl),
    timeout_(timeout)
{

}

void SerialController::setPort(QSerialPort *port)
{
    port_ = port;
}

Serial::RESULT SerialController::read()
{
    if (!port_->isOpen()) {
        ctrl_->error(QString("Failed to open port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    }

    QByteArray readData = port_->readAll();
    while (port_->waitForReadyRead(timeout_))
        readData.append(port_->readAll());

    if (port_->error() == QSerialPort::ReadError) {
        ctrl_->error(QString("Failed to read from port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    } else if (port_->error() == QSerialPort::TimeoutError && readData.isEmpty()) {
        ctrl_->error(QString("No data was currently available for reading from port %1").arg(port_->portName()));
        return Serial::FAIL;
    }

    ctrl_->dataReceived(readData);
    return Serial::SUCCESS;
}

Serial::RESULT SerialController::write(QByteArray data)
{
    if (!port_->isOpen()) {
        ctrl_->error(QString("Failed to open port %1, error: %2").arg(port_->portName()).arg(port_->error()));
        return Serial::FAIL;
    }

    qint64 bytesWritten = port_->write(data);

    if (bytesWritten == -1) {
        ctrl_->error(QString("Failed to write the data to port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    } else if (bytesWritten != data.size()) {
        ctrl_->error(QString("Failed to write all the data to port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    } else if (!port_->waitForBytesWritten(timeout_)) {
        ctrl_->error(QString("Operation timed out or an error occurred for port %1, error: %2").arg(port_->portName()).arg(port_->errorString()));
        return Serial::FAIL;
    }

    //port_->flush();
    ctrl_->dataSent(data);
    return Serial::SUCCESS;
}
