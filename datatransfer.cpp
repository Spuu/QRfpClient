#include "datatransfer.h"
#include "ui_datatransfer.h"
#include "serialportbrowser.h"
#include "serial/serialsession.h"
#include "serial/startpacket.h"
#include "manualserialcontroller.h"
#include "data/productsmanager.h"
#include "globalsettings.h"
#include "settings.h"
#include "logger.h"

#include <QSettings>
#include <QDebug>

DataTransfer::DataTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataTransfer)
{
    ui->setupUi(this);

    spb = std::make_unique<SerialPortBrowser>();
    gs = std::make_unique<GlobalSettings>();
    pm = std::make_unique<ProductsManager>();

    ui->tabWidget->addTab(spb.get(), "Serial Config");
    ui->tabWidget->addTab(gs.get(), "Global Settings");
    ui->tabWidget->setCurrentWidget(spb.get());

    pm->insert(new Product("test", "123456", 1.234, 18));

    ui->listView->setModel(pm.get());

    QObject::connect(spb.get(), &SerialPortBrowser::setupPort, this, &DataTransfer::setupPort);

    QObject::connect(&Logger::instance(), &Logger::logSig, ui->logList, [&](const QString &msg){
            ui->logList->insertItem(0, msg);
    });

    // setup manual serial controller
    msc = std::make_unique<ManualSerialController>(this);
    ui->tabWidget->addTab(msc.get(), "Manual Controller");
    QObject::connect(spb.get(), &SerialPortBrowser::setupPort, msc.get(), &ManualSerialController::setPort);
}

DataTransfer::~DataTransfer()
{
    Logger::instance().disconnect();
    delete ui;
}

void DataTransfer::on_getAllProductsButton_clicked()
{
    Logger::instance().log(LogLevel::INFO, "Weszliśmy do GetAllProducts :-)");

    QThread* thread = new QThread;
    SerialSession* worker = new SerialSession(this->spp, StartPacket("I#00", '0'), pm.get(), 60000);
    worker->moveToThread(thread);

    connect(thread, SIGNAL (started()), worker, SLOT (process()));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    connect(worker, SIGNAL(finished()), this, SLOT(abc()));
    thread->start();
}

void DataTransfer::abc()
{
    Logger::instance().log(LogLevel::INFO, "End of thread");
}

void DataTransfer::setupPort(SerialPortParams params)
{
    spp = params;
    Logger::instance().log(LogLevel::INFO, QString("%1 port is chosen").arg(spp.getPortName()));
}

void DataTransfer::on_getNewProductsButton_clicked()
{
    pm->clear();
    pm->appendRow(new Product("abc","123",1.3, 1.2));
    pm->appendRow(new Product("abc","123",1.3, 1.2));
    pm->appendRow(new Product("abc","123",1.3, 1.2));
    pm->appendRow(new Product("abc","123",1.3, 1.2));
}
