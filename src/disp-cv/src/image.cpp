#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>

using namespace std;

static const string OPENCV_WINDOW = "Image window";

class detect
    {
        private:
            string cascade_name;
            cv::CascadeClassifier cascade;
            std::vector<cv::Rect> boxes;
        public:
            //default:detect face
            detect(){
                cascade_name="/opt/ros/kinetic/share/OpenCV-3.3.1-dev/lbpcascades/lbpcascade_frontalface.xml";
                  if( !cascade.load( cascade_name ) )
                  { ROS_INFO("--(!)Error loading face cascade\n");
                    return ;
                  };
            }
            //your haar cascade
            detect(string casacde_name){
                casacde_name=this->cascade_name;
                if( !cascade.load( cascade_name ) )
                { ROS_INFO("--(!)Error loading face cascade\n");
                  return ;
                };
            }
            void find_object_cpu(cv::Mat frame ){

                cv::Mat frame_gray;
                cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );

                cv::equalizeHist( frame_gray, frame_gray );
                cascade.detectMultiScale( frame_gray, boxes, 1.2, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(20, 20),cv::Size(200,200) );


                disp_boxes(frame);
            }
            void find_object_gpu(cv::Mat frame ){

                cv::UMat frame_gray,frame2;
                frame.copyTo(frame2);

                cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );

                cv::equalizeHist( frame_gray, frame_gray );
                cascade.detectMultiScale( frame_gray, boxes, 1.2, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(20, 20),cv::Size(200,200) );
                disp_boxes(frame);
            }
            void disp_boxes(cv::Mat frame){
                for(size_t i=0 ;i <boxes.size();i++){
                  cv::rectangle(frame,boxes[i],cv::Scalar(0,0,255));
                }

                cv::imshow(OPENCV_WINDOW,frame);

            }

    };
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
      /* string face_cascade_name="/opt/ros/kinetic/share/OpenCV-3.3.1-dev/lbpcascades/lbpcascade_frontalface.xml";
       cv::CascadeClassifier face_cascade;
         if( !face_cascade.load( face_cascade_name ) )
         { ROS_INFO("--(!)Error loading face cascade\n");
           return ;
         };*/

         //std::vector<cv::Rect> faces;
         //cv::Mat frame_gray;
         detect face=detect();
         face.find_object_gpu(cv_ptr->image);
         //gpu
         //cv::UMat frame_gray,frame;
         //cv_ptr->image.copyTo(frame);


        // cv::cvtColor( cv_ptr->image, frame_gray, cv::COLOR_BGR2GRAY );

         //gpu
         //cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
/*
         cv::equalizeHist( frame_gray, frame_gray );
         face_cascade.detectMultiScale( frame_gray, faces, 1.2, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(20, 20),cv::Size(200,200) );
         for(size_t i=0 ;i <faces.size();i++){
           cv::rectangle(cv_ptr->image,faces[i],cv::Scalar(0,0,255));
         }
       // Output modified video stream
*/
       image_pub_.publish(cv_ptr->toImageMsg());

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
