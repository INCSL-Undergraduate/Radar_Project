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


sensor_msgs::PointCloud2 cloud_msg;
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
        pub_ = n_.advertise<sensor_msgs::PointCloud2>("trans_cloud", 10);
        sub_1 = n_.subscribe<sensor_msgs::PointCloud2> ("radar/target_list_cartesian",10,&PubAndSub::cloud_callback,this);
        sub_2 = n_.subscribe<nav_msgs::Odometry>("/odom",10,&PubAndSub::odom_callback,this);
        callback();
       
    }

    void cloud_callback (const sensor_msgs::PointCloud2ConstPtr& msg_c){
	cloud_msg=*msg_c;
	std::cout<<"cloud ok"<<std::endl;
	pub_.publish(cloud_msg);
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
