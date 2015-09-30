/***********************************************************************************
* File name   : parse.h
* Author      : VAdmin Team
* Date        : 24th April 2015
* Location    : San Jose State University 
* Description : This file contains the declaration of all the
*               method for using for parsing the SAR output
*               and put it into the buffer that we are going to 
*               send to the server via load balancer
**********************************************************************************/
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>

using namespace std;
string ipAddr;
//Store the data for CPU
//utilization
typedef struct DataCpu {
    string time;
    string ampm;
    string cpu;
    string user;
    string nice;
    string system;
    string iowait;
    string steal;
    string idle;
}cpuUtilization;

//Store the Data for Queue Length
typedef struct queueLen {
    string time;
    string ampm;
    string runq;
    string plist;
    string ldavg;
    string blocked;
}queueLen;

//Store the Pageing Statistics
typedef struct DataPaging {
    string time;
    string ampm;
    string pgpgin;
    string pgpgout;
    string fault;
}pagingInfo;

//Store the Memory Utilization
typedef struct DataMem {
    string time;
    string ampm;
    string kbmemfree;
    string kbmemused;
    string memused;
    string kbbuffers;
    string kbcached;
    string kbcommit;
}memUtilization;

//Store the data for IO Report
typedef struct DataIO {
    string time;
    string ampm;
    string tps;
    string rtps;
    string wtps;
    string bread;
    string bwrtn;
}ioUtilization;

//Store the data for IO Report
struct DataDisk {
    string size;
    string used;
    string avail;
};

//This buffer we will sending across
//the socket
struct nodeData {
    string ipAddr;
    struct DataCpu dataCpu;
    struct queueLen queueLength;
    struct DataPaging dataPaging;
    struct DataMem dataMem;
    struct DataIO dataIO;
    struct DataDisk diskData;
};

struct bufNodeData{
    char time[50];
    char ipAddr[50];
    float cpu;
    float user;
    float nice;
    float system;
    float iowait;
    float steal;
    float idle;

    float runq;
    float plist;
    float ldavg;
    float blocked;

    float pgpgin;
    float pgpgout;
    float fault;

    float kbmemfree;
    float kbmemused;
    float memused;
    float kbbuffers;
    float kbcached;
    float kbcommit;

    float tps;
    float rtps;
    float wtps;
    float bread;
    float bwrtn;

    float size;
    float used;
    float avail;
};

struct nodeData data;
struct bufNodeData sendBuffer;
