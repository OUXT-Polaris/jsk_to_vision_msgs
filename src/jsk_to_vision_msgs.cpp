#include <jsk_to_vision_msgs/jsk_to_vision_msgs.h>

namespace jsk_to_vision_msgs
{
    void JskToVisionMsgs::onInit()
    {
        nh_ = getNodeHandle();
        pnh_ = getPrivateNodeHandle();
        pnh_.param<bool>("convert_3d_detection", convert_3d_detection_, false);
        pnh_.param<std::string>("vision_info_topic", vision_info_topic_, "vision_info");
        parser_ptr_ = std::unique_ptr<vision_info_parser::VisionInfoParser>(new vision_info_parser::VisionInfoParser(nh_));
        if(convert_3d_detection_)
        {

        }
        vision_info_sub_ = nh_.subscribe(vision_info_topic_,1,&JskToVisionMsgs::visionInfoCallback,this);
    }

    void JskToVisionMsgs::detectionCallback(const jsk_recognition_msgs::ClassificationResult::ConstPtr msg)
    {

    }

    void JskToVisionMsgs::detectionCallback(const jsk_recognition_msgs::BoundingBoxArray::ConstPtr msg)
    {

    }

    void JskToVisionMsgs::visionInfoCallback(const vision_msgs::VisionInfo::ConstPtr msg)
    {
        parser_ptr_->parseFromRosMessage(*msg);
        classes_ = parser_ptr_->getClasses();
    }
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(jsk_to_vision_msgs::JskToVisionMsgs,nodelet::Nodelet);