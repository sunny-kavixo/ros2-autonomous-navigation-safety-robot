# Nav2 + SLAM Integration

The repository contains a Nav2/SLAM integration baseline for the simulated differential-drive robot.

## Launch

```bash
colcon build --symlink-install
source install/setup.bash
ros2 launch robot_navigation navigation.launch.py
```

The intended runtime chain is:

```text
/scan + /odom -> SLAM Toolbox -> map/TF
                         |
                         v
                       Nav2
                         |
                      /cmd_vel
                         |
                         v
                safety_supervisor
                         |
                  /cmd_vel_safe
                         |
                         v
                 Gazebo DiffDrive
```

## Validation status

The Nav2/SLAM files are implemented and buildable source. Autonomous navigation is not marked runtime-validated until a compatible ROS 2 Jazzy + Gazebo session demonstrates map creation, goal acceptance, path execution, odometry/TF continuity, and safety stopping.
