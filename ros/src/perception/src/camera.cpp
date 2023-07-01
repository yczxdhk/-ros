#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/Image.h>




void depth(const sensor_msgs::Image::ConstPtr &msg) {

	cv::Mat depth_img = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::TYPE_32FC1)->image;


	cv::imshow("Depth Image", depth_img);
	cv::waitKey(1);
}


void color(const sensor_msgs::Image::ConstPtr &msg) {

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


int main(int argc, char **argv) {
	ros::init(argc, argv, "camera_viewer");


	ros::NodeHandle nh;

	ros::Subscriber color_image_sub = nh.subscribe("/camera/color/image_raw", 10, color);
	ros::Subscriber depth_image_sub = nh.subscribe("/camera/depth/image_rect_raw", 10, depth);

	ros::spin();

	return 0;
}
