#include "action/ActionGroup.hpp"
#include "pose/PoseHandler.hpp"
#include <gtest/gtest.h>

namespace adas {
TEST(ActionGroupTest, raw_actions_move_one_cell_even_with_fast_and_reverse_flags)
{
    PoseHandler pose({0, 0, 'E'}, VehicleType::Sport);
    ActionGroup({ActionType::Fast, ActionType::Reverse}).DoOperate(pose);
    ActionGroup({ActionType::ForwardOneStep}).DoOperate(pose);
    EXPECT_EQ(pose.Query().x, 1);
    ActionGroup({ActionType::BackwardOneStep}).DoOperate(pose);
    EXPECT_EQ(pose.Query().x, 0);
    ActionGroup({ActionType::TurnLeft, ActionType::ForwardOneStep}).DoOperate(pose);
    EXPECT_EQ(pose.Query().y, 1);
    EXPECT_EQ(pose.Query().heading, 'N');
    ActionGroup({ActionType::TurnRight, ActionType::BackwardOneStep}).DoOperate(pose);
    EXPECT_EQ(pose.Query().x, -1);
    EXPECT_TRUE(pose.IsFast());
    EXPECT_TRUE(pose.IsReverse());
}
TEST(ActionGroupTest, empty_action_group_preserves_pose)
{
    PoseHandler pose({1, 2, 'W'}, VehicleType::Bus);
    ActionGroup{}.DoOperate(pose);
    EXPECT_EQ(pose.Query().x, 1);
    EXPECT_EQ(pose.Query().y, 2);
    EXPECT_EQ(pose.Query().heading, 'W');
}
} // namespace adas
