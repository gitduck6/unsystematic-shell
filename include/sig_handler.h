#ifndef SIG_HANDLER_H
#define SIG_HANDLER_H

#include <signal.h>
#include <stdio.h>

extern int current_sig;

void sigint_handler(int si);

#endif