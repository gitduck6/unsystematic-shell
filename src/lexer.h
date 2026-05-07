#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * readline(FILE * fd);
char ** tokenize(char *string);

#endif