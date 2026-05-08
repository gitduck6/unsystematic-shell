#ifndef COMMAND_H
#define COMMAND_H
typedef struct command
{
    char ** argv;
    char *output;
    char *input;
}
Command;

#endif