#include "serialportbrowser.h"
#include "ui_serialportbrowser.h"

SerialPortBrowser::SerialPortBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPortBrowser)
{
    ui->setupUi(this);
}

SerialPortBrowser::~SerialPortBrowser()
{
    delete ui;
}
