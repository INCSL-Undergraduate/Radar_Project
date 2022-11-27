**Use master branch**

PointCloud2 -> PointCloud1 -> using wheel odom, Radar SLAM , no optimizer   

1) catkin_make
2) source ./devel/setup.bash (gedit ./~bashrc, 맨 아랫줄에 source ~/너의 ws/devel/steup.bash)
3) rosrun be[Tab] tr[Tab]
4) rviz 
5) rviz config - frame: radar, add: pointcloud 2말고 POINTCLOUD
6) rosbag play [너의 파일 위치로 들어가서] [파일 이름].bag
7) rviz 보기 (
