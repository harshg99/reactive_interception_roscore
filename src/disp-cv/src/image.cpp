#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>

using namespace std;

static const string OPENCV_WINDOW = "Image window";

class ImageConverter
   {
     ros::NodeHandle nh_;
     image_transport::ImageTransport it_;
     image_transport::Subscriber image_sub_;
     image_transport::Publisher image_pub_;

   public:
     ImageConverter()
       : it_(nh_)
     {
       // Subscrive to input video feed and publish output video feed
       image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1,
         &ImageConverter::imageCb, this);
       image_pub_ = it_.advertise("/image_converter/output_video", 1);

       cv::namedWindow(OPENCV_WINDOW);
     }

     ~ImageConverter()
     {
       cv::destroyWindow(OPENCV_WINDOW);
     }

     void imageCb(const sensor_msgs::ImageConstPtr& msg)
     {
       cv::TickMeter tm;
       tm.start();
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

       cv::waitKey(3);
       string face_cascade_name="/opt/ros/kinetic/share/OpenCV-3.3.1-dev/haarcascades/haarcascade_frontalface_alt.xml";
       cv::CascadeClassifier face_cascade;
         if( !face_cascade.load( face_cascade_name ) )
         { ROS_INFO("--(!)Error loading face cascade\n");
           return ;
         };

         std::vector<cv::Rect> faces;
         cv::Mat frame_gray;
         cv::cvtColor( cv_ptr->image, frame_gray, cv::COLOR_BGR2GRAY );
         cv::equalizeHist( frame_gray, frame_gray );
         face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
         for(size_t i=0 ;i <faces.size();i++){
           cv::rectangle(cv_ptr->image,faces[i],cv::Scalar(0,0,255));
         }
       // Output modified video stream

       image_pub_.publish(cv_ptr->toImageMsg());
        cv::imshow(OPENCV_WINDOW,cv_ptr->image);
        tm.stop();
        ROS_INFO("Time Taken for display: %lf ms",tm.getTimeMilli());
     }
   };

   int main(int argc, char** argv)
   {
     ros::init(argc, argv, "image");

     ImageConverter ic;

     ros::spin();
       return 0;
   }
