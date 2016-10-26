#ifndef PRODUCTSMANAGER_H
#define PRODUCTSMANAGER_H

#include <QStandardItemModel>
#include "product.h"

class ProductsManager : public QStandardItemModel
{
    Q_OBJECT
public:
    ProductsManager();
    virtual ~ProductsManager() {}

    void insert(Product *prod);
};

#endif // PRODUCTSMANAGER_H
