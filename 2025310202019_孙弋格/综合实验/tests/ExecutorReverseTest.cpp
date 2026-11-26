#include "Executor.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace adas {
namespace {
struct ReverseCase { char heading; const char* commands; Pose expected; };
class ReverseCommandTest : public testing::TestWithParam<ReverseCase> {};
TEST_P(ReverseCommandTest, reverse_and_fast_states_are_orthogonal)
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
INSTANTIATE_TEST_SUITE_P(StateCombinations, ReverseCommandTest, testing::Values(
    ReverseCase{'E', "BM", {-1, 0, 'E'}}, ReverseCase{'N', "BM", {0, -1, 'N'}},
    ReverseCase{'W', "BM", {1, 0, 'W'}}, ReverseCase{'S', "BM", {0, 1, 'S'}},
    ReverseCase{'E', "BL", {0, 0, 'S'}}, ReverseCase{'N', "BL", {0, 0, 'E'}},
    ReverseCase{'W', "BL", {0, 0, 'N'}}, ReverseCase{'S', "BL", {0, 0, 'W'}},
    ReverseCase{'E', "BR", {0, 0, 'N'}}, ReverseCase{'N', "BR", {0, 0, 'W'}},
    ReverseCase{'W', "BR", {0, 0, 'S'}}, ReverseCase{'S', "BR", {0, 0, 'E'}},
    ReverseCase{'E', "BFM", {-2, 0, 'E'}}, ReverseCase{'N', "BFM", {0, -2, 'N'}},
    ReverseCase{'W', "BFM", {2, 0, 'W'}}, ReverseCase{'S', "BFM", {0, 2, 'S'}},
    ReverseCase{'E', "BFL", {-1, 0, 'S'}}, ReverseCase{'N', "BFL", {0, -1, 'E'}},
    ReverseCase{'W', "BFL", {1, 0, 'N'}}, ReverseCase{'S', "BFL", {0, 1, 'W'}},
    ReverseCase{'E', "BFR", {-1, 0, 'N'}}, ReverseCase{'N', "BFR", {0, -1, 'W'}},
    ReverseCase{'W', "BFR", {1, 0, 'S'}}, ReverseCase{'S', "BFR", {0, 1, 'E'}},
    ReverseCase{'E', "BBM", {1, 0, 'E'}}, ReverseCase{'E', "BFFM", {-1, 0, 'E'}},
    ReverseCase{'E', "BFBM", {2, 0, 'E'}}, ReverseCase{'E', "BFMLBMR", {-3, -3, 'W'}}));
TEST(ExecutorReverseTest, reverse_persists_and_toggle_does_not_move)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(executor, nullptr);
    executor->Execute("BF");
    EXPECT_EQ(executor->Query().x, 0);
    EXPECT_EQ(executor->Query().heading, 'E');
    executor->Execute("M");
    EXPECT_EQ(executor->Query().x, -2);
    executor->Execute("B");
    executor->Execute("M");
    EXPECT_EQ(executor->Query().x, 0);
    executor->Execute("F");
    executor->Execute("M");
    EXPECT_EQ(executor->Query().x, 1);
}
TEST(ExecutorReverseTest, fast_and_reverse_toggle_order_is_irrelevant)
{
    std::unique_ptr<Executor> bf(Executor::NewExecutor());
    std::unique_ptr<Executor> fb(Executor::NewExecutor());
    ASSERT_NE(bf, nullptr);
    ASSERT_NE(fb, nullptr);
    bf->Execute("BFMLMRM");
    fb->Execute("FBMLMRM");
    EXPECT_EQ(bf->Query().x, fb->Query().x);
    EXPECT_EQ(bf->Query().y, fb->Query().y);
    EXPECT_EQ(bf->Query().heading, fb->Query().heading);
}
} // namespace
} // namespace adas
