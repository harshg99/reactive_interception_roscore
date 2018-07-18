#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <std_msgs/String.h>
#include <disp_cv/pose.h>

#include <stdio.h>
#define TCP_NODELAY 1
class tcpSocket
{
   struct sockaddr_in server;
   unsigned char buffer[28];
   int Socket;
   double MULT=1000000.0;
   int client;
   struct sockaddr_in cli_addr;
   socklen_t clilen;
   static int create;
   //ros::NodeHandle nh;
  // ros::Subscriber sub;
   //disp_cv::pose::ConstPtr pose;
public:
  int status=0;
  tcpSocket();
  bool buffInit(disp_cv::pose msg);
  bool buffInit(double x, double y, double z,double r1,double r2,double r3);
  bool send();
   //void interceptCallback(const disp_cv::pose::ConstPtr &msg);
  ~tcpSocket(){
    close(Socket);
    close(client);
  }


};
int tcpSocket::create=0;
tcpSocket::tcpSocket()
{
  //sub = nh.subscribe<disp_cv::pose>("intercept", 1, &tcpSocket::interceptCallback,this);
  if(create==0){
     Socket = socket(AF_INET, SOCK_STREAM, 0);
     printf("Creating Socket\n");
     if(Socket<0){
       printf("Error in creating socket\n");
       status=-1;
     }
     memset(&server, '0', sizeof(server));
     memset(buffer, '0', sizeof(buffer));

     server.sin_family = AF_INET;
     server.sin_addr.s_addr = htonl(INADDR_ANY);
     server.sin_port = htons(50006);
     printf("Attempting Bind to %d:%d\n",ntohl(server.sin_addr.s_addr),ntohs(server.sin_port));
     int flag=1;
     setsockopt(Socket, IPPROTO_TCP, TCP_NODELAY, (char *) &flag,
         sizeof(int));
     setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));
     if(bind(Socket, (struct sockaddr*)&server, sizeof(server))<0){
       printf("Error in Binding\n");
       status=-1;
     }
     listen(Socket, 10);
     printf("Listening\n");
     client=accept(Socket, (struct sockaddr*)&cli_addr, &clilen);
     if(client<0){
       printf("Invalid Client connection");
       status=-1;
     }
     else{
     printf("Client Socket Connected to:\n");
     }
     create=1;  }
   // sub = nh.subscribe<disp_cv::pose>("intercept", 1, &tcpSocket::interceptCallback,this);

}

bool tcpSocket::buffInit(disp_cv::pose pose){
    double tmp[6];
    int keepalive=1;
    tmp[0]=pose.x;
    tmp[1]=pose.y;
    tmp[2]=pose.z;
    tmp[3]=pose.r1;
    tmp[4]=pose.r2;
    tmp[5]=pose.r3;

    for (int i = 0; i < 6; i++) {
      int tmp_dig = htonl((int) (tmp[i] * MULT));
      buffer[i * 4] = tmp_dig & 0xff;
      buffer[i * 4 + 1] = (tmp_dig >> 8) & 0xff;
      buffer[i * 4 + 2] = (tmp_dig >> 16) & 0xff;
      buffer[i * 4 + 3] = (tmp_dig >> 24) & 0xff;
    }
    //printf("Message:%s\n",buffer);
    int tmp_dig = htonl((int) keepalive);
    buffer[6 * 4] = tmp_dig & 0xff;
    buffer[6 * 4 + 1] = (tmp_dig >> 8) & 0xff;
    buffer[6 * 4 + 2] = (tmp_dig >> 16) & 0xff;
    buffer[6 * 4 + 3] = (tmp_dig >> 24) & 0xff;
    //send();
    return true;
}

bool tcpSocket::buffInit(double x, double y, double z,double r1,double r2,double r3){
    int tmp[6];
    int keepalive=1;
    tmp[0]=x;
    tmp[1]=y;
    tmp[2]=z;
    tmp[3]=r1;
    tmp[4]=r2;
    tmp[5]=r3;
    /*
    disp_cv::pose Pose;
    Pose.x=tmp[0];
    Pose.y=tmp[1];
    Pose.z=tmp[2];
    Pose.r1=tmp[3];
    Pose.r2=tmp[4];
    Pose.r3=tmp[5];
    pose=(disp_cv::pose::ConstPtr)&Pose;
    */
/*
    for (int i = 0; i < 6; i++) {
      int tmp_dig = htonl((int) (tmp[i] * MULT));
      buffer[i * 4] = tmp_dig & 0xff;
      buffer[i * 4 + 1] = (tmp_dig >> 8) & 0xff;
      buffer[i * 4 + 2] = (tmp_dig >> 16) & 0xff;
      buffer[i * 4 + 3] = (tmp_dig >> 24) & 0xff;
    }
     //printf("Message:%s\n",buffer);
    int tmp_dig = htonl((int) keepalive);
    buffer[6 * 4] = tmp_dig & 0xff;
    buffer[6 * 4 + 1] = (tmp_dig >> 8) & 0xff;
    buffer[6 * 4 + 2] = (tmp_dig >> 16) & 0xff;
    buffer[6 * 4 + 3] = (tmp_dig >> 24) & 0xff;
    //send();
    */
    return true;
}

bool tcpSocket::send(){
  if(client<0){
    printf("Invalid CLient\n");
    return false;
  }
  int bytes_written=write(client, buffer, 28);
  printf("Bytes Written:%d\n",bytes_written);
  if(!bytes_written==28){
    return false;
  }
  return true;
}
/*
void tcpSocket::interceptCallback(const disp_cv::pose::ConstPtr &msg)
{
  ROS_INFO("Message Recieved:\n");
  pose=msg;
}
*/



#endif // TCPSOCKET_H
