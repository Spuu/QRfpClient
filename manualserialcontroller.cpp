#include <QSerialPort>

#include "manualserialcontroller.h"
#include "ui_manualserialcontroller.h"

#include "serial/serial.h"

ManualSerialController::ManualSerialController(QWidget *parent) :
    ui(new Ui::ManualSerialController),
    SerialController(this, 10000)
{
    ui->setupUi(this);
    this->setGui(false);

    QObject::connect(this, &ManualSerialController::errorSig, this, &ManualSerialController::handle_error);
    QObject::connect(this, &ManualSerialController::dataChange, this, &ManualSerialController::onDataChanged);
    QObject::connect(this, &ManualSerialController::dataReceivedSig, this, &ManualSerialController::onDataRead);
}

ManualSerialController::~ManualSerialController()
{
    delete ui;
}

void ManualSerialController::dataReceived(const QByteArray &data)
{
    emit dataReceivedSig(data);
}

void ManualSerialController::dataSent(const QByteArray &data)
{
    emit dataSentSig(data);
}

void ManualSerialController::error(const QString &err)
{
    emit errorSig(err);
}

void ManualSerialController::setPort(QSerialPort *port)
{
    if(port) {
        this->port_ = port;
        ui->portName->setText(port->portName());
    }
}

void ManualSerialController::setGui(bool isConnected)
{
    ui->openPortButton->setDisabled(isConnected);
    ui->closePortButton->setEnabled(isConnected);
    ui->readButton->setEnabled(isConnected);
    ui->writeButton->setEnabled(isConnected);
}

void ManualSerialController::on_openPortButton_clicked()
{
    if(!port_->isOpen()) {
        if(port_->open(QIODevice::ReadWrite))
            this->setGui(true);
        else
            emit errorSig(QString("COM port not connected."));
    }
}

void ManualSerialController::on_closePortButton_clicked()
{
    if(port_->isOpen()) {
        port_->close();
        this->setGui(false);
    }
}

void ManualSerialController::on_writeButton_clicked()
{
    if(write(data) != Serial::SUCCESS) {
        emit errorSig(QString("Write error."));
    }
}

void ManualSerialController::on_readButton_clicked()
{
    if(read() != Serial::SUCCESS) {
        emit errorSig(QString("Read error"));
    }
}

void ManualSerialController::on_clearButton_clicked()
{
    data.clear();
    emit dataChange();
}

void ManualSerialController::onDataChanged()
{
    ui->textEdit->setText(data);
    ui->byteEdit->setText(data.toHex());
}

void ManualSerialController::onDataRead(const QByteArray &bytes)
{
    data = bytes;
    emit dataChange();
}

void ManualSerialController::handle_error(const QString &str)
{
    data.clear();
    data.append(str);
    emit dataChange();
}

void ManualSerialController::on_enqButton_clicked()
{
    data.append(Serial::ENQ);
    emit dataChange();
}

void ManualSerialController::on_ackButton_clicked()
{
    data.append(Serial::ACK);
    emit dataChange();
}

void ManualSerialController::on_nakButton_clicked()
{
    data.append(Serial::NAK);
    emit dataChange();
}

void ManualSerialController::on_stxButton_clicked()
{
    data.append(Serial::STX);
    emit dataChange();
}

void ManualSerialController::on_eotButton_clicked()
{
    data.append(Serial::EOT);
    emit dataChange();
}

void ManualSerialController::on_etxButton_clicked()
{
    data.append(Serial::ETX);
    emit dataChange();
}

void ManualSerialController::on_etbButton_clicked()
{
    data.append(Serial::ETB);
    emit dataChange();
}

void ManualSerialController::on_wackButton_clicked()
{
    data.append(Serial::WACK);
    emit dataChange();
}

void ManualSerialController::on_rviButton_clicked()
{
    data.append(Serial::RVI);
    emit dataChange();
}

void ManualSerialController::on_addTextButton_clicked()
{
    data.append(ui->lineEdit->text());
    emit dataChange();
}

void ManualSerialController::on_byteButton_clicked()
{
    data.append(ui->byteBox->value());
    emit dataChange();
}
