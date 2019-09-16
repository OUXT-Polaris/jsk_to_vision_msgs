#ifndef JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED
#define JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED

// Headers in ROS
#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <vision_msgs/Detection2DArray.h>
#include <jsk_recognition_msgs/RectArray.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>

// Headers in Boost
#include <boost/optional.hpp>

// Headers in STL
#include <memory>

namespace jsk_to_vision_msgs
{
    class JskToVisionMsgs: public nodelet::Nodelet
    {
    protected:
        void onInit();
    private:
        void rectArrayCallback(const jsk_recognition_msgs::RectArray::ConstPtr msg);
        ros::NodeHandle nh_;
        ros::NodeHandle pnh_;
        ros::Subscriber rect_array_sub_;
        std::string rect_array_topic_;
        ros::Publisher detection_pub_;
    };
}

#endif  //JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED