#include "Executor.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <tuple>

namespace adas {
namespace {
using TurnRoundCase = std::tuple<VehicleType, std::string, int>;
class TurnRoundTest : public testing::TestWithParam<TurnRoundCase> {};
TEST_P(TurnRoundTest, ignores_reverse_and_uses_raw_vehicle_independent_actions)
{
    const auto type = std::get<0>(GetParam());
    const auto state = std::get<1>(GetParam());
    const auto turns = std::get<2>(GetParam());
    const std::string headings = "ENWS";
    Pose expected{state.find('F') == std::string::npos ? 0 : 1, 1, headings[(2 + turns) % 4]};
    for (int i = 0; i < turns; ++i) {
        const auto oldX = expected.x;
        expected.x = -expected.y;
        expected.y = oldX;
    }
    expected.x += 3;
    expected.y -= 2;
    std::unique_ptr<Executor> executor(Executor::NewExecutor({3, -2, headings[turns]}, type));
    ASSERT_NE(executor, nullptr);
    executor->Execute(state + "TR");
    const auto actual = executor->Query();
    EXPECT_EQ(actual.x, expected.x);
    EXPECT_EQ(actual.y, expected.y);
    EXPECT_EQ(actual.heading, expected.heading);
}
INSTANTIATE_TEST_SUITE_P(AllVehiclesStatesDirections, TurnRoundTest, testing::Combine(
    testing::Values(VehicleType::Normal, VehicleType::Sport, VehicleType::Bus),
    testing::Values(std::string(""), std::string("B"), std::string("F"), std::string("BF")),
    testing::Values(0, 1, 2, 3)));
struct BatchCase { const char* commands; Pose expected; };
class TurnRoundBatchTest : public testing::TestWithParam<BatchCase> {};
TEST_P(TurnRoundBatchTest, parses_pairs_and_preserves_state_for_following_commands)
{
    const auto& data = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(executor, nullptr);
    executor->Execute(data.commands);
    const auto actual = executor->Query();
    EXPECT_EQ(actual.x, data.expected.x);
    EXPECT_EQ(actual.y, data.expected.y);
    EXPECT_EQ(actual.heading, data.expected.heading);
}
INSTANTIATE_TEST_SUITE_P(TokenBoundaries, TurnRoundBatchTest, testing::Values(
    BatchCase{"TRR", {0, 1, 'N'}}, BatchCase{"TRTR", {0, 0, 'E'}},
    BatchCase{"TRTRTR", {0, 1, 'W'}}, BatchCase{"FTRM", {-1, 1, 'W'}},
    BatchCase{"BTRM", {1, 1, 'W'}}, BatchCase{"BFTRM", {3, 1, 'W'}},
    BatchCase{"TRFTRBTR", {0, 1, 'W'}}));
} // namespace
} // namespace adas
