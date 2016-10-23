#include "getallproducts.h"
#include "settings.h"
#include <QSettings>

GetAllProducts::GetAllProducts(Api::HTTP_ACTION action) :
    IRequester(action)
{
    QSettings cfg;
    QUrl url(cfg.value(Settings::URL_KEY).toString());
    url.setPath("posts");
    request_.setUrl(url);
}

void GetAllProducts::prepareData()
{}
