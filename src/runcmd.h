#ifndef RUNCMD_H
#define RUNCMD_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int runcmd(char ** argv);

#endif