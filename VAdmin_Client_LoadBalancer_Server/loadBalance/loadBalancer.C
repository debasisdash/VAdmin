/***********************************************************************************
* File name   : loadBalancer.C
* Author      : Debasis Dash
* Date        : 26th April 2015
* Location    : San Jose State University 
* Description : This file contains the implementation of all the
*               for multi-threaded implementation using mutex and
*               conditional varibale. This program will hanfle the 
*               incoming UDP traffic from the client node and add
*               into the dataPool, do auto-registering for the servers
*               route the incoming packet to the servers. 
**********************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include "util.h"
#include "parse.h"
#include <queue> 
#include <vector>

using namespace std;

//LoadBalancer Queue
std::queue<bufNodeData> dataPool;
std::vector<int> serverPool;
pthread_mutex_t dp_lock;
pthread_cond_t dp_cv;
int dummy = 0;

//Variable used for the socket connection
int tcpSock, udpSock;

//Structure to hold the server and client details
struct sockaddr_in tcpServerAddr, clientAddr, udpServerAddr, udpClientAddr;

//This is the message type to interact btween server and client
struct message msg;
static int counter;

void passiveTCPServer();
void passiveUDPServer();
int processTcpRequest(int sockFd);
int processUdpRequest(int sock);
void* processTCPClientReq(void* sock);
void* processUDPClientReq(void* sock);
void signal_callback_handler(int signum);
void* routeToServer(void*);

void sendMsgtoServerRR(bufNodeData data)
{
    if(serverPool.size() != 0)
    {
        //This will ensure for the Round Roubin method
        //to send data to registerd server
        if(counter == serverPool.size())
        {
            counter = 0;
        }

        int ret = send(serverPool[counter], &data, sizeof(bufNodeData),0);
        if(ret < 0 )
         {
             perror("Sending error...");
             return;
         }
         counter++;
    }
}
void* routeToServer(void* data)
{
    bufNodeData buff;
    int sock;
    //This code will keep running continiously
    while(1)
    {
        //Aquiring the mutex lock
        pthread_mutex_lock(&dp_lock);

        if(!(dataPool.empty()))
        {
            //Data is available to send
            if(!(serverPool.empty()))
            {
                //Sever Connections are available
                while(!(dataPool.empty()))
                {
                    buff = dataPool.front();
                    dataPool.pop();
                    sendMsgtoServerRR(buff);
                }
            }
            else
            {
                cout << "No Server Connection" << endl;
            }

        }
        else
        {
            //cout << "Load Balancer Sent All the Client Data to Server" << endl;
            pthread_cond_wait(&dp_cv, &dp_lock);
            sched_yield();

            //We have to resume from where we left
            if(!(serverPool.empty()))
            {
                //Sever Connections are available
                while(!(dataPool.empty()))
                {
                    buff = dataPool.front();
                    dataPool.pop();
                    sendMsgtoServerRR(buff);
                }
            }
        }

        //Releasing the Lock
        pthread_mutex_unlock(&dp_lock);

        //Sleep for some time
        sleep(1);
    }
}

int processTcpRequest(int sockFd)
{
    int newSockFd;
    socklen_t clientLen = sizeof(clientAddr);

    if((newSockFd = accept(sockFd, (struct sockaddr *)&clientAddr, &clientLen)) < 0)
    {
        perror("Accept Failed");
        cout << "Receive Error in VAdmin Connectio  Accept..Continueing Again" << endl;
        return 0;
    }

    //Adding the server pool
    serverPool.push_back(newSockFd);
    printf("VAdmin Server Request Accepted..\n\n");
    printf("Server with IP Address %s Registered with Load Balancer\n", inet_ntoa(clientAddr.sin_addr));
    return SUCCESS;

    /*
    *arg = newSockFd;

    //Creating a thread to start giving the TCP Response
    pthread_create(&tcpWorker, NULL, processTCPClientReq,(void*)arg);
    */
}
int processUdpRequest(int sock)
{
   int* arg = (int *)malloc(sizeof(int));
   *arg = sock;
   pthread_t udpWorker;

    //Creating a thread to start giving the UDP Response
    pthread_create(&udpWorker, NULL, processUDPClientReq,(void*)arg);
    return SUCCESS;
}
void* processTCPClientReq(void* sockParam)
{
    //This will contain the size of the clientAddr required by accept call
    socklen_t clientLen = sizeof(clientAddr);
    int newSockFd;
    int sockFd = *((int *) sockParam);

    if((newSockFd = accept(sockFd, (struct sockaddr *)&clientAddr, &clientLen)) < 0)
    {
        perror("Accept Failed");
        cout << "Receive Error in VAdmin Connectio  Accept..Continueing Again" << endl;
    }

    //Adding the server pool
    serverPool.push_back(newSockFd);
    printf("VAdmin Server Request Accepted..\n\n");
    printf("Registered with VAdmin IP Address: %s \n", inet_ntoa(clientAddr.sin_addr));

    //This is nothing to do
    //pthread_exit(sockParam);
    //return (sockParam);
}

