#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdbool.h>

#include "netcp.h"

extern char *optarg;

/*
    Function parses the buf trying to extract the command.
    arg1 void* a pointer to a buffer recieved from a client.
    arg2 ssize_t buffer size.
    ret task_t* 
*/
task_t *
parse_msg(void *buf, ssize_t size)
{
    char *arg = (char *) malloc(sizeof(char)*size);
    arg = memset((void *)arg, '\0', size);
    if(!arg)
    {
        fprintf(stderr, "parse_msg(): malloc|memset problem\n");
        exit(EXIT_FAILURE);
    }

    task_type_t cmd;
    int rc;
    rc = sscanf((const char *)buf, "%u\t%s", (unsigned int *)&cmd, arg);
    if((rc < 2) || (rc == EOF))
    {
        fprintf(stderr, "parse_msg(): sscanf problem\n");
        free(arg);
        return NULL;
    }

    task_t *result = (task_t *) malloc(sizeof(task_t));
    if(!result)
    {
        fprintf(stderr, "parse_msg(): malloc problem\n");
        exit(EXIT_FAILURE);
    }

    result->type = cmd;
    if(cmd == read_cmd)
    {
        result->sfile = (char *)arg;  
    }
    else if(cmd == write_cmd)
    {
        result->sfile = (char *)arg;
    }
    else
    {
        log(LOG_WARNING, "process_msg(): unsupported command in the message.\n");
        free(arg);
        free(result);
        result = NULL;
    }
   
    if(result)
        print_task(result); 

    return result; 
}

/*
    The f() waits for 10 secs in select waiting for a client msg that f() saves to a disk.
    arg1 int FD
    arg2 task_t* task description.
    ret int return code. 0 = OK
*/
int 
process_write_cmd(int fd, task_t *task)
{
    FILE *local_file = fopen(task->sfile, "a");
    int rc = -1;
    if(!local_file)
    {
        log(LOG_ERR, "process_task(): can't open file %s to write.\n", task->sfile);
        perror("process_task():");
        return -1;
    }

    fd_set write_set;
        FD_ZERO(&write_set);
    FD_SET(fd, &write_set);

    struct timeval timeout = (struct timeval) { 10, 10000 };
    
    if (select (FD_SETSIZE, NULL, &write_set, NULL, &timeout) < 0)
    {
        on_err("process_write_cmd(): couldn't select\n");
        return -1;
    }

    int nbytes;
    void *buf[BUF_LEN];

    if(FD_ISSET(fd, &write_set))
    {
        nbytes = read(fd, buf, BUF_LEN-1);
        buf[nbytes] = '\0';
        if(nbytes > 0)
        {
            log(LOG_DEBUG, "process_write_cmd(): receive msg: [ %s ]\n", (char *) buf);
            fwrite(buf, sizeof(char), nbytes, local_file);
            rc = 1;
        }
        else if (nbytes == 0) // no future reading coz socket is closed
        {
            log(LOG_DEBUG, "process_write_cmd(): receive empty msg: [ %s ]\n", (char *) buf);
            rc = 0;
        }
        else if ((nbytes == -1) && (errno == EAGAIN))
        {
            rc = 1;
        }
        fclose(local_file);
    }

    return rc;
}

/*
    The f() executes a task it receives as its first arg.
    arg1 int FD
    arg2 task_t* task description.
    ret int return code. 0 = OK
*/
int
process_task(int fd, task_t *task)
{
    FILE *local_file;
    int rc = -1, nbytes;
    void *buf[BUF_LEN];
    switch(task->type)
    {
        case read_cmd:
            local_file = fopen(task->sfile, "r");
            if(!local_file)
            {
                log(LOG_ERR, "process_task(): can't open file %s to read.\n", task->sfile);
                perror("process_task():");
                rc = -1;
                break;
            }
            // TODO add checks
            while(!feof(local_file))
            {
                nbytes = fread(buf, sizeof(char), BUF_LEN, local_file);
                write(fd, buf, nbytes);
            }
            fclose(local_file);
            rc = 0;
            break;
        case write_cmd:
            while((rc = process_write_cmd(fd, task)) > 0)
            {
                usleep(500);
            }
            break;
        default:
            log(LOG_ERR, "process_task(): unsupported command.\n");
    }

    return rc;
}

