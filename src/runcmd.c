#include "runcmd.h"

/*
    * In this documentation i will reference "sections" of the code with the following syntax:
    * // SECTION NAME:
    * ----
    * i/o redirection
    * If output not null, we assume its a filename
    * since the tokenizer sets it to NULL If no file redirection involved
    * and after assuming that its a filename we change out stdout to cmd.output
    * with the freopen function.
    * 
    * Same with the input for stdin
    * ----
    * creating the process
    * This shell follows a method common in unix systems:
    * - create a child (a clone via fork() )
    * - turn the child to a process we need (via execvp() )
    * - and as the parent, wait till the child exits
    * NOTE: return value of fork is:
    * - 0 for the child
    * - PID of the child for the parent
    * - and a negative value in case of failiure
*/

int runcmd(Command cmd)
{    
    // creating the process:
    __pid_t pid = fork();

    if (pid == 0)
    {
        // i/o redirection:
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