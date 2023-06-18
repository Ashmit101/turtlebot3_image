#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

using std::placeholders::_1;

class RawImageSubscriber : public rclcpp::Node
{
	public:
		RawImageSubscriber() : Node("raw_image_subscriber")
	{
		subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
				"/camera/image_raw", 10, std::bind(&RawImageSubscriber::imageCallback, this, _1));
	}

		private:
		void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
			{
				RCLCPP_INFO(this->get_logger(), "Received image with height: %d, width: %d", msg->height, msg->width);
			}

		rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);
	auto node = std::make_shared<RawImageSubscriber>();
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}

