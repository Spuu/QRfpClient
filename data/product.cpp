#include "product.h"
#include "logger.h"

Product::Product()
{
    Logger::instance().log(LogLevel::DEBUG, QString("Product %1 created.").arg(name.c_str()));
    init();
}

Product::Product(std::string name, std::string ean,
                 double price, double quantity) :
    name(name),
    ean(ean),
    price(price),
    quantity(quantity),
    QStandardItem(name.c_str())
{
    Logger::instance().log(LogLevel::DEBUG, QString("Product %1 created.").arg(name.c_str()));
    init();
}

Product::~Product()
{
    Logger::instance().log(LogLevel::DEBUG, QString("Product %1 destroyed.").arg(name.c_str()));
}

void Product::init()
{
    setEditable(false);
    setCheckable(true);
    setCheckState(Qt::Checked);
}
