#pragma once

#include <cstdint>
#include <string>

namespace adas {
struct Pose {
    std::int32_t x;
    std::int32_t y;
    char heading;
};

class Executor {
public:
    // 返回对象由调用者持有，建议立即交给 std::unique_ptr 管理。
    static Executor* NewExecutor(const Pose& pose = {0, 0, 'N'}) noexcept;
    virtual ~Executor() = default;
    virtual void Execute(const std::string& commands) noexcept = 0;
    virtual Pose Query() const noexcept = 0;
};
} // namespace adas
