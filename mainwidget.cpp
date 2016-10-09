#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QGridLayout>
#include "manualserialcontroller.h"
#include "serialportbrowser.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    layout = new QGridLayout(this);
    spb = new SerialPortBrowser(this);
    msc = new ManualSerialController(nullptr, this);

    QObject::connect(spb, &SerialPortBrowser::setupPort, msc, &ManualSerialController::setPort);

    layout->addWidget(spb, 0, 0);
    layout->addWidget(msc, 0, 2);
    this->setLayout(layout);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete spb;
    delete msc;
}
