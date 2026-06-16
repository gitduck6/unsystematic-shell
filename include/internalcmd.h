#ifndef INTERNALCMD_H
#define INTERNALCMD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

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