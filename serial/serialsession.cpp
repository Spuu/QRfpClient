#include "serialsession.h"
#include "logger.h"
#include "signalpacket.h"
#include <QMutexLocker>
#include <QEventLoop>
#include <algorithm>

SerialSession::SerialSession(QSerialPort *port, Serial::IPacket &&start_packet, std::vector<Serial::IPacket*> *input_data,
                             Serial::IPacketHandler *resp_handler, int timeout) :
    direction_(Serial::DEVICE),
    state_(STATE::NOT_STARTED),
    start_packet_(std::move(start_packet)),
    input_data_(input_data),
    resp_hdl_(resp_handler),
    SerialController(this, timeout)
{
    setPort(port);
    init();
}

SerialSession::SerialSession(QSerialPort *port, Serial::IPacket &&start_packet, Serial::IPacketHandler *resp_handler, int timeout) :
    direction_(Serial::HOST),
    state_(STATE::NOT_STARTED),
    start_packet_(std::move(start_packet)),
    input_data_(nullptr),
    resp_hdl_(resp_handler),
    SerialController(this, timeout)
{
    setPort(port);
    init();
}

void SerialSession::init()
{
    timer_ = std::make_unique<QTimer>();
    timer_->setInterval(timeout_);

    QObject::connect(port_, SIGNAL(readyRead()), this, SLOT(async_reader()));
    QObject::connect(timer_.get(), &QTimer::timeout, this, &SerialSession::watchdog);

    signalMap_[Serial::ENQ] = std::make_unique<SignalPacket>(Serial::ENQ);
    signalMap_[Serial::EOT] = std::make_unique<SignalPacket>(Serial::EOT);

    prepareDataToSend();
}

void SerialSession::prepareDataToSend()
{
    data_to_send_.clear();
    data_to_send_.push_back(signalMap_[Serial::ENQ].get());
    data_to_send_.push_back(&start_packet_);

    if(input_data_)
        copy(input_data_->begin(), input_data_->end(), back_inserter(data_to_send_));

    data_to_send_.push_back(signalMap_[Serial::EOT].get());
    d_iter_ = data_to_send_.begin();
}

void SerialSession::async_reader()
{
    read();
}

void SerialSession::run()
{
    process();
}

void SerialSession::process()
{
    Logger::instance().log(LogLevel::INFO, QString("Start Serial Session. Timeout = %1").arg(timeout_));

    if(!openPort()) return;
    timer_->start();

    writePrepared();
    QEventLoop eventloop;
    QObject::connect(this, &SerialSession::end_of_eventloop, &eventloop, &QEventLoop::quit);
    eventloop.exec();

    closePort();
    Logger::instance().log(LogLevel::TRACE, "End of Serial Session.");
    emit finished();
}

void SerialSession::writePrepared()
{
    if(d_iter_ == data_to_send_.end()) {
        if(state_ == STATE::HOST_TO_DEVICE) {
            if(direction_ == Serial::DEVICE)
                state_ = STATE::CLOSED;
            else
                state_ = STATE::DEVICE_TO_HOST;
        }
    }

    if(state_ == STATE::DEVICE_TO_HOST)
        write(Serial::createSerialPacket(Serial::ACK));
    else if(state_ != STATE::CLOSED)
        write((*d_iter_)->getData());
}

void SerialSession::watchdog()
{
    Logger::instance().log(LogLevel::ERROR, "Watchdog HIT! Timeout...");
    timer_->stop();
    state_ = STATE::CLOSED;

    emit end_of_eventloop();
}

bool SerialSession::openPort()
{
    if(!port_->open(QIODevice::ReadWrite)) {
        Logger::instance().log(LogLevel::ERROR, QString("Unable to open COM port: %1").arg(port_->portName()));
        return false;
    }

    Logger::instance().log(LogLevel::TRACE, QString("Opened COM port: %1").arg(port_->portName()));
    state_ = STATE::HOST_TO_DEVICE;
    return true;
}

void SerialSession::closePort()
{
    port_->close();
    Logger::instance().log(LogLevel::DEBUG, QString("Closing Port. Port isOpen -> %1").arg(port_->isOpen()));
}

void SerialSession::dataReceived(const QByteArray &data)
{
    timer_->start();
    Logger::instance().log(LogLevel::TRACE, QString("Data Received (%2 bytes): %1").arg(QString(data)).arg(data.size()));

    if(direction_ == Serial::DEVICE) {
        dataReceivedToDevice(data);
    } else {
        dataReceivedToHost(data);
    }
}

void SerialSession::dataReceivedToDevice(const QByteArray &data)
{
    if(data.size() != 1)
        Logger::instance().log(LogLevel::WARNING, "Received data should be 1 byte.");

    if(data.isEmpty()) {
        Logger::instance().log(LogLevel::ERROR, "Received data is empty.");
        return;
    }

    switch(data[0]) {
    case Serial::ACK:
        (*d_iter_)->setResult(Serial::SUCCESS);
        ++d_iter_;
        break;

    case Serial::NAK:
        break;

    case Serial::WACK:
        QThread::sleep(1);
        break;

    case Serial::RVI:
        state_ = STATE::RVI_ERROR;
        direction_ = Serial::HOST;
        data_to_send_.clear();
        data_to_send_.push_back(signalMap_[Serial::EOT].get());
        d_iter_ = data_to_send_.begin();
        break;

    case Serial::EOT:
        (*d_iter_)->setResult(Serial::SUCCESS);
        ++d_iter_;
        break;
    }

    writePrepared();
}

void SerialSession::dataReceivedToHost(const QByteArray &data)
{
    if(data.size() == 1) {
        if(data[0] == Serial::EOT) {
            write(Serial::createSerialPacket(Serial::EOT));
            state_ = STATE::CLOSED;
            return;
        }

        if(data[0] == Serial::WACK)
            return;
    }

    if(state_ == STATE::RVI_ERROR) {
        errorPackets_.push_back(std::make_unique<ErrorPacket>(data));
    } else if(resp_hdl_) {
        char result = resp_hdl_->handleData(data);
        write(Serial::createSerialPacket((Serial::PACKET)result));
    } else {
        write(Serial::createSerialPacket(Serial::ACK));
    }
}

void SerialSession::dataSent(const QByteArray &data)
{
    Logger::instance().log(LogLevel::TRACE, QString("Data Sent: %1").arg(QString(data)));
}

void SerialSession::error(const QString &err)
{
    Logger::instance().log(LogLevel::DEBUG, QString("Error: %1").arg(err));
}
