#ifndef GETALLPRODUCTS_H
#define GETALLPRODUCTS_H

#include "api/irequester.h"

class GetAllProducts : public IRequester
{
    Q_OBJECT
public:
    GetAllProducts(Api::HTTP_ACTION action, const QString &api_src);
    virtual ~GetAllProducts() {}
    virtual void prepareData();
};

#endif // GETALLPRODUCTS_H
