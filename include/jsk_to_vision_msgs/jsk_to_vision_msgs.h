#ifndef JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED
#define JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED

// Headers in ROS
#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <vision_msgs/Detection2DArray.h>
#include <vision_msgs/Detection3DArray.h>
#include <jsk_recognition_msgs/RectArray.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

// Headers in Boost
#include <boost/optional.hpp>

// Headers in STL
#include <memory>

namespace jsk_to_vision_msgs
{
    typedef message_filters::sync_policies::ApproximateTime<jsk_recognition_msgs::RectArray, jsk_recognition_msgs::BoundingBoxArray> SyncPolicy;
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
        ros::Publisher detection2d_pub_,detection3d_pub_;
        std::shared_ptr<message_filters::Subscriber<jsk_recognition_msgs::RectArray> > cluster_rect_sub_;
        std::shared_ptr<message_filters::Subscriber<jsk_recognition_msgs::BoundingBoxArray> > cluster_bbox_sub_;
        std::shared_ptr<message_filters::Synchronizer<SyncPolicy> > sync_ptr_;
        void callback(const jsk_recognition_msgs::RectArray::ConstPtr jsk_rect,const jsk_recognition_msgs::BoundingBoxArray::ConstPtr jsk_bbox);
    };
}

#endif  //JSK_TO_VISION_MSGS_JSK_TO_VISION_MSGS_H_INCLUDED