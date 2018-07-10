#ifndef TRAJ_PREDICTOR_H
#define TRAJ_PREDICTOR_H
#include<ros/ros.h>
#include<visualization_msgs/Marker.h>
#include<geometry_msgs/Point.h>
#include<disp_cv/pos3dtime.h>
#include<disp_cv/reg_pos3Dtime.h>

#define COUNT 7
class predict
{
  private:
    //int sphere_count=0;
    //geometry_msgs::Point points[5];
    ros::Subscriber sub;
    ros::Publisher pub;
    ros::NodeHandle node;
    int count;
    disp_cv::pos3dtime elem[COUNT];
  public:
    predict()
    {
      sub=node.subscribe<visualization_msgs::Marker>("/visualisation_marker",1,&predict::callback,this);
      pub=node.advertise<disp_cv::reg_pos3Dtime>("/regression_data",1);
      count=0;
    }

    void callback(const visualization_msgs::Marker::ConstPtr &markers)
    {
      disp_cv::pos3dtime pos;

      pos.timestamp=markers->header.stamp;
      pos.x=markers->points.begin()->x;
      pos.y=markers->points.begin()->y;
      pos.z=markers->points.begin()->z;

      if(pos.x!=NAN && pos.z!=NAN && pos.y!=NAN){
      elem[count%COUNT]=pos;
      //std::vector<disp_cv::pos3dtime> p(elem,elem+sizeof(elem)/sizeof(elem[0]);
      disp_cv::reg_pos3Dtime data;
      data.points.insert(data.points.begin(),elem,elem+sizeof(elem)/sizeof(elem[0]));
      data.ref=(count%COUNT+1)%COUNT;
      count++;
      if(count>=COUNT){
      ROS_INFO("Ref: %lf %lf %lf",data.points[data.ref].x,data.points[data.ref].y,data.points[data.ref].z);

      pub.publish(data);
      }
      }
    }







};
#endif // TRAJ_PREDICTOR_H
