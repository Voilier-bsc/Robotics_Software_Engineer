#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
    // Initialize the simple_navigation_goals node
    ros::init(argc, argv, "pick_objects");

    // tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    // Wait 5 sec for move_base action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    double PICK_UP_X;
    double PICK_UP_Y;
    double DROP_OFF_X;
    double DROP_OFF_Y;


    ros::NodeHandle nh;

    std::string node_name = ros::this_node::getName();
    nh.getParam(node_name + "/PICK_UP_X", PICK_UP_X);
    nh.getParam(node_name + "/PICK_UP_Y", PICK_UP_Y);
    nh.getParam(node_name + "/DROP_OFF_X", DROP_OFF_X);
    nh.getParam(node_name + "/DROP_OFF_Y", DROP_OFF_Y);



    move_base_msgs::MoveBaseGoal goal;

    // set up the frame parameters
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    // Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = PICK_UP_X;
    goal.target_pose.pose.position.y = PICK_UP_Y;
    goal.target_pose.pose.orientation.z = 0.7071081;
    goal.target_pose.pose.orientation.w = 0.7071081;

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);    

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("Robot picked up the virtual object");
        ros::Duration(5.0).sleep();

        /********************* Move to the desired dropoff zone *********************/
        // Define a position and orientation for the robot to reach
        goal.target_pose.pose.position.x = DROP_OFF_X;
        goal.target_pose.pose.position.y = DROP_OFF_Y;
        goal.target_pose.pose.orientation.z = 0.7071081;
        goal.target_pose.pose.orientation.w = 0.7071081;

        // Send the goal position and orientation for the robot to reach
        ROS_INFO("Robot is traveling to the drop off zone");
        ac.sendGoal(goal);    

         // Wait an infinite time for the results
        ac.waitForResult();

        // Check if the robot reached its goal
        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            ROS_INFO("Robot dropped the virtual object");
        else
            ROS_INFO("The base failed to move to dropoff zone");
    }

    else
        ROS_INFO("The base failed to move to pickup zone");

    return 0;
}