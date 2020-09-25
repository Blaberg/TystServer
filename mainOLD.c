/****SERVER CODE****/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>        //for sockets
#include <string.h>        //for string operations
#include <netinet/in.h>        //Internet Protocol family sockaddr_in defined here
#include <pthread.h>        // for the cosy POSIX threads
#include <arpa/inet.h>        // for inet_ntoa() function
#include <unistd.h>        //NULL constant defined here
#include <signal.h>        //for ctrl+c signal

#define BACKLOG 100        // connections in the queue
#define MAXDATALEN 256         //max size of messages to be sent
#define PORT 2012        //default port number

/*Note:   The port argument is optional. If no port is specified,
 *          the server uses the default given by PORT.*/

struct Node                    /*structure to handle all clients*/
{
    int port;
    char username[10];
    struct Node *next;
};

typedef struct Node *ptrtonode;
typedef ptrtonode head;
typedef ptrtonode addr;

void quitAll();            /*send msg to all if server shuts down*/
head makeEmpty(head h);        /*clearing list*/
void delete(int port, head h);    /*delete client values on client exit*/
void insert(int port, char *, head h, addr a);/*inserting new client */
void deleteList(head h);        /*clearing list*/
void *quitProc();             /*signal handler*/
void *server(void *arg);        /*server instance for every connected client*/

int broadCast(head list, char *message, int bufferSize, int flags, int senderPort);

struct Node getUser(char *user);

char username[10];        /*size of username*/
head h;                /*variable of type struct head*/
char buffer[MAXDATALEN];

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

/******main starts ***********/
int main(int argc, char *argv[]) {

    int sockfd, new_fd;             /*variables for socket*/
    int portnum;            /*variable for port numb if provided*/
    struct sockaddr_in server_addr;    /*structure to hold server's address */
    struct sockaddr_in client_addr;    /*structure to hold client's address */
    int cli_size, z;            /*length of address */
    pthread_t thr;            /*variable to hold thread ID */
    int yes = 1;
    addr a;                    /*variable of type struct addr*/

    printf("\n\t*-*-*-*SERVER STARTED*-*-*-*\n");
    /*=optional or default port argument=*/
    if (argc == 2)
        portnum = atoi(argv[1]);
    else
        portnum = PORT;  //if port number not given as argument then using default port
    printf("PORT NO.:\t%d\n", portnum);

    h = makeEmpty(NULL);        //frees the list

    /*=set info of server =*/
    server_addr.sin_family = AF_INET;        /* set family to Internet     */
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* set IP address */
    server_addr.sin_port = htons(portnum);
    printf("IP ADDRESS:\t%s\n", inet_ntoa(server_addr.sin_addr));

    /*=creating socket=*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("server- socket() error");    // debugging
        exit(1);
    } else
        printf("socket\t\tcreated.\n");

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        printf("setsockopt error");    // debugging
        exit(1);
    } else printf("reusing\t\tport\n");

    /*=binding socket=*/
    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
        printf("binding failed\n");    // debugging
        exit(1);
    } else
        printf("binding\t\tsuccess.\n\n");
    printf("\t\tPRESS CTRL+z TO VIEW ONLINE CLIENTS\n\n");
    /*=socket on listening mode=*/
    listen(sockfd, BACKLOG);
    printf("waiting for clients......\n");

    if (signal(SIGINT, (void *) quitProc) == 0)    //signal handler

        while (1) {
            cli_size = sizeof(struct sockaddr_in); //cli_size necessary as an argument for pthread_create
            new_fd = accept(sockfd, (struct sockaddr *) &client_addr, &cli_size); //accepting connection from client
            a = h;

            /*=sign in with name=*/
            bzero(username, 10);
            if (recv(new_fd, username, sizeof(username), 0) > 0);
            username[strlen(username) - 1] = ':';
            printf("\t%d->%s JOINED chatroom\n", new_fd, username);
            sprintf(buffer, "%s IS ONLINE\n", username);
            insert(new_fd, username, h, a);            //inserting newly accepted client socked fd in list
            a = a->next;

            /*=notify all clients about newly joining clients=*/
            broadCast(h, buffer, sizeof(buffer), 0, new_fd);
            getUser(username);

            printf("server got connection from %s & %d\n\n", inet_ntoa(client_addr.sin_addr), new_fd); // debugging

            struct Node args;                     //struct to pass multiple arguments to server function
            args.port = new_fd;
            strcpy(args.username, username);

            pthread_create(&thr, NULL, server, (void *) &args);     //creating thread for every client connected
            pthread_detach(thr);
        } /*while end*/

    deleteList(h);                     //deleting all clients when server closes
    close(sockfd);

}/********main ends***********/
#pragma clang diagnostic pop


