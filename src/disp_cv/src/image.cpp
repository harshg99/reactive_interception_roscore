

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/CameraInfo.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <disp_cv/cv_defs_xtion.h>





int main(int argc, char** argv)
{
     ros::init(argc, argv, "image");


     ImageConverter ic;


     ros::spin();
     return 0;
}



