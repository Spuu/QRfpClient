#ifndef PRODUCTSMANAGER_H
#define PRODUCTSMANAGER_H

#include <QStandardItemModel>
#include "product.h"
#include "serial/serial.h"

class ProductsManager : public QStandardItemModel, public Serial::IPacketHandler
{
    Q_OBJECT
public:
    ProductsManager();
    virtual ~ProductsManager() {}

    char handleData(const QByteArray&);
    void insert(Product *prod);
};

#endif // PRODUCTSMANAGER_H
