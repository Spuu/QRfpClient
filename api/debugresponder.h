#ifndef DEBUGRESPONDER_H
#define DEBUGRESPONDER_H

#include "api/iresponder.h"

class DebugResponder : public IResponder
{
    Q_OBJECT
public:
    DebugResponder();
    virtual ~DebugResponder() {}

public slots:
    void handleResponse(QNetworkReply *);
};

#endif // DEBUGRESPONDER_H
