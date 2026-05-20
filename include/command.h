#ifndef COMMAND_H
#define COMMAND_H

#include <unistd.h>
#include <stdio.h>

typedef struct command
{
    char ** argv;
    char *output;
    char *input;
}
Command;

typedef struct
{
    const char * name;
    int (*execute)(char **argv);
}
internalCommand;

int cmd_cd(char **argv);

extern internalCommand internal_commands[];
extern int icmd_count;

#endif