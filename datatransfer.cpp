#include "datatransfer.h"
#include "ui_datatransfer.h"
#include "serialportbrowser.h"
#include "serial/serialsession.h"
#include "serial/startpacket.h"
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

    ui->tabWidget->addTab(spb.get(), "Serial Config");
    ui->tabWidget->addTab(gs.get(), "Global Settings");
    ui->tabWidget->setCurrentWidget(spb.get());

    QObject::connect(spb.get(), &SerialPortBrowser::setupPort, this, &DataTransfer::setupPort);

    QObject::connect(&Logger::instance(), &Logger::logSig, ui->logList, [=](const QString &msg){
        ui->logList->addItem(msg);
    });
}

DataTransfer::~DataTransfer()
{
    delete ui;
    if(serialSession) delete serialSession;
}

void DataTransfer::on_getAllProductsButton_clicked()
{
    Logger::instance().log(LogLevel::INFO, "Weszliśmy do GetAllProducts :-)");

    serialSession = new SerialSession(Serial::HOST, StartPacket('I', '0'), NULL);
    serialSession->setPort(this->port_);
    serialSession->start();
}

void DataTransfer::setupPort(QSerialPort *port)
{
    port_ = port;
    Logger::instance().log(LogLevel::INFO, QString("%1 port is chosen").arg(port_->portName()));
}
