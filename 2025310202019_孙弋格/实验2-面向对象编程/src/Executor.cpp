#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <new>

namespace adas {
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const char code : commands) {
        const ICommand* command = FindCommand(code);
        if (command != nullptr) { command->DoOperate(*this); }
    }
}
void ExecutorImpl::Move() noexcept
{
    switch (pose.heading) {
        case 'N': ++pose.y; break;
        case 'E': ++pose.x; break;
        case 'S': --pose.y; break;
        case 'W': --pose.x; break;
        default: break;
    }
}
void ExecutorImpl::Turn(int offset) noexcept
{
    constexpr char headings[] = {'N', 'E', 'S', 'W'};
    for (int index = 0; index < 4; ++index) {
        if (headings[index] == pose.heading) {
            pose.heading = headings[(index + offset + 4) % 4];
            return;
        }
    }
}
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
} // namespace adas
