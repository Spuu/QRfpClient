#include "productsmanager.h"
#include <QDebug>
ProductsManager::ProductsManager()
{

}

void ProductsManager::insert(Product *prod)
{
    this->appendRow(prod);
}

char ProductsManager::handleData(const QByteArray& data)
{
    qDebug() << data.toHex();
    return Serial::ACK;
}
