#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QObject>

class SerialController : public QObject
{
    Q_OBJECT
public:
    explicit SerialController(QObject *parent = 0);

signals:

public slots:
};

#endif // SERIALCONTROLLER_H