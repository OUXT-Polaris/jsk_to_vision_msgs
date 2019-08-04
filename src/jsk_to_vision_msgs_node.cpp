// Headers in this package
#include <jsk_to_vision_msgs/jsk_to_vision_msgs.h>

// Headers in ROS
#include <ros/ros.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "jsk_to_vision_msgs_node");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");
    JskToVisionMsgs converter(nh,pnh);
    ros::spin();
    return 0;
}