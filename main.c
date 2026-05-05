#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
    char * code = readline(stdin);
    printf("%s ",code);
}
