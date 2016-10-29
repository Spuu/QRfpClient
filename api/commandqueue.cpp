#include "commandqueue.h"

CommandQueue::CommandQueue()
{

}

void CommandQueue::execute()
{
    commands_iter = commands.begin();
    executeNext();
}

void CommandQueue::executeNext()
{
    if(commands_iter != commands.end()) {
        (*commands_iter)->execute();
        ++commands_iter;
    }
}

void CommandQueue::add(CommandPtr cmd)
{
    commands.push_back(std::move(cmd));
    QObject::connect(cmd.get(), SIGNAL(done()), this, SLOT(executeNext()));
}
