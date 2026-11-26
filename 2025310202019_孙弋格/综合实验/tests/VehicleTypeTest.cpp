#include "Executor.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

namespace adas {
namespace {
struct VehicleCase {
    VehicleType type;
    char initialHeading;
    std::string commands;
    Pose expected;
};
// 期望值逐项来自综合课件第55页，基准朝向为E。
std::vector<VehicleCase> VehicleCases()
{
    const VehicleCase eastCases[] = {
        {VehicleType::Normal, 'E', "M", {1, 0, 'E'}},
        {VehicleType::Normal, 'E', "L", {0, 0, 'N'}},
        {VehicleType::Normal, 'E', "R", {0, 0, 'S'}},
        {VehicleType::Normal, 'E', "BM", {-1, 0, 'E'}},
        {VehicleType::Normal, 'E', "BL", {0, 0, 'S'}},
        {VehicleType::Normal, 'E', "BR", {0, 0, 'N'}},
        {VehicleType::Normal, 'E', "FM", {2, 0, 'E'}},
        {VehicleType::Normal, 'E', "FL", {1, 0, 'N'}},
        {VehicleType::Normal, 'E', "FR", {1, 0, 'S'}},
        {VehicleType::Normal, 'E', "BFM", {-2, 0, 'E'}},
        {VehicleType::Normal, 'E', "BFL", {-1, 0, 'S'}},
        {VehicleType::Normal, 'E', "BFR", {-1, 0, 'N'}},
        {VehicleType::Sport, 'E', "M", {2, 0, 'E'}},
        {VehicleType::Sport, 'E', "L", {0, 1, 'N'}},
        {VehicleType::Sport, 'E', "R", {0, -1, 'S'}},
        {VehicleType::Sport, 'E', "BM", {-2, 0, 'E'}},
        {VehicleType::Sport, 'E', "BL", {0, 1, 'S'}},
        {VehicleType::Sport, 'E', "BR", {0, -1, 'N'}},
        {VehicleType::Sport, 'E', "FM", {4, 0, 'E'}},
        {VehicleType::Sport, 'E', "FL", {1, 1, 'N'}},
        {VehicleType::Sport, 'E', "FR", {1, -1, 'S'}},
        {VehicleType::Sport, 'E', "BFM", {-4, 0, 'E'}},
        {VehicleType::Sport, 'E', "BFL", {-1, 1, 'S'}},
        {VehicleType::Sport, 'E', "BFR", {-1, -1, 'N'}},
        {VehicleType::Bus, 'E', "M", {1, 0, 'E'}},
        {VehicleType::Bus, 'E', "L", {1, 0, 'N'}},
        {VehicleType::Bus, 'E', "R", {1, 0, 'S'}},
        {VehicleType::Bus, 'E', "BM", {-1, 0, 'E'}},
        {VehicleType::Bus, 'E', "BL", {-1, 0, 'S'}},
        {VehicleType::Bus, 'E', "BR", {-1, 0, 'N'}},
        {VehicleType::Bus, 'E', "FM", {2, 0, 'E'}},
        {VehicleType::Bus, 'E', "FL", {2, 0, 'N'}},
        {VehicleType::Bus, 'E', "FR", {2, 0, 'S'}},
        {VehicleType::Bus, 'E', "BFM", {-2, 0, 'E'}},
        {VehicleType::Bus, 'E', "BFL", {-2, 0, 'S'}},
        {VehicleType::Bus, 'E', "BFR", {-2, 0, 'N'}}
    };
    const std::string headings = "ENWS";
    std::vector<VehicleCase> result;
    for (const auto& east : eastCases) {
        for (std::size_t turn = 0; turn < 4; ++turn) {
            auto data = east;
            data.initialHeading = headings[turn];
            for (std::size_t i = 0; i < turn; ++i) {
                const auto oldX = data.expected.x;
                data.expected.x = -data.expected.y;
                data.expected.y = oldX;
            }
            const auto index = headings.find(east.expected.heading);
            data.expected.heading = headings[(index + turn) % 4];
            data.expected.x += 5;
            data.expected.y -= 7;
            result.push_back(data);
        }
    }
    return result;
}
class VehicleTypeTest : public testing::TestWithParam<VehicleCase> {};
TEST_P(VehicleTypeTest, follows_vehicle_state_and_direction_matrix)
{
    const auto& data = GetParam();
    SCOPED_TRACE(data.commands);
    std::unique_ptr<Executor> executor(Executor::NewExecutor({5, -7, data.initialHeading}, data.type));
    ASSERT_NE(executor, nullptr);
    executor->Execute(data.commands);
    const auto actual = executor->Query();
    EXPECT_EQ(actual.x, data.expected.x);
    EXPECT_EQ(actual.y, data.expected.y);
    EXPECT_EQ(actual.heading, data.expected.heading);
}
INSTANTIATE_TEST_SUITE_P(ThreeVehiclesFourStatesFourDirections, VehicleTypeTest,
                         testing::ValuesIn(VehicleCases()));
TEST(VehicleStateTest, toggles_cancel_for_each_vehicle_and_persist_across_calls)
{
    for (auto type : {VehicleType::Normal, VehicleType::Sport, VehicleType::Bus}) {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, type));
        ASSERT_NE(executor, nullptr);
        const int unit = type == VehicleType::Sport ? 2 : 1;
        executor->Execute("B");
        executor->Execute("F");
        executor->Execute("M");
        EXPECT_EQ(executor->Query().x, -2 * unit);
        executor->Execute("BF");
        executor->Execute("M");
        EXPECT_EQ(executor->Query().x, -unit);
        executor->Execute("FFBBM");
        EXPECT_EQ(executor->Query().x, 0);
        EXPECT_EQ(executor->Query().heading, 'E');
    }
}
} // namespace
} // namespace adas
