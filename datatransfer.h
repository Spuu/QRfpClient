#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <QWidget>
#include <memory>

namespace Ui {
class DataTransfer;
}

class SerialSession;
class QSerialPort;
class SerialPortBrowser;
class GlobalSettings;

class DataTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit DataTransfer(QWidget *parent = 0);
    ~DataTransfer();

private slots:
    void on_getAllProductsButton_clicked();
    void setupPort(QSerialPort *port);

private:
    Ui::DataTransfer *ui;
    std::unique_ptr<SerialPortBrowser> spb;
    std::unique_ptr<GlobalSettings> gs;
    QSerialPort *port_;

    SerialSession *serialSession;
};

#endif // DATATRANSFER_H
