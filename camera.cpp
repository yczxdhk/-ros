#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>

void semanticSegmentation(const sensor_msgs::Image::ConstPtr &msg) {
	cv_bridge::CvImagePtr cv_ptr    {
		// Convert ROS image message to OpenCV format
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::imageodings::BGR8);
	} catch (cv_bridge::Exception &e) {
ROS_ERROR_bridge exception:
		% e.what());
		return;
	}

	// Perform semantic segmentation on the color image
	cv::Mat segmented_img;  // You will need to implement this part

	cv::imshow("Segmented Image", segmented_img);
	cv::waitKey(1);
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "camera_viewer");
	ros::NodeHandle nh;

	// Subscribe to the color image topic
	ros::Subscriber color_image_sub = nh.subscribe("/camera/color/image_raw", 10, semanticSegmentation);

	ros::spin();

	return 0;
}
