#include <sig_handler.h>

int current_sig;

void sig_handler(int si)
{
    current_sig = si;

    fputc('\n', stdout);
    return;
}