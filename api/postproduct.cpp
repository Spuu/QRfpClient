#include "postproduct.h"
#include "settings.h"

PostProduct::PostProduct(Api::HTTP_ACTION action, const Product &product) :
    IRequester(action),
    product(&product)
{
    QUrl url(Settings::URL_KEY);
    url.setPath("/posts");
    request_.setUrl(url);
}

void PostProduct::prepareData()
{

}
