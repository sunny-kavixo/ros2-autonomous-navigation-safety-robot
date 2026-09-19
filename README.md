# ROS2 Autonomous Navigation & Safety Robot

A job-focused robotics software portfolio project built around **ROS 2, C++, autonomous navigation, simulation, and safety supervision**.

## Goal

Build and validate an autonomous differential-drive mobile robot in simulation before hardware integration.

## Architecture

```text
Gazebo LiDAR + Odometry
          |
          v
        ROS 2
          |
          v
  SLAM / Localization      (planned)
          |
          v
         Nav2              (planned)
          |
          v
 Safety Supervisor (C++)
          |
          v
    /cmd_vel_safe
          |
          v
Gazebo Differential Drive
```

## Implemented

### C++ safety supervisor
- `geometry_msgs/Twist` command input
- `sensor_msgs/LaserScan` safety input
- emergency-stop and slow zones
- stale/invalid scan fail-safe
- deterministic safety policy separated from ROS I/O
- unit tests

### Differential-drive simulation baseline
- Xacro/URDF mobile robot
- left/right continuous drive wheels
- caster and LiDAR links
- inertial and collision geometry
- Gazebo Sim differential-drive system
- simulated 360-degree LiDAR
- odometry and joint-state topics
- ROS ↔ Gazebo bridge configuration
- test world with a fixed obstacle
- ROS 2 simulation launch file

These simulation assets are **implemented in source**. Runtime behavior will only be described as validated after the simulation is built and executed in a compatible ROS 2 / Gazebo environment.

## Build

```bash
colcon build --symlink-install
source install/setup.bash
```

## Run simulation

```bash
ros2 launch robot_description sim.launch.py
```

The intended command path is:

```text
navigation command -> cmd_vel_nav -> safety_supervisor -> cmd_vel_safe -> Gazebo robot
```

## Test safety policy

```bash
colcon test --packages-select safety_supervisor
colcon test-result --verbose
```

## Roadmap

1. Safety supervisor — **implemented**
2. Differential-drive URDF/Xacro — **implemented**
3. Gazebo simulation assets — **implemented; runtime validation pending**
4. TF and odometry runtime validation
5. Nav2 integration
6. SLAM/localization
7. Navigation failure tests
8. Reproducible demo evidence

## Evidence standard

This repository deliberately separates **source implementation** from **runtime validation**. Nav2, SLAM, successful Gazebo motion, and physical hardware operation are not claimed until they are actually demonstrated and tested.
