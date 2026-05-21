#include "command.h"

// basic cd implementation
int cmd_cd(char **argv)
{
    int status = chdir(argv[1]);
    if ( status != 0)
    {
        perror(argv[0]);
    }
    return status;
}

int cmd_exit(char **argv)
{
    (void)argv;

    printf("Exitting shell...\n");
    exit(0);
}

// An internal command to set enviroment variables
int cmd_set(char **argv)
{
    (void)argv;

    setenv(argv[1],argv[2],1);
}

internalCommand internal_commands[] =
{
    {"cd",cmd_cd},
    {"exit",cmd_exit},
    {"set", cmd_set}
};


int icmd_count = (sizeof(internal_commands)/ sizeof(internal_commands[0]));
// Calculates the amount of internal commands
