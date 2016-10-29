#ifndef SERIALSESSION_H
#define SERIALSESSION_H

#include "serial/serialcontroller.h"
#include "serial/signalpacket.h"
#include "serial/errorpacket.h"

#include <QThread>
#include <QTimer>

class SerialSession : public QObject, public ISerialCtrl, public SerialController
{
    Q_OBJECT
public:
    SerialSession(QSerialPort *port, Serial::IPacket &&start_packet, std::vector<Serial::IPacket*> *input_data,
                  Serial::IPacketHandler *resp_handler, int timeout = 10000);

    SerialSession(QSerialPort *port, Serial::IPacket &&start_packet,
                  Serial::IPacketHandler *resp_handler, int timeout = 10000);

    void dataReceived(const QByteArray &data);
    void dataSent(const QByteArray &data);
    void error(const QString &err);

public slots:
    void process();

signals:
    void end_of_eventloop();
    void finished();

private slots:
    void async_reader();

private:
    enum class STATE {
        NOT_STARTED,
        HOST_TO_DEVICE,
        DEVICE_TO_HOST,
        RVI_ERROR,
        CLOSED
    };

    std::vector<Serial::IPacket*> *input_data_;
    Serial::IPacket &&start_packet_;
    Serial::IPacketHandler *resp_hdl_;
    Serial::DIRECTION direction_;
    STATE state_;

    std::vector<Serial::IPacket*> data_to_send_;
    std::vector<Serial::IPacket*>::iterator d_iter_;

    std::unique_ptr<QTimer> timer_;

    std::map<Serial::PACKET, std::unique_ptr<SignalPacket>> signalMap_;
    std::vector<std::unique_ptr<ErrorPacket>> errorPackets_;

    void init();
    void watchdog();
    bool openPort();
    void closePort();
    void prepareDataToSend();
    void writePrepared();
    void run();
    void dataReceivedToDevice(const QByteArray &data);
    void dataReceivedToHost(const QByteArray &data);
};

#endif // SERIALSESSION_H
