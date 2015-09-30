/******************************************************************
* File name    : moniterServer.C
* Author       : VAdmin Team
* Date         : 24th april 2015
* Location     : San Jose State University
* Description  : This file contains the server which will respond to 
*                all the incoming request from all the nodeClient
*                and receive data from them. It will update the data
*                base by accepting all the legitimate data
******************************************************************/

//Inclusion of the required header file
#include "tcpUtil.h"
#include "pthread.h"
#include "parse.h"
#include "stdio.h"

using namespace std;
//###############
void InsertCPU(string nodeAddr,
               float user,
               float nice,
               float system,
               float iowait,
               float steal,
               float idle,
               string scan_time);

void InsertIOReport(string nodeAddr,
                    float tps,
                    float rtps,
                    float wtps,
                    float bread,
                    float bwrtn,
                    string scan_time);


void InsertPaging(string nodeAddr,
                  float pgpgin ,
                  float pgpgout,
                  float fault, 
                  string scan_time);


void InsertMemory(string nodeAddr,
                  float kbMemfree ,
                  float kbMemused,
                  float Memused, 
                  float kbBuffers, 
                  float kbCached, 
                  float kbCommit, 
                  string scan_time);

void InsertProcess(string nodeAddr,
                   float runq_sz,
                   float plist_sz,
                   float ldavg,  
                   float blocked,
                   string scan_time);
//###############
void processData(struct bufNodeData recvData);
void processClientRequest(int sock);
struct bufNodeData recvData;


void signal_callback_handler(int signum)
{
    printf("\nServer Stopped By The User...\n");
    exit(signum); 
}

int main(void)
{
    //Variable used for the socket connection
    int sockFd, clientLen;

    //Structure to hold the server and client details
    struct sockaddr_in serverAddr;

    //Local Variables
    int retVal = 0;

   //Registering the Signal Handler
   signal(SIGINT, signal_callback_handler);

   cout << "\n\n" << endl;
   cout << "#==================================================#" << endl;
   cout << "#=   VAdmin Monitoring and Managment Entitiy      =#" << endl;
   cout << "#=    Debasis, Juthika, Neeraj and Praktan        =#" << endl;
   cout << "#=                                                =#" << endl;
   cout << "#=   Collecting the below System Parameters       =#" << endl;
   cout << "#=   CPU Usage                                    =#" << endl;
   cout << "#=   Memory Usage Statistics                      =#" << endl;
   cout << "#=   Input/Output Statistics                      =#" << endl;
   cout << "#=   Paging Statistics                            =#" << endl;
   cout << "#=   System Queue length & stats details          =#" << endl;
   cout << "#==================================================#" << endl;
   cout << "\n\n\n";

   //Create a connection oriented socket
   if ((sockFd = socket(SOCK_FAMILY, SOCK_TYPE,0)) < 0) 
   {    
    perror("Server Socket Creation Failed..");
    exit(1);
   }

   // Resetting structure 
   memset((char *) &serverAddr,0, sizeof(serverAddr));
   
   //Fill the required data in the structure
   serverAddr.sin_family = SOCK_FAMILY;
   //serverAddr.sin_addr.s_addr = INADDR_ANY;
   
   //Connecting to load balancer
   serverAddr.sin_addr.s_addr = inet_addr("192.168.102.129");
   serverAddr.sin_port = htons(TCP_LB_PORT);

   if((connect(sockFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) < 0)
   {
    perror("Failed Connect to the server");
    exit(1);
    }


  //Keep looking for the client request
  while(1)
  {

      memset(&recvData,'0',sizeof(recvData));
      retVal = recv(sockFd, &recvData, sizeof(recvData), 0);
      if (retVal < 0)
      {
          perror("Receiving error..");
          close(sockFd);
          exit(1);
      }

      cout <<"----------------------------------------------" << endl;
      cout << "------ Receiving " << recvData.ipAddr << "  Data -------" << endl;
      cout <<"----------------------------------------------" << endl;

      //Processing the received Data
      processData(recvData);
  }
  //Closing the Server Socket
  close(sockFd);
  return 0;
}

void processData(struct bufNodeData recvData)
{
    //Processing IO Data
    cout <<"\n\n----------------------------------\n";
    cout << "Received Data From node: " << recvData.ipAddr  << endl
        << recvData.time
        << ", "
        << recvData.cpu
        << ", "
        << recvData.user
        << ", "
        << recvData.nice 
        << endl
        << recvData.system
        << ", "
        << recvData.iowait
        << ", "
        << recvData.steal
        << ", "
        << recvData.idle
        << ", "
        << recvData.runq
        << endl
        << recvData.plist
        << ", "
        << recvData.ldavg
        << ", "
        << recvData.blocked
        << ", "
        << recvData.pgpgin
        << ", "
        << recvData.pgpgout
        << endl
        << recvData.fault
        << ", "
        << recvData.kbmemfree
        << ", "
        << recvData.kbmemused
        << ", "
        << recvData.memused
        << ", "
        << recvData.kbbuffers
        << endl
        << recvData.kbcached
        << ", "
        << recvData.kbcommit
        << ", "
        << recvData.ldavg
        << ", "
        << recvData.tps 
        << ", "
        << recvData.rtps 
        << ", "
        << recvData.wtps 
        << ", " 
        << recvData.bread 
        << ", " 
        << recvData.bwrtn 
        << "\n" << endl;  

    //Updating the tbl_CPU
    InsertCPU(recvData.ipAddr, recvData.user, recvData.nice,recvData.system, recvData.iowait, recvData.steal, recvData.idle,recvData.time);
    InsertIOReport(recvData.ipAddr,recvData.tps, recvData.rtps, recvData.wtps, recvData.bread, recvData.bwrtn, recvData.time );
    InsertPaging(recvData.ipAddr,recvData.pgpgin, recvData.pgpgout, recvData.fault, recvData.time);
    InsertMemory(recvData.ipAddr,recvData.kbmemfree, recvData.kbmemused, recvData.memused, recvData.kbbuffers, recvData.kbcached, recvData.kbcommit, recvData.time);
    InsertProcess(recvData.ipAddr, recvData.runq, recvData.plist, recvData.ldavg ,recvData.blocked, recvData.time);
    cout << "Data updated to the Datbase" << endl;
    cout <<"----------------------------------\n\n";

}
