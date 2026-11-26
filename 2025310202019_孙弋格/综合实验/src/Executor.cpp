#include "Executor.hpp"
#include "command/CommandFactory.hpp"
#include "common/Singleton.hpp"
#include "pose/PoseHandler.hpp"
#include <new>

namespace adas {
namespace {
class ExecutorImpl final : public Executor {
public:
    ExecutorImpl(const Pose& initial, VehicleType type) noexcept : poseHandler(initial, type) {}
    Pose Query() const noexcept override { return poseHandler.Query(); }
    void Execute(const std::string& commands) noexcept override
    {
        const auto parsed = Singleton<CommandFactory>::Instance().GetCommands(commands);
        for (const auto& command : parsed) {
            // 必须逐条读取即时状态，不能在F/B执行前预计算后续动作。
            command(poseHandler).DoOperate(poseHandler);
        }
    }
private:
    PoseHandler poseHandler;
};
} // namespace
Executor* Executor::NewExecutor(const Pose& pose, VehicleType type) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose, type);
}
} // namespace adas
