#include "postproduct.h"

PostProduct::PostProduct(Api::HTTP_ACTION action, const QString &api_src, const Product &product) :
    IRequester(action),
    product(&product)
{
    QUrl url(api_src);
    url.setPath("/posts");
    request_.setUrl(url);
}

void PostProduct::prepareData()
{

}
