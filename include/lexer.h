#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

char * readline(FILE * fd);
Command tokenize(char *string);

#endif