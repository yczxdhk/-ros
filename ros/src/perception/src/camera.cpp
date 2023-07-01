#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

void colorImageCallback(const sensor_msgs::Image::ConstPtr &msg) {

	cv_bridge::CvImagePtr cv_ptr;
	try {
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	} catch (cv_bridge::Exception &e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}


	cv::imshow("Color Image", cv_ptr->image);
	cv::waitKey(1);
}

void depthImageCallback(const sensor_msgs::Image::ConstPtr &msg) {

	cv::Mat depth_img = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::TYPE_32FC1)->image;


	cv::imshow("Depth Image", depth_img);
	cv::waitKey(1);
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "camera_viewer");


	ros::NodeHandle nh;

	ros::Subscriber color_image_sub = nh.subscribe("/camera/color/image_raw", 10, colorImageCallback);
	ros::Subscriber depth_image_sub = nh.subscribe("/camera/depth/image_rect_raw", 10, depthImageCallback);

	ros::spin();

	return 0;
}