void* processUDPClientReq(void* sockParam)
{
    int sock = *((int*) sockParam);

    //defining the varibale to hold the data
    struct bufNodeData msg;

    //This will contain the size of the clientAddr required by accept call
    socklen_t clientLen = sizeof(clientAddr);

    //Waiting to receive the request from the client socket
    if(recvfrom(sock,                        // socketID
                &msg,                          // Buffer
                sizeof(msg),                   // Sizeof Buffer
                0,                             // For Flag
                (struct sockaddr *)&clientAddr,// ClientAddr
                &clientLen)            // length of ClientAddr
            == -1)
    {
        perror("recvfrom call failed..");

    }

    printf("Received Request From the UDP Client .. Processing..\n");
    printf("Client IP Address: %s \n", inet_ntoa(clientAddr.sin_addr));
    printf("Client Port Number: %d \n\n\n", ntohs(clientAddr.sin_port));

    //Aquiring the mutex lock
    pthread_mutex_lock(&dp_lock);

    //Need to put in the delivery queue
    dataPool.push(msg);

    //Releaseing the mutex lock
    pthread_mutex_unlock(&dp_lock);

    //signlaing the waiting thread
    pthread_cond_signal(&dp_cv);

    pthread_exit(NULL);
}

void passiveTCPServer()
{
    //Create a connection oriented socket
    if ((tcpSock = socket(SOCK_FAMILY, SOCK_TCP_TYPE,0)) < 0) 
    {    
        perror("Server Socket Creation Failed..");
        exit(FAILURE);
    }
    // Resetting structure 
    memset((char *) &tcpServerAddr,0, sizeof(tcpServerAddr));

    //Fill the required data in the structure
    tcpServerAddr.sin_family = SOCK_FAMILY;
    //tcpServerAddr.sin_addr.s_addr = INADDR_ANY;
    tcpServerAddr.sin_addr.s_addr = inet_addr("192.168.102.129");
    tcpServerAddr.sin_port = htons(SERVER_TCP_PORT);

    //Bind the TCP server socket to the given previous defined port
    if (bind(tcpSock,(struct sockaddr *) &tcpServerAddr, sizeof(tcpServerAddr)) < 0) 
    {
        close(tcpSock);
        perror("TCP Bind failed..");
        exit(FAILURE);
    }

    //Listen in the server socket
    if (listen(tcpSock, BACKLOG) < 0) 
    {
        perror("Listen failed..");
        exit(FAILURE);
    }
    printf("TCP Socket:%d  Bind and Listen Succecssful on port %d\n", tcpSock, SERVER_TCP_PORT);
}
void passiveUDPServer()
{
    //Creating the UDP Socket 
    if ((udpSock = socket(SOCK_FAMILY, SOCK_UDP_TYPE,0)) < 0) 
    {    
        perror("Server Socket Creation Failed..");
        exit(FAILURE);
    }

    // Resetting structure 
    memset((char *) &udpServerAddr,0, sizeof(udpServerAddr));

    //Fill the required data in the structure
    udpServerAddr.sin_family = SOCK_FAMILY;
    //udpServerAddr.sin_addr.s_addr = INADDR_ANY;
    udpServerAddr.sin_addr.s_addr = inet_addr("192.168.102.129");
    udpServerAddr.sin_port = htons(SERVER_UDP_PORT);

    //Bind the UDP server socket to the given previous defined port
    if (bind(udpSock,(struct sockaddr *) &udpServerAddr, sizeof(udpServerAddr)) < 0) 
    {
        close(udpSock);
        perror("UDP Bind failed..");
        exit(FAILURE);
    }
    printf("UDP Socket:%d  Bind Succecssful on port:%d \n", udpSock, SERVER_UDP_PORT);
}

int main(void)
{

    //Read FDs for the select call
    fd_set rfds, afds;
    struct timeval tv;
    int retval;

    //Initializing the readFds list
    FD_ZERO(&rfds);
    FD_ZERO(&afds);

    //Wait up to five seconds
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    //Initializing the mutex and conditional variable
    pthread_mutex_init(&dp_lock, NULL);
    pthread_cond_init (&dp_cv, NULL);


    //Printing the banner
    printf("\nVirtual Administrator Load Balancer Starting\nPress Ctrl + C to stop the server....\n");

    //Registering the Signal Handler
    signal(SIGINT, signal_callback_handler);

    //Creating TCP and UDP server socket
    passiveTCPServer();
    passiveUDPServer();

    int maxFd = getdtablesize();

    //Creating Thread to send the data to the socket
    int temp =0;
    pthread_t tcpServWorker;
    int* arg = (int *)malloc(sizeof(int));
    *arg = temp;

    //Creating a thread to start giving the TCP Response
    pthread_create(&tcpServWorker, NULL, routeToServer,(void*)arg);

    //Keep looking for the client request
    while(1)
    {
        //Setting the TCP and UDP socket in the readfds buffer
        FD_SET(udpSock,&afds);
        FD_SET(tcpSock,&afds);

        int retVal =  select(maxFd, &afds, NULL, NULL,&tv);

        if (retval == -1){
            perror("select()");
            exit (FAILURE);
        }
        else{
            //Start Serving for a new TCP connection
            if(FD_ISSET(tcpSock, &afds))
                processTcpRequest(tcpSock);

            //Start Serving for a new UDP connectopn
            if(FD_ISSET(udpSock, &afds))
                processUdpRequest(udpSock);
        }
    }
    //Closing the Server Socket
    close(tcpSock);
    close(udpSock);

    return SUCCESS;
}

void signal_callback_handler(int signum)
{
    printf("\nLoad Balancer Stopped By The User...\n");

    //Closing the Server Socket
    close(tcpSock);
    close(udpSock);
    exit(signum); 
}
