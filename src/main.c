#include <stdlib.h>

#include "runcmd.h"
#include "lexer.h"

/*
    * Hello im really bad at this stuff so ima try to make a new larger project
    * it is a basic shell BUT this time it will be more standalone
    * instead of using the system() function (which relies on other shells such as ksh and dash from what i know)
    * rightnow my goal is to implement a simple sh clone, with pipes, redirects and everything
    * but who knows how far it will go
    * 
    * Currently does almost nothing but execute commands in a very rudimentary way
    * did i mention that im making this cos i was too stupid to read xv6's sh.c
    * 
    * Hello dear reader! the development is going nice :)
    * atleast i feel nice coding it
    * i never wrote a "devlog" or even read one, maybe i should try that sometimes
    * also i seperated some functions into different files
*/

int main(void)
{
    
    while (1)
    {
        char * command = readline(stdin);
        Command parsed_command = tokenize(command); 
        runcmd(parsed_command);

        free(parsed_command.argv);
        free(command);
    }

    return 0;
}