/*
    The f() executes the task according with the cmd received from a connected client.
    arg1 int FD num to operate on.
    ret  int return code
*/
int
process_msg(int fd)
{
    ssize_t nbytes;
    char buf[BUF_LEN];
    task_t *task;
    int rc;

    if((nbytes = read(fd, (void *) buf, BUF_LEN)) < 0)
    {
        perror("process_msg() read():");
        return -1; // exit or return ??
    } 
    else if (nbytes == 0)
    {
        fprintf(stdout, "%s\n", "process_msg(): client disconnected.\n");
        return 1;
    }
    else
    {
        task = parse_msg(buf, nbytes);
        if((!task) || ((rc = process_task(fd, task)) != 0))
        {
            log(LOG_WARNING, "process_msg(): Cannot get or process the task.\n");
            return -1;
        }
    }
    return 0;
}

void
print_task(task_t *task)
{
    printf("type: %d, host %s, port %d", task->type, task->host, task->port);
    if(task->sfile)
         printf(" sfile %s", task->sfile);
    if(task->dfile)        
         printf(" dfile %s", task->dfile);

    printf("\n");
}

/*
    The f() parses args the binary gets.
    arg1 int argc
    arg2 char ** argv
    arg3 char * getopt's format string
    ret task_t * task description,
*/
task_t *
arg_parser(int argc, char **argv, char *args)
{
    //if(argc < 3)
    //    on_err("Usage netcp [mode] (host port|port) (src|dst)\n");

    task_t *result = (task_t *) calloc(1, sizeof(task_t));
    result->type = server;
    result->host = NULL;
    result->port = 0;
    result->sfile = NULL;
    result->dfile = NULL;
    result->slow = false;

    int c;
    while((c = getopt(argc, argv, args)) != -1)
    {
        switch(c)
        {
            case 'c':
                result->type = client;
                break;
            case 'm':
                result->slow = true;
                break;
            case 'h':
                result->host = optarg;
                break;
            case 'p':
                sscanf(optarg, "%d", (int *)&result->port);
                break;
            case 's':
                result->sfile = optarg;
                break;
            case 'd':
                result->dfile = optarg;
                break;
        }
    }

    // Set a client task type.
    if(result->type == client)
    {
        if(result->sfile)
        {
            result->type = write_cmd;
        }

        if(result->dfile)
        {
            result->type = read_cmd;
        }
    }

    print_task(result);
    return result;
}

/*
    The f() starts the server and process received commands in an endless loop.
    arg1 task_t* server task description.
*/
void
start_server(task_t *task)
{
    int server_fd;
    fd_set read_set, write_set, active_set;
    struct sockaddr_in server,client;    
    int rc, new;
    unsigned int size;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0)
        on_err("start_server(): couldn't create socket.\n");  

    server.sin_family = AF_INET;
    server.sin_port = htons(task->port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);    

    int opt_val = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);
    
    rc = bind(server_fd, (struct sockaddr *) &server, sizeof(server));   
    if(rc < 0)
        on_err("start_server(): couldn't bind\n");
    
    rc = listen(server_fd, 2);
    if(rc < 0)
        on_err("start_server(): couldn't listen\n");

    FD_ZERO(&active_set);
    FD_SET(server_fd, &active_set);

    struct timeval timeout = (struct timeval) { 5, 5000 };
    int sock_flags;
    for(;;)
    {
        if(task->slow)
            sleep(1);
        timeout = (struct timeval) { 5, 5000 };
        read_set = active_set;
        write_set = active_set;

        if (select (FD_SETSIZE, &read_set, &write_set, NULL, &timeout) < 0) 
        {
            on_err("start_server(): couldn't select\n");
        }
        for(int i = 0; i < 32; ++i)
        {
            if (FD_ISSET(i, &read_set))
            {
                if (i == server_fd){
                    size = sizeof (client);
                    new = accept (server_fd, (struct sockaddr *) &client, &size);
                    if (new < 0)
                    {
                        on_err("start_server(): couldn't accept\n");
                    }
                    fprintf(stdout, "Server: connect from host %s, port %hd.\n",
                         inet_ntoa (client.sin_addr),
                         ntohs (client.sin_port));
                    sock_flags = fcntl(new, F_GETFL, 0);
                    if((fcntl(new, F_SETFL, sock_flags | O_NONBLOCK)) < 0)
                    {
                        log(LOG_ERR, "start_server(): fail to set O_NONBLOCK for the sock.\n");
                    }
                    FD_SET (new, &active_set);
                } else {
                    rc = process_msg(i);
                    if(rc < 0)
                    {
                        fprintf(stdout, "start_server(): Cannot process the command.\n");
                        close(i);
                        FD_CLR(i, &active_set);
                    } 
                    else if (rc>=0)
                    {
                        log(LOG_DEBUG, "start_server(): Client disconnected.\n");
                        close(i);
                        FD_CLR(i, &active_set);
                    }
                    log(LOG_DEBUG, "start_server(): processed\n");
                }
            }
        }
    }

}

