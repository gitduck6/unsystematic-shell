#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <signal.h>

#include "readline.h"
#include "runcmd.h"
#include "lexer.h"
#include "sig_handler.h"

/*
    * Hello im really bad at this stuff so ima try to make a new larger project
    * it is a basic shell BUT this time it will be more standalone
    * instead of using the system() function (which relies on other shells such as ksh and dash from what i know)
    * rightnow my goal is to implement a simple sh clone, with pipes, redirects and everything
    * but who knows how far it will go
    * 
    * Currently kinda parses and executes with ability to handle simple file i/o
    * did i mention that im making this cos i was too stupid to read xv6's sh.c
    * 
    * Hello dear reader! the development is going nice :)
    * atleast i feel nice coding it
    * i never wrote a "devlog" or even read one, maybe i should try that sometimes
    * also i seperated some functions into different files
    * ----
    * Sumrary of the main.c file as of 24 jun 2026:
    * This file doesnt handle much except stick everything together,
    * the first part sets the signal handler function to sigint_handler
    * it kinda handles everything but kinda also only sigint idk :3
    * 
    * next theres a while (1) loop which runs forever,
    * print the shell prompt, fflush so it shows up regardless
    * 
    * read line, if its empty continue
    * 
    * if there was a signal, remove that signal from the variable and restart the loop
    * 
    * tokenise shell input into a parsed command type, run this parsed command
    * free everything we need, and restart the loop
*/

int main(void)
{
    
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigaction(SIGINT, &sa, NULL);

    while (1)
    {
        printf(" %s ",SHELL_PROMPT);
        fflush(stdout);

        char * shell_input = readline(stdin);

        if (shell_input == NULL)
        {
            continue;
        }
        else 
        {
            if (*shell_input == '\0') continue;
        }

        if (current_sig)
        {
            current_sig = 0;
            free(shell_input);
            continue;
        }

        Command parsed_command;
        tokenize(shell_input, &parsed_command); 

        runcmd(parsed_command);

        free_tokens(parsed_command.argv);
        free(shell_input);
    }

    return 0;
}
