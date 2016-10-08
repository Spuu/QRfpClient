#ifndef SERIALPORTBROWSER_H
#define SERIALPORTBROWSER_H

#include <QWidget>

namespace Ui {
class SerialPortBrowser;
}

class SerialPortBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortBrowser(QWidget *parent = 0);
    ~SerialPortBrowser();

private:
    Ui::SerialPortBrowser *ui;
};

#endif // SERIALPORTBROWSER_H
