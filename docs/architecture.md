# Architecture

Command path: `Nav2 -> cmd_vel_nav -> safety_supervisor -> cmd_vel_safe -> robot controller`.

## Implemented
- ROS 2 C++ package structure
- deterministic safety policy
- LaserScan + Twist interfaces
- configurable stop/slow thresholds
- stale-sensor fail-safe
- unit tests

## Planned, not yet claimed
- Gazebo robot simulation
- URDF/Xacro
- Nav2
- SLAM/localization
- autonomous navigation demo
- Raspberry Pi deployment
