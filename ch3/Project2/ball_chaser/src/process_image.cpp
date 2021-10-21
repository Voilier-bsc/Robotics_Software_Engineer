#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if(!client.call(srv))
        ROS_ERROR("Failed to call service");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img) //800 X 800
{

    int white_pixel = 255;
    int i;
    int col, row;
    int flag = 0;

    for(i=0; i < img.height * img.step; i+=3){
        if(img.data[i] + img.data[i+1] + img.data[i+2] == white_pixel*3){
            row = i / img.step;
            col = (i - img.step*row)/3;
            
            // ROS_INFO("white pixel num is : %d , %d", row, col);
            flag =1;

            if(flag==1 && col < img.width/3){
                drive_robot(0.0, 0.5);
                break;
            }

            if(flag==1 && col > img.width/3 && col < 2*img.width/3){
                drive_robot(0.5, 0.0);
                break;
            }

            if(flag==1 && col > 2*img.width/3){
                drive_robot(0.0, -0.5);
                break;
            }
        }
    }
    
    if(flag == 0){
        ROS_INFO("Can't find white ball");
        drive_robot(0.0, 0.0);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}