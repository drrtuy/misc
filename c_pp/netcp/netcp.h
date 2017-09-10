#ifndef H_NETCP

#define H_NETCP

#define ARGS "mch:p:s:d:"

#define on_err(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(EXIT_FAILURE); }
#define log(log_level, ...) { fprintf(stdout, __VA_ARGS__); }

#include <sys/types.h>
#include <stdbool.h>

#define BUF_LEN 4096
#define BUF_SMALL 32
#define PORT_LEN 6

#define LOG_EMERG   0   /* system is unusable */
#define LOG_ALERT   1   /* action must be taken immediately */
#define LOG_CRIT    2   /* critical conditions */
#define LOG_ERR     3   /* error conditions */
#define LOG_WARNING 4   /* warning conditions */
#define LOG_NOTICE  5   /* normal but significant condition */
#define LOG_INFO    6   /* informational */
#define LOG_DEBUG   7   /* debug-level messages */

#define READ_CMD 2
#define WRITE_CMD 3

typedef enum { client, server, read_cmd, write_cmd } task_type_t;

typedef struct
{
    bool slow; 
    char *host;
    u_int16_t port;
    task_type_t type;
    char *sfile;
    char *dfile;
} task_t;

void
print_task(task_t *task);

task_t *
arg_parser(int argc, char **argv, char *args);

void
start_server(task_t *task);

void
start_client(task_t *task);

int
process_msg(int fd);

task_t *
parse_msg(void *buf, ssize_t msg_size);

int
process_task(int fd, task_t *task);

int
process_write_cmd(int fd, task_t *task);

int
process_send(int fd, void *buf, int bufsize);

int
client_read_cmd(int fd, task_t *task);
#endif
