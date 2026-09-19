import subprocess
from pathlib import Path
import xml.etree.ElementTree as ET

XACRO = Path(__file__).parents[1] / "urdf" / "mobile_robot.urdf.xacro"

def rendered_root():
    result = subprocess.run(["xacro", str(XACRO)], check=True, capture_output=True, text=True)
    return ET.fromstring(result.stdout)

def test_required_links_and_joints_exist():
    root = rendered_root()
    links = {x.attrib["name"] for x in root.findall("link")}
    joints = {x.attrib["name"] for x in root.findall("joint")}
    assert {"base_footprint","base_link","left_wheel_link","right_wheel_link","lidar_link"} <= links
    assert {"left_wheel_joint","right_wheel_joint","lidar_joint"} <= joints

def test_gazebo_diff_drive_and_lidar_exist():
    root = rendered_root()
    plugins = root.findall(".//plugin")
    sensors = root.findall(".//sensor")
    assert any("DiffDrive" in p.attrib.get("name","") for p in plugins)
    assert any(s.attrib.get("type") == "gpu_lidar" for s in sensors)
