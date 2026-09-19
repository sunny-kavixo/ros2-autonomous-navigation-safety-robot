from pathlib import Path
from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import xacro

def generate_launch_description():
    share = Path(get_package_share_directory("robot_description"))
    robot_description = xacro.process_file(str(share / "urdf" / "mobile_robot.urdf.xacro")).toxml()
    world = str(share / "worlds" / "test_world.sdf")
    bridge = str(share / "config" / "bridge.yaml")

    return LaunchDescription([
        ExecuteProcess(cmd=["gz", "sim", "-r", world], output="screen"),
        Node(package="robot_state_publisher", executable="robot_state_publisher",
             parameters=[{"robot_description": robot_description, "use_sim_time": True}]),
        Node(package="ros_gz_sim", executable="create",
             arguments=["-name", "sunny_mobile_robot", "-string", robot_description, "-z", "0.10"],
             output="screen"),
        Node(package="ros_gz_bridge", executable="parameter_bridge",
             parameters=[{"config_file": bridge}], output="screen"),
    ])
