#ifndef H_EXEC
#define H_EXEC

#include <libpq-fe.h>

#define MAX_L 256
#define PARENT_SLEEP_TO 5
#define ONE 1

void *
doGetShared(size_t size);

PGconn *
doConnect(const char *connstring);

void
doGracefulExit(PGconn *conn);

char *
doGetConnString(const char *hostname);

char *
doGetLocalConnString();

void
doChildRun(const char *target, void *shmem);

void
doParentRun(const char *hostname, void *shmem);

//void 
//logger(const char *msg);

void
notifyPerson(const char *localHostname, const char *quries, const char *contact);

void
doUpdateTask(const char *hostname, long int id);

#endif
