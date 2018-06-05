#include<ros/ros.h>
#include<std_msgs/String.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include<image_transport/image_transport.h>
#include<sensor_msgs/image_encodings.h>
using namespace std;
static const string OPENCV_WINDOW = "Image window";

class ImageConverter{
private:
    ros::NodeHandle nh;
    image_transport::ImageTransport it;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;

public:
    //Proc-0 FOR CPU
    //Proc-1 FOR GPU

    ImageConverter():it(nh)
    {
      // Subscrive to input video feed and publish output video feed
      image_sub_ = it.subscribe("/camera/rgb/image_raw", 1,
        &ImageConverter::imageCbCPU, this);
     image_pub_ = it.advertise("/image_converter/output_video", 1);
      cv::namedWindow(OPENCV_WINDOW);

    }
    ~ImageConverter()
    {
      cv::destroyWindow(OPENCV_WINDOW);
    }

    void imageCbCPU(const sensor_msgs::ImageConstPtr& msg)
    {
      cv_bridge::CvImagePtr cv_ptr;
      try
      {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      }
      catch (cv_bridge::Exception& e)
      {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
      }
      image_pub_.publish(cv_ptr->toImageMsg());
      cv::imshow(OPENCV_WINDOW,cv_ptr->image);
    }
};

int main(int argc,char **argv ){
    ros::init(argc,argv,"cpu_display");
    //cv::TickMeter tick;
    //tick.start();
    ImageConverter images;
   // ROS_INFO("Time Taken for display: %lf ms",tick.getTimeMilli());
    //tick.stop();
    ros::spin();
    return 0;
}


