#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <QWidget>

namespace Ui {
class DataTransfer;
}

class SerialPortBrowser;

class DataTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit DataTransfer(QWidget *parent = 0);
    ~DataTransfer();

private:
    Ui::DataTransfer *ui;

    SerialPortBrowser *spb;
};

#endif // DATATRANSFER_H
