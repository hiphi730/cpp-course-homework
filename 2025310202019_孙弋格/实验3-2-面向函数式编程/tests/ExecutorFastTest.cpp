#include "Executor.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace adas {
namespace {
struct FastCase { char heading; const char* commands; Pose expected; };
class FastCommandTest : public testing::TestWithParam<FastCase> {};
TEST_P(FastCommandTest, moves_before_turning_in_fast_state)
{
    const auto& data = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, data.heading}));
    ASSERT_NE(executor, nullptr);
    executor->Execute(data.commands);
    const auto actual = executor->Query();
    EXPECT_EQ(actual.x, data.expected.x);
    EXPECT_EQ(actual.y, data.expected.y);
    EXPECT_EQ(actual.heading, data.expected.heading);
}
INSTANTIATE_TEST_SUITE_P(AllDirections, FastCommandTest, testing::Values(
    FastCase{'E', "FM", {2, 0, 'E'}}, FastCase{'N', "FM", {0, 2, 'N'}},
    FastCase{'W', "FM", {-2, 0, 'W'}}, FastCase{'S', "FM", {0, -2, 'S'}},
    FastCase{'E', "FL", {1, 0, 'N'}}, FastCase{'N', "FL", {0, 1, 'W'}},
    FastCase{'W', "FL", {-1, 0, 'S'}}, FastCase{'S', "FL", {0, -1, 'E'}},
    FastCase{'E', "FR", {1, 0, 'S'}}, FastCase{'N', "FR", {0, 1, 'E'}},
    FastCase{'W', "FR", {-1, 0, 'N'}}, FastCase{'S', "FR", {0, -1, 'W'}},
    FastCase{'E', "FFM", {1, 0, 'E'}}, FastCase{'E', "FFL", {0, 0, 'N'}},
    FastCase{'E', "FFR", {0, 0, 'S'}}, FastCase{'E', "FMFM", {3, 0, 'E'}}));
TEST(ExecutorFastTest, fast_state_persists_between_calls_and_is_per_instance)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    std::unique_ptr<Executor> normal(Executor::NewExecutor());
    ASSERT_NE(executor, nullptr);
    ASSERT_NE(normal, nullptr);
    executor->Execute("F");
    executor->Execute("M");
    EXPECT_EQ(executor->Query().y, 2);
    executor->Execute("F");
    executor->Execute("M");
    EXPECT_EQ(executor->Query().y, 3);
    normal->Execute("M");
    EXPECT_EQ(normal->Query().y, 1);
}
} // namespace
} // namespace adas
