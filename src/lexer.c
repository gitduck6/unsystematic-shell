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
    Command token_struct;
    token_struct.argv = malloc(sizeof(char *) * token_size);
    if (token_struct.argv == NULL) 
    {
        return (Command){0};
    } 

    char * token = strtok(string," \t"); // either space or tab
    while (token != NULL)
    {
        token_struct.argv[token_count] = token;
        token = strtok(NULL," \t");
        token_count++;

        if ((token_count + 1) >= token_size)
        {
            token_size *= 2;
            char **temp = realloc(token_struct.argv,sizeof(char*) * token_size);
            if (temp == NULL) 
            {
                free(token_struct.argv);
                return (Command){0};
            } 
            else token_struct.argv = temp;
        }
    }

    char ** temp = realloc(token_struct.argv,sizeof(char*) * (token_count + 1) );
    if (temp != NULL) 
    {
        token_struct.argv = temp;
    }
    // Lets just return it as was  in case of a realloc fail without freeing
    // since this part only attempts to lower the size, we already got more than enough memory anyway 

    token_struct.argv[token_count] = NULL;
    token_struct.input = NULL;
    token_struct.output = NULL;

    for (size_t i = 0;i < token_count;i++)
    {
        if (!strcmp(token_struct.argv[i],">"))
        {
            token_struct.output = ((i+1) < token_count) ? token_struct.argv[i+1] : NULL;
            token_struct.argv[i] = NULL;
            break;
        }
        if (!strcmp(token_struct.argv[i],"<"))
        {
            token_struct.input = ((i+1) < token_count) ? token_struct.argv[i+1] : NULL;
            token_struct.argv[i] = NULL;
            break;
        }
    }
    return token_struct;
}