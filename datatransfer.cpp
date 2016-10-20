#include "datatransfer.h"
#include "ui_datatransfer.h"
#include "serialportbrowser.h"

DataTransfer::DataTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataTransfer)
{
    ui->setupUi(this);

    spb = new SerialPortBrowser;

    ui->tabWidget->addTab(spb, "Serial Config");
    ui->tabWidget->setCurrentWidget(spb);
}

DataTransfer::~DataTransfer()
{
    delete ui;
}
