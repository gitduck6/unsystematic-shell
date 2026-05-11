#ifndef RUNCMD_H
#define RUNCMD_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

#include "command.h"

int runcmd(Command cmd);

#endif