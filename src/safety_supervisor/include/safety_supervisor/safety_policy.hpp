#pragma once
namespace safety_supervisor {
struct VelocityCommand { double linear_x{0.0}; double angular_z{0.0}; };
struct SafetyConfig { double stop_distance_m{0.35}; double slow_distance_m{0.70}; double slow_speed_mps{0.15}; };
class SafetyPolicy {
 public:
  explicit SafetyPolicy(SafetyConfig config = {});
  VelocityCommand evaluate(const VelocityCommand &requested, double nearest_obstacle_m, bool scan_is_fresh) const;
 private:
  SafetyConfig config_;
};
}  // namespace safety_supervisor
