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

internalCommand internal_commands[] =
{
    {"cd",cmd_cd}
};


int icmd_count = (sizeof(internal_commands)/ sizeof(internal_commands[0]));
// Calculates the amount of internal commands
