#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QGridLayout;
class SerialPortBrowser;
class ManualSerialController;

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
    SerialPortBrowser *spb;
    ManualSerialController *msc;
};

#endif // MAINWIDGET_H
