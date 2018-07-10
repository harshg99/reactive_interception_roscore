#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <disp_cv/pose.h>


class tcpSocket
{
   struct sockaddr_in server;
   char buffer[28];
   int Socket;
   int MULT=1000000;
   int client;

public:
  int status=0;
  tcpSocket();
  bool buffInit(const disp_cv::pose::ConstPtr &pose);
  bool send();
  ~tcpSocket(){
    close(Socket);
    close(client);
  }
};
tcpSocket::tcpSocket()
{
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
     if(bind(Socket, (struct sockaddr*)&server, sizeof(server))<0){
       printf("Error in Binding\n");
       status=-1;
     }
     listen(Socket, 10);
     printf("Listening");
     client=accept(Socket, (struct sockaddr*)NULL, NULL);
     if(client<0){
       printf("Invalid Client connection");
       status=-1;
     }

}

bool tcpSocket::buffInit(const disp_cv::pose::ConstPtr &pose){
    int tmp[6];
    int keepalive=1;
    tmp[0]=pose->x;
    tmp[1]=pose->y;
    tmp[2]=pose->z;
    tmp[3]=pose->r1;
    tmp[4]=pose->r2;
    tmp[5]=pose->r3;

    for (int i = 0; i < 6; i++) {
      int tmp_dig = htonl((int) (tmp[i] * MULT));
      buffer[i * 4] = tmp_dig & 0xff;
      buffer[i * 4 + 1] = (tmp_dig >> 8) & 0xff;
      buffer[i * 4 + 2] = (tmp_dig >> 16) & 0xff;
      buffer[i * 4 + 3] = (tmp_dig >> 24) & 0xff;
    }
    int tmp_dig = htonl((int) keepalive);
    buffer[6 * 4] = tmp_dig & 0xff;
    buffer[6 * 4 + 1] = (tmp_dig >> 8) & 0xff;
    buffer[6 * 4 + 2] = (tmp_dig >> 16) & 0xff;
    buffer[6 * 4 + 3] = (tmp_dig >> 24) & 0xff;
    return true;
}

bool tcpSocket::send(){
  if(write(client, buffer, strlen(buffer))<0){
    return false;
  }
  return true;
}



#endif // TCPSOCKET_H
