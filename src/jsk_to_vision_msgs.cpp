#include <jsk_to_vision_msgs/jsk_to_vision_msgs.h>

JskToVisionMsgs::JskToVisionMsgs(ros::NodeHandle nh,ros::NodeHandle pnh)
{
    nh_ = nh;
    pnh_ = pnh;
    pnh_.param<bool>("convert_3d_detection", convert_3d_detection_, false);
    pnh_.param<std::string>("vision_info_topic", vision_info_topic_, "vision_info");
}

JskToVisionMsgs::~JskToVisionMsgs()
{

}

void JskToVisionMsgs::visionInfoCallback(const vision_msgs::VisionInfo::ConstPtr msg)
{
    std::string class_meta_str;
    nh_.param<std::string>(msg->database_location, class_meta_str, "");
    std::stringstream ss;
    ss << class_meta_str;
    using namespace boost::property_tree;
    ptree pt;
    std::map<int,std::string> classes;
    read_xml(ss, pt);
    BOOST_FOREACH (const ptree::value_type& child, pt.get_child("vision_info"))
    {
        if(child.first == "class")
        {
            boost::optional<int> id = child.second.get_optional<int>("<xmlattr>.id");
            boost::optional<std::string> name = child.second.get_optional<std::string>("<xmlattr>.name");
            if(id && name)
            {
                classes[*id] = *name;
            }
            else
            {
                ROS_ERROR_STREAM("failed to read xml string");
                std::exit(-1);
            }
        }
    }
    classes_ = classes;
    return;
}