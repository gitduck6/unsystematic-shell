#include "runcmd.h"

int runcmd(char ** argv)
{
    __pid_t pid = fork();

    if (pid == 0)
    {
        execv(argv[0],argv);
    }
    else if (pid > 0) wait(NULL);
    else return -1;
}