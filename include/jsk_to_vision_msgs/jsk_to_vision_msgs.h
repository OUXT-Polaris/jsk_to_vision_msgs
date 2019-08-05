#ifndef JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED
#define JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED

// Headers in ROS
#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <vision_msgs/VisionInfo.h>
#include <vision_msgs/Detection2D.h>
#include <vision_msgs/Detection3D.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>
#include <jsk_recognition_msgs/ClassificationResult.h>
#include <vision_info_server/vision_info_parser.h>

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
        void visionInfoCallback(const vision_msgs::VisionInfo::ConstPtr msg);
        void detectionCallback(const jsk_recognition_msgs::ClassificationResult::ConstPtr msg);
        void detectionCallback(const jsk_recognition_msgs::BoundingBoxArray::ConstPtr msg);
        bool convert_3d_detection_;
        std::string vision_info_topic_;
        boost::optional<std::map<int,std::string> > classes_;
        ros::NodeHandle nh_;
        ros::NodeHandle pnh_;
        ros::Subscriber vision_info_sub_;
        std::unique_ptr<vision_info_parser::VisionInfoParser> parser_ptr_;
    };
}

#endif  //JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED