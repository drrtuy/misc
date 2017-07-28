#include <string.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "executer.h"

void *
doGetShared(size_t size)
{
    int prot = PROT_READ | PROT_WRITE;
    int vis = MAP_ANONYMOUS | MAP_SHARED;
    void *shmem = mmap(NULL, size, prot, vis, 0, 0);    
    if(!shmem){
        fprintf(stderr, "Error in doGetShared()\n");
        exit(1);
    }
    *(long int *) shmem = -1;
    return shmem;
}

void
doGracefulExit(PGconn *conn)
{
    PQfinish(conn);
    fprintf(stdout, "Gracefully disconnected from doGracefulExit()\n");
} 
 
/*
    Connect wrapper.
    TODO Mark the message with a connstring pieces.
*/
PGconn *
doConnect(const char *connstring)
{
    PGconn *conn = PQconnectdb(connstring);

    if(PQstatus(conn) != CONNECTION_OK){
        fprintf(stderr, "Connection failed at doConnect() with %s\n",
            PQerrorMessage(conn));
        doGracefulExit(conn);
    }    

    return conn;
}

/*
void
logger(const char *msg)
{
    FILE *log = fopen(LOG_FILE, "a");
    int result = fwrite((void *) msg, sizeof(char), strlen(msg), log);
    
    if(result == -1) {
        perror("Coudnl't write log at log()"); 
    }

    result = fclose(log);

    if(result == -1) {
        perror("Coudnl't close log at log()"); 
    }


}
*/

char *
doGetConnString(const char *hostname)
{
    char *result = (char *) malloc(MAX_L*sizeof(char));
    snprintf(result, MAX_L-33, "host=%s user=sched dbname=devops", hostname);
    return result;
}

char *
doGetLocalConnString(const char *dbname)
{
    char *result = (char *) malloc((MAX_L+1)*sizeof(char));
    // Hostname must be changed to a localhost.
    snprintf(result, MAX_L, "host=127.0.0.1 user=postgres dbname=%s", dbname);
    printf("doGetLocalConnString() conninfo: %s\n", result);
    return result;
}

/*
    Function quries the base for a next task and executes it. 
    All errors go to stderr and a msg describing the result goes to stdout.
    arg1 char* hostname of the host to execute query at.
    TODO Make the query external to change it w/o compilation.
         rename target to schedDbHost
*/
void
doChildRun(const char *target, void *shmem)
{
    char *connstring = doGetConnString(target);
    PGconn *conn;
    PGresult *res;
    conn = PQconnectdb(connstring);

    // msg to the parent that we have started
    *(long int*) shmem = -2;

    if(PQstatus(conn) != CONNECTION_OK){
        fprintf(stderr, "Remote connection failed at doChildRun() with %s\n",
            PQerrorMessage(conn));
        doGracefulExit(conn);
        return;
    }

    // Make the query external to change it w/o compilation.
    char *task_query_text = "WITH c AS(  "
    "SELECT id,query,updated_at "
    "FROM "
    "    sched.queries q "
    "WHERE "
    "    q.host=$$%s$$ "
    "AND "
    "    q.updated_at IS NULL "
    "LIMIT 1 "
    ") UPDATE  "
    "    sched.queries  "
    "SET  "
    "    updated_at=now(), priority=priority-1"
    "WHERE "
    "    id = (SELECT id FROM C)  "
    " AND priority > 0 "
    "RETURNING id,query,COALESCE(task#>>'{\"dbname\"}','postgres') as dbname; ";
   
    char *task_query = (char *) malloc(sizeof(char)*MAX_L*2);
    char hostname[MAX_L];
    gethostname(hostname, MAX_L-1);
    snprintf(task_query, MAX_L*2-1, task_query_text, hostname);  

    printf("%s\n", task_query);

    res = PQexec(conn, task_query);
    printf("result: %d\n", PQresultStatus(res));
   
    //doesn't complain if zero rows returned. 
    if(PQresultStatus(res) != PGRES_TUPLES_OK){
        fprintf(stderr, "Failed to retrieve scheduler data with %s\n", PQerrorMessage(conn));
        PQclear(res);
        doGracefulExit(conn);
        return;
    }

    if(!PQntuples(res)){
        printf("No queries to execute - exit here\n");
        PQclear(res);
        doGracefulExit(conn);
        return;
    }

    int queryLength = PQgetlength(res, 0, 1);
    int dbnameLength = PQgetlength(res, 0, 2);
    char *id = PQgetvalue(res, 0, 0);
    char queries[queryLength];
    strncpy(queries, PQgetvalue(res, 0, 1), queryLength);
    queries[queryLength] = '\0';
    char dbname[MAX_L];
    strncpy(dbname, PQgetvalue(res, 0, 2), dbnameLength);
    dbname[dbnameLength] = '\0';
    printf("id %s\tdbname %s\tqueries %s\n\r", id, dbname, queries);
    *(long int*) shmem = atoi(id);

    free(connstring);
    PQclear(res);
    PQfinish(conn);

    /* TODO check for an empty query.
    // Got no query so returns.
    if(!queries){
        doGracefulExit(conn);
        return;
    }
    */

    //Executing the query.
    connstring = doGetLocalConnString((const char *)dbname);
    conn = doConnect(connstring); 
    
    if(PQstatus(conn) != CONNECTION_OK){
            fprintf(stderr, "Local connection failed at doChildRun() with %s\n",
                PQerrorMessage(conn));
            doGracefulExit(conn);
            return;
    }

    res = PQexec(conn, queries);

    printf("result: %d\n", PQresultStatus(res));

    if((PQresultStatus(res) != PGRES_TUPLES_OK) && (PQresultStatus(res) != PGRES_COMMAND_OK)){
        fprintf(stderr, "Failed to execute the task query with %s\n", PQerrorMessage(conn));
        doGracefulExit(conn);
        free(connstring);
        return;
    }

    notifyPerson("dev", (const char *) queries, "drrtuy@ya.ru");

    PQclear(res);
    PQfinish(conn);
    free(connstring);
    
    //doGracefulExit(conn); 
}

