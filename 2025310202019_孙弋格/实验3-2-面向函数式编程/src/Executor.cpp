#include "Executor.hpp"
#include "Command.hpp"
#include <new>
#include <unordered_map>

namespace adas {
namespace {
const std::unordered_map<char, Command>& GetCommands()
{
    // std::function 按值保存无状态函数对象，生命周期不依赖局部变量。
    static const std::unordered_map<char, Command> table{
        {'M', MoveCommand{}}, {'L', TurnLeftCommand{}}, {'R', TurnRightCommand{}},
        {'F', FastCommand{}}, {'B', ReverseCommand{}}
    };
    return table;
}
class ExecutorImpl final : public Executor {
public:
    explicit ExecutorImpl(const Pose& initial) noexcept : poseHandler(initial) {}
    Pose Query() const noexcept override { return poseHandler.Query(); }
    void Execute(const std::string& commands) noexcept override
    {
        const auto& table = GetCommands();
        for (const char code : commands) {
            const auto it = table.find(code);
            if (it != table.end()) { it->second(poseHandler); }
        }
    }
private:
    PoseHandler poseHandler;
};
} // namespace
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
} // namespace adas
