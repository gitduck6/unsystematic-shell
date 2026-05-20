#ifndef RUNCMD_H
#define RUNCMD_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"

#define SHELL_PROMPT "%"

int runcmd(Command cmd);

#endif