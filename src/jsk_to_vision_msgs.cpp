#include <jsk_to_vision_msgs/jsk_to_vision_msgs.h>

namespace jsk_to_vision_msgs
{
    void JskToVisionMsgs::onInit()
    {
        nh_ = getNodeHandle();
        pnh_ = getPrivateNodeHandle();
        detection_pub_ = pnh_.advertise<vision_msgs::Detection2DArray>("output",1);
        rect_array_sub_ = pnh_.subscribe("input",1,&JskToVisionMsgs::rectArrayCallback,this);
    }

    void JskToVisionMsgs::rectArrayCallback(const jsk_recognition_msgs::RectArray::ConstPtr msg)
    {
        vision_msgs::Detection2DArray detection_msg;
        detection_msg.header = msg->header;
        for(auto itr = msg->rects.begin(); itr != msg->rects.end(); itr++)
        {
            vision_msgs::Detection2D detection;
            detection.header = msg->header;
            detection.bbox.center.theta = 0;
            detection.bbox.center.x = (double)itr->x+0.5*(double)itr->width;
            detection.bbox.center.y = (double)itr->y+0.5*(double)itr->height;
            detection.bbox.size_x = (double)itr->width;
            detection.bbox.size_y = (double)itr->height;
            detection.is_tracking = false;
            detection_msg.detections.push_back(detection);
        }
        detection_pub_.publish(detection_msg);
    }
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(jsk_to_vision_msgs::JskToVisionMsgs,nodelet::Nodelet);