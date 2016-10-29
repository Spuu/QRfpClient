#include "productsmanager.h"

ProductsManager::ProductsManager()
{

}

void ProductsManager::insert(Product *prod)
{
    this->appendRow(prod);
}

char ProductsManager::handleData(const QByteArray&)
{
    return Serial::ACK;
}