/*
    The f() sends the buffer contents.
    arg1 int fd
    arg2 void* buffer
    arg3 int buffer size
    ret int bytes sent OR -1 if any error
*/
int
process_send(int fd, void *buf, int size)
{
    int bytes_sent = 0, bytes_left = size;
    int nbytes;
    while (bytes_sent < size)
    {
        nbytes = send(fd, buf, bytes_left, 0);
        if(nbytes == -1)
            break;
        bytes_sent += nbytes;   
        bytes_left -= nbytes;
    } 
    
    return nbytes == -1?-1:bytes_sent;
}

/*
    The f() sends a file toa remote server. 
    arg1 int FD
    arg2 task_t *
    ret int RC - 0 is OK
*/
int
client_write_cmd(int fd, task_t *task)
{
    int rc = 0, nbytes = 0;
    int cmd_len = strlen(task->sfile)+3;
    char *cmd = (char *) malloc(sizeof(char) * cmd_len);
    char buf[BUF_LEN];
    // check
    snprintf(cmd, cmd_len, "%d %s", WRITE_CMD, task->sfile);     
    cmd[cmd_len] = '\0';

    int opt = 1;
    setsockopt(fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt));

    if((send(fd, cmd, cmd_len, 0)) == -1)
    {
        log(LOG_ERR, "client_write_cmd(): can't send the command.\n");
        perror("client_write_cmd():");
        exit(1);
    }

    FILE *local_file = fopen(task->sfile, "r");
    while(!feof(local_file))
    {
        nbytes = fread(buf, sizeof(char), BUF_LEN, local_file);    
        if((rc = process_send(fd, (void *)buf, nbytes)) < 0)
        {
            log(LOG_ERR, "client_write_cmd(): cant send.\n");
            perror("client_write_cmd():");
            rc = -1;
            break;
        }
    }

    fclose(local_file);
    return rc;
}

/*
    The f() gets a file from a remote server and sends it to stdout.
    arg1 int FD
    arg2 task_t *
    ret int RC - 0 is OK
*/
int client_read_cmd(int fd, task_t *task)
{
    int rc = 0, nbytes = 0;
    int cmd_len = strlen(task->dfile)+3;
    char *cmd = (char *) malloc(sizeof(char) * cmd_len);
    char buf[BUF_LEN+1]; 

    snprintf(cmd, cmd_len, "%d %s", READ_CMD, task->dfile);

    int opt = 1;
    setsockopt(fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt));

    if((send(fd, cmd, cmd_len, 0)) == -1)
    {
        log(LOG_ERR, "client_read_cmd(): can't send the command.\n");
        perror("client_read_cmd():");
        exit(1);
    }

    while(true)
    {
        nbytes = recv(fd, (void *) buf, BUF_LEN, 0);
        if(nbytes <= 0)
        {
            log(LOG_DEBUG, "client_read_cmd(): nbytes [ %d ].\n", nbytes);
            break;
        }
        else
        {
            buf[nbytes] = '\0';
            fprintf(stdout, "%s", buf);
        }
    }

    return rc;


}

void
start_client(task_t *task)
{
    int sockfd, rc;
    char port[PORT_LEN];
    struct addrinfo hints, *server;

    // getting socket   
    snprintf(port, 5, "%d", task->port); 
    port[5] = '\0'; 

    memset((void *)&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    if((rc = getaddrinfo(task->host, port, &hints, &server) != 0))
    {
        log(LOG_ERR, "start_client(): getaddrinfo error.\n"); 
        exit(1);
    }

    if((sockfd = socket(server->ai_family, server->ai_socktype,
 server->ai_protocol)) == -1)
    {
        log(LOG_ERR, "start_client(): socket() error.\n");
        perror("start_client(): ");
        exit(1);
    }
    
    if((connect(sockfd, server->ai_addr, server->ai_addrlen) == -1))
    {
        log(LOG_ERR, "start_client(): connect() error.\n");
        perror("start_client(): ");
        close(sockfd);
        exit(1);
    }

    // sending cmd
    switch(task->type)
    {
        case(write_cmd):
            rc = client_write_cmd(sockfd, task);
            break;
        case(read_cmd):
            rc = client_read_cmd(sockfd, task);
            break;
        default:
            rc = -1;
    }

    if(rc == -1)
    {
        close(sockfd);
        on_err("start_client(): Wrong task type.\n");
    }

}
