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
#include "hashmap.h"
#include <sys/types.h>

int main() {

    struct user {
        char username[10];
        int conn;
        struct user *next;
    };

    const unsigned initial_size_hashmap = 2;
    struct hashmap_s hashmap;
    if (0 != hashmap_create(initial_size_hashmap, &hashmap)) {
        printf("Hashmap failed to initialize.");
    }

    struct user all[10];
    int fd[2], nbytes;
    char buff[1024];
    char username[10];

    //Setup Buffer Array
    memset(buff, '0', sizeof(buff));
    memset(username,0,sizeof(username));

    //Create Socket
    fd[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
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


    bind(fd, (struct sockaddr *) &server, sizeof(server));

    int conn;

    listen(fd, 10);


    while (1) {
        conn = accept(fd, (struct sockaddr *) NULL, NULL);
        if(conn>0) {
            int childpid, n;
            pipe(fd);
            if ((childpid = fork()) == 0) {
                //close listening socket
                close(fd[0]);

                recv(conn, username, 10, 0);
                write(fd[1], username, 11);

                //Clear Zeroes
                bzero(buff, 256);
                while ((n = recv(conn, buff, 256, 0)) > 0) {
                    printf("%s> %s", username, buff);
                    //send(conn, buff, strlen(buff), 0);
                    bzero(buff, 256);

                }
                close(conn);
                exit(0);
            } else {

                close(fd[1]);
                nbytes = read(fd[0], username, sizeof(username));
                printf("Received string: %s", username);

            }
            conn = 0;
        }
    }
}