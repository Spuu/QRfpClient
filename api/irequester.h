#ifndef IREQUESTER_H
#define IREQUESTER_H

#include <QNetworkRequest>
#include <memory>

namespace Api {
enum HTTP_ACTION {
    GET,
    POST,
    PUT,
    DELETE
};
}

class IRequester {

public:
    IRequester(Api::HTTP_ACTION action);
    virtual ~IRequester() {}

    virtual const QNetworkRequest& request();
    virtual const QByteArray& data();
    virtual Api::HTTP_ACTION getAction();

protected:
    virtual void prepareData() = 0;
    QNetworkRequest request_;
    QByteArray data_;
    Api::HTTP_ACTION action;
};

#endif // IREQUESTER_H
