#include "manualserialcontroller.h"
#include "ui_manualserialcontroller.h"

ManualSerialController::ManualSerialController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualSerialController)
{
    ui->setupUi(this);
}

ManualSerialController::~ManualSerialController()
{
    delete ui;
}
