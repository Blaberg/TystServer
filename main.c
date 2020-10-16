/*
=======================================================
CHAT APPLICATION IN C: SERVER
Author: RUCHIR SHARMA
Email ID: ruchir.sharma@students.iiit.ac.in
=======================================================
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main()
{
    int fd = 0;
    char buff[1024];

    //Setup Buffer Array
    memset(buff, '0',sizeof(buff));

    //Create Socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd<0)
    {
        perror("Client Error: Socket not created succesfully");
        return 0;
    }

    //Structure to store details
    struct sockaddr_in server;
    memset(&server, '0', sizeof(server));

    //Initialize
    server.sin_family = AF_INET;
    server.sin_port = htons(8096);
    server.sin_addr.s_addr = htonl(INADDR_ANY);


    bind(fd, (struct sockaddr*)&server, sizeof(server));

    int conn;

    listen(fd, 10);
    while(	conn = accept(fd, (struct sockaddr*)NULL, NULL))
    {
        int childpid,n;
        if ( (childpid = fork ()) == 0 ){
            //close listening socket
            close (fd);

            //Clear Zeroes
            bzero(buff,256);
            while ((n = recv(conn, buff, 256,0)) > 0)
            {
                printf("Server Received: %s",buff);
                send(conn, buff, strlen(buff), 0);
                bzero(buff,256);

            }
            close(conn);
            exit(0);
        }
    }
}