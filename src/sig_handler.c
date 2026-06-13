#include <sig_handler.h>

int current_sig;

void sigint_handler(int si)
{
    (void)si;

    fputc('\n', stdout);
    return;
}