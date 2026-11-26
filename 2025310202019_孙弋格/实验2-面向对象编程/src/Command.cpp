#include "Command.hpp"
#include "ExecutorImpl.hpp"

namespace adas {
void MoveCommand::DoOperate(ExecutorImpl& executor) const noexcept
{
    if (executor.IsFast()) { executor.Move(); }
    executor.Move();
}
void TurnLeftCommand::DoOperate(ExecutorImpl& executor) const noexcept
{
    if (executor.IsFast()) { executor.Move(); }
    executor.TurnLeft();
}
void TurnRightCommand::DoOperate(ExecutorImpl& executor) const noexcept
{
    if (executor.IsFast()) { executor.Move(); }
    executor.TurnRight();
}
void FastCommand::DoOperate(ExecutorImpl& executor) const noexcept { executor.Fast(); }
const ICommand* FindCommand(char command) noexcept
{
    static const MoveCommand move;
    static const TurnLeftCommand left;
    static const TurnRightCommand right;
    static const FastCommand fast;
    switch (command) {
        case 'M': return &move;
        case 'L': return &left;
        case 'R': return &right;
        case 'F': return &fast;
        default: return nullptr;
    }
}
} // namespace adas
