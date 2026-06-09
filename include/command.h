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

#endif