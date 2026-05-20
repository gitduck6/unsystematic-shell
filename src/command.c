#include "command.h"

int change_dir(char **argv)
{
    int status = chdir(argv[1]);
    if ( status != 0)
    {
        perror(argv[0]);
    }
    return status;
}
