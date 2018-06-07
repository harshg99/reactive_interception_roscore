#include <iostream>
#include <iomanip>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<ros/ros.h>
#include <opencv2/core/ocl.hpp>







using namespace std;

int main(int argc, char **argv){

  ros::init(argc,argv,"gpu_detect");
  cv::ocl::Context context;
  if(!context.create(cv::ocl::Device::TYPE_GPU)){
    ROS_INFO("Failed to create context");
    return 0;
  }

  cv::ocl::Device device;
  ROS_INFO("%d GPU devices are detected.", context.ndevices());


 for (int i = 0; i < context.ndevices(); i++)
     {
     cv::ocl::Device device = context.device(i);
     ROS_INFO("name                 :%d\n " , device.name());
     ROS_INFO("available            :%d\n " , device.available());
     ROS_INFO("imageSupport         :%d\n " , device.imageSupport());
     ROS_INFO("OpenCL_C_Version     :%d\n " , device.OpenCL_C_Version());
     break;
    }
 return 1;
}
