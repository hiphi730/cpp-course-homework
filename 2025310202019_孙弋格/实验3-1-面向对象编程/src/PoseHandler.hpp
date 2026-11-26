#pragma once
#include "Executor.hpp"
#include <cstddef>

namespace adas {
class PoseHandler final {
public:
    explicit PoseHandler(const Pose& initial) noexcept;
    Pose Query() const noexcept;
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept { fast = !fast; }
    bool IsFast() const noexcept { return fast; }

private:
    std::int32_t x;
    std::int32_t y;
    std::size_t direction{0};
    bool fast{false};

};
} // namespace adas
