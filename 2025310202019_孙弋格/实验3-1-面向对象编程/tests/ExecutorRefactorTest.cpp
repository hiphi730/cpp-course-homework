#include "Executor.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace adas {
TEST(ExecutorRefactorTest, shared_commands_do_not_share_executor_state)
{
    for (int i = 0; i < 50; ++i) {
        std::unique_ptr<Executor> fast(Executor::NewExecutor());
        std::unique_ptr<Executor> normal(Executor::NewExecutor());
        ASSERT_NE(fast, nullptr);
        ASSERT_NE(normal, nullptr);
        fast->Execute("FM");
        normal->Execute("M");
        EXPECT_EQ(fast->Query().y, 2);
        EXPECT_EQ(normal->Query().y, 1);
    }
}
} // namespace adas
