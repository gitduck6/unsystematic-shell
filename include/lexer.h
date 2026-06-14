#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <command.h>
#include <internalcmd.h>
#include <sig_handler.h>

#define N_TOKEN 64


char * readline(FILE * fd);
char ** lexer(char *string, size_t * count_p);
int tokenize(char *string, Command* target);

#endif