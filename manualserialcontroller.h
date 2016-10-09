#ifndef MANUALSERIALCONTROLLER_H
#define MANUALSERIALCONTROLLER_H

#include <QWidget>
#include "serial/serialcontroller.h"

class QSerialPort;

namespace Ui {
class ManualSerialController;
}

class ManualSerialController : public SerialController
{
    Q_OBJECT

public:
    explicit ManualSerialController(QSerialPort *port = nullptr, QWidget *parent = 0);
    ~ManualSerialController();

signals:
    void dataChange();

public slots:
    void setPort(QSerialPort *port);

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

private:
    Ui::ManualSerialController *ui;

    QByteArray data;
};

#endif // MANUALSERIALCONTROLLER_H
