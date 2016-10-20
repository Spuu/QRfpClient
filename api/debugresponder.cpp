#include "debugresponder.h"
#include <QDebug>
#include <QNetworkReply>

DebugResponder::DebugResponder()
{

}

void DebugResponder::handleResponse(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
}
