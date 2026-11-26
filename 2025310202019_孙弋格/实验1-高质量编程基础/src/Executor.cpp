#include "Executor.hpp"
#include <new>

namespace adas {
namespace {
class ExecutorImpl final : public Executor {
public:
    explicit ExecutorImpl(const Pose& initial) noexcept : pose(initial) {}
    Pose Query() const noexcept override { return pose; }
    void Execute(const std::string& commands) noexcept override
    {
        for (const char command : commands) {
            switch (command) {
                case 'M': Move(); break;
                case 'L': Turn(-1); break;
                case 'R': Turn(1); break;
                default: break;
            }
        }
    }
private:
    void Move() noexcept
    {
        switch (pose.heading) {
            case 'N': ++pose.y; break;
            case 'E': ++pose.x; break;
            case 'S': --pose.y; break;
            case 'W': --pose.x; break;
            default: break;
        }
    }
    void Turn(int offset) noexcept
    {
        constexpr char headings[] = {'N', 'E', 'S', 'W'};
        for (int index = 0; index < 4; ++index) {
            if (headings[index] == pose.heading) {
                pose.heading = headings[(index + offset + 4) % 4];
                return;
            }
        }
    }
    Pose pose;
};
} // namespace
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
} // namespace adas
