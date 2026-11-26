#include "action/ActionGroup.hpp"
#include "pose/PoseHandler.hpp"
#include <array>
#include <cstddef>

namespace adas {
void ActionGroup::DoOperate(PoseHandler& poseHandler) const noexcept
{
    using Action = void (PoseHandler::*)() noexcept;
    static constexpr std::array<Action, 6> operations{{
        &PoseHandler::Forward, &PoseHandler::Backward, &PoseHandler::TurnLeft,
        &PoseHandler::TurnRight, &PoseHandler::Fast, &PoseHandler::Reverse
    }};
    for (const ActionType action : actions) {
        (poseHandler.*operations[static_cast<std::size_t>(action)])();
    }
}
} // namespace adas
