#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>

void pointCloudCallback(const sensor_msgs::PointCloud2ConstPtr &msg) {
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::fromROSMsg(*msg, *cloud);

	// 进行语义分割算法（示例：平面分割）
	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
	pcl::SACSegmentation<pcl::PointXYZRGB> seg;
	seg.setOptimizeCoefficients(true);
	seg.setModelType(pcl::SACMODEL_PLANE);
	seg.setMethodType(pcl::SAC_RANSAC);
	seg.setInputCloud(cloud);
	seg.segment(*inliers, *coefficients);

	// 提取分割结果
	pcl::PointCloud<pclPointXYZRGB>::Ptr segmented_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::ExtractIndices<pcl::PointXYZRGB> extract;
	extract.setInputCloud(cloud);
	extract.setIndices(inliers);
	extract.setNegative(false);
	extract.filter(*segmented_cloud);

	// 可以在此处执行其他的语义分割操作

	// 输出分割后的点云信息
	ROS_INFO("Segmented Point Cloud Size: %lu", segmented_cloud->size());
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "semantic_segmentation_subscriber");
	::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("/camera/point_cloud",, pointCloudCallback::spin();

	                                   return 0;
}
