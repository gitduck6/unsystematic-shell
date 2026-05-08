#include "lexer.h"

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
Command tokenize(char *string)
{
    size_t token_count = 0;
    size_t token_size = 4;
    char ** token_array = malloc(sizeof(char *) * token_size);
    if (token_array == NULL) 
    {
        return NULL;
    } 

    char * token = strtok(string," \t"); // either space or tab
    while (token != NULL)
    {
        token_array[token_count] = token;
        token = strtok(NULL," \t");
        token_count++;

        if ((token_count + 1) >= token_size)
        {
            token_size *= 2;
            char **temp = realloc(token_array,sizeof(char*) * token_size);
            if (temp == NULL) 
            {
                free(token_array);
                return NULL;
            } 
            else token_array = temp;
        }
    }

    char ** temp = realloc(token_array,sizeof(char*) * (token_count + 1) );
    if (temp != NULL) 
    {
        token_array = temp;
    }
    // Lets just return it as was  in case of a realloc fail without freeing
    // since this part only attempts to lower the size, we already got more than enough memory anyway 

    token_array[token_count] = NULL;
    return token_array;
}