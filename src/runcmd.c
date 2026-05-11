#include "runcmd.h"

int runcmd(Command cmd)
{
    __pid_t pid = fork();

    if (pid == 0)
    {
        if (cmd.output != NULL)
            freopen(cmd.output,"w",stdout);
            
        if (cmd.input != NULL)
            freopen(cmd.input,"r",stdin);
        
        execvp(cmd.argv[0],cmd.argv);

        perror(cmd.argv[0]);
        exit(1);
        return 0;
    }
    else if (pid > 0) 
    {
        wait(NULL);
        return 0;
    }
    else return -1;
}