#include "irequester.h"

IRequester::IRequester(Api::HTTP_ACTION action) : action(action)
{

}

Api::HTTP_ACTION IRequester::getAction()
{
    return action;
}

const QNetworkRequest& IRequester::request()
{
    return request_;
}

const QByteArray& IRequester::data()
{
    return data_;
}