void
notifyPerson(const char *localHostname, const char *quries, const char *contact)
{

} 

void                                                                                                                                                                
doParentRun(const char *hostname, void *shmem)
{
    long int *taskId = (long int *)shmem; 
    while(*taskId == -1)
        sleep(ONE);
   
    if(*taskId>0) 
        printf("Parent run id: %ld\n", *taskId);

    while(*taskId != 0){
        printf("Parent run id loop id: %ld\n", *taskId); 
        doUpdateTask(hostname, *taskId);
        sleep(PARENT_SLEEP_TO);
    }

}

void
doUpdateTask(const char *hostname, long int id)
{
    char *connstring = doGetConnString(hostname);
    PGconn *conn;
    PGresult *res;
    conn = PQconnectdb(connstring);

    if(PQstatus(conn) != CONNECTION_OK){
        fprintf(stderr, "Remote connection failed at doUpdateTask() with %s\n",
            PQerrorMessage(conn));
        doGracefulExit(conn);
    }

    // Make the query external to change it w/o compilation.
    char *query_text = "UPDATE  "
    "    sched.queries  "
    "SET  "
    "    updated_at=now() "
    "WHERE "
    "    id = %d; ";

    char update_query[MAX_L*2];
    
    sprintf(update_query, query_text, id); 
   
    //printf("%s\n", update_query);
 
    res = PQexec(conn, update_query);
    //printf("result: %d\n", PQresultStatus(res));
  
 
    //doesn't complain if zero rows returned. 
    //if(PQresultStatus(res) != PGRES_TUPLES_OK){
    //    fprintf(stderr, "Failed to retrieve scheduler data with %s\n", PQerrorMessage(conn));
        PQclear(res);
        doGracefulExit(conn);
        return;
    //}


}

signed int
doSetFlock()
{
    int fd = -1;   
 
    fd = open(LOCK_FILE, O_RDONLY | O_CREAT);
    if(flock(fd, LOCK_EX | LOCK_NB) != 0){
        if(errno == EWOULDBLOCK){
           fprintf(stderr, "doSetFlock(): Already locked.\n");
        } else {
            perror("doSetFlock(): ");
        }
        close(fd);
        fd = -1;
    }

    return fd;

}

void
doReleaseFlock(signed int fd)
{
    flock(fd, LOCK_UN);   
    close(fd);
}



