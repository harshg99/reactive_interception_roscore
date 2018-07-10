

tcpSocket::tcpSocket()
{
     Socket = socket(AF_INET, SOCK_STREAM, 0);
     if(Socket<0){
       printf("Error in creating socket\n");
     }
     memset(&server, '0', sizeof(serv_addr));
     memset(buffer, '0', sizeof(sendBuff));

     server.sin_family = AF_INET;
     server.sin_addr.s_addr = htonl(INADDR_ANY);
     server.sin_port = htons(50006);
     if(bind(Socket, (struct sockaddr*)&server, sizeof(server))<0){
       printf("Error in Binding\n");
     }
     listen(Socket, 10);
     printf("Listening");
     client=accept(Socket, (struct sockaddr*)NULL, NULL);
}

tcpSocket::buffInit(const disp_cv::pose::ConstPtr &pose){
    int tmp[6];
    int keepAlive=1;
    tmp[0]=pose->x;
    tmp[1]=pose->y;
    tmp[2]=pose->z;
    tmp[3]=pose->r1;
    tmp[4]=pose->r2;
    tmp[5]=pose->r3;

    for (int i = 0; i < 6; i++) {
      int tmp_dig = htonl((int) (tmp[i] * MULT_JOINTSTATE_));
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

tcpSocket::send(){
  if(write(client, buffer, strlen(sendBuff))<0){
    return false;
  }
  return true;
}


