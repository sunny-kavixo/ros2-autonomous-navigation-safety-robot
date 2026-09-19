from pathlib import Path
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    nav_share = Path(get_package_share_directory("robot_navigation"))
    desc_share = Path(get_package_share_directory("robot_description"))
    nav2_share = Path(get_package_share_directory("nav2_bringup"))
    slam_share = Path(get_package_share_directory("slam_toolbox"))

    sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(desc_share / "launch" / "sim.launch.py"))
    )
    slam = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(slam_share / "launch" / "online_async_launch.py")),
        launch_arguments={"slam_params_file": str(nav_share / "config" / "slam_params.yaml"),
                          "use_sim_time": "true"}.items(),
    )
    nav2 = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(nav2_share / "launch" / "navigation_launch.py")),
        launch_arguments={"params_file": str(nav_share / "config" / "nav2_params.yaml"),
                          "use_sim_time": "true",
                          "autostart": "true"}.items(),
    )
    safety = Node(package="safety_supervisor", executable="safety_supervisor_node",
                  remappings=[("cmd_vel_nav", "/cmd_vel"),
                              ("cmd_vel_safe", "/cmd_vel_safe")],
                  parameters=[{"use_sim_time": True}])
    return LaunchDescription([sim, slam, nav2, safety])
