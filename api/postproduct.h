#ifndef POSTPRODUCT_H
#define POSTPRODUCT_H

#include "api/irequester.h"
#include "data/product.h"

class PostProduct : public IRequester
{
public:
    PostProduct(Api::HTTP_ACTION action, const Product &product);
    virtual ~PostProduct() {}

    virtual void prepareData();

private:
    const Product *product;
};

#endif // POSTPRODUCT_H
