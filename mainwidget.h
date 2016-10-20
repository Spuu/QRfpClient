#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QGridLayout;
class QStackedWidget;
class DataTransfer;
class SerialPortBrowser;
class ManualSerialController;
class GetAllProducts;

#include "api/commandqueue.h"
#include "api/debugresponder.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    QGridLayout *layout;
    QStackedWidget *stack;
    DataTransfer *dataTransfer;
    /*SerialPortBrowser *spb;
    ManualSerialController *msc;

    CommandQueue commandQueue;
    DebugResponder debugResponder;

    std::unique_ptr<GetAllProducts> get_all_products;*/
};

#endif // MAINWIDGET_H
