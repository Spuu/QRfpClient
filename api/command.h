#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QNetworkAccessManager>

class IRequester;
class IResponder;

class Command : public QObject
{
    Q_OBJECT
public:
    Command(IRequester *req, IResponder *res);
    virtual ~Command() {}

public slots:
    virtual void execute();

signals:
    void done();

protected:
    IRequester *req;
    IResponder *res;

    QNetworkAccessManager qnam;
};

#endif // COMMAND_H
