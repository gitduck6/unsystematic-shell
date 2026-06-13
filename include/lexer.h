#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <command.h>
#include <internalcmd.h>
#include <sig_handler.h>

char * readline(FILE * fd);
int tokenize(char *string, Command* target);

#endif