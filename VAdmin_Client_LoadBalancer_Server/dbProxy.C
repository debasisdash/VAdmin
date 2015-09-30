/***********************************************************************************
* File name   : dbProxy.C
* Author      : VAdmin Team
* Date        : 24th April 2015
* Location    : San Jose State University 
* Description : This file contains the implementation of all the
*               method for commiting data to the database. We will
*               be using this for the to invoke from the server.
**********************************************************************************/

//This is the required headerfile
#include "dbProxy.h"

using namespace std;

//Creating the global DAO
sqlite3 *db;

//Method to open the database connection
void opendb()
{
	int rc = sqlite3_open("/home/debasis/cmpe207/project/VAdminDB", &db);
    if(rc)
    {
        std::cout << "Can't open database\n";
    } else {
        //std::cout << "Open database successfully\n";
    }
}

//Close the database connection
void closedb()
{
    if(db)
    {
        sqlite3_close(db);
    }
}

//Inserting to CPUStats table
void InsertCPU(string nodeAddr,
               float user,
               float nice,
               float system,
               float iowait,
               float steal,
               float idle,
               string readTime)
{
    char *szErrMsg = 0;

    //Opening the Database connection
    opendb();

    std::stringstream insertQuery;
    sqlite3_stmt *insertStmt;
    insertQuery << INSERT_CPU_TBL
        << nodeAddr << "','"
        << user << "','"
        << nice << "','" 
        << system << "','" 
        << iowait <<"','" 
        << steal << "','" 
        << idle << "','" 
        << readTime  << "')";

    //Prepare the Query
    sqlite3_prepare(db, insertQuery.str().c_str(),-1, &insertStmt, NULL);
    
    //Update the Table
    if (sqlite3_step(insertStmt) != SQLITE_DONE)
        cout << "Didn't Insert Item! cpu" << endl;
    
    //Closing the database
    closedb();
}

//Inserting data to IOReport Table
void InsertIOReport(string nodeAddr,
                    float tps,
                    float rtps,
                    float wtps,
                    float bread,
                    float bwrtn,
                    string readTime)
{
    char *szErrMsg = 0;

    //Opening the Database connection
    opendb();
    std::stringstream insertQuery;
    sqlite3_stmt *insertStmt;
    insertQuery << INSERT_IOREPORT_TBL 
        << nodeAddr << "','" 
        << tps << "','" 
        << rtps << "','"
        << wtps << "','"
        << bread << "','"
        << bwrtn << "','" 
        << readTime  << "' )";


    //Prepare the Query
    sqlite3_prepare(db, insertQuery.str().c_str(),-1, &insertStmt, NULL);
    
    //Update the Table
    if (sqlite3_step(insertStmt) != SQLITE_DONE) 
        cout << "Didn't Insert Item io report!" << endl;
    
    //Closing the database
    closedb();
}

//Inserting Data to Paging Table
void InsertPaging(string nodeAddr,
                  float pgpgin ,
                  float pgpgout,
                  float fault, 
                  string readTime)
{
    char *szErrMsg = 0;
    
    //Opening the Database connection
    opendb();
    std::stringstream insertQuery;
    sqlite3_stmt *insertStmt;
    insertQuery << INSERT_PAGING_TBL 
        << nodeAddr << "','"
        << pgpgin   << "','"
        << pgpgout  << "','"
        << fault    << "','"
        << readTime << "')";

    //Prepare the Query
    sqlite3_prepare(db, insertQuery.str().c_str(),-1, &insertStmt, NULL);
    
    //Update the Table
    if (sqlite3_step(insertStmt) != SQLITE_DONE) 
        cout << "Didn't Insert Item! for paging table" << endl;
    
    //Closing of the database
    closedb();
}


//Inserting Data to Memory Table
void InsertMemory(string nodeAddr,
                  float kbMemfree ,
                  float kbMemused,
                  float Memused, 
                  float kbBuffers, 
                  float kbCached, 
                  float kbCommit, 
                  string readTime)
{
    char *szErrMsg = 0;
    
    //Opening the Database
    opendb();

    std::stringstream insertQuery;
    sqlite3_stmt *insertStmt;
    insertQuery << INSERT_MEMORY_TBL
        << nodeAddr  << "','" 
        << kbMemfree << "','"
        << kbMemused <<"','"
        << Memused   <<"','"
        << kbBuffers <<"','" 
        << kbCached  <<"','" 
        << kbCommit  <<"','"  
        << readTime << "' )";

    //Preparing the Data
    sqlite3_prepare(db, insertQuery.str().c_str(),-1, &insertStmt, NULL);
    
    //Commiting the data
    if (sqlite3_step(insertStmt) != SQLITE_DONE) 
        cout << "Didn't Insert Item!Memory table" << endl;
    
    //Closing the database
    closedb();
}

//Inserting data to Process Table
void InsertProcess(string nodeAddr,
                   float runq_sz,
                   float plist_sz,
                   float ldavg,  
                   float blocked,
                   string readTime)
{
    char *szErrMsg = 0;

    //Opening the database
    opendb();

    std::stringstream insertQuery;
    sqlite3_stmt *insertStmt;
    insertQuery << INSERT_PROCESS_TBL 
        << nodeAddr   <<"','" 
        << runq_sz    <<"','"
        << plist_sz   <<"','"
        << ldavg      <<"','"
        << blocked    <<"','" 
        << readTime  << "' )";

    //Preparing the Data
    sqlite3_prepare(db, insertQuery.str().c_str(),-1, &insertStmt, NULL);
    
    //Commiting the Data
    if (sqlite3_step(insertStmt) != SQLITE_DONE) 
        cout << "Didn't Insert Item!Process table" << endl;
    
    //Closing the database
    closedb();
}

//Method to Inser data to Disk table
void InsertDisk(string nodeAddr,
                   float size,
                   float used,
                   float avail,  
                   string readTime)
{
    char *szErrMsg = 0;

    //Opening the database
    opendb();

    std::stringstream insertQuery;
    sqlite3_stmt *insertStmt;
    insertQuery << INSERT_DISK_TBL 
        << size <<"','" 
        << used    <<"','"
        << avail   <<"','"
        << readTime  << "' )";

    //Preparing the Data
    sqlite3_prepare(db, insertQuery.str().c_str(),-1, &insertStmt, NULL);
    
    //Commiting the Data
    if (sqlite3_step(insertStmt) != SQLITE_DONE) 
        cout << "Didn't Insert Item! for Disk table" << endl;
    
    //Closing the database
    closedb();
}
