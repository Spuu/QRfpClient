#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{   
public:
    Product(std::string name, std::string ean, double price, double quantity);
    virtual ~Product() {}

private:
    std::string name;
    std::string ean;
    double price;
    double quantity;
};

#endif // PRODUCT_H
