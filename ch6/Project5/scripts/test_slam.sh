#!/bin/sh
xterm  -e  "source devel/setup.bash; roslaunch my_robot world.launch" &
sleep 5
xterm  -e  "source devel/setup.bash; rosrun gmapping slam_gmapping scan:=scan _base_frame:=odom" &
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch" 