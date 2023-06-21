#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

using namespace std::placeholders;

class CVImagePublisher : public rclcpp::Node {
	public:
		CVImagePublisher() : Node("opencv_image_publisher") {
			subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
					"/camera/image_raw", 10, std::bind(&CVImagePublisher::imageCallback, this, _1));
		}

	private:
		void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
		{
			cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
			// TODO: Use the image for image processing
		}

		rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscriber_;
};

int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);
	auto node = std::make_shared<CVImagePublisher>();
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}


