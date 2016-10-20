#ifndef IRESPONDER_H
#define IRESPONDER_H

#include <QObject>

class QNetworkReply;

class IResponder : public QObject {
    Q_OBJECT

public:
    IResponder() {}
    virtual ~IResponder() {}

public slots:
    virtual void handleResponse(QNetworkReply *) = 0;

signals:
    void done();
};

#endif // IRESPONDER_H
