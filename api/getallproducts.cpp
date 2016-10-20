#include "getallproducts.h"

GetAllProducts::GetAllProducts(Api::HTTP_ACTION action, const QString &api_src) :
    IRequester(action)
{
    QUrl url(api_src);
    url.setPath("/posts");
    request_.setUrl(url);
}

void GetAllProducts::prepareData()
{}
