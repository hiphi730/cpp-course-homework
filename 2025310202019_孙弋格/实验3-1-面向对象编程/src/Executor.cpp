#include "Executor.hpp"
#include "Command.hpp"
#include "PoseHandler.hpp"
#include <memory>
#include <new>
#include <unordered_map>

namespace adas {
namespace {
using CommandTable = std::unordered_map<char, std::unique_ptr<ICommand>>;
const CommandTable& GetCommands()
{
    // unique_ptr 独占命令对象；共享的命令不保存执行器状态。
    static const CommandTable table = [] {
        CommandTable commands;
        commands.emplace('M', std::make_unique<MoveCommand>());
        commands.emplace('L', std::make_unique<TurnLeftCommand>());
        commands.emplace('R', std::make_unique<TurnRightCommand>());
        commands.emplace('F', std::make_unique<FastCommand>());
        return commands;
    }();
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
            if (it != table.end()) { it->second->DoOperate(poseHandler); }
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
