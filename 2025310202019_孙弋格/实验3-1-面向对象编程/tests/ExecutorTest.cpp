#include "Executor.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace adas {
namespace {
void ExpectPose(const Pose& actual, const Pose& expected)
{
    EXPECT_EQ(actual.x, expected.x);
    EXPECT_EQ(actual.y, expected.y);
    EXPECT_EQ(actual.heading, expected.heading);
}
struct BasicCase {
    char heading;
    const char* commands;
    Pose expected;
};
class BasicCommandTest : public testing::TestWithParam<BasicCase> {};
TEST_P(BasicCommandTest, follows_axis_and_turn_rules)
{
    const auto& data = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor({7, -3, data.heading}));
    ASSERT_NE(executor, nullptr);
    executor->Execute(data.commands);
    ExpectPose(executor->Query(), data.expected);
}
INSTANTIATE_TEST_SUITE_P(AllDirections, BasicCommandTest, testing::Values(
    BasicCase{'N', "M", {7, -2, 'N'}}, BasicCase{'E', "M", {8, -3, 'E'}},
    BasicCase{'S', "M", {7, -4, 'S'}}, BasicCase{'W', "M", {6, -3, 'W'}},
    BasicCase{'N', "L", {7, -3, 'W'}}, BasicCase{'E', "L", {7, -3, 'N'}},
    BasicCase{'S', "L", {7, -3, 'E'}}, BasicCase{'W', "L", {7, -3, 'S'}},
    BasicCase{'N', "R", {7, -3, 'E'}}, BasicCase{'E', "R", {7, -3, 'S'}},
    BasicCase{'S', "R", {7, -3, 'W'}}, BasicCase{'W', "R", {7, -3, 'N'}}));

TEST(ExecutorTest, default_pose_and_empty_batch)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(executor, nullptr);
    ExpectPose(executor->Query(), {0, 0, 'N'});
    executor->Execute("");
    ExpectPose(executor->Query(), {0, 0, 'N'});
}
TEST(ExecutorTest, preserves_explicit_pose_and_int32_boundaries)
{
    const Pose initial{-2147483647 - 1, 2147483647, 'W'};
    std::unique_ptr<Executor> executor(Executor::NewExecutor(initial));
    ASSERT_NE(executor, nullptr);
    ExpectPose(executor->Query(), initial);
    executor->Execute("RRRR");
    ExpectPose(executor->Query(), initial);
}
TEST(ExecutorTest, executes_course_batch)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(executor, nullptr);
    executor->Execute("MLMMRM");
    ExpectPose(executor->Query(), {-2, 2, 'N'});
}
TEST(ExecutorTest, split_batches_equal_one_batch)
{
    std::unique_ptr<Executor> split(Executor::NewExecutor({-5, 4, 'W'}));
    std::unique_ptr<Executor> whole(Executor::NewExecutor({-5, 4, 'W'}));
    ASSERT_NE(split, nullptr);
    ASSERT_NE(whole, nullptr);
    split->Execute("ML");
    split->Execute("MMRM");
    whole->Execute("MLMMRM");
    ExpectPose(split->Query(), whole->Query());
    ExpectPose(whole->Query(), {-7, 2, 'W'});
}
TEST(ExecutorTest, full_turns_and_closed_route)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(executor, nullptr);
    executor->Execute("LLLLRRRRMRMRMRMR");
    ExpectPose(executor->Query(), {0, 0, 'N'});
}
TEST(ExecutorTest, instances_keep_independent_positions)
{
    std::unique_ptr<Executor> first(Executor::NewExecutor());
    std::unique_ptr<Executor> second(Executor::NewExecutor({3, 4, 'S'}));
    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);
    first->Execute("MM");
    ExpectPose(first->Query(), {0, 2, 'N'});
    ExpectPose(second->Query(), {3, 4, 'S'});
}
} // namespace
} // namespace adas
