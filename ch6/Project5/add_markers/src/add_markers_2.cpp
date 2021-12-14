#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

#define thres 0.3

class Subs_Pub
{
private:

    double PICK_UP_X;
    double PICK_UP_Y;
    double DROP_OFF_X;
    double DROP_OFF_Y;
    

    bool pickup_reached = false;

    // to subscribe odometry
    ros::Subscriber odom_sub;

    // to publish markers
    ros::Publisher marker_pub;

    ros::NodeHandle nh;
    visualization_msgs::Marker marker;

    uint32_t shape = visualization_msgs::Marker::CUBE;

    double calculate_d(double x_1, double y_1, double x_2, double y_2)
    {
        return sqrt(pow((x_1-x_2), 2) + pow((y_1-y_2), 2));
    }
    
public:
    Subs_Pub();
    void odom_callback(const nav_msgs::Odometry odom);
};



Subs_Pub::Subs_Pub()
{
    // set parameters
    std::string node_name = ros::this_node::getName();

    nh.getParam(node_name + "/PICK_UP_X", PICK_UP_X);
    nh.getParam(node_name + "/PICK_UP_Y", PICK_UP_Y);
    nh.getParam(node_name + "/DROP_OFF_X", DROP_OFF_X);
    nh.getParam(node_name + "/DROP_OFF_Y", DROP_OFF_Y);

    marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // subscibe odometry    
    odom_sub = nh.subscribe("/odom", 10, &Subs_Pub::odom_callback, this);    

    uint32_t shape = visualization_msgs::Marker::CUBE;

    // Set marker parameters
    marker.header.stamp = ros::Time::now();
    marker.header.frame_id = "map";

    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.pose.position.x = PICK_UP_X;
    marker.pose.position.y = PICK_UP_Y;
    marker.pose.position.z = 0;

    marker.ns = "add_markers";
    marker.id = 0;

    marker.type = shape;
    marker.action = visualization_msgs::Marker::ADD;
    marker.lifetime = ros::Duration();

    // Publish the markers
    while (marker_pub.getNumSubscribers() < 1)
    {
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);
    }
    marker_pub.publish(marker);
}

void Subs_Pub::odom_callback(const nav_msgs::Odometry odom)
{
    double robot_pose_x = odom.pose.pose.position.x;
    double robot_pose_y = odom.pose.pose.position.y;

    double pickup_distance = calculate_d(robot_pose_x, robot_pose_y, PICK_UP_X, PICK_UP_Y);
    double dropoff_distance = calculate_d(robot_pose_x, robot_pose_y, DROP_OFF_X, DROP_OFF_Y);


    if (pickup_distance < thres)
    {
        pickup_reached = true;

        marker.header.stamp = ros::Time::now();

        marker.pose.position.x = PICK_UP_X;
        marker.pose.position.y = PICK_UP_Y;
        marker.pose.position.z = 0;

        marker.action = visualization_msgs::Marker::DELETE;

        marker.lifetime = ros::Duration();

        // Publish the markers
        marker_pub.publish(marker);
    }

    if (pickup_reached == true && dropoff_distance < thres)
    {
        marker.header.stamp = ros::Time::now();

        marker.pose.position.x = DROP_OFF_X;
        marker.pose.position.y = DROP_OFF_Y;
        marker.pose.position.z = 0;

        marker.action = visualization_msgs::Marker::ADD;

        marker.lifetime = ros::Duration();
        // Publish the markers
        marker_pub.publish(marker);
    }    
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    Subs_Pub SP;
    ros::spin();

    return 0;
}