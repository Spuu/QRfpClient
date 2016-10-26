#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <QStandardItem>

class Product : public QStandardItem
{   
public:
    Product();
    Product(std::string name, std::string ean, double price, double quantity);
    Product(const Product&) = default;
    virtual ~Product();

private:
    std::string name;
    std::string ean;
    double price;
    double quantity;

    void init();
};
Q_DECLARE_METATYPE(Product)

#endif // PRODUCT_H
