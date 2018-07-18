#include<ros/ros.h>
#include<ios>
#include<stdlib.h>
#include<stdio.h>
#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <fstream>

static std::string OPENCV_WINDOW="window_train";
class Trainer
   {
     ros::NodeHandle nh_;
     image_transport::ImageTransport it_;
     image_transport::Subscriber image_sub_;
     image_transport::Publisher image_pub_;
     int count;
     int lat;
     int option;
     std::ofstream output;
   public:
     Trainer(int k)
       : it_(nh_)
     {
       // Subscrive to input video feed and publish output video feed
       image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1,
         &Trainer::imageCb, this);
       image_pub_ = it_.advertise("/image_converter/output_video", 1);


       cv::namedWindow(OPENCV_WINDOW);
       count=0;
       lat=0;
       option=k;
       if(option==1){
       output.open("/home/harsh/dataset/annot_data/posinfo.dat");
       }
       else{
       output.open("/home/harsh/dataset/annot_data/bg.txt");
       }
     }

     ~Trainer()
     {
       cv::destroyWindow(OPENCV_WINDOW);
     }

     void imageCb(const sensor_msgs::ImageConstPtr& msg)
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

       // Draw an example circle on the video stream
      // if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
     //    cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

       // Update GUI Window
      std::stringstream ss;


      cv::Mat frame_gray;
      if(option==1){
      cv::Rect train_box;
      train_box.x=240;
      train_box.y=180;
      train_box.height=192;
      train_box.width=192;
      cv::rectangle(cv_ptr->image,train_box,cv::Scalar(0,0,255));
      cv::waitKey(3);

      cv::cvtColor(cv_ptr->image, frame_gray, cv::COLOR_BGR2GRAY );
      cv::imshow(OPENCV_WINDOW,frame_gray);
      if(lat>200 && lat<=1200)
      {
      ss<<"/home/harsh/dataset/ball/ball"<<count<<".jpg";
      count++;
      output<<ss.str()<<" 1 0 0 192 192\n";
      cv::imwrite(ss.str(),frame_gray);
      }
      else{
        ROS_INFO("TAKEN\N");
      }
      }
      else{
       cv::waitKey(3);
       cv::Mat frame_gray;
       cv::cvtColor(cv_ptr->image, frame_gray, cv::COLOR_BGR2GRAY );
       cv::imshow(OPENCV_WINDOW,frame_gray);
       if(count<3000){
       ss<<"/home/harsh/dataset/background/back"<<count<<".jpg";
       count++;
       output<<ss.str()<<"\n";
       cv::imwrite(ss.str(),frame_gray);
      }
       else{
         ROS_INFO("TAKEN\N");
       }
      }
       lat++;
     }

};


int main(int argc, char** argv)
{

     ros::init(argc, argv, "image_train");
     int option;
     printf("Positive Images or Negative Images \n");
     std::cin>>option;

     Trainer ic(option);
     ros::spin();
     return 0;
}
