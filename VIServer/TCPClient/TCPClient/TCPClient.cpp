/*
* tcpclient.c - A simple TCP client
* usage: tcpclient <host> <port>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket_types.hpp"
#include "winsock_init.hpp"
#include "ClientProtocolDefines.h"

#define BUFSIZE 1024

/*
* error - wrapper for perror
*/
void error(char *msg) {
    perror(msg);
    //exit(0);
}

int main(int argc, char **argv) {
    int sockfd, portno, n;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char buf[BUFSIZE];

    portno = 4159;

    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    /* gethostbyname: get the server's DNS entry */


    /* build the server's Internet address */
    memset((char *)&serveraddr, 0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //memcpy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    /* connect: create a connection with the server */
    if (connect(sockfd, (sockaddr*)&serveraddr, sizeof(sockaddr_in)) < 0)
        error("ERROR connecting");

    while (true)
    {
        /* get message line from the user */
        printf("Please enter msg: ");
        memset(buf, 0, BUFSIZE);
        fgets(buf, BUFSIZE, stdin);

        int sendCount = 0;
        char DataStream[1024] = { 0 };
        char* pDataStream = DataStream;
        memcpy(pDataStream, &CLIENT_CHAT, sizeof(int));
        pDataStream += sizeof(int);
        sendCount += sizeof(int);
        int msgLen = strlen(buf);
        memcpy(pDataStream, &msgLen, sizeof(int));
        pDataStream += sizeof(int);
        sendCount += sizeof(int);
        memcpy(pDataStream, (char*)buf, msgLen);
        sendCount += strlen(buf);
        /* send the message line to the server */
        n = send(sockfd, DataStream, sendCount, 0);
        if (n < 0)
            error("ERROR writing to socket");

        /* print the server's reply */
        memset(buf, 0, BUFSIZE);
        n = recv(sockfd, buf, BUFSIZE, 0);
        if (n < 0)
            error("ERROR reading from socket");
        printf("Echo from server: %s \n", buf);
    }

    closesocket(sockfd);

    system("pause");

    return 0;
}