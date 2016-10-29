#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QObject>

class ICommand : public QObject
{
    Q_OBJECT

public slots:
    virtual void execute() = 0;
};

#endif // ICOMMAND_H
