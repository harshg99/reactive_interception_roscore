


#ifndef CV_DEFS_XTION_H
#define CV_DEFS_XTION_H



#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/CameraInfo.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <disp_cv/box.h>
#include <disp_cv/multibox.h>


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
            detect(string cascade_name){
                this->cascade_name=cascade_name;
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
            std::vector<cv::Rect> retBoxes()
            {
              return boxes;
            }

    };
class publishBox{

  public:
    ros::Publisher pub;
    publishBox(){}
    publishBox(ros::NodeHandle nh_){
       pub =nh_.advertise<disp_cv::multibox>("/bounding_boxes",1);
    }
    void publish(std::vector<cv::Rect> allboxes){
     //ros::NodeHandle node;
     //ros::Rate rate(30);
    // pub=n.advertise<disp_cv::multibox>("/bounding_boxes",1);
     std::vector<cv::Rect> boxes= allboxes;
     disp_cv::multibox k;
     if(!boxes.empty()){
       convert(boxes,&k);
       k.timestamp=ros::Time::now();
       if(k.boxes.empty()){
         ROS_INFO("Empty");
       }
      // if(pub.getNumSubscribers()>0){
       pub.publish(k);
       ROS_INFO("Published\n");
   //    }

     }
     else{
       ROS_INFO("Publish Error\n");
     }
   }
    void convert(std::vector<cv::Rect>boxes,disp_cv::multibox *all)
    {
      //disp_cv::box temp[boxes.size()];
      all->boxes.clear();
      for(size_t i=0;i<boxes.size();i++){
         disp_cv::box box;
         box.x=boxes[i].x;
         box.y=boxes[i].y;
         box.w=boxes[i].width+15;
         box.h=boxes[i].height;
         //printf("Value: %d",box.h);
         all->boxes.push_back(box);
         //temp[i]=box;
      }


      return ;
    }

};
class ImageConverter
   {
     ros::NodeHandle nh_;
     image_transport::ImageTransport it_;
     image_transport::Subscriber image_sub_;
     image_transport::Publisher image_pub_;
     detect object;
     publishBox publish;
   public:
     ImageConverter()
       : it_(nh_)
     {
       // Subscrive to input video feed and publish output video feed
       image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1,
         &ImageConverter::imageCb, this);
       image_pub_ = it_.advertise("/image_converter/output_video", 1);
       publish=publishBox(nh_);

       cv::namedWindow(OPENCV_WINDOW);
       object=detect("/home/harsh/dataset/cascade/cascade.xml");
       //object=detect();
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


        object.find_object_gpu(cv_ptr->image);
        image_pub_.publish(cv_ptr->toImageMsg());

        publish.publish(object.retBoxes());

       // pubCameraInfo();
        tm.stop();
        ROS_INFO("Time Taken for display: %lf ms",tm.getTimeMilli());
     }

     void CallBackInfo(const sensor_msgs::CameraInfo::ConstPtr& msg){
        ros::Publisher info_pub;
        nh_.advertise<sensor_msgs::CameraInfo>("/image_converter/camera_info",1);
        //msg->header.stamp=ros::Time::now();
        info_pub.publish(msg);
     }
     void pubCameraInfo()
     {
       sensor_msgs::CameraInfo Info;
       ros::NodeHandle n1;

       ros::Subscriber info_sub;
       info_sub=n1.subscribe<sensor_msgs::CameraInfo>("/camera/rgb/camera_info",1,&ImageConverter::CallBackInfo,this);
        ros::spinOnce();
       /*
       Info.header.stamp=ros::Time::now();
       Info.header.frame_id="camera_rgb_optical_frame";
       Info.height=480;
       Info.width=640;
       Info.distortion_model="plumb_bob";
       Info.D=[0.0,0.0,0.0,0.0,0.0];
*/
     }
     detect retObj(){
       return object;
     }

   };


#endif
