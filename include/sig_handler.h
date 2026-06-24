#ifndef SIG_HANDLER_H
#define SIG_HANDLER_H

#include <signal.h>
#include <stdio.h>

extern int current_sig;

void sig_handler(int si);

#endif