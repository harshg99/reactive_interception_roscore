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

tcpSocket Socket;
void interceptCallback(const disp_cv::pose::ConstPtr &msg)
{
  ROS_INFO("Message Recieved:\n");
  Socket.buffInit(msg);
  if(!Socket.send()){
    ROS_INFO("Error Sending message");
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "traj_tcp_server");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<disp_cv::pose>("intercept", 1);
  ros::Subscriber sub = nh.subscribe<disp_cv::pose>("intercept", 1, &interceptCallback);


  Socket=tcpSocket();
  if(Socket.status==-1){
    printf("Exiting Node");
    std::getchar();
    exit(0);
  }
  ros::spin();

  return 0;
}
