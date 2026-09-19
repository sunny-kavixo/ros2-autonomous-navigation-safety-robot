# Gazebo Runtime Validation

CI validates build, unit tests, and Xacro structure. Runtime validation requires a graphical ROS 2 Jazzy + Gazebo environment.

## Start

```bash
colcon build --symlink-install
source install/setup.bash
ros2 launch robot_description sim.launch.py
```

In separate sourced terminals, verify:

```bash
ros2 topic list
ros2 topic echo /scan --once
ros2 topic echo /odom --once
ros2 run tf2_ros tf2_echo odom base_footprint
```

Start the safety supervisor:

```bash
ros2 run safety_supervisor safety_supervisor_node
```

Then request forward motion through its navigation-side input:

```bash
ros2 topic pub --once /cmd_vel_nav geometry_msgs/msg/Twist "{linear: {x: 0.25}, angular: {z: 0.0}}"
```

## PASS criteria

Runtime is marked validated only when all are observed:

1. Robot model spawns in Gazebo.
2. `/scan` publishes finite LiDAR ranges.
3. `/odom` publishes changing robot pose during motion.
4. TF resolves `odom -> base_footprint`.
5. A safe `/cmd_vel_nav` request reaches `/cmd_vel_safe` and causes simulated motion.
6. An obstacle inside the configured stop distance prevents forward motion.

Record terminal output/screenshots before changing README status from pending to validated.
