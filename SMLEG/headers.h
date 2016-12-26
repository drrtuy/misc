#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <postgresql/libpq-fe.h>
#include "include/SmApiBlocking_c.h"
#include "include/GeneralDefs.h"

#define MAXTHREADS 1 //SM allocates 5 threads to serve an instance
#define AWSTRLEN 128
#define SMLSTRLEN 32
#define SMRECONNTO 10
#define SMPORT 14374

typedef struct ThrArgStruct{	
	SMB_HANDLE SMRes;
	char *DBConnInfo;	
} ;

typedef struct SMData{
	char NameID[SMLSTRLEN];
	char NetID[SMLSTRLEN];
	char Policy[SMLSTRLEN];
	char SMDataID[AWSTRLEN];
	char TaskID[AWSTRLEN];
	char SMOptions[AWSTRLEN];
	bool WasSent;
};
extern int DBConnIsAlive(PGconn *DBconn);
extern int SMConnIsAlive();
extern int GetLEGData(struct SMData *SMDataEntry, PGconn *DBconn);
extern int SendLEGData(struct SMData *SMDataEntry, SMB_HANDLE smAPI);
extern void DBSetResult(struct SMData *SMDataEntry, PGconn *DBconn);
extern int isEmpty(char *String);


