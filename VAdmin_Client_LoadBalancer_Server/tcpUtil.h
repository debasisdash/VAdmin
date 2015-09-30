/******************************************************************* 
* File Name   : tcpUtil.h
* Author      : VAdmin Team
* Location    : San Jose State University
* Description : This file give all the declaration of method, 
*               constant and inclusion of the system level 
*               header file. 
********************************************************************/
#ifndef HOSTDETAILUTIL_H
#define HOSTDETAILUTIL_H

//Inclusion of the system level header file
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/time.h>


//For Signal Handling
#include <signal.h>

// User level Constants Used for the Socket Server and Client Application
#define IPADDR_MAX_LEN 32
#define SERVER_IP_ADDR "localhost"
#define SERVER_PORT 19819
#define UDP_SERVER_PORT 19211
#define BACKLOG 15
#define SOCK_FAMILY AF_INET
#define SOCK_TYPE SOCK_STREAM
#define SOCK_UDP_TYPE SOCK_DGRAM
#define MAX_HOST_NAME 256
#define SLEEP_TIME 20
#define TCP_LB_PORT 19819

//User defined utility methods used in Server side
int getIPAdressFromHostName(char* hostName, char *IPAddr);
void signal_callback_handler(int signum);
void processClientRequest(int sock);
void processUdpClientRequest(int sockFd);
/*
struct message{
    char req[100];
    struct timeval currTime;
};
*/
#endif

