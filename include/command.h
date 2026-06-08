#ifndef COMMAND_H
#define COMMAND_H

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
// Macro that allows setenv to exist

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
int cmd_exit(char **argv);
int cmd_set(char **argv);
int cmd_help(char **argv);


extern internalCommand internal_commands[];
extern int icmd_count;

#endif