#include <readline.h>

char * readline(FILE * fd)
{
    size_t size = 16;
    size_t len = 0;
    char * dest = calloc(size,sizeof(char));
    if (dest == NULL) return NULL;

    int c;
    while ((c = fgetc(fd)) != '\n')
    {
        if (c == EOF)
        {
            if (current_sig == 2)
            {
                current_sig = 0;
                free(dest);
                return NULL;
            }
            if (current_sig == 0)
            {
                cmd_exit(NULL);
            }
        }

        if ((len + 2) >= size)
        {
            size *= 2;
            char * temp = realloc(dest,size * sizeof(char)); 
            if (temp != NULL) dest = temp;
            else 
            {
                free(dest);
                return NULL;
            }
        }
        dest[len++] = (char)c;
    }
    dest[len] = '\0';
    return dest;
}