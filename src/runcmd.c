#include "runcmd.h"

int runcmd(command cmd)
{
    __pid_t pid = fork();

    if (pid == 0)
    {
        execvp(cmd.argv[0],cmd.argv);
        return 0;
    }
    else if (pid > 0) 
    {
        wait(NULL);
        return 0;
    }
    else return -1;
}