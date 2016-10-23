#include "serialportbrowser.h"
#include "ui_serialportbrowser.h"

#include <QSerialPortInfo>

SerialPortBrowser::SerialPortBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPortBrowser),
    serialPortInfos(QSerialPortInfo::availablePorts()),
    port(nullptr)
{
    ui->setupUi(this);

    populatePortBox(serialPortInfos);

    QStringList baudRate;
    baudRate << QString::number(QSerialPort::Baud115200)
             << QString::number(QSerialPort::Baud57600)
             << QString::number(QSerialPort::Baud38400)
             << QString::number(QSerialPort::Baud19200)
             << QString::number(QSerialPort::Baud9600)
             << QString::number(QSerialPort::Baud4800)
             << QString::number(QSerialPort::Baud2400)
             << QString::number(QSerialPort::Baud1200);
    ui->baudRateBox->addItems(baudRate);
    ui->baudRateBox->setCurrentIndex(4);

    QStringList parity;
    parity << QString::number(QSerialPort::NoParity)
           << QString::number(QSerialPort::EvenParity)
           << QString::number(QSerialPort::OddParity)
           << QString::number(QSerialPort::SpaceParity)
           << QString::number(QSerialPort::MarkParity);
    ui->parityBox->addItems(parity);

    QStringList dataBits;
    dataBits << QString::number(QSerialPort::Data8)
             << QString::number(QSerialPort::Data7)
             << QString::number(QSerialPort::Data6)
             << QString::number(QSerialPort::Data5);
    ui->dataBitsBox->addItems(dataBits);

    QStringList flowControl;
    flowControl << QString::number(QSerialPort::NoFlowControl)
                << QString::number(QSerialPort::HardwareControl)
                << QString::number(QSerialPort::SoftwareControl);
    ui->flowControlBox->addItems(flowControl);

    QStringList stopBits;
    stopBits << QString::number(QSerialPort::OneStop)
             << QString::number(QSerialPort::OneAndHalfStop)
             << QString::number(QSerialPort::TwoStop);
    ui->stopBitsBox->addItems(stopBits);
}

SerialPortBrowser::~SerialPortBrowser()
{
    delete ui;
}

void SerialPortBrowser::on_portsBox_currentIndexChanged(const QString &arg1)
{
    QSerialPort port(arg1);
    ui->statusEdit->setText(port.isOpen() ? "Opened" : "Closed");
}

void SerialPortBrowser::on_refreshButton_clicked()
{
    serialPortInfos = QSerialPortInfo::availablePorts();
    populatePortBox(serialPortInfos);
}

void SerialPortBrowser::populatePortBox(const QList<QSerialPortInfo> ports)
{
    ui->portsBox->clear();
    for(const QSerialPortInfo port : ports) {
        ui->portsBox->addItem(port.portName());
    }
}

void SerialPortBrowser::on_setupButton_clicked()
{
    if(!port.isOpen()) {
        port.setPortName(ui->portsBox->currentText());
        port.setBaudRate((QSerialPort::BaudRate) ui->baudRateBox->currentText().toInt());
        port.setDataBits((QSerialPort::DataBits) ui->dataBitsBox->currentText().toInt());
        port.setParity((QSerialPort::Parity) ui->parityBox->currentText().toInt());
        port.setFlowControl((QSerialPort::FlowControl) ui->flowControlBox->currentText().toInt());
        port.setStopBits((QSerialPort::StopBits) ui->stopBitsBox->currentText().toInt());
        emit setupPort(&port);
    }
}
