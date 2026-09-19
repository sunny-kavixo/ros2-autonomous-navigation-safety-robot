# ROS2 Autonomous Navigation & Safety Robot

A job-focused robotics software portfolio project built around **ROS 2, C++, autonomous navigation, simulation, and safety supervision**.

## Goal

Build and test an autonomous differential-drive mobile robot in simulation before hardware integration.

## Architecture

```text
LiDAR + Odometry
       |
       v
     ROS 2
       |
       v
SLAM / Localization
       |
       v
      Nav2
       |
       v
Global + Local Planning
       |
       v
Safety Supervisor (C++)
       |
       v
   /cmd_vel_safe
       |
       v
Simulated Differential-Drive Robot
```

## Current implementation

The first component is `safety_supervisor`, a ROS 2 C++ package with velocity-command and LaserScan inputs, configurable emergency-stop/slow distances, stale-scan fail-safe behavior, safe velocity output, a deterministic policy separated from ROS I/O, and unit tests.

| Condition | Behavior |
|---|---|
| LaserScan missing/stale | STOP |
| Obstacle inside emergency distance | STOP |
| Obstacle inside slow distance | Reduce forward speed |
| Path clear | Pass navigation command |

This is a **simulation-first portfolio project**, not a claim of deployment on a physical robot.

## Build and test

```bash
colcon build --symlink-install
source install/setup.bash
colcon test --packages-select safety_supervisor
colcon test-result --verbose
```

## Roadmap

1. Safety supervisor — **implemented**
2. Differential-drive URDF/Xacro
3. Gazebo simulation
4. TF and odometry validation
5. Nav2 integration
6. SLAM/localization
7. Navigation failure tests
8. Reproducible demo evidence

Claims will be updated only after reproducible validation exists.
