#include "internalcmd.h"


static char * getcwd_physical(void)
{
    size_t size = 64;
    char *buff = malloc(size);

    while (getcwd(buff,size) == NULL)
    {

        if (errno != ERANGE) 
        {
            perror("range");
            free(buff);
            exit(-1);
        }

        size*=2;
        char * temp = realloc(buff,size);
        if (temp == NULL)
        {
            perror("memory");
            free(buff);
            exit(-2);
        }
        buff = temp;
    }

    return buff;
}

// basic cd implementation
int cmd_cd(char **argv)
{
    char * addr;
    if (argv[1] == NULL)
        addr = getenv("HOME");
    else
        addr = argv[1];

    int status = chdir(addr);

    if (status < 0)
    {
        perror(argv[0]);
    }
    else
    {
        setenv("PWD", getcwd_physical(), 1);
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

    if ((argv[1] != NULL) && (argv[2] != NULL)) 
        setenv(argv[1],argv[2],1);
    else
    {
        fprintf(stderr,"Usage: %s [variable name] [new value]\n",argv[0]);
        return -1;
    }

    return 0;
}

int cmd_help(char **argv)
{
    (void)argv;

    char *msg = 
    "Ushell - Unsystematic Unix Shell (Havent thought of a name yet)\n"
    "Use \"man command name\" to find out about a command,\n"
    "this is just the shell's help menu!\n"
    "The internal commands are as follows:\n\n"

    "cd [directory]\n"
    "\t-Changes directory to the specified one\n"

    "exit\n"
    "\t-Exits the shell\n"

    "set [varname] [new value]\n"
    "\t-Sets a variable to a new value\n"

    "help\n"
    "\t-Display this menu\n"
    "For more information visit: https://github.com/gitduck6/unnamed-shell1\n";

    printf("%s",msg);
    return 0;
}


internalCommand internal_commands[] =
{
    {"cd", cmd_cd},
    {"exit", cmd_exit},
    {"set", cmd_set},
    {"help", cmd_help}
};


int icmd_count = (sizeof(internal_commands)/ sizeof(internal_commands[0]));
// Calculates the amount of internal commands