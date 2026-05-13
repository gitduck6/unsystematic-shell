#include "lexer.h"

/*
    * Hello in this text i will attept to document the functions in this file,
    * ill document it in a format similar runcmd.c
    * ----
    * readline function:
    * this function uses a dynamic approach to get everything 
    * from the terminal input to a buffer.
    * after which it will tokenise said input and later execute it
    * 
    * the algorithm initially creates a 16 byte buffer
    * (also use calloc since malloc would print some garbage values)
    * gets a character from the FD untill the character is a EOF or a newline
    * IF len (the amount of letters we have already taken) is almost as large as our buffer
    * double the size of the buffer
    * after this just make the character position we are at to the character we just got
    * 
    * after finally reaching an EOF or newline. just NULL terminate the string we made for safety
    * and return the string.
    * 
    * P.S.: sometimes i cant even read what i wrote, 
    * so please leave an issue/PR if any part is ambigious.
    * Thank you!
    * ----
    *
    * 
*/

char * readline(FILE * fd)
{
    size_t size = 16;
    size_t len = 0;
    char * dest = calloc(size,sizeof(char));
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