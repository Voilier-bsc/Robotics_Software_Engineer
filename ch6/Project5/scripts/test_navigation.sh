#!/bin/sh
xterm  -e  "source /opt/ros/melodic/setup.bash; roscore" & 
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch my_robot world.launch" &
sleep 5
xterm  -e  "source devel/setup.bash; rosrun gmapping slam_gmapping scan:=scan _base_frame:=odom" &
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch my_robot amcl_demo.launch" 
