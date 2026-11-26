#pragma once
#include "PoseHandler.hpp"
#include <functional>

namespace adas {
using Command = std::function<void(PoseHandler&)>;
class MoveCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept;
};
class TurnLeftCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept;
};
class TurnRightCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept;
};
class FastCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept;
};
class ReverseCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept;
};
} // namespace adas
