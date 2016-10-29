#include "datatransfer.h"
#include "ui_datatransfer.h"
#include "serialportbrowser.h"
#include "serial/serialsession.h"
#include "serial/startpacket.h"
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
    pm = new ProductsManager();

    ui->tabWidget->addTab(spb.get(), "Serial Config");
    ui->tabWidget->addTab(gs.get(), "Global Settings");
    ui->tabWidget->setCurrentWidget(spb.get());

    pm->insert(new Product("test", "123456", 1.234, 18));

    ui->listView->setModel(pm);

    QObject::connect(spb.get(), &SerialPortBrowser::setupPort, this, &DataTransfer::setupPort);

    QObject::connect(&Logger::instance(), &Logger::logSig, ui->logList, [&](const QString &msg){
        ui->logList->insertItem(0, msg);
    });
}

DataTransfer::~DataTransfer()
{
    delete ui;
}

void DataTransfer::on_getAllProductsButton_clicked()
{
    Logger::instance().log(LogLevel::INFO, "Weszliśmy do GetAllProducts :-)");

    if(serialSession == nullptr) {
        serialSession.reset(new SerialSession(this->port_, StartPacket('I', '0'), pm));
        QObject::connect(serialSession.get(), &SerialSession::finished, [&]() {
            serialSession.reset();
        });
        //QObject::connect(serialSession, SIGNAL(finished()), this, SLOT(abc()));
        serialSession->process();
    }
}

void DataTransfer::abc()
{
    Logger::instance().log(LogLevel::INFO, "End of thread");
}

void DataTransfer::setupPort(QSerialPort *port)
{
    port_ = port;
    Logger::instance().log(LogLevel::INFO, QString("%1 port is chosen").arg(port_->portName()));
}

void DataTransfer::on_getNewProductsButton_clicked()
{
    pm->clear();
    pm->appendRow(new Product("abc","123",1.3, 1.2));
    pm->appendRow(new Product("abc","123",1.3, 1.2));
    pm->appendRow(new Product("abc","123",1.3, 1.2));
    pm->appendRow(new Product("abc","123",1.3, 1.2));
}
