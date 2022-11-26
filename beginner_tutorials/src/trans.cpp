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
#include <sensor_msgs/point_cloud_conversion.h>

sensor_msgs::PointCloud2 cloud_msg;
sensor_msgs::PointCloud out_cloud;
nav_msgs::Odometry odom_ekf;


class PubAndSub
{
private:
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Subscriber sub_1;
    ros::Subscriber sub_2;

public:

    PubAndSub()
    {
        pub_ = n_.advertise<sensor_msgs::PointCloud>("out_cloud", 10);
        sub_1 = n_.subscribe<sensor_msgs::PointCloud2> ("radar/target_list_cartesian",10,&PubAndSub::cloud_callback,this);
        sub_2 = n_.subscribe<nav_msgs::Odometry>("/odom",10,&PubAndSub::odom_callback,this);
        callback();
       
    }

    void cloud_callback (const sensor_msgs::PointCloud2ConstPtr& msg_c){
	cloud_msg=*msg_c;
	std::cout<<"cloud Ok"<<std::endl;
	sensor_msgs::convertPointCloud2ToPointCloud(cloud_msg, out_cloud);
	geometry_msgs::Point32 point;
	
	for(int i = 0 ; i < out_cloud.points.size();i++){
	std::cout<<"TRANS OK"<<std::endl;
	out_cloud.points[i].x = out_cloud.points[i].x + odom_ekf.pose.pose.position.x*100;
	out_cloud.points[i].y = out_cloud.points[i].y + odom_ekf.pose.pose.position.y*100;
	out_cloud.points[i].z = out_cloud.points[i].z + odom_ekf.pose.pose.position.z*100;
	}
	
	pub_.publish(out_cloud);
	}
	
    void odom_callback(const nav_msgs::Odometry::ConstPtr& msg_o){
	odom_ekf = *msg_o;
	std::cout<<"odom ok"<<std::endl;
	}
    
    void callback(){
       std::cout<<"trans ok"<<std::endl;
       }  
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "multi_node");
    PubAndSub PAS;
    ros::spin();
    return 0;
}
