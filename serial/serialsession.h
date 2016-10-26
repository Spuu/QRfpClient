#ifndef SERIALSESSION_H
#define SERIALSESSION_H

#include "serial/serialcontroller.h"

#include <QThread>
#include <QTimer>

class SerialSession : public QThread, public ISerialCtrl, public SerialController
{
    Q_OBJECT
public:
    SerialSession(QSerialPort *port, Serial::DIRECTION direction, Serial::IPacket &&start_packet,
                  const std::vector<Serial::IPacket*> *input_data, Serial::IPacket *resp_handler, int timeout = 10000);

    SerialSession(QSerialPort *port, Serial::DIRECTION direction, Serial::IPacket &&start_packet,
                  Serial::IPacket *resp_handler, int timeout = 2000);

    void dataReceived(const QByteArray &data);
    void dataSent(const QByteArray &data);
    void error(const QString &err);

public slots:
    void process();

signals:
    void end_of_eventloop();

private slots:
    void async_reader();

private:
    enum class STATE {
        NOT_STARTED,
        HOST_TO_DEVICE,
        DEVICE_TO_HOST,
        CLOSED
    };

    const std::vector<Serial::IPacket*> *input_data_;
    Serial::IPacket &&start_packet_;
    Serial::IPacket *resp_hdl_;
    Serial::DIRECTION direction_;
    STATE state_;

    std::vector<Serial::IPacket*> data_to_send_;
    std::vector<Serial::IPacket*>::iterator d_iter_;

    std::unique_ptr<QTimer> timer_;

    void init();
    void watchdog();
    bool openPort();
    void closePort();
    void prepareDataToSend();
    void writePrepared();
    void run();
};

#endif // SERIALSESSION_H
