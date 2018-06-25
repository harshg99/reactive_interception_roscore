#ifndef DEPTH_CALC_H
#define DEPTH_CALC_H

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
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>
#include <queue>

typedef pcl::PointCloud<pcl::PointXYZ> PC;


using namespace std;
static const string OPENCV_WINDOW2 = "Image window2";
class depth{
  private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
    ros::Subscriber boxListener;
    cv::Mat frame;
    ros::Subscriber pointCloudListener;
    ros::Publisher  pointCloudPublisher;
    ros::Publisher  visualiser;
    PC pointcloud;
    int count;

  public:
    depth()
      : it_(nh_)
    {
      // Subscrive to input video feed and publish output video feed
      image_sub_ = it_.subscribe("/camera/depth/image", 1,
        &depth::imageCb, this);
      boxListener=nh_.subscribe<disp_cv::multibox>("/bounding_boxes",1,&depth::boxCallBack,this);
      image_pub_ = it_.advertise("/image_converter/output_depth", 1);
      cv::namedWindow(OPENCV_WINDOW2);
      pointCloudListener=nh_.subscribe<PC>("/camera/depth_registered/points",1,&depth::PCCallBack,this);
      pointCloudPublisher=nh_.advertise<PC>("/pointcloud/points",1);
      visualiser=nh_.advertise<visualization_msgs::Marker>("/visualisation_marker",10);
      count=0;
    }
    ~depth()
    {
      cv::destroyWindow(OPENCV_WINDOW2);
    }

    void imageCb(const sensor_msgs::ImageConstPtr& msg)
    {

      cv_bridge::CvImagePtr cv_ptr;
      try
      {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_16UC1);
        //image_pub_.publish(cv_ptr->toImageMsg());
        //cv::imshow(OPENCV_WINDOW2,cv_ptr->image);
        frame=cv_ptr->image;
        //ROS_INFO("Depth Displayed \n");
      }
      catch (cv_bridge::Exception& e)
      {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
      }
      //cv::Mat frame_col;
      //cv::cvtColor(cv_ptr->image,frame_col,cv::COLOR_BGR2RGBA);

      // Draw an example circle on the video stream
     // if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
    //    cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

      // Update GUI Window
    }
    void boxCallBack(const disp_cv::multibox::ConstPtr &msg){

      //POint cloud computations
      pcl::PointXY points[msg->boxes.size()][4];
      visualization_msgs::Marker line_Strip[msg->boxes.size()];
      visualization_msgs::Marker points_viz;

      for(size_t i=0;i<msg->boxes.size();i++){
        cv::rectangle(frame,toRect(msg->boxes[i],points,i),cv::Scalar(0,0,0),10);
      }

      //visualisation of bounding boxes on point cloud

       points_viz.id=(count)%20;;
       points_viz.type=visualization_msgs::Marker::SPHERE_LIST;
       points_viz.scale.x=0.035;
       points_viz.scale.y=0.035;
       points_viz.scale.z=0.035;
       points_viz.color.r=0.0;
       points_viz.color.g=1.0;
       points_viz.color.b=0.0;
       points_viz.color.a=0.8;
       points_viz.header.stamp=ros::Time::now();
       points_viz.header.frame_id="camera_rgb_optical_frame";
      for(int i=0;i<msg->boxes.size();i++){
     //   line_Strip[i].id=i;
        //line_Strip[i].type=visualization_msgs::Marker::LINE_STRIP;
      //  line_Strip[i].scale.x=2.0;
    //    line_Strip[i].color.r=1.0;
    //   line_Strip[i].header.stamp=ros::Time::now();
    //    line_Strip[i].header.frame_id="camera_rgb_optical_frame";

/*
        for(int j=0;j<4;j++){
          pcl::PointXYZ temp_point=pointcloud.at(points[i][j].x,points[i][j].y);
          geometry_msgs::Point p;

          if((temp_point.z!=NAN && temp_point.y!=NAN && temp_point.x!=NAN) ||
             (temp_point.z!=INFINITY && temp_point.y!=INFINITY && temp_point.x!=INFINITY))
          {
            p.z=temp_point.z;
            p.x=temp_point.x;
            p.y=temp_point.y;
          }
          else{
            p.x=0;
            p.y=0;
            p.z=0;
          }
          line_Strip[i].points.push_back(p);
        }
        */
        //pcl::PointXYZ temp_point=pointcloud.at((int)(msg->boxes[i].x+msg->boxes[i].w/2),(int)((msg->boxes[i].y+msg->boxes[i].h)/2));
        if(!msg->boxes.empty()){
          geometry_msgs::Point p=calc_dist(msg->boxes[i]);
          points_viz.points.push_back(p);
        }
        //p.z=temp_point.z;
        //p.x=temp_point.x;
        //p.y=temp_point.y;
        //if(p.z<=3.5){

        //}
       // ROS_INFO("Face At: x:%lf y:%lf z:%lf",p.x,p.y,p.z);

       // visualiser.publish(line_Strip[i]);
      }
        visualiser.publish(points_viz);

      std_msgs::Header header; header.stamp=ros::Time::now();
      cv_bridge::CvImage cv_Image(header,sensor_msgs::image_encodings::TYPE_16UC1,frame);
      image_pub_.publish(cv_Image.toImageMsg());
    }
    cv::Rect toRect(disp_cv::box loc,pcl::PointXY points[][4], int i){
      cv::Rect box;
      box.x=loc.x;
      box.y=loc.y;
      box.height=loc.h;
      box.width=loc.w;

/*
      points[i][0].x=box.x;
      points[i][0].y=box.y;

      points[i][1].x=box.x+box.width;
      points[i][1].y=box.y;

      points[i][2].x=box.x+box.width;
      points[i][2].y=box.y+box.height;

      points[i][3].x=box.x;
      points[i][3].y=box.y+box.height;

*/

      return box;
    }

    void PCCallBack(const PC::ConstPtr &msg ){
      pointcloud=*msg;
      pointCloudPublisher.publish(pointcloud);
    }


    geometry_msgs::Point calc_dist(disp_cv::box box){
      geometry_msgs::Point p;
      p.x=0.0;p.y=0.0;p.z=0.0;
     // int max=10;
      std::queue<std::pair<int,int> > dfs_queue;

      std::pair<int,int> point;
      point.first=box.x+box.w/2;
      point.second=box.y+box.h/2;
      dfs_queue.push(point);


      //standard dfs routine to find closest values of accuracy

    //  while(!dfs_queue.empty()/*&& max>0*/ &&dfs_queue.size()<80){
        std::pair<int,int> popped=dfs_queue.front();
      //  dfs_queue.pop();
        pcl::PointXYZ eval=pointcloud.at(popped.first,popped.second);
     //   if(eval.z<=3.5){
        if(eval.x!=NAN &&eval.y!=NAN &&eval.z!=NAN &&eval.z<=3.75&&eval.z>=0.4){
          p.x=eval.x;
          p.y=eval.y;
          p.z=eval.z;
          count++;
        }
          //max--;
          while(!dfs_queue.empty()) dfs_queue.pop();
          return p;
       // }
        /*else{
          popped.first+=1;
          dfs_queue.push(popped);
          popped.first-=2;
          dfs_queue.push(popped);
          popped.first+=1;
          popped.second+=1;
          dfs_queue.push(popped);
          popped.second-=2;
          dfs_queue.push(popped);
        }
*/
       // ROS_INFO("Max:%d", max);
     // }

    //  p.x/=(10-max);p.y/=(10-max);p.z/=(10-max);
   //   return p;
     // return p;
    }

};

#endif // DEPTH_CALC_H
