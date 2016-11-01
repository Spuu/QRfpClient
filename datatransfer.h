#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <QWidget>
#include <memory>

#include "serial/serialportparams.h"

namespace Ui {
class DataTransfer;
}

class SerialSession;
class QSerialPort;
class SerialPortBrowser;
class GlobalSettings;
class ProductsManager;
class ManualSerialController;

/**
 * Widget gathering all Serial and API behaviour
 */
class DataTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit DataTransfer(QWidget *parent = 0);
    ~DataTransfer();

private slots:
    void on_getAllProductsButton_clicked();
    void setupPort(SerialPortParams params);
    void abc();

    void on_getNewProductsButton_clicked();

private:
    Ui::DataTransfer *ui;

    std::unique_ptr<SerialPortBrowser> spb;
    std::unique_ptr<GlobalSettings> gs;
    std::unique_ptr<ManualSerialController> msc;
    std::unique_ptr<ProductsManager> pm;
    std::unique_ptr<SerialSession> serialSession;

    SerialPortParams spp;
};

#endif // DATATRANSFER_H
