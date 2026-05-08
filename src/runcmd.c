#include "runcmd.h"

int runcmd(char ** argv)
{
    __pid_t pid = fork();

    if (pid == 0)
    {
        execvp(argv[0],argv);
        return 0;
    }
    else if (pid > 0) 
    {
        wait(NULL);
        return 0;
    }
    else return -1;
}