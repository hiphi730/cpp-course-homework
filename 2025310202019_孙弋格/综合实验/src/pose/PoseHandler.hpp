#pragma once
#include "Executor.hpp"
#include <cstddef>

namespace adas {
class PoseHandler final {
public:
    explicit PoseHandler(const Pose& initial, VehicleType type) noexcept;
    Pose Query() const noexcept;
    void Forward() noexcept;
    void Backward() noexcept;
    void TurnLeft() noexcept { direction = (direction + 3) % 4; }
    void TurnRight() noexcept { direction = (direction + 1) % 4; }
    void Fast() noexcept { fast = !fast; }
    void Reverse() noexcept { reverse = !reverse; }
    bool IsFast() const noexcept { return fast; }
    bool IsReverse() const noexcept { return reverse; }
    VehicleType Type() const noexcept { return type; }
private:
    std::int32_t x;
    std::int32_t y;
    std::size_t direction{0};
    VehicleType type;
    bool fast{false};
    bool reverse{false};
};
} // namespace adas
