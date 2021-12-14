#!/bin/sh
xterm  -e  "source devel/setup.bash; roslaunch my_robot worldwoRviz.launch" &
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch my_robot amcl_demo.launch" &
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch add_markers add_markers_1.launch"