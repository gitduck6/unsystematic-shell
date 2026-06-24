#include <sig_handler.h>

int current_sig;

void sig_handler(int si)
{
    current_sig = si;

    if (current_sig == SIGINT) fputc('\n', stdout);
    return;
}