/*******ALL FUNCTIONS DEFINED BELOW*********/

/* ==========Server function for every connected Client =========*/

void *server(void *arguments) {

    struct Node *args = arguments;

    char msg[MAXDATALEN], ubuf[50], uname[10];    /* buffer for string the server sends */
    char *strp;
    char *usrname = (char *) malloc(MAXDATALEN);
    int ts_fd, x, y;
    int sfd;

    ts_fd = args->port;     /*socket variable passed as arg*/
    strcpy(uname, args->username);
    addr a;

    /*=sending list of clients online=*/
    a = h;
    do {
        a = a->next;
        sprintf(ubuf, " %s is online\n", a->username);
        send(ts_fd, ubuf, strlen(ubuf), 0);
    } while (a->next != NULL);


    /*=start chatting=*/
    while (1) {

        bzero(msg, 256);
        y = recv(ts_fd, msg, MAXDATALEN, 0);

        /*=if a client quits=*/
        if (strncmp(msg, "quit", 4) == 0 || y == 0) {
            printf("%d ->%s left chat deleting from list\n", ts_fd, uname);
            sprintf(msg, "%s has left the chat\n", uname);

            addr a = h;
            do {
                a = a->next;
                sfd = a->port;
                if (sfd == ts_fd)
                    delete(sfd, h);
                if (sfd != ts_fd)
                    send(sfd, msg, MAXDATALEN, 0);
            } while (a->next != NULL);

            close(ts_fd);
            free(usrname);

            break;
        }


        /*=sending message to all clients =*/
        printf("%s %s\n", uname, msg);
        strcpy(usrname, uname);
        x = strlen(usrname);
        strp = usrname;
        strp += x;
        char *token;
        char *users;
        char *message;
        token = strtok(msg, ">");
        for (int i = 0; i < 2; i++) {
            printf("%s\n", msg);
            token = strtok(NULL, ">");

        }
        /*  token = strtok(users, " ");
          head g;
          g = makeEmpty(NULL);
          while(token){
              struct Node test = getUser(users);
              test.next =
          }*/
        strcat(strp, msg);
        broadCast(h, usrname, strlen(msg), 0, ts_fd);

        bzero(msg, MAXDATALEN);

    }//end while
    return 0;

}// end server


/*=====empties and deletes the list======*/
head makeEmpty(head h) {
    if (h != NULL)
        deleteList(h);
    h = malloc(sizeof(struct Node));
    if (h == NULL)
        printf("Out of memory!");
    h->next = NULL;
    return h;
}

/*======delete list=======*/
void deleteList(head h) {
    addr a, Tmp;
    a = h->next;
    h->next = NULL;
    while (a != NULL) {
        Tmp = a->next;
        free(a);
        a = Tmp;
    }
}

/*===============inserting new clients to list==========*/
void insert(int port, char *username, head h, addr a) {
    addr TmpCell;
    TmpCell = malloc(sizeof(struct Node));
    if (TmpCell == NULL)
        printf("Out of space!!!");
    TmpCell->port = port;
    strcpy(TmpCell->username, username);
    TmpCell->next = a->next;
    a->next = TmpCell;
}


/*===========client deleted from list if client quits================*/
void delete(int port, head h) {
    addr a, TmpCell;
    a = h;
    while (a->next != NULL && a->next->port != port)
        a = a->next;
    if (a->next != NULL) {
        TmpCell = a->next;
        a->next = TmpCell->next;
        free(TmpCell);
    }
}

/*======handling signals==========*/
void *quitProc() {
    quitAll();
    exit(0);
}

/*===============notifying server shutdown===========*/
void quitAll() {
    int i;
    if (h->next == NULL) {
        printf("......BYE.....\nno clients \n\n");
        exit(0);
    } else {
        i = broadCast(h, "Server: Shutting down", 21, 0, -1);
    }
    printf("%d clients closed\n\n", i);
}

int broadCast(head list, char *message, int buffersize, int flags, int senderPort) {
    int i = 0;
    addr a = list;
    do {
        i++;
        a = a->next;
        if (a->port != senderPort)
            send(a->port, message, buffersize, flags);
    } while (a->next != NULL);
    return i;
}

struct Node getUser(char *user) {
    addr a = h;
    do {
        a = a->next;
        if (strcmp(user, a->username) == 0) {
            printf("Found user: %s\n", user);
            printf("Port: %d\n", a->port);
            return *a;
        }
    } while (a->next != NULL);
    printf("Could not find User: %s", user);
}

/*=========================================================================================================*/