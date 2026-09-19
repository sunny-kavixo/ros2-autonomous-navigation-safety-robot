# ROS2 Autonomous Navigation & Safety Robot

A job-focused robotics software portfolio project using **ROS 2 Jazzy, C++, Gazebo, Nav2, SLAM Toolbox, LiDAR, TF/odometry, and safety supervision**.

## System

```text
Gazebo LiDAR + Odometry
          |
          v
   SLAM Toolbox
          |
       map + TF
          |
          v
         Nav2
          |
       /cmd_vel
          |
          v
 Safety Supervisor (C++)
          |
    /cmd_vel_safe
          |
          v
Gazebo Differential Drive
```

## Implemented

- C++ ROS 2 safety supervisor with emergency-stop, slowdown and stale-sensor fail-safe behavior
- deterministic C++ unit tests
- differential-drive Xacro/URDF robot with collision/inertial geometry
- simulated 360° LiDAR
- Gazebo differential-drive, odometry and joint-state integration
- ROS ↔ Gazebo bridge configuration
- test world with obstacle
- robot-description structural tests
- ROS 2 Jazzy CI build/test/Xacro validation
- Nav2 planner/controller/costmap configuration
- SLAM Toolbox configuration
- integrated simulation + SLAM + Nav2 + safety launch
- runtime validation checklist

## Verification boundary

GitHub CI verifies that the ROS 2 workspace builds, the deterministic tests pass, and the Xacro description renders. **Gazebo motion, TF/odometry continuity, SLAM mapping and autonomous Nav2 goal execution remain runtime-validation items** until captured from a compatible ROS 2 Jazzy/Gazebo session.

That distinction is intentional: implemented source is not presented as runtime evidence.

## Demo evidence

Runtime screenshots and video will be added here **after the full ROS 2 Jazzy/Gazebo validation is actually run and captured**. No simulated screenshot, stock image, generated image, or unrelated robotics video is presented as evidence of this repository.

Planned evidence:

1. Gazebo robot spawned in the test world
2. Live 360° LiDAR `/scan`
3. Odometry and `odom -> base_footprint` TF
4. Safety-supervisor STOP / SLOW / PASS behavior
5. SLAM Toolbox map generation
6. Nav2 autonomous goal execution
7. Short end-to-end demo video

Validation procedure and PASS criteria are documented in `docs/runtime-validation.md`.

## Build and test

```bash
colcon build --symlink-install
source install/setup.bash
colcon test
colcon test-result --verbose
```

## Run full navigation stack

```bash
ros2 launch robot_navigation navigation.launch.py
```

See `docs/runtime-validation.md` and `docs/nav2.md` for validation criteria.

## Portfolio status

**Feature-complete source baseline; runtime demo validation pending.**

The repository is designed as a portfolio project demonstrating ROS 2 package architecture, C++ safety logic, robot description, simulation integration, navigation configuration, testing, and evidence-aware engineering. Physical-hardware deployment is outside the current scope.
