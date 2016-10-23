#ifndef SERIALPORTBROWSER_H
#define SERIALPORTBROWSER_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class SerialPortBrowser;
}

class QSerialPortInfo;

class SerialPortBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortBrowser(QWidget *parent = 0);
    ~SerialPortBrowser();

private slots:
    void on_portsBox_currentIndexChanged(const QString &arg1);
    void on_refreshButton_clicked();
    void on_setupButton_clicked();

signals:
    void setupPort(QSerialPort *port);

private:
    Ui::SerialPortBrowser *ui;
    QList<QSerialPortInfo> serialPortInfos;
    void populatePortBox(const QList<QSerialPortInfo> ports);
    QSerialPort port;
};

#endif // SERIALPORTBROWSER_H
