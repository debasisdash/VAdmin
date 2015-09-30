/***********************************************************************************
* File name   : nodeClient.c
* Author      : VAdmin Team
* Date        : 24th April 2015
* Location    : San Jose State University 
* Description : This file contains the implementation of all the
*               required method for connecting to the server app
*               and sendig the system parameters to the from the
*               each individial clients.
**********************************************************************************/
#include "util.h"
#include "parse.h"

using namespace std;
/////////////////////////
void collectDiskData()
{
    int cnt = 0;
    system("df -H > /tmp/output.txt");
    ifstream ifile("/tmp/output.txt");
    cout << "---------: DISK Stat Details :------------" << endl;

    while(cnt < 7)
    {
        ++cnt;
        string temp;

        if(cnt == 1)
        {
            ifile >> temp >> temp >> temp >> temp >> temp >> temp >> temp;
        }
        else if(cnt == 6)
        {
            ifile >> temp
                >> data.diskData.size
                >> data.diskData.used
                >> data.diskData.avail
                >> temp
                >> temp;
        }
        else
        {
            ifile >> temp >> temp >> temp >> temp >> temp >> temp;
        }
        if(cnt == 6)
        {
            cout << "data: " 
                << data.diskData.size
                << ", "
                << data.diskData.used
                << ", " 
                << data.diskData.avail
                << endl;  
            cout << "\n\n";
            return;
        }
    }
}
void collectIOData()
{
    int cnt = 0;

    system("/usr/bin/sar -b  1 1 > /tmp/output.txt");
    ifstream ifile("/tmp/output.txt");
    cout << "---------: IO Stat Details :------------" << endl;

    while(cnt < 4)
    {
        ++cnt;
        string temp;

        if(cnt == 1)
        {
            ifile >> temp >> temp >> temp >> temp >> temp >> temp ;
        }
        else if(cnt == 2)
        {
            ifile >> temp;
        }
        else
        {
          ifile >> data.dataIO.time 
                >> data.dataIO.ampm 
                >> data.dataIO.tps 
                >> data.dataIO.rtps 
                >> data.dataIO.wtps 
                >> data.dataIO.bread
                >> data.dataIO.bwrtn;
        }
        if(cnt == 4)
        {
            cout << "data: " 
                << data.dataIO.time 
                << ", "
                << data.dataIO.ampm 
                << ", " 
                << data.dataIO.tps 
                << ", "
                << data.dataIO.rtps 
                << ", "
                << data.dataIO.wtps 
                << ", " 
                << data.dataIO.bread 
                << ", " 
                << data.dataIO.bwrtn 
                << endl;  
            cout << "\n\n";
            return;
        }
    }
}
void collectMemData()
{
    int cnt = 0;

    system("/usr/bin/sar -r  1 1 > /tmp/output.txt");
    ifstream ifile("/tmp/output.txt");
    cout << "---------: Memory Stat Details :------------" << endl;

    while(cnt < 4)
    {
        ++cnt;
        string temp;

        if(cnt == 1)
        {
            ifile >> temp >> temp >> temp >> temp >> temp >> temp ;
        }
        else if(cnt == 2)
        {
            ifile >> temp;
        }
        else
        {
          ifile >> data.dataMem.time 
                >> data.dataMem.ampm 
                >> data.dataMem.kbmemfree 
                >> data.dataMem.kbmemused 
                >> data.dataMem.memused 
                >> data.dataMem.kbbuffers
                >> data.dataMem.kbcached 
                >> data.dataMem.kbcommit 
                >> temp >> temp >> temp >> temp;
        }
        if(cnt == 4)
        {
            cout << "data: " 
                << data.dataMem.time 
                << ", " 
                << data.dataMem.ampm 
                << ", " 
                << data.dataMem.kbmemfree 
                << ", "
                << data.dataMem.kbmemused 
                << ", "
                << data.dataMem.memused 
                << ", " 
                << data.dataMem.kbbuffers 
                << ", " 
                << data.dataMem.kbcached 
                << ", " 
                << data.dataMem.kbcommit 
                << endl;  
            cout << "\n\n";
            return;
        }
    }
}
void collectQueueData()
{
    int cnt = 0;

    system("/usr/bin/sar -q  1 1 > /tmp/output.txt");
    ifstream ifile("/tmp/output.txt");
    cout << "---------: System Queue Details :------------" << endl;

    while(cnt < 4)
    {
        ++cnt;
        string temp;

        if(cnt == 1)
        {
            ifile >> temp >> temp >> temp >> temp >> temp >> temp ;
        }
        else if(cnt == 2)
        {
            ifile >> temp;
        }
        else
        {
          ifile >> data.queueLength.time 
                >> data.queueLength.ampm 
                >> data.queueLength.runq 
                >> data.queueLength.plist 
                >> temp 
                >> data.queueLength.ldavg 
                >>  temp 
                >> data.queueLength.blocked;
        }
        if(cnt == 4)
        {
            cout << "data: " 
                << data.queueLength.time 
                << ", " 
                << data.queueLength.ampm 
                << ", " 
                << data.queueLength.runq 
                << ", "
                << data.queueLength.plist 
                << ", "
                << data.queueLength.ldavg 
                << ", " 
                << data.queueLength.blocked 
                << endl;  
            cout << "\n\n";
            return;
        }
    }
}
void collectPagingStat()
{
    int cnt = 0;

    system("/usr/bin/sar -B  1 1 > /tmp/output.txt");
    ifstream ifile("/tmp/output.txt");
    cout << "---------: Paging Details :------------" << endl;

    while(cnt < 4)
    {
        ++cnt;
        string temp;

        if(cnt == 1)
        {
            ifile >> temp >> temp >> temp >> temp >> temp >> temp ;
        }
        else if(cnt == 2)
        {
            ifile >> temp;
        }
        else
        {
                ifile >> data.dataPaging.time 
                      >> data.dataPaging.ampm 
                      >> data.dataPaging.pgpgin 
                      >> data.dataPaging.pgpgout 
                      >> data.dataPaging.fault 
                      >> temp >> temp >> temp >> temp
                      >> temp >> temp;
        }
        if(cnt == 4)
        {
            cout << "data: " 
                << data.dataPaging.time 
                << ", " 
                << data.dataPaging.ampm 
                << ", " 
                << data.dataPaging.pgpgin 
                << ", "
                << data.dataPaging.pgpgout  
                << ", " 
                << data.dataPaging.fault 
                << endl;
            cout << "\n\n";
            return;
        }
    }
}

