#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdlib.h>

#include "executer.h"

int main(int argc, char **argv)
{
    char *hostname;
    pid_t pid;
    void *shmem;
    int status;
    signed int lockFd;

    shmem = doGetShared(sizeof(long int));

    if(argc>1){
        hostname = argv[1];
    } else
        hostname = "localhost";

    if((lockFd = doSetFlock()) == -1){
        exit(1);
    }

    pid = fork();
    if(pid == 0){
        doChildRun(hostname, shmem);
        // Notify the parent that child has finished.
        *(long int *)shmem = 0;
    }
    else{
        doParentRun(hostname, shmem);
        wait(&status);
        munmap(shmem, sizeof(long int));
    } 

    doReleaseFlock();

    return 0;
}
