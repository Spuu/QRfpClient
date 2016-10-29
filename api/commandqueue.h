#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <vector>
#include <memory>
#include "command.h"

typedef std::unique_ptr<Command> CommandPtr;
typedef std::vector<CommandPtr> CommandVec;
typedef CommandVec::iterator CommandVecIter;

class CommandQueue : public ICommand
{
    Q_OBJECT

public:
    CommandQueue();
    virtual ~CommandQueue() {}
    void add(CommandPtr cmd);

public slots:
    void execute();
    void executeNext();

private:
    CommandVec commands;
    CommandVecIter commands_iter;
};

#endif // COMMANDQUEUE_H