void collectCpuData()
{
    int cnt = 0;

    system("/usr/bin/sar -u  1 1 > /tmp/output.txt");
    ifstream ifile("/tmp/output.txt");
    cout << "---------: Cpu Details :------------" << endl;

    while(cnt < 4)
    {
        ++cnt;
        string temp;

        if(cnt == 1)
        {
            ifile >> temp >> temp >> temp >> temp >> temp >> temp ;
        }
        else if(cnt == 2)
        {
            ifile >> temp;
        }
        else
        {

            ifile >> data.dataCpu.time 
                  >> data.dataCpu.ampm 
                  >> data.dataCpu.cpu 
                  >> data.dataCpu.user 
                  >> data.dataCpu.nice 
                  >> data.dataCpu.system 
                  >> data.dataCpu.iowait 
                  >> data.dataCpu.steal 
                  >> data.dataCpu.idle;
        }
        if(cnt == 4)
        {
            cout << "data: " 
                << data.dataCpu.time 
                << ", "
                << data.dataCpu.ampm
                << ", " 
                << data.dataCpu.cpu
                << ", " 
                << data.dataCpu.user
                << ", " 
                << data.dataCpu.nice
                << ", " 
                << data.dataCpu.system
                << ", " 
                << data.dataCpu.iowait
                << ", " 
                << data.dataCpu.steal
                << ", " 
                << data.dataCpu.idle;
            cout << "\n\n";
            return;
        }

    }
}

