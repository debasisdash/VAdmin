/***********************************************************************************
* File name   : dbProxy.h
* Author      : VAdmin Team
* Date        : 24th April 2015
* Location    : San Jose State University 
* Description : This file contains the declaratin of all the
*               method for commiting data to the database. We will
*               be using this for the to invoke from the server.
**********************************************************************************/
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sqlite3.h>
#include <sstream>


#define INSERT_PROCESS_TBL "INSERT INTO Process (nodeAddr,runq_sz ,plist_sz ,ldavg,blocked ,readTime) values('"
#define INSERT_MEMORY_TBL "INSERT INTO Memory (nodeAddr,kbMemfree , kbMemused, Memused, kbBuffers, kbCached, kbCommit,readTime) values('"
#define INSERT_PAGING_TBL "INSERT INTO Paging (nodeAddr,pgpgin , pgpgout, fault, readTime) values('" 
#define INSERT_IOREPORT_TBL "INSERT INTO IOReport (nodeAddr,tps,rtps,wtps,bread,bwrtn,readTime) values('"
#define INSERT_CPU_TBL "INSERT INTO CPUStats(nodeAddr,user,nice,system,ioWait,steal,idle,readTime) values('"
#define INSERT_DISK_TBL "INSERT INTO DISK(nodeAddr, size, used, avail, readTime) vaues ('"




