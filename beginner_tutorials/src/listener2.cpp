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
#include "pcl_ros/point_cloud.h"

void cloud_callback(const sensor_msgs::PointCloud2ConstPtr& laser_scan){
	std::cout<<"hello"<<std::endl;
}

 
int main (int argc, char** argv) {
 /*pcl::PointCloud<pcl::PointXYZ> pt_cloud;*/
 /*sensor_msgs::PointCloud cloud_msg;*/
 ros::init (argc, argv, "cloud_sub2");
 ros::NodeHandle nh;
 ros::Subscriber sub1;
 while (nh.ok()) {
   sub1 = nh.subscribe<sensor_msgs::PointCloud2> ("/laser_scan",0, cloud_callback);
   ros::spin();
 }
}
