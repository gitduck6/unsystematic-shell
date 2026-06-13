#include <sig_handler.h>

int current_sig;

void sigint_handler(int si)
{
    current_sig = si;

    fputc('\n', stdout);
    return;
}