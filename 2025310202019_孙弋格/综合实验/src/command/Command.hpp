#pragma once
#include "action/ActionGroup.hpp"
#include "pose/PoseHandler.hpp"
#include <functional>

namespace adas {
using Command = std::function<ActionGroup(const PoseHandler&)>;
class MoveCommand final {
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const;
};
class TurnLeftCommand final {
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const;
};
class TurnRightCommand final {
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const;
};
class FastCommand final {
public:
    ActionGroup operator()(const PoseHandler&) const { return {ActionType::Fast}; }
};
class ReverseCommand final {
public:
    ActionGroup operator()(const PoseHandler&) const { return {ActionType::Reverse}; }
};
class TurnRoundCommand final {
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const;
};
} // namespace adas
