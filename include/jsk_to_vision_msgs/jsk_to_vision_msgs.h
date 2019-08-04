#ifndef JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED
#define JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED

// Headers in ROS
#include <ros/ros.h>
#include <vision_msgs/VisionInfo.h>
#include <vision_msgs/Detection2D.h>
#include <vision_msgs/Detection3D.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>
#include <jsk_recognition_msgs/ClassificationResult.h>

// Headers in Boost
#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

class JskToVisionMsgs
{
public:
    JskToVisionMsgs(ros::NodeHandle nh,ros::NodeHandle pnh);
    ~JskToVisionMsgs();
private:
    void visionInfoCallback(const vision_msgs::VisionInfo::ConstPtr msg);
    void detectionCallback(const vision_msgs::Detection3D::ConstPtr msg);
    void detectionCallback(const jsk_recognition_msgs::BoundingBoxArray::ConstPtr msg);
    bool convert_3d_detection_;
    std::string vision_info_topic_;
    boost::optional<std::map<int,std::string> > classes_;
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    ros::Subscriber vision_ingo_sub_;
};

#endif  //JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED