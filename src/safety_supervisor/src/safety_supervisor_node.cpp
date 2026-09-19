#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "safety_supervisor/safety_policy.hpp"

class SafetySupervisorNode : public rclcpp::Node {
 public:
  SafetySupervisorNode() : Node("safety_supervisor") {
    const auto stop = declare_parameter("stop_distance_m", 0.35);
    const auto slow = declare_parameter("slow_distance_m", 0.70);
    const auto slow_speed = declare_parameter("slow_speed_mps", 0.15);
    scan_timeout_s_ = declare_parameter("scan_timeout_s", 0.5);
    policy_ = std::make_unique<safety_supervisor::SafetyPolicy>(safety_supervisor::SafetyConfig{stop, slow, slow_speed});
    safe_pub_ = create_publisher<geometry_msgs::msg::Twist>("cmd_vel_safe", 10);
    cmd_sub_ = create_subscription<geometry_msgs::msg::Twist>("cmd_vel_nav", 10, [this](geometry_msgs::msg::Twist::SharedPtr msg){ on_command(*msg); });
    scan_sub_ = create_subscription<sensor_msgs::msg::LaserScan>("scan", rclcpp::SensorDataQoS(), [this](sensor_msgs::msg::LaserScan::SharedPtr msg){ on_scan(*msg); });
  }
 private:
  void on_scan(const sensor_msgs::msg::LaserScan &scan) {
    nearest_obstacle_m_ = std::numeric_limits<double>::infinity();
    for (float range : scan.ranges)
      if (std::isfinite(range) && range >= scan.range_min && range <= scan.range_max)
        nearest_obstacle_m_ = std::min(nearest_obstacle_m_, static_cast<double>(range));
    last_scan_time_ = now(); have_scan_ = true;
  }
  void on_command(const geometry_msgs::msg::Twist &msg) {
    const bool fresh = have_scan_ && (now() - last_scan_time_).seconds() <= scan_timeout_s_;
    const auto result = policy_->evaluate({msg.linear.x, msg.angular.z}, nearest_obstacle_m_, fresh);
    geometry_msgs::msg::Twist safe; safe.linear.x = result.linear_x; safe.angular.z = result.angular_z; safe_pub_->publish(safe);
  }
  std::unique_ptr<safety_supervisor::SafetyPolicy> policy_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr safe_pub_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_sub_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub_;
  rclcpp::Time last_scan_time_{0, 0, RCL_ROS_TIME};
  double nearest_obstacle_m_{std::numeric_limits<double>::infinity()}, scan_timeout_s_{0.5};
  bool have_scan_{false};
};
int main(int argc, char **argv) {
  rclcpp::init(argc, argv); rclcpp::spin(std::make_shared<SafetySupervisorNode>()); rclcpp::shutdown(); return 0;
}
