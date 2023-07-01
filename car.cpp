#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

void pointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr &msg) {
	// ת��ΪPCL���Ƹ�ʽ
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::fromROSMsg(*msg, *cloud);

	// ִ����ά�ؽ��㷨��ʾ�����򵥵����ػ��˲���
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::VoxelGrid<pcl::PointXYZRGB> voxel_grid;
	voxel_grid.setInputCloud(cloud);
	voxel_grid.setLeafSize(0.01f, 0.01f, 0.01f);
	voxel_grid.filter(*filtered_cloud);

	// �����ڴ˴�ִ����������ά�ؽ�����

	// ����ؽ���ĵ�����Ϣ
	ROS_INFO("Reconstructed Point Cloud Size: %lu", filtered_cloud->size());
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "point_cloud_subscriber");
	ros::NodeHandle nh;

	// ���ĵ��ƻ���
	ros::Subscriber point_cloud_sub = nh.subscribe("/camera/point_cloud", 1, pointCloudCallback);

	ros::spin();

	return 0;
}
