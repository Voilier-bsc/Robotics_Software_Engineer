# Project 5 : Home Servie Robot

## Overview

In this project, I use everything learned in the Nanodegree Program to build a Home Service Robot in ROS

### Mapping
- In mapping Section, I use my robot instead turtlebot to mapping my environment.
- I create a 'test_slam.sh' script file.

### Localization and Navigation
- I create a 'test_navigation.sh' script file.
  - In Localization and Navigation Section, My robot is able to naviagte in the  envirionment after a 2D Nav Goal Command is issued.
- I create a 'pick_objects.sh' script file. 
  - My robot tavels to the desired pickup zone, displays a message that it reached its destination, waits 5 seconds, travels to the desired drop off zone(infront of a man in environment), and displays a message that it reached the drop off zone.

### Home Service robot 
- I create 'add_marker.sh' file
  - I create marker and marker initially be published at the pickup zone.
  - after 5 seconds, it should be hidden.
  - after another 5 seconds it should appear at the drop off zone.
- I create 'home_service.sh' file
  - the marker initially be published at the pickup zone.
  - Hide the marker when my robot reaches the pickup zone.
  - wait 5 seconds to pickup
  - the marker published at the drop off zone when my robot reaches infront of a man.
  

## Structure
    .
    ├── add_markers
    │   ├── CMakeLists.txt
    │   ├── config.yaml
    │   ├── launch
    │   ├── package.xml
    │   └── src
    ├── my_robot
    │   ├── CMakeLists.txt
    │   ├── config
    │   ├── launch
    │   ├── maps
    │   ├── meshes
    │   ├── package.xml
    │   ├── rviz
    │   ├── urdf
    │   └── worlds
    ├── pick_objects
    │   ├── CMakeLists.txt
    │   ├── config.yaml
    │   ├── launch
    │   ├── package.xml
    │   └── src
    ├── scripts
    │   ├── add_markers.sh
    │   ├── home_service.sh
    │   ├── pick_objects.sh
    │   ├── test_navigation.sh
    │   └── test_slam.sh
    ├── slam_gmapping
    │   ├── gmapping
    │   ├── README.md
    │   └── slam_gmapping
    └── turtlebot3
        ├── ISSUE_TEMPLATE.md
        ├── LICENSE
        ├── README.md
        ├── turtlebot3
        ├── turtlebot3_bringup
        ├── turtlebot3_description
        ├── turtlebot3_example
        ├── turtlebot3_navigation
        ├── turtlebot3_slam
        └── turtlebot3_teleop

## How to build and run Instructions.
1. clone this Project5 folder in the catkin_ws/src/ folder
      ```bash
   catkin_ws                      
      ├── src                         
      │   ├── Project5  
      │   │   ├── add_markers
      │   │   │──  ...
      └─ ...
   ```

2. Build dependencies:
    - I use **melodic** environment. -> please test in melodic
    - `rospkg`
      ```bash
      $ pip install rospkg
      ```
    
    - catkin_make
       ```bash
        $ cd /home/workspace/catkin_ws/
        $ catkin_make
        ```

    - Test SLAM
        ```bash
        $ cd /home/workspace/catkin_ws/
        $ src/Project5/scripts/test_slam.sh
        ```
    - Test Navigation
        ```bash
        $ cd /home/workspace/catkin_ws/
        $ src/Project5/scripts/test_navigation.sh
        ```
    - Pick Objects
        ```bash
        $ cd /home/workspace/catkin_ws/
        $ src/Project5/scripts/pick_objects.sh
        ```
    - Add markers
        ```bash
        $ cd /home/workspace/catkin_ws/
        $ src/Project5/scripts/add_markses.sh
        ```
    - Pick Objects
        ```bash
        $ cd /home/workspace/catkin_ws/
        $ src/Project5/scripts/home_service.sh
        ```
    
