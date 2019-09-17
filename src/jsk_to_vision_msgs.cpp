#include <jsk_to_vision_msgs/jsk_to_vision_msgs.h>

namespace jsk_to_vision_msgs
{
    void JskToVisionMsgs::onInit()
    {
        nh_ = getNodeHandle();
        pnh_ = getPrivateNodeHandle();
        detection2d_pub_ = pnh_.advertise<vision_msgs::Detection2DArray>("output/detection_2d",1);
        detection3d_pub_ = pnh_.advertise<vision_msgs::Detection3DArray>("output/detection_3d",1);
        cluster_rect_sub_ = std::make_shared<message_filters::Subscriber<jsk_recognition_msgs::RectArray> >(pnh_, "input/rect", 10);
        cluster_bbox_sub_ = std::make_shared<message_filters::Subscriber<jsk_recognition_msgs::BoundingBoxArray> >(pnh_, "input/bbox", 10);
        sync_ptr_ = std::make_shared<message_filters::Synchronizer<SyncPolicy> >(SyncPolicy(10), *cluster_rect_sub_ , *cluster_bbox_sub_);
        sync_ptr_->registerCallback(boost::bind(&JskToVisionMsgs::callback, this, _1, _2));
    }

    void JskToVisionMsgs::callback(const jsk_recognition_msgs::RectArray::ConstPtr jsk_rect,const jsk_recognition_msgs::BoundingBoxArray::ConstPtr jsk_bbox)
    {
        vision_msgs::Detection2DArray detection2d_msg;
        detection2d_msg.header = jsk_rect->header;
        for(auto itr = jsk_rect->rects.begin(); itr != jsk_rect->rects.end(); itr++)
        {
            vision_msgs::Detection2D detection;
            detection.header = jsk_rect->header;
            detection.bbox.center.theta = 0;
            detection.bbox.center.x = (double)itr->x+0.5*(double)itr->width;
            detection.bbox.center.y = (double)itr->y+0.5*(double)itr->height;
            detection.bbox.size_x = (double)itr->width;
            detection.bbox.size_y = (double)itr->height;
            detection.is_tracking = false;
            detection.detection_id = unique_id::toMsg(unique_id::fromRandom());
            detection2d_msg.detections.push_back(detection);
        }
        vision_msgs::Detection3DArray detection3d_msg;
        detection3d_msg.header = jsk_bbox->header;
        for(auto itr = jsk_bbox->boxes.begin(); itr != jsk_bbox->boxes.end(); itr++)
        {
            vision_msgs::Detection3D detection;
            detection.header = jsk_bbox->header;
            detection.bbox.center = itr->pose;
            detection.bbox.size = itr->dimensions;
            detection.detection_id = unique_id::toMsg(unique_id::fromRandom());
            detection3d_msg.detections.push_back(detection);
        }
        detection2d_pub_.publish(detection2d_msg);
        detection3d_pub_.publish(detection3d_msg);
    }
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(jsk_to_vision_msgs::JskToVisionMsgs,nodelet::Nodelet);