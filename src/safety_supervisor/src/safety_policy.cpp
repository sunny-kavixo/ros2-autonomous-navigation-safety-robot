#include "safety_supervisor/safety_policy.hpp"
#include <cmath>
#include <stdexcept>
namespace safety_supervisor {
SafetyPolicy::SafetyPolicy(SafetyConfig config) : config_(config) {
  if (config_.stop_distance_m <= 0.0 || config_.slow_distance_m <= config_.stop_distance_m || config_.slow_speed_mps < 0.0)
    throw std::invalid_argument("Invalid safety configuration");
}
VelocityCommand SafetyPolicy::evaluate(const VelocityCommand &requested, double nearest_obstacle_m, bool scan_is_fresh) const {
  if (!scan_is_fresh || !std::isfinite(nearest_obstacle_m)) return {};
  if (requested.linear_x > 0.0 && nearest_obstacle_m <= config_.stop_distance_m) return {};
  VelocityCommand safe = requested;
  if (safe.linear_x > config_.slow_speed_mps && nearest_obstacle_m <= config_.slow_distance_m) safe.linear_x = config_.slow_speed_mps;
  return safe;
}
}  // namespace safety_supervisor
