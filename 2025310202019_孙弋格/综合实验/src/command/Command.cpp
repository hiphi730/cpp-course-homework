#include "command/Command.hpp"

namespace adas {
namespace {
ActionType StepFor(const PoseHandler& poseHandler) noexcept
{
    return poseHandler.IsReverse() ? ActionType::BackwardOneStep : ActionType::ForwardOneStep;
}
ActionGroup BuildTurn(const PoseHandler& poseHandler, bool left)
{
    ActionGroup group;
    const auto step = StepFor(poseHandler);
    // F 的额外移动发生在转向前；Bus 本身也需要先移动一格。
    if (poseHandler.IsFast()) { group.PushAction(step); }
    if (poseHandler.Type() == VehicleType::Bus) { group.PushAction(step); }
    const bool turnLeft = left != poseHandler.IsReverse();
    group.PushAction(turnLeft ? ActionType::TurnLeft : ActionType::TurnRight);
    if (poseHandler.Type() == VehicleType::Sport) { group.PushAction(step); }
    return group;
}
}
ActionGroup MoveCommand::operator()(const PoseHandler& poseHandler) const
{
    ActionGroup group;
    const int distance = (poseHandler.Type() == VehicleType::Sport ? 2 : 1)
                       * (poseHandler.IsFast() ? 2 : 1);
    for (int i = 0; i < distance; ++i) { group.PushAction(StepFor(poseHandler)); }
    return group;
}
ActionGroup TurnLeftCommand::operator()(const PoseHandler& poseHandler) const
{
    return BuildTurn(poseHandler, true);
}
ActionGroup TurnRightCommand::operator()(const PoseHandler& poseHandler) const
{
    return BuildTurn(poseHandler, false);
}
ActionGroup TurnRoundCommand::operator()(const PoseHandler& poseHandler) const
{
    ActionGroup group;
    // 需求4优先：TR使用真实左转和前进，不受B与车辆M/L/R规则影响。
    if (poseHandler.IsFast()) { group.PushAction(ActionType::ForwardOneStep); }
    group.PushAction(ActionType::TurnLeft);
    group.PushAction(ActionType::ForwardOneStep);
    group.PushAction(ActionType::TurnLeft);
    return group;
}
} // namespace adas
