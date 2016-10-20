#include "command.h"

#include <QNetworkReply>
#include <QDebug>
#include "irequester.h"
#include "iresponder.h"
#include "debugresponder.h"

Command::Command(IRequester *req_, IResponder *res_) :
    req(req_),
    res(res_)
{
    QObject::connect(&qnam, SIGNAL(finished(QNetworkReply*)), this->res, SLOT(handleResponse(QNetworkReply*)));
    QObject::connect(this->res, &IResponder::done, this, &Command::done);
}

void Command::execute()
{
    switch(req->getAction()) {
    case Api::GET:
        qnam.get(req->request());
        break;

    case Api::POST:
        qnam.post(req->request(), req->data());
        break;

    case Api::PUT:
        qnam.put(req->request(), req->data());
        break;

    case Api::DELETE:
        qnam.deleteResource(req->request());
        break;
    }
}
