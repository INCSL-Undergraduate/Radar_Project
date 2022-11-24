#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>
#include <iostream>
#include <pcl/conversions.h>
#include "nav_msgs/Odometry.h"

void cloud_callback (const sensor_msgs::PointCloud2ConstPtr& cloud_msg){

}

void odom_callback(const nav_msgs::Odometry::ConstPtr& msg){
 ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
}

 
int main (int argc, char** argv) {
 /*pcl::PointCloud<pcl::PointXYZ> pt_cloud;*/
 ros::init (argc, argv, "cloud_sub");
 ros::NodeHandle nh;
 ros::Subscriber sub1;
 ros::Subscriber sub2;
 while (nh.ok()) {
   sub1 = nh.subscribe<sensor_msgs::PointCloud2> ("radar/target_list_cartesian",10, cloud_callback);
   sub2 = nh.subscribe<nav_msgs::Odometry>("/odom",10,odom_callback);
   ros::spin();
 }
}
