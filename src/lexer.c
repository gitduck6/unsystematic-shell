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
    * tokenize function:
    * This function takes a string (specifically the user input we got from readline)
    * and parses it into a Command struct containing a tokenised string array,
    * input and output filenames.
    * 
    * id like to seperate this funciton into 2 sections,
    * firstly the raw tokenisation, where its just seperated into argv style string array
    * secondly the i/o tokenisation, where we decide where the output and input are
    * 
    * at first we need to understand what strtok does, so please look up the opengroup definition.
    * https://pubs.opengroup.org/onlinepubs/007904975/functions/strtok.html 
    * but ofc there are other sources too
    * what we do is, make a dynamic buffer that doubles when needed similar to readline's
    * but here its a char pointer array, each containing a string (what execv() expects)
    * each pointer gets a string via strtok, grows when needs to and doesnt stop till strtok returns a NULL 
    * (thats when it ends i think)
    * 
    * section2:
    * this part essentially  takes our raw token array
    * e.g. : argv={"ls", "-la", ">", "file.txt", NULL}, output=NULL, input=NULL
    * and turns it to a command struct containing something like
    * argv={"ls", "-la", NULL}, output="file.txt", input=NULL
    * (btw if input/output is null we use the regular std i/o's)
    * 
    * algorithm overview:
    * iterate through the tokens,
    * if we are at NULL (token end) break and exit the function;
    * if we see a > and output isnt defined
    * THEN define output as the next token IF IT EXISTS (aka is in our token_count range)
    * cut the rest of the token array cos we dont need the > in execution
    * 
    * if we see a < and input isnt defined
    * THEN define input as the next token IF IT EXISTS (aka is in our token_count range)
    * cut the rest of the token array cos we dont need the < in execution
    * 
    * PHEW, that was alot. 
    * also now thanks to this i think i see a few edge cases that may have unwanted behaviour
    * which i plan to hopefully fix 
    * AGAIN, if there are any inconsistencies while reading this, PLEASE leave an issue or a PR
    * id be happy if you did so! (or just text me if ur too lazy)
    * 
    * section 3: (enviroment variables)
    * This section might be the simplest one yet
    * 
    * goes through the token array, if it sees a token starting with $
    * assumes its a variable, get the variable via getenv()
    * and replace the token with the getenv's value
    * but when it doesnt exist, put a space in its place (THATS WHEN IT IS NULL)
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
    //section1:
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

    // resize to the exact needed size
    char ** temp = realloc(target->argv,sizeof(char*) * (token_count + 1) );
    if (temp != NULL) 
    {
        target->argv = temp;
    }
    // Lets just return it as was  in case of a realloc fail without freeing
    // since this part only attempts to lower the size, we already got more than enough memory anyway 

    //section2:
    target->argv[token_count] = NULL; //null terminate pointer array
    target->input = NULL;
    target->output = NULL;
    // Set to null to have it undefined initially

    for (size_t i = 0;i < token_count;i++)
    {
        if (target->argv[i] == NULL)
        break;

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

    //section3: (enviroment variables)
    for (size_t i = 0;i < token_count;i++)
    {
        if (target->argv[i] == NULL)
        break;

        if (target->argv[i][0] == '$')
        {
            // +1 in order to get the part after the dollar sign
            char * variable = getenv(target->argv[i]+1);
            
            if (variable != NULL)
            {
                target->argv[i] = variable;
            }
            else
                target->argv[i] = " ";
        }
    }

    return 0;
}