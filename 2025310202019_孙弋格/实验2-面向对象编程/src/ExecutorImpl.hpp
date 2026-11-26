#pragma once
#include "Executor.hpp"

namespace adas {
class ExecutorImpl final : public Executor {
public:
    explicit ExecutorImpl(const Pose& initial) noexcept : pose(initial) {}
    void Execute(const std::string& commands) noexcept override;
    Pose Query() const noexcept override { return pose; }
    void Move() noexcept;
    void TurnLeft() noexcept { Turn(-1); }
    void TurnRight() noexcept { Turn(1); }
    void Fast() noexcept { fast = !fast; }
    bool IsFast() const noexcept { return fast; }
private:
    void Turn(int offset) noexcept;
    Pose pose;
    bool fast{false};
};
} // namespace adas
