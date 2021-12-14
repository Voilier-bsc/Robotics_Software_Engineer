#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle nh;
    ros::Rate r(1);
    ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;

    // set pick, drop nodes
    double PICK_UP_X;
    double PICK_UP_Y;
    double DROP_OFF_X;
    double DROP_OFF_Y;

    std::string node_name = ros::this_node::getName();

    nh.getParam(node_name + "/PICK_UP_X", PICK_UP_X);
    nh.getParam(node_name + "/PICK_UP_Y", PICK_UP_Y);
    nh.getParam(node_name + "/DROP_OFF_X", DROP_OFF_X);
    nh.getParam(node_name + "/DROP_OFF_Y", DROP_OFF_Y);


    visualization_msgs::Marker marker;

    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = PICK_UP_X;
    marker.pose.position.y = PICK_UP_Y;
    marker.pose.position.z = 0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
        if (!ros::ok())
            return 0;
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);
    }
    // Publish the marker at the pickup zone
    marker_pub.publish(marker);

    // Pause 5 seconds
    ros::Duration(5).sleep();

    // Hide the marker
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);

    // Pause 5 seconds
    ros::Duration(5).sleep();

    // Publish the marker at the drop off zone
    marker.pose.position.x = DROP_OFF_X;
    marker.pose.position.y = DROP_OFF_Y;
    marker.pose.position.z = 0;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    
    r.sleep();

}