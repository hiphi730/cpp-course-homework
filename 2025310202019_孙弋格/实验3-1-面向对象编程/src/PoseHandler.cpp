#include "PoseHandler.hpp"
#include <array>

namespace adas {
namespace {
constexpr std::array<char, 4> HEADINGS{{'N', 'E', 'S', 'W'}};
constexpr std::array<std::int32_t, 4> DX{{0, 1, 0, -1}};
constexpr std::array<std::int32_t, 4> DY{{1, 0, -1, 0}};
}
PoseHandler::PoseHandler(const Pose& initial) noexcept : x(initial.x), y(initial.y)
{
    for (std::size_t i = 0; i < HEADINGS.size(); ++i) {
        if (HEADINGS[i] == initial.heading) { direction = i; break; }
    }
}
Pose PoseHandler::Query() const noexcept { return {x, y, HEADINGS[direction]}; }
void PoseHandler::Move() noexcept
{
    const std::int32_t step = 1;
    x += DX[direction] * step;
    y += DY[direction] * step;
}
void PoseHandler::TurnLeft() noexcept { direction = (direction + 3) % 4; }
void PoseHandler::TurnRight() noexcept { direction = (direction + 1) % 4; }
} // namespace adas
