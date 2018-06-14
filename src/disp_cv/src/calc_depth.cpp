
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/CameraInfo.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <disp_cv/depth_calc.h>


int main(int argc, char** argv)
{
     ros::init(argc, argv, "calc_depth");


     depth d;


     ros::spin();
     return 0;
}