void getIPAddr()
{
    //string ipAddr;
    system("hostname -I > /tmp/ipaddr.txt");
    ifstream ifile("/tmp/ipaddr.txt");
    ifile >> ipAddr;
    cout << ipAddr << endl;;
}
////////////////////////
void collectData()
{
    //Collecting all the data
    cout << "\nCollecting System Resource Usage for: ";
    getIPAddr();
    cout << "\n" << endl;
    collectCpuData();
    collectPagingStat();
    collectQueueData();
    collectMemData();
    collectIOData();
    collectDiskData();
}
void packToSendBuffer()
{
    memset(&sendBuffer,'0',sizeof(sendBuffer));
    strcpy(sendBuffer.time,data.dataCpu.time.c_str());

    int len = data.dataCpu.time.length();
    strcpy(sendBuffer.time+len,data.dataCpu.ampm.c_str());
    strcpy(sendBuffer.ipAddr,ipAddr.c_str());

    sendBuffer.cpu    = ::atof(data.dataCpu.cpu.c_str());
    sendBuffer.user   = ::atof(data.dataCpu.user.c_str());
    sendBuffer.nice   = ::atof(data.dataCpu.nice.c_str());
    sendBuffer.system = ::atof(data.dataCpu.system.c_str());
    sendBuffer.iowait = ::atof(data.dataCpu.iowait.c_str());
    sendBuffer.steal  = ::atof(data.dataCpu.steal.c_str());
    sendBuffer.idle   = ::atof(data.dataCpu.idle.c_str());

    sendBuffer.runq = ::atof(data.queueLength.runq.c_str());
    sendBuffer.plist = ::atof(data.queueLength.plist.c_str());
    sendBuffer.ldavg = ::atof(data.queueLength.ldavg.c_str());
    sendBuffer.blocked = ::atof(data.queueLength.blocked.c_str());

    sendBuffer.pgpgin= ::atof(data.dataPaging.pgpgin.c_str());
    sendBuffer.pgpgout = ::atof(data.dataPaging.pgpgout.c_str());
    sendBuffer.fault = ::atof(data.dataPaging.fault.c_str());

    sendBuffer.kbmemfree = ::atof(data.dataMem.kbmemfree.c_str());
    sendBuffer.kbmemused = ::atof(data.dataMem.kbmemused.c_str());
    sendBuffer.memused = ::atof(data.dataMem.memused.c_str());
    sendBuffer.kbbuffers = ::atof(data.dataMem.kbbuffers.c_str());
    sendBuffer.kbcached = ::atof(data.dataMem.kbcached.c_str());
    sendBuffer.kbcommit = ::atof(data.dataMem.kbcommit.c_str());

    sendBuffer.tps = ::atof(data.dataIO.tps.c_str());
    sendBuffer.rtps = ::atof(data.dataIO.rtps.c_str());
    sendBuffer.wtps = ::atof(data.dataIO.wtps.c_str());
    sendBuffer.bread = ::atof(data.dataIO.bread.c_str());
    sendBuffer.bwrtn = ::atof(data.dataIO.bwrtn.c_str());

    sendBuffer.size = ::atof(data.diskData.size.c_str());
    sendBuffer.used = ::atof(data.diskData.used.c_str());
    sendBuffer.avail = ::atof(data.diskData.avail.c_str());
}

int main(int argc , char *argv[])
{
    //This will store the IP and HOST name
    //char ipAddr[IPADDR_MAX_LEN] = {0};

    int sockFd;
    struct sockaddr_in serverAddr;

    memset((char *) &serverAddr,0, sizeof(serverAddr)); 
    //serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //Here I need to give the load balance IP Address
    //This is  the load balancer IP
    serverAddr.sin_addr.s_addr = inet_addr("192.168.102.129");
    serverAddr.sin_family = SOCK_FAMILY;
    serverAddr.sin_port = htons(SERVER_UDP_PORT);

    cout << "\n\n" << endl;
    cout << "#==================================================#" << endl;
    cout << "#=       VAdmin  (Virtual Admin Client)           =#" << endl;
    cout << "#=     Debasis, Juthika, Neeraj and Praktan       =#" << endl;
    cout << "#==================================================#" << endl;
    cout << "\n\n";
    while(1)
    {
        //Collecing all the system Data
        collectData();

        //Packing in to the buffer 
        //for sending across the socket
        packToSendBuffer();

        //Create Socket 
        if ((sockFd = socket(SOCK_FAMILY, SOCK_UDP_TYPE, 0)) < 0) 
        {    
            perror("Socket Creation Failed");
            exit(1);
        }

        if (( sendto(sockFd,                           // socketID
                        &sendBuffer,                   // Buffer
                        sizeof(sendBuffer),            // Sizeof Buffer
                        0,                             // For Flag
                        (struct sockaddr *)&serverAddr,// ServerAddr
                        sizeof(serverAddr))) < 0)      // Size of server address
        {
            perror("Not Able to Send Message to Server");
            close(sockFd);
            return 0;
        }       

        cout << "------- Sent Data Successfully to VAdmin Server -----------" << endl;

        //Closing the socket as desired job is completed
        close(sockFd);
        sleep(10);
    }
    //Successful Completion of the program
    return 0;
}

