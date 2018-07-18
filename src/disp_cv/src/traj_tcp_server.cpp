#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <std_msgs/String.h>

#include<disp_cv/pose.h>
#include<disp_cv/tcpsocket.h>

disp_cv::pose pose;
bool send_val=false;

void interceptCallback(const disp_cv::pose::ConstPtr &msg)
{
  ROS_INFO("Message Recieved: %lf %lf %lf\n",msg->x,msg->y,msg->z);
  pose=*msg;
  send_val=true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "traj_tcp_server");

  tcpSocket Socket;
  ros::NodeHandle nh;
  ros::Rate rate(125);
  if(Socket.status==-1){
    printf("Exiting Node");
    std::getchar();
  }
  disp_cv::pose Pose;
  Pose.x=0.0;
  Pose.y=-0.25;
  Pose.z=0.35;
  Pose.r1=0.0;
  Pose.r2=1.57;
  Pose.r3=0.0;
  //pose=(disp_cv::pose::ConstPtr)&Pose;
  pose=Pose;
  send_val=false;
  //ros::Publisher pub = nh.advertise<disp_cv::pose>("intercept", 1);
  ros::Subscriber sub = nh.subscribe<disp_cv::pose>("intercept", 1, &interceptCallback);
  //Socket.buffInit(0.0,-0.25,0.35,0.0,1.57,0.0);
  while(ros::ok()){
    Socket.buffInit(pose);
    if(send_val){
      if(!Socket.send()){
        ROS_INFO("Error Sending message");
      }
      send_val=false;
    }
     printf("Sent\n");
     ros::spinOnce();
     rate.sleep();
  }
  /*if(!Socket.send()){
    ROS_INFO("Error Sending message");
  }
  */

  printf("Exiting Node");

  return 0;
}
