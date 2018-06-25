#ifndef REGRESSION_H
#define REGRESSION_H

#include<ros/ros.h>
#include<disp_cv/pos3dtime.h>
#include<disp_cv/reg_pos3Dtime.h>
#include<visualization_msgs/Marker.h>
#include<eigen3/Eigen/Dense>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/IterativeLinearSolvers>
#include<eigen3/Eigen/Householder>
#include<eigen3/Eigen/Geometry>
#include<eigen3/Eigen/Eigen>
#include<iostream>
#include<math.h>

#define time_interval_reg 0.08
#define dataSize 20
#define tolerance 0.01

#define AXIS_X 1
#define AXIS_Y 2
#define AXIS_Z 3

using namespace Eigen;
class regression
{
  private:
    ros::Subscriber sub;
    ros::Publisher pub;
    ros::NodeHandle node;

    int degree;

    Matrix<double,3,1> coeffx;
    Matrix<double,3,1> coeffy;
    Matrix<double,3,1> coeffz;

    Matrix<double,dataSize,1> posx;
    Matrix<double,dataSize,1> posy;
    Matrix<double,dataSize,1> posz;

    Matrix<double,dataSize,3> t;

  public:
    regression()
    {
      sub=node.subscribe<disp_cv::reg_pos3Dtime>("/regression_data",1,&regression::CallBack,this);
      pub=node.advertise<visualization_msgs::Marker>("/visualisation_marker2",1);
      degree=2;

      //coeffx=MatrixXd::setZero(3,1);

      //coeffy=MatrixXd::setZero(3,1);
      //coeffz::setZero(3,1);

      //posx=MatrixXd::setZero(20,1);
      //posy=MatrixXd::setZero(20,1);
      //posz=MatrixXd::setZero(20,1);

      //t=MatrixXd::setZero(20,3);

    }

    void CallBack(const disp_cv::reg_pos3Dtime::ConstPtr &msg )
    {
    //  ROS_INFO("Initialising matrices: %d",msg->points.size());
      geometry_msgs::Point pointref;
      for(int i=0;i<msg->points.size();i++)
      {
         posx(i,0)=msg->points[i].x-msg->points[msg->ref].x;
         posy(i,0)=msg->points[i].y-msg->points[msg->ref].y;
         posz(i,0)=msg->points[i].z-msg->points[msg->ref].z;
         t(i,0)=1;
         t(i,1)=(double)(msg->points[i].timestamp-msg->points[msg->ref].timestamp).sec+(double)(msg->points[i].timestamp-msg->points[msg->ref].timestamp).nsec/1000000000.0;
         t(i,2)=t(i,1)*t(i,1);

         pointref.x=msg->points[msg->ref].x;
         pointref.y=msg->points[msg->ref].y;
         pointref.z=msg->points[msg->ref].z;

      }
     std::cout<<t<<"\n\n"<<posx<<"\n\n"<<posy<<"\n\n"<<posz<<"\n\n";


     bool regressX=isRegressed(msg->ref-1,AXIS_X);
     bool regressY=isRegressed(msg->ref-1,AXIS_Y);
     bool regressZ=isRegressed(msg->ref-1,AXIS_Z);
     if(regressX)
     {
       calc_coeffsx();
     }
     else{

     }
     if(regressY)
     {
       calc_coeffsy();
     }
     if(regressZ)
     {
       calc_coeffsz();
     }
       std::cout<<coeffx<<"\n\n"<<coeffy<<"\n\n"<<coeffz<<"\n\n";
      predict(msg->ref-1,pointref,regressX,regressY,regressZ);
    }

    //this function checks for whetehr regession is feasible
    bool isRegressed(int ref,int type){

      //counts number of equal points
      int count=0;

      //base of comparision
      float base;
      for(int j=8;j>=1;j--)
      {
        int temp=ref-j;
        temp=(temp<0)?temp+20:temp;
        if(j==8){
          switch(type){
            case AXIS_X:base=posx(temp,0);break;
            case AXIS_Y:base=posy(temp,0);break;
            case AXIS_Z:base=posz(temp,0);break;
          }
        }

          switch(type){
            case AXIS_X:
            if(fabs(posx(temp,0)-base)<tolerance){
              count++;
            }
            break;
          case AXIS_Y:
          if(fabs(posy(temp,0)-base)<tolerance){
            count++;
          }
          break;
          case AXIS_Z:
          if(fabs(posz(temp,0)-base)<tolerance){
            count++;
          }
          break;
        }

      }
      if(count>=5){
        return false;
      }
      else{
        return true;
      }

    }

    void calc_coeffsx()
    {
     // ROS_INFO("calculating\n");
      coeffx=(t.transpose()*t).ldlt().solve(t.transpose()*posx);
    }

    void calc_coeffsy()
    {
     // ROS_INFO("calculating\n");
      coeffy=(t.transpose()*t).ldlt().solve(t.transpose()*posy);

    }

    void calc_coeffsz()
    {
     // ROS_INFO("calculating\n");

      coeffz=(t.transpose()*t).ldlt().solve(t.transpose()*posz);
    }

    void predict(int ref,geometry_msgs::Point refp,bool isX, bool isY, bool isZ)
    {
    //  ROS_INFO("Predicting\n");
      visualization_msgs::Marker marker;
      marker.id=100;
      marker.type=visualization_msgs::Marker::SPHERE_LIST;
      marker.scale.x=0.035;
      marker.scale.y=0.035;
      marker.scale.z=0.035;
      marker.color.r=0.0;
      marker.color.g=0.0;
      marker.color.b=1.0;
      marker.color.a=0.8;
      marker.header.stamp=ros::Time::now();
      marker.header.frame_id="camera_rgb_optical_frame";
      if(ref<0){
        ref=ref+20;
      }

      bool flag=false;
      ROS_INFO("Reference Time: %lf",t(ref,1));
      for(int j=1;j<=10;j++)
      {
        geometry_msgs::Point p;
        //ROS_INFO("Reference at: %d",ref);
        double pt=t(ref,1)+(double)j*time_interval_reg;
        if(isX){
        p.x=refp.x+coeffx(0,0)+coeffx(1,0)*pt+coeffx(2,0)*pt*pt;
        }
        else{
        p.x=refp.x;
        }
        if(isY){
        p.y=refp.y+coeffy(0,0)+coeffy(1,0)*pt+coeffy(2,0)*pt*pt;
        }
        else{
           p.y=refp.y;
        }
        if(isZ){
        p.z=refp.z+coeffz(0,0)+coeffz(1,0)*pt+coeffz(2,0)*pt*pt;
        }
        else{
         p.z=refp.z;
        }
        if(p.x!=NAN&&p.y!=NAN&&p.z!=NAN){
        marker.points.push_back(p);
        flag=true;
        }
        ROS_INFO("Predict at time %lf: %lf %lf %lf",pt,p.x,p.y,p.z);

      }
      if(flag){
      pub.publish(marker);
      }

    }
/*
    void unWrapData(std::vector<disp_cv::pos3dtime>positions,int ref)
    {
      posx.
      posx.
    }

*/







};
#endif // REGRESSION_H
