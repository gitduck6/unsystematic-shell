#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
    * Hello im really bad at this stuff so ima try to make a new larger project
    * it is a basic shell BUT this time it will be more standalone
    * instead of using the system() function (which relies on other shells such as ksh and dash from what i know)
    * rightnow my goal is to implement a simple sh clone, with pipes, redirects and everything
    * but who knows how far it will go
*/

char * readline(FILE * fd)
{
    size_t size = 16;
    size_t len = 0;
    char * dest = malloc(size);
    if (dest == NULL) return NULL;

    char c;
    for (;((c = fgetc(fd)) != EOF) && (c != '\n');len++)
    {
        if ((len + 2) >= size)
        {
            size *= 2;
            char * temp = realloc(dest,size); 
            if (temp != NULL) dest = temp;
            else 
            {
                free(dest);
                return NULL;
            }
        }
        dest[len] = c;
    }
    dest[++len] = '\0';
    return dest;
}

/*
    attempts to return a cstring array in the {"Hello", "World", "!", NULL}; format
*/
char ** tokenize(char *string)
{
    size_t token_count = 0;
    size_t token_buffer = 4;
    char ** token_array = malloc(sizeof(char *) * token_buffer);

    char * token = strtok(string," \t"); // either space or tab
    while (token != NULL)
    {
        token_array[token_count] = token;
        token = strtok(NULL," \t");
        token_count++;
    }

    token_array[token_count] = NULL;
    return token_array;
}

int main(void)
{
    char * code = readline(stdin);
    execv("/usr/bin/ls", tokenize(code));
    free(code);
    return 0;
}
