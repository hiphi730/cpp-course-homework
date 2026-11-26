#include "Command.hpp"

namespace adas {
void MoveCommand::operator()(PoseHandler& poseHandler) const noexcept
{
    if (poseHandler.IsFast()) { poseHandler.Move(); }
    poseHandler.Move();
}
void TurnLeftCommand::operator()(PoseHandler& poseHandler) const noexcept
{
    if (poseHandler.IsFast()) { poseHandler.Move(); }
    poseHandler.TurnLeft();
}
void TurnRightCommand::operator()(PoseHandler& poseHandler) const noexcept
{
    if (poseHandler.IsFast()) { poseHandler.Move(); }
    poseHandler.TurnRight();
}
void FastCommand::operator()(PoseHandler& poseHandler) const noexcept { poseHandler.Fast(); }
void ReverseCommand::operator()(PoseHandler& poseHandler) const noexcept { poseHandler.Reverse(); }
} // namespace adas
