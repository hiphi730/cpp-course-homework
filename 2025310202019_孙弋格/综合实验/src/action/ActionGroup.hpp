#pragma once
#include <initializer_list>
#include <vector>

namespace adas {
class PoseHandler;
enum class ActionType { ForwardOneStep, BackwardOneStep, TurnLeft, TurnRight, Fast, Reverse };
class ActionGroup final {
public:
    ActionGroup() = default;
    ActionGroup(std::initializer_list<ActionType> initial) : actions(initial) {}
    void PushAction(ActionType action) { actions.push_back(action); }
    void DoOperate(PoseHandler& poseHandler) const noexcept;
private:
    std::vector<ActionType> actions;
};
} // namespace adas
