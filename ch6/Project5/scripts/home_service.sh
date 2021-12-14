#!/bin/sh
xterm  -e  "source devel/setup.bash; roslaunch my_robot worldwoRviz.launch" &
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch my_robot amcl_demo.launch" &
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch add_markers add_markers_2.launch" &
sleep 5
xterm  -e  "source devel/setup.bash; roslaunch pick_objects pick_objects.launch"