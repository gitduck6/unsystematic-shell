#include "runcmd.h"

/*
    * In this documentation i will reference "sections" of the code with the following syntax:
    * // SECTION NAME:
    * ----
    * internal command:
    * the internal command part is quite simple once youve grasped all the other stuff it uses
    * it goes through the internal command list, 
    * if it finds an internal command with the same name as the inputted command,
    * execute that internal commands function (with the argv of the cmd) 
    * 
    * Credits: i learned about this name-functionpointer struct approach 
    * in the Vahix operating systems shell, so great thanks to that
    * ----
    * i/o redirection
    * If output not null, we assume its a filename
    * since the tokenizer sets it to NULL If no file redirection involved
    * and after assuming that its a filename we change out stdout to cmd.output
    * with the freopen function.
    * 
    * Same with the input for stdin
    * ----
    * creating the process:
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
    // (Check if its an) internal command:
    for (int i = 0;i < icmd_count;i++)
    {
        if (strcmp(internal_commands[i].name,cmd.argv[0]) == 0)
        {
            return internal_commands[i].execute(cmd.argv);
        }
    }

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