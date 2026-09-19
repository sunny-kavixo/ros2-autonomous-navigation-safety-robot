#include <gtest/gtest.h>
#include <limits>
#include "safety_supervisor/safety_policy.hpp"
using safety_supervisor::SafetyPolicy;
TEST(SafetyPolicy, StopsWhenScanIsStale) { SafetyPolicy p; auto o=p.evaluate({0.4,0.2},2.0,false); EXPECT_DOUBLE_EQ(o.linear_x,0.0); EXPECT_DOUBLE_EQ(o.angular_z,0.0); }
TEST(SafetyPolicy, StopsForCloseObstacle) { SafetyPolicy p; auto o=p.evaluate({0.4,0.0},0.20,true); EXPECT_DOUBLE_EQ(o.linear_x,0.0); }
TEST(SafetyPolicy, SlowsForWarningZone) { SafetyPolicy p; auto o=p.evaluate({0.4,0.1},0.50,true); EXPECT_DOUBLE_EQ(o.linear_x,0.15); EXPECT_DOUBLE_EQ(o.angular_z,0.1); }
TEST(SafetyPolicy, PassesWhenClear) { SafetyPolicy p; auto o=p.evaluate({0.4,-0.2},2.0,true); EXPECT_DOUBLE_EQ(o.linear_x,0.4); EXPECT_DOUBLE_EQ(o.angular_z,-0.2); }
TEST(SafetyPolicy, FailsSafeForInvalidRange) { SafetyPolicy p; auto o=p.evaluate({0.4,0.0},std::numeric_limits<double>::infinity(),true); EXPECT_DOUBLE_EQ(o.linear_x,0.0); }
