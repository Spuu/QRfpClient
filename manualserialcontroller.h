#ifndef MANUALSERIALCONTROLLER_H
#define MANUALSERIALCONTROLLER_H

#include <QWidget>
#include "serial/serialcontroller.h"
#include "serial/serialport.h"

class QSerialPort;

namespace Ui {
class ManualSerialController;
}

class ManualSerialController : public QWidget, public ISerialCtrl, public SerialController
{
    Q_OBJECT

public:
    explicit ManualSerialController(QWidget *parent = 0);
    ~ManualSerialController();

signals:
    void dataChange();
    void dataReceivedSig(const QByteArray &data);
    void dataSentSig(const QByteArray &data);
    void errorSig(const QString &err);

public slots:
    void setPort(SerialPortParams params);

private slots:
    void on_enqButton_clicked();
    void on_ackButton_clicked();
    void on_nakButton_clicked();
    void on_stxButton_clicked();
    void on_eotButton_clicked();
    void on_etxButton_clicked();
    void on_etbButton_clicked();
    void on_wackButton_clicked();
    void on_rviButton_clicked();

    void on_addTextButton_clicked();
    void on_openPortButton_clicked();
    void on_closePortButton_clicked();
    void on_writeButton_clicked();
    void on_readButton_clicked();
    void on_clearButton_clicked();

    void handle_error(const QString &str);
    void onDataChanged();
    void onDataRead(const QByteArray &bytes);

    void setGui(bool isConnected);

    void on_byteButton_clicked();

private:
    Ui::ManualSerialController *ui;
    QByteArray data;

    std::unique_ptr<SerialPort> port_;

    void dataReceived(const QByteArray &data);
    void dataSent(const QByteArray &data);
    void error(const QString &err);
};

#endif // MANUALSERIALCONTROLLER_H
