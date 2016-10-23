#ifndef GETALLPRODUCTS_H
#define GETALLPRODUCTS_H

#include "api/irequester.h"

class GetAllProducts : public IRequester
{
public:
    GetAllProducts(Api::HTTP_ACTION action);
    virtual ~GetAllProducts() {}
    void prepareData();
};

#endif // GETALLPRODUCTS_H
