#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QGridLayout>
#include <QStackedWidget>
#include <memory>

#include "datatransfer.h"

#include "manualserialcontroller.h"
#include "serialportbrowser.h"
#include "api/getallproducts.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    layout = new QGridLayout;
    stack = new QStackedWidget;

    layout->addWidget(stack,0,0);
    dataTransfer = new DataTransfer;

    stack->addWidget(dataTransfer);

    this->setLayout(layout);
    /*spb = new SerialPortBrowser(this);
    msc = new ManualSerialController(nullptr, this);

    QObject::connect(spb, &SerialPortBrowser::setupPort, msc, &ManualSerialController::setPort);

    layout->addWidget(spb, 0, 0);
    layout->addWidget(msc, 0, 2);
    this->setLayout(layout);

    get_all_products = std::make_unique<GetAllProducts>(Api::GET, "http://jsonplaceholder.typicode.com");
    CommandPtr get_products = std::make_unique<Command>(get_all_products.get(), &this->debugResponder);
    commandQueue.add(std::move(get_products));
    commandQueue.execute();*/
}

MainWidget::~MainWidget()
{
    delete ui;
    delete dataTransfer;
    delete stack;
    delete layout;
    //delete spb;
    //delete msc;
}
