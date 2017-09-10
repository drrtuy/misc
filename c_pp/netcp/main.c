#include <stdlib.h>
#include <stdio.h>

#include "netcp.h"

int main(int argc, char **argv)
{
    task_t *task = arg_parser(argc, argv, ARGS);   
    switch(task->type)
    {
        case client:
        case write_cmd:
        case read_cmd:
            start_client(task);
            break;
        case server:
            start_server(task);
            break;
        default:
            on_err("Usage..\n");
    }

    return(EXIT_SUCCESS);
}
