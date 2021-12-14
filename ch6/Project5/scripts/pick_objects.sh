#!/bin/sh
xterm  -e  "source devel/setup.bash; roslaunch my_robot world.launch" &
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch my_robot amcl_demo.launch" &
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch pick_objects pick_objects.launch"