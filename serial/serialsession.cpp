#include "serialsession.h"
#include "logger.h"
#include "signalpacket.h"

SerialSession::SerialSession(Serial::DIRECTION direction, Serial::IPacket &&start_packet, const std::vector<Serial::IPacket*> *input_data,
                             Serial::IPacket *resp_handler, int timeout) :
    direction_(direction),
    state_(STATE::NOT_STARTED),
    start_packet_(std::move(start_packet)),
    input_data_(input_data),
    resp_hdl_(resp_handler),
    SerialController(this, timeout)
{
    init();
}

SerialSession::SerialSession(Serial::DIRECTION direction, Serial::IPacket &&start_packet, Serial::IPacket *resp_handler, int timeout) :
    direction_(direction),
    state_(STATE::NOT_STARTED),
    start_packet_(std::move(start_packet)),
    input_data_(NULL),
    resp_hdl_(resp_handler),
    SerialController(this, timeout)
{
    init();
}

void SerialSession::init()
{
    timer_ = std::make_unique<QTimer>(this);
    timer_->setInterval(timeout_);

    QObject::connect(this->port_, SIGNAL(readyRead()), this, SLOT(async_reader()));
    QObject::connect(timer_.get(), &QTimer::timeout, this, &SerialSession::watchdog);

    prepareDataToSend();
}

void SerialSession::prepareDataToSend()
{
    data_to_send_.push_back(new SignalPacket(Serial::ENQ));
    data_to_send_.push_back(&start_packet_);
    data_to_send_.push_back(new SignalPacket(Serial::EOT));
    d_iter_ = data_to_send_.begin();
}

void SerialSession::async_reader()
{
    read();
}

void SerialSession::run()
{
    Logger::instance().log(LogLevel::INFO, QString("Start Serial Session. Timeout = %1").arg(timeout_));

    if(!openPort()) return;

    timer_->start();

    writePrepared();
    while(state_ != STATE::CLOSED) {

    }

    closePort();
    Logger::instance().log(LogLevel::TRACE, "End of Serial Session.");
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
            direction_ = Serial::HOST;
            data_to_send_.clear();
            data_to_send_.push_back(new SignalPacket(Serial::EOT));
            d_iter_ = data_to_send_.begin();
            break;

        case Serial::EOT:
            (*d_iter_)->setResult(Serial::SUCCESS);
            ++d_iter_;
            break;
        }

        writePrepared();
    } else {
        if(data.size() == 1 && data[0] == Serial::EOT) {
            write(Serial::createSerialPacket(Serial::EOT));
            state_ = STATE::CLOSED;
        } else {
            write(Serial::createSerialPacket(Serial::ACK));
        }
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
