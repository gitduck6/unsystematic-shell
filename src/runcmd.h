#ifndef RUNCMD_H
#define RUNCMD_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef struct command
{
    char ** argv;
    char *output;
    char *input;
}
command;


int runcmd(command cmd);

#endif