#include "pose/PoseHandler.hpp"
#include <array>

namespace adas {
namespace {
constexpr std::array<char, 4> HEADINGS{{'N', 'E', 'S', 'W'}};
constexpr std::array<std::int32_t, 4> DX{{0, 1, 0, -1}};
constexpr std::array<std::int32_t, 4> DY{{1, 0, -1, 0}};
}
PoseHandler::PoseHandler(const Pose& initial, VehicleType vehicleType) noexcept
    : x(initial.x), y(initial.y), type(vehicleType)
{
    for (std::size_t i = 0; i < HEADINGS.size(); ++i) {
        if (HEADINGS[i] == initial.heading) { direction = i; break; }
    }
}
Pose PoseHandler::Query() const noexcept { return {x, y, HEADINGS[direction]}; }
// 原子动作不读取 B/F；组合规则只在命令编排层处理。
void PoseHandler::Forward() noexcept { x += DX[direction]; y += DY[direction]; }
void PoseHandler::Backward() noexcept { x -= DX[direction]; y -= DY[direction]; }
} // namespace adas
