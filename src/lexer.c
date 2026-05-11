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
int tokenize(char *string, Command* target)
{
    size_t token_count = 0;
    size_t token_size = 4;
    target->argv = malloc(sizeof(char *) * token_size);
    if (target->argv == NULL) 
    {
        return -2;
    } 

    char * token = strtok(string," \t"); // either space or tab
    while (token != NULL)
    {
        target->argv[token_count] = token;
        token = strtok(NULL," \t");
        token_count++;

        if ((token_count + 1) >= token_size)
        {
            token_size *= 2;
            char **temp = realloc(target->argv,sizeof(char*) * token_size);
            if (temp == NULL) 
            {
                free(target->argv);
                return -1;
            } 
            else target->argv = temp;
        }
    }

    char ** temp = realloc(target->argv,sizeof(char*) * (token_count + 1) );
    if (temp != NULL) 
    {
        target->argv = temp;
    }
    // Lets just return it as was  in case of a realloc fail without freeing
    // since this part only attempts to lower the size, we already got more than enough memory anyway 

    target->argv[token_count] = NULL;
    target->input = NULL;
    target->output = NULL;

    for (size_t i = 0;i < token_count;i++)
    {
        if (target->argv[i] == NULL)
        continue;

        if ((!strcmp(target->argv[i],">")) && (target->output == NULL))
        {
            target->output = ((i+1) < token_count) ? target->argv[i+1] : NULL;
            target->argv[i] = NULL;
        }
        else
        if ((!strcmp(target->argv[i],"<")) && (target->input == NULL))
        {
            target->input = ((i+1) < token_count) ? target->argv[i+1] : NULL;
            target->argv[i] = NULL;
        }
    }
    return 0;
}